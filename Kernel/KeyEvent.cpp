//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "KeyEvent.h"
#include "Keyboard/SystemSymbol.h"
#include <cassert> //pch
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Definition of CKeyEvent
//---------------------------------------------------------------------------

CKeyEvent::CKeyEvent(CVKCodeType VKCode,
                     HKL Layout,
                     microseconds PressingTime)
  : CKeyVKCodeLangLayoutBase(VKCode, Layout),
    CKeyPressingTimeBase(PressingTime),
    CKeyReleasingTimeBase(PressingTime + kStandardDuration) {
}
//---------------------------------------------------------------------------

CKeyEvent::CKeyEvent(CVKCodeType VKCode,
                     HKL Layout,
                     microseconds PressingTime,
                     microseconds ReleasingTime)
  : CKeyVKCodeLangLayoutBase(VKCode, Layout),
    CKeyPressingTimeBase(PressingTime),
    CKeyReleasingTimeBase(ReleasingTime) {
  assert(PressingTime < ReleasingTime);
}
//---------------------------------------------------------------------------

CKeyEvent::CKeyEvent(const NSKeyboard::CRawKey& RawKey)
  : CKeyEvent(RawKey.getVKCode(), RawKey.getLayout(), RawKey.getTime()) {
}
//---------------------------------------------------------------------------

void CKeyEvent::setReleasingTimeByDelay(microseconds HoldingTime) {
  setReleasingTime(CKeyPressingTimeBase::Time_ + HoldingTime);
}
//---------------------------------------------------------------------------

bool CKeyEvent::isReleasedBeforePressed(const CKeyEvent& KeyEvent) const {
  return isReleasedBefore(KeyEvent.getPressingTime());
}
//---------------------------------------------------------------------------

bool CKeyEvent::isReleasedBeforeReleased(const CKeyEvent& KeyEvent) const {
  return isReleasedBefore(KeyEvent.getReleasingTime());
}
//---------------------------------------------------------------------------

bool CKeyEvent::isPressedBeforePressed(const CKeyEvent& KeyEvent) const {
  return isPressedBefore(KeyEvent.getPressingTime());
}
//---------------------------------------------------------------------------

bool CKeyEvent::isPressedBeforeReleased(const CKeyEvent& KeyEvent) const {
  return isPressedBefore(KeyEvent.getReleasingTime());
}
//---------------------------------------------------------------------------

bool CKeyEvent::isReleasedAfterPressed(const CKeyEvent& KeyEvent) const {
  return isReleasedAfter(KeyEvent.getPressingTime());
}
//---------------------------------------------------------------------------

bool CKeyEvent::isReleasedAfterReleased(const CKeyEvent& KeyEvent) const {
  return isReleasedAfter(KeyEvent.getReleasingTime());
}
//---------------------------------------------------------------------------

bool CKeyEvent::isPressedAfterPressed(const CKeyEvent& KeyEvent) const {
  return isPressedAfter(KeyEvent.getPressingTime());
}
//---------------------------------------------------------------------------

bool CKeyEvent::isPressedAfterReleased(const CKeyEvent& KeyEvent) const {
  return isPressedAfter(KeyEvent.getReleasingTime());
}
//---------------------------------------------------------------------------

microseconds CKeyEvent::getDurationTime() const {
  return CKeyReleasingTimeBase::Time_ - CKeyPressingTimeBase::Time_;
}
//---------------------------------------------------------------------------

wchar_t CKeyEvent::getKeySymbol(
  const NSKeyboard::CKeyboardState& KeyboardState) const {
  wchar_t keyName;
  if(ToUnicodeEx(getVKCode(),
                 getScanCode(),
                 KeyboardState.getLowLevelKeyboardState(),
                 &keyName,
                 1,
                 0,
                 getLayout()) == 1)
    return keyName;
  return NSKeyboard::CSystemSymbol::Unknown;
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
