c *******************************************************************************
c   Add the forcing to Maxwell's equations such as for moving charges
c *******************************************************************************

#beginMacro beginLoops()
do i3=n3a,n3b
do i2=n2a,n2b
do i1=n1a,n1b
if( mask(i1,i2,i3).gt.0 )then
#endMacro

#beginMacro endLoops()
end if
end do
end do
end do
#endMacro

#beginMacro declareGaussianVariables()
 real x0,x1,x2,q,r2Min,realMin,betap,a0,ap,app,appp
 real rho,rhop,rhopp,rhoppp
 real r2,r2x,r2y,r2z,r2t,r2f,expr,rhox,rhoy,rhoz,rhot
 real r2xx,r2xy,r2yy,r2xz,r2yz,r2zz,r2xt,r2yt,r2zt,r2tt
 real rhoxx,rhoxy,rhoyy,rhoxz,rhoyz,rhozz
 real r2xxx,r2xxy,r2xyy,r2xxz,r2xzz,r2yyy,r2yyz,r2yzz,r2xyz,r2zzz,r2xxt,r2yyt,r2zzt,r2ttt,r2xtt,r2ytt,r2ztt
 real rhoxxx,rhoxxy,rhoxyy,rhoxxz,rhoxzz,rhoyyy,rhoyyz,rhoyzz,rhoxyz,rhozzz,rhoxxt,rhoyyt,rhozzt
 real rhoxtt,rhoytt,rhoztt,rhottt
 real deltaRhoX,deltaRhoY,deltaRhoZ,deltaRhot
 real deltaJ0t,deltaJ1t,deltaJ2t,j0ttt,j1ttt,j2ttt
#endMacro

c =====================================================================
c Evaluate the Gaussian pulse 
c
c      rho = a*exp( - [beta* | (xv-xpv) - vv*t |]^p ) )
c =====================================================================
#beginMacro evalGaussianPulse(DIM,x,y,z,t,rho)

   x0 = x -xp0
   x1 = y -xp1
   #If #DIM == "3"
     x2 = z -xp2
   #End

   #If #DIM == "2"
     r2 = ( x0-vp0*(t) )**2 + ( x1-vp1*(t) )**2
   #Else
     r2 = ( x0-vp0*(t) )**2 + ( x1-vp1*(t) )**2 + ( x2-vp2*(t) )**2 
   #End

   expr = exp(-betap*r2**q)  ! exp( -(beta*r)^p )
   rho = amplitude*expr 
#endMacro

#beginMacro getCoords(x0,x1,x2,DIM,GRIDTYPE)
 #If #GRIDTYPE eq "curvilinear"
   x0 = xy(i1,i2,i3,0)-xp0
   x1 = xy(i1,i2,i3,1)-xp1
   #If #DIM == "3"
     x2 = xy(i1,i2,i3,2)-xp2
   #End
 #Else
   x0 = xa(0)+i1*dx(0) -xp0
   x1 = xa(1)+i2*dx(1) -xp1
   #If #DIM == "3"
     x2 = xa(2)+i3*dx(2) -xp2
   #End
 #End
 #If #DIM == "2"
   r2 = ( x0-vp0*(t) )**2 + ( x1-vp1*(t) )**2
 #Else
   r2 = ( x0-vp0*(t) )**2 + ( x1-vp1*(t) )**2 + ( x2-vp2*(t) )**2 
 #End
#endMacro


