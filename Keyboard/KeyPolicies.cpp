//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "KeyPolicies.h"
#include "SystemSymbol.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKeyboard {

//---------------------------------------------------------------------------
// Definition of CKeyFlagsBase
//---------------------------------------------------------------------------

CKeyFlagsBase::CKeyFlagsBase(CFlagsType Flags)
  : Flags_(Flags) {
}
//---------------------------------------------------------------------------

CKeyFlagsBase::CFlagsType CKeyFlagsBase::getFlags() const {
  return Flags_;
}
//---------------------------------------------------------------------------

bool CKeyFlagsBase::isPressed() const {
  return (Flags_ & 1) == RI_KEY_MAKE;
}
//---------------------------------------------------------------------------

bool CKeyFlagsBase::isReleased() const {
  return (Flags_ & 1) == RI_KEY_BREAK;
}
//---------------------------------------------------------------------------
// Definition of CKeyVKCodeBase
//---------------------------------------------------------------------------

CKeyVKCodeBase::CKeyVKCodeBase(CVKCodeType VKCode)
  : VKCode_(VKCode) {
}
//---------------------------------------------------------------------------

bool CKeyVKCodeBase::isLShift() const {
  return VKCode_ == CVKCode::LeftShift;
}
//---------------------------------------------------------------------------

bool CKeyVKCodeBase::isRShift() const {
  return VKCode_ == CVKCode::RightShift;
}
//---------------------------------------------------------------------------

bool CKeyVKCodeBase::isShift() const {
  return VKCode_ == CVKCode::Shift;
}
//---------------------------------------------------------------------------

bool CKeyVKCodeBase::isAnyShift() const {
  return isLShift() || isRShift() || isShift();
}
//---------------------------------------------------------------------------

bool CKeyVKCodeBase::isLCtrl() const {
  return VKCode_ == CVKCode::LeftCtrl;
}
//---------------------------------------------------------------------------

bool CKeyVKCodeBase::isRCtrl() const {
  return VKCode_ == CVKCode::RightCtrl;
}
//---------------------------------------------------------------------------

bool CKeyVKCodeBase::isCtrl() const {
  return VKCode_ == CVKCode::Ctrl;
}
//---------------------------------------------------------------------------

bool CKeyVKCodeBase::isAnyCtrl() const {
  return isLCtrl() || isRCtrl() || isCtrl();
}
//---------------------------------------------------------------------------

bool CKeyVKCodeBase::isLAlt() const {
  return VKCode_ == CVKCode::LeftAlt;
}
//---------------------------------------------------------------------------

bool CKeyVKCodeBase::isRAlt() const {
  return VKCode_ == CVKCode::RightAlt;
}
//---------------------------------------------------------------------------

bool CKeyVKCodeBase::isAlt() const {
  return VKCode_ == CVKCode::Alt;
}
//---------------------------------------------------------------------------

bool CKeyVKCodeBase::isAnyAlt() const {
  return isLAlt() || isRAlt() || isAlt();
}
//---------------------------------------------------------------------------

bool CKeyVKCodeBase::isEnter() const {
  return VKCode_ == CVKCode::Enter;
}
//---------------------------------------------------------------------------

bool CKeyVKCodeBase::isBackspace() const {
  return VKCode_ == CVKCode::Backspace;
}
//---------------------------------------------------------------------------

bool CKeyVKCodeBase::isCapslock() const {
  return VKCode_ == CVKCode::Capslock;
}
//---------------------------------------------------------------------------

bool CKeyVKCodeBase::isSpacebar() const {
  return VKCode_ == CVKCode::Spacebar;
}
//---------------------------------------------------------------------------

bool CKeyVKCodeBase::isEscape() const {
  return VKCode_ == CVKCode::Esc;
}
//---------------------------------------------------------------------------

bool CKeyVKCodeBase::isSystemKey() const {
  return  isAnyShift() || isAnyCtrl() || isAnyAlt() ||
          isCapslock() || isEnter()   || isBackspace();
}
//---------------------------------------------------------------------------

bool CKeyVKCodeBase::isSymbolKey() const {
  if (isNumber())
    return true;
  if (isEnglishSymbol())
    return true;
  if (CVKCode::Eng_Semicolon <= VKCode_ &&
      VKCode_ <= CVKCode::Eng_Slash_Question)
    return true;
  if (CVKCode::Eng_Left_Brace <= VKCode_ &&
      VKCode_ <= CVKCode::Eng_Quote)
    return true;
  if (VKCode_ == CVKCode::Eng_Tilde)
    return true;
  return false;
}
//---------------------------------------------------------------------------

bool CKeyVKCodeBase::isSymbolOrSpace() const {
  return isSpacebar() || isSymbolKey();
}
//---------------------------------------------------------------------------

bool CKeyVKCodeBase::isNumber() const {
  return CVKCode::VK_0 <= VKCode_ && VKCode_ <= CVKCode::VK_9;
}
//---------------------------------------------------------------------------

