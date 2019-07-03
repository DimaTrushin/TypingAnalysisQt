#ifndef KEYFILTER_H
#define KEYFILTER_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "Library/DiscreteInterval.h"
#include "VKCode.h"
#include <vector> //pch
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKeyboard {
//---------------------------------------------------------------------------
// Declaration of CKeyInterval
//---------------------------------------------------------------------------

// Intervals of the form [First, Last], where First and Last are VKCodes
class CKeyInterval
  : public NSLibrary::CDiscreteInterval<CVKCode::CVKCodeType> {
public:
  using CBase = NSLibrary::CDiscreteInterval<CVKCode::CVKCodeType>;
  using CVKCodeType = CVKCode::CVKCodeType;

  // TO DO
  // If the base is never empty, we can make
  // the default ctor to be = default;
  // the other two constructors can be replaced by using directive
  // Now the ctors use assert to prevent the empty state in debug mode
  //using CBase::CBase;
  CKeyInterval();
  CKeyInterval(const CVKCodeType& First, const CVKCodeType& Last);
  CKeyInterval(const CVKCodeType& Value);
  CKeyInterval(const CBase& base);

  static CKeyInterval getNumberInterval();
  static CKeyInterval getEnglishSymbolInterval();
};
//---------------------------------------------------------------------------
// Declaration of CKeyFilter
//---------------------------------------------------------------------------

// CKeyIntervals in the CKeyFilter are always:
// 1) non-empty
// 2) disjoint
// 3) sorted by NSLibrary::isLess
class CKeyFilter : protected std::vector<CKeyInterval> {
public:
  using CBase = std::vector<CKeyInterval>;
  using CBase::iterator;
  using CBase::const_iterator;
  using CVKCodeType = CVKCode::CVKCodeType;

  bool isProcessable(CVKCodeType VKCode) const;
  void AddInterval(const CKeyInterval& Interval);
  void RemoveInterval(const CKeyInterval& Interval);

  using CBase::begin;
  using CBase::end;
  using CBase::empty;
  // TO DO
  // This function is a temporary solution.
  // It restricts the zone on keyboard for capturing.
  // There should be different zone names and different functions.
  void setToDefaultFilter();
private:
  bool findFirstAtLeastAdjacent(const CKeyInterval& Interval,
                                iterator* pIterator);
  // this function assumes that the previous one returns true
  void findLastAtLeastAdjacent( const CKeyInterval& Interval,
                                iterator* pIterator);
  bool findFirstIntersecting( const CKeyInterval& Interval,
                              iterator* pIterator);
  // this function assumes that the previous one returns true
  void findLastIntersecting(const CKeyInterval& Interval,
                            iterator* pIterator);
  void removeFromOneInterval( const iterator& Intersection,
                              const CKeyInterval& Interval);
  void removeFromRange( iterator FirstIntersection,
                        iterator LastIntersection,
                        const CKeyInterval& Interval);
};
//---------------------------------------------------------------------------
} // NSKeyboard
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // KEYFILTER_H
