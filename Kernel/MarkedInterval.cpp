//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "MarkedInterval.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Definition of CInterval
//---------------------------------------------------------------------------

CInterval::CInterval(double first, double second)
  : CBase(first, second) {
}
//---------------------------------------------------------------------------

double CInterval::getCenter() const {
  return (first + second) / 2.0;
}
//---------------------------------------------------------------------------

double CInterval::getLength() const {
  return second - first;
}
//---------------------------------------------------------------------------
// Definitions of CRoughMaxMinPair
//---------------------------------------------------------------------------

CRoughMaxMinPair::CRoughMaxMinPair(
  const CInterval& RoughMaxInterval,
  const CInterval& RoughMinInterval)
  : CBase(RoughMaxInterval, RoughMinInterval) {
}
//---------------------------------------------------------------------------

CRoughMaxMinPair::CRoughMaxMinPair(
  CInterval&& RoughMaxInterval,
  CInterval&& RoughMinInterval)
  : CBase(RoughMaxInterval, RoughMinInterval) {
}
//---------------------------------------------------------------------------

CRoughMaxMinPair::CRoughMaxMinPair(const CBase& pair)
  : CBase(pair) {
}
//---------------------------------------------------------------------------

CRoughMaxMinPair::CRoughMaxMinPair(CBase&& pair)
  : CBase(pair) {
}
//---------------------------------------------------------------------------
// Definition of CMarkedInterval
//---------------------------------------------------------------------------

CMarkedInterval::CMarkedInterval()
  : CBase(), point(0.0) {
}
//---------------------------------------------------------------------------

CMarkedInterval::CMarkedInterval(const CInterval& Interval)
  : CBase(Interval), point(Interval.getCenter()) {
}
//---------------------------------------------------------------------------

CMarkedInterval::CMarkedInterval(CInterval&& Interval)
  : CBase(Interval), point(Interval.getCenter()) {
}
//---------------------------------------------------------------------------
// Definition of CMarkedIntervalContainer
//---------------------------------------------------------------------------

void CMarkedIntervalContainer::setWithIntervalContainer(
  const CIntervalContainer& Intervals) {
  clear();
  size_t size = Intervals.size();
  resize(size);
  for (size_t index = 0; index < size; ++index)
    (*this)[index] = CMarkedInterval(Intervals[index]);
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
