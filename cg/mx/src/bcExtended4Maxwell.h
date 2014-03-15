

! ****************** Fourth-order ********************
      g1a = a21*(6*u(i1,i2,i3,ex)-4*u(i1+is1,i2,i3,ex)+u(i1+2*is1,i2,i3,ex))+a22*(6*u(i1,i2,i3,ey)-4*u(i1+is1,i2,i3,ey)+u(i1+2*is1,i2,i3,ey))

      g2a = a11*(6*u(i1,i2,i3,ex)-4*u(i1,i2+is2,i3,ex)+u(i1,i2+2*is2,i3,ex))+a12*(6*u(i1,i2,i3,ey)-4*u(i1,i2+is2,i3,ey)+u(i1,i2+2*is2,i3,ey))

      cu20=-1/12.*c11/dra**2+1/12.*c1/dra

      cu02=-1/12.*c22/dsa**2+1/12.*c2/dsa

      cu10=4/3.*c11/dra**2-2/3.*c1/dra

      cu01=4/3.*c22/dsa**2-2/3.*c2/dsa

      cv20=-1/12.*c11/dra**2+1/12.*c1/dra

      cv02=-1/12.*c22/dsa**2+1/12.*c2/dsa

      cv10=4/3.*c11/dra**2-2/3.*c1/dra

      cv01=4/3.*c22/dsa**2-2/3.*c2/dsa

      gLu= uLap-(cu20*u(i1-2*is1,i2,i3,ex) + cu10*u(i1-is1,i2,i3,ex) + cu02*u(i1,i2-2*is2,i3,ex) + cu01*u(i1,i2-is2,i3,ex)) -utt00 

      gLv= vLap-(cv20*u(i1-2*is1,i2,i3,ey) + cv10*u(i1-is1,i2,i3,ey) + cv02*u(i1,i2-2*is2,i3,ey) + cv01*u(i1,i2-is2,i3,ey)) -vtt00 

      det=4*a11m2*a22*cv02*a21zm2*a12*a21zm1*cu10*a12m1+4*a11m1*a22*cu20*a12m2*cv01*a21zm1*a21zm2*a12-16*a21*a12m1*a21zm2*cu20*a12m2*cv02*a12*a21zm1-4*a21*a12m1*cu20*a12m2*cv01*a21zm1*a21zm2*a12-a21*a12m2*cv01*a21zm1*a21zm2*a12*cu10*a12m1+16*a11m1*a22*a21zm2*cu20*a12m2*cv02*a12*a21zm1-4*a21*a12m2*cv02*a21zm2*a12*a21zm1*cu10*a12m1+16*a11m2*cv20*a21*a12m1*cu02*a22zm2*a12*a21zm1-16*a11m2*a11m1*cv20*a22*cu02*a22zm2*a12*a21zm1-a11m1*a21*a12m2*cv10*a22zm1*cu01*a11*a22zm2-4*a11m1*a21*a12m2*cv10*a22zm1*cu02*a22zm2*a11+4*a11m2*a11m1*cv20*a22*a22zm1*cu01*a11*a22zm2+16*a11m2*a11m1*cv20*a22*a22zm1*cu02*a22zm2*a11-4*a11m2*a11m1*a22*cv10*cu02*a22zm2*a12*a21zm1+4*a11m2*a11m1*a22*cv10*a22zm1*cu02*a22zm2*a11-a11m2*a22*cv01*a21zm1*a11*a22zm2*cu10*a12m1-4*a11m1*a22*cu20*a12m2*cv01*a21zm1*a11*a22zm2+4*a21*a12m1*cu20*a12m2*cv01*a21zm1*a11*a22zm2+4*a11m1*a21*a12m2*cv10*cu02*a22zm2*a12*a21zm1+a21*a12m2*cv01*a21zm1*a11*a22zm2*cu10*a12m1-4*a11m2*cv20*a21*a12m1*a22zm1*cu01*a11*a22zm2-16*a11m2*cv20*a21*a12m1*a22zm1*cu02*a22zm2*a11+a11m2*a11m1*a22*cv10*a22zm1*cu01*a11*a22zm2-a11m2*a11m1*a22*cv10*a22zm1*cu01*a21zm2*a12+16*a21*a12m1*a22zm1*a21zm2*cu20*a12m2*cv02*a11+4*a22zm1*a21*a12m2*cv02*a21zm2*a11*cu10*a12m1+4*a11m2*cv20*a21*a12m1*a22zm1*cu01*a21zm2*a12+a11m2*a22*cv01*a21zm1*a21zm2*a12*cu10*a12m1+a11m1*a21*a12m2*cv10*a22zm1*cu01*a21zm2*a12-16*a11m1*a22*a22zm1*a21zm2*cu20*a12m2*cv02*a11-4*a11m2*a11m1*cv20*a22*a22zm1*cu01*a21zm2*a12-4*a11m2*a22zm1*a22*cv02*a21zm2*a11*cu10*a12m1

      u(i1-is1,i2,i3,ex)=(a12m1*cu01*a21zm2*a12*a21*a12m2*cv01*tdu01+a12m1*a22zm1*a11m2*cv20*cu01*a21zm2*a12*g1a+a12m1*a22zm1*cu01*a21zm2*a12*a21*tdu20*cv20+4*a12m1*a22zm1*a11*a21zm2*cu20*tdu20*a22*cv02+4*a12m1*a22zm1*a11*a21zm2*cu20*a12m2*cv02*g1a+a12m1*a22zm1*cu01*a21zm2*a12*a21*a12m2*gLv-4*a12m1*a22zm1*a11*a21zm2*gLu*a21*a12m2*cv02-a12m1*a22zm1*cu01*a21zm2*g2a*a21*a12m2*cv02-4*tdu10*a11m2*cv20*a22*a22zm1*cu01*a21zm2*a12-4*a12m1*a11*cu02*a22zm2*a21*a12m2*cv01*tdu01-4*a12m1*a21zm2*cu20*tdu20*a12*a21zm1*a22*cv02+a12m1*a22zm1*a11m2*cu01*a21zm2*g2a*a22*cv02-a12m1*a22zm1*a11m2*cu01*a21zm2*a12*a22*gLv+4*a12m1*a22zm1*a11m2*a11*a21zm2*gLu*a22*cv02+tdu10*a21*a12m2*cv10*a22zm1*cu01*a21zm2*a12-16*tdu10*a22*a22zm1*a21zm2*cu20*a12m2*cv02*a11-tdu10*a11m2*a22*cv10*a22zm1*cu01*a21zm2*a12-4*a12m1*a21zm2*cu20*a12m2*cv02*a12*a21zm1*g1a-a12m1*cu20*a12m2*cv01*a21zm1*a21zm2*a12*g1a+4*a12m1*a21zm2*gLu*a12*a21zm1*a21*a12m2*cv02+a12m1*a21zm2*gLu*a21*a12m2*cv01*a21zm1*a12-a12m1*a21zm2*cu20*tdu20*a22*cv01*a21zm1*a12+4*a12m1*cu01*a21zm2*a12*tdu01*a21*a12m2*cv02-a12m1*a11m2*cu01*a21zm2*a12*a22*cv01*tdu01-4*a12m1*a11m2*cu01*a21zm2*a12*tdu01*a22*cv02-a12m1*a11m2*a21zm2*gLu*a22*cv01*a21zm1*a12-4*a12m1*a11m2*a21zm2*gLu*a12*a21zm1*a22*cv02+4*tdu10*a22*cu20*a12m2*cv01*a21zm1*a21zm2*a12+16*tdu10*a22*a21zm2*cu20*a12m2*cv02*a12*a21zm1-a12m1*a22zm1*a11*cv20*cu01*a22zm2*a21*tdu20-a12m1*a22zm1*a11m2*a11*cv20*cu01*a22zm2*g1a+4*a12m1*a11m2*a11*cu02*a22zm2*a22*cv01*tdu01+a12m1*a11m2*a11*cu01*a22zm2*a22*cv01*tdu01-a12m1*a11*cu01*a22zm2*a21*a12m2*cv01*tdu01+4*tdu10*a11m2*cv20*a22*a22zm1*cu01*a11*a22zm2+4*tdu10*a21*a12m2*cv10*cu02*a22zm2*a12*a21zm1+a12m1*a11*cu20*a12m2*cv01*a21zm1*a22zm2*g1a+4*a12m1*cu02*a22zm2*a12*a21zm1*a21*a12m2*gLv+4*a12m1*cu02*a22zm2*a12*a21zm1*a21*tdu20*cv20+a12m1*a11*cu20*tdu20*a22*cv01*a21zm1*a22zm2+4*a12m1*a11m2*cv20*cu02*a22zm2*a12*a21zm1*g1a-4*tdu10*a21*a12m2*cv10*a22zm1*cu02*a22zm2*a11-tdu10*a21*a12m2*cv10*a22zm1*cu01*a11*a22zm2-a12m1*a11m2*cu02*a22zm2*a22*cv01*a21zm1*g2a-4*a12m1*a11m2*cu02*a22zm2*a12*a21zm1*a22*gLv+a12m1*a11m2*a11*gLu*a22*cv01*a21zm1*a22zm2-4*tdu10*a11m2*a22*cv10*cu02*a22zm2*a12*a21zm1-16*tdu10*a11m2*cv20*a22*cu02*a22zm2*a12*a21zm1+a12m1*cu02*a22zm2*a21*a12m2*cv01*a21zm1*g2a-a12m1*a11*gLu*a21*a12m2*cv01*a21zm1*a22zm2+tdu10*a11m2*a22*cv10*a22zm1*cu01*a11*a22zm2+a12m1*a22zm1*a11m2*a11*cu01*a22zm2*a22*gLv+16*tdu10*a11m2*cv20*a22*a22zm1*cu02*a22zm2*a11+4*tdu10*a11m2*a22*cv10*a22zm1*cu02*a22zm2*a11-a12m1*a22zm1*a11*cu01*a22zm2*a21*a12m2*gLv-4*a12m1*a22zm1*a11*cu02*a22zm2*a21*a12m2*gLv-4*a12m1*a22zm1*a11m2*a11*cv20*cu02*a22zm2*g1a+4*a12m1*a22zm1*a11m2*a11*cu02*a22zm2*a22*gLv-4*a12m1*a22zm1*a11*cv20*cu02*a22zm2*a21*tdu20-4*a12m1*a11m2*cu02*tdu02*a12*a21zm1*a22*cv02-a12m1*a11m2*cu02*tdu02*a22*cv01*a21zm1*a12+4*a12m1*cu02*tdu02*a12*a21zm1*a21*a12m2*cv02+a12m1*cu02*tdu02*a21*a12m2*cv01*a21zm1*a12-4*tdu10*a22*cu20*a12m2*cv01*a21zm1*a11*a22zm2+4*a12m1*a22zm1*a11m2*a11*cu02*tdu02*a22*cv02+a12m1*a22zm1*a11m2*a11*cu01*tdu02*a22*cv02-4*a12m1*a22zm1*a11*cu02*tdu02*a21*a12m2*cv02-a12m1*a22zm1*a11*cu01*tdu02*a21*a12m2*cv02)/det

      u(i1-is1,i2,i3,ey)=(-4*a22zm1*a11m2*a11*a11m1*cu02*tdu02*a22*cv02-a22zm1*a11m2*a11*a11m1*cu01*tdu02*a22*cv02+4*a22zm1*a11*a11m1*cu02*tdu02*a21*a12m2*cv02+a22zm1*a11*a11m1*cu01*tdu02*a21*a12m2*cv02+4*a11m2*a11m1*cu02*tdu02*a12*a21zm1*a22*cv02-4*a11m1*cu02*tdu02*a12*a21zm1*a21*a12m2*cv02+a11m2*a11m1*cu02*tdu02*a22*cv01*a21zm1*a12-a11m1*cu02*tdu02*a21*a12m2*cv01*a21zm1*a12+a11*a11m1*cu01*a22zm2*a21*a12m2*cv01*tdu01+4*a11*a11m1*cu02*a22zm2*a21*a12m2*cv01*tdu01+4*a22zm1*a11*cv20*a11m1*cu02*a22zm2*a21*tdu20-4*a22zm1*a11m2*a11*a11m1*cu02*a22zm2*a22*gLv+a22zm1*a11m2*a11*cv20*a11m1*cu01*a22zm2*g1a-4*a22zm1*a11m2*a11*cv20*tdu10*a21*cu01*a22zm2-16*a22zm1*a11m2*a11*cv20*tdu10*a21*cu02*a22zm2-a22zm1*a11m2*a11*a11m1*cu01*a22zm2*a22*gLv+4*a22zm1*a11m2*a11*cv20*a11m1*cu02*a22zm2*g1a+4*a22zm1*a11*a11m1*cu02*a22zm2*a21*a12m2*gLv+a22zm1*a11*a11m1*cu01*a22zm2*a21*a12m2*gLv+a11*a11m1*gLu*a21*a12m2*cv01*a21zm1*a22zm2-4*a11m1*cu02*a22zm2*a12*a21zm1*a21*a12m2*gLv-a11m2*a11*tdu10*a22*cv01*a21zm1*a22zm2*cu10+16*a11m2*cv20*tdu10*a12*a21zm1*a21*cu02*a22zm2-a11*a11m1*cu20*a12m2*cv01*a21zm1*a22zm2*g1a+a11*tdu10*a21*a12m2*cv01*a21zm1*a22zm2*cu10+4*a11*tdu10*a21*cu20*a12m2*cv01*a21zm1*a22zm2-a11m1*cu02*a22zm2*a21*a12m2*cv01*a21zm1*g2a-a11m2*a11*a11m1*gLu*a22*cv01*a21zm1*a22zm2+4*a11m2*a11m1*cu02*a22zm2*a12*a21zm1*a22*gLv-a11*a11m1*cu20*tdu20*a22*cv01*a21zm1*a22zm2-4*a11m1*cu02*a22zm2*a12*a21zm1*a21*tdu20*cv20+a11m2*a11m1*cu02*a22zm2*a22*cv01*a21zm1*g2a-4*a11m2*cv20*a11m1*cu02*a22zm2*a12*a21zm1*g1a-4*a11m1*a21zm2*gLu*a12*a21zm1*a21*a12m2*cv02-a11m1*a21zm2*gLu*a21*a12m2*cv01*a21zm1*a12+4*a11m1*a21zm2*cu20*a12m2*cv02*a12*a21zm1*g1a+4*a11m1*a21zm2*cu20*tdu20*a12*a21zm1*a22*cv02+a11m1*a21zm2*cu20*tdu20*a22*cv01*a21zm1*a12+a11m2*a11m1*a21zm2*gLu*a22*cv01*a21zm1*a12+a22zm1*a11*cv20*a11m1*cu01*a22zm2*a21*tdu20-a11m2*a11*a11m1*cu01*a22zm2*a22*cv01*tdu01-4*a11m2*a11*a11m1*cu02*a22zm2*a22*cv01*tdu01+4*a22zm1*a11*a21zm2*tdu10*a21*a12m2*cv02*cu10+16*a22zm1*a11*a21zm2*tdu10*a21*cu20*a12m2*cv02+4*a22zm1*a11*a11m1*a21zm2*gLu*a21*a12m2*cv02-a22zm1*a11m1*cu01*a21zm2*a12*a21*a12m2*gLv-4*a22zm1*a11*a11m1*a21zm2*cu20*a12m2*cv02*g1a+a22zm1*a11m1*cu01*a21zm2*g2a*a21*a12m2*cv02-4*a22zm1*a11m2*a11*a21zm2*tdu10*a22*cv02*cu10+4*a22zm1*a11m2*cv20*a21zm2*tdu10*a21*cu01*a12+a11m1*cu20*a12m2*cv01*a21zm1*a21zm2*a12*g1a+4*a11m2*cu10*a21zm2*tdu10*a12*a21zm1*a22*cv02+4*a11m2*a11m1*a21zm2*gLu*a12*a21zm1*a22*cv02-cu10*a21zm2*tdu10*a21*a12m2*cv01*a21zm1*a12-4*a21zm2*tdu10*a21*cu20*a12m2*cv01*a21zm1*a12-4*cu10*a21zm2*tdu10*a12*a21zm1*a21*a12m2*cv02+4*a11m2*a11m1*cu01*a21zm2*a12*tdu01*a22*cv02+a11m2*a11m1*cu01*a21zm2*a12*a22*cv01*tdu01-4*a11m1*cu01*a21zm2*a12*tdu01*a21*a12m2*cv02-a11m1*cu01*a21zm2*a12*a21*a12m2*cv01*tdu01+a11m2*cu10*a21zm2*tdu10*a22*cv01*a21zm1*a12-16*a21zm2*tdu10*a12*a21zm1*a21*cu20*a12m2*cv02-a22zm1*a11m1*cu01*a21zm2*a12*a21*tdu20*cv20-a22zm1*a11m2*a11m1*cu01*a21zm2*g2a*a22*cv02-a22zm1*a11m2*cv20*a11m1*cu01*a21zm2*a12*g1a-4*a22zm1*a11m2*a11*a11m1*a21zm2*gLu*a22*cv02+a22zm1*a11m2*a11m1*cu01*a21zm2*a12*a22*gLv-4*a22zm1*a11*a11m1*a21zm2*cu20*tdu20*a22*cv02)/det

      u(i1,i2-is2,i3,ex)=(a22zm1*a11*a22zm2*cv20*a21*tdu20*cu10*a12m1-a22zm1*a11*a22zm2*a11m1*a22*cv10*cu20*tdu20+4*a22zm1*a11*a22zm2*a21*a12m1*cu20*a12m2*gLv+a22zm1*a11*a22zm2*a21*a12m2*gLv*cu10*a12m1-4*a22zm1*g2a*a11m2*cv20*a21*a12m1*cu02*a22zm2-a22zm1*a11*a22zm2*a11m2*a22*gLv*cu10*a12m1+4*a22zm1*a11*a22zm2*a11m2*cv20*a21*a12m1*gLu-4*a22zm1*a11*a22zm2*a11m2*a11m1*cv20*a22*gLu+a22zm1*a11*a22zm2*a11m2*cv20*g1a*cu10*a12m1-a22zm1*a11*a22zm2*a11m2*a11m1*a22*cv10*gLu-4*a22zm1*a11*a22zm2*a11m1*a22*cu20*a12m2*gLv-4*a22zm1*a11*a22zm2*a11m1*cv20*a22*cu20*tdu20+a22zm1*a11*a22zm2*a11m1*a21*a12m2*cv10*gLu-a22zm1*a11*a22zm2*a11m1*g1a*cu20*a12m2*cv10-a22zm1*a11*a22zm2*a11m2*a22*cv10*cu10*tdu10-4*a22zm1*a11*a22zm2*a11m2*cv20*a22*cu10*tdu10+4*a22zm1*a11*a22zm2*cv20*a21*a12m1*cu20*tdu20-16*a21zm2*a12*tdu01*a21*a12m1*cu20*a12m2*cv02+16*a21zm2*a12*tdu01*a11m1*a22*cu20*a12m2*cv02+4*a21zm2*a12*a11m1*a22*cu20*a12m2*cv01*tdu01-a21zm2*a12*a21*a12m2*cv01*tdu01*cu10*a12m1-4*a21zm2*a12*a21*a12m1*cu20*a12m2*cv01*tdu01-4*a21zm2*a12*tdu01*a21*a12m2*cv02*cu10*a12m1+a22zm1*a21zm2*a12*a11m1*g1a*cu20*a12m2*cv10+a22zm1*a21zm2*a12*a11m1*a22*cv10*cu20*tdu20+4*a22zm1*a21zm2*a12*a11m1*cv20*a22*cu20*tdu20+a21zm2*a12*a11m2*a22*cv01*tdu01*cu10*a12m1+4*a21zm2*a12*tdu01*a11m2*a22*cv02*cu10*a12m1-a22zm1*a21zm2*g2a*a11m2*a22*cv02*cu10*a12m1+4*a22zm1*a21zm2*a12*a11m2*a11m1*cv20*a22*gLu-4*a22zm1*a21zm2*g2a*a11m1*a22*cu20*a12m2*cv02-4*a22zm1*a21zm2*a12*a11m2*cv20*a21*a12m1*gLu+a22zm1*a21zm2*a12*a11m2*a11m1*a22*cv10*gLu-a22zm1*a21zm2*a12*a21*a12m2*cv10*cu10*tdu10-a22zm1*a21zm2*a12*a11m2*cv20*g1a*cu10*a12m1-4*a22zm1*a21zm2*a12*a21*a12m1*cu20*a12m2*gLv+4*a22zm1*a21zm2*a12*a11m2*cv20*a22*cu10*tdu10+a22zm1*a21zm2*a12*a11m2*a22*cv10*cu10*tdu10+4*a22zm1*a21zm2*a12*a11m1*a22*cu20*a12m2*gLv-4*a22zm1*a21zm2*a12*a21*tdu10*cu20*a12m2*cv10+a22zm1*a21zm2*a12*a11m2*a22*gLv*cu10*a12m1-a22zm1*a21zm2*a12*cv20*a21*tdu20*cu10*a12m1-4*a22zm1*a21zm2*a12*cv20*a21*a12m1*cu20*tdu20+4*a22zm1*a21zm2*g2a*a21*a12m1*cu20*a12m2*cv02-a22zm1*a21zm2*a12*a21*a12m2*gLv*cu10*a12m1+a22zm1*a21zm2*g2a*a21*a12m2*cv02*cu10*a12m1-a22zm1*a21zm2*a12*a11m1*a21*a12m2*cv10*gLu+a11*a22zm2*a21*a12m2*cv01*tdu01*cu10*a12m1-4*a11*a22zm2*a11m1*a22*cu20*a12m2*cv01*tdu01-16*a12*tdu01*a11m2*a11m1*cv20*a22*cu02*a22zm2+16*a12*tdu01*a11m2*cv20*a21*a12m1*cu02*a22zm2-4*a12*tdu01*a11m2*a11m1*a22*cv10*cu02*a22zm2+4*a12*tdu01*a11m1*a21*a12m2*cv10*cu02*a22zm2+4*a11*a22zm2*a21*a12m1*cu20*a12m2*cv01*tdu01-a22zm1*g2a*a11m1*a21*a12m2*cv10*cu02*a22zm2-a11*a22zm2*a11m2*a22*cv01*tdu01*cu10*a12m1+a22zm1*a11*a22zm2*a21*a12m2*cv10*cu10*tdu10+a22zm1*g2a*a11m2*a11m1*a22*cv10*cu02*a22zm2+4*a22zm1*a11*a22zm2*a21*tdu10*cu20*a12m2*cv10-a22zm1*a12*a11m1*a21*a12m2*cv10*cu02*tdu02+a22zm1*a12*a11m2*a11m1*a22*cv10*cu02*tdu02+4*a22zm1*a12*a11m2*a11m1*cv20*a22*cu02*tdu02-a22zm1*a11*tdu02*a11m2*a22*cv02*cu10*a12m1-4*a22zm1*a12*a11m2*cv20*a21*a12m1*cu02*tdu02+4*a22zm1*a11*tdu02*a21*a12m1*cu20*a12m2*cv02-4*a22zm1*a11*tdu02*a11m1*a22*cu20*a12m2*cv02+a22zm1*a11*tdu02*a21*a12m2*cv02*cu10*a12m1+4*a22zm1*g2a*a11m2*a11m1*cv20*a22*cu02*a22zm2)/det

      u(i1,i2-is2,i3,ey)=(-4*a21zm1*a11*a22zm2*a21*a12m1*cu20*a12m2*gLv+a21zm1*g2a*a11m1*a21*a12m2*cv10*cu02*a22zm2+4*tdu01*a21*a12m2*cv02*a21zm2*a11*cu10*a12m1-a21zm1*a21zm2*g2a*a21*a12m2*cv02*cu10*a12m1-a21zm1*a11*tdu02*a21*a12m2*cv02*cu10*a12m1+4*a21zm1*a11*tdu02*a11m1*a22*cu20*a12m2*cv02+a11m1*a21*a12m2*cv10*cu02*tdu02*a12*a21zm1-4*a21zm1*a11*tdu02*a21*a12m1*cu20*a12m2*cv02+a21zm1*a11*tdu02*a11m2*a22*cv02*cu10*a12m1+4*a11m2*cv20*a21*a12m1*cu02*tdu02*a12*a21zm1-a11m2*a11m1*a22*cv10*cu02*tdu02*a12*a21zm1-4*a11m2*a11m1*cv20*a22*cu02*tdu02*a12*a21zm1-16*tdu01*a11m2*cv20*a21*a12m1*cu02*a22zm2*a11-a21zm1*a11*a22zm2*a21*a12m2*cv10*cu10*tdu10+tdu01*a11m2*a11m1*a22*cv10*cu01*a11*a22zm2-4*tdu01*a11m2*cv20*a21*a12m1*cu01*a11*a22zm2+4*tdu01*a11m2*a11m1*a22*cv10*cu02*a22zm2*a11-4*a21zm1*a11*a22zm2*cv20*a21*a12m1*cu20*tdu20+a21zm1*a11*a22zm2*a11m1*a22*cv10*cu20*tdu20+4*a21zm1*a11*a22zm2*a11m1*cv20*a22*cu20*tdu20-a21zm1*a11*a22zm2*cv20*a21*tdu20*cu10*a12m1-4*a21zm1*a11*a22zm2*a21*tdu10*cu20*a12m2*cv10+16*tdu01*a11m2*a11m1*cv20*a22*cu02*a22zm2*a11+4*tdu01*a11m2*a11m1*cv20*a22*cu01*a11*a22zm2+a21zm1*a11*a22zm2*a11m2*a22*gLv*cu10*a12m1+4*a21zm1*a11*a22zm2*a11m2*a11m1*cv20*a22*gLu-a21zm1*g2a*a11m2*a11m1*a22*cv10*cu02*a22zm2-4*a21zm1*a11*a22zm2*a11m2*cv20*a21*a12m1*gLu-4*a21zm1*g2a*a11m2*a11m1*cv20*a22*cu02*a22zm2+a21zm1*a11*a22zm2*a11m2*a11m1*a22*cv10*gLu+4*a21zm1*g2a*a11m2*cv20*a21*a12m1*cu02*a22zm2+4*a21zm1*a11*a22zm2*a11m1*a22*cu20*a12m2*gLv+a21zm1*a11*a22zm2*a11m1*g1a*cu20*a12m2*cv10+16*tdu01*a21*a12m1*a21zm2*cu20*a12m2*cv02*a11+a11m1*a21*a12m2*cv10*cu01*a21zm2*a12*tdu01-a21zm1*a11*a22zm2*a21*a12m2*gLv*cu10*a12m1-4*tdu01*a11m2*a22*cv02*a21zm2*a11*cu10*a12m1+4*a11m2*cv20*a21*a12m1*cu01*a21zm2*a12*tdu01-16*tdu01*a11m1*a22*a21zm2*cu20*a12m2*cv02*a11+a21zm1*a11*a22zm2*a11m2*a22*cv10*cu10*tdu10-a21zm1*a11*a22zm2*a11m1*a21*a12m2*cv10*gLu+4*a21zm1*a11*a22zm2*a11m2*cv20*a22*cu10*tdu10-a21zm1*a11*a22zm2*a11m2*cv20*g1a*cu10*a12m1+a21*a12m2*gLv*a21zm2*a12*a21zm1*cu10*a12m1-4*a11m2*a11m1*cv20*a22*cu01*a21zm2*a12*tdu01-a11m2*a11m1*a22*cv10*cu01*a21zm2*a12*tdu01-a11m1*a22*cv10*a21zm2*cu20*tdu20*a12*a21zm1+4*a21*tdu10*a21zm2*a12*a21zm1*cu20*a12m2*cv10+a21*a12m2*cv10*a21zm2*cu10*tdu10*a12*a21zm1-a11m2*a11m1*a22*cv10*a21zm2*gLu*a12*a21zm1-4*a11m2*a11m1*cv20*a22*a21zm2*gLu*a12*a21zm1+cv20*a21*tdu20*a21zm2*a12*a21zm1*cu10*a12m1+4*cv20*a21*a12m1*a21zm2*cu20*tdu20*a12*a21zm1-4*a11m1*cv20*a22*a21zm2*cu20*tdu20*a12*a21zm1+4*a21zm1*a21zm2*g2a*a11m1*a22*cu20*a12m2*cv02+4*a11m2*cv20*a21*a12m1*a21zm2*gLu*a12*a21zm1-a11m2*a22*gLv*a21zm2*a12*a21zm1*cu10*a12m1-4*a11m1*a22*a21zm2*cu20*a12m2*gLv*a12*a21zm1-4*a11m2*cv20*a22*a21zm2*cu10*tdu10*a12*a21zm1+a11m2*cv20*g1a*a21zm2*a12*a21zm1*cu10*a12m1+a21zm1*a21zm2*g2a*a11m2*a22*cv02*cu10*a12m1-a11m1*g1a*a21zm2*a12*a21zm1*cu20*a12m2*cv10-a11m2*a22*cv10*a21zm2*cu10*tdu10*a12*a21zm1+4*a21*a12m1*a21zm2*cu20*a12m2*gLv*a12*a21zm1-4*a21zm1*a21zm2*g2a*a21*a12m1*cu20*a12m2*cv02+a11m1*a21*a12m2*cv10*a21zm2*gLu*a12*a21zm1-4*tdu01*a11m1*a21*a12m2*cv10*cu02*a22zm2*a11-tdu01*a11m1*a21*a12m2*cv10*cu01*a11*a22zm2)/det

      u(i1-2*is1,i2,i3,ex)=(-4*a12m2*a11m1*cu02*tdu02*a22*cv01*a21zm1*a12-16*a12m2*a11m1*cu02*tdu02*a12*a21zm1*a22*cv02+16*a12m1*cu02*tdu02*a12*a21zm1*a21*a12m2*cv02+4*a12m1*cu02*tdu02*a21*a12m2*cv01*a21zm1*a12+4*a12m2*a22zm1*a11*a11m1*cu01*tdu02*a22*cv02+16*a12m2*a22zm1*a11*a11m1*cu02*tdu02*a22*cv02-16*a12m1*a22zm1*a11*cu02*tdu02*a21*a12m2*cv02-4*a12m1*a22zm1*a11*cu01*tdu02*a21*a12m2*cv02+4*a12m1*cu01*a21zm2*a12*a21*a12m2*cv01*tdu01+16*a12m1*cu01*a21zm2*a12*tdu01*a21*a12m2*cv02-4*a12m2*a11m1*a21zm2*gLu*a22*cv01*a21zm1*a12-16*a12m2*a11m1*a21zm2*gLu*a12*a21zm1*a22*cv02+4*a12m2*cv02*g1a*a21zm2*a12*a21zm1*cu10*a12m1-4*a12m2*cu10*a21zm2*tdu10*a22*cv01*a21zm1*a12+a12m2*cv01*a21zm1*a21zm2*a12*g1a*cu10*a12m1+16*a12m2*a22zm1*a11*a21zm2*tdu10*a22*cv02*cu10-4*a12m2*a22zm1*a11m1*cu01*a21zm2*a12*a22*gLv-4*a12m2*a22zm1*cv02*g1a*a21zm2*a11*cu10*a12m1-a12m2*a22zm1*cv10*a11m1*cu01*a21zm2*a12*g1a+16*a12m2*a22zm1*a11*a11m1*a21zm2*gLu*a22*cv02-16*tdu10*a21*a12m2*cv10*a22zm1*cu02*a22zm2*a11-4*a12m1*a22zm1*a11*cu01*a22zm2*a21*a12m2*gLv-16*a12m1*a22zm1*a11*cu02*a22zm2*a21*a12m2*gLv+16*tdu20*a11m1*cv20*a22*a22zm1*cu02*a22zm2*a11+16*a12m1*cu02*a22zm2*a12*a21zm1*a21*tdu20*cv20-4*a12m1*a11*gLu*a21*a12m2*cv01*a21zm1*a22zm2-16*a12m2*a11m1*cu02*a22zm2*a12*a21zm1*a22*gLv-4*a12m2*a11m1*cu02*a22zm2*a22*cv01*a21zm1*g2a+4*a12m2*a11*a11m1*gLu*a22*cv01*a21zm1*a22zm2-4*a12m2*cv10*a11m1*cu02*a22zm2*a12*a21zm1*g1a+4*a12m1*cu02*a22zm2*a21*a12m2*cv01*a21zm1*g2a-tdu20*a22*cv01*a21zm1*a11*a22zm2*cu10*a12m1-a12m2*cv01*a21zm1*a11*a22zm2*g1a*cu10*a12m1-16*tdu20*a11m1*cv20*a22*cu02*a22zm2*a12*a21zm1-16*a12m1*a11*cu02*a22zm2*a21*a12m2*cv01*tdu01+4*a12m2*a11*a11m1*cu01*a22zm2*a22*cv01*tdu01-4*tdu20*a22zm1*a22*cv02*a21zm2*a11*cu10*a12m1+4*a12m2*a22zm1*a11m1*cu01*a21zm2*g2a*a22*cv02-16*a12m2*a11m1*cu01*a21zm2*a12*tdu01*a22*cv02-4*a12m2*a11m1*cu01*a21zm2*a12*a22*cv01*tdu01+4*a12m1*a22zm1*cu01*a21zm2*a12*a21*a12m2*gLv-16*a12m1*a22zm1*a11*a21zm2*gLu*a21*a12m2*cv02+4*a12m1*a22zm1*cu01*a21zm2*a12*a21*tdu20*cv20-4*a12m1*a22zm1*cu01*a21zm2*g2a*a21*a12m2*cv02-4*tdu20*a11m1*cv20*a22*a22zm1*cu01*a21zm2*a12-tdu20*a11m1*a22*cv10*a22zm1*cu01*a21zm2*a12+4*tdu10*a21*a12m2*cv10*a22zm1*cu01*a21zm2*a12-4*tdu20*a11m1*a22*cv10*cu02*a22zm2*a12*a21zm1-4*a12m1*a11*cu01*a22zm2*a21*a12m2*cv01*tdu01+16*a12m2*a11*a11m1*cu02*a22zm2*a22*cv01*tdu01+4*a12m2*a11*tdu10*a22*cv01*a21zm1*a22zm2*cu10+16*a12m1*cu02*a22zm2*a12*a21zm1*a21*a12m2*gLv+16*tdu10*a21*a12m2*cv10*cu02*a22zm2*a12*a21zm1-4*tdu10*a21*a12m2*cv10*a22zm1*cu01*a11*a22zm2+16*a12m2*a22zm1*a11*a11m1*cu02*a22zm2*a22*gLv+4*a12m2*a22zm1*cv10*a11*a11m1*cu02*a22zm2*g1a+4*a12m2*a22zm1*a11*a11m1*cu01*a22zm2*a22*gLv+a12m2*a22zm1*cv10*a11*a11m1*cu01*a22zm2*g1a-4*a12m1*a22zm1*a11*cv20*cu01*a22zm2*a21*tdu20-16*a12m1*a22zm1*a11*cv20*cu02*a22zm2*a21*tdu20+4*tdu20*a11m1*cv20*a22*a22zm1*cu01*a11*a22zm2+tdu20*a11m1*a22*cv10*a22zm1*cu01*a11*a22zm2+4*tdu20*a11m1*a22*cv10*a22zm1*cu02*a22zm2*a11-16*a12m2*cu10*a21zm2*tdu10*a12*a21zm1*a22*cv02+tdu20*a22*cv01*a21zm1*a21zm2*a12*cu10*a12m1+16*a12m1*a21zm2*gLu*a12*a21zm1*a21*a12m2*cv02+4*a12m1*a21zm2*gLu*a21*a12m2*cv01*a21zm1*a12+4*tdu20*a22*cv02*a21zm2*a12*a21zm1*cu10*a12m1)/det

      u(i1-2*is1,i2,i3,ey)=(4*a22zm1*cv02*a11m2*a21*a12m1*cu01*a21zm2*g2a+16*a22zm1*cv02*a11m2*a21*a12m1*cu02*tdu02*a11+4*a22zm1*cv02*a11m2*a21*a12m1*cu01*a11*tdu02-16*a22zm1*a11m2*a11*a11m1*cu02*tdu02*a22*cv02-4*cv01*a21zm1*a12*a11m2*a21*a12m1*cu02*tdu02-16*cv02*a11m2*a21*a12m1*cu02*tdu02*a12*a21zm1-4*a22zm1*a11m2*a11*a11m1*cu01*tdu02*a22*cv02+16*a11m2*a11m1*cu02*tdu02*a12*a21zm1*a22*cv02+4*a11m2*a11m1*cu02*tdu02*a22*cv01*a21zm1*a12+16*a11m2*a11m1*a21zm2*gLu*a12*a21zm1*a22*cv02+16*a11m2*cu10*a21zm2*tdu10*a12*a21zm1*a22*cv02-4*cv02*a11m2*g1a*a21zm2*a12*a21zm1*cu10*a12m1+16*a11m1*a21zm2*cu20*tdu20*a12*a21zm1*a22*cv02-4*cv01*a21zm1*a21zm2*a12*a21*a12m1*cu20*tdu20+16*cv01*tdu01*a11m2*a21*a12m1*cu02*a22zm2*a11+4*cv01*tdu01*a11m2*a21*a12m1*cu01*a11*a22zm2-16*a11m2*a11*a11m1*cu02*a22zm2*a22*cv01*tdu01-4*a11m2*a11*a11m1*cu01*a22zm2*a22*cv01*tdu01+4*a22zm1*cv02*a11m2*g1a*a21zm2*a11*cu10*a12m1-4*a22zm1*gLv*a11m2*a21*a12m1*cu01*a21zm2*a12+16*a22zm1*cv02*a11m2*a21*a12m1*a21zm2*gLu*a11-cv01*a21zm1*a21zm2*a12*a21*tdu20*cu10*a12m1+4*a11m1*a21zm2*cu20*tdu20*a22*cv01*a21zm1*a12-4*cv02*a21*tdu20*a21zm2*a12*a21zm1*cu10*a12m1-16*cv02*a21*a12m1*a21zm2*cu20*tdu20*a12*a21zm1+16*a22zm1*cv02*a21*a12m1*a21zm2*cu20*tdu20*a11+4*a11m2*cu10*a21zm2*tdu10*a22*cv01*a21zm1*a12-16*a22zm1*a11*a11m1*a21zm2*cu20*tdu20*a22*cv02+a22zm1*cv10*a11m1*cu01*a21zm2*a12*a21*tdu20+4*a11m2*a11m1*a21zm2*gLu*a22*cv01*a21zm1*a12-16*cv02*a11m2*a21*a12m1*a21zm2*gLu*a12*a21zm1-4*cv01*a21zm1*a21zm2*a12*a11m2*a21*a12m1*gLu-cv01*a21zm1*a21zm2*a12*a11m2*g1a*cu10*a12m1+4*a22zm1*cv02*a21*tdu20*a21zm2*a11*cu10*a12m1-16*a22zm1*a11m2*a11*a21zm2*tdu10*a22*cv02*cu10+16*a11m2*a11m1*cu01*a21zm2*a12*tdu01*a22*cv02+4*a22zm1*a11m2*a11m1*cu01*a21zm2*a12*a22*gLv-16*a22zm1*a11m2*a11*a11m1*a21zm2*gLu*a22*cv02-4*a22zm1*a11m2*a11m1*cu01*a21zm2*g2a*a22*cv02+a22zm1*cv10*a11m2*a11m1*cu01*a21zm2*a12*g1a-4*a22zm1*cv10*a11m2*a21zm2*tdu10*a21*cu01*a12-16*cv02*a11m2*a21*a12m1*cu01*a21zm2*a12*tdu01-4*cv01*tdu01*a11m2*a21*a12m1*cu01*a21zm2*a12+4*a11m2*a11m1*cu01*a21zm2*a12*a22*cv01*tdu01-4*a11m2*a11*tdu10*a22*cv01*a21zm1*a22zm2*cu10+4*cv01*a21zm1*a11*a22zm2*a21*a12m1*cu20*tdu20+4*cv10*a11m1*cu02*a22zm2*a12*a21zm1*a21*tdu20-4*a11*a11m1*cu20*tdu20*a22*cv01*a21zm1*a22zm2+cv01*a21zm1*a11*a22zm2*a21*tdu20*cu10*a12m1-16*a22zm1*a11m2*a11*a11m1*cu02*a22zm2*a22*gLv-4*a22zm1*cv10*a11m2*a11*a11m1*cu02*a22zm2*g1a-a22zm1*cv10*a11m2*a11*a11m1*cu01*a22zm2*g1a+16*a22zm1*cv10*a11m2*a11*tdu10*a21*cu02*a22zm2+4*a22zm1*cv10*a11m2*a11*tdu10*a21*cu01*a22zm2+4*a22zm1*gLv*a11m2*a21*a12m1*cu01*a11*a22zm2+4*cv10*a11m2*a11m1*cu02*a22zm2*a12*a21zm1*g1a+4*a11m2*a11m1*cu02*a22zm2*a22*cv01*a21zm1*g2a-16*cv10*a11m2*tdu10*a12*a21zm1*a21*cu02*a22zm2-4*a22zm1*cv10*a11*a11m1*cu02*a22zm2*a21*tdu20-a22zm1*cv10*a11*a11m1*cu01*a22zm2*a21*tdu20+4*cv01*a21zm1*a11*a22zm2*a11m2*a21*a12m1*gLu+cv01*a21zm1*a11*a22zm2*a11m2*g1a*cu10*a12m1-4*cv01*a21zm1*g2a*a11m2*a21*a12m1*cu02*a22zm2-16*gLv*a11m2*a21*a12m1*cu02*a22zm2*a12*a21zm1-4*a22zm1*a11m2*a11*a11m1*cu01*a22zm2*a22*gLv+16*a22zm1*gLv*a11m2*a21*a12m1*cu02*a22zm2*a11+16*a11m2*a11m1*cu02*a22zm2*a12*a21zm1*a22*gLv-4*a11m2*a11*a11m1*gLu*a22*cv01*a21zm1*a22zm2)/det

      u(i1,i2-2*is2,i3,ex)=(-16*a22zm1*a11*a22zm2*a11m2*cv20*a22*cu10*tdu10-4*a22zm1*a11*a22zm2*a11m2*a22*cv10*cu10*tdu10+a22zm2*a11m1*a21*a12m2*cv10*a22zm1*cu01*g2a-4*a22zm1*a11*a22zm2*a11m2*a11m1*a22*cv10*gLu+4*a22zm2*a11m1*g1a*a12*a21zm1*cu20*a12m2*cv10-4*a22zm2*a11m1*a21*a12m2*cv10*gLu*a12*a21zm1+16*a22zm2*a11m2*a11m1*cv20*a22*cu01*a12*tdu01+4*a22zm2*a11m2*a11m1*a22*cv10*cu01*a12*tdu01-16*a22zm2*a11m2*cv20*a21*a12m1*cu01*a12*tdu01-4*a11*a22zm2*a11m2*a22*cv01*tdu01*cu10*a12m1-16*a11*a22zm2*a11m1*a22*cu20*a12m2*cv01*tdu01+16*a11*a22zm2*a21*a12m1*cu20*a12m2*cv01*tdu01+4*a11*a22zm2*a21*a12m2*cv01*tdu01*cu10*a12m1-4*a22zm2*a11m1*a21*a12m2*cv10*cu01*a12*tdu01-4*a22zm1*a11*a22zm2*a11m1*a22*cv10*cu20*tdu20-16*a22zm2*a11m2*cv20*a21*a12m1*gLu*a12*a21zm1+16*a22zm2*a11m1*a22*cu20*a12m2*gLv*a12*a21zm1-16*a22zm1*a11*a22zm2*a11m2*a11m1*cv20*a22*gLu+4*a22zm1*a11*a22zm2*a11m1*a21*a12m2*cv10*gLu+16*a22zm1*a11*a22zm2*a21*tdu10*cu20*a12m2*cv10+4*a22zm1*a11*a22zm2*a21*a12m2*cv10*cu10*tdu10+4*a22zm1*a11*a22zm2*a21*a12m2*gLv*cu10*a12m1+16*a22zm1*a11*a22zm2*a21*a12m1*cu20*a12m2*gLv-16*a22zm1*a11*a22zm2*a11m1*a22*cu20*a12m2*gLv-4*a22zm1*a11*a22zm2*a11m1*g1a*cu20*a12m2*cv10+16*a22zm1*a11*a22zm2*a11m2*cv20*a21*a12m1*gLu+4*a22zm1*a11*a22zm2*a11m2*cv20*g1a*cu10*a12m1-4*a22zm1*a11*a22zm2*a11m2*a22*gLv*cu10*a12m1-a22zm2*a11m2*a11m1*a22*cv10*a22zm1*cu01*g2a-4*a22zm2*a11m2*a11m1*cv20*a22*a22zm1*cu01*g2a+4*a22zm2*a11m2*cv20*a21*a12m1*a22zm1*cu01*g2a+4*a22zm2*a11m1*a22*cv10*cu20*tdu20*a12*a21zm1+16*a22zm2*a11m1*cv20*a22*cu20*tdu20*a12*a21zm1-4*a22zm2*cv20*a21*tdu20*a12*a21zm1*cu10*a12m1-16*a22zm2*cv20*a21*a12m1*cu20*tdu20*a12*a21zm1-4*a22zm2*a21*a12m2*gLv*a12*a21zm1*cu10*a12m1-16*a22zm2*a21*tdu10*a12*a21zm1*cu20*a12m2*cv10+4*a22zm2*a11m1*a22*cu20*a12m2*cv01*a21zm1*g2a-4*a22zm2*a21*a12m1*cu20*a12m2*cv01*a21zm1*g2a-16*a22zm2*a21*a12m1*cu20*a12m2*gLv*a12*a21zm1-4*a22zm2*a21*a12m2*cv10*cu10*tdu10*a12*a21zm1+4*a22zm2*a11m2*a22*cv10*cu10*tdu10*a12*a21zm1+16*a22zm2*a11m2*cv20*a22*cu10*tdu10*a12*a21zm1-a22zm2*a21*a12m2*cv01*a21zm1*g2a*cu10*a12m1+16*a22zm1*a11*a22zm2*cv20*a21*a12m1*cu20*tdu20+4*a22zm1*a11*a22zm2*cv20*a21*tdu20*cu10*a12m1-16*a22zm1*a11*a22zm2*a11m1*cv20*a22*cu20*tdu20+4*a22zm2*a11m2*a11m1*a22*cv10*gLu*a12*a21zm1-4*a22zm2*a11m2*cv20*g1a*a12*a21zm1*cu10*a12m1+16*a22zm2*a11m2*a11m1*cv20*a22*gLu*a12*a21zm1+a22zm2*a11m2*a22*cv01*a21zm1*g2a*cu10*a12m1+4*a22zm2*a11m2*a22*gLv*a12*a21zm1*cu10*a12m1-4*tdu02*a11m2*a11m1*cv20*a22*a22zm1*cu01*a12+4*tdu02*a11m2*cv20*a21*a12m1*a22zm1*cu01*a12-tdu02*a11m2*a11m1*a22*cv10*a22zm1*cu01*a12-4*a22zm1*a11*tdu02*a11m2*a22*cv02*cu10*a12m1+tdu02*a11m1*a21*a12m2*cv10*a22zm1*cu01*a12-16*a22zm1*a11*tdu02*a11m1*a22*cu20*a12m2*cv02+4*a22zm1*a11*tdu02*a21*a12m2*cv02*cu10*a12m1+16*a22zm1*a11*tdu02*a21*a12m1*cu20*a12m2*cv02+4*tdu02*a11m2*a22*cv02*a12*a21zm1*cu10*a12m1+tdu02*a11m2*a22*cv01*a21zm1*a12*cu10*a12m1+16*tdu02*a11m1*a22*cu20*a12m2*cv02*a12*a21zm1+4*tdu02*a11m1*a22*cu20*a12m2*cv01*a21zm1*a12-4*tdu02*a21*a12m2*cv02*a12*a21zm1*cu10*a12m1-tdu02*a21*a12m2*cv01*a21zm1*a12*cu10*a12m1-4*tdu02*a21*a12m1*cu20*a12m2*cv01*a21zm1*a12-16*tdu02*a21*a12m1*cu20*a12m2*cv02*a12*a21zm1)/det

      u(i1,i2-2*is2,i3,ey)=(-16*a11m2*a11m1*cv20*a22*cu01*a21zm2*a12*tdu01+4*a11m2*a22*cv01*tdu01*a21zm2*a11*cu10*a12m1-4*a21*a12m2*cv01*tdu01*a21zm2*a11*cu10*a12m1-a11m1*a21*a12m2*cv10*a22zm1*cu01*a11*tdu02-4*a11m1*a21*a12m2*cv10*a22zm1*cu02*tdu02*a11-16*a11m2*cv20*a21*a12m1*a22zm1*cu02*tdu02*a11+a11m2*a11m1*a22*cv10*a22zm1*cu01*a11*tdu02+16*a11m2*a11m1*cv20*a22*a22zm1*cu02*tdu02*a11+4*a11m2*a11m1*a22*cv10*a22zm1*cu02*tdu02*a11+4*a11m2*a11m1*cv20*a22*a22zm1*cu01*a11*tdu02-4*a11m2*cv20*a21*a12m1*a22zm1*cu01*a11*tdu02-4*a11m1*a22*cu20*a12m2*cv01*a21zm1*a11*tdu02+4*a11m1*a21*a12m2*cv10*cu02*tdu02*a12*a21zm1+a21*a12m2*cv01*a21zm1*a11*tdu02*cu10*a12m1+4*a21*a12m1*cu20*a12m2*cv01*a21zm1*a11*tdu02+16*a11m2*cv20*a21*a12m1*cu02*tdu02*a12*a21zm1-4*a11m2*a11m1*a22*cv10*cu02*tdu02*a12*a21zm1-a11m2*a22*cv01*a21zm1*a11*tdu02*cu10*a12m1-16*a11m2*a11m1*cv20*a22*cu02*tdu02*a12*a21zm1+4*a21*a12m2*cv10*a21zm2*cu10*tdu10*a12*a21zm1+16*a21*tdu10*a21zm2*a12*a21zm1*cu20*a12m2*cv10-a11m2*a22*cv01*a21zm1*a21zm2*g2a*cu10*a12m1-16*a11m1*a22*a21zm2*cu20*a12m2*gLv*a12*a21zm1+4*a11m1*a21*a12m2*cv10*a21zm2*gLu*a12*a21zm1-4*a11m1*g1a*a21zm2*a12*a21zm1*cu20*a12m2*cv10-4*a11m1*a22*cu20*a12m2*cv01*a21zm1*a21zm2*g2a+16*a21*a12m1*a21zm2*cu20*a12m2*gLv*a12*a21zm1+4*a21*a12m2*gLv*a21zm2*a12*a21zm1*cu10*a12m1+16*cv20*a21*a12m1*a21zm2*cu20*tdu20*a12*a21zm1+a21*a12m2*cv01*a21zm1*a21zm2*g2a*cu10*a12m1+4*a21*a12m1*cu20*a12m2*cv01*a21zm1*a21zm2*g2a-4*a11m1*a22*cv10*a21zm2*cu20*tdu20*a12*a21zm1-16*a11m1*cv20*a22*a21zm2*cu20*tdu20*a12*a21zm1+4*cv20*a21*tdu20*a21zm2*a12*a21zm1*cu10*a12m1+4*a11m2*a22zm1*a22*gLv*a21zm2*a11*cu10*a12m1+a11m2*a11m1*a22*cv10*a22zm1*cu01*a21zm2*g2a+16*a11m2*cv20*a22*a22zm1*a21zm2*cu10*tdu10*a11-4*a11m2*cv20*a22zm1*g1a*a21zm2*a11*cu10*a12m1-4*a11m2*cv20*a21*a12m1*a22zm1*cu01*a21zm2*g2a-4*a21*a12m2*cv10*a22zm1*a21zm2*cu10*tdu10*a11-16*a22zm1*a21*tdu10*a21zm2*a11*cu20*a12m2*cv10+16*a11m2*a11m1*cv20*a22*a22zm1*a21zm2*gLu*a11-4*a22zm1*a21*a12m2*gLv*a21zm2*a11*cu10*a12m1+4*a11m2*a11m1*cv20*a22*a22zm1*cu01*a21zm2*g2a+4*a11m2*a22*cv10*a22zm1*a21zm2*cu10*tdu10*a11+4*a11m2*a11m1*a22*cv10*a22zm1*a21zm2*gLu*a11-a11m1*a21*a12m2*cv10*a22zm1*cu01*a21zm2*g2a+4*a11m1*a22zm1*g1a*a21zm2*a11*cu20*a12m2*cv10-4*a11m1*a21*a12m2*cv10*a22zm1*a21zm2*gLu*a11-16*a11m2*cv20*a22*a21zm2*cu10*tdu10*a12*a21zm1+16*a11m2*cv20*a21*a12m1*a21zm2*gLu*a12*a21zm1+4*a11m1*a22*cv10*a22zm1*a21zm2*cu20*tdu20*a11+16*a11m1*cv20*a22*a22zm1*a21zm2*cu20*tdu20*a11-4*cv20*a22zm1*a21*tdu20*a21zm2*a11*cu10*a12m1+4*a11m2*cv20*g1a*a21zm2*a12*a21zm1*cu10*a12m1-16*cv20*a21*a12m1*a22zm1*a21zm2*cu20*tdu20*a11+16*a11m1*a22*a22zm1*a21zm2*cu20*a12m2*gLv*a11-16*a21*a12m1*a22zm1*a21zm2*cu20*a12m2*gLv*a11-16*a11m2*cv20*a21*a12m1*a22zm1*a21zm2*gLu*a11-16*a21*a12m1*a21zm2*cu20*a12m2*cv01*tdu01*a11+16*a11m1*a22*a21zm2*cu20*a12m2*cv01*tdu01*a11+4*a11m1*a21*a12m2*cv10*cu01*a21zm2*a12*tdu01-4*a11m2*a11m1*a22*cv10*a21zm2*gLu*a12*a21zm1-16*a11m2*a11m1*cv20*a22*a21zm2*gLu*a12*a21zm1-4*a11m2*a22*cv10*a21zm2*cu10*tdu10*a12*a21zm1-4*a11m2*a22*gLv*a21zm2*a12*a21zm1*cu10*a12m1+16*a11m2*cv20*a21*a12m1*cu01*a21zm2*a12*tdu01-4*a11m2*a11m1*a22*cv10*cu01*a21zm2*a12*tdu01)/det



! ****************** done fourth-order ********************
