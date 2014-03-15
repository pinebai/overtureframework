* make a c-grid
*
  spline
    enter spline points
      17
      1. 0.
      .9  0.
      .8  0.
      .7  0.
      .6  0.
      .5 0.
      .25 .1
      .005 .03
      0. 0.
      .005 -.03
      .25 -.1
      .5 0.
      .6 0.
      .7 0.
      .8 0.
      .9 0.
      1. 0.
    shape preserving (toggle)
    mappingName
      c-surface
    exit
*
  hyperbolic
    distance to march
      .25
    generate
    uniform dissipation coefficient
      .02
    generate
    c-grid
      specify c-grid matching tolerance
        1.e-4
      determine c-grid automatically    
  pause
     done
    mappingName
      c-grid
    boundary conditions
      0 0 1 0
    exit
*
   DataPointMapping
     build from a mapping
       c-grid
    c-grid
      specify c-grid matching tolerance
        1.e-4
      determine c-grid automatically    
    done
     mappingName
      c-grid-dp
  exit
*
  rectangle
*
    set corners
      -.5 1.5 -.5 .5
    lines
      41 21
    exit
  view mappings
    c-grid
    square

