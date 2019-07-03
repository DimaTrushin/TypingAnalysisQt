//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "SymbolIterator.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Definition of CSymbolIterator
//---------------------------------------------------------------------------

CSymbolIterator::CSymbolIterator(const CTextDataTree& TextTree,
                                 ETextMode mode,
                                 ESymbolIteratorStart BeginFrom)
  : pHostTree_(&TextTree),
    IteratorMode_(mode),
    CurrentPosition_(TextTree.beginFromRoot()) {
  if (BeginFrom == ESymbolIteratorStart::FromTextBegin)
    CurrentPosition_ = TextTree.beginText(mode);
}
//---------------------------------------------------------------------------

ETextFormat CSymbolIterator::getTextFormat() const {
  if (getSymbolStatus() == ESymbolStatus::TextSymbol)
    return ETextFormat::MainText;
  if (getSymbolStatus() == ESymbolStatus::DeletedSymbolAccidental)
    return ETextFormat::DeletedTextAccidental;
  if (getSymbolStatus() == ESymbolStatus::DeletedSymbolRequired)
    return ETextFormat::DeletedTextRequired;
  if (getSymbolStatus() == ESymbolStatus::MistakeSymbol)
    return ETextFormat::MistakenSymbol;
  if (getSymbolStatus() == ESymbolStatus::RootSymbol)
    return ETextFormat::SessionDelimiter;
  // any unknown key has MainText format
  return ETextFormat::MainText;
}
//---------------------------------------------------------------------------

CFormatStructure CSymbolIterator::getTextFormatStructure() const {
  return CFormatStructure(getTextFormat(), getDepth());
}
//---------------------------------------------------------------------------

wchar_t CSymbolIterator::getSymbol() const {
  return CurrentPosition_->getSymbol();
}
//---------------------------------------------------------------------------

CSymbolIterator::CCKCodeType CSymbolIterator::getVKCode() const {
  return CurrentPosition_->getVKCode();
}
//---------------------------------------------------------------------------

bool CSymbolIterator::isValid() const {
  if (pHostTree_ == nullptr)
    return false;
  return CurrentPosition_ != pHostTree_->endText(IteratorMode_);
}
//---------------------------------------------------------------------------

microseconds CSymbolIterator::getPressingTime() const {
  return CurrentPosition_->getPressingTime();
}
//---------------------------------------------------------------------------

microseconds CSymbolIterator::getReleasingTime() const {
  return CurrentPosition_->getReleasingTime();
}
//---------------------------------------------------------------------------

void CSymbolIterator::setNext() {
  if (IteratorMode_ == ETextMode::Full)
    setNextFull();
  else {
    assert(IteratorMode_ == ETextMode::Printed);
    setNextNonFull();
  }
}
//---------------------------------------------------------------------------

microseconds CSymbolIterator::getPhysicalResponseTime() const {
  return CurrentPosition_->getResponseTime();
}
//---------------------------------------------------------------------------

void CSymbolIterator::setNextFull() {
  CTextDataTree::CConstFullTextIterator next(CurrentPosition_);
  ++next;
  CurrentPosition_ = next;
}
//---------------------------------------------------------------------------

void CSymbolIterator::setNextNonFull() {
  CTextDataTree::CConstTextIterator next(CurrentPosition_);
  ++next;
  CurrentPosition_ = next;
}
//---------------------------------------------------------------------------

ESymbolStatus CSymbolIterator::getSymbolStatus() const {
  return CurrentPosition_->getSymbolStatus();
}
//---------------------------------------------------------------------------

unsigned int CSymbolIterator::getDepth() const {
  if (getSymbolStatus() == ESymbolStatus::RootSymbol ||
      getSymbolStatus() == ESymbolStatus::TextSymbol)
    return 0;
  if (getSymbolStatus() == ESymbolStatus::DeletedSymbolAccidental)
    return getAccidentalDeletedDepth();
  if (getSymbolStatus() == ESymbolStatus::DeletedSymbolRequired)
    return getRequiredDeletedDepth();
  assert(getSymbolStatus() == ESymbolStatus::MistakeSymbol);
  return getMistakeDepth();
}
//---------------------------------------------------------------------------

unsigned int CSymbolIterator::getAccidentalDeletedDepth() const {
  return getAccidentalDeletedDepth(CurrentPosition_);
}
//---------------------------------------------------------------------------

unsigned int CSymbolIterator::getAccidentalDeletedDepth(
  const CTextDataTree::CConstBasicIterator& Position) const {
  auto Parent = getParentPosition(Position);
  assert(Parent.isDefined());
  if(Parent->getSymbolStatus() !=
      ESymbolStatus::DeletedSymbolAccidental)
    return  0;
  return getAccidentalDeletedDepth(Parent) + 1;
}
//---------------------------------------------------------------------------

unsigned int CSymbolIterator::getRequiredDeletedDepth() const {
  return getRequiredDeletedDepth(CurrentPosition_);
}
//---------------------------------------------------------------------------

unsigned int CSymbolIterator::getRequiredDeletedDepth(
  const CTextDataTree::CConstBasicIterator& Position) const {
  auto Parent = getParentPosition(Position);
  assert(Parent.isDefined());
  if(Parent->getSymbolStatus() != ESymbolStatus::DeletedSymbolRequired)
    return  0;
  return getRequiredDeletedDepth(Parent) + 1;
}
//---------------------------------------------------------------------------

unsigned int CSymbolIterator::getMistakeDepth() const {
  assert(getParentPosition(CurrentPosition_)->MistakeRoutes_.size() > 0);
  return getParentPosition(CurrentPosition_)->MistakeRoutes_.size() - 1;
}
//---------------------------------------------------------------------------

CTextDataTree::CConstBasicIterator
CSymbolIterator::getParentPosition(
  const CTextDataTree::CConstBasicIterator& Position) const {
  auto Parent = Position;
  Parent.setToParent();
  return Parent;
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
