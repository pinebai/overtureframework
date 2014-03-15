

! ************ Results from bc43d.maple *******************


! ************ solution using extrapolation for a1.u *******************
      gIII1=-tau11*(c22*uss+c2*us+c33*utt+c3*ut)-tau12*(c22*vss+c2*vs+c33*vtt+c3*vt)-tau13*(c22*wss+c2*ws+c33*wtt+c3*wt)

      gIII2=-tau21*(c22*uss+c2*us+c33*utt+c3*ut)-tau22*(c22*vss+c2*vs+c33*vtt+c3*vt)-tau23*(c22*wss+c2*ws+c33*wtt+c3*wt)

      tau1U=tau11*u(i1,i2,i3,ex)+tau12*u(i1,i2,i3,ey)+tau13*u(i1,i2,i3,ez)

      tau1Up1=tau11*u(i1+is1,i2+is2,i3+is3,ex)+tau12*u(i1+is1,i2+is2,i3+is3,ey)+tau13*u(i1+is1,i2+is2,i3+is3,ez)

      tau1Up2=tau11*u(i1+2*is1,i2+2*is2,i3+2*is3,ex)+tau12*u(i1+2*is1,i2+2*is2,i3+2*is3,ey)+tau13*u(i1+2*is1,i2+2*is2,i3+2*is3,ez)

      tau1Up3=tau11*u(i1+3*is1,i2+3*is2,i3+3*is3,ex)+tau12*u(i1+3*is1,i2+3*is2,i3+3*is3,ey)+tau13*u(i1+3*is1,i2+3*is2,i3+3*is3,ez)

      tau2U=tau21*u(i1,i2,i3,ex)+tau22*u(i1,i2,i3,ey)+tau23*u(i1,i2,i3,ez)

      tau2Up1=tau21*u(i1+is1,i2+is2,i3+is3,ex)+tau22*u(i1+is1,i2+is2,i3+is3,ey)+tau23*u(i1+is1,i2+is2,i3+is3,ez)

      tau2Up2=tau21*u(i1+2*is1,i2+2*is2,i3+2*is3,ex)+tau22*u(i1+2*is1,i2+2*is2,i3+2*is3,ey)+tau23*u(i1+2*is1,i2+2*is2,i3+2*is3,ez)

      tau2Up3=tau21*u(i1+3*is1,i2+3*is2,i3+3*is3,ex)+tau22*u(i1+3*is1,i2+3*is2,i3+3*is3,ey)+tau23*u(i1+3*is1,i2+3*is2,i3+3*is3,ez)

! tau1.D+^p u = 0
      gIV1=-10*tau1U+10*tau1Up1-5*tau1Up2+tau1Up3 +gIVf1

! tau2.D+^p u = 0
      gIV2=-10*tau2U+10*tau2Up1-5*tau2Up2+tau2Up3 +gIVf2


! ttu11 = tau1.u(-1), ttu12 = tau1.u(-2)
      ttu11=-(-12*c11*tau1Up1+24*c11*tau1U+c11*ctlrr*tau1Up2-4*c11*ctlrr*tau1Up1+6*c11*ctlrr*tau1U+c11*ctlrr*gIV1-6*c1*dra*tau1Up1+c1*dra*ctlr*tau1Up2-2*c1*dra*ctlr*tau1Up1-c1*dra*ctlr*gIV1+12*gIII1*dra**2+12*tau1DotUtt*dra**2)/(-12*c11+c11*ctlrr+6*c1*dra-3*c1*dra*ctlr)
      ttu12=-(-60*c11*tau1Up1+120*c11*tau1U+5*c11*ctlrr*tau1Up2-20*c11*ctlrr*tau1Up1+30*c11*ctlrr*tau1U+4*c11*ctlrr*gIV1-30*c1*dra*tau1Up1+5*c1*dra*ctlr*tau1Up2-10*c1*dra*ctlr*tau1Up1-2*c1*dra*ctlr*gIV1+60*gIII1*dra**2+60*tau1DotUtt*dra**2+12*c11*gIV1-6*gIV1*c1*dra)/(-12*c11+c11*ctlrr+6*c1*dra-3*c1*dra*ctlr)

