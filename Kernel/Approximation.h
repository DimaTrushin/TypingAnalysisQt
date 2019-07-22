#ifndef APPROXIMATION_H
#define APPROXIMATION_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <vector> //pch
#include <numeric> //pch
#include <algorithm> //pch
#include "FunctionGridDefault.h"
#include "Library/SmoothFunction.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Declaration of CApproximationDefinitions
//---------------------------------------------------------------------------

class CApproximationDefinitions {
public:
  using CMeanDataContainer = std::vector<double>;
  using CMeanDataConstIterator = CMeanDataContainer::const_iterator;
  using CMeanDataIterator = CMeanDataContainer::iterator;
  using CDoublePair = std::pair<double, double>;
  using CMeanDataConstIteratorPair = std::pair< CMeanDataConstIterator,
        CMeanDataConstIterator>;
};
//---------------------------------------------------------------------------
// Declaration of CSpeedDefinitions
//---------------------------------------------------------------------------

class CSpeedDefinitions : public CApproximationDefinitions,
  public CSpeedGridDefault {
public:
  using CGridDefault = CSpeedGridDefault;
  // double = symbolsPerMinute
  // active range = [kMinimumValue, kMaximumValue]
  // with step = kStep and number of steps = kNumberOfSteps
  static constexpr double kDeviationCoefficient = 2.5;
  static constexpr double kUniformDeviation = 50.0;
  static constexpr double kDerivativeScaleCoefficient = 100.0;
  static constexpr double kHistogramChunk = 5.0;
protected:
  double getDeviation(double mean) const;
  CDoublePair getChunkOfValues(double argument, double chunk) const;
  double directRescale(double argument) const;
  double reverseRescale(double argument) const;
};
//---------------------------------------------------------------------------
// Declaration of CTimeDefinitions
//---------------------------------------------------------------------------

// TO DO
// Need to define all constants for Time Approximation
//class CTimeDefinitions : public CApproximationDefinitions,
//                         public CTimeGridDefault {
//};
//---------------------------------------------------------------------------
// Declaration of CApproximationBase
//---------------------------------------------------------------------------

template<class TModeDefinitions>
class CApproximationBase : protected TModeDefinitions {
  using CBase = TModeDefinitions;
  using CMeanDataContainer = typename CBase::CMeanDataContainer;
  using CDoublePair = typename CBase::CDoublePair;
public:
  using CGridDefault = typename CBase::CGridDefault;
  using CMeanDataConstIteratorPair = typename CBase::CMeanDataConstIteratorPair;
  CApproximationBase() = default;
  CApproximationBase(const CMeanDataContainer& MeanData);
  CApproximationBase(CMeanDataContainer&& MeanData);
  void setApproximation(const CMeanDataContainer& MeanData);
  void setApproximation(CMeanDataContainer&& MeanData);

  double evaluateHistogram(double argument, double chunk) const;

  size_t getNumberOfSamples() const;
  size_t getNumberOfSamplesLessThan(double delimiter) const;
  bool isEmpty() const;
  double getDiscreteMean() const;
  double getDiscreteDeviation() const;

  using CBase::kDerivativeScaleCoefficient;
  using CBase::kHistogramChunk;
protected:
  CMeanDataConstIteratorPair
  getChunkOfMeanData(const CDoublePair& ChunkOfValues) const;
  CMeanDataContainer MeanData_;
};
//---------------------------------------------------------------------------
// Global Functions
//---------------------------------------------------------------------------

double StandardDistribution(double argument);
//---------------------------------------------------------------------------
// Declaration of CApproximationDirectEvaluate
//---------------------------------------------------------------------------

template<class TApproximationBase>
class CApproximationDirectEvaluate : public TApproximationBase {
  using CBase = TApproximationBase;
public:
  using CGridDefault = typename CBase::CGridDefault;
  using CBase::CBase;
  inline double evaluate0(double argument) const;
  inline double evaluate1(double argument) const;
  inline double evaluate2(double argument) const;
  inline double evaluate3(double argument) const;

  inline double evaluateUniform0(double argument) const;
  inline double evaluateUniform1(double argument) const;
  inline double evaluateUniform2(double argument) const;
  inline double evaluateUniform3(double argument) const;
protected:
  template<class TMethod>
  double evaluateMethod(const TMethod& Method, double argument) const;

  double evaluate0At( double argument, double mean) const;
  double evaluate1At( double argument, double mean) const;
  double evaluate2At( double argument, double mean) const;
  double evaluate3At( double argument, double mean) const;

  double evaluateUniform0At( double argument, double mean) const;
  double evaluateUniform1At( double argument, double mean) const;
  double evaluateUniform2At( double argument, double mean) const;
  double evaluateUniform3At( double argument, double mean) const;
};
//---------------------------------------------------------------------------
// Declaration of CApproximationTemplateEvaluate
//---------------------------------------------------------------------------

