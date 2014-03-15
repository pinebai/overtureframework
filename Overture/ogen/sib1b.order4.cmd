*
* Same resoluition as sib1.order4 but in a bigger box
*
create mappings
* first make a sphere
Sphere
exit
*
* now make a mapping for the north pole
*
reparameterize
  orthographic
    specify sa,sb
      2.35 2.35
  exit
  lines
    33 33 13 * 21 21 7  31 31 11  61 61 21 45 45 15   15 15 5
  boundary conditions
    0 0 0 0 1 0
  share
    0 0 0 0 1 0
  mappingName
    north-pole
exit
*
* now make a mapping for the south pole
*
reparameterize
  orthographic
    choose north or south pole
      -1
    specify sa,sb
      2.35 2.35
  exit
  lines
    33 33 13   * 21 21 7  31 31 11 61 61 21 45 45 15  15 15 5
  boundary conditions
    0 0 0 0 1 0
  share
    0 0 0 0 1 0
  mappingName
    south-pole
exit
*
* Here is the box
*
Box
  set corners
    -4 4 -4 4 -4 4   * -2 2 -2 2 -2 2 
  lines
    81 81 81 * 41 41 41   81 81 81 61 61 61  21 21 21
  mappingName
    box
  exit
exit
*
generate an overlapping grid
  box
  north-pole
  south-pole
  done
  change parameters
*    interpolation type
*      explicit for all grids
    ghost points
      all
      2 2 2 2 2 3
    order of accuracy
      fourth order
  exit
  compute overlap
exit
save an overlapping grid
sib1b.order4.hdf
sib
exit
