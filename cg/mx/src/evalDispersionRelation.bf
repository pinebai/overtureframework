! =====================================================================================================
! 
! -----------------------------------------------------------------------------------
! Evaluate the dispersion relation for the generalized dispersion model (GDM)
!  With multiple polarization vectors 
! -----------------------------------------------------------------------------------
!
!       E_tt - c^2 Delta(E) = -alphaP P_tt
!       P_tt + b1 P_1 + b0 = a0*E + a1*E_t 
!
!  Input:
!      mode : mode to choose, i.e. which root to choose. If mode=-1 then the default root is chosen.
!                The default root is the one with largest NEGATIVE imaginary part.
!      Np : number of polarization vectors  
!      c,k, 
!      a0(0:Np-1), a1(0:Np-1), b0(0:Np-1), b1(0:Np-1), alphaP : GDM parameters
! Output:
!      sr(0:nEig-1),si(0:nEig-1) : real and imaginary part of eigenvalues: nEig = 2*NpP+2 
!      srm, sim : eigenvalue with largest imaginary part 
!      psir(0:Np-1),psii(0:Np-1) : real and imaginary parts of psi : P = psi*E for s=(srm,sim) 
!
! =====================================================================================================
      subroutine evalEigGDM( mode, Np, c,k, a0,a1,b0,b1,alphaP, sr,si, srm,sim,psir,psii )

      implicit none

      integer mode, Np
      real c,k, srm,sim
      real a0(0:*),a1(0:*),b0(0:*),b1(0:*),alphaP, psir(0:*),psii(0:*)
      real sr(0:*),si(0:*)

      ! local variables 
      real ck,ck2, eps
      integer nd,lda, lwork, i, iMode, j  
      ! lwork>= 3*lda : for good performance lwork must generally be larger
      parameter( lda=10, lwork=10*lda )
      real a(0:lda-1,0:lda-1), work(lwork), vr(1), vl(1)
      integer info 

      complex*16 s, psi 

      ck=c*k
      ck2=ck**2 
      if( Np .eq. 1 )then 
        ! Companion matrix for GDM model Np=1, File written by CG/DMX/matlab/gdm.maple
#Include "generalizedDispersionModelCompanionMatrix1.h"
      else if( Np .eq. 2 )then
#Include "generalizedDispersionModelCompanionMatrix2.h"
      else if( Np .eq. 3 )then
#Include "generalizedDispersionModelCompanionMatrix3.h"
      else
        stop 1234
      end if

      nd = 2*Np+2 ! order of the matrix
      
      ! Compute eigenvalues of a general non-symtreic matrix 
      call dgeev( 'N','N',nd,a,lda,sr,si,vl,1,vr,1,work,lwork,info )
      write(*,'("evalEigGDM: return from dgeev: info=",i8)') info 

      if( .true. )then
          write(*,'(" evalEigGDM: input: mode=",i6)') mode
        do i=0,nd-1
          write(*,'(" evalEigGDM: i=",i3," s=(",1P,e20.12,",", 1P,e20.12,")")') i,sr(i),si(i)    
       end do
      end if
      if( mode.ge.0 )then
       ! Take user supplied mode: 
       iMode=min(mode,nd-1)
      else
        ! choose s with largest NEGATIVE imaginary part
        iMode=0
        sim=si(iMode) 
        do i=0,nd-1
          if( si(i) .lt. sim )then
            iMode=i
           sim=si(i)
          end if
        end do
      end if
      sim=si(iMode) 
      srm=sr(iMode) 


      ! P = psi(s)*E
      eps=1.e-14 ! FIX ME 
      do j=0,Np-1
        s = cmplx(srm,sim)
        if( abs(real(s)) + abs(imag(s)) .gt.eps )then
          psi = (a0(j)+a1(j)*s)/(s**2+b1(j)*s+b0(j))
        else
          psi=0.
        end if

        psir(j) = real(psi)
        psii(j) = imag(psi)  
      end do 

      call flush(6)

      return
      end  




