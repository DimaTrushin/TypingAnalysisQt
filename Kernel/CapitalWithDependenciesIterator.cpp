//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "CapitalWithDependenciesIterator.h"
#include <cassert> //pch
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Definitions of CCapitalWithDependenciesIterator
//---------------------------------------------------------------------------

CCapitalWithDependenciesIterator::
CCapitalWithDependenciesIterator(
  const CCapWDepCont& CapitalContainer,
  const CSession& Session,
  ETextMode textMode,
  ECapitalMode capitalMode,
  ECapitalType capitalType)
  : pCapitalContainer_(&CapitalContainer),
    pSession_(&Session),
    TextMode_(textMode),
    CapitalMode_(capitalMode),
    CapitalType_(capitalType),
    CurrentPosition_(getBegin()) {
}
//---------------------------------------------------------------------------

ETextFormat CCapitalWithDependenciesIterator::getTextFormat() const {
  if (CapitalType_ == ECapitalType::Shift) {
    if (isEssential())
      return ETextFormat::EssentialShiftFormat;
    return ETextFormat::ShiftFormat;
  }
  if (CapitalType_ == ECapitalType::Capslock) {
    if (isEssential())
      return ETextFormat::EssentialCapslockFormat;
    return ETextFormat::CapslockFormat;
  }
  return ETextFormat::SystemKey;
}
//---------------------------------------------------------------------------

CFormatStructure
CCapitalWithDependenciesIterator::getTextFormatStructure() const {
  return CFormatStructure(getTextFormat(), getDependencyNumber());
}
//---------------------------------------------------------------------------

wchar_t CCapitalWithDependenciesIterator::getSymbol() const {
  return CurrentPosition_->getIterator()->getSystemKeySymbol();
}
//---------------------------------------------------------------------------

CCapitalWithDependenciesIterator::CVKCodeType
CCapitalWithDependenciesIterator::getVKCode() const {
  return CurrentPosition_->getIterator()->getVKCode();
}
//---------------------------------------------------------------------------

bool CCapitalWithDependenciesIterator::isValid() const {
  if (pCapitalContainer_ == nullptr)
    return false;
  return CurrentPosition_ != getEnd();
}
//---------------------------------------------------------------------------

microseconds
CCapitalWithDependenciesIterator::getPressingTime() const {
  return CurrentPosition_->getIterator()->getPressingTime();
}
//---------------------------------------------------------------------------

microseconds
CCapitalWithDependenciesIterator::getReleasingTime() const {
  return CurrentPosition_->getIterator()->getReleasingTime();
}
//---------------------------------------------------------------------------

void CCapitalWithDependenciesIterator::setNext() {
  if (CapitalMode_ == ECapitalMode::Non)
    return;
  ++CurrentPosition_;
  if (CapitalMode_ == ECapitalMode::All)
    return;
  assert(CapitalMode_ == ECapitalMode::Essential);
  moveUntilEssential(TextMode_, &CurrentPosition_);
}
//---------------------------------------------------------------------------

microseconds
CCapitalWithDependenciesIterator::
getPhysicalResponseTime() const {
  return pSession_->getResponseTime(CurrentPosition_->getIterator());
}
//---------------------------------------------------------------------------

bool CCapitalWithDependenciesIterator::isEssential() const {
  return CurrentPosition_->isEssential(TextMode_);
}
//---------------------------------------------------------------------------

CCapitalWithDependenciesContainer::const_iterator
CCapitalWithDependenciesIterator::getBegin() const {
  if (CapitalMode_ == ECapitalMode::All)
    return pCapitalContainer_->begin();
  if (CapitalMode_ == ECapitalMode::Non)
    return pCapitalContainer_->end();
  assert(CapitalMode_ == ECapitalMode::Essential);
  return getEssentialBegin();
}
//---------------------------------------------------------------------------

CCapitalWithDependenciesContainer::const_iterator
CCapitalWithDependenciesIterator::getEssentialBegin() const {
  CCapWDepCont::const_iterator
  itBegin = pCapitalContainer_->begin();
  moveUntilEssential(TextMode_, &itBegin);
  return itBegin;
}
//---------------------------------------------------------------------------

CCapitalWithDependenciesContainer::const_iterator
CCapitalWithDependenciesIterator::getEnd() const {
  return pCapitalContainer_->end();
}
//---------------------------------------------------------------------------

void CCapitalWithDependenciesIterator::moveUntilEssential(
  ETextMode TextMode,
  CCapWDepCont::const_iterator* pIterator) const {
  CCapWDepCont::const_iterator& Iterator = *pIterator;
  while (Iterator != getEnd()) {
    if (Iterator->isEssential(TextMode))
      break;
    ++Iterator;
  }
}
//---------------------------------------------------------------------------

unsigned int CCapitalWithDependenciesIterator::getDependencyNumber() const {
  if (TextMode_ == ETextMode::Full)
    return CurrentPosition_->getNumberOfDependentFullKeys();
  assert(TextMode_ == ETextMode::Printed);
  return CurrentPosition_->getNumberOfDependentPrintedKeys();
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
