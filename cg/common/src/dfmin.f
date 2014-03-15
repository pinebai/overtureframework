      DOUBLE PRECISION FUNCTION DFMIN(F,X,A,B,T)
C
C  DFMIN FINDS AN APPROXIMATION X TO THE POINT IN
C  THE INTERVAL (A,B) AT WHICH F ATTAINS ITS MINIMUM,
C  AND RETURNS IN DFMIN THE VALUE OF F AT X.
C
C  T DETERMINES A TOLERANCE OF
C
C              TOL  =  D1MACH(4) * DABS(X) + T
C
C  AND F IS NEVER EVALUATED AT TWO POINTS CLOSER
C  TOGETHER THAN TOL.
C
C  IF T IS INPUT .LE. ZERO, IT IS SET TO 10.*D1MACH(1)
C
C  THE METHOD USED IS A COMBINATION OF GOLDEN SEARCH
C  AND SUCCESSIVE PARABOLIC INTERPOLATION.
C  CONVERGENCE IS NEVER MUCH SLOWER THAN FOR A
C  FIBONACCI SEARCH.
C  IF F HAS A CONTINUOUS SECOND DERIVATIVE WHICH IS POSITIVE
C  AT THE MINIMUM ( NOT AT A OR B) THEN, IGNORING
C  ROUNDING ERRORS, CONVERGENCE IS SUPERLINEAR,
C  AND USUALLY THE ORDER IS AT LEAST 1.3247....
C
C  THIS IS BRENT'S ALGORITHM - SEE PAGE 188 OF HIS BOOK.
C
C  A, STORED IN SA, AND B, STORED IN SB ARE
C  AT ANY STEP THE CURRENT BOUNDARIES FOR
C  THE INTERVAL CONTAINING THE MINIMUM.
C
C  X IS THE POINT AT WHICH F HAS THE LEAST VALUE
C  SO FAR, (OR THE POINT OF MOST RECENT EVALUATION
C  IF THERE IS A TIE).
C
C  W IS THE POINT WITH THE NEXT LOWEST VALUE OF F
C
C  V IS THE PREVIOUS VALUE OF W
C
C  U IS THE LAST POINT AT WHICH F HAS BEEN EVALUATED
C   (U IS UNDEFINED THE FIRST TIME.)
C
      DOUBLE PRECISION A,B,D1MACH,T,F,X,SA,SB,D,E,M,P,Q,R
      DOUBLE PRECISION TOL,T2,TT,U,V,W,FU,FV,FW,FX,CONS
      EXTERNAL F
      TT = T
      IF (T .LE. 0.D0 ) TT = 10.D0*D1MACH(1)
      IF (A .LT. B) GO TO 5
      SA = B
      SB = A
      GO TO 8
    5 SA = A
      SB = B
    8 CONS = .5D0*(3.0D0-DSQRT(5.0D0))
C
C  ARBITRARILY FOR THE FIRST STEP CHOOSE
C
C     X = A + .5(3-DSQRT(5))* (B-A)
C
      X = SA + CONS*(SB - SA)
      W = X
      V = W
      E = 0.0D0
      FX = F(X)
      FW = FX
      FV = FW
C
C  THE MAIN LOOP STARTS HERE.
C
      it=0  ! *wdh* add a stop for maximum iterations
      maxit=100

   10 M = 0.5D0*(SA + SB)
      TOL = D1MACH(4) * DABS(X) + TT
      T2 = 2.0D0 * TOL
C
C  CHECK THE STOPPING CRITERION:
C        (M = MIDPOINT)
C  IF DABS(X-M) .LE. (2*TOL - .5(B-A)),
C  I.E. IF MAX(X-A, B-X) .LE. 2*TOL, THEN
C  THE PROCEDURE TERMINATES WITH X AS THE
C  APPROXIMATE POSITION OF THE MINIMUM.
C
      IF (DABS(X-M) .LE. T2-0.5D0*(SB-SA)) GO TO 190
      it=it+1
      if( it.gt.maxit ) goto 190

      R = 0.0D0
      Q = R
      P = Q
      IF (DABS(E) .LE. TOL) GO TO 40
