
     function nstage1(pow1, pow2, p0, p1)
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
  1  continue
  
     do 15 n=2,300
     
       do 3 i=0,1
         b(n,i,0)=q(i)**n
!     write(*,22) n,i,b(n,i,0)
! 22  format(" n= ",i5," i= ",i5," b= ",f10.8)
         f(n,i,0)=b(n,i,0)
         
         do 2 j=1,n
           b(n,i,j)=n*p(i)*b(n-1,i,j-1)/j
           f(n,i,j)=f(n,i,j-1)+b(n,i,j)
!    write(*,23) n,i,j,b(n,i,j)
! 23  format(" n= ",i5," i= ",i5," j= ",i5," b= ",f10.8)         
!     write(*,24) n,i,j,f(n,i,j)
! 24  format(" n= ",i5," i= ",i5," j= ",i5," f= ",f10.8)
  2      continue
  3    continue
           
       do 4 j=1,n
!       write(*,25) n,j, f(n,0,j), f(n,1,j)
! 25    format(" n=",i5," j= ",i5," f0= ",f10.8," f1 = ",f10.8)
         if ((f(n,0,j)>=b0) .and. (f(n,1,j)<=beta)) go to 10
  4    continue
  
 15  continue
 
     print*,n
     nstage1 = 0
     go to 20
     
 10  size=1.0d0-f(n,0,j)
     power=1.0d0-f(n,1,j)
     ss=j+1
     write(*,21) n, ss, size, power
 21  format(i5,3x,i5,3x,f10.8,3x,f10.8)
     nstage1 = n
 20  continue
     return
     end
