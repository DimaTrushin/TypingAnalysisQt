//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "SessionIterator.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Declaration of CSessionIterator
//---------------------------------------------------------------------------

CSessionIterator::CSessionIterator(const CSession& Session)
  : pSession_(&Session),
    CurrentPosition_(Session.begin()) {
  CurrentKeyboardState_.setKeyboardState(Session.getKeyboardState());
  PressedKeys_.push_heap(CurrentPosition_);
}
//---------------------------------------------------------------------------

ETextFormat CSessionIterator::getTextFormat() const {
  if (CurrentPosition_->isSymbolOrSpace())
    return ETextFormat::MainText;
  if (CurrentPosition_->isAnyShift())
    return ETextFormat::ShiftFormat;
  if (CurrentPosition_->isAnyCtrl())
    return ETextFormat::CtrlFormat;
  if (CurrentPosition_->isAnyAlt())
    return ETextFormat::AltFormat;
  if (CurrentPosition_->isCapslock())
    return ETextFormat::CapslockFormat;
  if (CurrentPosition_->isEnter())
    return ETextFormat::EnterFormat;
  if (CurrentPosition_->isBackspace())
    return ETextFormat::BackspaceFormat;
  // any unknown key has MainText format
  return ETextFormat::MainText;
}
//---------------------------------------------------------------------------

CFormatStructure CSessionIterator::getTextFormatStructure() const {
  return CFormatStructure(getTextFormat(), 0);
}
//---------------------------------------------------------------------------

wchar_t CSessionIterator::getSymbol() const {
  if (CurrentPosition_->isSymbolOrSpace())
    return CurrentPosition_->getKeySymbol(CurrentKeyboardState_);
  if (CurrentPosition_->isSystemKey())
    return CurrentPosition_->getSystemKeySymbol();
  // unknown symbol
  return L'?';
}
//---------------------------------------------------------------------------

CSessionIterator::CVKCodeType CSessionIterator::getVKCode() const {
  return CurrentPosition_->getVKCode();
}
//---------------------------------------------------------------------------

bool CSessionIterator::isValid() const {
  return CurrentPosition_ != pSession_->end();
}
//---------------------------------------------------------------------------

microseconds CSessionIterator::getPressingTime() const {
  return CurrentPosition_->getPressingTime();
}
//---------------------------------------------------------------------------

microseconds CSessionIterator::getReleasingTime() const {
  return CurrentPosition_->getReleasingTime();
}
//---------------------------------------------------------------------------

void CSessionIterator::setNext() {
  pressCurrentKeyOnKeyboardState(CurrentPosition_);
  ++CurrentPosition_;
  if (!isValid())
    return;
  releaseBefore(CurrentPosition_->getPressingTime());
  PressedKeys_.push_heap(CurrentPosition_);
}
//---------------------------------------------------------------------------

microseconds CSessionIterator::getPhysicalResponseTime() const {
  return pSession_->getResponseTime(CurrentPosition_);
}
//---------------------------------------------------------------------------

void CSessionIterator::releaseBefore(microseconds Time) {
  PressedKeys_.releaseBefore(Time, &CurrentKeyboardState_);
}
//---------------------------------------------------------------------------

void CSessionIterator::pressCurrentKeyOnKeyboardState(
  const CSession::const_iterator& KeyIterator) {
  CurrentKeyboardState_.PressKey(KeyIterator->getVKCode());
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
