//                                   -*- c++ -*-
#ifndef NONLINEAR_BEAM_MODEL_H
#define NONLINEAR_BEAM_MODEL_H
 
#include "Overture.h"
#include "HyperbolicMapping.h"
#include "GenericGraphicsInterface.h"
#include "GridEvolution.h"
#include "DBase.hh"
#include <fstream>
using namespace DBase;

// Forward defs:
class GenericGraphicsInterface;
class MappingInformation;
class DeformingGrid;
class GridFunction; 
class Parameters;

//................................
class NonlinearBeamModel {

 public:

  enum BoundaryCondition { Pinned = 1 , Cantilevered = 2, Free = 4 , Periodic = 8 };

  struct BeamNode {

    // undeformed location
    real X[3];

    // displacement
    real u[3];

    // 
    real undeformedRotation;
    
    real rotation;

    real p0[2];
    real p[3];

    // beam thickness at this node
    real thickness;

    real v[3];

    real a[3];

    real utilde[3];
    real vtilde[3];
    
    real angularVelocity;

    real angularAcceleration;

    real angletilde;
    real angularVelocitytilde;

    real oldAccelerations[3];
  };

  struct SlaveState {

    
    real uplus[3]; real uminus[3];
    real xplus[3]; real xminus[3];
    real Xplus[3]; real Xminus[3];
    real vplus[3]; real vminus[3];
    real aplus[3]; real aminus[3];
  };

  struct ProjectedPoint {

    int elem;
    real dist;
    real xi;
    real eta;

    real projDelta[2];
  };

  NonlinearBeamModel();

  ~NonlinearBeamModel();


  void projectDisplacement(int id, real& x, real& y);


  void projectAcceleration(int id, real& ax, real& ay);

  void addForce(int i1, real p1, int i2, real p2);

  void resetForce();

  void predictor(real dt);

  void corrector(real dt);

  bool hasCorrectionConverged() const;

  void setAddedMassRelaxation(double);
  
  void setSubIterationConvergenceTolerance(double tol);

  void addBodyForce(const real[2]);

  void readBeamFile(const char* filename);

  void initializeProjectedPoints(int sz);

  void projectInitialPoint(int id, real x, real y);
  
  int put( GenericDataBase & dir, const aString & name) const;

  int get( const GenericDataBase & dir, const aString & name);

 private:

  void computeShapeFunctions(real xi, real eta, real N[4]);
  void computeShapeFunctionGradients(real xi, real eta, real N[4][2]);

  void computeSlaveStates();


  void computeLaminarBasis(int elem,real xi, real eta,
			   real R[4], real ex[2],
			   real ey[2],
			   real Rdef[4]);

  void computeLaminarComponents(int elem,real xi, real eta, real R[4],
				real F[4], real E[4], real& J,
				real Nx[4][2], real& Jeta);

  void computeStressSVK(int elem,real xi, real eta, real R[4],
			real F[4], real E[4], real J,
			real sigma[4]);

  void computeInternalForce(int elem,RealArray& F,
			    RealArray& Kelem);

  void computeInternalForce(RealArray& F,RealArray& KT);

  void computeElementalMassMatrix(int elem, RealArray& M);

  void computeMassMatrix(int elem,RealArray& MT);

  void reevaluateMassMatrix();

  void computeBodyForce(RealArray& Fout);
  void computeBodyForce(int, RealArray& Fout);

  void computeMaterialStiffness(real cg[2][2],
				real Nxi, real Nyi,
				real Nxj, real Nyj);

  void computeGeometricStiffness(real kgeo[2][2],
				 real sigma[4],
				 real Nxi, real Nyi,
				 real Nxj, real Nyj) ;

  void setExactSolution(double t,RealArray& x, RealArray& v, RealArray& a);
  
  double getExactPressure(double t, double xl);
  
  void computeExtraInertiaTerm(RealArray&) ;

  BeamNode* beamNodes;

  SlaveState* slaveStates;

  ProjectedPoint* projectedPoints;

  int numProjectedPoints;

  real density, nu, Em;

  int numNodes,numElem;

  // Mass matrices
  RealArray M;

  // Stiffness Matrices
  RealArray K;

  real newmarkBeta,newmarkGamma;

  real omega_structure;

  BoundaryCondition bcLeft, bcRight;

  real bodyForce[2];

  RealArray Fext,Ffluid;

  int isSteady;

  real t;

  std::ofstream tipfile;

  real pressureNorm;

  int useExactSolution;

  int time_step_num;

  bool correctionHasConverged;

  double added_mass_relaxation;

  double convergenceTolerance;

  double initialResidual;

  int numCorrectorIterations;

  RealArray* elementMassMatrices;

  double rayleighAlpha, rayleighBeta;

};

#endif
