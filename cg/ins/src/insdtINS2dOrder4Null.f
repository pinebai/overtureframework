! This file automatically generated from insdtINS.bf with bpp.
        subroutine insdtINS2dOrder4(nd,n1a,n1b,n2a,n2b,n3a,n3b,nd1a,
     & nd1b,nd2a,nd2b,nd3a,nd3b,nd4a,nd4b,mask,xy,rsxy,radiusInverse, 
     &  u,uu, ut,uti,gv,dw,  bc, ipar, rpar, ierr )
c======================================================================
c       EMPTY VERSION for Linking without this Capability
c
c   Compute du/dt for the incompressible NS on rectangular grids
c     OPTIMIZED version for rectangular grids.
c nd : number of space dimensions
c
c gv : gridVelocity for moving grids
c uu : for moving grids uu is a workspace to hold u-gv, otherwise uu==u
c dw : distance to the wall for some turbulence models
c======================================================================
        implicit none
        integer nd, n1a,n1b,n2a,n2b,n3a,n3b,nd1a,nd1b,nd2a,nd2b,nd3a,
     & nd3b,nd4a,nd4b
        real u(nd1a:nd1b,nd2a:nd2b,nd3a:nd3b,nd4a:nd4b)
        real uu(nd1a:nd1b,nd2a:nd2b,nd3a:nd3b,nd4a:nd4b)
        real ut(nd1a:nd1b,nd2a:nd2b,nd3a:nd3b,nd4a:nd4b)
        real uti(nd1a:nd1b,nd2a:nd2b,nd3a:nd3b,nd4a:nd4b)
        real gv(nd1a:nd1b,nd2a:nd2b,nd3a:nd3b,0:nd-1)
        real dw(nd1a:nd1b,nd2a:nd2b,nd3a:nd3b)
        real xy(nd1a:nd1b,nd2a:nd2b,nd3a:nd3b,0:nd-1)
        real rsxy(nd1a:nd1b,nd2a:nd2b,nd3a:nd3b,0:nd-1,0:nd-1)
        real radiusInverse(nd1a:nd1b,nd2a:nd2b,nd3a:nd3b)
        integer mask(nd1a:nd1b,nd2a:nd2b,nd3a:nd3b)
        integer bc(0:1,0:2),ierr
        integer ipar(0:*)
        real rpar(0:*)
        write(*,'("ERROR: NULL version of subroutine insdtINS2dOrder4 
     & called")')
        write(*,'(" You may have to turn on an option in the 
     & Makefile.")')
        stop 1080
        return
        end
