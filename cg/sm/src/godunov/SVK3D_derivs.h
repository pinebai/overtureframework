      t1 = f(1,1) ** 2
      t2 = lambda * t1
      t4 = mu * t1
      t6 = f(2,1) ** 2
      t7 = lambda * t6
      t8 = t7 / 0.2E1
      t9 = f(3,1) ** 2
      t10 = lambda * t9
      t11 = t10 / 0.2E1
      t12 = 0.3E1 / 0.2E1 * lambda
      t13 = f(1,2) ** 2
      t14 = lambda * t13
      t15 = t14 / 0.2E1
      t16 = f(2,2) ** 2
      t17 = lambda * t16
      t18 = t17 / 0.2E1
      t19 = f(3,2) ** 2
      t20 = lambda * t19
      t21 = t20 / 0.2E1
      t22 = f(1,3) ** 2
      t23 = lambda * t22
      t24 = t23 / 0.2E1
      t25 = f(2,3) ** 2
      t26 = lambda * t25
      t27 = t26 / 0.2E1
      t28 = f(3,3) ** 2
      t29 = lambda * t28
      t30 = t29 / 0.2E1
      t31 = mu * t6
      t32 = mu * t9
      t33 = mu * t13
      t34 = mu * t22
      t35 = 0.3E1 / 0.2E1 * t2 + 0.3E1 * t4 + t8 + t11 - t12 + t15 + t18
     # + t21 + t24 + t27 + t30 + t31 + t32 - mu + t33 + t34
      t36 = lambda * f(1,2)
      t38 = mu * f(1,1)
      t39 = t38 * f(1,2)
      t41 = mu * f(2,1)
      t42 = t41 * f(2,2)
      t43 = mu * f(3,1)
      t44 = t43 * f(3,2)
      t45 = t36 * f(1,1) + 0.2E1 * t39 + t42 + t44
      t46 = lambda * f(1,3)
      t48 = t38 * f(1,3)
      t50 = t41 * f(2,3)
      t51 = t43 * f(3,3)
      t52 = t46 * f(1,1) + 0.2E1 * t48 + t50 + t51
      t53 = f(1,1) * lambda
      t55 = t38 * f(2,1)
      t57 = mu * f(2,2)
      t58 = t57 * f(1,2)
      t60 = mu * f(2,3) * f(1,3)
      t61 = t53 * f(2,1) + 0.2E1 * t55 + t58 + t60
      t62 = lambda * f(2,2)
      t65 = t62 * f(1,1) + t41 * f(1,2)
      t66 = lambda * f(2,3)
      t69 = t66 * f(1,1) + t41 * f(1,3)
      t71 = t38 * f(3,1)
      t73 = mu * f(3,2)
      t74 = t73 * f(1,2)
      t75 = mu * f(3,3)
      t76 = t75 * f(1,3)
      t77 = t53 * f(3,1) + 0.2E1 * t71 + t74 + t76
      t78 = lambda * f(3,2)
      t81 = t78 * f(1,1) + t43 * f(1,2)
      t82 = lambda * f(3,3)
      t85 = t82 * f(1,1) + t43 * f(1,3)
      t88 = t36 * f(2,1) + t38 * f(2,2)
      t91 = t46 * f(2,1) + t38 * f(2,3)
      t94 = t2 / 0.2E1
      t95 = mu * t16
      t96 = mu * t25
      t97 = 0.3E1 / 0.2E1 * t7 + 0.3E1 * t31 + t94 + t11 - t12 + t15 + t
     #18 + t21 + t24 + t27 + t30 + t4 + t32 - mu + t95 + t96
      t100 = t62 * f(2,1) + 0.2E1 * t42 + t39 + t44
      t103 = t66 * f(2,1) + 0.2E1 * t50 + t48 + t51
      t106 = t41 * f(3,1)
      t108 = t73 * f(2,2)
      t109 = t75 * f(2,3)
      t110 = f(2,1) * lambda * f(3,1) + 0.2E1 * t106 + t108 + t109
      t113 = t78 * f(2,1) + t43 * f(2,2)
      t116 = t82 * f(2,1) + t43 * f(2,3)
      t119 = t36 * f(3,1) + t38 * f(3,2)
      t122 = t46 * f(3,1) + t38 * f(3,3)
      t125 = t62 * f(3,1) + t41 * f(3,2)
      t128 = t66 * f(3,1) + t41 * f(3,3)
      t131 = mu * t19
      t132 = mu * t28
      t133 = 0.3E1 / 0.2E1 * t10 + 0.3E1 * t32 + t94 + t8 - t12 + t15 + 
     #t18 + t21 + t24 + t27 + t30 + t4 + t31 - mu + t131 + t132
      t136 = t78 * f(3,1) + 0.2E1 * t44 + t39 + t42
      t139 = t82 * f(3,1) + 0.2E1 * t51 + t48 + t50
      t142 = t4 + 0.3E1 / 0.2E1 * t14 + 0.3E1 * t33 + t94 + t8 + t11 - t
     #12 + t18 + t21 + t24 + t27 + t30 + t95 + t131 - mu + t34
      t144 = mu * f(1,2)
      t145 = t144 * f(1,3)
      t147 = t57 * f(2,3)
      t148 = t73 * f(3,3)
      t149 = t46 * f(1,2) + 0.2E1 * t145 + t147 + t148
      t152 = t55 + t36 * f(2,2) + 0.2E1 * t58 + t60
      t155 = t66 * f(1,2) + t57 * f(1,3)
      t158 = t71 + t36 * f(3,2) + 0.2E1 * t74 + t76
      t161 = t82 * f(1,2) + t73 * f(1,3)
      t164 = t46 * f(2,2) + t144 * f(2,3)
      t167 = t31 + 0.3E1 / 0.2E1 * t17 + 0.3E1 * t95 + t94 + t8 + t11 - 
     #t12 + t15 + t21 + t24 + t27 + t30 + t33 + t131 - mu + t96
      t170 = t66 * f(2,2) + 0.2E1 * t147 + t145 + t148
      t173 = t106 + t62 * f(3,2) + 0.2E1 * t108 + t109
      t176 = t82 * f(2,2) + t73 * f(2,3)
      t179 = t46 * f(3,2) + t144 * f(3,3)
      t182 = t66 * f(3,2) + t57 * f(3,3)
      t185 = t32 + 0.3E1 / 0.2E1 * t20 + 0.3E1 * t131 + t94 + t8 + t11 -
     # t12 + t15 + t18 + t24 + t27 + t30 + t33 + t95 - mu + t132
      t188 = t82 * f(3,2) + 0.2E1 * t148 + t145 + t147
      t191 = t4 + t33 + 0.3E1 / 0.2E1 * t23 + 0.3E1 * t34 + t94 + t8 + t
     #11 - t12 + t15 + t18 + t21 + t27 + t30 + t96 + t132 - mu
      t194 = t55 + t58 + t46 * f(2,3) + 0.2E1 * t60
      t197 = t71 + t74 + t46 * f(3,3) + 0.2E1 * t76
      t200 = t31 + t95 + 0.3E1 / 0.2E1 * t26 + 0.3E1 * t96 + t94 + t8 + 
     #t11 - t12 + t15 + t18 + t21 + t24 + t30 + t34 + t132 - mu
      t203 = t106 + t108 + t66 * f(3,3) + 0.2E1 * t109
      t206 = t32 + t131 + 0.3E1 / 0.2E1 * t29 + 0.3E1 * t132 + t94 + t8 
     #+ t11 - t12 + t15 + t18 + t21 + t24 + t27 + t34 + t96 - mu
      dpdf(1,1,1,1) = t35
      dpdf(1,1,1,2) = t45
      dpdf(1,1,1,3) = t52
      dpdf(1,1,2,1) = t61
      dpdf(1,1,2,2) = t65
      dpdf(1,1,2,3) = t69
      dpdf(1,1,3,1) = t77
      dpdf(1,1,3,2) = t81
      dpdf(1,1,3,3) = t85
      dpdf(1,2,1,1) = t61
      dpdf(1,2,1,2) = t88
      dpdf(1,2,1,3) = t91
      dpdf(1,2,2,1) = t97
      dpdf(1,2,2,2) = t100
      dpdf(1,2,2,3) = t103
      dpdf(1,2,3,1) = t110
      dpdf(1,2,3,2) = t113
      dpdf(1,2,3,3) = t116
      dpdf(1,3,1,1) = t77
      dpdf(1,3,1,2) = t119
      dpdf(1,3,1,3) = t122
      dpdf(1,3,2,1) = t110
      dpdf(1,3,2,2) = t125
      dpdf(1,3,2,3) = t128
      dpdf(1,3,3,1) = t133
      dpdf(1,3,3,2) = t136
      dpdf(1,3,3,3) = t139
      dpdf(2,1,1,1) = t45
      dpdf(2,1,1,2) = t142
      dpdf(2,1,1,3) = t149
      dpdf(2,1,2,1) = t88
      dpdf(2,1,2,2) = t152
      dpdf(2,1,2,3) = t155
      dpdf(2,1,3,1) = t119
      dpdf(2,1,3,2) = t158
      dpdf(2,1,3,3) = t161
      dpdf(2,2,1,1) = t65
      dpdf(2,2,1,2) = t152
      dpdf(2,2,1,3) = t164
      dpdf(2,2,2,1) = t100
      dpdf(2,2,2,2) = t167
      dpdf(2,2,2,3) = t170
      dpdf(2,2,3,1) = t125
      dpdf(2,2,3,2) = t173
      dpdf(2,2,3,3) = t176
      dpdf(2,3,1,1) = t81
      dpdf(2,3,1,2) = t158
      dpdf(2,3,1,3) = t179
      dpdf(2,3,2,1) = t113
      dpdf(2,3,2,2) = t173
      dpdf(2,3,2,3) = t182
      dpdf(2,3,3,1) = t136
      dpdf(2,3,3,2) = t185
      dpdf(2,3,3,3) = t188
      dpdf(3,1,1,1) = t52
      dpdf(3,1,1,2) = t149
      dpdf(3,1,1,3) = t191
      dpdf(3,1,2,1) = t91
      dpdf(3,1,2,2) = t164
      dpdf(3,1,2,3) = t194
      dpdf(3,1,3,1) = t122
      dpdf(3,1,3,2) = t179
      dpdf(3,1,3,3) = t197
      dpdf(3,2,1,1) = t69
      dpdf(3,2,1,2) = t155
      dpdf(3,2,1,3) = t194
      dpdf(3,2,2,1) = t103
      dpdf(3,2,2,2) = t170
      dpdf(3,2,2,3) = t200
      dpdf(3,2,3,1) = t128
      dpdf(3,2,3,2) = t182
      dpdf(3,2,3,3) = t203
      dpdf(3,3,1,1) = t85
      dpdf(3,3,1,2) = t161
      dpdf(3,3,1,3) = t197
      dpdf(3,3,2,1) = t116
      dpdf(3,3,2,2) = t176
      dpdf(3,3,2,3) = t203
      dpdf(3,3,3,1) = t139
      dpdf(3,3,3,2) = t188
      dpdf(3,3,3,3) = t206

