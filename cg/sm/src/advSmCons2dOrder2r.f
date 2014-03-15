! This file automatically generated from advSmCons2dOrder2r.bf with bpp.
! ogf2d, ogf3d, ogDeriv2, etc. are foundin forcing.bC
      
      
!       ntd,nxd,nyd,nzd : number of derivatives to evaluate in t,x,y,z
      
       
      
      
      


! =========================================================================
!  Evaluate the RHS to the elasticity equations
! =========================================================================


! =================================================================
! Compute the RHS only including the cross-derivative terms
! =================================================================

! =================================================================
! Compute the RHS excluding the cross-derivative terms
! =================================================================


! =================================================================
! =================================================================

! =================================================================
! =================================================================

! =================================================================
! =================================================================




! ===========================================================================
! Advance the solution and update boundaries
! ===========================================================================
! end advanceSolutionMacro


c     
c     Advance the equations of solid mechanics
c       
      subroutine advSmCons2dOrder2r(nd,n1a,n1b,n2a,n2b,n3a,n3b,nd1a,
     & nd1b,
     &     nd2a,nd2b,nd3a,nd3b,nd4a,nd4b,mask,rsxy,xy, um,u,un,f,
     &     ndMatProp,matIndex,matValpc,matVal, bc, dis,
     &     varDis, ipar, rpar, ierr )
c======================================================================
c     Advance a time step for the equations of Solid Mechanics (linear elasticity for now)
c     
c     nd : number of space dimensions
c     
c     ipar(0)  = option : option=0 - Elasticity+Artificial diffusion
c     =1 - AD only
c     
c     dis(i1,i2,i3) : temp space to hold artificial dissipation
c     varDis(i1,i2,i3) : coefficient of the variable artificial dissipation
c======================================================================
      implicit none
      integer nd, n1a,n1b,n2a,n2b,n3a,n3b,nd1a,nd1b,nd2a,nd2b,nd3a,
     &     nd3b,nd4a,nd4b
      real um(nd1a:nd1b,nd2a:nd2b,nd3a:nd3b,nd4a:nd4b)
      real u(nd1a:nd1b,nd2a:nd2b,nd3a:nd3b,nd4a:nd4b)
      real un(nd1a:nd1b,nd2a:nd2b,nd3a:nd3b,nd4a:nd4b)
      real f(nd1a:nd1b,nd2a:nd2b,nd3a:nd3b,nd4a:nd4b)
      real dis(nd1a:nd1b,nd2a:nd2b,nd3a:nd3b,nd4a:nd4b)
      real varDis(nd1a:nd1b,nd2a:nd2b,nd3a:nd3b)
      real rsxy(nd1a:nd1b,nd2a:nd2b,nd3a:nd3b,0:nd-1,0:nd-1)
      real xy(nd1a:nd1b,nd2a:nd2b,nd3a:nd3b,0:nd-1)
      integer mask(nd1a:nd1b,nd2a:nd2b,nd3a:nd3b)
      integer bc(0:1,0:2),ierr
      integer ipar(0:*)
      real rpar(0:*)

      ! -- Declare arrays for variable material properties --
      include 'declareVarMatProp.h'

c     ---- local variables -----
      integer c,i1,i2,i3,n,gridType,orderOfAccuracy,orderInTime
      integer addForcing,orderOfDissipation,option
      integer useWhereMask,useWhereMaskSave,grid,
     &     useVariableDissipation,timeSteppingMethod
      integer useConservative,combineDissipationWithAdvance
      integer uc,vc,wc
      real dt,dx(0:3),adc,dr(0:3),c1,c2,kx,ky,kz,t
      real qx,qy,qz,rx,ry,rz,sx,sy,sz
      real lam2mu,lam,mu,uxy0,uy0,vxy0,vy0,epep,rho0,mu0,lambda0
      real l2m,l,m,lm,dxidxi0,dxidxi1,cofu(3,3),cofv(3,3)
      integer ipp,ip,im,jp,jm,i 
      real Dup, Dum, Dvp, Dvm, Ep, Em ,dcons,dc,Jac,u1,u2
      real rh1(nd1a:nd1b,nd2a:nd2b)
      real rh2(nd1a:nd1b,nd2a:nd2b)
      real dxi(0:2)
      real dtsq,dtsqByRho,errmaxu,errtmpu,exsolu,errmaxv,errtmpv,exsolv
      real du,fd22d,fd42d,adcdt,energy,weight
      real dtOld,cu,cum
      integer dirichlet,stressFree,debug,myid
      parameter( dirichlet=1,stressFree=2 )

      ! -- begin statement functions
      real rho,rhopc,mupc,lambdapc,lam2mupc, rhov,muv,lambdav,lam2muv
      ! (rho,mu,lambda) for materialFormat=piecewiseConstantMaterialProperties
      rhopc(i1,i2)    = matValpc( 0, matIndex(i1,i2))
      mupc(i1,i2)     = matValpc( 1, matIndex(i1,i2))
      lambdapc(i1,i2) = matValpc( 2, matIndex(i1,i2))
      lam2mupc(i1,i2) = (matValpc( 2, matIndex(i1,i2))+2.0*matValpc( 1,
     &  matIndex(i1,i2)))

      ! (rho,mu,lambda) for materialFormat=variableMaterialProperties
      rhov(i1,i2)    = matVal(i1,i2,0)
      muv(i1,i2)     = matVal(i1,i2,1)
      lambdav(i1,i2) = matVal(i1,i2,2)
      lam2muv(i1,i2) = (matVal(i1,i2,2)+2.0*matVal(i1,i2,1))

      ! lam(i1,i2)=(c1-c2)
      ! mu(i1,i2)=c2
      ! lam2mu(i1,i2)=(lam(i1,i2)+2.0*mu(i1,12))

      rho(i1,i2)=rho0
      lam(i1,i2)=lambda0
      mu(i1,i2)=mu0
      lam2mu(i1,i2)=(lambda0+2.0*mu0)

      u1(i1,i2)=u(i1,i2,0,uc)   !!???
      u2(i1,i2)=u(i1,i2,0,vc)   !!???
c ******* artificial dissipation ******
      du(i1,i2,i3,c)=u(i1,i2,i3,c)-um(i1,i2,i3,c)
c      (2nd difference)
      fd22d(i1,i2,i3,c)=(( du(i1-1,i2,i3,c)+du(i1+1,i2,i3,c)+du(i1,i2-
     & 1,i3,c)+du(i1,i2+1,i3,c) )-4.*du(i1,i2,i3,c))