c =====================================================================
c Evaluate the Gaussian pulse and its deriatives
c
c      rho = a*exp( - [beta* | (xv-xpv) - vv*t |]^p ) )
c
c  p should be even and positive: 2,4,6,...
c =====================================================================
#beginMacro evalGaussianPulseAndDerivatives(x0,x1,x2,DIM,GRIDTYPE,NDER)

   ! radx == r*r_x = .5* (r^2)_x 
   r2x = 2.*(x0-vp0*(t))
   r2y = 2.*(x1-vp1*(t))
   #If #DIM == "2"
     r2t = -2.*( ( x0-vp0*(t) )*vp0 + ( x1-vp1*(t) )*vp1 )
   #Else
     r2z = 2.*(x2-vp2*(t))
     r2t = -2.*( ( x0-vp0*(t) )*vp0 + ( x1-vp1*(t) )*vp1 + ( x2-vp2*(t) )*vp2 )
   #End

   a0=-betap*r2**q   
   expr = exp(a0)  ! exp( -(beta*r)^p )
   rho = amplitude*expr 

   r2f=max(r2Min,r2)  ! floor value of r2 to avoid division by zero

   ! rhop = [d(rho)/d(r2)]
   ap=a0*q/r2f  ! d(arg)/d(r2) , arg=-betap*r2**q

   rhop = rho*ap

   rhox = rhop*r2x
   rhoy = rhop*r2y
   rhot = rhop*r2t 
   #If #DIM == "3"
    rhoz = rhop*r2z
   #End

   #If NDER > 1

     app=ap*(q-1.)/r2f
     rhopp = rhop*ap+rho*app
    
     r2xx=2.
     r2xy=0.
     r2yy=2.

     r2xt=-2.*vp0
     r2yt=-2.*vp1
     #If #DIM == "2"
       r2tt=2.*(vp0**2+vp1**2)
     #Else
       r2xz=0.
       r2yz=0.
       r2zz=2.
       r2zt=-2.*vp2
       r2tt=2.*(vp0**2+vp1**2+vp2**2)
     #End

     rhoxx = rhopp*r2x*r2x + rhop*r2xx
     rhoxy = rhopp*r2x*r2y + rhop*r2xy
     rhoyy = rhopp*r2y*r2y + rhop*r2yy

     #If #DIM == "3"
       rhoxz = rhopp*r2x*r2z + rhop*r2xz
       rhoyz = rhopp*r2y*r2z + rhop*r2yz
       rhozz = rhopp*r2z*r2z + rhop*r2zz
     #End
   #End
   #If NDER > 2

     appp=app*(q-2.)/r2f
     rhoppp = rhopp*ap +2.*rhop*app+rho*appp

     r2xxx=0.
     r2xxy=0.
     r2xyy=0.
     r2xxt=0.
     r2yyt=0.
     r2ttt=0.

     rhoxxx = rhoppp*r2x*r2x*r2x + rhopp*( r2x*r2xx + r2x*r2xx + r2x*r2xx ) + rhop*r2xxx
     rhoxxy = rhoppp*r2x*r2x*r2y + rhopp*( r2y*r2xx + r2x*r2xy + r2x*r2xy ) + rhop*r2xxy
     rhoxyy = rhoppp*r2x*r2y*r2y + rhopp*( r2y*r2xy + r2y*r2xy + r2x*r2yy ) + rhop*r2xyy
     rhoyyy = rhoppp*r2y*r2y*r2y + rhopp*( r2y*r2yy + r2y*r2yy + r2y*r2yy ) + rhop*r2yyy
     rhoxxt = rhoppp*r2x*r2x*r2t + rhopp*( r2t*r2xx + r2x*r2xt + r2x*r2xt ) + rhop*r2xxt
     rhoyyt = rhoppp*r2y*r2y*r2t + rhopp*( r2t*r2yy + r2y*r2yt + r2y*r2yt ) + rhop*r2yyt
     rhottt = rhoppp*r2t*r2t*r2t + rhopp*( r2t*r2tt + r2t*r2tt + r2t*r2tt ) + rhop*r2ttt

     rhoxtt = rhoppp*r2x*r2t*r2t + rhopp*( r2t*r2xt + r2t*r2xt + r2x*r2tt ) + rhop*r2xtt
     rhoytt = rhoppp*r2y*r2t*r2t + rhopp*( r2t*r2yt + r2t*r2yt + r2y*r2tt ) + rhop*r2ytt
     #If #DIM == "3" 
       r2xxz=0.
       r2xzz=0.
       r2yyz=0.
       r2yzz=0.
       r2zzz=0.
       r2zzt=0.

       rhoxxz = rhoppp*r2x*r2x*r2z + rhopp*( r2z*r2xx + r2x*r2xz + r2x*r2xz ) + rhop*r2xxz
       rhoxzz = rhoppp*r2x*r2z*r2z + rhopp*( r2z*r2xz + r2z*r2xz + r2x*r2zz ) + rhop*r2xzz
       rhoyzz = rhoppp*r2y*r2z*r2z + rhopp*( r2z*r2yz + r2z*r2yz + r2y*r2zz ) + rhop*r2yzz
       rhoyyz = rhoppp*r2y*r2y*r2z + rhopp*( r2z*r2yy + r2y*r2yz + r2y*r2yz ) + rhop*r2yyz
       rhozzz = rhoppp*r2z*r2z*r2z + rhopp*( r2z*r2zz + r2z*r2zz + r2z*r2zz ) + rhop*r2zzz
       rhozzt = rhoppp*r2z*r2z*r2t + rhopp*( r2t*r2zz + r2z*r2zt + r2z*r2zt ) + rhop*r2zzt
       rhoztt = rhoppp*r2z*r2t*r2t + rhopp*( r2t*r2zt + r2t*r2zt + r2z*r2tt ) + rhop*r2ztt
     #End

   #End
