#ifndef DISCRETEINTERVAL_H
#define DISCRETEINTERVAL_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <list> //pch
#include <algorithm> //pch
#include <cassert> //pch
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {
//---------------------------------------------------------------------------
// Declaration of CDiscreteIntervalBase
//---------------------------------------------------------------------------

// TO DO
// rewrite the class such that the interval is never empty
// TO DO
// At least double check
// if everything is correct if at least one of the intervals is empty
// TO DO
// Add enable_if to check that TType is integral type

// Base for intervals of the form [First_, Last_]
template<class TType>
class CDiscreteIntervalBase {
public:
  CDiscreteIntervalBase();
  CDiscreteIntervalBase(const TType& First, const TType& Last);
  CDiscreteIntervalBase(const TType& Value);

  const TType& First() const;
  TType& First();
  const TType& Last() const;
  TType& Last();

  void setToEmpty();
  bool isEmpty() const;
  bool isInInterval(const TType& Element) const;
protected:
  TType First_;
  TType Last_;
};
//---------------------------------------------------------------------------
// Forward Declarations
//---------------------------------------------------------------------------

template<class TType>
class CDiscreteInterval;
//---------------------------------------------------------------------------

template<class TType>
bool isStrictlyLess(
  const CDiscreteInterval<TType>& first,
  const CDiscreteInterval<TType>& second);
//---------------------------------------------------------------------------

template<class TType>
bool isStrictlyLessOrEquivalent(
  const CDiscreteInterval<TType>& first,
  const CDiscreteInterval<TType>& second);
//---------------------------------------------------------------------------

template<class TType>
bool isLess(
  const CDiscreteInterval<TType>& first,
  const CDiscreteInterval<TType>& second);
//---------------------------------------------------------------------------

template<class TType>
bool isLessOrEquivalent(
  const CDiscreteInterval<TType>& first,
  const CDiscreteInterval<TType>& second);
//---------------------------------------------------------------------------

template<class TType>
bool isStrictlyGreater(
  const CDiscreteInterval<TType>& first,
  const CDiscreteInterval<TType>& second);
//---------------------------------------------------------------------------

template<class TType>
bool isStrictlyGreaterOrEquivalent(
  const CDiscreteInterval<TType>& first,
  const CDiscreteInterval<TType>& second);
//---------------------------------------------------------------------------

template<class TType>
bool isGreater(
  const CDiscreteInterval<TType>& first,
  const CDiscreteInterval<TType>& second);
//---------------------------------------------------------------------------

template<class TType>
bool isGreaterOrEquivalent(
  const CDiscreteInterval<TType>& first,
  const CDiscreteInterval<TType>& second);
//---------------------------------------------------------------------------
// Declaration of CDiscreteInterval
//---------------------------------------------------------------------------

template<class TType>
class CDiscreteInterval : public CDiscreteIntervalBase<TType> {
public:
  using CBase = CDiscreteIntervalBase<TType>;
  using CBase::CBase;

  void setToIntersection(const CDiscreteInterval& Interval);
  void setToConvexUnion(const CDiscreteInterval& Interval);

  bool isIntersecting(const CDiscreteInterval& Interval) const;
  bool isCoveredBy(const CDiscreteInterval& Interval) const;
  bool isCovering(const CDiscreteInterval& Interval) const;

  std::list<CDiscreteInterval>getDifference(
    const CDiscreteInterval& Interval) const;
  size_t getNumberOfComponentsInDifference(
    const CDiscreteInterval& Interval) const;
  CDiscreteInterval intersect(const CDiscreteInterval& Interval) const;
  CDiscreteInterval uniteConvexly(const CDiscreteInterval& Interval) const;

  CDiscreteInterval getLeftComponentOfDifference(
    const CDiscreteInterval& Interval) const;
  CDiscreteInterval getRightComponentOfDifference(
    const CDiscreteInterval& Interval) const;

  static CDiscreteInterval getEmptyInterval();

  // These friend functions are applicable only to non empty intervals
  // otherwise they assert in debug mode
  friend bool isStrictlyLess<TType>(
    const CDiscreteInterval& first, const CDiscreteInterval& second);
  friend bool isStrictlyLessOrEquivalent<TType>(
    const CDiscreteInterval& first, const CDiscreteInterval& second);
  friend bool isLess<TType>(
    const CDiscreteInterval& first, const CDiscreteInterval& second);
  friend bool isLessOrEquivalent<TType>(
    const CDiscreteInterval& first, const CDiscreteInterval& second);
  friend bool isStrictlyGreater<TType>(
    const CDiscreteInterval& first, const CDiscreteInterval& second);
  friend bool isStrictlyGreaterOrEquivalent<TType>(
    const CDiscreteInterval& first, const CDiscreteInterval& second);
  friend bool isGreater<TType>(
    const CDiscreteInterval& first, const CDiscreteInterval& second);
  friend bool isGreaterOrEquivalent<TType>(
    const CDiscreteInterval& first, const CDiscreteInterval& second);
private:
  void setLastToMax(const CDiscreteInterval& Interval);
  void setLastToMin(const CDiscreteInterval& Interval);
  void setFirstToMax(const CDiscreteInterval& Interval);
  void setFirstToMin(const CDiscreteInterval& Interval);
};
//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {

//---------------------------------------------------------------------------
// Definition of CDiscreteIntervalBase
//---------------------------------------------------------------------------

template<class TType>
CDiscreteIntervalBase<TType>::CDiscreteIntervalBase()
  : First_(TType()), Last_(TType()) {
}
//---------------------------------------------------------------------------

template<class TType>
CDiscreteIntervalBase<TType>::CDiscreteIntervalBase(
  const TType& First, const TType& Last)
  : First_(First), Last_(Last) {
  // If First_ > Last_ the interval is empty
}
//---------------------------------------------------------------------------

template<class TType>
CDiscreteIntervalBase<TType>::CDiscreteIntervalBase(
  const TType& Value)
  : First_(Value), Last_(Value) {
}
//---------------------------------------------------------------------------

template<class TType>
const TType& CDiscreteIntervalBase<TType>::First() const {
  return First_;
}
//---------------------------------------------------------------------------

template<class TType>
TType& CDiscreteIntervalBase<TType>::First() {
  return First_;
}
//---------------------------------------------------------------------------

template<class TType>
const TType& CDiscreteIntervalBase<TType>::Last() const {
  return Last_;
}
//---------------------------------------------------------------------------

template<class TType>
TType& CDiscreteIntervalBase<TType>::Last() {
  return Last_;
}
//---------------------------------------------------------------------------

template<class TType>
void CDiscreteIntervalBase<TType>::setToEmpty() {
  Last_ = TType();
  First_= Last_ + 1;
}
//---------------------------------------------------------------------------

template<class TType>
bool CDiscreteIntervalBase<TType>::isEmpty() const {
  return First_ > Last_;
}
//---------------------------------------------------------------------------

template<class TType>
bool CDiscreteIntervalBase<TType>::isInInterval(const TType& Element) const {
  return First_ <= Element && Element <= Last_;
}
//---------------------------------------------------------------------------
// Definition of CDiscreteInterval
//---------------------------------------------------------------------------

template<class TType>
void CDiscreteInterval<TType>::setToIntersection(
  const CDiscreteInterval& Interval) {
  setFirstToMax(Interval);
  setLastToMin(Interval);
}
//---------------------------------------------------------------------------

template<class TType>
void CDiscreteInterval<TType>::setToConvexUnion(
  const CDiscreteInterval& Interval) {
  if(Interval.isEmpty())
    return;
  if(isEmpty()) {
    *this = Interval;
    return;
  }
  setFirstToMin(Interval);
  setLastToMax(Interval);
}
//---------------------------------------------------------------------------

template<class TType>
bool CDiscreteInterval<TType>::isIntersecting(
  const CDiscreteInterval& Interval) const {
  return !intersect(Interval).isEmpty();
}
//---------------------------------------------------------------------------

template<class TType>
bool CDiscreteInterval<TType>::isCoveredBy(
  const CDiscreteInterval& Interval) const {
  if(isEmpty())
    return true;
  return Interval.First_ <= CBase::First_ && CBase::Last_ <= Interval.Last_;
}
//---------------------------------------------------------------------------

template<class TType>
bool CDiscreteInterval<TType>::isCovering(
  const CDiscreteInterval& Interval) const {
  return Interval.isCoveredBy(*this);
}
//---------------------------------------------------------------------------

template<class TType>
std::list<CDiscreteInterval<TType>> CDiscreteInterval<TType>::getDifference(
const CDiscreteInterval& Interval) const {
  std::list<CDiscreteInterval> Difference;
  CDiscreteInterval Left = getLeftComponentOfDifference(Interval);
  if(!Left.isEmpty())
    Difference.push_back(Left);

  CDiscreteInterval Right = getRightComponentOfDifference(Interval);
  if(!Right.isEmpty())
    Difference.push_back(Right);
  return Difference;
}
//---------------------------------------------------------------------------

template<class TType>
size_t CDiscreteInterval<TType>::getNumberOfComponentsInDifference(
  const CDiscreteInterval& Interval) const {
  if (isEmpty())
    return 0;
  if (Interval.isEmpty())
    return 1;

  size_t result = 0;
  if (CBase::First_ < Interval.First_)
    ++result;
  if (Interval.Last_ < CBase::Last_)
    ++result;
  return result;
}
//---------------------------------------------------------------------------

template<class TType>
CDiscreteInterval<TType> CDiscreteInterval<TType>::intersect(
  const CDiscreteInterval& Interval) const {
  CDiscreteInterval Intersection(*this);
  Intersection.setToIntersection(Interval);
  return Intersection;
}
//---------------------------------------------------------------------------

template<class TType>
CDiscreteInterval<TType> CDiscreteInterval<TType>::uniteConvexly(
  const CDiscreteInterval& Interval) const {
  CDiscreteInterval ConvexUnion(*this);
  ConvexUnion.setToConvexUnion(Interval);
  return ConvexUnion;
}
//---------------------------------------------------------------------------

template<class TType>
CDiscreteInterval<TType>
CDiscreteInterval<TType>::getLeftComponentOfDifference(
  const CDiscreteInterval& Interval) const {
  if (Interval.isEmpty())
    return *this;
  if (Interval.First_ <= CBase::First_)
    return getEmptyInterval();
  if(!isIntersecting(Interval))
    return *this;
  return CDiscreteInterval(CBase::First_, Interval.First_ - 1);
}
//---------------------------------------------------------------------------

template<class TType>
CDiscreteInterval<TType>
CDiscreteInterval<TType>::getRightComponentOfDifference(
  const CDiscreteInterval& Interval) const {
  // If I subtract an empty interval
  // the difference is considered as a left component
  if (CBase::Last_ <= Interval.Last_ || Interval.isEmpty())
    return getEmptyInterval();
  if(!isIntersecting(Interval))
    return *this;
  return CDiscreteInterval(Interval.Last_ + 1, CBase::Last_);
}
//---------------------------------------------------------------------------

template<class TType>
CDiscreteInterval<TType> CDiscreteInterval<TType>::getEmptyInterval() {
  CDiscreteInterval Interval;
  Interval.setToEmpty();
  return Interval;
}
//---------------------------------------------------------------------------

template<class TType>
void CDiscreteInterval<TType>::setLastToMax(
  const CDiscreteInterval& Interval) {
  CBase::Last_ = std::max(CBase::Last_, Interval.Last_);
}
//---------------------------------------------------------------------------

template<class TType>
void CDiscreteInterval<TType>::setLastToMin(
  const CDiscreteInterval& Interval) {
  CBase::Last_ = std::min(CBase::Last_, Interval.Last_);
}
//---------------------------------------------------------------------------

template<class TType>
void CDiscreteInterval<TType>::setFirstToMax(
  const CDiscreteInterval& Interval) {
  CBase::First_ = std::max(CBase::First_, Interval.First_);
}
//---------------------------------------------------------------------------

template<class TType>
void CDiscreteInterval<TType>::setFirstToMin(
  const CDiscreteInterval& Interval) {
  CBase::First_ = std::min(CBase::First_, Interval.First_);
}
//---------------------------------------------------------------------------
// Definitions of Global Functions
//---------------------------------------------------------------------------

template<class TType>
bool isStrictlyLess(
  const CDiscreteInterval<TType>& first,
  const CDiscreteInterval<TType>& second) {
  assert(!first.isEmpty() && !second.isEmpty());
  // first check is needed to overcome TType overflow
  if (first.Last_ >= second.First_)
    return false;
  return first.Last_ + 1 < second.First_;
}
//---------------------------------------------------------------------------

template<class TType>
bool isStrictlyLessOrEquivalent(
  const CDiscreteInterval<TType>& first,
  const CDiscreteInterval<TType>& second) {
  return !isStrictlyGreater(first, second);
}
//---------------------------------------------------------------------------

template<class TType>
bool isLess(
  const CDiscreteInterval<TType>& first,
  const CDiscreteInterval<TType>& second) {
  assert(!first.isEmpty() && !second.isEmpty());
  return first.Last_ < second.First_;
}
//---------------------------------------------------------------------------

template<class TType>
bool isLessOrEquivalent(
  const CDiscreteInterval<TType>& first,
  const CDiscreteInterval<TType>& second) {
  return !isGreater(first, second);
}
//---------------------------------------------------------------------------

template<class TType>
bool isStrictlyGreater(
  const CDiscreteInterval<TType>& first,
  const CDiscreteInterval<TType>& second) {
  return isStrictlyLess(second, first);
}
//---------------------------------------------------------------------------

template<class TType>
bool isStrictlyGreaterOrEquivalent(
  const CDiscreteInterval<TType>& first,
  const CDiscreteInterval<TType>& second) {
  return !isStrictlyLess(first, second);
}
//---------------------------------------------------------------------------

template<class TType>
bool isGreater(
  const CDiscreteInterval<TType>& first,
  const CDiscreteInterval<TType>& second) {
  return isLess(second, first);
}
//---------------------------------------------------------------------------

template<class TType>
bool isGreaterOrEquivalent(
  const CDiscreteInterval<TType>& first,
  const CDiscreteInterval<TType>& second) {
  return !isLess(first, second);
}
//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // DISCRETEINTERVAL_H