template<class TApproximationBase>
class CApproximationTemplateEvaluate : public TApproximationBase {
  using CBase = TApproximationBase;
  using CTStandardNormalDensity = NSLibrary::CTStandardNormalDensity;
  template<class F, unsigned int derivative>
  using CTSuccessiveDerivative =
    NSLibrary::CTSuccessiveDerivative<F, derivative>;
  template<unsigned int derivative>
  using CTStandardNormalDensityDerivative =
    CTSuccessiveDerivative<CTStandardNormalDensity, derivative>;
  // Define short-named form for convenience
  template<unsigned int derivative>
  using CTDensity = CTStandardNormalDensityDerivative<derivative>;
public:
  using CGridDefault = typename CBase::CGridDefault;
  using CBase::CBase;
  template<unsigned int derivative>
  double evaluate(double argument) const;
  template<unsigned int derivative>
  double evaluateUniform(double argument) const;
protected:
  template<unsigned int derivative>
  double evaluateAt(double argument, double mean) const;

  template<unsigned int derivative>
  double evaluateUniformAt(double argument, double mean) const;
};
//---------------------------------------------------------------------------
// Declaration of CSpeedApproximation
//---------------------------------------------------------------------------

using CSpeedApproximation =
  CApproximationTemplateEvaluate<
  CApproximationDirectEvaluate<
  CApproximationBase<
  CSpeedDefinitions>>>;
//---------------------------------------------------------------------------
// Declaration of CTimeApproximation
//---------------------------------------------------------------------------

//using CTimeApproximation =
//        CApproximationTemplateEvaluate<
//          CApproximationDirectEvaluate<
//            CApproximationBase<
//              CTimeDefinitions>>>;
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Definition of CApproximationBase
//---------------------------------------------------------------------------

template<class TModeDefinitions>
CApproximationBase<TModeDefinitions>::
CApproximationBase(const CMeanDataContainer& MeanData)
  : MeanData_(MeanData) {
  std::sort(MeanData_.begin(), MeanData_.end());
}
//---------------------------------------------------------------------------

template<class TModeDefinitions>
CApproximationBase<TModeDefinitions>::
CApproximationBase(CMeanDataContainer&& MeanData)
  : MeanData_(MeanData) {
  std::sort(MeanData_.begin(), MeanData_.end());
}
//---------------------------------------------------------------------------

template<class TModeDefinitions>
void
CApproximationBase<TModeDefinitions>::
setApproximation(const CMeanDataContainer& MeanData) {
  MeanData_ = MeanData;
  std::sort(MeanData_.begin(), MeanData_.end());
}
//---------------------------------------------------------------------------

template<class TModeDefinitions>
void
CApproximationBase<TModeDefinitions>::
setApproximation(CMeanDataContainer&& MeanData) {
  MeanData_ = MeanData;
  std::sort(MeanData_.begin(), MeanData_.end());
}
//---------------------------------------------------------------------------

template<class TModeDefinitions>
double
CApproximationBase<TModeDefinitions>::
evaluateHistogram(double argument, double chunk) const {
  if (MeanData_.empty())
    return 0.0;
  auto ChunkOfValues = CBase::getChunkOfValues(argument, chunk);
  auto ChunkOfMeanData = getChunkOfMeanData(ChunkOfValues);
  double chunkSize = ChunkOfValues.second - ChunkOfValues.first;
  double elementsInChunk = ChunkOfMeanData.second - ChunkOfMeanData.first;
  if (!(chunkSize > 0))
    return 0.0;
  return elementsInChunk / (static_cast<double>(MeanData_.size()) * chunkSize);
}
//---------------------------------------------------------------------------

template<class TModeDefinitions>
size_t CApproximationBase<TModeDefinitions>::getNumberOfSamples() const {
  return MeanData_.size();
}
//---------------------------------------------------------------------------

template<class TModeDefinitions>
size_t CApproximationBase<TModeDefinitions>::
getNumberOfSamplesLessThan(double delimiter) const {
  auto itDelimiter =
    std::lower_bound(MeanData_.begin(), MeanData_.end(), delimiter);
  return itDelimiter - MeanData_.begin();
}
//---------------------------------------------------------------------------

template<class TModeDefinitions>
bool CApproximationBase<TModeDefinitions>::isEmpty() const {
  return MeanData_.empty();
}
//---------------------------------------------------------------------------

