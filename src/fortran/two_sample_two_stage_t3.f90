! Two-sample, 2-stage, Type 3 Designs for Proportion Differences
!
!
! Stop early to conclude either H0 or H1
!
! H0:p2=p1=p0 versus H1:p2 = p1 + delta = p0 + delta

      parameter (p0=.40, delta = 0.15, nn = 200)
	  integer(4) b1, b2, t, a1, aa1, abest
	  real(8) tot, asn, prob0, prob1, e0, e1

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
      real p(0:1), q(0:1), pow(0:1)
	  real(8) prob(0:1)

	  pow(0)=.05            ! alpha-value
	  pow(1)=.80            ! power at H1
	  p(0)=p0               ! H0:p1 = p2 = p0
	  p(1)=p(0)+delta       ! p(1) is a value of p1-p2 under H1

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
	  fpd(n1,i,-n1)=(b(n1,0,n1)*b(n1,i,n1))**n1
	  fpd(n1,i,-n1-1)=0.0d0

	  do 2 j = 1,n1
	  b(n1,i,j)=n1*p(i)*b(n1-1,i,j-1)/j
	  fb(n1,i,j)=fb(n1,i,j-1)+b(n1,i,j)

! Next, compute P(S1-T1=ii) = sum(t=0,n1)P(T1=t)P(S1=ii+t) = pd(n1,i,ii)

! Note:  Under H0, the dists of S1 and T1 with p2 = p1 = p0
!        Under H1, p2 = p0 + delta, while p1 = p0

	  do 3 ii = -n1,n1
	  tot=0.0d0


	  do 4 t = 0,n1
	  if (((t+ii)<0).or.((t+ii)>n1)) go to 4
	  tot=tot+b(n1,0,t)*b(n1,i,ii+t)
4     continue

      pd(n1,i,ii)=tot
	  fpd(n1,i,ii)=fpd(n1,i,ii-1)+pd(n1,i,ii)

3	  continue

2	  continue

	  do 10 b1=1,m1

	  do 12 n2=2,n1
	  m2=n1+n2-1

	  do 13 b2=b1,m2

	  do 14 a1=-n1+1,b1


	  do 6 ii = 0,1
	  tot=0.0d0

	  do 7 t = a1,b1
	  compare:  if ((b2-t).gt.n2) then 
	  tot=tot+pd(n1,ii,t)
	  else 
	  tot=tot+pd(n1,ii,t)*fpd(n2,ii,b2-t)
	  end if compare
7	  continue
      
	  prob(ii)=1.0d0-fpd(n1,ii,a1-1)-tot
6	  continue

!      open(1,file='c:\fortran\jim23.out')

      if (prob(0)>pow(0)) go to 14
	  if (prob(1)<pow(1)) go to 14

      aa1=a1

30    abest=aa1
      prob0=prob(0)
	  prob1=prob(1)
	  aa1=aa1+1
	  if(aa1>b1) go to 31
	  k=b2+1-aa1
	  if(k>n2) go to 30

      prob(0)=prob(0)-pd(n1,0,aa1-1)*(1.0d0-fpd(n2,0,k))
      prob(1)=prob(1)-pd(n1,1,aa1-1)*(1.0d0-fpd(n2,1,k))

	  if((prob(0).gt.0.0d0).and.(prob(1).ge.pow(1))) go to 30
31    continue

	  e0=2*n1+2*n2*(fpd(n1,0,b1)-fpd(n1,0,abest-1))  ! e0=E[N|H0]
	  e1=2*n1+2*n2*(fpd(n1,1,b1)-fpd(n1,1,abest-1))  ! e1=E[N|H1]
	  asn=(e0+e1)/2.0d0              ! asn=average sample size

      write(*,36) n1
36    format("Accrue n1 =",i4," to each treatment.")
      print*
	  write(*,37) abest,b1
37    format("Conclude H0 if S1-T1 <",i4,". Conclude H1 if S1-T1 >",i4)
      print*
	  write(*,38) n2
38    format("Otherwise, accrue n2 =",i4," additional pts to each trmt.")
      print*
	  write(*,39) abest,b1
39    format("Conclude H1 only if",i4,"<= S1-T1 <=",i4)
      print*
	  write(*,40) b2
40    format("    and S1-T1+S2-T2 >",i4," .")
      print*
	  write(*,41) prob0,prob1,e0,e1,asn
41    format(5f10.4)
      print*

	  go to 20

14    continue
13    continue
12    continue
10    continue

300   continue
      print*,n1
20	  continue
      stop
	  end
