// #define BOUNDS_CHECK
#include "aString.H"
#include "TriangleWrapper.h"

extern "C" {

#define ANSI_DECLARATORS

// the following define is required by triangle
// warning : REAL exists elsewhere in Overture so do this undef after
//           overture includes are over
#ifdef REAL
#undef REAL
#endif
// define REAL real
#define REAL double

#include "triangle.h"

}

static int triangulateio_ctr( struct triangulateio &io, 
			      int numberOfPoints = 0, 
			      int numberOfPointAttributes = 0, 
			      int numberOfRegions = 0, 
			      int numberOfSegments = 0,
			      int numberOfHoles    = 0)
{
  //
  // "constructor" for the triangulateio struct in triangle.h
  // note that this function should be paired with the destructor 
  // given by triangulateio_dtr
  //

  // first nullify all the pointers
  io.pointlist             = NULL;
  io.pointattributelist    = NULL;
  io.pointmarkerlist       = NULL;
  io.trianglelist          = NULL;
  io.triangleattributelist = NULL;
  io.trianglearealist      = NULL;
  io.neighborlist          = NULL;
  io.segmentlist           = NULL;
  io.segmentmarkerlist     = NULL;
  io.holelist              = NULL;
  io.regionlist            = NULL;
  io.edgelist              = NULL;
  io.edgemarkerlist        = NULL;
  io.normlist              = NULL;

  //
  // allocate point data arrays
  //
  io.numberofpoints = numberOfPoints;
  io.numberofpointattributes = numberOfPointAttributes;
  if ( io.numberofpoints != 0 ) 
    {
      if ( (io.pointlist = new REAL[ 2 * io.numberofpoints ])==NULL ) return-1;
      if ( io.numberofpointattributes>0 )
	if ( (io.pointattributelist = new REAL[ io.numberofpoints*io.numberofpointattributes ])==NULL ) return -1;
      if ( (io.pointmarkerlist = new int[ io.numberofpoints ])==NULL ) return -1;
    }

  // 
  // allocate region data arrays
  //
  io.numberofregions = numberOfRegions;
  if ( io.numberofregions>0 )
    if ( (io.regionlist = new REAL[ io.numberofregions*4 ])==NULL ) return -1;
    
  //
  // allocate segment arrays
  //
  io.numberofsegments = numberOfSegments;
  if ( io.numberofsegments>0 )
    {
      if ( (io.segmentlist = new int[ 2*io.numberofsegments ])==NULL ) return -1;
      if ( (io.segmentmarkerlist = new int[ io.numberofsegments ])==NULL ) return -1;
    }

  io.numberofholes = numberOfHoles;
  if ( io.numberofholes>0 )
    {
      io.holelist = new REAL[ 2 * io.numberofholes ];
    }

  io.numberofedges = 0;

  return 0;
}

static int triangulateio_dtr( struct triangulateio &io, bool freeflag = false, bool outFlag = false)
{

  // 
  // "destructor" for struct triangulateio from triangle.h, 
  // this function should be paired with triangulateio_ctr
  //

  if ( !freeflag )
    {
      // 
      // deallocate memory newed in triangulateio_ctr
      //
      if ( io.pointlist != NULL )             delete [] io.pointlist ;
      if ( io.pointattributelist != NULL )    delete [] io.pointattributelist ;
      if ( io.pointmarkerlist != NULL )       delete [] io.pointmarkerlist ;
      if ( io.trianglelist != NULL )          delete [] io.trianglelist ;
      if ( io.triangleattributelist != NULL ) delete [] io.triangleattributelist ;
      if ( io.trianglearealist != NULL && !outFlag ) delete [] io.trianglearealist ;
      if ( io.neighborlist != NULL )          delete [] io.neighborlist ;
      if ( io.holelist != NULL && !outFlag)   delete [] io.holelist ;
      if ( io.regionlist != NULL && !outFlag ) delete [] io.regionlist ;
      if ( io.segmentlist != NULL )           delete [] io.segmentlist ;
      if ( io.segmentmarkerlist != NULL )     delete [] io.segmentmarkerlist ;
      if ( io.edgelist != NULL )              delete [] io.edgelist ;
      if ( io.edgemarkerlist != NULL )        delete [] io.edgemarkerlist ;
      if ( io.normlist != NULL )              delete [] io.normlist ;
    }
  else
    {
      //
      // deallocate memory malloced by triangle itself
      //
      if ( io.pointlist != NULL )             free ( io.pointlist );
      if ( io.pointattributelist != NULL )    free ( io.pointattributelist );
      if ( io.pointmarkerlist != NULL )       free ( io.pointmarkerlist );
      if ( io.trianglelist != NULL )          free ( io.trianglelist );
      if ( io.triangleattributelist != NULL ) free ( io.triangleattributelist );
      if ( io.trianglearealist != NULL && !outFlag ) free ( io.trianglearealist );
      if ( io.neighborlist != NULL )          free ( io.neighborlist );
      if ( io.holelist != NULL && !outFlag)   free ( io.holelist );
      if ( io.regionlist != NULL && !outFlag ) free ( io.regionlist );
      if ( io.segmentlist != NULL )           free ( io.segmentlist );
      if ( io.segmentmarkerlist != NULL )     free ( io.segmentmarkerlist );
      if ( io.edgelist != NULL )              free ( io.edgelist );
      if ( io.edgemarkerlist != NULL )        free ( io.edgemarkerlist );
      if ( io.normlist != NULL )              free ( io.normlist );
    }

  return 0;

}