C
C    FIT THE PARABOLA
C
C    Q = 2((X-V)(FX-FW) - (X-W)(FX-FV))
C    P = ((X-V)**2)(FX-FW) - ((X-W))**2)(FX-FV)
C
      R = (X-W)*(FX-FV)
      Q = (X-V)*(FX-FW)
      P = (X-V)*Q - (X-W) * R
      Q = 2.0D0*(Q-R)
      IF (Q .LE. 0.0D0) GO TO 20
      P = -P
      GO TO 30
C
   20 Q = -Q
   30 R = E
      E = D
C
C  HERE E IS THE VALUE OF P/Q AT THE SECOND LAST
C  CYCLE; IF DABS(E) .LE. TOL, OR IF Q = 0.0.
C  OR IF X+P/Q LIES OUTSIDE OF (A,B), OR
C  DABS(P/Q) .GE. .5E, THEN A "GOLDEN
C  SECTION" STEP IS PERFORMED (AT 60 BELOW).
C
C  OTHERWISE A PARABOLIC INTERPOLATION
C  STEP IS TAKEN
C
   40 IF (DABS(P).GE.DABS(0.5D0*Q*R)) GO TO 60
      IF ((P.LE.Q*(SA-X)).OR.(P.GE.Q*(SB-X))) GO TO 60
      D = P/Q
      U = X + D
C
C  EXCEPT F MUST NOT BE EVALUATED TOO CLOSE TO A OR B.
C
C  IF THE NEW POINT IS TOO CLOSE JUST PUT
C       D = +TOL   IF X.LT.M
C       D = -TOL   IF X.GE.M
C
      IF((U-SA.GE.T2).AND.(SB-U.GE.T2)) GO TO 90
      IF (X.GE.M) GO TO 50
      D = TOL
      GO TO 90
   50 D = -TOL
      GO TO 90
C
C  THIS IS THE "GOLDEN SECTION" STEP:
C
C       U = .5(SQRT(5)-1)X + .5(3-SQRT(5)A   IF X.GE.M
C       U = .5(SQRT(5)-1)X + .5(3-SQRT(5)B   IF X.LT.M
C
   60 IF (X.GE.M) GO TO 70
      E = SB - X
      GO TO 80
   70 E = SA - X
   80 D = CONS*E
C
C     U = X+(IF DABS(D).GE.TOL THEN D,
C          ELSE IF D.GT.0 THEN TOL     ELSE  -TOL)
C
   90 IF (DABS(D).LT.TOL) GO TO 100
      U = X + D
      GO TO 120
  100 IF (D.LE.0.0D0) GO TO 110
      U = X + TOL
      GO TO 120
  110 U = X - TOL
C
C  UPDATE EVERYTHING
C  IF FU.LE.FX THEN
C     BEGIN IF U.LT.X THEN B = X ELSE A = X
C     V = W;FV = FW;W = X;FW = FX;X = U;FX = FU
C     END
C  ELSE
C     BEGIN IF U.LT.X THEN A = U ELSE B = U
C     IF FU.LE.FW OR W = X THEN
C          BEGIN V = W;FV = FW;W = X;FW = FU END
C     ELSE IF FU.LE.FV OR V = X OR V = W THEN
C            BEGIN V = U; FV = FU
C            END
C     END
C
  120 FU = F(U)
      IF (FU.GT.FX) GO TO 150
      IF (U.GE.X) GO TO 130
      SB = X
      GO TO 140
  130 SA = X
  140 V = W
      FV = FW
      W = X
      FW = FX
      X = U
      FX = FU
      GO TO 10
C
  150 IF (U.GE.X) GO TO 160
      SA = U
      GO TO 170
  160 SB = U
  170 IF ((FU.GT.FW) .AND.(W.NE.X)) GO TO 180
      V = W
      FV = FW
      W = U
      FW = FU
      GO TO 10
C
  180 IF ((FU.GT.FV).AND.(V.NE.X).AND.(V.NE.W)) GO TO 10
      V = U
      FV = FU
      GO TO 10
C
  190 DFMIN = FX
      RETURN
      END