#endMacro


c ===========================================================================
c     Forcing for a Moving Gaussian Pulse of Charge rho(x,t)
c
c      E_tt = c^2 [ Delta(E) - grad(rho/eps) - mu J_t ]
c      H_tt = c^2 [ Delta(H) + curl( J ) ]
c
c      rho = a*exp( - [beta* | (xv-xpv) - vv*t |]^p ) )
c      J = rho*vv 
c
c  DIM : 2,3
c  ORDER: 2,4
c  GRIDTYPE : curvilinear, rectangular
c ===========================================================================
#beginMacro assignGaussianPulseChargeDensity(DIM,ORDER,GRIDTYPE)


c f = grad(rho) - J_t 


icount=0
beginLoops()

 getCoords(x0,x1,x2,DIM,GRIDTYPE)
 if( mask(i1,i2,i3).gt.0 .and. (r2 .lt. tolPulse) )then
! if( .true. )then
   ! only evaluate if this is a valid point and pulse value is not too small
  #If #ORDER == "2" 
   ! f = f + c^2 [- grad(rho/eps) - mu J_t ]
   ! ** evaluate pulse and 1 derivative **
   evalGaussianPulseAndDerivatives(x0,x1,x2,DIM,GRIDTYPE,1)

   f(i1,i2,i3,ex)=f(i1,i2,i3,ex) + csq*( -rhox/eps - mu*vp0*rhot )
   f(i1,i2,i3,ey)=f(i1,i2,i3,ey) + csq*( -rhoy/eps - mu*vp1*rhot )

   #If #DIM == "2"
     f(i1,i2,i3,hz)= f(i1,i2,i3,hz) + csq*( vp1*rhox - vp0*rhoy )
   #Else
     f(i1,i2,i3,ez)= f(i1,i2,i3,ez) + csq*( -rhoz/eps - mu*vp2*rhot )
   #End


  #Elif #ORDER == "4"

   ! for 4th order in time we need 
   !    f_tt and Delta(f)

   ! f = f + c^2 [- grad(rho/eps) - mu J_t ]
   !       + c^2*dt^2/12*{ c^2*[ -Delta*grad(rho/eps) - mu*Delta(J_t) ] - grad(rho_tt/eps) - mu*J_ttt } 

   ! ** evaluate pulse and 3 derivatives **
    evalGaussianPulseAndDerivatives(x0,x1,x2,DIM,GRIDTYPE,3)

    #If #DIM == "2"
     deltaRhoX = rhoxxx+rhoxyy
     deltaRhoY = rhoxxy+rhoyyy 
     deltaRhot = rhoxxt+rhoyyt
    #Else
     deltaRhoX = rhoxxx+rhoxyy+rhoxzz
     deltaRhoY = rhoxxy+rhoyyy+rhoyzz 
     deltaRhoZ = rhoxxz+rhoyyz+rhozzz 
     deltaRhot = rhoxxt+rhoyyt+rhozzt
    #End

    deltaJ0t = vp0*deltaRhot
    deltaJ1t = vp1*deltaRhot 

    j0ttt = vp0*rhottt
    j1ttt = vp1*rhottt
    #If #DIM == "2"
     deltaJ2t = vp2*deltaRhot 
     j2ttt = vp2*rhottt
    #End

    f(i1,i2,i3,ex)=f(i1,i2,i3,ex) + csq*( -rhox/eps - mu*vp0*rhot ) + \
                   csq*dtsq/12.*( -csq*( deltaRhoX/eps + mu*deltaJ0t ) - rhoxtt/eps -mu*j0ttt )
     
    f(i1,i2,i3,ey)=f(i1,i2,i3,ey) + csq*( -rhoy/eps - mu*vp1*rhot ) + \
                   csq*dtsq/12.*( -csq*( deltaRhoY/eps + mu*deltaJ1t ) - rhoytt/eps -mu*j1ttt )
    #If #DIM == "2"
      f(i1,i2,i3,hz)= f(i1,i2,i3,hz) + csq*( vp1*rhox - vp0*rhoy ) + \
                    csq*dtsq/12.*( vp1*deltaRhox - vp0*deltaRhoy +vp1*rhoxtt - vp0*rhoytt )
    #Else
     f(i1,i2,i3,ez)=f(i1,i2,i3,ez) + csq*( -rhoz/eps - mu*vp2*rhot ) + \
                    csq*dtsq/12.*( -csq*( deltaRhoZ/eps + mu*deltaJ2t ) - rhoztt/eps -mu*j2ttt )

    #End

  #Else
    stop 4103
  #End

  else
   icount=icount+1 ! this point not evaluated
  end if
 endLoops()
 ! write(*,'("charge source: total points=",i6," points evaluated=",i6," : r2>tolPulse=",e8.2)') \
 ! (n1b-n1a+1)*(n2b-n2a+1)*(n3b-n3a+1),(n1b-n1a+1)*(n2b-n2a+1)*(n3b-n3a+1)-icount,tolPulse
 ! '
