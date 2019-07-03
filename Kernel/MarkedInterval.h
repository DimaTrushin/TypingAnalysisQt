#ifndef MARKEDINTERVAL_H
#define MARKEDINTERVAL_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <vector> //pch
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Declaration of CInterval
//---------------------------------------------------------------------------
// The class defines a closed segment [first, second]

class CInterval : public std::pair<double, double> {
public:
  using CBase = std::pair<double, double>;
  CInterval(double first = 0.0, double second = 0.0);
  double getCenter() const;
  double getLength() const;
};
//---------------------------------------------------------------------------
// Declaration of CIntervalContainer
//---------------------------------------------------------------------------

class CIntervalContainer : public std::vector<CInterval> {
public:
  using CBase = std::vector<CInterval>;
};
//---------------------------------------------------------------------------
// Declaration of CRoughMaxMinPair
//---------------------------------------------------------------------------
// first must be an interval with a maximum
// second must be an interval containing the minimum right after the maximum

class CRoughMaxMinPair : public std::pair<CInterval, CInterval> {
public:
  using CBase = std::pair<CInterval, CInterval>;
  CRoughMaxMinPair(const CInterval& RoughMaxInterval,
                   const CInterval& RoughMinInterval);
  CRoughMaxMinPair(CInterval&& RoughMaxInterval,
                   CInterval&& RoughMinInterval);
  CRoughMaxMinPair(const CBase& pair);
  CRoughMaxMinPair(CBase&& pair);
};
//---------------------------------------------------------------------------
// Declaration of CRoughMaxMinPairContainer
//---------------------------------------------------------------------------

class CRoughMaxMinPairContainer : public std::vector<CRoughMaxMinPair> {
public:
  using CBase = std::vector<CRoughMaxMinPair>;
};
//---------------------------------------------------------------------------
// Declaration of CMarkedInterval
//---------------------------------------------------------------------------
// The class defines a closed segment [first, second] with a point inside

class CMarkedInterval : public CInterval {
public:
  using CBase = CInterval;
  CMarkedInterval();
  CMarkedInterval(const CInterval& Interval);
  CMarkedInterval(CInterval&& Interval);
  double point;

  template<class TApproximation>
  class Comparator {
  public:
    Comparator(const TApproximation& Approximation);
    bool operator()(const CMarkedInterval& first,
                    const CMarkedInterval& second) const;
  private:
    const TApproximation* pApproximation_;
  };
};
//---------------------------------------------------------------------------
// Declaration of CMarkedIntervalContainer
//---------------------------------------------------------------------------

class CMarkedIntervalContainer : public std::vector<CMarkedInterval> {
public:
  using CBase = std::vector<CMarkedInterval>;
  void setWithIntervalContainer(const CIntervalContainer& Intervals);
};
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Definition of CMarkedInterval::Comparator
//---------------------------------------------------------------------------

template<class TApproximation>
CMarkedInterval::Comparator<TApproximation>::Comparator(
  const TApproximation& Approximation)
  : pApproximation_(&Approximation) {
}
//---------------------------------------------------------------------------

template<class TApproximation>
bool CMarkedInterval::Comparator<TApproximation>::operator()(
  const CMarkedInterval& first,
  const CMarkedInterval& second) const {
  return  pApproximation_->evaluate0(first.point) >
          pApproximation_->evaluate0(second.point);
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // MARKEDINTERVAL_H