bool CKeyVKCodeBase::isEnglishSymbol() const {
  return CVKCode::A <= VKCode_ && VKCode_ <= CVKCode::Z;
}
//---------------------------------------------------------------------------

wchar_t CKeyVKCodeBase::getSystemKeySymbol() const {
  if (isEnter())
    return CSystemSymbol::Enter;

  if (isLShift())
    return CSystemSymbol::LeftShift;
  if (isRShift())
    return CSystemSymbol::RightShift;
  if (isShift())
    return CSystemSymbol::Shift;

  if (isLCtrl())
    return CSystemSymbol::LeftCtrl;
  if (isRCtrl())
    return CSystemSymbol::RightCtrl;
  if (isCtrl())
    return CSystemSymbol::Ctrl;

  if (isLAlt())
    return CSystemSymbol::LeftAlt;
  if (isRAlt())
    return CSystemSymbol::RightAlt;
  if (isAlt())
    return CSystemSymbol::Alt;

  if (isBackspace())
    return CSystemSymbol::Backspace;
  if (isCapslock())
    return CSystemSymbol::Capslock;
  return CSystemSymbol::Unknown;
}
//---------------------------------------------------------------------------

CKeyVKCodeBase::CVKCodeType CKeyVKCodeBase::getVKCode() const {
  return VKCode_;
}
//---------------------------------------------------------------------------
// Definition of CKeyVKCodeLangLayoutBase
//---------------------------------------------------------------------------

CKeyVKCodeLangLayoutBase::
CKeyVKCodeLangLayoutBase(CVKCodeType VKCode,
                         HKL Layout)
  : CKeyVKCodeBase(VKCode),
#ifdef STORE_LAYOUT_AS_HKL
    Layout_(Layout) {
#else
    Layout_(HandleToLong(Layout)) {
#endif
}
//---------------------------------------------------------------------------

bool CKeyVKCodeLangLayoutBase::isDeadKey() const {
  unsigned int Flag = MapVirtualKeyEx(VKCode_,
                                      MAPVK_VK_TO_CHAR,
                                      getLayout());
  if (((Flag << 1) >> 1) ^ Flag)
    return true;
  return false;
}
//---------------------------------------------------------------------------

CKeyVKCodeLangLayoutBase::CScanCodeType
CKeyVKCodeLangLayoutBase::getScanCode() const {
  return
    static_cast<CScanCodeType>(
      MapVirtualKeyEx(VKCode_, MAPVK_VK_TO_VSC, getLayout()));
}
//---------------------------------------------------------------------------

HKL CKeyVKCodeLangLayoutBase::getLayout() const {
#ifdef STORE_LAYOUT_AS_HKL
  return Layout_;
#else
  return reinterpret_cast<HKL>(LongToHandle(Layout_));
#endif
}
//---------------------------------------------------------------------------
// Definition of CKeyTimeBase
//---------------------------------------------------------------------------

CKeyTimeBase::CKeyTimeBase(microseconds Time)
  : Time_(Time) {
}
//---------------------------------------------------------------------------

microseconds CKeyTimeBase::getTime() const {
  return Time_;
}
//---------------------------------------------------------------------------

microseconds& CKeyTimeBase::getTime() {
  return Time_;
}
//---------------------------------------------------------------------------
// Definition of CKeyPressingTimeBase
//---------------------------------------------------------------------------

CKeyPressingTimeBase::CKeyPressingTimeBase(microseconds PressingTime)
  : CKeyTimeBase(PressingTime) {
}
//---------------------------------------------------------------------------

microseconds CKeyPressingTimeBase::getPressingTime() const {
  return CKeyTimeBase::getTime();
}
//---------------------------------------------------------------------------

bool CKeyPressingTimeBase::isPressedBefore(microseconds Time) const {
  return CKeyTimeBase::getTime() < Time;
}
//---------------------------------------------------------------------------

bool CKeyPressingTimeBase::isPressedAfter(microseconds Time) const {
  return CKeyTimeBase::getTime() > Time;
}
//---------------------------------------------------------------------------
// Definition of CKeyReleasingTimeBase
//---------------------------------------------------------------------------

CKeyReleasingTimeBase::CKeyReleasingTimeBase(microseconds ReleasingTime)
  : CKeyTimeBase(ReleasingTime) {
}
//---------------------------------------------------------------------------

microseconds CKeyReleasingTimeBase::getReleasingTime() const {
  return CKeyTimeBase::getTime();
}
//---------------------------------------------------------------------------

void CKeyReleasingTimeBase::setReleasingTime(microseconds ReleasingTime) {
  CKeyTimeBase::getTime() = ReleasingTime;
}
//---------------------------------------------------------------------------

bool CKeyReleasingTimeBase::isReleasedBefore(microseconds Time) const {
  return CKeyTimeBase::getTime() < Time;
}
//---------------------------------------------------------------------------

bool CKeyReleasingTimeBase::isReleasedAfter(microseconds Time) const {
  return CKeyTimeBase::getTime() > Time;
}
//---------------------------------------------------------------------------
} // NSKeyboard
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