#endMacro


#beginMacro getx(DIM,x,y,z,t,ux,uxx,uxxx)
 evalGaussianPulse(DIM ,x-2.*h,y,z,t,rhom2)
 evalGaussianPulse(DIM ,x-   h,y,z,t,rhom1)
 evalGaussianPulse(DIM ,x     ,y,z,t,rho  )
 evalGaussianPulse(DIM ,x+   h,y,z,t,rhop1)
 evalGaussianPulse(DIM ,x+2.*h,y,z,t,rhop2)

 ux = (rhop1-rhom1)/(2.*h)
 uxx = (rhop1-2.*rho+rhom1)/(h**2)
 uxxx = (-2.*(rhop1-rhom1)+(rhop2-rhom2))/(2.*h**3)
#endMacro

#beginMacro gety(DIM,x,y,z,t,ux,uxx,uxxx)
 evalGaussianPulse(DIM ,x,y-2.*h,z,t,rhom2)
 evalGaussianPulse(DIM ,x,y-   h,z,t,rhom1)
 evalGaussianPulse(DIM ,x,y     ,z,t,rho  )
 evalGaussianPulse(DIM ,x,y+   h,z,t,rhop1)
 evalGaussianPulse(DIM ,x,y+2.*h,z,t,rhop2)

 ux = (rhop1-rhom1)/(2.*h)
 uxx = (rhop1-2.*rho+rhom1)/(h**2)
 uxxx = (-2.*(rhop1-rhom1)+(rhop2-rhom2))/(2.*h**3)
#endMacro

#beginMacro getz(DIM,x,y,z,t,ux,uxx,uxxx)
 evalGaussianPulse(DIM ,x,y,z-2.*h,t,rhom2)
 evalGaussianPulse(DIM ,x,y,z-   h,t,rhom1)
 evalGaussianPulse(DIM ,x,y,z     ,t,rho  )
 evalGaussianPulse(DIM ,x,y,z+   h,t,rhop1)
 evalGaussianPulse(DIM ,x,y,z+2.*h,t,rhop2)

 ux = (rhop1-rhom1)/(2.*h)
 uxx = (rhop1-2.*rho+rhom1)/(h**2)
 uxxx = (-2.*(rhop1-rhom1)+(rhop2-rhom2))/(2.*h**3)
#endMacro

#beginMacro gett(DIM,x,y,z,t,ux,uxx,uxxx)
 evalGaussianPulse(DIM ,x,y,z,t-2.*h,rhom2)
 evalGaussianPulse(DIM ,x,y,z,t-   h,rhom1)
 evalGaussianPulse(DIM ,x,y,z,t     ,rho  )
 evalGaussianPulse(DIM ,x,y,z,t+   h,rhop1)
 evalGaussianPulse(DIM ,x,y,z,t+2.*h,rhop2)

 ux = (rhop1-rhom1)/(2.*h)
 uxx = (rhop1-2.*rho+rhom1)/(h**2)
 uxxx = (-2.*(rhop1-rhom1)+(rhop2-rhom2))/(2.*h**3)
#endMacro


