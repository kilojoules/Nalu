/*------------------------------------------------------------------------*/
/*  Copyright 2014 Sandia Corporation.                                    */
/*  This software is released under the license detailed                  */
/*  in the file, LICENSE, which is located in the top-level Nalu          */
/*  directory structure                                                   */
/*------------------------------------------------------------------------*/


#ifndef EnthalpyPropertyEvaluator_h
#define EnthalpyPropertyEvaluator_h

#include <property_evaluator/PolynomialPropertyEvaluator.h>
#include <FieldTypeDef.h>

#include <string>
#include <map>
#include <vector>

namespace stk {
namespace mesh {
class MetaData;
struct Entity;
}
}

namespace sierra{
namespace nalu{

class ReferencePropertyData;

class EnthalpyPropertyEvaluator : public PolynomialPropertyEvaluator
{
public:

  EnthalpyPropertyEvaluator(
      const std::map<std::string, ReferencePropertyData*> &referencePropertyDataMap,
      const std::map<std::string, std::vector<double> > &lowPolynomialCoeffsMap,
      const std::map<std::string, std::vector<double> > &highPolynomialCoeffsMap,
      double universalR);
  virtual ~EnthalpyPropertyEvaluator();
  
  double execute(
      double *indVarList,
      stk::mesh::Entity node);

  double compute_h_rt(
      const double &T,
      const double *pt_poly);
  
  std::vector<double> refMassFraction_;
  
};

class EnthalpyTYkPropertyEvaluator : public PolynomialPropertyEvaluator
{
public:

  EnthalpyTYkPropertyEvaluator(
      const std::map<std::string, ReferencePropertyData*> &referencePropertyDataMap,
      const std::map<std::string, std::vector<double> > &lowPolynomialCoeffsMap,
      const std::map<std::string, std::vector<double> > &highPolynomialCoeffsMap,
      double universalR,
      stk::mesh::MetaData &metaData);

  virtual ~EnthalpyTYkPropertyEvaluator();
  
  double execute(
      double *indVarList,
      stk::mesh::Entity node);

  double compute_h_rt(
      const double &T,
      const double *pt_poly);

  // field definition and extraction
  GenericFieldType *massFraction_;
  
};

class EnthalpyConstSpecHeatPropertyEvaluator : public PropertyEvaluator
{
public:

  EnthalpyConstSpecHeatPropertyEvaluator(
    const double & specificHeat,
    const double & referenceTemperature);

  virtual ~EnthalpyConstSpecHeatPropertyEvaluator();
  
  double execute(
    double *indVarList,
    stk::mesh::Entity node);

  double specificHeat_;
  double referenceTemperature_;

};

class EnthalpyConstCpkPropertyEvaluator : public PropertyEvaluator
{
public:

  EnthalpyConstCpkPropertyEvaluator(
      const std::map<std::string, double> &cpConstMap,
      const std::map<std::string, double> &hfConstMap,
      stk::mesh::MetaData &metaData,
      const double referenceTemperature);

  virtual ~EnthalpyConstCpkPropertyEvaluator();

  double execute(
      double *indVarList,
      stk::mesh::Entity node);

  // field definition and extraction
  const double referenceTemperature_;
  const size_t cpVecSize_;
  GenericFieldType *massFraction_;
  std::vector<double> cpVec_;
  std::vector<double> hfVec_;
};


} // namespace nalu
} // namespace Sierra

#endif