template<class TModeDefinitions>
double CApproximationBase<TModeDefinitions>::getDiscreteMean() const {
  if (MeanData_.empty())
    return 0.0;
  double mean = std::accumulate(MeanData_.begin(), MeanData_.end(), 0.0);
  mean /= static_cast<double>(MeanData_.size());
  return mean;
}
//---------------------------------------------------------------------------

template<class TModeDefinitions>
double CApproximationBase<TModeDefinitions>::getDiscreteDeviation() const {
  if (MeanData_.size() < 2)
    return 0.0;
  double mean = getDiscreteMean();
  double deviation = 0.0;
  size_t size = MeanData_.size();
  for (size_t index = 0; index < size; ++index)
    deviation += (MeanData_[index] - mean) * (MeanData_[index] - mean);
  deviation /= static_cast<double>(size - 1);
  deviation = std::sqrt(deviation);
  return deviation;
}
//---------------------------------------------------------------------------

template<class TModeDefinitions>
typename
CApproximationBase<TModeDefinitions>::
CMeanDataConstIteratorPair
CApproximationBase<TModeDefinitions>::getChunkOfMeanData(
  const CDoublePair& ChunkOfValues) const {
  auto leftPosition =
    std::lower_bound(MeanData_.begin(), MeanData_.end(), ChunkOfValues.first);
  auto rightPosition =
    std::lower_bound(MeanData_.begin(), MeanData_.end(), ChunkOfValues.second);
  return CMeanDataConstIteratorPair(leftPosition, rightPosition);
}
//---------------------------------------------------------------------------
// Definition of CApproximationDirectEvaluate
//---------------------------------------------------------------------------

template<class TApproximationBase>
double CApproximationDirectEvaluate<TApproximationBase>::
evaluate0(double argument) const {
  return evaluateMethod(&CApproximationDirectEvaluate::evaluate0At, argument);
}
//---------------------------------------------------------------------------

template<class TApproximationBase>
double CApproximationDirectEvaluate<TApproximationBase>::
evaluate1(double argument) const {
  return evaluateMethod(&CApproximationDirectEvaluate::evaluate1At, argument);
}
//---------------------------------------------------------------------------

template<class TApproximationBase>
double CApproximationDirectEvaluate<TApproximationBase>::
evaluate2(double argument) const {
  return evaluateMethod(&CApproximationDirectEvaluate::evaluate2At, argument);
}
//---------------------------------------------------------------------------

template<class TApproximationBase>
double CApproximationDirectEvaluate<TApproximationBase>::
evaluate3(double argument) const {
  return evaluateMethod(&CApproximationDirectEvaluate::evaluate3At, argument);
}
//---------------------------------------------------------------------------

template<class TApproximationBase>
double CApproximationDirectEvaluate<TApproximationBase>::
evaluateUniform0(double argument) const {
  return evaluateMethod(&CApproximationDirectEvaluate::evaluateUniform0At, argument);
}
//---------------------------------------------------------------------------

template<class TApproximationBase>
double CApproximationDirectEvaluate<TApproximationBase>::
evaluateUniform1(double argument) const {
  return evaluateMethod(&CApproximationDirectEvaluate::evaluateUniform1At, argument);
}
//---------------------------------------------------------------------------

template<class TApproximationBase>
double CApproximationDirectEvaluate<TApproximationBase>::
evaluateUniform2(double argument) const {
  return evaluateMethod(&CApproximationDirectEvaluate::evaluateUniform2At, argument);
}
//---------------------------------------------------------------------------

template<class TApproximationBase>
double CApproximationDirectEvaluate<TApproximationBase>::
evaluateUniform3(double argument) const {
  return evaluateMethod(&CApproximationDirectEvaluate::evaluateUniform3At, argument);
}
//---------------------------------------------------------------------------

template<class TApproximationBase>
template<class TMethod>
double
CApproximationDirectEvaluate<TApproximationBase>::
evaluateMethod(const TMethod& Method, double argument) const {
  if (CBase::MeanData_.empty())
    return 0.0;
  double result = 0.0;
  size_t size = CBase::MeanData_.size();
  for (size_t index = 0; index < size; ++index)
    result += (Method)(argument, CBase::MeanData_[index]);
  result /= static_cast<double>(size);
  return result;
}
//---------------------------------------------------------------------------

template<class TApproximationBase>
double CApproximationDirectEvaluate<TApproximationBase>::
evaluate0At(double argument,
            double mean) const {
  double deviation = CBase::getDeviation(mean);
  argument -= mean;
  argument /= deviation;
  return StandardDistribution(argument) / deviation;
}
//---------------------------------------------------------------------------

template<class TApproximationBase>
double CApproximationDirectEvaluate<TApproximationBase>::
evaluate1At(double argument,
            double mean) const {
  double deviation = CBase::getDeviation(mean);
  argument -= mean;
  argument /= deviation;
  return - StandardDistribution(argument) * argument / (deviation * deviation);
}
//---------------------------------------------------------------------------