#beginMacro checkx(DIM)

 gett(DIM,x,y,z,t,ux,uxx,uxxx)
 write(*,'("DIM d: rhot  =",e10.3," diff=",e10.3," err=",e8.2)') rhot,ux,abs(rhot-ux)
 write(*,'("DIM d: rhottt=",e10.3," diff=",e10.3," err=",e8.2)') rhottt,uxxx,abs(rhottt-uxxx)

 getx(DIM,x,y,z,t,ux,uxx,uxxx)
 write(*,'("DIM d: rhox  =",e10.3," diff=",e10.3," err=",e8.2)') rhox,ux,abs(rhox-ux)
 write(*,'("DIM d: rhoxx =",e10.3," diff=",e10.3," err=",e8.2)') rhoxx,uxx,abs(rhoxx-uxx)
 write(*,'("DIM d: rhoxxx=",e10.3," diff=",e10.3," err=",e8.2)') rhoxxx,uxxx,abs(rhoxxx-uxxx)

 gety(DIM,x,y,z,t,ux,uxx,uxxx)
 write(*,'("DIM d: rhoy  =",e10.3," diff=",e10.3," err=",e8.2)') rhoy,ux,abs(rhoy-ux)
 write(*,'("DIM d: rhoyy =",e10.3," diff=",e10.3," err=",e8.2)') rhoyy,uxx,abs(rhoyy-uxx)
 write(*,'("DIM d: rhoyyy=",e10.3," diff=",e10.3," err=",e8.2)') rhoyyy,uxxx,abs(rhoyyy-uxxx)

 #If #DIM == "3"
 getz(DIM,x,y,z,t,ux,uxx,uxxx)
 write(*,'("DIM d: rhoz  =",e10.3," diff=",e10.3," err=",e8.2)') rhoz,ux,abs(rhoz-ux)
 write(*,'("DIM d: rhozz =",e10.3," diff=",e10.3," err=",e8.2)') rhozz,uxx,abs(rhozz-uxx)
 write(*,'("DIM d: rhozzz=",e10.3," diff=",e10.3," err=",e8.2)') rhozzz,uxxx,abs(rhozzz-uxxx)
 #End


 h2=h
 getx(DIM,x,y  ,z,t,ux,uxx,uxxx)
 getx(DIM,x,y-h2,z,t,uxm1,uxxm1,uxxxm1)
 getx(DIM,x,y+h2,z,t,uxp1,uxxp1,uxxxp1)

 uxy=(uxp1-uxm1)/(2.*h2)
 uxxy=(uxxp1-uxxm1)/(2.*h2)
 uxyy=(uxp1-2.*ux+uxm1)/(h2**2)

