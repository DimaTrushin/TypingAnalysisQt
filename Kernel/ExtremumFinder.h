#ifndef EXTREMUMFINDER_H
#define EXTREMUMFINDER_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "RootFinder.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Declaration of CExtremumFinderDirectEvaluation
//---------------------------------------------------------------------------

template<class TRootFinder>
class CExtremumFinderDirectEvaluation {
public:
  template<class TApproximation>
  static double computeMaximumOnInterval0(
    const TApproximation& Approximation, const CInterval& Interval);

  template<class TApproximation>
  static double computeMaximumOnInterval1(
    const TApproximation& Approximation, const CInterval& Interval);

  template<class TApproximation>
  static double computeMinimumOnInterval1(
    const TApproximation& Approximation, const CInterval& Interval);
private:
  template <EExtremalPointType PointType, class TApproximation>
  inline static double computeExtremumOnInterval0(
    const TApproximation& Approximation, const CInterval& Interval);

  template <EExtremalPointType PointType, class TApproximation>
  inline static double computeExtremumOnInterval1(
    const TApproximation& Approximation, const CInterval& Interval);

  template<class TApproximation>
  inline static bool isSignOnEndsOfIntervalDifferent1(
    const TApproximation& Approximation, const CInterval& Interval);

  template<class TApproximation>
  inline static bool isSignOnEndsOfIntervalDifferent2(
    const TApproximation& Approximation, const CInterval& Interval);
};
//---------------------------------------------------------------------------
// Declaration of CExtremumFinderTemplateEvaluation
//---------------------------------------------------------------------------

template<class TRootFinder>
class CExtremumFinderTemplateEvaluation {
public:
  template <unsigned int derivative, class TApproximation>
  static double computeMaximumOnInterval(
    const TApproximation& Approximation, const CInterval& Interval);

  template <unsigned int derivative, class TApproximation>
  static double computeMinimumOnInterval(
    const TApproximation& Approximation, const CInterval& Interval);
private:
  template <unsigned int derivative,
            EExtremalPointType PointType,
            class TApproximation>
  inline static double computeExtremumOnInterval(
    const TApproximation& Approximation, const CInterval& Interval);

  template <unsigned int derivative, class TApproximation>
  inline static bool isSignOnEndsOfIntervalDifferent(
    const TApproximation& Approximation, const CInterval& Interval);
};
//---------------------------------------------------------------------------
// Declaration of CExtremumFinder
//---------------------------------------------------------------------------

using CExtremumFinder = CExtremumFinderDirectEvaluation<CRootFinder>;
//---------------------------------------------------------------------------
// Declaration of CExtremumFinderT
//---------------------------------------------------------------------------

using CExtremumFinderT = CExtremumFinderTemplateEvaluation<CRootFinderT>;
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Definition of CExtremumFinderDirectEvaluation
//---------------------------------------------------------------------------

template<class TRootFinder>
template<class TApproximation>
double
CExtremumFinderDirectEvaluation<TRootFinder>::computeMaximumOnInterval0(
  const TApproximation& Approximation, const CInterval& Interval) {
  return computeExtremumOnInterval0<EExtremalPointType::Maximum>(
           Approximation, Interval);
}
//---------------------------------------------------------------------------

template<class TRootFinder>
template<class TApproximation>
double
CExtremumFinderDirectEvaluation<TRootFinder>::computeMaximumOnInterval1(
  const TApproximation& Approximation, const CInterval& Interval) {
  return computeExtremumOnInterval1<EExtremalPointType::Maximum>(
           Approximation, Interval);
}
//---------------------------------------------------------------------------

template<class TRootFinder>
template<class TApproximation>
double
CExtremumFinderDirectEvaluation<TRootFinder>::computeMinimumOnInterval1(
  const TApproximation& Approximation, const CInterval& Interval) {
  return computeExtremumOnInterval1<EExtremalPointType::Minimum>(
           Approximation, Interval);
}
//---------------------------------------------------------------------------

