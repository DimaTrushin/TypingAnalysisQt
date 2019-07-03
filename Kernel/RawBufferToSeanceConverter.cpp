//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "RawBufferToSeanceConverter.h"
#include <cassert> //pch
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Definition of CKeysBeingPressed
//---------------------------------------------------------------------------

bool CKeysBeingPressed::findIteratorOfEvent(
  CVKCodeType VKey, const_iterator* pIndex) const {
  CKeysBeingPressed::const_iterator& index = *pIndex;
  index = std::find_if( begin(),
                        end(),
  [VKey](const CKeyEvent* pKeyEvent) {
    return pKeyEvent->getVKCode() == VKey;
  });
  if (index == end())
    return false;
  return true;
}
//---------------------------------------------------------------------------
// Definition of CRawBufferToSeanceConverter
//---------------------------------------------------------------------------

CRawBufferToSeanceConverter::
CRawBufferToSeanceConverter(microseconds SessionTimeLimit)
  : SessionTimeLimit_(SessionTimeLimit) {
  // TO DO
  // assert if SessionTimeLimit_ is too small!
}
//---------------------------------------------------------------------------

void CRawBufferToSeanceConverter::convert(
  CRawBuffer* pBuffer, CSeance* pSeance) {
  if (pBuffer->empty())
    return;

  setInternalResources(pBuffer, pSeance);
  prepareFirstSession();

  for (const auto& RawEvent : *pBuffer_)
    handleRawEvent(RawEvent);
  releaseAllRemainingKeys();
  removeEmptyOutput();
  flushBuffer();
}
//---------------------------------------------------------------------------

void CRawBufferToSeanceConverter::setInternalResources(
  CRawBuffer* pBuffer, CSeance* pSeance) {
  assert(!pBuffer->empty());
  pBuffer_ = pBuffer;
  pSeance_ = pSeance;
  CurrentKeyboardState_ = pBuffer_->getInitialKeyboardState();
  releaseAllKeysInCurrentKeyboard();
  PressedKeys_.clear();
}
//---------------------------------------------------------------------------

void CRawBufferToSeanceConverter::prepareFirstSession() {
  assert(pSeance_ != nullptr);
  pSeance_->openNewSession(CurrentKeyboardState_);
}
//---------------------------------------------------------------------------

void CRawBufferToSeanceConverter::handleRawEvent(const CRawKey& RawEvent) {
  if (RawEvent.isPressed()) {
    if (needNewSession(RawEvent))
      prepareNewSession();
    handlePressing(RawEvent);
  } else
    handleReleasing(RawEvent);
}
//---------------------------------------------------------------------------

bool CRawBufferToSeanceConverter::needNewSession(
  const CRawKey& RawEvent) const {
  if (CurrentSession().empty())
    return false;
  if (RawEvent.getTime() - CurrentSession().getLastPressingTime() >
      SessionTimeLimit_)
    return true;
  return false;
}
//---------------------------------------------------------------------------

void CRawBufferToSeanceConverter::prepareNewSession() {
  releaseAllKeysInCurrentKeyboard();
  pSeance_->openNewSession(CurrentKeyboardState_);
}
//---------------------------------------------------------------------------

void CRawBufferToSeanceConverter::releaseAllKeysInCurrentKeyboard() {
  CurrentKeyboardState_.ReleaseAllKeys();
}
//---------------------------------------------------------------------------

void CRawBufferToSeanceConverter::handlePressing(const CRawKey& RawEvent) {
  CKeysBeingPressed::iterator index;
  if (PressedKeys_.findIteratorOfEvent(RawEvent.getVKCode(),
                                       &index))
    handleKeyHolding(RawEvent, index);
  else {
    handleKeyPressing(RawEvent);
    CurrentKeyboardState_.PressKey(RawEvent.getVKCode());
  }
}
//---------------------------------------------------------------------------

void CRawBufferToSeanceConverter::
handleKeyHolding(const CRawKey& RawEvent,
                 const CKeysBeingPressed::iterator& index) {
  if (RawEvent.isSymbolOrSpace() ||
      RawEvent.isEnter() ||
      RawEvent.isBackspace()) {
    handleKeyReleasing(RawEvent.getTime(), index);
    handleKeyPressing(RawEvent);
  }
}
//---------------------------------------------------------------------------

void CRawBufferToSeanceConverter::handleKeyPressing(
  const CRawKey& RawEvent) {
  CurrentSession().emplace_back(RawEvent);
  PressedKeys_.push_back(&(CurrentSession().back()));
}
//---------------------------------------------------------------------------

void CRawBufferToSeanceConverter::handleReleasing(const CRawKey& RawEvent) {
  CKeysBeingPressed::iterator index;
  if (PressedKeys_.findIteratorOfEvent(RawEvent.getVKCode(), &index)) {
    handleKeyReleasing(RawEvent.getTime(), index);
    CurrentKeyboardState_.ReleaseKey(RawEvent.getVKCode());
  }
}
//---------------------------------------------------------------------------

void CRawBufferToSeanceConverter::handleKeyReleasing(
  microseconds ReleasingTime,
  const CKeysBeingPressed::iterator& index) {
  (*index)->setReleasingTime(ReleasingTime);
  PressedKeys_.erase(index);
}
//---------------------------------------------------------------------------

void CRawBufferToSeanceConverter::releaseAllRemainingKeys() {
  assert(pBuffer_ != nullptr && !pBuffer_->empty());
  microseconds lastTime = pBuffer_->back().getTime();
  releaseAtGivenTime(lastTime, &PressedKeys_);
}
//---------------------------------------------------------------------------

void CRawBufferToSeanceConverter::releaseAtGivenTime(
  microseconds ReleasingTime,
  CKeysBeingPressed* pKeysBeingPressed) {
  for (auto& itKey : *pKeysBeingPressed)
    if (itKey->getPressingTime() < ReleasingTime)
      itKey->setReleasingTime(ReleasingTime);
    else
      itKey->setReleasingTimeByDelay(kStandardHoldingTime);
  pKeysBeingPressed->clear();
}
//---------------------------------------------------------------------------

const CSession& CRawBufferToSeanceConverter::CurrentSession() const {
  assert(pSeance_ != nullptr);
  return pSeance_->back();
}
//---------------------------------------------------------------------------

CSession& CRawBufferToSeanceConverter::CurrentSession() {
  assert(pSeance_ != nullptr);
  return pSeance_->back();
}
//---------------------------------------------------------------------------

void CRawBufferToSeanceConverter::removeEmptyOutput() {
  assert(!pSeance_->empty());
  if (CurrentSession().empty())
    pSeance_->deleteLastSession();
}
//---------------------------------------------------------------------------

void CRawBufferToSeanceConverter::flushBuffer() {
  pBuffer_->clearKeys();
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
