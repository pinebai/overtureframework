* make a simple square
create mappings
  rectangle
    mappingName
      square
    lines
      2049 2049 1025 1025 
    boundary conditions
      1 1 1 1
  exit
exit
*
generate an overlapping grid
  square
  done
  change parameters
    ghost points
      all
      2 2 2 2 2 2
  exit
  compute overlap
exit
*
save an overlapping grid
  square2048.hdf
  square2048
exit