! ttu21 = tau2.u(-1), ttu22 = tau2.u(-2)
      ttu21=-(-12*c11*tau2Up1+24*c11*tau2U+c11*ctlrr*tau2Up2-4*c11*ctlrr*tau2Up1+6*c11*ctlrr*tau2U+c11*ctlrr*gIV2-6*c1*dra*tau2Up1+c1*dra*ctlr*tau2Up2-2*c1*dra*ctlr*tau2Up1-c1*dra*ctlr*gIV2+12*gIII2*dra**2+12*tau2DotUtt*dra**2)/(-12*c11+c11*ctlrr+6*c1*dra-3*c1*dra*ctlr)
      ttu22=-(-60*c11*tau2Up1+120*c11*tau2U+5*c11*ctlrr*tau2Up2-20*c11*ctlrr*tau2Up1+30*c11*ctlrr*tau2U+4*c11*ctlrr*gIV2-30*c1*dra*tau2Up1+5*c1*dra*ctlr*tau2Up2-10*c1*dra*ctlr*tau2Up1-2*c1*dra*ctlr*gIV2+60*gIII2*dra**2+60*tau2DotUtt*dra**2+12*c11*gIV2-6*gIV2*c1*dra)/(-12*c11+c11*ctlrr+6*c1*dra-3*c1*dra*ctlr)

      ! *********** set tangential components to be exact *****
      ! OGF3D(i1-is1,i2-is2,i3-is3,t, uvm(0),uvm(1),uvm(2))
      ! ttu11=tau11*uvm(0)+tau12*uvm(1)+tau13*uvm(2)
      ! ttu21=tau21*uvm(0)+tau22*uvm(1)+tau23*uvm(2)
      ! OGF3D(i1-2*is1,i2-2*is2,i3-2*is3,t, uvm(0),uvm(1),uvm(2))
      ! ttu12=tau11*uvm(0)+tau12*uvm(1)+tau13*uvm(2)
      ! ttu22=tau21*uvm(0)+tau22*uvm(1)+tau23*uvm(2)
      ! ******************************************************

      f1f  =a11*(15.*u(i1,i2,i3,ex)-20.*u(i1+is1,i2+is2,i3+is3,ex)+15.*u(i1+2*is1,i2+2*is2,i3+2*is3,ex)-6.*u(i1+3*is1,i2+3*is2,i3+3*is3,ex)+u(i1+4*is1,i2+4*is2,i3+4*is3,ex))+a12*(15.*u(i1,i2,i3,ey)-20.*u(i1+is1,i2+is2,i3+is3,ey)+15.*u(i1+2*is1,i2+2*is2,i3+2*is3,ey)-6.*u(i1+3*is1,i2+3*is2,i3+3*is3,ey)+u(i1+4*is1,i2+4*is2,i3+4*is3,ey))+a13*(15.*u(i1,i2,i3,ez)-20.*u(i1+is1,i2+is2,i3+is3,ez)+15.*u(i1+2*is1,i2+2*is2,i3+2*is3,ez)-6.*u(i1+3*is1,i2+3*is2,i3+3*is3,ez)+u(i1+4*is1,i2+4*is2,i3+4*is3,ez))

      f2um2=1/12.*a11m2
      f2um1=-2/3.*a11m1
      f2vm2=1/12.*a12m2
      f2vm1=-2/3.*a12m1
      f2wm2=1/12.*a13m2
      f2wm1=-2/3.*a13m1
      f2f  =2/3.*a11p1*u(i1+is1,i2+is2,i3+is3,ex)+2/3.*a12p1*u(i1+is1,i2+is2,i3+is3,ey)+2/3.*a13p1*u(i1+is1,i2+is2,i3+is3,ez)-1/12.*a11p2*u(i1+2*is1,i2+2*is2,i3+2*is3,ex)-1/12.*a12p2*u(i1+2*is1,i2+2*is2,i3+2*is3,ey)-1/12.*a13p2*u(i1+2*is1,i2+2*is2,i3+2*is3,ez)-Da1DotU*dra

      u(i1-is1,i2-is2,i3-is3,ez) = -1.*(tau21*f1f*f2um2*tau23*tau12**2-1.*tau12*tau22*tau13*tau21*f1f*f2um2+f1f*tau22*f2vm2*tau23*tau11**2-1.*f1f*tau22**2*f2wm2*tau11**2+tau11*tau13*f1f*tau22**2*f2um2-1.*tau11*f1f*tau23*tau12*f2vm2*tau21-1.*tau11*tau13*f1f*tau22*f2vm2*tau21-1.*tau11*f1f*tau22*f2um2*tau23*tau12+2.*tau11*f1f*tau22*f2wm2*tau12*tau21+tau12*tau13*tau21**2*f1f*f2vm2-1.*tau21**2*f1f*f2wm2*tau12**2+ttu12*f2vm2*tau21**2*a13*tau12-1.*ttu12*f2vm2*tau21*tau23*a11*tau12-1.*ttu12*tau22*f2vm2*tau21*a13*tau11+ttu12*tau22**2*f2um2*a13*tau11-1.*ttu12*tau22*f2um2*a13*tau21*tau12-1.*ttu12*tau22*f2um2*tau23*a12*tau11+f2um1*ttu21*tau21*tau12**2*a13+tau21**2*f2f*tau12**2*a13+f2um2*a13*tau12**2*tau21*ttu22-1.*tau12*tau22*tau21*a13*ttu11*f2um1-1.*tau21*f2f*tau23*tau12**2*a11-1.*tau12*tau21*a13*ttu21*tau11*f2vm1-1.*tau12*tau21*tau23*a11*ttu11*f2vm1-1.*tau12*tau22*ttu22*f2um2*a13*tau11-1.*tau12*tau13*f2um1*ttu21*tau21*a12-1.*tau12*tau13*f2um2*a12*tau21*ttu22+tau12*tau21**2*a13*ttu11*f2vm1+tau12*tau22*tau13*tau21*f2f*a11-1.*tau12*tau13*tau21**2*f2f*a12+tau11*a13*ttu11*tau22**2*f2um1-1.*tau11*tau13*tau22*f2vm2*ttu22*a11-1.*tau11*tau13*a11*tau22**2*f2f+tau11*tau22*f2f*tau23*tau12*a11-1.*tau11*tau13*a11*ttu21*tau22*f2vm1-1.*tau11*tau21*a13*ttu11*tau22*f2vm1+tau11*tau21*tau13*a12*tau22*f2f-2.*tau11*tau21*a13*tau12*tau22*f2f-1.*tau11*a13*tau12*tau22*f2um1*ttu21-1.*tau11*a12*tau22*tau23*f2um1*ttu11+tau11*tau21*a12*tau23*tau12*f2f+a13*tau22**2*tau11**2*f2f+tau22*f2vm2*ttu22*a13*tau11**2-1.*a12*tau23*tau11**2*tau22*f2f-1.*tau11*tau21*ttu22*f2vm2*a13*tau12+a13*ttu21*tau11**2*tau22*f2vm1+6.*ttu21*f2wm2*tau12**2*tau21*a11+tau22*tau11*f2wm2*tau12*ttu22*a11+tau21*tau23*ttu11*f2vm1*tau11*a12+tau21*tau13*a11*ttu11*tau22*f2vm1+tau22*f2vm2*tau23*tau11*ttu12*a11-1.*tau21*tau12**2*f2wm2*ttu22*a11+tau21*a11*tau12*tau22*f2wm2*ttu12-1.*ttu21*tau23*f2vm1*tau11**2*a12-6.*ttu21*f2vm2*tau23*tau11**2*a12-6.*ttu21*f2um2*tau23*a11*tau12**2+ttu21*tau23*f2vm1*tau11*tau12*a11-6.*ttu21*tau22*f2wm2*tau11*a11*tau12+6.*ttu21*f2um2*tau23*a12*tau11*tau12+6.*ttu21*f2vm2*tau23*tau11*a11*tau12-6.*tau21*ttu11*tau22*f2wm2*tau11*a12+6.*tau21*tau13*ttu11*tau22*f2um2*a12+tau21*tau13*ttu21*f2vm1*tau11*a12+tau21*a12*tau12*f2wm2*tau11*ttu22+tau22*tau13*f2um2*a12*tau11*ttu22+6.*tau22*tau13*f2um2*a11*ttu21*tau12+6.*tau22*tau13*f2vm2*tau21*a11*ttu11-1.*tau22*f2wm2*tau11**2*a12*ttu22+tau22*tau13*f2um1*ttu11*tau21*a12+tau22*tau13*f2um1*ttu21*tau12*a11-6.*ttu21*tau12*f2wm2*tau11*a12*tau21-6.*ttu21*tau13*f2vm2*tau21*a11*tau12+6.*tau22*f2um2*tau23*a11*ttu11*tau12-6.*tau22*f2wm2*tau12*tau21*a11*ttu11-6.*tau22*f2vm2*tau23*tau11*a11*ttu11+tau22*tau23*f2um1*ttu11*tau12*a11+tau22*tau21*f2wm2*ttu12*a12*tau11+tau21*tau13*tau12*f2vm2*ttu22*a11-6.*tau21**2*tau13*ttu11*f2vm2*a12+6.*tau21**2*ttu11*f2wm2*tau12*a12-1.*tau21**2*tau13*ttu11*f2vm1*a12-1.*tau21**2*ttu12*f2wm2*tau12*a12+6.*tau21*tau13*ttu21*f2vm2*a12*tau11-6.*ttu21*tau22*tau13*f2um2*a12*tau11-1.*ttu21*tau23*f2um1*tau12**2*a11+ttu21*tau23*f2um1*tau12*a12*tau11+6.*ttu21*tau22*f2wm2*tau11**2*a12-6.*tau22**2*tau13*f2um2*a11*ttu11-1.*tau22**2*tau13*f2um1*ttu11*a11-1.*tau22**2*f2wm2*ttu12*tau11*a11+6.*tau22**2*f2wm2*tau11*a11*ttu11+tau21*tau23*ttu12*f2um2*a12*tau12+6.*tau21*tau23*ttu11*f2vm2*a12*tau11-6.*tau21*tau23*ttu11*f2um2*a12*tau12)/(tau23*tau12*f2vm1*tau21*a13*tau11+6.*tau23*tau12*f2wm2*tau11*a12*tau21+tau23*tau12*f2wm1*tau11*tau21*a12-1.*f2wm1*tau21*tau12**2*tau23*a11+6.*tau23*tau12*f2vm2*tau21*a13*tau11-1.*tau23*f2um1*tau12**2*tau21*a13+6.*tau13*f2vm2*tau21*tau23*a11*tau12-2.*tau13*tau23*f2vm1*tau11*tau21*a12-6.*f2wm2*tau12**2*tau21*tau23*a11-6.*tau13*f2vm2*tau21**2*a13*tau12+tau13*f2vm1*tau21*tau23*tau12*a11-1.*tau23**2*f2um1*tau12*a12*tau11+tau13*tau23*f2um1*tau12*tau21*a12-12.*tau13*f2vm2*tau21*tau23*a12*tau11-6.*tau13*f2wm2*tau12*tau21**2*a12-1.*tau22**2*tau13*f2um1*a13*tau11+tau22*f2wm1*tau11*tau23*tau12*a11-6.*tau22*f2wm2*tau11**2*tau23*a12-6.*tau22*tau13**2*f2um2*a12*tau21-1.*tau22*tau13**2*f2um1*tau21*a12-6.*tau22*tau13**2*f2vm2*tau21*a11-1.*tau22*tau13**2*f2vm1*tau21*a11-1.*tau22*f2wm1*tau11**2*a12*tau23-1.*tau22*tau23*f2vm1*tau11**2*a13-12.*tau22*tau13*f2um2*tau23*a11*tau12-1.*tau13*f2vm1*tau21**2*tau12*a13-2.*tau22*f2wm1*tau21*tau12*a13*tau11+tau22*tau23*f2um1*tau12*a13*tau11-6.*f2um2*tau23**2*a12*tau11*tau12-6.*f2um2*a13*tau21*tau12**2*tau23-6.*f2vm2*tau23**2*tau11*a11*tau12+6.*tau13*f2um2*a12*tau21*tau23*tau12+6.*tau22*tau13*f2um2*a13*tau21*tau12+6.*tau22*tau13*f2wm2*tau12*tau21*a11+tau13**2*f2vm1*tau21**2*a12+tau22*tau13*f2vm1*tau21*a13*tau11+tau22*tau13*f2wm1*tau11*tau21*a12+6.*tau13**2*f2vm2*tau21**2*a12-6.*tau22**2*tau13*f2um2*a13*tau11+tau22*tau13*f2wm1*tau21*tau12*a11+6.*tau22*tau13*f2vm2*tau21*a13*tau11-2.*tau22*tau13*f2um1*a11*tau23*tau12+tau22*tau13*f2um1*a12*tau11*tau23-1.*tau22**2*tau13*f2wm1*tau11*a11+tau22*tau13*f2um1*tau21*tau12*a13-1.*tau23**2*f2vm1*tau11*tau12*a11+6.*tau22*f2wm2*tau11*tau23*a11*tau12-1.*tau13*f2wm1*tau21**2*tau12*a12-6.*tau22*f2vm2*tau23*tau11**2*a13-6.*tau22**2*tau13*f2wm2*tau11*a11+tau23**2*f2vm1*tau11**2*a12+6.*f2vm2*tau23**2*tau11**2*a12+6.*f2um2*tau23**2*a11*tau12**2+6.*tau22*f2um2*a13*tau11*tau23*tau12-12.*tau22*f2wm2*tau12*tau21*a13*tau11+6.*tau22*tau13*f2wm2*tau11*a12*tau21+tau22*tau13*tau23*f2vm1*tau11*a11+6.*tau22*tau13*f2vm2*tau23*tau11*a11+6.*tau22*tau13*f2um2*tau23*a12*tau11+tau22**2*tau13**2*f2um1*a11+6.*f2wm2*tau12**2*tau21**2*a13+tau23**2*f2um1*tau12**2*a11+f2wm1*tau21**2*tau12**2*a13+6.*tau22**2*f2wm2*tau11**2*a13+tau22**2*f2wm1*tau11**2*a13+6.*tau22**2*tau13**2*f2um2*a11)

      u(i1-2*is1,i2-2*is2,i3-2*is3,ez) = (-1.*tau21**2*f2wm1*tau12**2*f1f-1.*f2wm1*tau11**2*tau22**2*f1f+f2vm1*tau23*tau11**2*f1f*tau22+tau11*tau13*f2um1*tau22**2*f1f-1.*tau11*tau21*f2vm1*f1f*tau23*tau12-1.*tau11*tau21*tau13*f2vm1*f1f*tau22-1.*tau11*f2um1*tau23*tau12*f1f*tau22+tau12*tau13*tau21**2*f2vm1*f1f-1.*tau12*tau22*tau13*tau21*f2um1*f1f+tau21*f2um1*tau23*tau12**2*f1f+2.*tau11*tau21*f2wm1*tau12*f1f*tau22-1.*ttu12*tau22*tau13*f2um1*tau21*a12-6.*ttu12*tau22*tau13*f2vm2*tau21*a11+ttu12*tau23*f2um1*tau12*tau21*a12-6.*ttu12*tau22*tau13*f2um2*a12*tau21-1.*ttu12*tau22*tau13*f2vm1*tau21*a11-6.*ttu12*f2vm2*tau21**2*a13*tau12+6.*ttu12*f2vm2*tau21*tau23*a11*tau12+6.*ttu12*tau22*f2vm2*tau21*a13*tau11+ttu12*tau22*f2wm1*tau11*tau21*a12+6.*ttu12*tau13*f2vm2*tau21**2*a12-6.*ttu12*tau22**2*f2um2*a13*tau11+6.*ttu12*tau22*f2um2*a13*tau21*tau12+ttu12*tau13*f2vm1*tau21**2*a12+ttu12*tau22*tau23*f2vm1*tau11*a11+ttu12*tau22*f2wm1*tau21*tau12*a11+ttu12*tau22**2*tau13*f2um1*a11-1.*ttu12*f2wm1*tau21**2*tau12*a12-1.*ttu12*tau22**2*f2wm1*tau11*a11+6.*ttu12*tau22**2*tau13*f2um2*a11+6.*ttu12*tau22*f2um2*tau23*a12*tau11-6.*f2um1*ttu21*tau21*tau12**2*a13-6.*tau21**2*f2f*tau12**2*a13-6.*f2um2*a13*tau12**2*tau21*ttu22+6.*tau12*tau22*tau21*a13*ttu11*f2um1+6.*tau21*f2f*tau23*tau12**2*a11-1.*tau12*tau22*tau13*ttu22*f2um1*a11-6.*tau12*tau22*tau13*ttu22*f2um2*a11+tau12*tau22*ttu22*f2wm1*tau11*a11-1.*tau12*tau22*tau23*ttu12*f2um1*a11+6.*tau12*tau21*a13*ttu21*tau11*f2vm1-1.*tau12*ttu22*tau23*f2vm1*tau11*a11+6.*tau12*tau21*tau23*a11*ttu11*f2vm1-6.*tau12*tau22*tau23*ttu12*f2um2*a11+6.*tau12*tau22*ttu22*f2um2*a13*tau11-6.*tau12*tau23*f2um1*ttu11*tau21*a12+6.*tau12*tau13*f2um1*ttu21*tau21*a12-6.*tau12*f2wm1*ttu21*tau11*tau21*a12+6.*tau12*tau13*f2um2*a12*tau21*ttu22-6.*tau12*tau13*tau21*a11*ttu21*f2vm1+tau12*tau13*ttu22*f2vm1*tau21*a11-6.*tau12*tau21**2*a13*ttu11*f2vm1+6.*tau12*tau21**2*f2wm1*ttu11*a12-6.*tau12*tau22*tau13*tau21*f2f*a11-6.*tau12*tau22*tau21*f2wm1*ttu11*a11+6.*tau12*tau13*tau21**2*f2f*a12-6.*tau12*f2um2*a12*tau11*tau23*ttu22-6.*tau11*tau23*a11*ttu11*tau22*f2vm1-1.*tau11*a12*ttu22*tau23*f2um1*tau12-6.*tau11*a13*ttu11*tau22**2*f2um1+6.*tau11*tau13*tau22*f2vm2*ttu22*a11+6.*tau11*tau13*a11*tau22**2*f2f-6.*tau11*tau22*f2f*tau23*tau12*a11+6.*tau11*tau13*a11*ttu21*tau22*f2vm1+6.*tau11*tau21*a13*ttu11*tau22*f2vm1-6.*tau11*tau21*tau13*a12*ttu22*f2vm2-6.*tau11*tau21*tau13*a12*tau22*f2f+12.*tau11*tau21*a13*tau12*tau22*f2f+tau11*tau21*a12*ttu22*f2wm1*tau12-1.*tau11*tau21*tau13*a12*ttu22*f2vm1-6.*tau11*tau13*a12*tau22*f2um1*ttu21+6.*tau11*a13*tau12*tau22*f2um1*ttu21+6.*tau11*a12*tau22*tau23*f2um1*ttu11-6.*tau11*a11*ttu21*tau22*f2wm1*tau12+ttu22*f2um1*a11*tau23*tau12**2-1.*ttu22*f2wm1*tau21*tau12**2*a11+6.*tau21*a11*ttu21*f2wm1*tau12**2+6.*ttu22*f2um2*tau23*a11*tau12**2-6.*tau11*tau21*a12*tau23*tau12*f2f-6.*a13*tau22**2*tau11**2*f2f+a12*ttu22*tau23*f2vm1*tau11**2+6.*a12*tau22*f2wm1*ttu21*tau11**2-6.*tau22*f2vm2*ttu22*a13*tau11**2+6.*a12*ttu22*f2vm2*tau23*tau11**2-1.*a12*ttu22*tau22*f2wm1*tau11**2+6.*a12*tau23*tau11**2*tau22*f2f+6.*tau11*a11*tau22**2*f2wm1*ttu11+tau11*tau13*a12*ttu22*tau22*f2um1-6.*tau11*tau23*tau12*f2vm2*ttu22*a11-1.*tau11*tau21*a12*tau23*ttu12*f2vm1-6.*tau11*tau21*a12*tau22*f2wm1*ttu11+6.*tau11*tau21*ttu22*f2vm2*a13*tau12-6.*tau11*tau21*a12*tau23*ttu12*f2vm2-6.*a13*ttu21*tau11**2*tau22*f2vm1)/(tau23*tau12*f2vm1*tau21*a13*tau11+6.*tau23*tau12*f2wm2*tau11*a12*tau21+tau23*tau12*f2wm1*tau11*tau21*a12-1.*f2wm1*tau21*tau12**2*tau23*a11+6.*tau23*tau12*f2vm2*tau21*a13*tau11-1.*tau23*f2um1*tau12**2*tau21*a13+6.*tau13*f2vm2*tau21*tau23*a11*tau12-2.*tau13*tau23*f2vm1*tau11*tau21*a12-6.*f2wm2*tau12**2*tau21*tau23*a11-6.*tau13*f2vm2*tau21**2*a13*tau12+tau13*f2vm1*tau21*tau23*tau12*a11-1.*tau23**2*f2um1*tau12*a12*tau11+tau13*tau23*f2um1*tau12*tau21*a12-12.*tau13*f2vm2*tau21*tau23*a12*tau11-6.*tau13*f2wm2*tau12*tau21**2*a12-1.*tau22**2*tau13*f2um1*a13*tau11+tau22*f2wm1*tau11*tau23*tau12*a11-6.*tau22*f2wm2*tau11**2*tau23*a12-6.*tau22*tau13**2*f2um2*a12*tau21-1.*tau22*tau13**2*f2um1*tau21*a12-6.*tau22*tau13**2*f2vm2*tau21*a11-1.*tau22*tau13**2*f2vm1*tau21*a11-1.*tau22*f2wm1*tau11**2*a12*tau23-1.*tau22*tau23*f2vm1*tau11**2*a13-12.*tau22*tau13*f2um2*tau23*a11*tau12-1.*tau13*f2vm1*tau21**2*tau12*a13-2.*tau22*f2wm1*tau21*tau12*a13*tau11+tau22*tau23*f2um1*tau12*a13*tau11-6.*f2um2*tau23**2*a12*tau11*tau12-6.*f2um2*a13*tau21*tau12**2*tau23-6.*f2vm2*tau23**2*tau11*a11*tau12+6.*tau13*f2um2*a12*tau21*tau23*tau12+6.*tau22*tau13*f2um2*a13*tau21*tau12+6.*tau22*tau13*f2wm2*tau12*tau21*a11+tau13**2*f2vm1*tau21**2*a12+tau22*tau13*f2vm1*tau21*a13*tau11+tau22*tau13*f2wm1*tau11*tau21*a12+6.*tau13**2*f2vm2*tau21**2*a12-6.*tau22**2*tau13*f2um2*a13*tau11+tau22*tau13*f2wm1*tau21*tau12*a11+6.*tau22*tau13*f2vm2*tau21*a13*tau11-2.*tau22*tau13*f2um1*a11*tau23*tau12+tau22*tau13*f2um1*a12*tau11*tau23-1.*tau22**2*tau13*f2wm1*tau11*a11+tau22*tau13*f2um1*tau21*tau12*a13-1.*tau23**2*f2vm1*tau11*tau12*a11+6.*tau22*f2wm2*tau11*tau23*a11*tau12-1.*tau13*f2wm1*tau21**2*tau12*a12-6.*tau22*f2vm2*tau23*tau11**2*a13-6.*tau22**2*tau13*f2wm2*tau11*a11+tau23**2*f2vm1*tau11**2*a12+6.*f2vm2*tau23**2*tau11**2*a12+6.*f2um2*tau23**2*a11*tau12**2+6.*tau22*f2um2*a13*tau11*tau23*tau12-12.*tau22*f2wm2*tau12*tau21*a13*tau11+6.*tau22*tau13*f2wm2*tau11*a12*tau21+tau22*tau13*tau23*f2vm1*tau11*a11+6.*tau22*tau13*f2vm2*tau23*tau11*a11+6.*tau22*tau13*f2um2*tau23*a12*tau11+tau22**2*tau13**2*f2um1*a11+6.*f2wm2*tau12**2*tau21**2*a13+tau23**2*f2um1*tau12**2*a11+f2wm1*tau21**2*tau12**2*a13+6.*tau22**2*f2wm2*tau11**2*a13+tau22**2*f2wm1*tau11**2*a13+6.*tau22**2*tau13**2*f2um2*a11)

      u(i1-is1,i2-is2,i3-is3,ex) = -1.*(-1.*tau21*tau13*a12*tau22*f2wm1*ttu11+tau21*tau13*a12*tau23*tau12*f2f+6.*tau13*tau22**2*f2um2*a13*ttu11+2.*tau13*f1f*tau22*f2um2*tau23*tau12+tau13**2*f1f*tau22*f2vm2*tau21-1.*tau13*tau23*tau12*f2vm2*ttu22*a11-1.*f1f*tau23*tau12*f2wm2*tau11*tau22+f1f*tau23**2*tau12*f2vm2*tau11-1.*f1f*tau23*tau12*tau13*f2vm2*tau21+f1f*tau23*tau12**2*f2wm2*tau21-1.*tau13*f1f*tau22*f2wm2*tau12*tau21+tau13*f1f*tau22**2*f2wm2*tau11-1.*f1f*tau23**2*tau12**2*f2um2-1.*tau13**2*f1f*tau22**2*f2um2-1.*tau13*f1f*tau22*f2vm2*tau23*tau11+tau23**2*a11*tau12**2*f2f+tau13*a11*tau22**2*f2wm2*ttu12-1.*a12*tau23**2*tau12*f2f*tau11-1.*a12*tau23*tau12*f2wm2*tau11*ttu22-1.*a12*tau23*tau12*f2wm1*ttu21*tau11+tau23**2*a11*ttu11*tau12*f2vm1+tau23**2*tau12*f2vm2*ttu12*a11+tau23*tau12**2*f2wm2*ttu22*a11+a13*tau12*tau23*tau11*tau22*f2f+a11*ttu21*tau23*tau12**2*f2wm1-1.*tau23*a11*tau12*tau22*f2wm1*ttu11-1.*tau23*a11*tau12*tau22*f2wm2*ttu12-1.*tau13*tau22*f2vm2*ttu22*a13*tau11+tau13*a12*tau23*tau11*tau22*f2f-1.*tau13*tau22*f2vm2*tau23*ttu12*a11-1.*tau13*tau22*f2wm2*tau12*ttu22*a11-1.*tau13*tau23*a11*ttu11*tau22*f2vm1-1.*tau13*a11*ttu21*tau23*tau12*f2vm1-1.*tau13*a13*ttu21*tau11*tau22*f2vm1+tau13*a11*tau22**2*f2wm1*ttu11-1.*tau13*a11*ttu21*tau22*f2wm1*tau12-1.*tau13*a13*tau22**2*tau11*f2f+tau13**2*tau22*f2vm2*ttu22*a11+tau13**2*a11*ttu21*tau22*f2vm1+tau13**2*a11*tau22**2*f2f-2.*tau13*tau22*f2f*tau23*tau12*a11+tau22*f2wm1*ttu21*tau11*tau12*a13+tau23*ttu12*tau22*f2um2*a13*tau12+6.*tau22*f2vm2*tau23*tau11*a13*ttu11-6.*tau22*f2um2*a13*ttu11*tau23*tau12+6.*tau22*f2wm2*tau12*a13*ttu21*tau11+tau23*tau11*a13*ttu11*tau22*f2vm1+6.*tau23*ttu11*tau22*f2wm2*tau11*a12-6.*tau13*tau23*ttu11*tau22*f2um2*a12-6.*tau13*ttu21*f2um2*a12*tau23*tau12+tau13*ttu21*tau23*f2vm1*tau11*a12+6.*tau13*ttu21*f2vm2*tau23*a12*tau11-6.*tau13*ttu21*tau22*f2wm2*tau11*a12+tau13*tau23*ttu12*tau22*f2um2*a12-6.*tau13*ttu21*tau22*f2um2*a13*tau12+tau13*ttu22*tau22*f2um2*a13*tau12+tau13*ttu22*f2um2*a12*tau23*tau12-1.*tau13**2*ttu22*tau22*f2um2*a12+tau13*ttu22*tau22*f2wm2*tau11*a12+tau23*tau11*ttu22*f2vm2*a13*tau12-6.*tau23*tau12*f2vm2*a13*ttu21*tau11+tau23*tau11*a12*tau22*f2wm1*ttu11-6.*tau21*tau13**2*ttu21*f2vm2*a12-1.*tau21*ttu21*f2wm1*tau12**2*a13-6.*tau21*ttu21*f2wm2*tau12**2*a13-1.*tau21*tau13**2*ttu21*f2vm1*a12+tau21*tau13*ttu21*f2vm1*tau12*a13+tau21*tau13*tau22*f2vm2*a13*ttu12+6.*tau21*tau13*tau23*ttu11*f2vm2*a12+6.*tau21*tau13*ttu21*f2vm2*a13*tau12+6.*tau21*tau13*ttu21*f2wm2*tau12*a12-6.*tau21*tau23*ttu11*f2wm2*tau12*a12+tau21*tau13*tau23*ttu11*f2vm1*a12-6.*tau21*tau13*tau22*f2vm2*a13*ttu11+6.*tau21*tau22*f2wm2*tau12*a13*ttu11+tau21*tau22*f2wm1*ttu11*tau12*a13+tau21*tau23*ttu12*f2wm2*tau12*a12+tau21*tau13*ttu21*f2wm1*tau12*a12-6.*tau22**2*f2wm2*tau11*a13*ttu11-1.*tau21*tau13**2*a12*tau22*f2f-1.*tau21*tau13*a12*tau22*f2wm2*ttu12+tau21*tau13*a13*tau12*tau22*f2f-1.*tau22**2*f2wm1*ttu11*a13*tau11-1.*tau23**2*ttu12*f2um2*a12*tau12-1.*ttu22*f2um2*a13*tau12**2*tau23+6.*ttu21*f2um2*a13*tau12**2*tau23-1.*tau21*tau23*tau12**2*f2f*a13-6.*tau23**2*ttu11*f2vm2*a12*tau11+6.*tau23**2*ttu11*f2um2*a12*tau12-1.*tau13*tau22**2*f2um2*a13*ttu12-1.*tau23**2*ttu11*f2vm1*tau11*a12-1.*tau21*a13*ttu11*tau23*tau12*f2vm1-1.*tau21*tau23*tau12*f2vm2*a13*ttu12+6.*tau13**2*ttu21*tau22*f2um2*a12)/(tau23*tau12*f2vm1*tau21*a13*tau11+6.*tau23*tau12*f2wm2*tau11*a12*tau21+tau23*tau12*f2wm1*tau11*tau21*a12-1.*f2wm1*tau21*tau12**2*tau23*a11+6.*tau23*tau12*f2vm2*tau21*a13*tau11-1.*tau23*f2um1*tau12**2*tau21*a13+6.*tau13*f2vm2*tau21*tau23*a11*tau12-2.*tau13*tau23*f2vm1*tau11*tau21*a12-6.*f2wm2*tau12**2*tau21*tau23*a11-6.*tau13*f2vm2*tau21**2*a13*tau12+tau13*f2vm1*tau21*tau23*tau12*a11-1.*tau23**2*f2um1*tau12*a12*tau11+tau13*tau23*f2um1*tau12*tau21*a12-12.*tau13*f2vm2*tau21*tau23*a12*tau11-6.*tau13*f2wm2*tau12*tau21**2*a12-1.*tau22**2*tau13*f2um1*a13*tau11+tau22*f2wm1*tau11*tau23*tau12*a11-6.*tau22*f2wm2*tau11**2*tau23*a12-6.*tau22*tau13**2*f2um2*a12*tau21-1.*tau22*tau13**2*f2um1*tau21*a12-6.*tau22*tau13**2*f2vm2*tau21*a11-1.*tau22*tau13**2*f2vm1*tau21*a11-1.*tau22*f2wm1*tau11**2*a12*tau23-1.*tau22*tau23*f2vm1*tau11**2*a13-12.*tau22*tau13*f2um2*tau23*a11*tau12-1.*tau13*f2vm1*tau21**2*tau12*a13-2.*tau22*f2wm1*tau21*tau12*a13*tau11+tau22*tau23*f2um1*tau12*a13*tau11-6.*f2um2*tau23**2*a12*tau11*tau12-6.*f2um2*a13*tau21*tau12**2*tau23-6.*f2vm2*tau23**2*tau11*a11*tau12+6.*tau13*f2um2*a12*tau21*tau23*tau12+6.*tau22*tau13*f2um2*a13*tau21*tau12+6.*tau22*tau13*f2wm2*tau12*tau21*a11+tau13**2*f2vm1*tau21**2*a12+tau22*tau13*f2vm1*tau21*a13*tau11+tau22*tau13*f2wm1*tau11*tau21*a12+6.*tau13**2*f2vm2*tau21**2*a12-6.*tau22**2*tau13*f2um2*a13*tau11+tau22*tau13*f2wm1*tau21*tau12*a11+6.*tau22*tau13*f2vm2*tau21*a13*tau11-2.*tau22*tau13*f2um1*a11*tau23*tau12+tau22*tau13*f2um1*a12*tau11*tau23-1.*tau22**2*tau13*f2wm1*tau11*a11+tau22*tau13*f2um1*tau21*tau12*a13-1.*tau23**2*f2vm1*tau11*tau12*a11+6.*tau22*f2wm2*tau11*tau23*a11*tau12-1.*tau13*f2wm1*tau21**2*tau12*a12-6.*tau22*f2vm2*tau23*tau11**2*a13-6.*tau22**2*tau13*f2wm2*tau11*a11+tau23**2*f2vm1*tau11**2*a12+6.*f2vm2*tau23**2*tau11**2*a12+6.*f2um2*tau23**2*a11*tau12**2+6.*tau22*f2um2*a13*tau11*tau23*tau12-12.*tau22*f2wm2*tau12*tau21*a13*tau11+6.*tau22*tau13*f2wm2*tau11*a12*tau21+tau22*tau13*tau23*f2vm1*tau11*a11+6.*tau22*tau13*f2vm2*tau23*tau11*a11+6.*tau22*tau13*f2um2*tau23*a12*tau11+tau22**2*tau13**2*f2um1*a11+6.*f2wm2*tau12**2*tau21**2*a13+tau23**2*f2um1*tau12**2*a11+f2wm1*tau21**2*tau12**2*a13+6.*tau22**2*f2wm2*tau11**2*a13+tau22**2*f2wm1*tau11**2*a13+6.*tau22**2*tau13**2*f2um2*a11)

      u(i1-2*is1,i2-2*is2,i3-2*is3,ex) = (-1.*a12*tau23**2*ttu12*f2um1*tau12-1.*tau21*a13*ttu12*tau22*f2wm1*tau12-6.*tau21*tau13*a12*tau23*ttu12*f2vm2+6.*tau21*tau13*a12*tau22*f2wm1*ttu11-6.*tau21*tau13*ttu22*f2vm2*a13*tau12-6.*tau21*tau13*a12*tau23*tau12*f2f-6.*tau21*tau13*a12*ttu22*f2wm2*tau12-1.*tau21*tau13*a12*tau23*ttu12*f2vm1-6.*tau21*a12*tau23*tau12*f2wm1*ttu11+tau21*ttu22*f2wm1*tau12**2*a13-1.*tau13**2*a12*ttu22*tau22*f2um1+6.*tau13*tau23*tau12*f2vm2*ttu22*a11+a13*ttu12*tau22**2*f2wm1*tau11-6.*tau23**2*a11*tau12**2*f2f+2.*tau13*f2um1*tau23*tau12*f1f*tau22-1.*tau13*f2vm1*tau23*tau11*f1f*tau22-6.*tau13*a11*tau22**2*f2wm2*ttu12+6.*a12*tau23**2*tau12*f2f*tau11+6.*a12*tau23*tau12*f2wm2*tau11*ttu22-1.*a12*tau23*ttu12*tau22*f2wm1*tau11-6.*a12*tau23*tau11*tau22*f2wm2*ttu12+6.*a12*tau23*tau12*f2wm1*ttu21*tau11+6.*a12*tau11*tau23**2*ttu12*f2vm2+6.*a12*tau23**2*tau12*f2um1*ttu11+a12*tau11*tau23**2*ttu12*f2vm1-6.*tau23**2*a11*ttu11*tau12*f2vm1-1.*ttu22*tau23*f2um1*tau12**2*a13+ttu22*tau23*tau12*f2vm1*a13*tau11+f2vm1*tau23**2*tau11*f1f*tau12-1.*f2um1*tau23**2*tau12**2*f1f-1.*tau13**2*f2um1*tau22**2*f1f-6.*tau23**2*tau12*f2vm2*ttu12*a11+6.*tau23*tau12**2*f2um1*ttu21*a13-1.*f2wm1*tau12*f1f*tau22*tau23*tau11-6.*tau23*tau12**2*f2wm2*ttu22*a11-6.*a13*tau12*tau23*tau11*tau22*f2f-6.*a11*ttu21*tau23*tau12**2*f2wm1+a13*tau12*tau23*ttu12*tau22*f2um1-6.*tau23*tau11*tau22*f2vm2*a13*ttu12-6.*a13*tau12*tau22*tau23*f2um1*ttu11+6.*tau23*a11*tau12*tau22*f2wm1*ttu11+6.*tau23*a11*tau12*tau22*f2wm2*ttu12-1.*ttu22*tau22*f2wm1*tau12*a13*tau11-6.*a13*tau12*tau22*f2wm2*tau11*ttu22-1.*tau23*ttu12*tau22*f2vm1*a13*tau11+tau13*a12*tau23*ttu12*tau22*f2um1-6.*tau13*a12*tau22*tau23*f2um1*ttu11-6.*tau13*a12*tau23*tau12*f2um1*ttu21-1.*tau13*a12*ttu22*tau23*f2vm1*tau11+tau13*a12*ttu22*tau23*f2um1*tau12-6.*tau13*a12*tau22*f2wm1*ttu21*tau11+6.*tau13*tau22*f2vm2*ttu22*a13*tau11-6.*tau13*a12*ttu22*f2vm2*tau23*tau11+tau13*a12*ttu22*tau22*f2wm1*tau11-6.*tau13*a12*tau23*tau11*tau22*f2f+6.*tau13*tau22*f2vm2*tau23*ttu12*a11-6.*tau13*a13*tau12*tau22*f2um1*ttu21+6.*tau13*tau22*f2wm2*tau12*ttu22*a11+6.*tau13*tau23*a11*ttu11*tau22*f2vm1+tau13*ttu22*tau22*f2um1*tau12*a13+6.*tau13*a11*ttu21*tau23*tau12*f2vm1+6.*tau13*a13*ttu21*tau11*tau22*f2vm1-6.*tau13*a11*tau22**2*f2wm1*ttu11+6.*tau13*a11*ttu21*tau22*f2wm1*tau12+6.*tau13*a13*tau22**2*tau11*f2f+6.*tau13*a13*ttu11*tau22**2*f2um1-1.*tau13*a13*ttu12*tau22**2*f2um1-6.*a13*ttu21*tau11*tau23*tau12*f2vm1-6.*tau13**2*tau22*f2vm2*ttu22*a11+6.*tau13**2*a12*tau22*f2um1*ttu21-6.*tau13**2*a11*ttu21*tau22*f2vm1-6.*tau13**2*a11*tau22**2*f2f+tau13*f2wm1*tau11*tau22**2*f1f+tau21*f2wm1*tau12**2*f1f*tau23+12.*tau13*tau22*f2f*tau23*tau12*a11+tau21*tau13**2*a12*ttu22*f2vm1+6.*tau21*tau13**2*a12*tau22*f2f+tau21*a12*tau23*ttu12*f2wm1*tau12-1.*tau21*tau13*a12*ttu22*f2wm1*tau12-1.*tau21*tau13*ttu22*f2vm1*tau12*a13+tau21*tau13*a13*ttu12*tau22*f2vm1-6.*tau21*tau13*a13*ttu11*tau22*f2vm1+6.*tau21*tau13*a12*tau22*f2wm2*ttu12-6.*tau21*tau13*a13*tau12*tau22*f2f+6.*tau21*tau13**2*a12*ttu22*f2vm2+6.*tau21*tau23*tau12**2*f2f*a13+6.*tau21*ttu22*f2wm2*tau12**2*a13+6.*tau21*a13*ttu11*tau23*tau12*f2vm1-6.*tau21*a13*tau12*tau22*f2wm2*ttu12+6.*tau21*tau23*tau12*f2vm2*a13*ttu12-1.*tau21*tau13*f2wm1*tau12*f1f*tau22-1.*tau21*tau13*f2vm1*f1f*tau23*tau12+tau21*tau13**2*f2vm1*f1f*tau22+6.*a13*tau22**2*tau11*f2wm2*ttu12)/(tau23*tau12*f2vm1*tau21*a13*tau11+6.*tau23*tau12*f2wm2*tau11*a12*tau21+tau23*tau12*f2wm1*tau11*tau21*a12-1.*f2wm1*tau21*tau12**2*tau23*a11+6.*tau23*tau12*f2vm2*tau21*a13*tau11-1.*tau23*f2um1*tau12**2*tau21*a13+6.*tau13*f2vm2*tau21*tau23*a11*tau12-2.*tau13*tau23*f2vm1*tau11*tau21*a12-6.*f2wm2*tau12**2*tau21*tau23*a11-6.*tau13*f2vm2*tau21**2*a13*tau12+tau13*f2vm1*tau21*tau23*tau12*a11-1.*tau23**2*f2um1*tau12*a12*tau11+tau13*tau23*f2um1*tau12*tau21*a12-12.*tau13*f2vm2*tau21*tau23*a12*tau11-6.*tau13*f2wm2*tau12*tau21**2*a12-1.*tau22**2*tau13*f2um1*a13*tau11+tau22*f2wm1*tau11*tau23*tau12*a11-6.*tau22*f2wm2*tau11**2*tau23*a12-6.*tau22*tau13**2*f2um2*a12*tau21-1.*tau22*tau13**2*f2um1*tau21*a12-6.*tau22*tau13**2*f2vm2*tau21*a11-1.*tau22*tau13**2*f2vm1*tau21*a11-1.*tau22*f2wm1*tau11**2*a12*tau23-1.*tau22*tau23*f2vm1*tau11**2*a13-12.*tau22*tau13*f2um2*tau23*a11*tau12-1.*tau13*f2vm1*tau21**2*tau12*a13-2.*tau22*f2wm1*tau21*tau12*a13*tau11+tau22*tau23*f2um1*tau12*a13*tau11-6.*f2um2*tau23**2*a12*tau11*tau12-6.*f2um2*a13*tau21*tau12**2*tau23-6.*f2vm2*tau23**2*tau11*a11*tau12+6.*tau13*f2um2*a12*tau21*tau23*tau12+6.*tau22*tau13*f2um2*a13*tau21*tau12+6.*tau22*tau13*f2wm2*tau12*tau21*a11+tau13**2*f2vm1*tau21**2*a12+tau22*tau13*f2vm1*tau21*a13*tau11+tau22*tau13*f2wm1*tau11*tau21*a12+6.*tau13**2*f2vm2*tau21**2*a12-6.*tau22**2*tau13*f2um2*a13*tau11+tau22*tau13*f2wm1*tau21*tau12*a11+6.*tau22*tau13*f2vm2*tau21*a13*tau11-2.*tau22*tau13*f2um1*a11*tau23*tau12+tau22*tau13*f2um1*a12*tau11*tau23-1.*tau22**2*tau13*f2wm1*tau11*a11+tau22*tau13*f2um1*tau21*tau12*a13-1.*tau23**2*f2vm1*tau11*tau12*a11+6.*tau22*f2wm2*tau11*tau23*a11*tau12-1.*tau13*f2wm1*tau21**2*tau12*a12-6.*tau22*f2vm2*tau23*tau11**2*a13-6.*tau22**2*tau13*f2wm2*tau11*a11+tau23**2*f2vm1*tau11**2*a12+6.*f2vm2*tau23**2*tau11**2*a12+6.*f2um2*tau23**2*a11*tau12**2+6.*tau22*f2um2*a13*tau11*tau23*tau12-12.*tau22*f2wm2*tau12*tau21*a13*tau11+6.*tau22*tau13*f2wm2*tau11*a12*tau21+tau22*tau13*tau23*f2vm1*tau11*a11+6.*tau22*tau13*f2vm2*tau23*tau11*a11+6.*tau22*tau13*f2um2*tau23*a12*tau11+tau22**2*tau13**2*f2um1*a11+6.*f2wm2*tau12**2*tau21**2*a13+tau23**2*f2um1*tau12**2*a11+f2wm1*tau21**2*tau12**2*a13+6.*tau22**2*f2wm2*tau11**2*a13+tau22**2*f2wm1*tau11**2*a13+6.*tau22**2*tau13**2*f2um2*a11)

      u(i1-is1,i2-is2,i3-is3,ey) = (-1.*tau23**2*tau11*f1f*f2um2*tau12+tau23*tau12*tau21*f1f*f2wm2*tau11+tau13**2*tau21**2*f1f*f2vm2+tau23**2*tau11**2*f1f*f2vm2-1.*tau13*tau21**2*f1f*f2wm2*tau12+tau13*tau21*f1f*f2um2*tau23*tau12-1.*tau22*tau23*tau11**2*f1f*f2wm2-2.*tau13*tau21*f1f*f2vm2*tau23*tau11-1.*tau22*tau13**2*tau21*f1f*f2um2+tau22*tau13*tau21*f1f*f2wm2*tau11-6.*tau13**2*f2vm2*tau21*a11*ttu21-1.*tau13**2*f2um2*a12*tau21*ttu22+tau13*f2wm2*tau11*a12*tau21*ttu22+tau13*f2um2*a13*tau12*tau21*ttu22-1.*tau13*tau21*f2f*tau23*tau12*a11+tau13*tau23*f2um1*ttu11*tau21*a12-1.*tau13*f2vm2*tau21*ttu22*a13*tau11+tau13*f2um1*ttu21*a12*tau11*tau23+tau13*f2um1*ttu21*tau21*tau12*a13-1.*tau13*f2um1*ttu21*tau23*tau12*a11+tau13*tau21**2*f2f*tau12*a13-1.*tau13*tau21**2*f2wm2*ttu12*a12+6.*tau13*f2vm2*tau21*a13*ttu21*tau11-1.*tau13*f2vm2*tau21*tau23*ttu12*a11-1.*tau13*f2wm2*tau12*tau21*ttu22*a11-1.*tau13*f2vm2*tau23*tau11*ttu22*a11+tau13*f2wm1*ttu21*tau11*tau21*a12+tau13*f2vm2*tau21**2*a13*ttu12+tau22*tau13*tau23*tau11*f1f*f2um2-1.*tau23*tau12*tau21*f2f*a13*tau11-6.*tau13*f2vm2*tau21**2*a13*ttu11+2.*tau13*tau21*f2f*a12*tau11*tau23+6.*tau13*f2vm2*tau23*tau11*a11*ttu21+tau13*f2um2*a12*tau21*tau23*ttu12+tau13*f2um2*a12*tau11*tau23*ttu22+6.*tau13*f2wm2*tau12*tau21*a11*ttu21-6.*tau13*f2um2*a11*ttu21*tau23*tau12+6.*tau13*f2vm2*tau21*tau23*a11*ttu11-1.*tau13**2*f2um1*ttu21*tau21*a12+tau13**2*f2vm2*tau21*ttu22*a11+6.*f2vm2*tau23*tau11*a13*tau21*ttu11+tau23*tau11*f2wm1*tau12*ttu21*a11-1.*f2vm2*tau21*tau23*ttu12*a13*tau11-1.*f2wm2*tau11**2*a12*tau23*ttu22+f2vm2*tau23*tau11**2*ttu22*a13+tau23**2*f2um1*ttu11*tau12*a11-6.*f2wm2*tau12*tau21*a13*ttu21*tau11-1.*f2wm1*ttu21*tau11*tau21*tau12*a13-1.*f2wm1*ttu21*tau11**2*a12*tau23-6.*f2vm2*tau23*tau11**2*a13*ttu21-1.*f2um2*tau23*a13*tau12*tau11*ttu22-1.*tau21*f2wm1*ttu11*a11*tau23*tau12+f2vm2*tau23**2*tau11*ttu12*a11+tau21*f2wm2*ttu12*a12*tau11*tau23+tau23*tau11*f2wm2*tau12*ttu22*a11+6.*f2um2*a13*ttu21*tau11*tau23*tau12-1.*tau23*f2um1*ttu11*tau21*tau12*a13-1.*tau23**2*f2um1*ttu11*a12*tau11+tau23**2*tau11*f2f*tau12*a11+tau21**2*f2wm1*ttu11*tau12*a13+tau21*f2wm1*ttu11*a12*tau11*tau23-1.*tau23**2*tau11**2*f2f*a12-1.*tau13**2*tau21**2*f2f*a12-1.*tau13*tau21**2*f2wm1*ttu11*a12+6.*f2um2*tau23**2*a11*ttu11*tau12+6.*f2wm2*tau12*tau21**2*a13*ttu11-6.*f2wm2*tau12*tau21*tau23*a11*ttu11-1.*f2um2*a12*tau11*tau23**2*ttu12-6.*f2um2*a13*tau21*ttu11*tau23*tau12-6.*f2vm2*tau23**2*tau11*a11*ttu11-1.*tau22*tau13*tau21*f2f*a13*tau11-1.*tau22*tau13*tau23*f2um1*ttu11*a11+tau22*tau13*tau21*f2wm2*ttu12*a11-6.*tau22*tau13*f2wm2*tau11*a11*ttu21-1.*tau22*tau23*f2wm2*ttu12*tau11*a11-6.*tau22*tau13*f2um2*a13*ttu21*tau11+6.*tau22*f2wm2*tau11**2*a13*ttu21+tau22*f2wm1*ttu21*tau11**2*a13+tau22*tau23*tau11**2*f2f*a13+tau22*tau13**2*f2um1*ttu21*a11+tau22*tau13**2*tau21*f2f*a11+6.*tau22*tau13**2*f2um2*a11*ttu21+6.*tau22*f2wm2*tau11*tau23*a11*ttu11-1.*tau22*tau13*tau23*tau11*f2f*a11-1.*tau22*tau13*f2wm1*ttu21*tau11*a11-1.*tau22*tau13*f2um1*ttu21*a13*tau11-1.*tau22*tau13*f2um2*a13*ttu12*tau21+tau22*tau13*tau21*f2wm1*ttu11*a11-6.*tau22*f2wm2*tau11*a13*tau21*ttu11+tau22*tau23*f2um1*ttu11*a13*tau11+tau22*f2um2*tau23*a13*ttu12*tau11+6.*tau22*tau13*f2um2*a13*tau21*ttu11-1.*tau22*tau21*f2wm1*ttu11*a13*tau11-6.*tau22*tau13*f2um2*tau23*a11*ttu11)/(tau23*tau12*f2vm1*tau21*a13*tau11+6.*tau23*tau12*f2wm2*tau11*a12*tau21+tau23*tau12*f2wm1*tau11*tau21*a12-1.*f2wm1*tau21*tau12**2*tau23*a11+6.*tau23*tau12*f2vm2*tau21*a13*tau11-1.*tau23*f2um1*tau12**2*tau21*a13+6.*tau13*f2vm2*tau21*tau23*a11*tau12-2.*tau13*tau23*f2vm1*tau11*tau21*a12-6.*f2wm2*tau12**2*tau21*tau23*a11-6.*tau13*f2vm2*tau21**2*a13*tau12+tau13*f2vm1*tau21*tau23*tau12*a11-1.*tau23**2*f2um1*tau12*a12*tau11+tau13*tau23*f2um1*tau12*tau21*a12-12.*tau13*f2vm2*tau21*tau23*a12*tau11-6.*tau13*f2wm2*tau12*tau21**2*a12-1.*tau22**2*tau13*f2um1*a13*tau11+tau22*f2wm1*tau11*tau23*tau12*a11-6.*tau22*f2wm2*tau11**2*tau23*a12-6.*tau22*tau13**2*f2um2*a12*tau21-1.*tau22*tau13**2*f2um1*tau21*a12-6.*tau22*tau13**2*f2vm2*tau21*a11-1.*tau22*tau13**2*f2vm1*tau21*a11-1.*tau22*f2wm1*tau11**2*a12*tau23-1.*tau22*tau23*f2vm1*tau11**2*a13-12.*tau22*tau13*f2um2*tau23*a11*tau12-1.*tau13*f2vm1*tau21**2*tau12*a13-2.*tau22*f2wm1*tau21*tau12*a13*tau11+tau22*tau23*f2um1*tau12*a13*tau11-6.*f2um2*tau23**2*a12*tau11*tau12-6.*f2um2*a13*tau21*tau12**2*tau23-6.*f2vm2*tau23**2*tau11*a11*tau12+6.*tau13*f2um2*a12*tau21*tau23*tau12+6.*tau22*tau13*f2um2*a13*tau21*tau12+6.*tau22*tau13*f2wm2*tau12*tau21*a11+tau13**2*f2vm1*tau21**2*a12+tau22*tau13*f2vm1*tau21*a13*tau11+tau22*tau13*f2wm1*tau11*tau21*a12+6.*tau13**2*f2vm2*tau21**2*a12-6.*tau22**2*tau13*f2um2*a13*tau11+tau22*tau13*f2wm1*tau21*tau12*a11+6.*tau22*tau13*f2vm2*tau21*a13*tau11-2.*tau22*tau13*f2um1*a11*tau23*tau12+tau22*tau13*f2um1*a12*tau11*tau23-1.*tau22**2*tau13*f2wm1*tau11*a11+tau22*tau13*f2um1*tau21*tau12*a13-1.*tau23**2*f2vm1*tau11*tau12*a11+6.*tau22*f2wm2*tau11*tau23*a11*tau12-1.*tau13*f2wm1*tau21**2*tau12*a12-6.*tau22*f2vm2*tau23*tau11**2*a13-6.*tau22**2*tau13*f2wm2*tau11*a11+tau23**2*f2vm1*tau11**2*a12+6.*f2vm2*tau23**2*tau11**2*a12+6.*f2um2*tau23**2*a11*tau12**2+6.*tau22*f2um2*a13*tau11*tau23*tau12-12.*tau22*f2wm2*tau12*tau21*a13*tau11+6.*tau22*tau13*f2wm2*tau11*a12*tau21+tau22*tau13*tau23*f2vm1*tau11*a11+6.*tau22*tau13*f2vm2*tau23*tau11*a11+6.*tau22*tau13*f2um2*tau23*a12*tau11+tau22**2*tau13**2*f2um1*a11+6.*f2wm2*tau12**2*tau21**2*a13+tau23**2*f2um1*tau12**2*a11+f2wm1*tau21**2*tau12**2*a13+6.*tau22**2*f2wm2*tau11**2*a13+tau22**2*f2wm1*tau11**2*a13+6.*tau22**2*tau13**2*f2um2*a11)

      u(i1-2*is1,i2-2*is2,i3-2*is3,ey) = -1.*(-1.*tau13*tau21**2*f2wm1*tau12*f1f+tau13**2*tau21**2*f2vm1*f1f+tau23*tau12*tau21*f2wm1*tau11*f1f-1.*tau23**2*tau11*f2um1*tau12*f1f-1.*tau22*tau23*tau11**2*f2wm1*f1f-2.*tau13*tau21*f2vm1*tau23*tau11*f1f+tau13*tau21*f2um1*tau23*tau12*f1f-1.*tau22*tau13**2*tau21*f2um1*f1f+tau22*tau13*tau21*f2wm1*tau11*f1f+tau22*tau13*tau23*tau11*f2um1*f1f+6.*tau22*tau13*tau21*a13*ttu11*f2um1+tau22*tau13*tau23*ttu12*f2um1*a11+tau22*tau21*a13*ttu12*f2wm1*tau11+6.*tau22*tau13*ttu22*f2wm2*tau11*a11+6.*tau22*tau23*tau11*a11*f2wm1*ttu11-1.*tau22*tau13**2*ttu22*f2um1*a11-6.*tau22*tau13**2*ttu22*f2um2*a11-1.*tau22*ttu22*f2wm1*tau11**2*a13-6.*tau22*ttu22*f2wm2*tau11**2*a13+6.*tau22*tau21*a13*tau11*f2wm2*ttu12-1.*tau22*tau23*ttu12*f2wm1*tau11*a11+tau22*tau13*ttu22*f2wm1*tau11*a11+tau22*tau13*ttu22*f2um1*a13*tau11+6.*tau22*tau13*tau23*ttu12*f2um2*a11+6.*tau22*tau13*ttu22*f2um2*a13*tau11-1.*tau22*tau13*tau21*a13*ttu12*f2um1+tau13*tau21**2*a13*ttu12*f2vm1-6.*tau13*tau21**2*a13*ttu11*f2vm1+6.*tau13*tau21*a13*ttu21*tau11*f2vm1+6.*tau13*tau21*a11*ttu21*f2wm1*tau12-1.*tau13*tau23*ttu12*f2vm1*tau21*a11-1.*tau13*ttu22*tau23*f2vm1*tau11*a11+6.*tau13*ttu22*f2um2*tau23*a11*tau12+6.*tau13*tau21*tau23*a11*ttu11*f2vm1-1.*tau13*ttu22*f2vm1*tau21*a13*tau11-1.*tau13*ttu22*f2wm1*tau21*tau12*a11+tau13*ttu22*f2um1*a11*tau23*tau12+6.*tau13*tau23*tau11*a11*ttu21*f2vm1-6.*tau13**2*tau21*a11*ttu21*f2vm1+tau13**2*ttu22*f2vm1*tau21*a11-6.*tau21**2*a13*tau12*f2wm2*ttu12+6.*tau23*tau11*a13*tau12*f2um1*ttu21-1.*tau23*tau11*ttu22*f2um1*tau12*a13-6.*tau23*tau11**2*a13*ttu21*f2vm1-6.*tau23**2*ttu12*f2um2*a11*tau12+tau21*ttu22*f2wm1*tau12*a13*tau11+6.*tau21*a13*tau12*f2wm2*tau11*ttu22+ttu22*tau23*f2vm1*tau11**2*a13-1.*tau23**2*ttu12*f2um1*a11*tau12-1.*tau21**2*a13*ttu12*f2wm1*tau12+6.*tau21*tau23*a11*tau12*f2wm2*ttu12+tau23*ttu12*f2wm1*tau21*tau12*a11+tau23**2*ttu12*f2vm1*tau11*a11+6.*tau23*ttu12*f2um2*a13*tau21*tau12+6.*tau23*tau11*tau21*a13*ttu11*f2vm1-1.*tau21*tau23*ttu12*f2vm1*a13*tau11-6.*tau23**2*tau11*a11*ttu11*f2vm1+tau21*a13*tau12*tau23*ttu12*f2um1+tau23**2*tau11**2*f2vm1*f1f+6.*tau13**2*f2um2*a12*tau21*ttu22-6.*tau13*f2wm2*tau11*a12*tau21*ttu22-6.*tau13*f2um2*a13*tau12*tau21*ttu22+6.*tau13*tau21*f2f*tau23*tau12*a11-6.*tau13*tau23*f2um1*ttu11*tau21*a12-6.*tau13*f2um1*ttu21*a12*tau11*tau23-6.*tau13*f2um1*ttu21*tau21*tau12*a13-6.*tau13*tau21**2*f2f*tau12*a13+6.*tau13*tau21**2*f2wm2*ttu12*a12-6.*tau13*f2wm1*ttu21*tau11*tau21*a12+6.*tau23*tau12*tau21*f2f*a13*tau11-12.*tau13*tau21*f2f*a12*tau11*tau23-6.*tau13*f2um2*a12*tau21*tau23*ttu12-6.*tau13*f2um2*a12*tau11*tau23*ttu22+6.*tau13**2*f2um1*ttu21*tau21*a12-6.*tau23*tau11*f2wm1*tau12*ttu21*a11+6.*f2wm2*tau11**2*a12*tau23*ttu22+6.*f2wm1*ttu21*tau11**2*a12*tau23-6.*tau21*f2wm2*ttu12*a12*tau11*tau23-6.*tau23*tau11*f2wm2*tau12*ttu22*a11+6.*tau23**2*f2um1*ttu11*a12*tau11-6.*tau23**2*tau11*f2f*tau12*a11-6.*tau21*f2wm1*ttu11*a12*tau11*tau23+6.*tau23**2*tau11**2*f2f*a12+6.*tau13**2*tau21**2*f2f*a12+6.*tau13*tau21**2*f2wm1*ttu11*a12+6.*f2um2*a12*tau11*tau23**2*ttu12+6.*tau22*tau13*tau21*f2f*a13*tau11-6.*tau22*tau13*tau21*f2wm2*ttu12*a11-6.*tau22*tau23*tau11**2*f2f*a13-6.*tau22*tau13**2*tau21*f2f*a11+6.*tau22*tau13*tau23*tau11*f2f*a11-6.*tau22*tau13*tau21*f2wm1*ttu11*a11-6.*tau22*tau23*f2um1*ttu11*a13*tau11-6.*tau22*f2um2*tau23*a13*ttu12*tau11)/(tau23*tau12*f2vm1*tau21*a13*tau11+6.*tau23*tau12*f2wm2*tau11*a12*tau21+tau23*tau12*f2wm1*tau11*tau21*a12-1.*f2wm1*tau21*tau12**2*tau23*a11+6.*tau23*tau12*f2vm2*tau21*a13*tau11-1.*tau23*f2um1*tau12**2*tau21*a13+6.*tau13*f2vm2*tau21*tau23*a11*tau12-2.*tau13*tau23*f2vm1*tau11*tau21*a12-6.*f2wm2*tau12**2*tau21*tau23*a11-6.*tau13*f2vm2*tau21**2*a13*tau12+tau13*f2vm1*tau21*tau23*tau12*a11-1.*tau23**2*f2um1*tau12*a12*tau11+tau13*tau23*f2um1*tau12*tau21*a12-12.*tau13*f2vm2*tau21*tau23*a12*tau11-6.*tau13*f2wm2*tau12*tau21**2*a12-1.*tau22**2*tau13*f2um1*a13*tau11+tau22*f2wm1*tau11*tau23*tau12*a11-6.*tau22*f2wm2*tau11**2*tau23*a12-6.*tau22*tau13**2*f2um2*a12*tau21-1.*tau22*tau13**2*f2um1*tau21*a12-6.*tau22*tau13**2*f2vm2*tau21*a11-1.*tau22*tau13**2*f2vm1*tau21*a11-1.*tau22*f2wm1*tau11**2*a12*tau23-1.*tau22*tau23*f2vm1*tau11**2*a13-12.*tau22*tau13*f2um2*tau23*a11*tau12-1.*tau13*f2vm1*tau21**2*tau12*a13-2.*tau22*f2wm1*tau21*tau12*a13*tau11+tau22*tau23*f2um1*tau12*a13*tau11-6.*f2um2*tau23**2*a12*tau11*tau12-6.*f2um2*a13*tau21*tau12**2*tau23-6.*f2vm2*tau23**2*tau11*a11*tau12+6.*tau13*f2um2*a12*tau21*tau23*tau12+6.*tau22*tau13*f2um2*a13*tau21*tau12+6.*tau22*tau13*f2wm2*tau12*tau21*a11+tau13**2*f2vm1*tau21**2*a12+tau22*tau13*f2vm1*tau21*a13*tau11+tau22*tau13*f2wm1*tau11*tau21*a12+6.*tau13**2*f2vm2*tau21**2*a12-6.*tau22**2*tau13*f2um2*a13*tau11+tau22*tau13*f2wm1*tau21*tau12*a11+6.*tau22*tau13*f2vm2*tau21*a13*tau11-2.*tau22*tau13*f2um1*a11*tau23*tau12+tau22*tau13*f2um1*a12*tau11*tau23-1.*tau22**2*tau13*f2wm1*tau11*a11+tau22*tau13*f2um1*tau21*tau12*a13-1.*tau23**2*f2vm1*tau11*tau12*a11+6.*tau22*f2wm2*tau11*tau23*a11*tau12-1.*tau13*f2wm1*tau21**2*tau12*a12-6.*tau22*f2vm2*tau23*tau11**2*a13-6.*tau22**2*tau13*f2wm2*tau11*a11+tau23**2*f2vm1*tau11**2*a12+6.*f2vm2*tau23**2*tau11**2*a12+6.*f2um2*tau23**2*a11*tau12**2+6.*tau22*f2um2*a13*tau11*tau23*tau12-12.*tau22*f2wm2*tau12*tau21*a13*tau11+6.*tau22*tau13*f2wm2*tau11*a12*tau21+tau22*tau13*tau23*f2vm1*tau11*a11+6.*tau22*tau13*f2vm2*tau23*tau11*a11+6.*tau22*tau13*f2um2*tau23*a12*tau11+tau22**2*tau13**2*f2um1*a11+6.*f2wm2*tau12**2*tau21**2*a13+tau23**2*f2um1*tau12**2*a11+f2wm1*tau21**2*tau12**2*a13+6.*tau22**2*f2wm2*tau11**2*a13+tau22**2*f2wm1*tau11**2*a13+6.*tau22**2*tau13**2*f2um2*a11)


 ! *********** done *********************