c     -(fourth difference)
      fd42d(i1,i2,i3,c)=(-( du(i1-2,i2,i3,c)+du(i1+2,i2,i3,c)+du(i1,i2-
     & 2,i3,c)+du(i1,i2+2,i3,c) )+4.*( du(i1-1,i2,i3,c)+du(i1+1,i2,i3,
     & c)+du(i1,i2-1,i3,c)+du(i1,i2+1,i3,c) )-12.*du(i1,i2,i3,c) )
      ! -- end statement functions
      
      dt    =rpar(0)
      dx(0) =rpar(1)
      dx(1) =rpar(2)
      dx(2) =rpar(3)
      adc   =rpar(4)  ! coefficient of artificial dissipation
      dr(0) =rpar(5)
      dr(1) =rpar(6)
      dr(2) =rpar(7)
      c1    =rpar(8)
      c2    =rpar(9)
      kx    =rpar(10)
      ky    =rpar(11)
      kz    =rpar(12)
      epep  =rpar(13)
      t     =rpar(14)
      dtOld =rpar(15) ! dt used on the previous time step
      rho0  =rpar(16)  ! for constant coefficients
      mu0   =rpar(17)
      lambda0=rpar(18)

      option             =ipar(0)
      gridType           =ipar(1)
      orderOfAccuracy    =ipar(2)
      orderInTime        =ipar(3)
      addForcing         =ipar(4)
      orderOfDissipation =ipar(5)
      uc                 =ipar(6)
      vc                 =ipar(7)
      wc                 =ipar(8)
      useWhereMask       =ipar(9)
      timeSteppingMethod =ipar(10)
      useVariableDissipation=ipar(11)
      useConservative    =ipar(12)
      combineDissipationWithAdvance = ipar(13)
      debug              =ipar(14)
      materialFormat     =ipar(16)
      myid               =ipar(17)

      if( t.lt.dt )then
         write(*,'(" ***advSmCons2dOrder2r:INFO: materialFormat=",i2," 
     & (0=const, 1=pc, 2=var)")') materialFormat
         write(*,'(" ***advSmCons2dOrder2r:INFO: rho0,mu0,lambda0=",
     & 3e10.2)') rho0,mu0,lambda0
      end if

      ! --- Output rho, mu and lambda at t=0 for testing ---
      if( materialFormat.ne.0 .and. t.le.0 .and. (nd1b-nd1a)*(nd2b-
     & nd2a).lt. 1000 )then

       write(*,'("advSmCons2dOrder2r: rho:")')
       do i2=nd2b,nd2a,-1
         if( materialFormat.eq.piecewiseConstantMaterialProperties )
     & then
          write(*,9000) (rhopc(i1,i2),i1=nd1a,nd1b)
         else
          write(*,9000) (rhov(i1,i2),i1=nd1a,nd1b)
         end if
       end do
       write(*,'("advSmCons2dOrder2r: mu:")')
       do i2=nd2b,nd2a,-1
         if( materialFormat.eq.piecewiseConstantMaterialProperties )
     & then
          write(*,9000) (mupc(i1,i2),i1=nd1a,nd1b)
         else
          write(*,9000) (muv(i1,i2),i1=nd1a,nd1b)
         end if
       end do
       write(*,'("advSmCons2dOrder2r: lambda:")')
       do i2=nd2b,nd2a,-1
         if( materialFormat.eq.piecewiseConstantMaterialProperties )
     & then
          write(*,9000) (lambdapc(i1,i2),i1=nd1a,nd1b)
         else
          write(*,9000) (lambdav(i1,i2),i1=nd1a,nd1b)
         end if
       end do
       write(*,'("advSmCons2dOrder2r: lam2mu:")')
       do i2=nd2b,nd2a,-1
         if( materialFormat.eq.piecewiseConstantMaterialProperties )
     & then
          write(*,9000) (lam2mupc(i1,i2),i1=nd1a,nd1b)
         else
          write(*,9000) (lam2muv(i1,i2),i1=nd1a,nd1b)
         end if
       end do

 9000  format(100(f5.1))

      end if

      dtsq=dt*dt
      do i=0,2 
         dxi(i)=1.0/dx(i)
      enddo

      ! *wdh* 100201 -- fixes for variable time step : locally 2nd order --
      cu=  2.     ! coeff. of u(t) in the time-step formula
      cum=-1.     ! coeff. of u(t-dtOld)
      if( dtOld.le.0 )then
         write(*,'(" advSmCons:ERROR : dtOld<=0 ")')
         stop 8167
      end if
      if( dt.ne.dtOld )then
         write(*,'(" advSmCons:INFO: dt=",e12.4," <> dtOld=",e12.4," 
     & diff=",e9.2)') dt,dtOld,dt-dtOld
         ! adjust the coefficients for a variable time step : this is locally second order accurate
         cu= 1.+dt/dtOld     ! coeff. of u(t) in the time-step formula
         cum=-dt/dtOld       ! coeff. of u(t-dtOld)
         dtsq=dt*(dt+dtOld)*.5
      end if


      if( materialFormat.eq.piecewiseConstantMaterialProperties ) then

        ! --- piecewise constant material properties ---
          ! -- evaluate the interior equations at all points ---
          !  -- the cross terms on boundaries are fixed up afterward --
           dc=0.25*dxi(0)*dxi(1)
           do i2=n2a,n2b
           do i1=n1a,n1b
             rh1(i1,i2)=0.
             rh2(i1,i2)=0.
               ip=i1+1
               im=i1-1
               jp=i2+1
               jm=i2-1
               !       (2 mupc+lambdapc) uxx 
                 Ep=lam2mupc(ip,i2)+lam2mupc(i1,i2)
                 Em=lam2mupc(im,i2)+lam2mupc(i1,i2)
                 rh1(i1,i2)=rh1(i1,i2)+0.5*dxi(0)**2*(Ep*(u1(ip,i2)-u1(
     & i1,i2))-Em*(u1(i1,i2)-u1(im,i2)))
               ! write(2,'(" rhs1=",e14.8," (",i2,",",i2,") uxx ")') rh1(i1,i2),i1,i2
               ! mupc uyy 
                 Ep=mupc(i1,jp)+mupc(i1,i2)
                 Em=mupc(i1,jm)+mupc(i1,i2)
                 rh1(i1,i2)=rh1(i1,i2)+0.5*dxi(1)**2*(Ep*(u1(i1,jp)-u1(
     & i1,i2))-Em*(u1(i1,i2)-u1(i1,jm)))
               ! write(2,'(" rhs1=",e14.8," (",i2,",",i2,") uyy ")') rh1(i1,i2),i1,i2
               ! d_x lambdapc v_y
                 rh1(i1,i2)=rh1(i1,i2)+dc*(lambdapc(ip,i2)*(u2(ip,jp)-
     & u2(ip,jm))-lambdapc(im,i2)*(u2(im,jp)-u2(im,jm)))
               ! d_y mupc v_x
                 rh1(i1,i2)=rh1(i1,i2)+dc*(mupc(i1,jp)*(u2(ip,jp)-u2(
     & im,jp))-mupc(i1,jm)*(u2(ip,jm)-u2(im,jm)))
               ! write(2,'(" rhs1=",e14.8," (",i2,",",i2,") done ")') rh1(i1,i2),i1,i2
               ! mupc vxx 	
                 Ep=mupc(ip,i2)+mupc(i1,i2)
                 Em=mupc(im,i2)+mupc(i1,i2)
                 rh2(i1,i2)=rh2(i1,i2)+0.5*dxi(0)**2*(Ep*(u2(ip,i2)-u2(
     & i1,i2))-Em*(u2(i1,i2)-u2(im,i2)))
               ! write(2,'(" rhs2=",e14.8," (",i2,",",i2,") vxx ")') rh2(i1,i2),i1,i2
               ! (2 mupc + lambdapc) vyy 
                 Ep=lam2mupc(i1,jp)+lam2mupc(i1,i2)
                 Em=lam2mupc(i1,jm)+lam2mupc(i1,i2)
                 rh2(i1,i2)=rh2(i1,i2)+0.5*dxi(1)**2*(Ep*(u2(i1,jp)-u2(
     & i1,i2))-Em*(u2(i1,i2)-u2(i1,jm)))
               ! write(2,'(" rhs2=",e14.8," (",i2,",",i2,") vyy ")') rh2(i1,i2),i1,i2
               ! d_x mupc u_y
                 rh2(i1,i2)=rh2(i1,i2)+dc*(mupc(ip,i2)*(u1(ip,jp)-u1(
     & ip,jm))-mupc(im,i2)*(u1(im,jp)-u1(im,jm)))
               ! write(2,'(" rhs2=",e14.8," (",i2,",",i2,") (m uy).x ")') rh2(i1,i2),i1,i2
               ! d_y lambdapc u_x
                 rh2(i1,i2)=rh2(i1,i2)+dc*(lambdapc(i1,jp)*(u1(ip,jp)-
     & u1(im,jp))-lambdapc(i1,jm)*(u1(ip,jm)-u1(im,jm)))
               ! write(2,'(" rhs2=",e14.8," (",i2,",",i2,") done ")') rh2(i1,i2),i1,i2
           end do
           end do
           !  -- Now correct the cross terms on all the sides --
           dc=0.5*dxi(0)*dxi(1)
           if( bc(0,0).eq.stressFree)then
            do i2=n2a,n2b
            do i1=n1a,n1a
             rh1(i1,i2)=0.
             rh2(i1,i2)=0.
               ip=i1+1
               im=i1-1
               jp=i2+1
               jm=i2-1
               !       (2 mupc+lambdapc) uxx 
                 Ep=lam2mupc(ip,i2)+lam2mupc(i1,i2)
                 Em=lam2mupc(im,i2)+lam2mupc(i1,i2)
                 rh1(i1,i2)=rh1(i1,i2)+0.5*dxi(0)**2*(Ep*(u1(ip,i2)-u1(
     & i1,i2))-Em*(u1(i1,i2)-u1(im,i2)))
               ! mupc uyy 
                 Ep=mupc(i1,jp)+mupc(i1,i2)
                 Em=mupc(i1,jm)+mupc(i1,i2)
                 rh1(i1,i2)=rh1(i1,i2)+0.5*dxi(1)**2*(Ep*(u1(i1,jp)-u1(
     & i1,i2))-Em*(u1(i1,i2)-u1(i1,jm)))
               ! mupc vxx 	
                 Ep=mupc(ip,i2)+mupc(i1,i2)
                 Em=mupc(im,i2)+mupc(i1,i2)
                 rh2(i1,i2)=rh2(i1,i2)+0.5*dxi(0)**2*(Ep*(u2(ip,i2)-u2(
     & i1,i2))-Em*(u2(i1,i2)-u2(im,i2)))
               ! (2 mupc + lambdapc) vyy 
                 Ep=lam2mupc(i1,jp)+lam2mupc(i1,i2)
                 Em=lam2mupc(i1,jm)+lam2mupc(i1,i2)
                 rh2(i1,i2)=rh2(i1,i2)+0.5*dxi(1)**2*(Ep*(u2(i1,jp)-u2(
     & i1,i2))-Em*(u2(i1,i2)-u2(i1,jm)))
             ip=i1+1
             im=i1 
             jp=i2+1 
             jm=i2-1
               ! d_x lambdapc v_y
                 rh1(i1,i2)=rh1(i1,i2)+dc*(lambdapc(ip,i2)*(u2(ip,jp)-
     & u2(ip,jm))-lambdapc(im,i2)*(u2(im,jp)-u2(im,jm)))
               ! d_y mupc v_x
                 rh1(i1,i2)=rh1(i1,i2)+dc*(mupc(i1,jp)*(u2(ip,jp)-u2(
     & im,jp))-mupc(i1,jm)*(u2(ip,jm)-u2(im,jm)))
               ! d_x my u_y
                 rh2(i1,i2)=rh2(i1,i2)+dc*(mupc(ip,i2)*(u1(ip,jp)-u1(
     & ip,jm))-mupc(im,i2)*(u1(im,jp)-u1(im,jm)))
               ! d_y lambdapc u_x
                 rh2(i1,i2)=rh2(i1,i2)+dc*(lambdapc(i1,jp)*(u1(ip,jp)-
     & u1(im,jp))-lambdapc(i1,jm)*(u1(ip,jm)-u1(im,jm)))
            enddo
            enddo
           endif
           if( bc(1,0).eq.stressFree) then ! correct edge
            do i2=n2a,n2b
            do i1=n1b,n1b
             rh1(i1,i2)=0.
             rh2(i1,i2)=0.
               ip=i1+1
               im=i1-1
               jp=i2+1
               jm=i2-1
               !       (2 mupc+lambdapc) uxx 
                 Ep=lam2mupc(ip,i2)+lam2mupc(i1,i2)
                 Em=lam2mupc(im,i2)+lam2mupc(i1,i2)
                 rh1(i1,i2)=rh1(i1,i2)+0.5*dxi(0)**2*(Ep*(u1(ip,i2)-u1(
     & i1,i2))-Em*(u1(i1,i2)-u1(im,i2)))
               ! mupc uyy 
                 Ep=mupc(i1,jp)+mupc(i1,i2)
                 Em=mupc(i1,jm)+mupc(i1,i2)
                 rh1(i1,i2)=rh1(i1,i2)+0.5*dxi(1)**2*(Ep*(u1(i1,jp)-u1(
     & i1,i2))-Em*(u1(i1,i2)-u1(i1,jm)))
               ! mupc vxx 	
                 Ep=mupc(ip,i2)+mupc(i1,i2)
                 Em=mupc(im,i2)+mupc(i1,i2)
                 rh2(i1,i2)=rh2(i1,i2)+0.5*dxi(0)**2*(Ep*(u2(ip,i2)-u2(
     & i1,i2))-Em*(u2(i1,i2)-u2(im,i2)))
               ! (2 mupc + lambdapc) vyy 
                 Ep=lam2mupc(i1,jp)+lam2mupc(i1,i2)
                 Em=lam2mupc(i1,jm)+lam2mupc(i1,i2)
                 rh2(i1,i2)=rh2(i1,i2)+0.5*dxi(1)**2*(Ep*(u2(i1,jp)-u2(
     & i1,i2))-Em*(u2(i1,i2)-u2(i1,jm)))
             ip=i1
             im=i1-1
             jp=i2+1 
             jm=i2-1
               ! d_x lambdapc v_y
                 rh1(i1,i2)=rh1(i1,i2)+dc*(lambdapc(ip,i2)*(u2(ip,jp)-
     & u2(ip,jm))-lambdapc(im,i2)*(u2(im,jp)-u2(im,jm)))
               ! d_y mupc v_x
                 rh1(i1,i2)=rh1(i1,i2)+dc*(mupc(i1,jp)*(u2(ip,jp)-u2(
     & im,jp))-mupc(i1,jm)*(u2(ip,jm)-u2(im,jm)))
               ! d_x my u_y
                 rh2(i1,i2)=rh2(i1,i2)+dc*(mupc(ip,i2)*(u1(ip,jp)-u1(
     & ip,jm))-mupc(im,i2)*(u1(im,jp)-u1(im,jm)))
               ! d_y lambdapc u_x
                 rh2(i1,i2)=rh2(i1,i2)+dc*(lambdapc(i1,jp)*(u1(ip,jp)-
     & u1(im,jp))-lambdapc(i1,jm)*(u1(ip,jm)-u1(im,jm)))
            enddo
            enddo
           endif
           if( bc(0,1).eq.stressFree) then ! correct edge
            do i2=n2a,n2a
            do i1=n1a,n1b
             rh1(i1,i2)=0.
             rh2(i1,i2)=0.
               ip=i1+1
               im=i1-1
               jp=i2+1
               jm=i2-1
               !       (2 mupc+lambdapc) uxx 
                 Ep=lam2mupc(ip,i2)+lam2mupc(i1,i2)
                 Em=lam2mupc(im,i2)+lam2mupc(i1,i2)
                 rh1(i1,i2)=rh1(i1,i2)+0.5*dxi(0)**2*(Ep*(u1(ip,i2)-u1(
     & i1,i2))-Em*(u1(i1,i2)-u1(im,i2)))
               ! mupc uyy 
                 Ep=mupc(i1,jp)+mupc(i1,i2)
                 Em=mupc(i1,jm)+mupc(i1,i2)
                 rh1(i1,i2)=rh1(i1,i2)+0.5*dxi(1)**2*(Ep*(u1(i1,jp)-u1(
     & i1,i2))-Em*(u1(i1,i2)-u1(i1,jm)))
               ! mupc vxx 	
                 Ep=mupc(ip,i2)+mupc(i1,i2)
                 Em=mupc(im,i2)+mupc(i1,i2)
                 rh2(i1,i2)=rh2(i1,i2)+0.5*dxi(0)**2*(Ep*(u2(ip,i2)-u2(
     & i1,i2))-Em*(u2(i1,i2)-u2(im,i2)))
               ! (2 mupc + lambdapc) vyy 
                 Ep=lam2mupc(i1,jp)+lam2mupc(i1,i2)
                 Em=lam2mupc(i1,jm)+lam2mupc(i1,i2)
                 rh2(i1,i2)=rh2(i1,i2)+0.5*dxi(1)**2*(Ep*(u2(i1,jp)-u2(
     & i1,i2))-Em*(u2(i1,i2)-u2(i1,jm)))
             ip=i1+1
             im=i1-1 
             jp=i2+1
             jm=i2 
               ! d_x lambdapc v_y
                 rh1(i1,i2)=rh1(i1,i2)+dc*(lambdapc(ip,i2)*(u2(ip,jp)-
     & u2(ip,jm))-lambdapc(im,i2)*(u2(im,jp)-u2(im,jm)))
               ! d_y mupc v_x
                 rh1(i1,i2)=rh1(i1,i2)+dc*(mupc(i1,jp)*(u2(ip,jp)-u2(
     & im,jp))-mupc(i1,jm)*(u2(ip,jm)-u2(im,jm)))
               ! d_x my u_y
                 rh2(i1,i2)=rh2(i1,i2)+dc*(mupc(ip,i2)*(u1(ip,jp)-u1(
     & ip,jm))-mupc(im,i2)*(u1(im,jp)-u1(im,jm)))
               ! d_y lambdapc u_x
                 rh2(i1,i2)=rh2(i1,i2)+dc*(lambdapc(i1,jp)*(u1(ip,jp)-
     & u1(im,jp))-lambdapc(i1,jm)*(u1(ip,jm)-u1(im,jm)))
            enddo
            enddo
           endif
           if( bc(1,1).eq.stressFree) then ! correct edge
           do i2=n2b,n2b
           do i1=n1a,n1b
            rh1(i1,i2)=0.
            rh2(i1,i2)=0.
              ip=i1+1
              im=i1-1
              jp=i2+1
              jm=i2-1
              !       (2 mupc+lambdapc) uxx 
                Ep=lam2mupc(ip,i2)+lam2mupc(i1,i2)
                Em=lam2mupc(im,i2)+lam2mupc(i1,i2)
                rh1(i1,i2)=rh1(i1,i2)+0.5*dxi(0)**2*(Ep*(u1(ip,i2)-u1(
     & i1,i2))-Em*(u1(i1,i2)-u1(im,i2)))
              ! mupc uyy 
                Ep=mupc(i1,jp)+mupc(i1,i2)
                Em=mupc(i1,jm)+mupc(i1,i2)
                rh1(i1,i2)=rh1(i1,i2)+0.5*dxi(1)**2*(Ep*(u1(i1,jp)-u1(
     & i1,i2))-Em*(u1(i1,i2)-u1(i1,jm)))
              ! mupc vxx 	
                Ep=mupc(ip,i2)+mupc(i1,i2)
                Em=mupc(im,i2)+mupc(i1,i2)
                rh2(i1,i2)=rh2(i1,i2)+0.5*dxi(0)**2*(Ep*(u2(ip,i2)-u2(
     & i1,i2))-Em*(u2(i1,i2)-u2(im,i2)))
              ! (2 mupc + lambdapc) vyy 
                Ep=lam2mupc(i1,jp)+lam2mupc(i1,i2)
                Em=lam2mupc(i1,jm)+lam2mupc(i1,i2)
                rh2(i1,i2)=rh2(i1,i2)+0.5*dxi(1)**2*(Ep*(u2(i1,jp)-u2(
     & i1,i2))-Em*(u2(i1,i2)-u2(i1,jm)))
            ip=i1+1
            im=i1-1
            jp=i2
            jm=i2-1
              ! d_x lambdapc v_y
                rh1(i1,i2)=rh1(i1,i2)+dc*(lambdapc(ip,i2)*(u2(ip,jp)-
     & u2(ip,jm))-lambdapc(im,i2)*(u2(im,jp)-u2(im,jm)))
              ! d_y mupc v_x
                rh1(i1,i2)=rh1(i1,i2)+dc*(mupc(i1,jp)*(u2(ip,jp)-u2(im,
     & jp))-mupc(i1,jm)*(u2(ip,jm)-u2(im,jm)))
              ! d_x my u_y
                rh2(i1,i2)=rh2(i1,i2)+dc*(mupc(ip,i2)*(u1(ip,jp)-u1(ip,
     & jm))-mupc(im,i2)*(u1(im,jp)-u1(im,jm)))
              ! d_y lambdapc u_x
                rh2(i1,i2)=rh2(i1,i2)+dc*(lambdapc(i1,jp)*(u1(ip,jp)-
     & u1(im,jp))-lambdapc(i1,jm)*(u1(ip,jm)-u1(im,jm)))
           enddo
           enddo
          endif
          ! Now correct the corners
          dc=dxi(0)*dxi(1)
          if((bc(0,0).eq.stressFree).and.(bc(0,1).eq.stressFree))then
           do i2=n2a,n2a
           do i1=n1a,n1a
            rh1(i1,i2)=0.
            rh2(i1,i2)=0.
              ip=i1+1
              im=i1-1
              jp=i2+1
              jm=i2-1
              !       (2 mupc+lambdapc) uxx 
                Ep=lam2mupc(ip,i2)+lam2mupc(i1,i2)
                Em=lam2mupc(im,i2)+lam2mupc(i1,i2)
                rh1(i1,i2)=rh1(i1,i2)+0.5*dxi(0)**2*(Ep*(u1(ip,i2)-u1(
     & i1,i2))-Em*(u1(i1,i2)-u1(im,i2)))
              ! mupc uyy 
                Ep=mupc(i1,jp)+mupc(i1,i2)
                Em=mupc(i1,jm)+mupc(i1,i2)
                rh1(i1,i2)=rh1(i1,i2)+0.5*dxi(1)**2*(Ep*(u1(i1,jp)-u1(
     & i1,i2))-Em*(u1(i1,i2)-u1(i1,jm)))
              ! mupc vxx 	
                Ep=mupc(ip,i2)+mupc(i1,i2)
                Em=mupc(im,i2)+mupc(i1,i2)
                rh2(i1,i2)=rh2(i1,i2)+0.5*dxi(0)**2*(Ep*(u2(ip,i2)-u2(
     & i1,i2))-Em*(u2(i1,i2)-u2(im,i2)))
              ! (2 mupc + lambdapc) vyy 
                Ep=lam2mupc(i1,jp)+lam2mupc(i1,i2)
                Em=lam2mupc(i1,jm)+lam2mupc(i1,i2)
                rh2(i1,i2)=rh2(i1,i2)+0.5*dxi(1)**2*(Ep*(u2(i1,jp)-u2(
     & i1,i2))-Em*(u2(i1,i2)-u2(i1,jm)))
            ip=i1+1 
            im=i1
            jp=i2+1
            jm=i2
              ! d_x lambdapc v_y
                rh1(i1,i2)=rh1(i1,i2)+dc*(lambdapc(ip,i2)*(u2(ip,jp)-
     & u2(ip,jm))-lambdapc(im,i2)*(u2(im,jp)-u2(im,jm)))
              ! d_y mupc v_x
                rh1(i1,i2)=rh1(i1,i2)+dc*(mupc(i1,jp)*(u2(ip,jp)-u2(im,
     & jp))-mupc(i1,jm)*(u2(ip,jm)-u2(im,jm)))
              ! d_x my u_y
                rh2(i1,i2)=rh2(i1,i2)+dc*(mupc(ip,i2)*(u1(ip,jp)-u1(ip,
     & jm))-mupc(im,i2)*(u1(im,jp)-u1(im,jm)))
              ! d_y lambdapc u_x
                rh2(i1,i2)=rh2(i1,i2)+dc*(lambdapc(i1,jp)*(u1(ip,jp)-
     & u1(im,jp))-lambdapc(i1,jm)*(u1(ip,jm)-u1(im,jm)))
           enddo
           enddo
          endif
          if((bc(0,0).eq.stressFree).and.(bc(1,1).eq.stressFree))then
           do i2=n2b,n2b
           do i1=n1a,n1a
            rh1(i1,i2)=0.
            rh2(i1,i2)=0.
              ip=i1+1
              im=i1-1
              jp=i2+1
              jm=i2-1
              !       (2 mupc+lambdapc) uxx 
                Ep=lam2mupc(ip,i2)+lam2mupc(i1,i2)
                Em=lam2mupc(im,i2)+lam2mupc(i1,i2)
                rh1(i1,i2)=rh1(i1,i2)+0.5*dxi(0)**2*(Ep*(u1(ip,i2)-u1(
     & i1,i2))-Em*(u1(i1,i2)-u1(im,i2)))
              ! mupc uyy 
                Ep=mupc(i1,jp)+mupc(i1,i2)
                Em=mupc(i1,jm)+mupc(i1,i2)
                rh1(i1,i2)=rh1(i1,i2)+0.5*dxi(1)**2*(Ep*(u1(i1,jp)-u1(
     & i1,i2))-Em*(u1(i1,i2)-u1(i1,jm)))
              ! mupc vxx 	
                Ep=mupc(ip,i2)+mupc(i1,i2)
                Em=mupc(im,i2)+mupc(i1,i2)
                rh2(i1,i2)=rh2(i1,i2)+0.5*dxi(0)**2*(Ep*(u2(ip,i2)-u2(
     & i1,i2))-Em*(u2(i1,i2)-u2(im,i2)))
              ! (2 mupc + lambdapc) vyy 
                Ep=lam2mupc(i1,jp)+lam2mupc(i1,i2)
                Em=lam2mupc(i1,jm)+lam2mupc(i1,i2)
                rh2(i1,i2)=rh2(i1,i2)+0.5*dxi(1)**2*(Ep*(u2(i1,jp)-u2(
     & i1,i2))-Em*(u2(i1,i2)-u2(i1,jm)))
            ip=i1+1
            im=i1
            jp=i2
            jm=i2-1
              ! d_x lambdapc v_y
                rh1(i1,i2)=rh1(i1,i2)+dc*(lambdapc(ip,i2)*(u2(ip,jp)-
     & u2(ip,jm))-lambdapc(im,i2)*(u2(im,jp)-u2(im,jm)))
              ! d_y mupc v_x
                rh1(i1,i2)=rh1(i1,i2)+dc*(mupc(i1,jp)*(u2(ip,jp)-u2(im,
     & jp))-mupc(i1,jm)*(u2(ip,jm)-u2(im,jm)))
              ! d_x my u_y
                rh2(i1,i2)=rh2(i1,i2)+dc*(mupc(ip,i2)*(u1(ip,jp)-u1(ip,
     & jm))-mupc(im,i2)*(u1(im,jp)-u1(im,jm)))
              ! d_y lambdapc u_x
                rh2(i1,i2)=rh2(i1,i2)+dc*(lambdapc(i1,jp)*(u1(ip,jp)-
     & u1(im,jp))-lambdapc(i1,jm)*(u1(ip,jm)-u1(im,jm)))
           enddo
           enddo
          endif
          if((bc(1,0).eq.stressFree).and.(bc(0,1).eq.stressFree))then
           do i2=n2a,n2a
           do i1=n1b,n1b
            rh1(i1,i2)=0.
            rh2(i1,i2)=0.
              ip=i1+1
              im=i1-1
              jp=i2+1
              jm=i2-1
              !       (2 mupc+lambdapc) uxx 
                Ep=lam2mupc(ip,i2)+lam2mupc(i1,i2)
                Em=lam2mupc(im,i2)+lam2mupc(i1,i2)
                rh1(i1,i2)=rh1(i1,i2)+0.5*dxi(0)**2*(Ep*(u1(ip,i2)-u1(
     & i1,i2))-Em*(u1(i1,i2)-u1(im,i2)))
              ! mupc uyy 
                Ep=mupc(i1,jp)+mupc(i1,i2)
                Em=mupc(i1,jm)+mupc(i1,i2)
                rh1(i1,i2)=rh1(i1,i2)+0.5*dxi(1)**2*(Ep*(u1(i1,jp)-u1(
     & i1,i2))-Em*(u1(i1,i2)-u1(i1,jm)))
              ! mupc vxx 	
                Ep=mupc(ip,i2)+mupc(i1,i2)
                Em=mupc(im,i2)+mupc(i1,i2)
                rh2(i1,i2)=rh2(i1,i2)+0.5*dxi(0)**2*(Ep*(u2(ip,i2)-u2(
     & i1,i2))-Em*(u2(i1,i2)-u2(im,i2)))
              ! (2 mupc + lambdapc) vyy 
                Ep=lam2mupc(i1,jp)+lam2mupc(i1,i2)
                Em=lam2mupc(i1,jm)+lam2mupc(i1,i2)
                rh2(i1,i2)=rh2(i1,i2)+0.5*dxi(1)**2*(Ep*(u2(i1,jp)-u2(
     & i1,i2))-Em*(u2(i1,i2)-u2(i1,jm)))
            ip=i1
            im=i1-1
            jp=i2+1
            jm=i2
              ! d_x lambdapc v_y
                rh1(i1,i2)=rh1(i1,i2)+dc*(lambdapc(ip,i2)*(u2(ip,jp)-
     & u2(ip,jm))-lambdapc(im,i2)*(u2(im,jp)-u2(im,jm)))
              ! d_y mupc v_x
                rh1(i1,i2)=rh1(i1,i2)+dc*(mupc(i1,jp)*(u2(ip,jp)-u2(im,
     & jp))-mupc(i1,jm)*(u2(ip,jm)-u2(im,jm)))
              ! d_x my u_y
                rh2(i1,i2)=rh2(i1,i2)+dc*(mupc(ip,i2)*(u1(ip,jp)-u1(ip,
     & jm))-mupc(im,i2)*(u1(im,jp)-u1(im,jm)))
              ! d_y lambdapc u_x
                rh2(i1,i2)=rh2(i1,i2)+dc*(lambdapc(i1,jp)*(u1(ip,jp)-
     & u1(im,jp))-lambdapc(i1,jm)*(u1(ip,jm)-u1(im,jm)))
           enddo
           enddo
          endif
          if((bc(1,1).eq.stressFree).and.(bc(1,0).eq.stressFree))then
           do i2=n2b,n2b
           do i1=n1b,n1b
            rh1(i1,i2)=0.
            rh2(i1,i2)=0.
              ip=i1+1
              im=i1-1
              jp=i2+1
              jm=i2-1
              !       (2 mupc+lambdapc) uxx 
                Ep=lam2mupc(ip,i2)+lam2mupc(i1,i2)
                Em=lam2mupc(im,i2)+lam2mupc(i1,i2)
                rh1(i1,i2)=rh1(i1,i2)+0.5*dxi(0)**2*(Ep*(u1(ip,i2)-u1(
     & i1,i2))-Em*(u1(i1,i2)-u1(im,i2)))
              ! mupc uyy 
                Ep=mupc(i1,jp)+mupc(i1,i2)
                Em=mupc(i1,jm)+mupc(i1,i2)
                rh1(i1,i2)=rh1(i1,i2)+0.5*dxi(1)**2*(Ep*(u1(i1,jp)-u1(
     & i1,i2))-Em*(u1(i1,i2)-u1(i1,jm)))
              ! mupc vxx 	
                Ep=mupc(ip,i2)+mupc(i1,i2)
                Em=mupc(im,i2)+mupc(i1,i2)
                rh2(i1,i2)=rh2(i1,i2)+0.5*dxi(0)**2*(Ep*(u2(ip,i2)-u2(
     & i1,i2))-Em*(u2(i1,i2)-u2(im,i2)))
              ! (2 mupc + lambdapc) vyy 
                Ep=lam2mupc(i1,jp)+lam2mupc(i1,i2)
                Em=lam2mupc(i1,jm)+lam2mupc(i1,i2)
                rh2(i1,i2)=rh2(i1,i2)+0.5*dxi(1)**2*(Ep*(u2(i1,jp)-u2(
     & i1,i2))-Em*(u2(i1,i2)-u2(i1,jm)))
            ip=i1
            im=i1-1
            jp=i2
            jm=i2-1
              ! d_x lambdapc v_y
                rh1(i1,i2)=rh1(i1,i2)+dc*(lambdapc(ip,i2)*(u2(ip,jp)-
     & u2(ip,jm))-lambdapc(im,i2)*(u2(im,jp)-u2(im,jm)))
              ! d_y mupc v_x
                rh1(i1,i2)=rh1(i1,i2)+dc*(mupc(i1,jp)*(u2(ip,jp)-u2(im,
     & jp))-mupc(i1,jm)*(u2(ip,jm)-u2(im,jm)))
              ! d_x my u_y
                rh2(i1,i2)=rh2(i1,i2)+dc*(mupc(ip,i2)*(u1(ip,jp)-u1(ip,
     & jm))-mupc(im,i2)*(u1(im,jp)-u1(im,jm)))
              ! d_y lambdapc u_x
                rh2(i1,i2)=rh2(i1,i2)+dc*(lambdapc(i1,jp)*(u1(ip,jp)-
     & u1(im,jp))-lambdapc(i1,jm)*(u1(ip,jm)-u1(im,jm)))
           enddo
           enddo
          endif
          !   --- Assign next time level ---
          do i2=n2a,n2b
          do i1=n1a,n1b
            dtsqByRho = dtsq/rhopc(i1,i2)
            un(i1,i2,nd3a,uc)=cu*u(i1,i2,nd3a,uc)+cum*um(i1,i2,nd3a,uc)
     & +dtsqByRho*rh1(i1,i2)
            un(i1,i2,nd3a,vc)=cu*u(i1,i2,nd3a,vc)+cum*um(i1,i2,nd3a,vc)
     & +dtsqByRho*rh2(i1,i2)
          end do
          end do

      else if( materialFormat.eq.variableMaterialProperties ) then

        ! --- variable material properties ---
          ! -- evaluate the interior equations at all points ---
          !  -- the cross terms on boundaries are fixed up afterward --
           dc=0.25*dxi(0)*dxi(1)
           do i2=n2a,n2b
           do i1=n1a,n1b
             rh1(i1,i2)=0.
             rh2(i1,i2)=0.
               ip=i1+1
               im=i1-1
               jp=i2+1
               jm=i2-1
               !       (2 muv+lambdav) uxx 
                 Ep=lam2muv(ip,i2)+lam2muv(i1,i2)
                 Em=lam2muv(im,i2)+lam2muv(i1,i2)
                 rh1(i1,i2)=rh1(i1,i2)+0.5*dxi(0)**2*(Ep*(u1(ip,i2)-u1(
     & i1,i2))-Em*(u1(i1,i2)-u1(im,i2)))
               ! write(2,'(" rhs1=",e14.8," (",i2,",",i2,") uxx ")') rh1(i1,i2),i1,i2
               ! muv uyy 
                 Ep=muv(i1,jp)+muv(i1,i2)
                 Em=muv(i1,jm)+muv(i1,i2)
                 rh1(i1,i2)=rh1(i1,i2)+0.5*dxi(1)**2*(Ep*(u1(i1,jp)-u1(
     & i1,i2))-Em*(u1(i1,i2)-u1(i1,jm)))
               ! write(2,'(" rhs1=",e14.8," (",i2,",",i2,") uyy ")') rh1(i1,i2),i1,i2
               ! d_x lambdav v_y
                 rh1(i1,i2)=rh1(i1,i2)+dc*(lambdav(ip,i2)*(u2(ip,jp)-
     & u2(ip,jm))-lambdav(im,i2)*(u2(im,jp)-u2(im,jm)))
               ! d_y muv v_x
                 rh1(i1,i2)=rh1(i1,i2)+dc*(muv(i1,jp)*(u2(ip,jp)-u2(im,
     & jp))-muv(i1,jm)*(u2(ip,jm)-u2(im,jm)))
               ! write(2,'(" rhs1=",e14.8," (",i2,",",i2,") done ")') rh1(i1,i2),i1,i2
               ! muv vxx 	
                 Ep=muv(ip,i2)+muv(i1,i2)
                 Em=muv(im,i2)+muv(i1,i2)
                 rh2(i1,i2)=rh2(i1,i2)+0.5*dxi(0)**2*(Ep*(u2(ip,i2)-u2(
     & i1,i2))-Em*(u2(i1,i2)-u2(im,i2)))
               ! write(2,'(" rhs2=",e14.8," (",i2,",",i2,") vxx ")') rh2(i1,i2),i1,i2
               ! (2 muv + lambdav) vyy 
                 Ep=lam2muv(i1,jp)+lam2muv(i1,i2)
                 Em=lam2muv(i1,jm)+lam2muv(i1,i2)
                 rh2(i1,i2)=rh2(i1,i2)+0.5*dxi(1)**2*(Ep*(u2(i1,jp)-u2(
     & i1,i2))-Em*(u2(i1,i2)-u2(i1,jm)))
               ! write(2,'(" rhs2=",e14.8," (",i2,",",i2,") vyy ")') rh2(i1,i2),i1,i2
               ! d_x muv u_y
                 rh2(i1,i2)=rh2(i1,i2)+dc*(muv(ip,i2)*(u1(ip,jp)-u1(ip,
     & jm))-muv(im,i2)*(u1(im,jp)-u1(im,jm)))
               ! write(2,'(" rhs2=",e14.8," (",i2,",",i2,") (m uy).x ")') rh2(i1,i2),i1,i2
               ! d_y lambdav u_x
                 rh2(i1,i2)=rh2(i1,i2)+dc*(lambdav(i1,jp)*(u1(ip,jp)-
     & u1(im,jp))-lambdav(i1,jm)*(u1(ip,jm)-u1(im,jm)))
               ! write(2,'(" rhs2=",e14.8," (",i2,",",i2,") done ")') rh2(i1,i2),i1,i2
           end do
           end do
           !  -- Now correct the cross terms on all the sides --
           dc=0.5*dxi(0)*dxi(1)
           if( bc(0,0).eq.stressFree)then
            do i2=n2a,n2b
            do i1=n1a,n1a
             rh1(i1,i2)=0.
             rh2(i1,i2)=0.
               ip=i1+1
               im=i1-1
               jp=i2+1
               jm=i2-1
               !       (2 muv+lambdav) uxx 
                 Ep=lam2muv(ip,i2)+lam2muv(i1,i2)
                 Em=lam2muv(im,i2)+lam2muv(i1,i2)
                 rh1(i1,i2)=rh1(i1,i2)+0.5*dxi(0)**2*(Ep*(u1(ip,i2)-u1(
     & i1,i2))-Em*(u1(i1,i2)-u1(im,i2)))
               ! muv uyy 
                 Ep=muv(i1,jp)+muv(i1,i2)
                 Em=muv(i1,jm)+muv(i1,i2)
                 rh1(i1,i2)=rh1(i1,i2)+0.5*dxi(1)**2*(Ep*(u1(i1,jp)-u1(
     & i1,i2))-Em*(u1(i1,i2)-u1(i1,jm)))
               ! muv vxx 	
                 Ep=muv(ip,i2)+muv(i1,i2)
                 Em=muv(im,i2)+muv(i1,i2)
                 rh2(i1,i2)=rh2(i1,i2)+0.5*dxi(0)**2*(Ep*(u2(ip,i2)-u2(
     & i1,i2))-Em*(u2(i1,i2)-u2(im,i2)))
               ! (2 muv + lambdav) vyy 
                 Ep=lam2muv(i1,jp)+lam2muv(i1,i2)
                 Em=lam2muv(i1,jm)+lam2muv(i1,i2)
                 rh2(i1,i2)=rh2(i1,i2)+0.5*dxi(1)**2*(Ep*(u2(i1,jp)-u2(
     & i1,i2))-Em*(u2(i1,i2)-u2(i1,jm)))
             ip=i1+1
             im=i1 
             jp=i2+1 
             jm=i2-1
               ! d_x lambdav v_y
                 rh1(i1,i2)=rh1(i1,i2)+dc*(lambdav(ip,i2)*(u2(ip,jp)-
     & u2(ip,jm))-lambdav(im,i2)*(u2(im,jp)-u2(im,jm)))
               ! d_y muv v_x
                 rh1(i1,i2)=rh1(i1,i2)+dc*(muv(i1,jp)*(u2(ip,jp)-u2(im,
     & jp))-muv(i1,jm)*(u2(ip,jm)-u2(im,jm)))
               ! d_x my u_y
                 rh2(i1,i2)=rh2(i1,i2)+dc*(muv(ip,i2)*(u1(ip,jp)-u1(ip,
     & jm))-muv(im,i2)*(u1(im,jp)-u1(im,jm)))
               ! d_y lambdav u_x
                 rh2(i1,i2)=rh2(i1,i2)+dc*(lambdav(i1,jp)*(u1(ip,jp)-
     & u1(im,jp))-lambdav(i1,jm)*(u1(ip,jm)-u1(im,jm)))
            enddo
            enddo
           endif
           if( bc(1,0).eq.stressFree) then ! correct edge
            do i2=n2a,n2b
            do i1=n1b,n1b
             rh1(i1,i2)=0.
             rh2(i1,i2)=0.
               ip=i1+1
               im=i1-1
               jp=i2+1
               jm=i2-1
               !       (2 muv+lambdav) uxx 
                 Ep=lam2muv(ip,i2)+lam2muv(i1,i2)
                 Em=lam2muv(im,i2)+lam2muv(i1,i2)
                 rh1(i1,i2)=rh1(i1,i2)+0.5*dxi(0)**2*(Ep*(u1(ip,i2)-u1(
     & i1,i2))-Em*(u1(i1,i2)-u1(im,i2)))
               ! muv uyy 
                 Ep=muv(i1,jp)+muv(i1,i2)
                 Em=muv(i1,jm)+muv(i1,i2)
                 rh1(i1,i2)=rh1(i1,i2)+0.5*dxi(1)**2*(Ep*(u1(i1,jp)-u1(
     & i1,i2))-Em*(u1(i1,i2)-u1(i1,jm)))
               ! muv vxx 	
                 Ep=muv(ip,i2)+muv(i1,i2)
                 Em=muv(im,i2)+muv(i1,i2)
                 rh2(i1,i2)=rh2(i1,i2)+0.5*dxi(0)**2*(Ep*(u2(ip,i2)-u2(
     & i1,i2))-Em*(u2(i1,i2)-u2(im,i2)))
               ! (2 muv + lambdav) vyy 
                 Ep=lam2muv(i1,jp)+lam2muv(i1,i2)
                 Em=lam2muv(i1,jm)+lam2muv(i1,i2)
                 rh2(i1,i2)=rh2(i1,i2)+0.5*dxi(1)**2*(Ep*(u2(i1,jp)-u2(
     & i1,i2))-Em*(u2(i1,i2)-u2(i1,jm)))
             ip=i1
             im=i1-1
             jp=i2+1 
             jm=i2-1
               ! d_x lambdav v_y
                 rh1(i1,i2)=rh1(i1,i2)+dc*(lambdav(ip,i2)*(u2(ip,jp)-
     & u2(ip,jm))-lambdav(im,i2)*(u2(im,jp)-u2(im,jm)))
               ! d_y muv v_x
                 rh1(i1,i2)=rh1(i1,i2)+dc*(muv(i1,jp)*(u2(ip,jp)-u2(im,
     & jp))-muv(i1,jm)*(u2(ip,jm)-u2(im,jm)))
               ! d_x my u_y
                 rh2(i1,i2)=rh2(i1,i2)+dc*(muv(ip,i2)*(u1(ip,jp)-u1(ip,
     & jm))-muv(im,i2)*(u1(im,jp)-u1(im,jm)))
               ! d_y lambdav u_x
                 rh2(i1,i2)=rh2(i1,i2)+dc*(lambdav(i1,jp)*(u1(ip,jp)-
     & u1(im,jp))-lambdav(i1,jm)*(u1(ip,jm)-u1(im,jm)))
            enddo
            enddo
           endif
           if( bc(0,1).eq.stressFree) then ! correct edge
            do i2=n2a,n2a
            do i1=n1a,n1b
             rh1(i1,i2)=0.
             rh2(i1,i2)=0.
               ip=i1+1
               im=i1-1
               jp=i2+1
               jm=i2-1
               !       (2 muv+lambdav) uxx 
                 Ep=lam2muv(ip,i2)+lam2muv(i1,i2)
                 Em=lam2muv(im,i2)+lam2muv(i1,i2)
                 rh1(i1,i2)=rh1(i1,i2)+0.5*dxi(0)**2*(Ep*(u1(ip,i2)-u1(
     & i1,i2))-Em*(u1(i1,i2)-u1(im,i2)))
               ! muv uyy 
                 Ep=muv(i1,jp)+muv(i1,i2)
                 Em=muv(i1,jm)+muv(i1,i2)
                 rh1(i1,i2)=rh1(i1,i2)+0.5*dxi(1)**2*(Ep*(u1(i1,jp)-u1(
     & i1,i2))-Em*(u1(i1,i2)-u1(i1,jm)))
               ! muv vxx 	
                 Ep=muv(ip,i2)+muv(i1,i2)
                 Em=muv(im,i2)+muv(i1,i2)
                 rh2(i1,i2)=rh2(i1,i2)+0.5*dxi(0)**2*(Ep*(u2(ip,i2)-u2(
     & i1,i2))-Em*(u2(i1,i2)-u2(im,i2)))
               ! (2 muv + lambdav) vyy 
                 Ep=lam2muv(i1,jp)+lam2muv(i1,i2)
                 Em=lam2muv(i1,jm)+lam2muv(i1,i2)
                 rh2(i1,i2)=rh2(i1,i2)+0.5*dxi(1)**2*(Ep*(u2(i1,jp)-u2(
     & i1,i2))-Em*(u2(i1,i2)-u2(i1,jm)))
             ip=i1+1
             im=i1-1 
             jp=i2+1
             jm=i2 
               ! d_x lambdav v_y
                 rh1(i1,i2)=rh1(i1,i2)+dc*(lambdav(ip,i2)*(u2(ip,jp)-
     & u2(ip,jm))-lambdav(im,i2)*(u2(im,jp)-u2(im,jm)))
               ! d_y muv v_x
                 rh1(i1,i2)=rh1(i1,i2)+dc*(muv(i1,jp)*(u2(ip,jp)-u2(im,
     & jp))-muv(i1,jm)*(u2(ip,jm)-u2(im,jm)))
               ! d_x my u_y
                 rh2(i1,i2)=rh2(i1,i2)+dc*(muv(ip,i2)*(u1(ip,jp)-u1(ip,
     & jm))-muv(im,i2)*(u1(im,jp)-u1(im,jm)))
               ! d_y lambdav u_x
                 rh2(i1,i2)=rh2(i1,i2)+dc*(lambdav(i1,jp)*(u1(ip,jp)-
     & u1(im,jp))-lambdav(i1,jm)*(u1(ip,jm)-u1(im,jm)))
            enddo
            enddo
           endif
           if( bc(1,1).eq.stressFree) then ! correct edge
           do i2=n2b,n2b
           do i1=n1a,n1b
            rh1(i1,i2)=0.
            rh2(i1,i2)=0.
              ip=i1+1
              im=i1-1
              jp=i2+1
              jm=i2-1
              !       (2 muv+lambdav) uxx 
                Ep=lam2muv(ip,i2)+lam2muv(i1,i2)
                Em=lam2muv(im,i2)+lam2muv(i1,i2)
                rh1(i1,i2)=rh1(i1,i2)+0.5*dxi(0)**2*(Ep*(u1(ip,i2)-u1(
     & i1,i2))-Em*(u1(i1,i2)-u1(im,i2)))
              ! muv uyy 
                Ep=muv(i1,jp)+muv(i1,i2)
                Em=muv(i1,jm)+muv(i1,i2)
                rh1(i1,i2)=rh1(i1,i2)+0.5*dxi(1)**2*(Ep*(u1(i1,jp)-u1(
     & i1,i2))-Em*(u1(i1,i2)-u1(i1,jm)))
              ! muv vxx 	
                Ep=muv(ip,i2)+muv(i1,i2)
                Em=muv(im,i2)+muv(i1,i2)
                rh2(i1,i2)=rh2(i1,i2)+0.5*dxi(0)**2*(Ep*(u2(ip,i2)-u2(
     & i1,i2))-Em*(u2(i1,i2)-u2(im,i2)))
              ! (2 muv + lambdav) vyy 
                Ep=lam2muv(i1,jp)+lam2muv(i1,i2)
                Em=lam2muv(i1,jm)+lam2muv(i1,i2)
                rh2(i1,i2)=rh2(i1,i2)+0.5*dxi(1)**2*(Ep*(u2(i1,jp)-u2(
     & i1,i2))-Em*(u2(i1,i2)-u2(i1,jm)))
            ip=i1+1
            im=i1-1
            jp=i2
            jm=i2-1
              ! d_x lambdav v_y
                rh1(i1,i2)=rh1(i1,i2)+dc*(lambdav(ip,i2)*(u2(ip,jp)-u2(
     & ip,jm))-lambdav(im,i2)*(u2(im,jp)-u2(im,jm)))
              ! d_y muv v_x
                rh1(i1,i2)=rh1(i1,i2)+dc*(muv(i1,jp)*(u2(ip,jp)-u2(im,
     & jp))-muv(i1,jm)*(u2(ip,jm)-u2(im,jm)))
              ! d_x my u_y
                rh2(i1,i2)=rh2(i1,i2)+dc*(muv(ip,i2)*(u1(ip,jp)-u1(ip,
     & jm))-muv(im,i2)*(u1(im,jp)-u1(im,jm)))
              ! d_y lambdav u_x
                rh2(i1,i2)=rh2(i1,i2)+dc*(lambdav(i1,jp)*(u1(ip,jp)-u1(
     & im,jp))-lambdav(i1,jm)*(u1(ip,jm)-u1(im,jm)))
           enddo
           enddo
          endif
          ! Now correct the corners
          dc=dxi(0)*dxi(1)
          if((bc(0,0).eq.stressFree).and.(bc(0,1).eq.stressFree))then
           do i2=n2a,n2a
           do i1=n1a,n1a
            rh1(i1,i2)=0.
            rh2(i1,i2)=0.
              ip=i1+1
              im=i1-1
              jp=i2+1
              jm=i2-1
              !       (2 muv+lambdav) uxx 
                Ep=lam2muv(ip,i2)+lam2muv(i1,i2)
                Em=lam2muv(im,i2)+lam2muv(i1,i2)
                rh1(i1,i2)=rh1(i1,i2)+0.5*dxi(0)**2*(Ep*(u1(ip,i2)-u1(
     & i1,i2))-Em*(u1(i1,i2)-u1(im,i2)))
              ! muv uyy 
                Ep=muv(i1,jp)+muv(i1,i2)
                Em=muv(i1,jm)+muv(i1,i2)
                rh1(i1,i2)=rh1(i1,i2)+0.5*dxi(1)**2*(Ep*(u1(i1,jp)-u1(
     & i1,i2))-Em*(u1(i1,i2)-u1(i1,jm)))
              ! muv vxx 	
                Ep=muv(ip,i2)+muv(i1,i2)
                Em=muv(im,i2)+muv(i1,i2)
                rh2(i1,i2)=rh2(i1,i2)+0.5*dxi(0)**2*(Ep*(u2(ip,i2)-u2(
     & i1,i2))-Em*(u2(i1,i2)-u2(im,i2)))
              ! (2 muv + lambdav) vyy 
                Ep=lam2muv(i1,jp)+lam2muv(i1,i2)
                Em=lam2muv(i1,jm)+lam2muv(i1,i2)
                rh2(i1,i2)=rh2(i1,i2)+0.5*dxi(1)**2*(Ep*(u2(i1,jp)-u2(
     & i1,i2))-Em*(u2(i1,i2)-u2(i1,jm)))
            ip=i1+1 
            im=i1
            jp=i2+1
            jm=i2
              ! d_x lambdav v_y
                rh1(i1,i2)=rh1(i1,i2)+dc*(lambdav(ip,i2)*(u2(ip,jp)-u2(
     & ip,jm))-lambdav(im,i2)*(u2(im,jp)-u2(im,jm)))
              ! d_y muv v_x
                rh1(i1,i2)=rh1(i1,i2)+dc*(muv(i1,jp)*(u2(ip,jp)-u2(im,
     & jp))-muv(i1,jm)*(u2(ip,jm)-u2(im,jm)))
              ! d_x my u_y
                rh2(i1,i2)=rh2(i1,i2)+dc*(muv(ip,i2)*(u1(ip,jp)-u1(ip,
     & jm))-muv(im,i2)*(u1(im,jp)-u1(im,jm)))
              ! d_y lambdav u_x
                rh2(i1,i2)=rh2(i1,i2)+dc*(lambdav(i1,jp)*(u1(ip,jp)-u1(
     & im,jp))-lambdav(i1,jm)*(u1(ip,jm)-u1(im,jm)))
           enddo
           enddo
          endif
          if((bc(0,0).eq.stressFree).and.(bc(1,1).eq.stressFree))then
           do i2=n2b,n2b
           do i1=n1a,n1a
            rh1(i1,i2)=0.
            rh2(i1,i2)=0.
              ip=i1+1
              im=i1-1
              jp=i2+1
              jm=i2-1
              !       (2 muv+lambdav) uxx 
                Ep=lam2muv(ip,i2)+lam2muv(i1,i2)
                Em=lam2muv(im,i2)+lam2muv(i1,i2)
                rh1(i1,i2)=rh1(i1,i2)+0.5*dxi(0)**2*(Ep*(u1(ip,i2)-u1(
     & i1,i2))-Em*(u1(i1,i2)-u1(im,i2)))
              ! muv uyy 
                Ep=muv(i1,jp)+muv(i1,i2)
                Em=muv(i1,jm)+muv(i1,i2)
                rh1(i1,i2)=rh1(i1,i2)+0.5*dxi(1)**2*(Ep*(u1(i1,jp)-u1(
     & i1,i2))-Em*(u1(i1,i2)-u1(i1,jm)))
              ! muv vxx 	
                Ep=muv(ip,i2)+muv(i1,i2)
                Em=muv(im,i2)+muv(i1,i2)
                rh2(i1,i2)=rh2(i1,i2)+0.5*dxi(0)**2*(Ep*(u2(ip,i2)-u2(
     & i1,i2))-Em*(u2(i1,i2)-u2(im,i2)))
              ! (2 muv + lambdav) vyy 
                Ep=lam2muv(i1,jp)+lam2muv(i1,i2)
                Em=lam2muv(i1,jm)+lam2muv(i1,i2)
                rh2(i1,i2)=rh2(i1,i2)+0.5*dxi(1)**2*(Ep*(u2(i1,jp)-u2(
     & i1,i2))-Em*(u2(i1,i2)-u2(i1,jm)))
            ip=i1+1
            im=i1
            jp=i2
            jm=i2-1
              ! d_x lambdav v_y
                rh1(i1,i2)=rh1(i1,i2)+dc*(lambdav(ip,i2)*(u2(ip,jp)-u2(
     & ip,jm))-lambdav(im,i2)*(u2(im,jp)-u2(im,jm)))
              ! d_y muv v_x
                rh1(i1,i2)=rh1(i1,i2)+dc*(muv(i1,jp)*(u2(ip,jp)-u2(im,
     & jp))-muv(i1,jm)*(u2(ip,jm)-u2(im,jm)))
              ! d_x my u_y
                rh2(i1,i2)=rh2(i1,i2)+dc*(muv(ip,i2)*(u1(ip,jp)-u1(ip,
     & jm))-muv(im,i2)*(u1(im,jp)-u1(im,jm)))
              ! d_y lambdav u_x
                rh2(i1,i2)=rh2(i1,i2)+dc*(lambdav(i1,jp)*(u1(ip,jp)-u1(
     & im,jp))-lambdav(i1,jm)*(u1(ip,jm)-u1(im,jm)))
           enddo
           enddo
          endif
          if((bc(1,0).eq.stressFree).and.(bc(0,1).eq.stressFree))then
           do i2=n2a,n2a
           do i1=n1b,n1b
            rh1(i1,i2)=0.
            rh2(i1,i2)=0.
              ip=i1+1
              im=i1-1
              jp=i2+1
              jm=i2-1
              !       (2 muv+lambdav) uxx 
                Ep=lam2muv(ip,i2)+lam2muv(i1,i2)
                Em=lam2muv(im,i2)+lam2muv(i1,i2)
                rh1(i1,i2)=rh1(i1,i2)+0.5*dxi(0)**2*(Ep*(u1(ip,i2)-u1(
     & i1,i2))-Em*(u1(i1,i2)-u1(im,i2)))
              ! muv uyy 
                Ep=muv(i1,jp)+muv(i1,i2)
                Em=muv(i1,jm)+muv(i1,i2)
                rh1(i1,i2)=rh1(i1,i2)+0.5*dxi(1)**2*(Ep*(u1(i1,jp)-u1(
     & i1,i2))-Em*(u1(i1,i2)-u1(i1,jm)))
              ! muv vxx 	
                Ep=muv(ip,i2)+muv(i1,i2)
                Em=muv(im,i2)+muv(i1,i2)
                rh2(i1,i2)=rh2(i1,i2)+0.5*dxi(0)**2*(Ep*(u2(ip,i2)-u2(
     & i1,i2))-Em*(u2(i1,i2)-u2(im,i2)))
              ! (2 muv + lambdav) vyy 
                Ep=lam2muv(i1,jp)+lam2muv(i1,i2)
                Em=lam2muv(i1,jm)+lam2muv(i1,i2)
                rh2(i1,i2)=rh2(i1,i2)+0.5*dxi(1)**2*(Ep*(u2(i1,jp)-u2(
     & i1,i2))-Em*(u2(i1,i2)-u2(i1,jm)))
            ip=i1
            im=i1-1
            jp=i2+1
            jm=i2
              ! d_x lambdav v_y
                rh1(i1,i2)=rh1(i1,i2)+dc*(lambdav(ip,i2)*(u2(ip,jp)-u2(
     & ip,jm))-lambdav(im,i2)*(u2(im,jp)-u2(im,jm)))
              ! d_y muv v_x
                rh1(i1,i2)=rh1(i1,i2)+dc*(muv(i1,jp)*(u2(ip,jp)-u2(im,
     & jp))-muv(i1,jm)*(u2(ip,jm)-u2(im,jm)))
              ! d_x my u_y
                rh2(i1,i2)=rh2(i1,i2)+dc*(muv(ip,i2)*(u1(ip,jp)-u1(ip,
     & jm))-muv(im,i2)*(u1(im,jp)-u1(im,jm)))
              ! d_y lambdav u_x
                rh2(i1,i2)=rh2(i1,i2)+dc*(lambdav(i1,jp)*(u1(ip,jp)-u1(
     & im,jp))-lambdav(i1,jm)*(u1(ip,jm)-u1(im,jm)))
           enddo
           enddo
          endif
          if((bc(1,1).eq.stressFree).and.(bc(1,0).eq.stressFree))then
           do i2=n2b,n2b
           do i1=n1b,n1b
            rh1(i1,i2)=0.
            rh2(i1,i2)=0.
              ip=i1+1
              im=i1-1
              jp=i2+1
              jm=i2-1
              !       (2 muv+lambdav) uxx 
                Ep=lam2muv(ip,i2)+lam2muv(i1,i2)
                Em=lam2muv(im,i2)+lam2muv(i1,i2)
                rh1(i1,i2)=rh1(i1,i2)+0.5*dxi(0)**2*(Ep*(u1(ip,i2)-u1(
     & i1,i2))-Em*(u1(i1,i2)-u1(im,i2)))
              ! muv uyy 
                Ep=muv(i1,jp)+muv(i1,i2)
                Em=muv(i1,jm)+muv(i1,i2)
                rh1(i1,i2)=rh1(i1,i2)+0.5*dxi(1)**2*(Ep*(u1(i1,jp)-u1(
     & i1,i2))-Em*(u1(i1,i2)-u1(i1,jm)))
              ! muv vxx 	
                Ep=muv(ip,i2)+muv(i1,i2)
                Em=muv(im,i2)+muv(i1,i2)
                rh2(i1,i2)=rh2(i1,i2)+0.5*dxi(0)**2*(Ep*(u2(ip,i2)-u2(
     & i1,i2))-Em*(u2(i1,i2)-u2(im,i2)))
              ! (2 muv + lambdav) vyy 
                Ep=lam2muv(i1,jp)+lam2muv(i1,i2)
                Em=lam2muv(i1,jm)+lam2muv(i1,i2)
                rh2(i1,i2)=rh2(i1,i2)+0.5*dxi(1)**2*(Ep*(u2(i1,jp)-u2(
     & i1,i2))-Em*(u2(i1,i2)-u2(i1,jm)))
            ip=i1
            im=i1-1
            jp=i2
            jm=i2-1
              ! d_x lambdav v_y
                rh1(i1,i2)=rh1(i1,i2)+dc*(lambdav(ip,i2)*(u2(ip,jp)-u2(
     & ip,jm))-lambdav(im,i2)*(u2(im,jp)-u2(im,jm)))
              ! d_y muv v_x
                rh1(i1,i2)=rh1(i1,i2)+dc*(muv(i1,jp)*(u2(ip,jp)-u2(im,
     & jp))-muv(i1,jm)*(u2(ip,jm)-u2(im,jm)))
              ! d_x my u_y
                rh2(i1,i2)=rh2(i1,i2)+dc*(muv(ip,i2)*(u1(ip,jp)-u1(ip,
     & jm))-muv(im,i2)*(u1(im,jp)-u1(im,jm)))
              ! d_y lambdav u_x
                rh2(i1,i2)=rh2(i1,i2)+dc*(lambdav(i1,jp)*(u1(ip,jp)-u1(
     & im,jp))-lambdav(i1,jm)*(u1(ip,jm)-u1(im,jm)))
           enddo
           enddo
          endif
          !   --- Assign next time level ---
          do i2=n2a,n2b
          do i1=n1a,n1b
            dtsqByRho = dtsq/rhov(i1,i2)
            un(i1,i2,nd3a,uc)=cu*u(i1,i2,nd3a,uc)+cum*um(i1,i2,nd3a,uc)
     & +dtsqByRho*rh1(i1,i2)
            un(i1,i2,nd3a,vc)=cu*u(i1,i2,nd3a,vc)+cum*um(i1,i2,nd3a,vc)
     & +dtsqByRho*rh2(i1,i2)
          end do
          end do
        ! -- for testing : pass const materials 
        ! advanceSolutionMacro(rho,lam,mu,lam2mu)

      else

       ! --- Constant material properties ---
       ! write(*,'(" advSmCons: const mat. prop")') 

       l2m = (lambda0+2.*mu0)/rho0
       l = lambda0/rho0
       m = mu0/rho0
       lm = l+m
       dxidxi0 = dxi(0)*dxi(0)
       dxidxi1 = dxi(1)*dxi(1)
       dc=0.25*dxi(0)*dxi(1)   ! *wdh* 091201
       cofu(3,2) = dxidxi0*l2m
       cofu(1,2) = dxidxi0*l2m
       cofu(2,2) = -2.*dxidxi0*l2m-2.*dxidxi1*m
       cofu(2,1) = dxidxi1*m
       cofu(2,3) = dxidxi1*m
       cofu(1,1) = dc*lm
       cofu(3,3) = dc*lm
       cofu(3,1) = -dc*lm
       cofu(1,3) = -dc*lm
       cofv(3,2) = dxidxi0*m
       cofv(1,2) = dxidxi0*m
       cofv(2,2) = -2.*dxidxi1*l2m-2.*dxidxi0*m
       cofv(2,1) = dxidxi1*l2m
       cofv(2,3) = dxidxi1*l2m
       cofv(1,1) = dc*lm
       cofv(3,3) = dc*lm
       cofv(3,1) = -dc*lm
       cofv(1,3) = -dc*lm
!       initialize to zero
!       do the cross terms everywhere and overwrite if necessary
! *wdh* 091201        dc=0.25*dxi(0)*dxi(1)
        do i2=n2a,n2b
        do i1=n1a,n1b
        ip=i1+1
        im=i1-1
        jp=i2+1
        jm=i2-1
        rh1(i1,i2)=cofu(3,2)*u1(ip,i2)+cofu(2,2)*u1(i1,i2)+cofu(1,2)*
     & u1(im,i2)+cofu(2,3)*u1(i1,jp)+cofu(2,1)*u1(i1,jm)+cofu(3,3)*u2(
     & ip,jp)+cofu(3,1)*u2(ip,jm)+cofu(1,3)*u2(im,jp)+cofu(1,1)*u2(im,
     & jm)
        rh2(i1,i2)=cofv(3,2)*u2(ip,i2)+cofv(2,2)*u2(i1,i2)+cofv(1,2)*
     & u2(im,i2)+cofv(2,3)*u2(i1,jp)+cofv(2,1)*u2(i1,jm)+cofv(3,3)*u1(
     & ip,jp)+cofv(3,1)*u1(ip,jm)+cofv(1,3)*u1(im,jp)+cofv(1,1)*u1(im,
     & jm)
        end do
        end do
!       We correct the sides
        dc=0.5*dxi(0)*dxi(1)
        if( bc(0,0).eq.stressFree)then
         do i2=n2a,n2b
         do i1=n1a,n1a
          rh1(i1,i2)=0.
          rh2(i1,i2)=0.
            ip=i1+1
            im=i1-1
            jp=i2+1
            jm=i2-1
            ! (2 mu+lam) uxx + mu uyy
            rh1(i1,i2)=rh1(i1,i2)+dxidxi0*l2m*(u1(ip,i2)-2.*u1(i1,i2)+
     & u1(im,i2))+dxidxi1*m*(u1(i1,jp)-2.*u1(i1,i2)+u1(i1,jm))
            ! mu vxx + (2 mu + lam) vyy
            rh2(i1,i2)=rh2(i1,i2)+dxidxi0*m*(u2(ip,i2)-2.*u2(i1,i2)+u2(
     & im,i2))+dxidxi1*l2m*(u2(i1,jp)-2.*u2(i1,i2)+u2(i1,jm))
            ! write(*,'("ComputeRhsideNonCrossConst: i1,i2=",2i4," rh1,rh2=",2e12.2)') i1,i2,rh1(i1,i2),rh2(i1,i2)
          ip=i1+1
          im=i1 
          jp=i2+1 
          jm=i2-1
            ! d_x lam v_y + d_y mu v_x
            rh1(i1,i2)=rh1(i1,i2) + dc*lm*(u2(ip,jp)-u2(ip,jm)-u2(im,
     & jp)+u2(im,jm))
            ! d_x my u_y + d_y lam u_y
            rh2(i1,i2)=rh2(i1,i2) + dc*lm*(u1(ip,jp)-u1(ip,jm)-u1(im,
     & jp)+u1(im,jm))
            ! write(*,'("ComputeRhsideCrossConst: i1,i2=",2i4," rh1,rh2=",2e12.2)') i1,i2,rh1(i1,i2),rh2(i1,i2)
         enddo
         enddo
        endif
        if( bc(1,0).eq.stressFree) then ! correct edge
         do i2=n2a,n2b
         do i1=n1b,n1b
          rh1(i1,i2)=0.
          rh2(i1,i2)=0.
            ip=i1+1
            im=i1-1
            jp=i2+1
            jm=i2-1
            ! (2 mu+lam) uxx + mu uyy
            rh1(i1,i2)=rh1(i1,i2)+dxidxi0*l2m*(u1(ip,i2)-2.*u1(i1,i2)+
     & u1(im,i2))+dxidxi1*m*(u1(i1,jp)-2.*u1(i1,i2)+u1(i1,jm))
            ! mu vxx + (2 mu + lam) vyy
            rh2(i1,i2)=rh2(i1,i2)+dxidxi0*m*(u2(ip,i2)-2.*u2(i1,i2)+u2(
     & im,i2))+dxidxi1*l2m*(u2(i1,jp)-2.*u2(i1,i2)+u2(i1,jm))
            ! write(*,'("ComputeRhsideNonCrossConst: i1,i2=",2i4," rh1,rh2=",2e12.2)') i1,i2,rh1(i1,i2),rh2(i1,i2)
          ip=i1
          im=i1-1
          jp=i2+1 
          jm=i2-1
            ! d_x lam v_y + d_y mu v_x
            rh1(i1,i2)=rh1(i1,i2) + dc*lm*(u2(ip,jp)-u2(ip,jm)-u2(im,
     & jp)+u2(im,jm))
            ! d_x my u_y + d_y lam u_y
            rh2(i1,i2)=rh2(i1,i2) + dc*lm*(u1(ip,jp)-u1(ip,jm)-u1(im,
     & jp)+u1(im,jm))
            ! write(*,'("ComputeRhsideCrossConst: i1,i2=",2i4," rh1,rh2=",2e12.2)') i1,i2,rh1(i1,i2),rh2(i1,i2)
         enddo
         enddo
        endif
        if( bc(0,1).eq.stressFree) then ! correct edge
         do i2=n2a,n2a
         do i1=n1a,n1b
          rh1(i1,i2)=0.
          rh2(i1,i2)=0.
            ip=i1+1
            im=i1-1
            jp=i2+1
            jm=i2-1
            ! (2 mu+lam) uxx + mu uyy
            rh1(i1,i2)=rh1(i1,i2)+dxidxi0*l2m*(u1(ip,i2)-2.*u1(i1,i2)+
     & u1(im,i2))+dxidxi1*m*(u1(i1,jp)-2.*u1(i1,i2)+u1(i1,jm))
            ! mu vxx + (2 mu + lam) vyy
            rh2(i1,i2)=rh2(i1,i2)+dxidxi0*m*(u2(ip,i2)-2.*u2(i1,i2)+u2(
     & im,i2))+dxidxi1*l2m*(u2(i1,jp)-2.*u2(i1,i2)+u2(i1,jm))
            ! write(*,'("ComputeRhsideNonCrossConst: i1,i2=",2i4," rh1,rh2=",2e12.2)') i1,i2,rh1(i1,i2),rh2(i1,i2)
          ip=i1+1
          im=i1-1 
          jp=i2+1
          jm=i2 
            ! d_x lam v_y + d_y mu v_x
            rh1(i1,i2)=rh1(i1,i2) + dc*lm*(u2(ip,jp)-u2(ip,jm)-u2(im,
     & jp)+u2(im,jm))
            ! d_x my u_y + d_y lam u_y
            rh2(i1,i2)=rh2(i1,i2) + dc*lm*(u1(ip,jp)-u1(ip,jm)-u1(im,
     & jp)+u1(im,jm))
            ! write(*,'("ComputeRhsideCrossConst: i1,i2=",2i4," rh1,rh2=",2e12.2)') i1,i2,rh1(i1,i2),rh2(i1,i2)
         enddo
         enddo
        endif
        if( bc(1,1).eq.stressFree) then ! correct edge
        do i2=n2b,n2b
        do i1=n1a,n1b
         rh1(i1,i2)=0.
         rh2(i1,i2)=0.
           ip=i1+1
           im=i1-1
           jp=i2+1
           jm=i2-1
           ! (2 mu+lam) uxx + mu uyy
           rh1(i1,i2)=rh1(i1,i2)+dxidxi0*l2m*(u1(ip,i2)-2.*u1(i1,i2)+
     & u1(im,i2))+dxidxi1*m*(u1(i1,jp)-2.*u1(i1,i2)+u1(i1,jm))
           ! mu vxx + (2 mu + lam) vyy
           rh2(i1,i2)=rh2(i1,i2)+dxidxi0*m*(u2(ip,i2)-2.*u2(i1,i2)+u2(
     & im,i2))+dxidxi1*l2m*(u2(i1,jp)-2.*u2(i1,i2)+u2(i1,jm))
           ! write(*,'("ComputeRhsideNonCrossConst: i1,i2=",2i4," rh1,rh2=",2e12.2)') i1,i2,rh1(i1,i2),rh2(i1,i2)
         ip=i1+1
         im=i1-1
         jp=i2
         jm=i2-1
           ! d_x lam v_y + d_y mu v_x
           rh1(i1,i2)=rh1(i1,i2) + dc*lm*(u2(ip,jp)-u2(ip,jm)-u2(im,jp)
     & +u2(im,jm))
           ! d_x my u_y + d_y lam u_y
           rh2(i1,i2)=rh2(i1,i2) + dc*lm*(u1(ip,jp)-u1(ip,jm)-u1(im,jp)
     & +u1(im,jm))
           ! write(*,'("ComputeRhsideCrossConst: i1,i2=",2i4," rh1,rh2=",2e12.2)') i1,i2,rh1(i1,i2),rh2(i1,i2)
        enddo
        enddo
       endif
       ! Now correct the corners
       dc=dxi(0)*dxi(1)
       if((bc(0,0).eq.stressFree).and.(bc(0,1).eq.stressFree))then
        do i2=n2a,n2a
        do i1=n1a,n1a
         rh1(i1,i2)=0.
         rh2(i1,i2)=0.
           ip=i1+1
           im=i1-1
           jp=i2+1
           jm=i2-1
           ! (2 mu+lam) uxx + mu uyy
           rh1(i1,i2)=rh1(i1,i2)+dxidxi0*l2m*(u1(ip,i2)-2.*u1(i1,i2)+
     & u1(im,i2))+dxidxi1*m*(u1(i1,jp)-2.*u1(i1,i2)+u1(i1,jm))
           ! mu vxx + (2 mu + lam) vyy
           rh2(i1,i2)=rh2(i1,i2)+dxidxi0*m*(u2(ip,i2)-2.*u2(i1,i2)+u2(
     & im,i2))+dxidxi1*l2m*(u2(i1,jp)-2.*u2(i1,i2)+u2(i1,jm))
           ! write(*,'("ComputeRhsideNonCrossConst: i1,i2=",2i4," rh1,rh2=",2e12.2)') i1,i2,rh1(i1,i2),rh2(i1,i2)
         ip=i1+1 
         im=i1
         jp=i2+1
         jm=i2
           ! d_x lam v_y + d_y mu v_x
           rh1(i1,i2)=rh1(i1,i2) + dc*lm*(u2(ip,jp)-u2(ip,jm)-u2(im,jp)
     & +u2(im,jm))
           ! d_x my u_y + d_y lam u_y
           rh2(i1,i2)=rh2(i1,i2) + dc*lm*(u1(ip,jp)-u1(ip,jm)-u1(im,jp)
     & +u1(im,jm))
           ! write(*,'("ComputeRhsideCrossConst: i1,i2=",2i4," rh1,rh2=",2e12.2)') i1,i2,rh1(i1,i2),rh2(i1,i2)
        enddo
        enddo
       endif
       if((bc(0,0).eq.stressFree).and.(bc(1,1).eq.stressFree))then
        do i2=n2b,n2b
        do i1=n1a,n1a
         rh1(i1,i2)=0.
         rh2(i1,i2)=0.
           ip=i1+1
           im=i1-1
           jp=i2+1
           jm=i2-1
           ! (2 mu+lam) uxx + mu uyy
           rh1(i1,i2)=rh1(i1,i2)+dxidxi0*l2m*(u1(ip,i2)-2.*u1(i1,i2)+
     & u1(im,i2))+dxidxi1*m*(u1(i1,jp)-2.*u1(i1,i2)+u1(i1,jm))
           ! mu vxx + (2 mu + lam) vyy
           rh2(i1,i2)=rh2(i1,i2)+dxidxi0*m*(u2(ip,i2)-2.*u2(i1,i2)+u2(
     & im,i2))+dxidxi1*l2m*(u2(i1,jp)-2.*u2(i1,i2)+u2(i1,jm))
           ! write(*,'("ComputeRhsideNonCrossConst: i1,i2=",2i4," rh1,rh2=",2e12.2)') i1,i2,rh1(i1,i2),rh2(i1,i2)
         ip=i1+1
         im=i1
         jp=i2
         jm=i2-1
           ! d_x lam v_y + d_y mu v_x
           rh1(i1,i2)=rh1(i1,i2) + dc*lm*(u2(ip,jp)-u2(ip,jm)-u2(im,jp)
     & +u2(im,jm))
           ! d_x my u_y + d_y lam u_y
           rh2(i1,i2)=rh2(i1,i2) + dc*lm*(u1(ip,jp)-u1(ip,jm)-u1(im,jp)
     & +u1(im,jm))
           ! write(*,'("ComputeRhsideCrossConst: i1,i2=",2i4," rh1,rh2=",2e12.2)') i1,i2,rh1(i1,i2),rh2(i1,i2)
        enddo
        enddo
       endif
       if((bc(1,0).eq.stressFree).and.(bc(0,1).eq.stressFree))then
        do i2=n2a,n2a
        do i1=n1b,n1b
         rh1(i1,i2)=0.
         rh2(i1,i2)=0.
           ip=i1+1
           im=i1-1
           jp=i2+1
           jm=i2-1
           ! (2 mu+lam) uxx + mu uyy
           rh1(i1,i2)=rh1(i1,i2)+dxidxi0*l2m*(u1(ip,i2)-2.*u1(i1,i2)+
     & u1(im,i2))+dxidxi1*m*(u1(i1,jp)-2.*u1(i1,i2)+u1(i1,jm))
           ! mu vxx + (2 mu + lam) vyy
           rh2(i1,i2)=rh2(i1,i2)+dxidxi0*m*(u2(ip,i2)-2.*u2(i1,i2)+u2(
     & im,i2))+dxidxi1*l2m*(u2(i1,jp)-2.*u2(i1,i2)+u2(i1,jm))
           ! write(*,'("ComputeRhsideNonCrossConst: i1,i2=",2i4," rh1,rh2=",2e12.2)') i1,i2,rh1(i1,i2),rh2(i1,i2)
         ip=i1
         im=i1-1
         jp=i2+1
         jm=i2
           ! d_x lam v_y + d_y mu v_x
           rh1(i1,i2)=rh1(i1,i2) + dc*lm*(u2(ip,jp)-u2(ip,jm)-u2(im,jp)
     & +u2(im,jm))
           ! d_x my u_y + d_y lam u_y
           rh2(i1,i2)=rh2(i1,i2) + dc*lm*(u1(ip,jp)-u1(ip,jm)-u1(im,jp)
     & +u1(im,jm))
           ! write(*,'("ComputeRhsideCrossConst: i1,i2=",2i4," rh1,rh2=",2e12.2)') i1,i2,rh1(i1,i2),rh2(i1,i2)
        enddo
        enddo
       endif
       if((bc(1,1).eq.stressFree).and.(bc(1,0).eq.stressFree))then
        do i2=n2b,n2b
        do i1=n1b,n1b
         rh1(i1,i2)=0.
         rh2(i1,i2)=0.
           ip=i1+1
           im=i1-1
           jp=i2+1
           jm=i2-1
           ! (2 mu+lam) uxx + mu uyy
           rh1(i1,i2)=rh1(i1,i2)+dxidxi0*l2m*(u1(ip,i2)-2.*u1(i1,i2)+
     & u1(im,i2))+dxidxi1*m*(u1(i1,jp)-2.*u1(i1,i2)+u1(i1,jm))
           ! mu vxx + (2 mu + lam) vyy
           rh2(i1,i2)=rh2(i1,i2)+dxidxi0*m*(u2(ip,i2)-2.*u2(i1,i2)+u2(
     & im,i2))+dxidxi1*l2m*(u2(i1,jp)-2.*u2(i1,i2)+u2(i1,jm))
           ! write(*,'("ComputeRhsideNonCrossConst: i1,i2=",2i4," rh1,rh2=",2e12.2)') i1,i2,rh1(i1,i2),rh2(i1,i2)
         ip=i1
         im=i1-1
         jp=i2
         jm=i2-1
           ! d_x lam v_y + d_y mu v_x
           rh1(i1,i2)=rh1(i1,i2) + dc*lm*(u2(ip,jp)-u2(ip,jm)-u2(im,jp)
     & +u2(im,jm))
           ! d_x my u_y + d_y lam u_y
           rh2(i1,i2)=rh2(i1,i2) + dc*lm*(u1(ip,jp)-u1(ip,jm)-u1(im,jp)
     & +u1(im,jm))
           ! write(*,'("ComputeRhsideCrossConst: i1,i2=",2i4," rh1,rh2=",2e12.2)') i1,i2,rh1(i1,i2),rh2(i1,i2)
        enddo
        enddo
       endif

       !   --- Assign next time level ---
       ! write(*,'(" l,m,l2m=",3e12.2)') l,m,l2m
       do i2=n2a,n2b
       do i1=n1a,n1b
         ! write(*,'(" i1,i2=",2i4," rh1,rh2=",2e12.2)') i1,i2,rh1(i1,i2),rh2(i1,i2)
         un(i1,i2,nd3a,uc)=cu*u(i1,i2,nd3a,uc)+cum*um(i1,i2,nd3a,uc)+
     & dtsq*rh1(i1,i2)
         un(i1,i2,nd3a,vc)=cu*u(i1,i2,nd3a,vc)+cum*um(i1,i2,nd3a,vc)+
     & dtsq*rh2(i1,i2)
       end do
       end do

      endif  ! end if constant material parameters




      ! ---  Add on forcing ---
      if(addForcing.ne.0) then
       do i2=n2a,n2b
       do i1=n1a,n1b
         un(i1,i2,nd3a,uc)=un(i1,i2,nd3a,uc)+dtsq*f(i1,i2,nd3a,uc)
         un(i1,i2,nd3a,vc)=un(i1,i2,nd3a,vc)+dtsq*f(i1,i2,nd3a,vc)
       end do
       end do
      end if

      ! ---- Add artificial dissipation ----
      if( (orderOfDissipation.eq.4 ).and.(adc.gt.0))then
       adcdt=adc*dt
       do i2=n2a,n2b
       do i1=n1a,n1b
        un(i1,i2,nd3a,uc)=un(i1,i2,nd3a,uc)+adcdt*fd42d(i1,i2,nd3a,uc)
        end do
        end do
      end if
      if( (orderOfDissipation.eq.2 ).and.(adc.gt.0))then
       adcdt=adc*dt
       do i2=n2a,n2b
       do i1=n1a,n1b
        un(i1,i2,nd3a,uc)=un(i1,i2,nd3a,uc)+adcdt*fd22d(i1,i2,nd3a,uc)
        end do
        end do
      end if

      if(debug.eq.3) then 
       ! --- compute the energy ---
       energy=0.
       do i2=n2a,n2b
       do i1=n1a,n1b
             weight=1.
       if ((i1.eq.n1a).and.((bc(0,0).eq.stressFree))) weight=weight*0.5
       if ((i1.eq.n1b).and.((bc(0,1).eq.stressFree))) weight=weight*0.5
       if ((i2.eq.n2a).and.((bc(1,0).eq.stressFree))) weight=weight*0.5
      if ((i2.eq.n2b).and.((bc(1,1).eq.stressFree))) weight=weight*0.5
      energy=energy-weight*un(i1,i2,nd3a,uc)*rh1(i1,i2)
      energy=energy-weight*un(i1,i2,nd3a,vc)*rh2(i1,i2)
	!       we use rh to store u_t
        rh1(i1,i2)=(un(i1,i2,nd3a,uc)-u(i1,i2,nd3a,uc))/dt
        rh2(i1,i2)=(un(i1,i2,nd3a,vc)-u(i1,i2,nd3a,vc))/dt
      energy=energy+weight*rh1(i1,i2)*rh1(i1,i2)
      energy=energy+weight*rh2(i1,i2)*rh2(i1,i2)
       end do
       end do
       write(*,*) "Discrete energy ",energy
      end if


      ! *wdh end subroutine 
      end

