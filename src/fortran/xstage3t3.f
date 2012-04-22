
! 3T3: THREE-STAGE STUDY: STOP EARLY TO CONCLUDE H0 OR H1
!
!  This program determines optimal sample sizes for a 3-stage test
!  of H0:p = p0 vs H1:p > p0
!
!  The design is as follows:
!  Accrue n1 pts.
!  If there are too few responders (S1<=a1-1), permanently stop
!  the study for lack of activity.
!  If S1>=b1+1, conclude H1.
!  If a1<=S1<=b1, accrue n2 additional pts.
!  If S1+S2<=a2-1, permanently stop the study for lack of activity.
!  If S1+S2>=b2+1, conclude H1.
!  If a2<=S1+S2<=b2, accrue n3 additional pts.
!  If S1+S2+S3>=b3+1, conclude H1
!  If S1+S2+S3<=b3, there is insufficient evidence to conclude H1.
!
!  alpha = pow(0) = the significance level of the test
!  1-beta = pow(1) = power when p = p1 and p1> p0
!  sum1(0)=P(S1>=b1+1, S1+S2<=b2 | p0)
!  sum1(1)=P(S1>=b1+1, S1+S2<=b2 | p1)
!  sum2(0)=P(S1>=b1+1, S1+S2>=b2+1, S1+S2+S3<=b3 | p0)
!  sum2(1)=P(S1>=b1+1, S1+S2>=b2+1, S1+S2+S3<=b3 | p1
!

      integer a1,a2,a11,a21,b1,b2,b3,b11,b21,b31,bb,bbb,maxn
      integer i,j,n11,n21,ii,bb1,bb2,aa1,k1,k2,b12,b22

      real(8) sum,sum2,sum3
      real(8) delta,asn
      real(8) p(2),q(2),pow(2),prob(2),e(2),f(200,2,201)
      real(8) b(200,2,201)

      pow(1)=.05d0
      pow(2)=.80d0
      delta=0.15d0
      p(1)=.20d0
      p(2)=p(1)+delta

      maxn = nstage1(pow(1), pow(2), p(1), p(2))
      print*,'maxn=',maxn
      if (maxn .eq. 0) then
        print*,'No Solution'
        go to 42
      elseif (maxn .gt. 200) then
        print*,'ERROR - maxn is greater than 200'
        print*,'redimension the FORTRAN program'
        go to 42
      else
      endif

      do 1 i=1,2
        q(i)=1.0d0-p(i)
        b(1,i,1)=q(i)
        b(1,i,2)=p(i)
1    continue

      maxn1=maxn+1

      do 9 n1=2,maxn1
        do 3 i=1,2
          b(n1,i,1)=q(i)**n1
          f(n1,i,1)=b(n1,i,1)
          n11=n1+1
          do 2 j=2,n11
            b(n1,i,j)=n1*p(i)*b(n1-1,i,j-1)/(j-1)
            f(n1,i,j)=f(n1,i,j-1)+b(n1,i,j)
2        continue
3      continue
        do 10 n2=2,n1
          if((n1+n2)>maxn1) go to 9
          do 11 n3=2,n2
            if((n1+n2+n3)>maxn1) go to 10
            m1=n1
            m2=n1+n2
            m3=n1+n2+n3
            n11=n1+1
            n21=n2+1
	      n31=n3+1
            do 12 b1=1,m1
              b11=b1+1
	        b12=min(b1,m1)
              do 13 b2=b1,m2
                b21=b2+1
	          b22=min(b2,m2)
                do 14 b3=b2,m3
                  b31=b3+1
                  do 15 a1=b12,2,-1
                    a11=a1+1
                    do 16 a2=b22,a1,-1
                      a21=a2+1
                      do 4 ii=1,2
                        sum2=0.0d0

!       sum2=P(a1<=S1<=b1, S1+S2<=a2-1)
!           =sum(a1+1<=i<=b1+1)P(S1*=i)P(S2*<=a2-i+1)

                        sum3=0.0d0
                        do 5 i=a11,b11

                          k1=a21-i
                          if(k1 > n21) then
                            sum2=sum2+b(n1,ii,i)
                          else if(k1 > 0 .and. k1 <= n21) then
                            sum2=sum2+b(n1,ii,i)*f(n2,ii,k1)
                          endif

                          bb1=max(0,a2-i+2)
                          bb2=min(n21,b21-i+1)

!       sum3=P(a1<=S1<=b1, a2<=S1+S2<=b2, S1+S2+S3<=b3)
!           =sum(a1+1<i<=b1+1) 
sum(bb1<=j<=bb2)P(S1*=i)P(S2*=j)*P(S3*<=b3-i-j+3)

                          do 6 j=bb1,bb2

                           k2=b3-i-j+3
                           if(k2 > n31) then
                             sum3=sum3+b(n1,ii,i)*b(n2,ii,j)
                           else if(k2 > 0 .and. k2 <= n31) then
                             sum3=sum3+b(n1,ii,i)*b(n2,ii,j)*f(n3,ii,k2)
                           endif

6                        continue
5                      continue
                        prob(ii)=1.0d0-f(n1,ii,a1)-sum2-sum3
4                    continue
                      if (prob(1) .gt. pow(1)) go to 16
                      if (prob(2) .lt. pow(2)) go to 16
                      go to 50

16                 continue
15               continue
14             continue
13           continue
12         continue
11       continue
10     continue
  9   continue
      n1=n1-1
      print*, n1
      print*,'An ERROR has occurred'
      print*,'n1 cannot exceed the 1 stage sample size'
      go to 42


50    continue
      do 40 ii=1,2
        sum=0.0d0
        do 41 i=a11,b11
          sum=sum+b(n1,ii,i)*(f(n2,ii,b2-i+2)-f(n2,ii,a21-i))
41     continue
      e(ii)=n1+n2*(f(n1,ii,b11)-f(n1,ii,a11))+n3*sum
40   continue
      asn=(e(1)+e(2))/2

      print*,n1,a1,b1
	print*,n2,a2,b2
	print*,n3,b3
	print*, prob(1),prob(2)
      print*, e(1),e(2),asn
42   continue
      stop
      end

!     Subprogram to generate maxn (1-stage) follows.

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
!      write(*,22) n,i,b(n,i,0)
! 22   format(" n= ",i5," i= ",i5," b= ",f10.8)
          f(n,i,0)=b(n,i,0)

          do 2 j=1,n
            b(n,i,j)=n*p(i)*b(n-1,i,j-1)/j
            f(n,i,j)=f(n,i,j-1)+b(n,i,j)
!     write(*,23) n,i,j,b(n,i,j)
! 23   format(" n= ",i5," i= ",i5," j= ",i5," b= ",f10.8)
!      write(*,24) n,i,j,f(n,i,j)
! 24   format(" n= ",i5," i= ",i5," j= ",i5," f= ",f10.8)
  2       continue
  3     continue

        do 4 j=1,n
!        write(*,25) n,j, f(n,0,j), f(n,1,j)
! 25     format(" n=",i5," j= ",i5," f0= ",f10.8," f1 = ",f10.8)
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

