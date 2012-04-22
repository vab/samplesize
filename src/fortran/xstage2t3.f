
! 2T3: TWO-STAGE STUDY: STOP EARLY TO CONCLUDE H0 OR H1
!  This program determines the optimal sample size for a two-stage test
!  of H0:p = p0 vs H1:p > p0
!
!  The design is as follows:
!  Accrue n1 pts.
!  If there are too few responders (S1<=a1-1), permanently stop
!  the study for lack of activity.
!  If S1>=b1+1, conclude H1.
!  If a1<=S1<=b1, accrue n2 additional pts.
!  If S1+S2>=b2+1, conclude H1.
!  If S1+S2<=b2, there is insufficient evidence to conclude H1.
!
!  alpha = pow(0) = the significance level of the test
!  1-beta = pow(1) = power when p = p1 and p1> p0
!  prob(p)=P(a1<=S1>=b1, S1+S2>=b2+1 | p )
!

      integer a1,a2,b1,b2,a11,b11,aa1,abest, maxn
      real(8) p(2)
      real(8) q(2)
      real(8) pow(2), delta
      real(8) prob(2)
      real(8) prob12, prob22
      real(8) sum(2,2)
      real(8) f(200,2,201)     ! f(n,i,x)=P(X<=x) when X:b(n,pi)
      real(8) b(200,2,201)     ! b(n,i,x)=P(X=x) when X:b(n,pi)
      pow(1)=.10d0               ! alpha-value
      pow(2)=.90d0               ! power when p = p(2)
      delta=0.20d0
      p(1)=.05                 ! H0: p = p(1)
      p(2)=p(1)+delta          ! p = p(2) is a value of p under H1

      maxn = nstage1(pow(1), pow(2), p(1), p(2))
      print*,'maxn=',maxn
      if (maxn .eq. 0) then
        print*,'No Solution'
        go to 20
      elseif (maxn .gt. 200) then
        print*,'ERROR - maxn is greater than 200'
        print*,'redimension the FORTRAN program'
        go to 20
      else
      endif

      do 1 i=1,2
        q(i)=1-p(i)
        b(1,i,1)=q(i)
        b(1,i,2)=p(i)
1     continue

      do 15 n1=2,maxn

        do 3 i=1,2
          b(n1,i,1)=q(i)**n1
          f(n1,i,1)=b(n1,i,1)
          n11=n1+1
          do 2 j=2,n11
            b(n1,i,j)=n1*p(i)*b(n1-1,i,j-1)/(j-1)
            f(n1,i,j)=f(n1,i,j-1)+b(n1,i,j)
2         continue
3       continue

        m1=n1-1
        do 10 b1=1,m1
          b11=b1+1
          do 11 a1=1,b1
            a11=a1+1
            do 12 n2=2,n1
              if(n1+n2 > maxn) go to 11   !stop and return to previous loop
              m2=n1+n2-1
              do 13 b2=b1,m2
!          print*,'n1=',n1,' b1=',b1,' a1=',a1,' n2=',n2,' b2=',b2
                do 4 ii=1,2
                  sum(ii,2)=0
                  do 5 i=a11,b11
                    k=b2-i+2
                    sum(ii,2)=sum(ii,2)+b(n1,ii,i)*f(n2,ii,k)
5                 continue
4               continue
                prob(1)=1-f(n1,1,a1)-sum(1,2)
                prob(2)=1-f(n1,2,a1)-sum(2,2)
!                if ((prob(1)<=pow(1)-.01) .or. (prob(1)>pow(1))) go to 13
                if (prob(1)>pow(1)) go to 13
                if (prob(2)<pow(2)) go to 13
                aa1=a1
30              abest=aa1
                prob12=prob(1)
                prob22=prob(2)
                aa1=aa1+1
                if (aa1>b1) go to 31
                k=b2-aa1+2
                prob(1)=prob(1)-b(n1,1,aa1)*(1-f(n2,1,k))
                prob(2)=prob(2)-b(n1,2,aa1)*(1-f(n2,2,k))
!                if ((prob(1)>=pow(1)-.01).and.(prob(2)>=pow(2))) go to 30
                if (prob(2)>=pow(2)) go to 30
31              continue
                e1=n1+n2*(f(n1,1,b1+1)-f(n1,1,abest))    ! e1=E(NM|P(1))
                e2=n1+n2*(f(n1,2,b1+1)-f(n1,2,abest))    ! e2=E(NM|P(2))
                asn=(e1+e2)/2                   ! asn=average sample size

      write(*,26) n1,abest,b1,n2,b2
26	format("n1= ",i3,"  a1= ",i3,"  b1= ",i3,"  n2= ",i3,"  b2= ",i5)
!                print*, n1,abest,b1,n2,b2
                print*, prob12, prob22
                print*, e1, e2, asn
                go to 20
13            continue
12          continue
11        continue
10      continue
15    continue
      n1=n1-1
      print*, n1
      print*,'An ERROR has occurred'
      print*,'n1 cannot exceed the 1 stage sample size'
20    continue
      stop
      end

      integer function nstage1(pow1, pow2, p0, p1)
      integer ss
      real(8) p(0:1), q(0:1)
      real(8) b(1:500, 0:1, 0:500), f(1:500, 0:1, 0:500)
      real(8) alpha, beta, b0, size, power, p0, p1, pow1, pow2

      alpha=pow1
      beta=1.0 - pow2
      p(0)=p0
      p(1)=p1
      b0 = 1.0 - alpha

      do 1 i=0,1
        q(i)=1-p(i)
        b(1,i,0)=q(i)
        b(1,i,1)=p(i)
  1   continue

      do 15 n=2,300

        do 3 i=0,1
          b(n,i,0)=q(i)**n
!          write(*,22) n,i,b(n,i,0)
! 22       format(" n= ",i5," i= ",i5," b= ",f10.8)
          f(n,i,0)=b(n,i,0)

          do 2 j=1,n
            b(n,i,j)=n*p(i)*b(n-1,i,j-1)/j
            f(n,i,j)=f(n,i,j-1)+b(n,i,j)
!            write(*,23) n,i,j,b(n,i,j)
! 23         format(" n= ",i5," i= ",i5," j= ",i5," b= ",f10.8)
!            write(*,24) n,i,j,f(n,i,j)
! 24         format(" n= ",i5," i= ",i5," j= ",i5," f= ",f10.8)
  2       continue
  3     continue

        do 4 j=1,n
!          write(*,25) n,j, f(n,0,j), f(n,1,j)
! 25       format(" n=",i5," j= ",i5," f0= ",f10.8," f1 = ",f10.8)
          if ((f(n,0,j)>=b0) .and. (f(n,1,j)<=beta)) go to 10
  4     continue

15   continue

      print*,n
      nstage1 = 0
      go to 20

10   size=1.0d0-f(n,0,j)
      power=1.0d0-f(n,1,j)
      ss=j+1
      write(*,21) n, ss, size, power
21   format(i5,3x,i5,3x,f10.8,3x,f10.8)
      nstage1 = n
20   continue
      return
      end

