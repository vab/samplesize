
! 2T2: TWO-STAGE STUDY: STOP EARLY ONLY TO CONCLUDE H0
!  This program determines optimal sample sizes for a two-stage test
!  of H0:p=p0 vs H1:p>p0
!
!  The design is as follows:
!  Accrue n1 pts.
!  If there are too few responders (S1<=b1), permanently stop
!  the study for lack of activity.
!  If S1>=b1+1, accrue n2 additional pts.
!  If S1+S2>=b2+1, conclude H1.
!  If S1+S2<=b2, there is insufficient evidence to conclude H1.
!
!  alpha = pow(0) = the significance level of the test
!  1-beta = pow(1) = power when p = p1 and p1> p0
!  prob(p)=P(S1>=b1+1, S1+S2>=b2+1 | p )
!
!  This design guarantees that n1+n2 pts will be accrued unless an
!  early stop for low activity is necessary.
!

      integer b1,b2,b11,bb1,bbest, maxn
      real(8) p(0:1), q(0:1), pow(0:1), prob(0:1), delta
      real(8) b(1:200, 0:1, 0:200), f(1:200, 0:1, 0:200)
!      b(n,i,x) = P[ X=x | X:b(n,pi) ]
!      f(n,i,x) = P[ X<=x | X:b(n,pi) ]
      pow(0)=.05              ! alpha-value
      pow(1)=.80              ! power when p=p(1)
      delta=0.15d0
      p(0)=.80                ! H0:p=p(0)
      p(1)=p(0)+delta         ! p=p(1) is a value of p under H1

      maxn = nstage1(pow(0), pow(1), p(0), p(1))
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

      do 1 i=0,1
        q(i)=1-p(i)
        b(1,i,0)=q(i)
        b(1,i,1)=p(i)
1     continue

      do 15 n1=2,maxn

        do 3 i=0,1
          b(n1,i,0)=q(i)**n1
          f(n1,i,0)=b(n1,i,0)
          do 2 j=1,n1
            b(n1,i,j)=n1*p(i)*b(n1-1,i,j-1)/j
            f(n1,i,j)=f(n1,i,j-1)+b(n1,i,j)
  2       continue
  3     continue

        m1=n1-1

        do 10 n2=2,n1
          if(n1+n2 > maxn) go to 15      !stop and return to previous loop
	  m2=n1+n2-1
         do 11 b1=m1,0,-1
!          do 11 b1=0,m1
	    b11=b1+1

            do 12 b2=b1,m2

              do 4 ii=0,1
                sum=0
                do 5 i=b11,n1
	          compare: if ((b2-i+1>=1).and.(b2-i+1<=n2)) then
	          sum=sum+b(n1,ii,i)*(1-f(n2,ii,b2-i))
                  else if ((b2-i+1<=0).and.(b2-i+1<=n2)) then
	          sum=sum+b(n1,ii,i)
	          end if compare
5	        continue
                prob(ii)=sum
4             continue

              if (prob(0)>pow(0)) go to 12
!              if ((prob(0)<=pow(0)-.01).or. (prob(0)>pow(0))) go to 12
              if (prob(1)<pow(1)) go to 12

! The following statement controls P(conclude H0|H0) at stage 1.
! If this probability is not large enough, the search continues.
!	       if (f(n1,0,b1)<=.60) go to 12

              bb1=b1
30            bbest=bb1
              prob0=prob(0)
	      prob1=prob(1)
	      e1=n1+n2*(1-f(n1,0,bbest))        ! e1=E[N | p(0)]
	      e2=n1+n2*(1-f(n1,1,bbest))        ! e2=E[N | p(1)]
	      asn=(e1+e2)/2			!  asn=average sample number

!              print*, n1,bbest,n2,b2
!              print*, prob0,prob1
!              print*, e1,e2,asn

	      bb1=bb1+1
	      if (bb1>b2) go to 31
	      if (b2-bb1.eq.0) then
	        prob(0)=prob(0)-b(n1,0,bb1+1)
	        prob(1)=prob(1)-b(n1,1,bb1+1)
	      else if (b2-bb1>0) then
	        prob(0)=prob(0)-b(n1,0,bb1+1)*(1-f(n2,0,b2-bb1-1))
	        prob(1)=prob(1)-b(n1,1,bb1+1)*(1-f(n2,1,b2-bb1-1))
	      end if
	      if ((prob(1)<pow(1)).or.(prob(0)<0.0)) go to 31
!	       if (pow(0)-.01<prob(0) .and. prob(0)<=pow(0)) go to 30
              go to 30
31            continue

              print*, 'n1=',n1,' bbest=',bbest,' n2=',n2,' b2=',b2
              print*, prob0,prob1
              print*, 'e1=',e1,' e2=',e2,' asn=',asn
              go to 20
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