template<class TApproximationBase>
double CApproximationDirectEvaluate<TApproximationBase>::
evaluate2At(double argument,
            double mean) const {
  double deviation = CBase::getDeviation(mean);
  argument -= mean;
  argument /= deviation;
  return StandardDistribution(argument) *
         (argument * argument - 1.0) /
         (deviation * deviation * deviation);
}
//---------------------------------------------------------------------------

template<class TApproximationBase>
double CApproximationDirectEvaluate<TApproximationBase>::
evaluate3At(double argument,
            double mean) const {
  double deviation = CBase::getDeviation(mean);
  argument -= mean;
  argument /= deviation;
  return StandardDistribution(argument) *
         argument *
         (2.0 / deviation + 1.0 - argument * argument) /
         (deviation * deviation * deviation);
}
//---------------------------------------------------------------------------

template<class TApproximationBase>
double CApproximationDirectEvaluate<TApproximationBase>::
evaluateUniform0At( double argument,
                    double mean) const {
  argument -= mean;
  argument /= CBase::kUniformDeviation;
  return StandardDistribution(argument) / CBase::kUniformDeviation;
}
//---------------------------------------------------------------------------

template<class TApproximationBase>
double CApproximationDirectEvaluate<TApproximationBase>::
evaluateUniform1At( double argument,
                    double mean) const {
  argument -= mean;
  argument /= CBase::kUniformDeviation;
  return - StandardDistribution(argument) * argument /
         (CBase::kUniformDeviation * CBase::kUniformDeviation);
}
//---------------------------------------------------------------------------

template<class TApproximationBase>
double CApproximationDirectEvaluate<TApproximationBase>::
evaluateUniform2At( double argument,
                    double mean) const {
  argument -= mean;
  argument /= CBase::kUniformDeviation;
  return StandardDistribution(argument) *
         (argument * argument - 1.0) /
         ( CBase::kUniformDeviation *
           CBase::kUniformDeviation *
           CBase::kUniformDeviation);
}
//---------------------------------------------------------------------------

template<class TApproximationBase>
double CApproximationDirectEvaluate<TApproximationBase>::
evaluateUniform3At( double argument,
                    double mean) const {
  argument -= mean;
  argument /= CBase::kUniformDeviation;
  return StandardDistribution(argument) *
         argument *
         (2.0 / CBase::kUniformDeviation + 1.0 - argument * argument) /
         ( CBase::kUniformDeviation *
           CBase::kUniformDeviation *
           CBase::kUniformDeviation);
}
//---------------------------------------------------------------------------
// Definition of CApproximationTemplateEvaluate
//---------------------------------------------------------------------------

template<class TApproximationBase>
template<unsigned int derivative>
double
CApproximationTemplateEvaluate<TApproximationBase>::
evaluate(double argument) const {
  if (CBase::MeanData_.empty())
    return 0.0;
  double result = 0.0;
  size_t size = CBase::MeanData_.size();
  for (size_t index = 0; index < size; ++index)
    result += evaluateAt<derivative>(argument, CBase::MeanData_[index]);
  result /= static_cast<double>(size);
  return result;
}
//---------------------------------------------------------------------------

template<class TApproximationBase>
template<unsigned int derivative>
double
CApproximationTemplateEvaluate<TApproximationBase>::
evaluateUniform(double argument) const {
  if (CBase::MeanData_.empty())
    return 0.0;
  double result = 0.0;
  size_t size = CBase::MeanData_.size();
  for (size_t index = 0; index < size; ++index)
    result += evaluateUniformAt<derivative>(argument, CBase::MeanData_[index]);
  result /= static_cast<double>(size);
  return result;
}
//---------------------------------------------------------------------------

template<class TApproximationBase>
template<unsigned int derivative>
double
CApproximationTemplateEvaluate<TApproximationBase>::
evaluateAt( double argument,
            double mean) const {
  double deviation = CBase::getDeviation(mean);
  argument -= mean;
  argument /= deviation;
  return  CTDensity<derivative>::evaluate(argument) /
          NSLibrary::CTPower<derivative + 1>::evaluate(deviation);
}
//---------------------------------------------------------------------------

template<class TApproximationBase>
template<unsigned int derivative>
double
CApproximationTemplateEvaluate<TApproximationBase>::
evaluateUniformAt(double argument,
                  double mean) const {
  argument -= mean;
  argument /= CBase::kUniformDeviation;
  return  CTDensity<derivative>::evaluate(argument) /
          NSLibrary::CTPower<derivative + 1>::evaluate(CBase::kUniformDeviation);
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // APPROXIMATION_H
