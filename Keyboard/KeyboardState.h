#ifndef KEYBOARDSTATE_H
#define KEYBOARDSTATE_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <array> //pch
#include "KeyPolicies.h"
//---------------------------------------------------------------------------
namespace NSApplication {
namespace NSKeyboard {
//---------------------------------------------------------------------------
// Using
//---------------------------------------------------------------------------

using CLowLevelKeyState = unsigned char;
//---------------------------------------------------------------------------

using CLowLevelKeyboardState =
  std::array<CLowLevelKeyState, CVKCode::kNumberOfVKCodes>;
//---------------------------------------------------------------------------
// Declaration of CKeyboardState
//---------------------------------------------------------------------------

class CKeyboardState {
public:
  using CVKCodeType = CVKCode::CVKCodeType;
  // this requires KeyPolicies.h to be included!
  using CFlagsType = CKeyFlagsBase::CFlagsType;

  CKeyboardState();
  void setToSystemKeyboardState();
  void setKeyboardState(const CKeyboardState& currentKeyboardState);
  void setKeyState(CVKCodeType VKCode, CFlagsType KeyFlags);

  // For the next two functions:
  // The application kernel uses left and right versions
  // of Ctrl, Alt, Shift. Windows API uses twosided versions
  // of those in almost all cases (e.g. ToUnicodeEx).
  // Thus, the functions additionally deal with twosided
  // versions of Ctrl, Alt, Shift, even if a onesided key
  // is passed.
  void PressKey(CVKCodeType VKCode);
  void ReleaseKey(CVKCodeType VKCode);
  void ReleaseAllKeys();

  const CLowLevelKeyState* getLowLevelKeyboardState() const;
  CLowLevelKeyState getKeyState(CVKCodeType VKCode) const;
  bool isPressed(CVKCodeType VKCode) const;
  bool isReleased(CVKCodeType VKCode) const;
  bool isToggled(CVKCodeType VKCode) const;

private:
  void pressTwoSidedKey( CVKCodeType VKCode,
                         CVKCodeType VKLeft,
                         CVKCodeType VKRight,
                         CVKCodeType VKTwoSided);
  void releaseTwoSidedKey( CVKCodeType VKCode,
                           CVKCodeType VKLeft,
                           CVKCodeType VKRight,
                           CVKCodeType VKTwoSided);
  CLowLevelKeyboardState LowLevelKeyboardState_;
};
//---------------------------------------------------------------------------
} // NSKeyboard
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // KEYBOARDSTATE_H
