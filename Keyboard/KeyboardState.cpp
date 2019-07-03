//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "KeyboardState.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKeyboard {
//---------------------------------------------------------------------------
// Definition of CKeyboardState
//---------------------------------------------------------------------------

CKeyboardState::CKeyboardState() {
  // TO DO
  // There must be a constructor for that purpose
  LowLevelKeyboardState_.fill(0);
}
//---------------------------------------------------------------------------

void CKeyboardState::setToSystemKeyboardState() {
  GetKeyboardState(&(LowLevelKeyboardState_[0]));
}
//---------------------------------------------------------------------------

void CKeyboardState::setKeyboardState(
  const CKeyboardState& CurrentKeyboardState) {
  LowLevelKeyboardState_ =
    CurrentKeyboardState.LowLevelKeyboardState_;
}
//---------------------------------------------------------------------------

void CKeyboardState::setKeyState( CVKCodeType VKCode,
                                  CFlagsType KeyFlags) {
  LowLevelKeyboardState_[VKCode] = KeyFlags;
}
//---------------------------------------------------------------------------

void CKeyboardState::PressKey(CVKCodeType VKCode) {
  // First press the key itself
  LowLevelKeyboardState_[VKCode] = (LowLevelKeyboardState_[VKCode] | 128) ^ 1;
  // The application kernel uses left and right versions
  // of Ctrl, Alt, Shift. Windows API uses twosided versions
  // of those in almost all cases. Hence, we need to press
  // twosided key also.
  pressTwoSidedKey(VKCode, CVKCode::LeftCtrl, CVKCode::RightCtrl, CVKCode::Ctrl);
  pressTwoSidedKey(VKCode, CVKCode::LeftShift, CVKCode::RightShift, CVKCode::Shift);
  pressTwoSidedKey(VKCode, CVKCode::LeftAlt, CVKCode::RightAlt, CVKCode::Alt);
}
//---------------------------------------------------------------------------

void CKeyboardState::ReleaseKey(CVKCodeType VKCode) {
  // First press the key itself
  LowLevelKeyboardState_[VKCode] = LowLevelKeyboardState_[VKCode] & 127;
  // The application kernel uses left and right versions
  // of Ctrl, Alt, Shift. Windows API uses twosided versions
  // of those in almost all cases. Hence, we need to release
  // twosided key also.
  releaseTwoSidedKey(VKCode, CVKCode::LeftCtrl, CVKCode::RightCtrl, CVKCode::Ctrl);
  releaseTwoSidedKey(VKCode, CVKCode::LeftShift, CVKCode::RightShift, CVKCode::Shift);
  releaseTwoSidedKey(VKCode, CVKCode::LeftAlt, CVKCode::RightAlt, CVKCode::Alt);
}
//---------------------------------------------------------------------------

void CKeyboardState::ReleaseAllKeys() {
  CVKCodeType VKCode = CVKCode::FirstCode;
  for(; VKCode < CVKCode::LastCode; ++VKCode)
    LowLevelKeyboardState_[VKCode] = LowLevelKeyboardState_[VKCode] & 127;
  LowLevelKeyboardState_[VKCode] = LowLevelKeyboardState_[VKCode] & 127;
}
//---------------------------------------------------------------------------

const CLowLevelKeyState* CKeyboardState::getLowLevelKeyboardState() const {
  return &(LowLevelKeyboardState_[0]);
}
//---------------------------------------------------------------------------

CLowLevelKeyState CKeyboardState::getKeyState(CVKCodeType VKCode) const {
  return LowLevelKeyboardState_[VKCode];
}
//---------------------------------------------------------------------------

bool CKeyboardState::isPressed(CVKCodeType VKCode) const {
  if (getKeyState(VKCode) & 128)
    return true;
  return false;
}
//---------------------------------------------------------------------------

bool CKeyboardState::isReleased(CVKCodeType VKCode) const {
  return !isPressed(VKCode);
}
//---------------------------------------------------------------------------

bool CKeyboardState::isToggled(CVKCodeType VKCode) const {
  if (getKeyState(VKCode) & 1)
    return true;
  return false;
}
//---------------------------------------------------------------------------

void CKeyboardState::pressTwoSidedKey(CVKCodeType VKCode,
                                      CVKCodeType VKLeft,
                                      CVKCodeType VKRight,
                                      CVKCodeType VKTwoSided) {
  if (VKCode == VKLeft || VKCode == VKRight)
    LowLevelKeyboardState_[VKTwoSided] =
      (LowLevelKeyboardState_[VKTwoSided] | 128) ^ 1;
}
//---------------------------------------------------------------------------

void CKeyboardState::releaseTwoSidedKey(CVKCodeType VKCode,
                                        CVKCodeType VKLeft,
                                        CVKCodeType VKRight,
                                        CVKCodeType VKTwoSided) {
  if ((VKCode == VKLeft && isReleased(VKRight)) ||
      (VKCode == VKRight && isReleased(VKLeft)))
    LowLevelKeyboardState_[VKTwoSided] =
      LowLevelKeyboardState_[VKTwoSided] & 127;
}
//---------------------------------------------------------------------------
} // NSKeyboard
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
