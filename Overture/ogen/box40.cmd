*
* make a box
*
create mappings
  Box
    lines
      41 41 41 
    mappingName
      box
  exit
exit
*
generate an overlapping grid
  box
  done
  change parameters
    ghost points
      all
      2 2 2 2 2 2
  exit
  compute overlap
exit
save an overlapping grid
box40.hdf
box
exit