!write(*,'("DIM d: ux,uxm1,uxp1=",3e12.5') ux,uxm1,uxp1
!write(*,'("DIM d: uxx,uxxm1,uxxp1=",3e12.5') uxx,uxxm1,uxxp1
!write(*,'("DIM d: uxxx,uxxxm1,uxxxp1=",3e12.5') uxxx,uxxxm1,uxxxp1

 write(*,'("DIM d: rhoxy =",e10.3," diff=",e10.3," err=",e8.2)') rhoxy,uxy,abs(rhoxy-uxy)
 write(*,'("DIM d: rhoxxy=",e10.3," diff=",e10.3," err=",e8.2)') rhoxxy,uxxy,abs(rhoxxy-uxxy)
 write(*,'("DIM d: rhoxyy=",e10.3," diff=",e10.3," err=",e8.2)') rhoxyy,uxyy,abs(rhoxyy-uxyy)

 getx(DIM,x,y,z,t,ux,uxx,uxxx)
 getx(DIM,x,y,z,t-h2,uxm1,uxxm1,uxxxm1)
 getx(DIM,x,y,z,t+h2,uxp1,uxxp1,uxxxp1)

 uxxt=(uxxp1-uxxm1)/(2.*h2)
 uxtt=(uxp1-2.*ux+uxm1)/(h2**2)

 write(*,'("DIM d: rhoxxt=",e10.3," diff=",e10.3," err=",e8.2)') rhoxxt,uxxt,abs(rhoxxt-uxxt)
 write(*,'("DIM d: rhoxtt=",e10.3," diff=",e10.3," err=",e8.2)') rhoxtt,uxtt,abs(rhoxtt-uxtt)

 gety(DIM,x,y,z,t,ux,uxx,uxxx)
 gety(DIM,x,y,z,t-h2,uxm1,uxxm1,uxxxm1)
 gety(DIM,x,y,z,t+h2,uxp1,uxxp1,uxxxp1)
 uxxt=(uxxp1-uxxm1)/(2.*h2)
 uxtt=(uxp1-2.*ux+uxm1)/(h2**2)
 write(*,'("DIM d: rhoyyt=",e10.3," diff=",e10.3," err=",e8.2)') rhoyyt,uxxt,abs(rhoyyt-uxxt)
 write(*,'("DIM d: rhoytt=",e10.3," diff=",e10.3," err=",e8.2)') rhoytt,uxtt,abs(rhoytt-uxtt)

 #If #DIM == "3"

 getx(DIM,x,y  ,z,t,ux,uxx,uxxx)
 getx(DIM,x,y,z-h2,t,uxm1,uxxm1,uxxxm1)
 getx(DIM,x,y,z+h2,t,uxp1,uxxp1,uxxxp1)

 uxz=(uxp1-uxm1)/(2.*h2)
 uxxz=(uxxp1-uxxm1)/(2.*h2)
 uxzz=(uxp1-2.*ux+uxm1)/(h2**2)

 write(*,'("DIM d: rhoxz =",e10.3," diff=",e10.3," err=",e8.2)') rhoxz,uxz,abs(rhoxz-uxz)
 write(*,'("DIM d: rhoxxz=",e10.3," diff=",e10.3," err=",e8.2)') rhoxxz,uxxz,abs(rhoxxz-uxxz)
 write(*,'("DIM d: rhoxzz=",e10.3," diff=",e10.3," err=",e8.2)') rhoxzz,uxzz,abs(rhoxzz-uxzz)

 gety(DIM,x,y  ,z,t,ux,uxx,uxxx)
 gety(DIM,x,y,z-h2,t,uxm1,uxxm1,uxxxm1)
 gety(DIM,x,y,z+h2,t,uxp1,uxxp1,uxxxp1)
 uyz=(uxp1-uxm1)/(2.*h2)
 uyyz=(uxxp1-uxxm1)/(2.*h2)
 uyzz=(uxp1-2.*ux+uxm1)/(h2**2)

 write(*,'("DIM d: rhoyz =",e10.3," diff=",e10.3," err=",e8.2)') rhoyz,uyz,abs(rhoyz-uyz)
 write(*,'("DIM d: rhoyyz=",e10.3," diff=",e10.3," err=",e8.2)') rhoyyz,uyyz,abs(rhoyyz-uyyz)
 write(*,'("DIM d: rhoyzz=",e10.3," diff=",e10.3," err=",e8.2)') rhoyzz,uyzz,abs(rhoyzz-uyzz)

 getz(DIM,x,y,z,t,ux,uxx,uxxx)
 getz(DIM,x,y,z,t-h2,uxm1,uxxm1,uxxxm1)
 getz(DIM,x,y,z,t+h2,uxp1,uxxp1,uxxxp1)
 uxxt=(uxxp1-uxxm1)/(2.*h2)
 uxtt=(uxp1-2.*ux+uxm1)/(h2**2)
 write(*,'("DIM d: rhozzt=",e10.3," diff=",e10.3," err=",e8.2)') rhozzt,uxxt,abs(rhozzt-uxxt)
 write(*,'("DIM d: rhoztt=",e10.3," diff=",e10.3," err=",e8.2)') rhoztt,uxtt,abs(rhoztt-uxtt)

 #End
#endMacro

      subroutine testGaussianPulse()
