*
* circle in a channel
*
create mappings
*
rectangle
  set corners
    -2. 2. -2. 2.
  lines
    63 63  32 32 
  boundary conditions
    1 1 1 1
  mappingName
  square
exit
*
Annulus
  lines
    65 13  33 7
  boundary conditions
    -1 -1 1 0
exit
*
exit
generate an overlapping grid
    square
    Annulus
  done
  change parameters
    * choose implicit or explicit interpolation
    interpolation type
      explicit for all grids
    ghost points
      all
      2 2 2 2 2 2
  exit
*  display intermediate results
  compute overlap
  exit
*
* save an overlapping grid
save a grid (compressed)
cice2.hdf
cic
exit
