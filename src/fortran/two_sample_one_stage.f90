! Two-sample, 1-stage Designs for Proportions
!
! H0:p2=p1=p0 versus H1:p2 = p1 + delta = p0 + delta

		parameter (p0=.6, delta = .15, nn = 200)
		integer a1, b1, b2, t
		real tot, b0, beta, power, size

		real b(1:200, 0:1, 0:200), fb(1:200, 0:1, 0:200)
! b(n1,0,x)=P(X=x) with X:b(n1,p0) under H0
! b(n1,1,x)=P(X=x) with X:b(n1,p1) under H1
! fb(n1,0,x)=P(X<=x) under H0
! fb(n1,1,x)=P(X<=x) under H1

		real pd(1:200, 0:1, -200:200), fpd(1:200, 0:1, -200:200)
! pd(n1,0,x)=P(S1-T1=x) where S1,T1 are independent b(n1,p0)
! pd(n1,1,x)=P(S1-T1=x) under H1
! fpd(n1,0,x)=P(S1-T1<=x) under H0
! fpd(n1,1,x)=P(S1-T1<=x) under H1

		real p(0:1), q(0:1), pow(0:1), prob(0:1)
	
	pow(0)=.05d0            ! alpha-value
	pow(1)=.80d0            ! power at H1
	b0=1-pow(0)
	beta=1-pow(1)
	p(0)=p0               ! H0:p1 = p2 = p0
	p(1)=p(0)+delta       ! p(1) is a value of p1-p2 under H1

	do 1 i = 0,1
		q(i)=1-p(i)
		b(1,i,0)=q(i)
		b(1,i,1)=p(i)
1	continue

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
4	continue

	pd(n1,i,ii)=tot
	fpd(n1,i,ii)=fpd(n1,i,ii-1)+pd(n1,i,ii)

3	continue

2	continue

	do 10 j=0,m1
	if ((fpd(n1,0,j)>=b0).and.(fpd(n1,1,j)<=beta)) go to 11
10	continue

300	continue
	print*,n1
	go to 20


11	size=1.0d0-fpd(n1,0,j)
	power=1.0d0-fpd(n1,1,j)
	jj=j+1

	write(*,12) n1,jj
12	format("n = ",i4, " to each treatment",3x,"  Conclude H1 if S-T>=",i4)
	print*
	write(*,13) size,power
13	format("alpha = ",f10.8,3x,"power = ",f10.8)
	print*
	go to 20

20	continue
	stop
	end