c =========================================================================
c  Test the Gaussian pulse and derivatives
c =========================================================================
      implicit none

      real xa(0:2),dx(0:2)
      real amplitude,beta,p,xp0,xp1,xp2,vp0,vp1,vp2
      real x,y,z,h,t,h2
      integer nd,i1,i2,i3
      real rhom2,rhom1,rhop1,rhop2,ux,uxx,uxxx

      real uxm1,uxxm1,uxxxm1,uxp1,uxxp1,uxxxp1
      real uxy,uxxy,uxyy,uxz,uxxz,uxzz,uyz,uyyz,uyzz
      real uxt,uxxt,uxtt, uyt,uyyt,uytt

      declareGaussianVariables()


      amplitude  =1. 
      beta       =2.  ! 1/width       
      p          =2. ! 4. ! 2. 
      xp0        =.3
      xp1        =.4
      xp2        =.5
      vp0        =.25
      vp1        =.35
      vp2        =.15

      t=.1

      xa(0)=xp0 + vp0*t
      xa(1)=xp1 + vp1*t
      xa(2)=xp2 + vp2*t
      dx(0)=.03
      dx(1)=.04
      dx(2)=.05

      h = (1.e-16)**(1./4.)

      realMin=1.e-30  ! should be REAL_MIN

      betap=beta**p 
      q=p/2.
      r2Min=realMin*100.

      do nd=2,3

        ! (x,y,z) must be consistent with (i1,i2,i3)
        i1=1
        i2=1
        i3=1
        x = xa(0)+i1*dx(0)
        y = xa(1)+i2*dx(1)
        z = xa(2)+i3*dx(2) 


        if( nd.eq.2 )then

          getCoords(x0,x1,x2,2,rectangular)
          evalGaussianPulseAndDerivatives(x0,x1,x2,2,rectangular,3)

          ! compare derivatives to those from differences
          write(*,'("2d: rho=",e10.4)') rho

          checkx(2)

        else

          getCoords(x0,x1,x2,3,rectangular)
          evalGaussianPulseAndDerivatives(x0,x1,x2,3,rectangular,3)

          ! compare derivatives to those from differences

          checkx(3)

        end if

      end do

      return 
      end


      subroutine forcingOptMaxwell( nd, nd1a,nd1b,nd2a,nd2b,nd3a,nd3b,\
                               ndf1a,ndf1b,ndf2a,ndf2b,ndf3a,ndf3b,\
                               u,f,mask,rsxy, xy,\
                               ipar, rpar, ierr )
c ===================================================================================
c  Optimised Forcing functions for Maxwell's Equations.
c
c   Add the source terms for changes to the forcing RHS f.
c
c             f <- f + (charge source terms)
c
c ===================================================================================

      implicit none

      integer nd, nd1a,nd1b,nd2a,nd2b,nd3a,nd3b, ndf1a,ndf1b,ndf2a,ndf2b,ndf3a,ndf3b

      real u(nd1a:nd1b,nd2a:nd2b,nd3a:nd3b,0:*)
      real f(ndf1a:ndf1b,ndf2a:ndf2b,ndf3a:ndf3b,0:*)
      integer mask(nd1a:nd1b,nd2a:nd2b,nd3a:nd3b)
      real rsxy(nd1a:nd1b,nd2a:nd2b,nd3a:nd3b,0:nd-1,0:nd-1)
      real xy(nd1a:nd1b,nd2a:nd2b,nd3a:nd3b,0:nd-1)

      integer ipar(0:*)
      real rpar(0:*)

