//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "Session.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Definition of CSession
//---------------------------------------------------------------------------

CSession::CSession(const CKeyboardState& KeyboardState)
  : InitialKeyboardState_(KeyboardState) {
}
//---------------------------------------------------------------------------

void CSession::setKeyboardState(const CKeyboardState& newKeyboardState) {
  InitialKeyboardState_ = newKeyboardState;
}
//---------------------------------------------------------------------------

const CSession::CKeyboardState& CSession::getKeyboardState() const {
  return InitialKeyboardState_;
}
//---------------------------------------------------------------------------

CSession::CKeyboardState& CSession::getKeyboardState() {
  return InitialKeyboardState_;
}
//---------------------------------------------------------------------------

microseconds CSession::getDurationTime() const {
  if (empty())
    return 0;
  return getLastPressingTime() - getFirstPressingTime();
}
//---------------------------------------------------------------------------

microseconds CSession::getFirstPressingTime() const {
  return front().getPressingTime();
}
//---------------------------------------------------------------------------

microseconds CSession::getLastPressingTime() const {
  return back().getPressingTime();
}
//---------------------------------------------------------------------------

microseconds CSession::getResponseTime(const const_iterator& index) const {
  if (index == begin())
    return 0;
  auto previous = index;
  --previous;
  return  index->getPressingTime() -
          previous->getPressingTime();
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