! =====================================================================================================
! 
! -----------------------------------------------------------------------------------
! Evaluate the "INVERSE" dispersion relation (compute k=*(kr,ki) given s=(sr,si) 
! for the generalized dispersion model (GDM) With multiple polarization vectors 
! -----------------------------------------------------------------------------------
!
!       E_tt - c^2 Delta(E) = -alphaP P_tt
!       P_tt + b1 P_1 + b0 = a0*E + a1*E_t 
!
!  Input:
!      sr,si : s=(sr,si)
!      Np : number of polarization vectors  
!      c  : 
!      a0(0:Np-1), a1(0:Np-1), b0(0:Np-1), b1(0:Np-1), alphaP : GDM parameters
! Output:
!      kr,ki : k=(kr,ki) = complex wave number 
!      psir(0:Np-1),psii(0:Np-1) : real and imaginary parts of psi : P = psi*E for s=(srm,sim) 
!
! =====================================================================================================
      subroutine evalInverseGDM( c, sr,si, Np, a0,a1,b0,b1,alphaP, kr,ki,psir,psii )

      implicit none

      real c,sr,si
      integer Np
      real a0(0:*),a1(0:*),b0(0:*),b1(0:*),alphaP, psir(0:*),psii(0:*)
      real kr,ki

      ! local variables 
      real eps
      integer j
      complex*16 s, psi, sum , k

      s=cmplx(sr,si)

      sum = 0.
      do j=0,Np-1
        ! Phat = psi(s) * Ehat
        psi = (a0(j)+a1(j)*s)/(s**2+b1(j)*s+b0(j))
        psir(j) = real(psi)
        psii(j) = imag(psi)  

        sum =sum + psi
      end do 
  
      ! (ck)^2 = -s^2 - alphaP* s^2 *sum_k{ psi_k(s) }
      k = csqrt(-s*s -alphaP*s*s*( sum ) )/c 

      kr = real(k)
      ki = imag(k)

      return
      end  










! -----------------------------------------------------------------------------------
! Evaluate the dispersion relation for the generalized dispersion model (GDM)
! -----------------------------------------------------------------------------------
!
!       E_tt - c^2 Delta(E) = -alphaP P_tt
!       P_tt + b1 P_1 + b0 = a0*E + a1*E_t 
!
!  Input:
!      c,k, a0,a1,b0,b1,alphaP
! Output:
!      sr,si : real and imaginary part of s
!      psir,psii : real and imaginary parts of psi : P = psi*E 
!
      subroutine evalGeneralizedDispersionRelation( c,k, a0,a1,b0,b1,alphaP, sr,si, psir,psii )


      ! implicit none
      implicit complex*16 (t)

      real c,k, a0,a1,b0,b1,alphaP, psir,psii
      real ck,ck2,  f ,ap, cki,ck2i 
      real sr,si
      complex*16 ai, ss,s,cComplex, psi

      ! cComplex = dcmplx(c,0.) ! convert c to complex to force complex arithmetic below
      ck=c*k
      ck2=ck*ck
      cki=1/ck
      ck2i=1./ck2 

      ap=alphaP
 
! File generated by overtureFramework/cg/mx/codes/gdm.maple

#Include "generalizedDispersionRelation1.h"

      ! The valid root will have an imaginary part close to I*ck 
      if( abs(dimag(ss)) < .01*ck )then
#Include "generalizedDispersionRelation3.h"     
        write(*,'("evalGDM: Use root 3")')
        if( abs(dimag(ss)) < .01*ck )then
          write(*,'("evalGDM: INVALID root found!?")')
          stop 6666
        end if
      else
        write(*,'("evalGDM: Use root 1")')
      end if

      s =ss*ck

      if( dimag(s)>0. )then
        s=dconjg(s) ! choose right moving wave, imag(s) < 0 
      end if 

      sr= dreal(s)
      si= dimag(s)

      ! P = psi(s)*E
      psi = (a0+a1*s)/(s**2+b1*s+b0)
      psir = dreal(psi)
      psii = dimag(psi)  ! NOTE: CHOOSE RIGHT MOVING WAVE

      ! check root:
      f = cabs((ss**2 + 1)*(ss**2 + cki*b1*ss+ck2i*b0) + ap*ss**2*cki*( a1*ss+ cki*a0 ) )

      write(*,'("evalGDM: c,k,a0,a1,b0,b1=",6(1P,e20.12)," alphaP=",1Pe20.12)') c,k,a0,a1,b0,b1,alphaP
      write(*,'("evalGDM: sr,si=",2(1P,e24.15)," |f|=",e12.4)') sr,si,f
      write(*,'("evalGDM: psir,psii=",2e12.4)') psir,psii


      return
      end   


! Evaluate the dispersion relation for the Drude model 
!
!    E_tt + c^2 k^2 E = -alphaP*P_tt
!
!  Input:
!      c0,eps,gam,omegap,k : 
! Output:
!      reS,imS
!
      subroutine evalDispersionRelation( c0,eps,gam,omegap,k, reS,imS )


      implicit none

      real c0,eps,gam,omegap,k, ck2, epsi, om2, det
      real reS,imS
      complex*16 ai, c, s

      ck2=(c0*k)**2
      epsi=1./eps
      om2=omegap**2

       ! ai=cmplx(0.,1.)  ! i 
       c = cmplx(c0,0.) ! convert c to complex to force complex arithmetic below
! File generated by overtureFramework/cg/mx/codes/dispersion.maple
! Here is root 3 from the dispersion relation exp( i*k*x + s*t) .
! s = -1/12*(36*epsi*gam*om2-72*ck2*gam-8*gam^3+12*(12*epsi^3*om2^3-3*epsi^2*gam^2*om2^2+36*ck2*epsi^2*om2^2-60*ck2*epsi*gam^2*om2+12*ck2*gam^4+36*ck2^2*epsi*om2+24*ck2^2*gam^2+12*ck2^3)^(1/2))^(1/3)+3*(1/3*epsi*om2+1/3*ck2-1/9*gam^2)/(36*epsi*gam*om2-72*ck2*gam-8*gam^3+12*(12*epsi^3*om2^3-3*epsi^2*gam^2*om2^2+36*ck2*epsi^2*om2^2-60*ck2*epsi*gam^2*om2+12*ck2*gam^4+36*ck2^2*epsi*om2+24*ck2^2*gam^2+12*ck2^3)^(1/2))^(1/3)-1/3*gam+1/2*I*3^(1/2)*(1/6*(36*epsi*gam*om2-72*ck2*gam-8*gam^3+12*(12*epsi^3*om2^3-3*epsi^2*gam^2*om2^2+36*ck2*epsi^2*om2^2-60*ck2*epsi*gam^2*om2+12*ck2*gam^4+36*ck2^2*epsi*om2+24*ck2^2*gam^2+12*ck2^3)^(1/2))^(1/3)+6*(1/3*epsi*om2+1/3*ck2-1/9*gam^2)/(36*epsi*gam*om2-72*ck2*gam-8*gam^3+12*(12*epsi^3*om2^3-3*epsi^2*gam^2*om2^2+36*ck2*epsi^2*om2^2-60*ck2*epsi*gam^2*om2+12*ck2*gam^4+36*ck2^2*epsi*om2+24*ck2^2*gam^2+12*ck2^3)^(1/2))^(1/3))
      s = -(((36*epsi*gam*om2)-(72*ck2*gam)-(8*gam ** 3)+12.*sqrt((12*epsi ** 3*om2 ** 3-3*epsi ** 2*om2 ** 2*gam ** 2+36*epsi ** 2*om2 ** 2*ck2-60*epsi*om2*ck2*gam ** 2+12*ck2*gam ** 4+36*epsi*om2*ck2 ** 2+24*ck2 ** 2*gam ** 2+12*ck2 ** 3))) ** (1./3.)/12.)+(3.*((epsi*om2)/3.+(ck2)/3.-(gam ** 2)/0.9E1)*((36*epsi*gam*om2)-(72*ck2*gam)-(8*gam ** 3)+12.*sqrt((12*epsi ** 3*om2 ** 3-3*epsi ** 2*om2 ** 2*gam ** 2+36*epsi ** 2*om2 ** 2*ck2-60*epsi*om2*ck2*gam ** 2+12*ck2*gam ** 4+36*epsi*om2*ck2 ** 2+24*ck2 ** 2*gam ** 2+12*ck2 ** 3))) ** (-1./3.))-((gam)/3.)+cmplx(0, 1./2.)*sqrt(3.)*(((36*epsi*gam*om2)-(72*ck2*gam)-(8*gam ** 3)+12.*sqrt((12*epsi ** 3*om2 ** 3-3*epsi ** 2*om2 ** 2*gam ** 2+36*epsi ** 2*om2 ** 2*ck2-60*epsi*om2*ck2*gam ** 2+12*ck2*gam ** 4+36*epsi*om2*ck2 ** 2+24*ck2 ** 2*gam ** 2+12*ck2 ** 3))) ** (1./3.)/6.+6.*((epsi*om2)/3.+(ck2)/3.-(gam ** 2)/0.9E1)*((36*epsi*gam*om2)-(72*ck2*gam)-(8*gam ** 3)+12.*sqrt((12*epsi ** 3*om2 ** 3-3*epsi ** 2*om2 ** 2*gam ** 2+36*epsi ** 2*om2 ** 2*ck2-60*epsi*om2*ck2*gam ** 2+12*ck2*gam ** 4+36*epsi*om2*ck2 ** 2+24*ck2 ** 2*gam ** 2+12*ck2 ** 3))) ** (-1./3.))

      reS= real(s)
      imS= aimag(s)

      ! check root:
      det = cabs((s**2 + ck2)*(s**2 + gam*s) + om2*s**2*epsi)
      write(*,'("*OLD* evalDisp: eps,omegap=",2e12.4," gam,k=",2e12.4," |det|=",e12.4)') eps,omegap,gam,k,det
      write(*,'("*OLD* evalDisp: reS,imS=",2(1P,e22.15))') reS,imS
      return
      end   



