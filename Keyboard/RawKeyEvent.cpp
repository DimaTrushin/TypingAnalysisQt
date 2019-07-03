//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "RawKeyEvent.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKeyboard {
//---------------------------------------------------------------------------
// Definition of CRawKey
//---------------------------------------------------------------------------

CRawKey::CRawKey( CVKCodeType VKCode,
                  HKL Layout,
                  CFlagsType Flags,
                  microseconds Time)
  : CKeyVKCodeLangLayoutBase(VKCode, Layout),
    CKeyFlagsBase(Flags),
    CKeyTimeBase(Time) {
}
//---------------------------------------------------------------------------
// Definitions of CRawEventContainer
//---------------------------------------------------------------------------

void CRawEventContainer::clearKeys() {
  while (!empty())
    popFirstKey();
}
//---------------------------------------------------------------------------

void CRawEventContainer::popFirstKey() {
  setNewKeyboardState(front());
  CBase::pop_front();
}
//---------------------------------------------------------------------------

void CRawEventContainer::setToSystemKeyboardState() {
  InitialKeyboardState_.setToSystemKeyboardState();
}
//---------------------------------------------------------------------------

void CRawEventContainer::setKeyboardState(
  const CKeyboardState& newKeyboardState) {
  InitialKeyboardState_.setKeyboardState(newKeyboardState);
}
//---------------------------------------------------------------------------

const CKeyboardState& CRawEventContainer::getInitialKeyboardState() const {
  return InitialKeyboardState_;
}
//---------------------------------------------------------------------------

CKeyboardState& CRawEventContainer::getInitialKeyboardState() {
  return InitialKeyboardState_;
}
//---------------------------------------------------------------------------

void CRawEventContainer::setNewKeyboardState(const CRawKey& RawKey) {
  if (RawKey.isPressed())
    InitialKeyboardState_.PressKey(RawKey.getVKCode());
  else
    InitialKeyboardState_.ReleaseKey(RawKey.getVKCode());
}
//---------------------------------------------------------------------------
} // NSKeyboard
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
