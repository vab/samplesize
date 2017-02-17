! Two-sample, 2-stage, Type 1 Designs for Proportions
!
!
! Stop early only to conclude H1
!
! H0:p2=p1=p0 versus H1:p2 = p1 + delta = p0 + delta

      parameter (p0=.20, delta = 0.20, nn = 200)
	  integer(4) b1, b2, t
	  real(8) tot, asn

	  real(8) b(1:200, 0:1, 0:200), fb(1:200, 0:1, 0:200)
! b(n1,0,x)=P(X=x) with X:b(n1,p0) under H0
! b(n1,1,x)=P(X=x) with X:b(n1,p1) under H1
! fb(n1,0,x)=P(X<=x) under H0
! fb(n1,1,x)=P(X<=x) under H1

      real(8) pd(1:200, 0:1, -200:200), fpd(1:200, 0:1, -200:200)
! pd(n1,0,x)=P(S1-T1=x) where S1,T1 are independent b(n1,p0)
! pd(n1,1,x)=P(S1-T1=x) under H1
! fpd(n1,0,x)=P(S1-T1<=x) under H0
! fpd(n1,1,x)=P(S1-T1<=x) under H1

      real(8) p(0:1), q(0:1), pow(0:1), prob(0:1)
	  pow(0)=.05d0            ! alpha-value
	  pow(1)=.80d0            ! power at H1
	  p(0)=p0                 ! H0:p1 = p2 = p0
	  p(1)=p(0)+delta         ! p(1) is a value of p1-p2 under H1

	  do 1 i = 0,1
	  q(i)=1-p(i)
	  b(1,i,0)=q(i)
	  b(1,i,1)=p(i)
1     continue

      do 300 n1=2,nn
	  m1=n1-1
	  n11=-m1
	  nn1=n1+1
	  nn2=2*n1+1

	  do 2 i = 0,1
	  b(n1,i,0)=q(i)**n1
	  fb(n1,i,0)=b(n1,i,0)

	  do 2 j = 1,n1
	  b(n1,i,j)=n1*p(i)*b(n1-1,i,j-1)/j
	  fb(n1,i,j)=fb(n1,i,j-1)+b(n1,i,j)

! Compute P(S1-T1=ii) = sum(t=0,n1)P(T1=t)P(S1=ii+t) = pd(n1,i,ii)

	  do 3 ii = -n1,n1
	  tot=0.0d0

	  do 4 t = 0,n1
	  if ((t+ii)<0.or.(t+ii)>n1) go to 4
	  tot=tot+b(n1,0,t)*b(n1,i,ii+t)
4     continue

      pd(n1,i,ii)=tot
	  fpd(n1,i,ii)=fpd(n1,i,ii-1)+pd(n1,i,ii)

3     continue
2	  continue

      do 10 n2=2,n1
	  m2=n1+n2-1

	  do 12 b1=0,m1

	  do 13 b2=b1,m2

	  do 6 ii = 0,1
	  tot=0.0d0

	  do 7 t = -n1,b1
	  compare:  if ((b2-t).gt.n2) then 
	  tot=tot+pd(n1,ii,t)
	  else 
      tot=tot+pd(n1,ii,t)*fpd(n2,ii,b2-t)	  
	  end if compare
7	  continue
      
	  prob(ii)=1.0d0-tot
6	  continue

      if (prob(0)>pow(0)+0.00001) go to 13
	  if (prob(1)<pow(1)) go to 13
	  e1=2*n1+2*n2*fpd(n1,0,b1)      ! e1=E[NM|p(0)]
	  e2=2*n1+2*n2*fpd(n1,1,b1)      ! e2=E[NM|p(1)]
	  asn=(e1+e2)/2.0d0              ! asn=average sample size

	  write(*,28) n1,b1
28    format("n1 =",i4," to each treatment. Conclude H1 if S1-T1 > ",i4)
      print*
      write(*,29) n2
29    format("Otherwise, accrue n2 =",i4," additional subjects to each trmt.")
      print*
      write(*,30) b1,b2
30    format("Conclude H1 if S1-T1 <=",i4," and S1-T1+S2-T2 >",i4)
      print*
      write(*,31) prob(0),prob(1),e1,e2,asn
31	  format(5(f10.4,3x))
      print*

      go to 20

13	  continue
12	  continue
10	  continue

300	  continue
	  print*,n1

	  
22    continue
      print*
23    continue

20	  continue
      stop
	  end