template<class TRootFinder>
template <EExtremalPointType PointType, class TApproximation>
double
CExtremumFinderDirectEvaluation<TRootFinder>::computeExtremumOnInterval0(
  const TApproximation& Approximation, const CInterval& Interval) {
  if (!isSignOnEndsOfIntervalDifferent1(Approximation, Interval)) {
    // Extremum is on the boundary
    if (isFirstExtremum<PointType>(
          Approximation.evaluate0(Interval.first),
          Approximation.evaluate0(Interval.second)))
      return Interval.first;
    return Interval.second;
  }
  // Extremum is internal (= zero of the derivative)
  return TRootFinder::findRoot1(Approximation, Interval);
}
//---------------------------------------------------------------------------

template<class TRootFinder>
template <EExtremalPointType PointType, class TApproximation>
double
CExtremumFinderDirectEvaluation<TRootFinder>::computeExtremumOnInterval1(
  const TApproximation& Approximation, const CInterval& Interval) {
  if (!isSignOnEndsOfIntervalDifferent2(Approximation, Interval)) {
    // Extremum is on the boundary
    if (isFirstExtremum<PointType>(
          Approximation.evaluate1(Interval.first),
          Approximation.evaluate1(Interval.second)))
      return Interval.first;
    return Interval.second;
  }
  // Extremum is internal (= zero of the derivative)
  return TRootFinder::findRoot2(Approximation, Interval);
}
//---------------------------------------------------------------------------

template<class TRootFinder>
template<class TApproximation>
bool
CExtremumFinderDirectEvaluation<TRootFinder>::
isSignOnEndsOfIntervalDifferent1(
  const TApproximation& Approximation, const CInterval& Interval) {
  return
    Approximation.evaluate1(Interval.first) *
    Approximation.evaluate1(Interval.second) < 0.0;
}
//---------------------------------------------------------------------------

template<class TRootFinder>
template<class TApproximation>
bool
CExtremumFinderDirectEvaluation<TRootFinder>::
isSignOnEndsOfIntervalDifferent2(
  const TApproximation& Approximation, const CInterval& Interval) {
  return
    Approximation.evaluate2(Interval.first) *
    Approximation.evaluate2(Interval.second) < 0.0;
}
//---------------------------------------------------------------------------
// Definition of CExtremumFinderTemplateEvaluation
//---------------------------------------------------------------------------

template<class TRootFinder>
template <unsigned int derivative, class TApproximation>
double
CExtremumFinderTemplateEvaluation<TRootFinder>::computeMaximumOnInterval(
  const TApproximation& Approximation, const CInterval& Interval) {
  return computeExtremumOnInterval<derivative, EExtremalPointType::Maximum>(
           Approximation, Interval);
}
//---------------------------------------------------------------------------

template<class TRootFinder>
template <unsigned int derivative, class TApproximation>
double
CExtremumFinderTemplateEvaluation<TRootFinder>::computeMinimumOnInterval(
  const TApproximation& Approximation, const CInterval& Interval) {
  return computeExtremumOnInterval<derivative, EExtremalPointType::Minimum>(
           Approximation, Interval);
}
//---------------------------------------------------------------------------

template<class TRootFinder>
template<unsigned int derivative,
         EExtremalPointType PointType,
         class TApproximation>
double
CExtremumFinderTemplateEvaluation<TRootFinder>::computeExtremumOnInterval(
  const TApproximation& Approximation, const CInterval& Interval) {
  if (!isSignOnEndsOfIntervalDifferent<derivative + 1>( Approximation,
      Interval)) {
    // Extremum is on the boundary
    if (isFirstExtremum<PointType>(
          Approximation.template evaluate<derivative>(Interval.first),
          Approximation.template evaluate<derivative>(Interval.second)))
      return Interval.first;
    return Interval.second;
  }
  // Extremum is internal (= zero of the derivative)
  return TRootFinder::template findRoot<derivative + 1>(
    Approximation, Interval);
}
//---------------------------------------------------------------------------

template<class TRootFinder>
template <unsigned int derivative, class TApproximation>
bool
CExtremumFinderTemplateEvaluation<TRootFinder>::
isSignOnEndsOfIntervalDifferent(
  const TApproximation& Approximation, const CInterval& Interval) {
  return
    Approximation.template evaluate<derivative>(Interval.first) *
    Approximation.template evaluate<derivative>(Interval.second) < 0.0;
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // EXTREMUMFINDER_H