c     --- local variables ----
      
      integer ierr,orderOfExtrapolation
      integer n1a,n1b,n2a,n2b,n3a,n3b
      integer i1,i2,i3

      ! for macro:
      declareGaussianVariables()

      integer rectangular,curvilinear
      parameter(\
        rectangular=0,\
        curvilinear=1)

      ! forcingOption takes on these values:
      integer noForcing,magneticSinusoidalPointSource,gaussianSource,twilightZoneForcing,\
              planeWaveBoundaryForcing,gaussianChargeSource
      parameter(noForcing=0,\
           magneticSinusoidalPointSource=1,\
           gaussianSource=2,\
           twilightZoneForcing=3,\
           planeWaveBoundaryForcing=4,\
           gaussianChargeSource=5)


      integer gridType,orderOfAccuracyInSpace,orderOfAccuracyInTime,useForcing
      integer ex,ey,ez,hx,hy,hz,useWhereMask,grid,debug,forcingOption,icount
      real dx(0:2),dr(0:2),t,ep,dt,c,csq,dtsq,eps,mu,kx,ky,kz,slowStartInterval
      real xa(0:2)
      real amplitude,p,beta,xp0,xp1,xp2,vp0,vp1,vp2
      real tol, tolPulse

      ierr=0

      n1a                   =ipar(0)
      n1b                   =ipar(1)
      n2a                   =ipar(2)
      n2b                   =ipar(3)
      n3a                   =ipar(4)
      n3b                   =ipar(5)
      gridType              =ipar(6)
      orderOfAccuracyInSpace=ipar(7)
      orderOfAccuracyInTime =ipar(8)
      orderOfExtrapolation  =ipar(9) 
      useForcing            =ipar(10)
      ex                    =ipar(11)
      ey                    =ipar(12)
      ez                    =ipar(13)
      hx                    =ipar(14)
      hy                    =ipar(15)
      hz                    =ipar(16)
      useWhereMask          =ipar(17)
      grid                  =ipar(18)
      debug                 =ipar(19)
      forcingOption         =ipar(20)

      dx(0)                 =rpar(0)
      dx(1)                 =rpar(1)
      dx(2)                 =rpar(2)
      dr(0)                 =rpar(3)
      dr(1)                 =rpar(4)
      dr(2)                 =rpar(5)
      t                     =rpar(6)
      ep                    =rpar(7)
      dt                    =rpar(8)
      c                     =rpar(9)
      eps                   =rpar(10)
      mu                    =rpar(11)
      kx                    =rpar(12)  ! for plane wave forcing
      ky                    =rpar(13)
      kz                    =rpar(14)
      slowStartInterval     =rpar(15)
      xa(0)                 =rpar(16)  ! for rectangular grids
      xa(1)                 =rpar(17)
      xa(2)                 =rpar(18)
  
      amplitude             =rpar(19)  ! pulse parameters
      beta                  =rpar(20)  ! power
      p                     =rpar(21)  ! pulse parameters
      xp0                   =rpar(22)  ! initial position of the pulse
      xp1                   =rpar(23)
      xp2                   =rpar(24)
      vp0                   =rpar(25)  ! speed of the pulse
      vp1                   =rpar(26)
      vp2                   =rpar(27)

      realMin=1.e-30  ! should be REAL_MIN ******************** fix this ************

      csq=c*c 
      dtsq=dt*dt

      betap=beta**p 
      q=p/2.
      r2Min=realMin*100.

      tol=1.e-12  ! ignore relative pulse values below this ******************** fix this ************
      ! exp( -(beta*r)^p ) < tol   (don't include amplitude to make relative)
      tolPulse = ( ( log(1./tol)**(1./p) )/beta )**2 ! tolerance for r2=r^2 


      if( forcingOption.eq.gaussianChargeSource )then

       if( orderOfAccuracyInTime.eq.2 )then
        ! ***** 2nd order in time *****
        if( gridType.eq.curvilinear .and. nd.eq.2 )then

          !                               (DIM,ORDER,GRIDTYPE)
          assignGaussianPulseChargeDensity(2,2,curvilinear) 

        else if( gridType.eq.rectangular .and. nd.eq.2 )then

          !                               (DIM,ORDER,GRIDTYPE)
          assignGaussianPulseChargeDensity(2,2,rectangular) 

        else if( gridType.eq.curvilinear .and. nd.eq.3 )then

          !                               (DIM,ORDER,GRIDTYPE)
          assignGaussianPulseChargeDensity(3,2,curvilinear) 

        else if( gridType.eq.rectangular .and. nd.eq.3 )then

          !                               (DIM,ORDER,GRIDTYPE)
          assignGaussianPulseChargeDensity(3,2,rectangular) 

        else
          write(*,'("forcingOptMaxwell: case not implemented")')
          stop 7729
        end if

       else if( orderOfAccuracyInTime.eq.4 )then
        ! ***** 4th order in time *****
        if( gridType.eq.curvilinear .and. nd.eq.2 )then
          !                               (DIM,ORDER,GRIDTYPE)
          assignGaussianPulseChargeDensity(2,4,curvilinear) 

        else if( gridType.eq.rectangular .and. nd.eq.2 )then

          !                               (DIM,ORDER,GRIDTYPE)
          assignGaussianPulseChargeDensity(2,4,rectangular) 

        else if( gridType.eq.curvilinear .and. nd.eq.3 )then

          !                               (DIM,ORDER,GRIDTYPE)
          assignGaussianPulseChargeDensity(3,4,curvilinear) 

        else if( gridType.eq.rectangular .and. nd.eq.3 )then

          !                               (DIM,ORDER,GRIDTYPE)
          assignGaussianPulseChargeDensity(3,4,rectangular) 

        else
          write(*,'("forcingOptMaxwell: case not implemented")')
          stop 7729
        end if

       else
        write(*,'("forcingOptMaxwell: unknown orderOfAccuracyInTime",i6)') orderOfAccuracyInTime
        stop 5219
       end if

      else
        write(*,'("forcingOptMaxwell: unknown forcingOption=",i6)') forcingOption
        stop 5219
      end if

      return
      end
