//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "KeyFilter.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKeyboard {
//---------------------------------------------------------------------------
// Definition Of CKeyInterval
//---------------------------------------------------------------------------

CKeyInterval::CKeyInterval()
  : CBase() {
  assert(!isEmpty());
}
//---------------------------------------------------------------------------

CKeyInterval::CKeyInterval(
  const CVKCodeType& First, const CVKCodeType& Last)
  : CBase(First, Last) {
  assert(!isEmpty());
}
//---------------------------------------------------------------------------

CKeyInterval::CKeyInterval(const CVKCodeType& Value)
  : CBase(Value) {
  assert(!isEmpty());
}
//---------------------------------------------------------------------------

CKeyInterval::CKeyInterval(const CBase& base)
  : CBase(base) {
  assert(!isEmpty());
}
//---------------------------------------------------------------------------

CKeyInterval CKeyInterval::getNumberInterval() {
  return CKeyInterval(CVKCode::VK_0, CVKCode::VK_9);
}
//---------------------------------------------------------------------------

CKeyInterval CKeyInterval::getEnglishSymbolInterval() {
  return CKeyInterval(CVKCode::A, CVKCode::Z);
}
//---------------------------------------------------------------------------
// Definitions of CKeyFilter
//---------------------------------------------------------------------------

bool CKeyFilter::isProcessable(CVKCodeType VKCode) const {
  auto iterator = std::lower_bound(begin(),
                                   end(),
                                   CKeyInterval(VKCode),
                                   NSLibrary::isLess<CVKCodeType>);
  if (iterator == end())
    return false;
  return iterator->isInInterval(VKCode);
}
//---------------------------------------------------------------------------

void CKeyFilter::AddInterval(const CKeyInterval& Interval) {
  assert(!Interval.isEmpty());
  iterator FirstAdjacent;
  if (!findFirstAtLeastAdjacent(Interval, &FirstAdjacent)) {
    insert(FirstAdjacent, Interval);
    return;
  }
  assert(FirstAdjacent->Last() >= Interval.First() ||
         FirstAdjacent->Last() + 1 >= Interval.First());
  iterator LastAdjacent;
  findLastAtLeastAdjacent(Interval, &LastAdjacent);
  assert(LastAdjacent->First() <= Interval.Last() ||
         LastAdjacent->First() <= Interval.Last() + 1);
  LastAdjacent->setToConvexUnion(*FirstAdjacent);
  LastAdjacent->setToConvexUnion(Interval);
  erase(FirstAdjacent, LastAdjacent);
}
//---------------------------------------------------------------------------

void CKeyFilter::RemoveInterval(const CKeyInterval& Interval) {
  iterator FirstIntersection;
  if(!findFirstIntersecting(Interval, &FirstIntersection))
    return;
  assert(FirstIntersection->Last() >= Interval.First());
  iterator LastIntersection;
  findLastIntersecting(Interval, &LastIntersection);
  assert(LastIntersection->First() <= Interval.Last());
  if (FirstIntersection == LastIntersection)
    removeFromOneInterval(FirstIntersection, Interval);
  else
    removeFromRange(FirstIntersection, LastIntersection, Interval);
}
//---------------------------------------------------------------------------

void CKeyFilter::setToDefaultFilter() {
  AddInterval(CKeyInterval::getNumberInterval());
  AddInterval(CKeyInterval::getEnglishSymbolInterval());

  AddInterval(CKeyInterval(CVKCode::Eng_Semicolon,
                           CVKCode::Eng_Slash_Question));
  AddInterval(CKeyInterval(CVKCode::Eng_Left_Brace,
                           CVKCode::Eng_Quote));

  AddInterval(CKeyInterval(CVKCode::Eng_Tilde));
  AddInterval(CKeyInterval(CVKCode::Shift, CVKCode::Alt));
  AddInterval(CKeyInterval(CVKCode::LeftShift, CVKCode::RightAlt));
  AddInterval(CKeyInterval(CVKCode::Capslock));
  AddInterval(CKeyInterval(CVKCode::Enter));
  AddInterval(CKeyInterval(CVKCode::Backspace));
  AddInterval(CKeyInterval(CVKCode::Spacebar));
}
//---------------------------------------------------------------------------

bool CKeyFilter::findFirstAtLeastAdjacent(
  const CKeyInterval& Interval, iterator* pIterator) {
  iterator& Iterator = *pIterator;
  Iterator = std::lower_bound(begin(),
                              end(),
                              Interval,
                              NSLibrary::isStrictlyLess<CVKCodeType>);
  if (Iterator == end())
    return false;
  if (NSLibrary::isStrictlyLess(Interval, *Iterator))
    return false;
  return true;
}
//---------------------------------------------------------------------------

void CKeyFilter::findLastAtLeastAdjacent(
  const CKeyInterval& Interval, iterator* pIterator) {
  iterator& Iterator = *pIterator;
  Iterator = std::upper_bound(begin(),
                              end(),
                              Interval,
                              NSLibrary::isStrictlyLess<CVKCodeType>);
  --Iterator;
}
//---------------------------------------------------------------------------

bool CKeyFilter::findFirstIntersecting( const CKeyInterval& Interval,
                                        iterator* pIterator) {
  iterator& Iterator = *pIterator;
  Iterator = std::lower_bound(begin(),
                              end(),
                              Interval,
                              NSLibrary::isLess<CVKCodeType>);
  if (Iterator == end())
    return false;
  if (NSLibrary::isLess(Interval, *Iterator))
    return false;
  return true;

}
//---------------------------------------------------------------------------

void CKeyFilter::findLastIntersecting( const CKeyInterval& Interval,
                                       iterator* pIterator) {
  iterator& Iterator = *pIterator;
  Iterator = std::upper_bound(begin(),
                              end(),
                              Interval,
                              NSLibrary::isLess<CVKCodeType>);
  --Iterator;
}
//---------------------------------------------------------------------------

void CKeyFilter::removeFromOneInterval( const iterator& Intersection,
                                        const CKeyInterval& Interval) {
  auto Difference = Intersection->getDifference(Interval);
  if (Difference.size() == 0) {
    erase(Intersection);
    return;
  }
  if (Difference.size() == 1) {
    *Intersection = Difference.back();
    return;
  }
  *Intersection = Difference.back();
  insert(Intersection, Difference.front());
}
//---------------------------------------------------------------------------

void CKeyFilter::removeFromRange( iterator FirstIntersection,
                                  iterator LastIntersection,
                                  const CKeyInterval& Interval) {
  *FirstIntersection =
    FirstIntersection->getLeftComponentOfDifference(Interval);
  if (!FirstIntersection->isEmpty())
    ++FirstIntersection;
  *LastIntersection =
    LastIntersection->getRightComponentOfDifference(Interval);
  if (LastIntersection->isEmpty())
    ++LastIntersection;
  erase(FirstIntersection, LastIntersection);
}
//---------------------------------------------------------------------------
} // NSKeyboard
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
