      t2 = cc ** 2
      t5 = rx(i + 1,j,0,0) * rx(i + 1,j,1,1) - rx(i + 1,j,1,0) * rx(i + 
     #1,j,0,1)
      t6 = 0.1D1 / t5
      t7 = rx(i + 1,j,0,0) ** 2
      t8 = rx(i + 1,j,0,1) ** 2
      t10 = t6 * (t7 + t8)
      t13 = rx(i,j,0,0) * rx(i,j,1,1) - rx(i,j,1,0) * rx(i,j,0,1)
      t14 = 0.1D1 / t13
      t15 = rx(i,j,0,0) ** 2
      t16 = rx(i,j,0,1) ** 2
      t18 = t14 * (t15 + t16)
      t19 = t10 + t18
      t20 = t2 * t19 / 0.2D1
      t22 = 0.1D1 / dx
      t23 = (u(i + 1,j,n) - u(i,j,n)) * t22
      t24 = t20 * t23
      t25 = ut(i + 1,j,n) - ut(i,j,n)
      t34 = 0.1D1 / (rx(i + 2,j,0,0) * rx(i + 2,j,1,1) - rx(i + 2,j,1,0)
     # * rx(i + 2,j,0,1))
      t35 = rx(i + 2,j,0,0) ** 2
      t36 = rx(i + 2,j,0,1) ** 2
      t42 = (u(i + 2,j,n) - u(i + 1,j,n)) * t22
      t51 = 0.1D1 / dy
      t58 = t2 * t6
      t61 = rx(i + 1,j,0,0) * rx(i + 1,j,1,0) + rx(i + 1,j,0,1) * rx(i +
     # 1,j,1,1)
      t63 = (u(i + 1,j + 1,n) - u(i + 1,j,n)) * t51
      t65 = (u(i + 1,j,n) - u(i + 1,j - 1,n)) * t51
      t68 = t58 * t61 * (t63 + t65) / 0.2D1
      t72 = t2 * t14
      t75 = rx(i,j,0,0) * rx(i,j,1,0) + rx(i,j,0,1) * rx(i,j,1,1)
      t77 = (u(i,j + 1,n) - u(i,j,n)) * t51
      t79 = (u(i,j,n) - u(i,j - 1,n)) * t51
      t82 = t72 * t75 * (t77 + t79) / 0.2D1
      t85 = (t68 - t82) * t22 / 0.2D1
      t89 = 0.1D1 / (rx(i + 1,j + 1,0,0) * rx(i + 1,j + 1,1,1) - rx(i + 
     #1,j + 1,1,0) * rx(i + 1,j + 1,0,1))
      t90 = t2 * t89
      t93 = rx(i + 1,j + 1,0,0) * rx(i + 1,j + 1,1,0) + rx(i + 1,j + 1,0
     #,1) * rx(i + 1,j + 1,1,1)
      t97 = (u(i + 1,j + 1,n) - u(i,j + 1,n)) * t22
      t103 = t58 * t61 * (t42 + t23) / 0.2D1
      t110 = 0.1D1 / (rx(i + 1,j - 1,0,0) * rx(i + 1,j - 1,1,1) - rx(i +
     # 1,j - 1,1,0) * rx(i + 1,j - 1,0,1))
      t111 = t2 * t110
      t114 = rx(i + 1,j - 1,0,0) * rx(i + 1,j - 1,1,0) + rx(i + 1,j - 1,
     #0,1) * rx(i + 1,j - 1,1,1)
      t118 = (u(i + 1,j - 1,n) - u(i,j - 1,n)) * t22
      t125 = rx(i + 1,j + 1,1,0) ** 2
      t126 = rx(i + 1,j + 1,1,1) ** 2
      t129 = rx(i + 1,j,1,0) ** 2
      t130 = rx(i + 1,j,1,1) ** 2
      t132 = t6 * (t129 + t130)
      t136 = rx(i + 1,j - 1,1,0) ** 2
      t137 = rx(i + 1,j - 1,1,1) ** 2
      t151 = t25 * t22
      t157 = rx(i - 1,j,0,0) * rx(i - 1,j,1,1) - rx(i - 1,j,1,0) * rx(i 
     #- 1,j,0,1)
      t158 = 0.1D1 / t157
      t159 = rx(i - 1,j,0,0) ** 2
      t160 = rx(i - 1,j,0,1) ** 2
      t162 = t158 * (t159 + t160)
      t163 = t18 + t162
      t164 = t2 * t163 / 0.2D1
      t166 = (u(i,j,n) - u(i - 1,j,n)) * t22
      t167 = t164 * t166
      t170 = t2 * t158
      t173 = rx(i - 1,j,0,0) * rx(i - 1,j,1,0) + rx(i - 1,j,0,1) * rx(i 
     #- 1,j,1,1)
      t175 = (u(i - 1,j + 1,n) - u(i - 1,j,n)) * t51
      t177 = (u(i - 1,j,n) - u(i - 1,j - 1,n)) * t51
      t180 = t170 * t173 * (t175 + t177) / 0.2D1
      t183 = (t82 - t180) * t22 / 0.2D1
      t186 = rx(i,j + 1,0,0) * rx(i,j + 1,1,1) - rx(i,j + 1,1,0) * rx(i,
     #j + 1,0,1)
      t187 = 0.1D1 / t186
      t188 = t2 * t187
      t191 = rx(i,j + 1,0,0) * rx(i,j + 1,1,0) + rx(i,j + 1,0,1) * rx(i,
     #j + 1,1,1)
      t193 = (u(i,j + 1,n) - u(i - 1,j + 1,n)) * t22
      t196 = t188 * t191 * (t97 + t193) / 0.2D1
      t199 = t72 * t75 * (t23 + t166) / 0.2D1
      t202 = (t196 - t199) * t51 / 0.2D1
      t205 = rx(i,j - 1,0,0) * rx(i,j - 1,1,1) - rx(i,j - 1,1,0) * rx(i,
     #j - 1,0,1)
      t206 = 0.1D1 / t205
      t207 = t2 * t206
      t210 = rx(i,j - 1,0,0) * rx(i,j - 1,1,0) + rx(i,j - 1,0,1) * rx(i,
     #j - 1,1,1)
      t212 = (u(i,j - 1,n) - u(i - 1,j - 1,n)) * t22
      t215 = t207 * t210 * (t118 + t212) / 0.2D1
      t218 = (t199 - t215) * t51 / 0.2D1
      t219 = rx(i,j + 1,1,0) ** 2
      t220 = rx(i,j + 1,1,1) ** 2
      t222 = t187 * (t219 + t220)
      t223 = rx(i,j,1,0) ** 2
      t224 = rx(i,j,1,1) ** 2
      t226 = t14 * (t223 + t224)
      t227 = t222 + t226
      t228 = t2 * t227 / 0.2D1
      t229 = t228 * t77
      t230 = rx(i,j - 1,1,0) ** 2
      t231 = rx(i,j - 1,1,1) ** 2
      t233 = t206 * (t230 + t231)
      t234 = t226 + t233
      t235 = t2 * t234 / 0.2D1
      t236 = t235 * t79
      t242 = dt * ((t24 - t167) * t22 + t85 + t183 + t202 + t218 + (t229
     # - t236) * t51) * t13 / 0.2D1
      t243 = ut(i,j,n) - ut(i - 1,j,n)
      t244 = t243 * t22
      t247 = dx * (t151 + t244) / 0.4D1
      t254 = t24 + t20 * dt * t25 * t22 / 0.2D1 + cc * t19 * (ut(i + 1,j
     #,n) + dt * ((t2 * (t34 * (t35 + t36) + t10) * t42 / 0.2D1 - t24) *
     # t22 + (t2 * t34 * (rx(i + 2,j,0,0) * rx(i + 2,j,1,0) + rx(i + 2,j
     #,0,1) * rx(i + 2,j,1,1)) * ((u(i + 2,j + 1,n) - u(i + 2,j,n)) * t5
     #1 + (u(i + 2,j,n) - u(i + 2,j - 1,n)) * t51) / 0.2D1 - t68) * t22 
     #/ 0.2D1 + t85 + (t90 * t93 * ((u(i + 2,j + 1,n) - u(i + 1,j + 1,n)
     #) * t22 + t97) / 0.2D1 - t103) * t51 / 0.2D1 + (t103 - t111 * t114
     # * ((u(i + 2,j - 1,n) - u(i + 1,j - 1,n)) * t22 + t118) / 0.2D1) *
     # t51 / 0.2D1 + (t2 * (t89 * (t125 + t126) + t132) * t63 / 0.2D1 - 
     #t2 * (t132 + t110 * (t136 + t137)) * t65 / 0.2D1) * t51) * t5 / 0.
     #2D1 - dx * ((ut(i + 2,j,n) - ut(i + 1,j,n)) * t22 + t151) / 0.4D1 
     #- ut(i,j,n) - t242 - t247) * sqrt(0.2D1) * (t7 + t8 + t15 + t16) *
     #* (-0.1D1 / 0.2D1) / 0.4D1
      t255 = dt ** 2
      t258 = t14 * t75
      t260 = t2 * (t6 * t61 + t258) / 0.2D1
      t267 = ut(i,j + 1,n) - ut(i,j,n)
      t268 = t267 * t51
      t269 = ut(i,j,n) - ut(i,j - 1,n)
      t270 = t269 * t51
      t275 = t260 * (t63 + t65 + t77 + t79) / 0.4D1 + t260 * dt * ((ut(i
     # + 1,j + 1,n) - ut(i + 1,j,n)) * t51 + (ut(i + 1,j,n) - ut(i + 1,j
     # - 1,n)) * t51 + t268 + t270) / 0.8D1
      t285 = 0.1D1 / (rx(i - 2,j,0,0) * rx(i - 2,j,1,1) - rx(i - 2,j,1,0
     #) * rx(i - 2,j,0,1))
      t286 = rx(i - 2,j,0,0) ** 2
      t287 = rx(i - 2,j,0,1) ** 2
      t293 = (u(i - 1,j,n) - u(i - 2,j,n)) * t22
      t314 = 0.1D1 / (rx(i - 1,j + 1,0,0) * rx(i - 1,j + 1,1,1) - rx(i -
     # 1,j + 1,1,0) * rx(i - 1,j + 1,0,1))
      t315 = t2 * t314
      t318 = rx(i - 1,j + 1,0,0) * rx(i - 1,j + 1,1,0) + rx(i - 1,j + 1,
     #0,1) * rx(i - 1,j + 1,1,1)
      t326 = t170 * t173 * (t166 + t293) / 0.2D1
      t333 = 0.1D1 / (rx(i - 1,j - 1,0,0) * rx(i - 1,j - 1,1,1) - rx(i -
     # 1,j - 1,1,0) * rx(i - 1,j - 1,0,1))
      t334 = t2 * t333
      t337 = rx(i - 1,j - 1,0,0) * rx(i - 1,j - 1,1,0) + rx(i - 1,j - 1,
     #0,1) * rx(i - 1,j - 1,1,1)
      t346 = rx(i - 1,j + 1,1,0) ** 2
      t347 = rx(i - 1,j + 1,1,1) ** 2
      t350 = rx(i - 1,j,1,0) ** 2
      t351 = rx(i - 1,j,1,1) ** 2
      t353 = t158 * (t350 + t351)
      t357 = rx(i - 1,j - 1,1,0) ** 2
      t358 = rx(i - 1,j - 1,1,1) ** 2
      t381 = t167 + t164 * dt * t243 * t22 / 0.2D1 + cc * t163 * (ut(i,j
     #,n) + t242 - t247 - ut(i - 1,j,n) - dt * ((t167 - t2 * (t162 + t28
     #5 * (t286 + t287)) * t293 / 0.2D1) * t22 + t183 + (t180 - t2 * t28
     #5 * (rx(i - 2,j,0,0) * rx(i - 2,j,1,0) + rx(i - 2,j,0,1) * rx(i - 
     #2,j,1,1)) * ((u(i - 2,j + 1,n) - u(i - 2,j,n)) * t51 + (u(i - 2,j,
     #n) - u(i - 2,j - 1,n)) * t51) / 0.2D1) * t22 / 0.2D1 + (t315 * t31
     #8 * (t193 + (u(i - 1,j + 1,n) - u(i - 2,j + 1,n)) * t22) / 0.2D1 -
     # t326) * t51 / 0.2D1 + (t326 - t334 * t337 * (t212 + (u(i - 1,j - 
     #1,n) - u(i - 2,j - 1,n)) * t22) / 0.2D1) * t51 / 0.2D1 + (t2 * (t3
     #14 * (t346 + t347) + t353) * t175 / 0.2D1 - t2 * (t353 + t333 * (t
     #357 + t358)) * t177 / 0.2D1) * t51) * t157 / 0.2D1 - dx * (t244 + 
     #(ut(i - 1,j,n) - ut(i - 2,j,n)) * t22) / 0.4D1) * sqrt(0.2D1) * (t
     #15 + t16 + t159 + t160) ** (-0.1D1 / 0.2D1) / 0.4D1
      t385 = t2 * (t258 + t158 * t173) / 0.2D1
      t396 = t385 * (t77 + t79 + t175 + t177) / 0.4D1 + t385 * dt * (t26
     #8 + t270 + (ut(i - 1,j + 1,n) - ut(i - 1,j,n)) * t51 + (ut(i - 1,j
     #,n) - ut(i - 1,j - 1,n)) * t51) / 0.8D1
      t403 = t2 * (t187 * t191 + t258) / 0.2D1
      t414 = t403 * (t97 + t193 + t23 + t166) / 0.4D1 + t403 * dt * ((ut
     #(i + 1,j + 1,n) - ut(i,j + 1,n)) * t22 + (ut(i,j + 1,n) - ut(i - 1
     #,j + 1,n)) * t22 + t151 + t244) / 0.8D1
      t421 = rx(i + 1,j + 1,0,0) ** 2
      t422 = rx(i + 1,j + 1,0,1) ** 2
      t425 = rx(i,j + 1,0,0) ** 2
      t426 = rx(i,j + 1,0,1) ** 2
      t428 = t187 * (t425 + t426)
      t432 = rx(i - 1,j + 1,0,0) ** 2
      t433 = rx(i - 1,j + 1,0,1) ** 2
      t447 = (u(i,j + 2,n) - u(i,j + 1,n)) * t51
      t450 = t188 * t191 * (t447 + t77) / 0.2D1
      t465 = 0.1D1 / (rx(i,j + 2,0,0) * rx(i,j + 2,1,1) - rx(i,j + 2,1,0
     #) * rx(i,j + 2,0,1))
      t480 = rx(i,j + 2,1,0) ** 2
      t481 = rx(i,j + 2,1,1) ** 2
      t500 = dy * (t268 + t270) / 0.4D1
      t507 = t229 + t228 * dt * t267 * t51 / 0.2D1 + cc * t227 * (ut(i,j
     # + 1,n) + dt * ((t2 * (t89 * (t421 + t422) + t428) * t97 / 0.2D1 -
     # t2 * (t428 + t314 * (t432 + t433)) * t193 / 0.2D1) * t22 + (t90 *
     # t93 * ((u(i + 1,j + 2,n) - u(i + 1,j + 1,n)) * t51 + t63) / 0.2D1
     # - t450) * t22 / 0.2D1 + (t450 - t315 * t318 * ((u(i - 1,j + 2,n) 
     #- u(i - 1,j + 1,n)) * t51 + t175) / 0.2D1) * t22 / 0.2D1 + (t2 * t
     #465 * (rx(i,j + 2,0,0) * rx(i,j + 2,1,0) + rx(i,j + 2,0,1) * rx(i,
     #j + 2,1,1)) * ((u(i + 1,j + 2,n) - u(i,j + 2,n)) * t22 + (u(i,j + 
     #2,n) - u(i - 1,j + 2,n)) * t22) / 0.2D1 - t196) * t51 / 0.2D1 + t2
     #02 + (t2 * (t465 * (t480 + t481) + t222) * t447 / 0.2D1 - t229) * 
     #t51) * t186 / 0.2D1 - dy * ((ut(i,j + 2,n) - ut(i,j + 1,n)) * t51 
     #+ t268) / 0.4D1 - ut(i,j,n) - t242 - t500) * sqrt(0.2D1) * (t219 +
     # t220 + t223 + t224) ** (-0.1D1 / 0.2D1) / 0.4D1
      t511 = t2 * (t258 + t206 * t210) / 0.2D1
      t522 = t511 * (t23 + t166 + t118 + t212) / 0.4D1 + t511 * dt * (t1
     #51 + t244 + (ut(i + 1,j - 1,n) - ut(i,j - 1,n)) * t22 + (ut(i,j - 
     #1,n) - ut(i - 1,j - 1,n)) * t22) / 0.8D1
      t529 = rx(i + 1,j - 1,0,0) ** 2
      t530 = rx(i + 1,j - 1,0,1) ** 2
      t533 = rx(i,j - 1,0,0) ** 2
      t534 = rx(i,j - 1,0,1) ** 2
      t536 = t206 * (t533 + t534)
      t540 = rx(i - 1,j - 1,0,0) ** 2
      t541 = rx(i - 1,j - 1,0,1) ** 2
      t555 = (u(i,j - 1,n) - u(i,j - 2,n)) * t51
      t558 = t207 * t210 * (t79 + t555) / 0.2D1
      t573 = 0.1D1 / (rx(i,j - 2,0,0) * rx(i,j - 2,1,1) - rx(i,j - 2,1,0
     #) * rx(i,j - 2,0,1))
      t588 = rx(i,j - 2,1,0) ** 2
      t589 = rx(i,j - 2,1,1) ** 2
      t612 = t236 + t235 * dt * t269 * t51 / 0.2D1 + cc * t234 * (ut(i,j
     #,n) + t242 - t500 - ut(i,j - 1,n) - dt * ((t2 * (t110 * (t529 + t5
     #30) + t536) * t118 / 0.2D1 - t2 * (t536 + t333 * (t540 + t541)) * 
     #t212 / 0.2D1) * t22 + (t111 * t114 * (t65 + (u(i + 1,j - 1,n) - u(
     #i + 1,j - 2,n)) * t51) / 0.2D1 - t558) * t22 / 0.2D1 + (t558 - t33
     #4 * t337 * (t177 + (u(i - 1,j - 1,n) - u(i - 1,j - 2,n)) * t51) / 
     #0.2D1) * t22 / 0.2D1 + t218 + (t215 - t2 * t573 * (rx(i,j - 2,0,0)
     # * rx(i,j - 2,1,0) + rx(i,j - 2,0,1) * rx(i,j - 2,1,1)) * ((u(i + 
     #1,j - 2,n) - u(i,j - 2,n)) * t22 + (u(i,j - 2,n) - u(i - 1,j - 2,n
     #)) * t22) / 0.2D1) * t51 / 0.2D1 + (t236 - t2 * (t233 + t573 * (t5
     #88 + t589)) * t555 / 0.2D1) * t51) * t205 / 0.2D1 - dy * (t270 + (
     #ut(i,j - 1,n) - ut(i,j - 2,n)) * t51) / 0.4D1) * sqrt(0.2D1) * (t2
     #23 + t224 + t230 + t231) ** (-0.1D1 / 0.2D1) / 0.4D1
      cg(1,1) = u(i,j,n) + dt * ut(i,j,n) + (t254 * t255 + t275 * t255 -
     # t381 * t255 - t396 * t255) * t13 * t22 / 0.2D1 + (t414 * t255 + t
     #507 * t255 - t522 * t255 - t612 * t255) * t13 * t51 / 0.2D1
      cg(2,1) = ut(i,j,n) + (t254 * dt + t275 * dt - t381 * dt - t396 * 
     #dt) * t13 * t22 + (t414 * dt + t507 * dt - t522 * dt - t612 * dt) 
     #* t13 * t51
