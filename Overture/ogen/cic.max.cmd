*
* circle in a channel
*
create mappings
*
rectangle
  specify corners
    -2. -2. 2. 2.
  lines
    32 32 
  boundary conditions
    1 1 1 1
  mappingName
  square
exit
*
Annulus
  lines
    33 7
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
    maximize overlap
    ghost points
      all
      2 2 2 2 2 2
  exit
  compute overlap

  exit
*
save an overlapping grid
cic.hdf
cic
exit