aString 
TriangleWrapperParameters::
generateArgumentString() const 
{

  //
  // set some initial options
  // p - use PSLG as input
  // z - indices start from 0
  // A - attributes triangles to segment bounded regions
  // e - construct edge output
  // n - compute triangle neighbors
  //
  aString output;
  output ="pzAe";   // *wdh*  "pzAen";

  if( saveNeighbours ) output +="n";   // save triangle neighbours.
  
  if( quietMode ) output += "Q";       // turn on informational output.
  
  if( verboseMode==1 ) 
    output+="V";                 // verbose mode (level 1)
  else if( verboseMode==2 )
    output+="VV";                // even more verbose
  else if( verboseMode==3 )
    output+="VVV";               // very verbose

  // freeze the segments, ie do not allow segment splitting
  // ( note this even freezes internal segments by specifying 
  //   two Ys )
  //
  if ( freezeSegments ) output += "YY";

  //
  // set the minimum angle constraint.
  // if minAngle is less than zero, use triangle's default
  // otherwise use minAngle
  //
  aString buff;

  if ( minAngle < 0 ) 
    output += "q";
  else if( minAngle>0. )
  {
    //char buff[5];
    aString num;
    // *wdh* sPrintF(num, "%f5.1", minAngle);
    if( minAngle<1. )
      sPrintF(num, "%9.8f", minAngle);
    else if( minAngle<10. )
      sPrintF(num, "%9.7f", minAngle);
    else if( minAngle<100. )
      sPrintF(num, "%9.6f", minAngle);
    else 
      sPrintF(num, "%9.5f", minAngle);

    output += "q";
    output += num;
  }

  // 
  // set the maximum area specification, only if it is provided,
  // otherwise use the triangle's default
  //
  if ( maxArea > 0 )
    {
      // *wdh* sPrintF(buff, "%f5.1", maxArea);
      // there can be no blank following the 'a'
      //  ** didn't work:      sPrintF(buff, "%8.2e", maxArea);
      
      if( maxArea<1. )
	sPrintF(buff, "%9.8f", maxArea);
      else if( maxArea<10. )
	sPrintF(buff, "%9.7f", maxArea);
      else if( maxArea<100. )
	sPrintF(buff, "%9.6f", maxArea);
      else if( maxArea<1000. )
	sPrintF(buff, "%9.5f", maxArea);
      else if( maxArea<10000. )
	sPrintF(buff, "%9.4f", maxArea);
      else if( maxArea<100000. )
	sPrintF(buff, "%9.3f", maxArea);
      else 
	sPrintF(buff, "%9.2f", maxArea);
      
      output += "a";
      output += buff;
    }

  //
  // set (or not) the voronoi flag
  //
  if ( voronoi ) output += "v";

  return output;
}

TriangleWrapper::
TriangleWrapper()
{
  
}



void
TriangleWrapper::
initialize( const intArray & faces, const realArray & xyz )
{
  initialFaces.redim(0);
  initialFaces = faces;
  initialPoints.redim(0);
  initialPoints = xyz;
  holes.redim(0);

  numberOfEdges=0;
  numberOfBoundaryEdges=0;
}

void
TriangleWrapper::
setHoles( const realArray & newHoles )
{
  holes.redim(0);
  holes = newHoles;
}

