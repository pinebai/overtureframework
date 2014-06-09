function CC = getCMat3D( rho,mu,lambda,alpha,f )

  CC = zeros(12,12);

t1 = 0.1e1 / rho;
t2 = alpha(1) * t1;
t3 = alpha(2) * t1;
t4 = alpha(3) * t1;
t5 = f(1,1) ^ 2;
t6 = lambda * t5;
t8 = mu * t5;
t10 = f(2,1) ^ 2;
t11 = lambda * t10;
t12 = t11 / 0.2e1;
t13 = f(3,1) ^ 2;
t14 = lambda * t13;
t15 = t14 / 0.2e1;
t16 = 0.3e1 / 0.2e1 * lambda;
t17 = f(1,2) ^ 2;
t18 = lambda * t17;
t19 = t18 / 0.2e1;
t20 = f(2,2) ^ 2;
t21 = lambda * t20;
t22 = t21 / 0.2e1;
t23 = f(3,2) ^ 2;
t24 = lambda * t23;
t25 = t24 / 0.2e1;
t26 = f(1,3) ^ 2;
t27 = lambda * t26;
t28 = t27 / 0.2e1;
t29 = f(2,3) ^ 2;
t30 = lambda * t29;
t31 = t30 / 0.2e1;
t32 = f(3,3) ^ 2;
t33 = lambda * t32;
t34 = t33 / 0.2e1;
t35 = mu * t10;
t36 = mu * t13;
t37 = mu * t17;
t38 = mu * t26;
t39 = 0.3e1 / 0.2e1 * t6 + 0.3e1 * t8 + t12 + t15 - t16 + t19 + t22 + t25 + t28 + t31 + t34 + t35 + t36 - mu + t37 + t38;
t41 = lambda * f(1,2);
t43 = mu * f(1,1);
t44 = t43 * f(1,2);
t46 = mu * f(2,1);
t47 = t46 * f(2,2);
t48 = mu * f(3,1);
t49 = t48 * f(3,2);
t50 = t41 * f(1,1) + 0.2e1 * t44 + t47 + t49;
t52 = lambda * f(1,3);
t54 = t43 * f(1,3);
t56 = t46 * f(2,3);
t57 = t48 * f(3,3);
t58 = t52 * f(1,1) + 0.2e1 * t54 + t56 + t57;
t61 = f(1,1) * lambda;
t63 = t43 * f(2,1);
t65 = mu * f(2,2);
t66 = t65 * f(1,2);
t68 = mu * f(2,3) * f(1,3);
t70 = alpha(1) * (t61 * f(2,1) + 0.2e1 * t63 + t66 + t68);
t71 = lambda * f(2,2);
t74 = t71 * f(1,1) + t46 * f(1,2);
t76 = lambda * f(2,3);
t79 = t76 * f(1,1) + t46 * f(1,3);
t83 = t43 * f(3,1);
t85 = mu * f(3,2);
t86 = t85 * f(1,2);
t87 = mu * f(3,3);
t88 = t87 * f(1,3);
t90 = alpha(1) * (t61 * f(3,1) + 0.2e1 * t83 + t86 + t88);
t91 = lambda * f(3,2);
t94 = t91 * f(1,1) + t48 * f(1,2);
t96 = lambda * f(3,3);
t99 = t96 * f(1,1) + t48 * f(1,3);
t104 = t41 * f(2,1) + t43 * f(2,2);
t108 = t52 * f(2,1) + t43 * f(2,3);
t113 = t6 / 0.2e1;
t114 = mu * t20;
t115 = mu * t29;
t116 = 0.3e1 / 0.2e1 * t11 + 0.3e1 * t35 + t113 + t15 - t16 + t19 + t22 + t25 + t28 + t31 + t34 + t8 + t36 - mu + t114 + t115;
t120 = t71 * f(2,1) + 0.2e1 * t47 + t44 + t49;
t124 = t76 * f(2,1) + 0.2e1 * t56 + t54 + t57;
t129 = t46 * f(3,1);
t131 = t85 * f(2,2);
t132 = t87 * f(2,3);
t134 = alpha(1) * (f(2,1) * lambda * f(3,1) + 0.2e1 * t129 + t131 + t132);
t137 = t91 * f(2,1) + t48 * f(2,2);
t141 = t96 * f(2,1) + t48 * f(2,3);
t146 = t41 * f(3,1) + t43 * f(3,2);
t150 = t52 * f(3,1) + t43 * f(3,3);
t155 = t71 * f(3,1) + t46 * f(3,2);
t159 = t76 * f(3,1) + t46 * f(3,3);
t164 = mu * t23;
t165 = mu * t32;
t166 = 0.3e1 / 0.2e1 * t14 + 0.3e1 * t36 + t113 + t12 - t16 + t19 + t22 + t25 + t28 + t31 + t34 + t8 + t35 - mu + t164 + t165;
t170 = t91 * f(3,1) + 0.2e1 * t49 + t44 + t47;
t174 = t96 * f(3,1) + 0.2e1 * t57 + t54 + t56;
t180 = t8 + 0.3e1 / 0.2e1 * t18 + 0.3e1 * t37 + t113 + t12 + t15 - t16 + t22 + t25 + t28 + t31 + t34 + t114 + t164 - mu + t38;
t183 = mu * f(1,2);
t184 = t183 * f(1,3);
t186 = t65 * f(2,3);
t187 = t85 * f(3,3);
t188 = t52 * f(1,2) + 0.2e1 * t184 + t186 + t187;
t195 = alpha(2) * (t63 + t41 * f(2,2) + 0.2e1 * t66 + t68);
t198 = t76 * f(1,2) + t65 * f(1,3);
t205 = alpha(2) * (t83 + t41 * f(3,2) + 0.2e1 * t86 + t88);
t208 = t96 * f(1,2) + t85 * f(1,3);
t214 = t52 * f(2,2) + t183 * f(2,3);
t220 = t35 + 0.3e1 / 0.2e1 * t21 + 0.3e1 * t114 + t113 + t12 + t15 - t16 + t19 + t25 + t28 + t31 + t34 + t37 + t164 - mu + t115;
t224 = t76 * f(2,2) + 0.2e1 * t186 + t184 + t187;
t231 = alpha(2) * (t129 + t71 * f(3,2) + 0.2e1 * t131 + t132);
t234 = t96 * f(2,2) + t85 * f(2,3);
t240 = t52 * f(3,2) + t183 * f(3,3);
t246 = t76 * f(3,2) + t65 * f(3,3);
t252 = t36 + 0.3e1 / 0.2e1 * t24 + 0.3e1 * t164 + t113 + t12 + t15 - t16 + t19 + t22 + t28 + t31 + t34 + t37 + t114 - mu + t165;
t256 = t96 * f(3,2) + 0.2e1 * t187 + t184 + t186;
t263 = t8 + t37 + 0.3e1 / 0.2e1 * t27 + 0.3e1 * t38 + t113 + t12 + t15 - t16 + t19 + t22 + t25 + t31 + t34 + t115 + t165 - mu;
t271 = alpha(3) * (t63 + t66 + t52 * f(2,3) + 0.2e1 * t68);
t278 = alpha(3) * (t83 + t86 + t52 * f(3,3) + 0.2e1 * t88);
t287 = t35 + t114 + 0.3e1 / 0.2e1 * t30 + 0.3e1 * t115 + t113 + t12 + t15 - t16 + t19 + t22 + t25 + t28 + t34 + t38 + t165 - mu;
t295 = alpha(3) * (t129 + t131 + t76 * f(3,3) + 0.2e1 * t132);
t307 = t36 + t164 + 0.3e1 / 0.2e1 * t33 + 0.3e1 * t165 + t113 + t12 + t15 - t16 + t19 + t22 + t25 + t28 + t31 + t38 + t115 - mu;
CC(1,1) = 0.0e0;
CC(1,2) = 0.0e0;
CC(1,3) = 0.0e0;
CC(1,4) = -t2;
CC(1,5) = 0.0e0;
CC(1,6) = 0.0e0;
CC(1,7) = -t3;
CC(1,8) = 0.0e0;
CC(1,9) = 0.0e0;
CC(1,10) = -t4;
CC(1,11) = 0.0e0;
CC(1,12) = 0.0e0;
CC(2,1) = 0.0e0;
CC(2,2) = 0.0e0;
CC(2,3) = 0.0e0;
CC(2,4) = 0.0e0;
CC(2,5) = -t2;
CC(2,6) = 0.0e0;
CC(2,7) = 0.0e0;
CC(2,8) = -t3;
CC(2,9) = 0.0e0;
CC(2,10) = 0.0e0;
CC(2,11) = -t4;
CC(2,12) = 0.0e0;
CC(3,1) = 0.0e0;
CC(3,2) = 0.0e0;
CC(3,3) = 0.0e0;
CC(3,4) = 0.0e0;
CC(3,5) = 0.0e0;
CC(3,6) = -t2;
CC(3,7) = 0.0e0;
CC(3,8) = 0.0e0;
CC(3,9) = -t3;
CC(3,10) = 0.0e0;
CC(3,11) = 0.0e0;
CC(3,12) = -t4;
CC(4,1) = alpha(1) * t39 + alpha(2) * t50 + alpha(3) * t58;
CC(4,2) = t70 + alpha(2) * t74 + alpha(3) * t79;
CC(4,3) = t90 + alpha(2) * t94 + alpha(3) * t99;
CC(4,4) = 0.0e0;
CC(4,5) = 0.0e0;
CC(4,6) = 0.0e0;
CC(4,7) = 0.0e0;
CC(4,8) = 0.0e0;
CC(4,9) = 0.0e0;
CC(4,10) = 0.0e0;
CC(4,11) = 0.0e0;
CC(4,12) = 0.0e0;
CC(5,1) = t70 + alpha(2) * t104 + alpha(3) * t108;
CC(5,2) = alpha(1) * t116 + alpha(2) * t120 + alpha(3) * t124;
CC(5,3) = t134 + alpha(2) * t137 + alpha(3) * t141;
CC(5,4) = 0.0e0;
CC(5,5) = 0.0e0;
CC(5,6) = 0.0e0;
CC(5,7) = 0.0e0;
CC(5,8) = 0.0e0;
CC(5,9) = 0.0e0;
CC(5,10) = 0.0e0;
CC(5,11) = 0.0e0;
CC(5,12) = 0.0e0;
CC(6,1) = t90 + alpha(2) * t146 + alpha(3) * t150;
CC(6,2) = t134 + alpha(2) * t155 + alpha(3) * t159;
CC(6,3) = alpha(1) * t166 + alpha(2) * t170 + alpha(3) * t174;
CC(6,4) = 0.0e0;
CC(6,5) = 0.0e0;
CC(6,6) = 0.0e0;
CC(6,7) = 0.0e0;
CC(6,8) = 0.0e0;
CC(6,9) = 0.0e0;
CC(6,10) = 0.0e0;
CC(6,11) = 0.0e0;
CC(6,12) = 0.0e0;
CC(7,1) = alpha(1) * t50 + alpha(2) * t180 + alpha(3) * t188;
CC(7,2) = alpha(1) * t104 + t195 + alpha(3) * t198;
CC(7,3) = alpha(1) * t146 + t205 + alpha(3) * t208;
CC(7,4) = 0.0e0;
CC(7,5) = 0.0e0;
CC(7,6) = 0.0e0;
CC(7,7) = 0.0e0;
CC(7,8) = 0.0e0;
CC(7,9) = 0.0e0;
CC(7,10) = 0.0e0;
CC(7,11) = 0.0e0;
CC(7,12) = 0.0e0;
CC(8,1) = alpha(1) * t74 + t195 + alpha(3) * t214;
CC(8,2) = alpha(1) * t120 + alpha(2) * t220 + alpha(3) * t224;
CC(8,3) = alpha(1) * t155 + t231 + alpha(3) * t234;
CC(8,4) = 0.0e0;
CC(8,5) = 0.0e0;
CC(8,6) = 0.0e0;
CC(8,7) = 0.0e0;
CC(8,8) = 0.0e0;
CC(8,9) = 0.0e0;
CC(8,10) = 0.0e0;
CC(8,11) = 0.0e0;
CC(8,12) = 0.0e0;
CC(9,1) = alpha(1) * t94 + t205 + alpha(3) * t240;
CC(9,2) = alpha(1) * t137 + t231 + alpha(3) * t246;
CC(9,3) = alpha(1) * t170 + alpha(2) * t252 + alpha(3) * t256;
CC(9,4) = 0.0e0;
CC(9,5) = 0.0e0;
CC(9,6) = 0.0e0;
CC(9,7) = 0.0e0;
CC(9,8) = 0.0e0;
CC(9,9) = 0.0e0;
CC(9,10) = 0.0e0;
CC(9,11) = 0.0e0;
CC(9,12) = 0.0e0;
CC(10,1) = alpha(1) * t58 + alpha(2) * t188 + alpha(3) * t263;
CC(10,2) = alpha(1) * t108 + alpha(2) * t214 + t271;
CC(10,3) = alpha(1) * t150 + alpha(2) * t240 + t278;
CC(10,4) = 0.0e0;
CC(10,5) = 0.0e0;
CC(10,6) = 0.0e0;
CC(10,7) = 0.0e0;
CC(10,8) = 0.0e0;
CC(10,9) = 0.0e0;
CC(10,10) = 0.0e0;
CC(10,11) = 0.0e0;
CC(10,12) = 0.0e0;
CC(11,1) = alpha(1) * t79 + alpha(2) * t198 + t271;
CC(11,2) = alpha(1) * t124 + alpha(2) * t224 + alpha(3) * t287;
CC(11,3) = alpha(1) * t159 + alpha(2) * t246 + t295;
CC(11,4) = 0.0e0;
CC(11,5) = 0.0e0;
CC(11,6) = 0.0e0;
CC(11,7) = 0.0e0;
CC(11,8) = 0.0e0;
CC(11,9) = 0.0e0;
CC(11,10) = 0.0e0;
CC(11,11) = 0.0e0;
CC(11,12) = 0.0e0;
CC(12,1) = alpha(1) * t99 + alpha(2) * t208 + t278;
CC(12,2) = alpha(1) * t141 + alpha(2) * t234 + t295;
CC(12,3) = alpha(1) * t174 + alpha(2) * t256 + alpha(3) * t307;
CC(12,4) = 0.0e0;
CC(12,5) = 0.0e0;
CC(12,6) = 0.0e0;
CC(12,7) = 0.0e0;
CC(12,8) = 0.0e0;
CC(12,9) = 0.0e0;
CC(12,10) = 0.0e0;
CC(12,11) = 0.0e0;
CC(12,12) = 0.0e0;

return


