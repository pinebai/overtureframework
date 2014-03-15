*
  Circle or ellipse (3D)
    mappingName
      ellipse0
    specify axes of the ellipse
      .7 .2 
    specify centre
      2.3 0. .2
    exit
*
  Circle or ellipse (3D)
    mappingName
      ellipse1
    specify axes of the ellipse
      .7 .2 
    specify centre
      2.3 0. 1. 
    exit
*
  Circle or ellipse (3D)
    mappingName
      ellipse2
    specify axes of the ellipse
      .7 .2 
    specify centre
      2.3 0. 1.8
    exit
*
  CrossSection
    mappingName
      sail-surface
    general
      3
    ellipse0
    ellipse1
    ellipse2
    polar singularity at end
  exit
* orthographic patch for the cap of the sail
  reparameterize  
    mappingName
      sail-cap-surface
    pause
  exit
* stretch lines on cap
  stretch coordinates
    stretch
      specify stretching along axis=0 (x1)
        layers
          1
          1. 5. .5
        exit
      exit
    exit
*  volume mapping for the cap
  mapping from normals
    mappingName
      sail-cap
    normal distance
      .35
    extend normals from which mapping?
    stretched-sail-cap-surface
    lines
      15 15 9
    share
      0 0 0 0 1 0
    pause
    exit
* volume mapping for the sail body
  mapping from normals
    mappingName
      sail-volume
    normal distance
      .4
    extend normals from which mapping?
      sail-surface
    lines
      31 15 5
    boundary conditions
      -1 -1 0 0 1 2
    share
      0 0 0 0 1 0
    pause
    exit
*
  Cylinder
    orientation
      1 2 0
    bounds on the radial variable
      .8 1.3
    bounds on the axial variable
      1. 4.
    boundary conditions
      -1 -1 3 3 2 0
    share
       0  0 3 3 2 0
    lines
      31 21 7
    exit
*
  join
    mappingName
      sail
    end of join
     .9
    choose curves
    sail-volume 
    Cylinder (side=0,axis=2)
    lines
      31 11 7
    boundary conditions
      -1 -1 2 0 1 0
    share
       0  0 2 0 1 0
    compute join