void
TriangleWrapper::
generate()
{

  struct triangulateio in, out, vor;

  //
  // initialize the input triangulateio structure
  //
  if ( triangulateio_ctr( in, initialPoints.getLength(0), 0, 1, 
			  initialFaces.getLength(0), holes.getLength(0) )<0 )

    throw "error allocating memory for struct triangulatio";

  //
  // gather some information for the region 
  //
  real mins[2],maxs[2];

  mins[0] = mins[1] =  REAL_MAX;
  maxs[0] = maxs[1] = -REAL_MAX;

  const real *initialPointsp = initialPoints.Array_Descriptor.Array_View_Pointer2;
  const int initialPointsDim0=initialPoints.getRawDataSize(0);
#define INITIALPOINTS(i0,i1) initialPointsp[i0+initialPointsDim0*(i1)]

  const int *initialFacesp = initialFaces.Array_Descriptor.Array_View_Pointer2;
  const int initialFacesDim0=initialFaces.getRawDataSize(0);
#define INITIALFACES(i0,i1) initialFacesp[i0+initialFacesDim0*(i1)]

  const real *holesp = holes.Array_Descriptor.Array_View_Pointer2;
  const int holesDim0=holes.getRawDataSize(0);
#define HOLES(i0,i1) holesp[i0+holesDim0*(i1)]

  int p,a;

  for ( p=0; p<in.numberofpoints; p++ )
    {
      for ( a=0; a<2; a++ )
	{
	  in.pointlist[ 2*p + a ] = INITIALPOINTS(p,a);
	  mins[a] = min(mins[a], INITIALPOINTS(p,a));
	  maxs[a] = max(maxs[a], INITIALPOINTS(p,a));
	}
      in.pointmarkerlist[p] = 0;
    }

  // set the constraint location at the mid point of the region's bounding box
  in.regionlist[0] = (maxs[0] + mins[0])/2.0;
  in.regionlist[1] = (maxs[1] + mins[1])/2.0;
  in.regionlist[2] = 7.0;   // not sure what this attribute does
  // set the region's area constraint
  in.regionlist[3] = 0.1; //parameters.getMaximumArea();

  //
  // assign the initial list of segments
  //
  for ( int s=0; s<in.numberofsegments; s++ )
    {
      for ( p=0; p<2; p++ )
	in.segmentlist[ 2*s + p ] = INITIALFACES(s,p);
      
      in.segmentmarkerlist[s] = s;
    }

  // 
  // assign any holes
  //
  for ( int h=0; h<in.numberofholes; h++ )
    for ( p=0; p<2; p++ )
      in.holelist[2*h + p] = HOLES(h,p);

  // 
  // initialize the output triangulateio structures
  //
  if ( triangulateio_ctr( out )<0 ) throw "error allocating memory for triangulatio";
  if ( triangulateio_ctr( vor )<0 ) throw "error allocating memory for triangulatio";

  //
  // actually create the triangulation
  //
  // *wdh* if ( !parameters.getVoronoi() ) parameters.toggleVoronoi(); //(toggle the voronoi diagram on if neccessary )

  aString paramString = parameters.generateArgumentString();

  // printf("Argument string to Triangle: %s\n",(const char*)paramString);

  triangulate((char *)paramString.c_str(), &in, &out, &vor);
  triangles.redim(out.numberoftriangles, 3);
  points.redim(out.numberofpoints, 2);

  //
  // set the output results
  //
  int *trianglesp = triangles.Array_Descriptor.Array_View_Pointer2;
  const int trianglesDim0=triangles.getRawDataSize(0);
#define TRIANGLES(i0,i1) trianglesp[i0+trianglesDim0*(i1)]

  real *pointsp = points.Array_Descriptor.Array_View_Pointer2;
  const int pointsDim0=points.getRawDataSize(0);
#define POINTS(i0,i1) pointsp[i0+pointsDim0*(i1)]

  for ( int t=0; t<out.numberoftriangles; t++ )
    for ( int c=0; c<3; c++ )
      TRIANGLES(t,c) = out.trianglelist[3*t + c];
  
  for ( p=0; p<out.numberofpoints; p++ )
    for ( a=0; a<2; a++ )
      POINTS(p,a) = out.pointlist[2*p+a];
  
  if( parameters.getVoronoi() )
  {
    initialFaces2TriangleMapping.redim(out.numberofedges);
    // kkc    initialFaces2TriangleMapping.redim(out.numberofsegments);
    initialFaces2TriangleMapping = -1;
    for ( int e=0; e<vor.numberofedges; e++ )
      if ( vor.edgelist[ 2*e + 1 ] == -1 ) 
      {
	initialFaces2TriangleMapping(out.edgemarkerlist[e]) = vor.edgelist[2*e];
      }
    
  }
  
  // save the neighbour list
  if( parameters.getSaveNeighbours() )
  {
    neighbours.redim(out.numberoftriangles,3);
    int n=0;
    for ( n=0; n<out.numberoftriangles; n++ )
      for ( int c=0; c<3; c++ )
	neighbours(n,c) = out.neighborlist[3*n + c];
    
  }
  
  numberOfEdges=out.numberofedges;
  numberOfBoundaryEdges=out.numberofsegments;
//   for ( n=0; n<numberOfBoundaryEdges; n++ )
//   {
//      printf("From triangle: edge: %i (%i,%i) marker=%i\n",n,out.segmentlist[2*n],out.segmentlist[1+2*n],
//        out.segmentmarkerlist[n]);
//    }
  
  
  //
  // delete the memory inside the input and output triangulateio structures
  //
  if ( triangulateio_dtr( in )<0 ) throw "error deallocating a triangulatio";

  //
  // out and vor will have had memory allocated in triangle itself so use the "true" freeFlag
  // to the "destructor", also note that these are output triangulatios so send the outFlag as true
  //
  if ( triangulateio_dtr( out, true, true ) < 0 ) throw "error deallocating memory created by triangle";
  if ( triangulateio_dtr( vor, true, true ) < 0 ) throw "error deallocating memory created by triangle";

}
  
#undef REAL
