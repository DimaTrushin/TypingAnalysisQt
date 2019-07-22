#ifndef KEYPOLICIES_H
#define KEYPOLICIES_H
//---------------------------------------------------------------------------
// Defines
//---------------------------------------------------------------------------

#define STORE_LAYOUT_AS_HKL
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <Windows.h> //pch
#include "VKCode.h"
#include "../TimeDefinitions.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKeyboard {

//---------------------------------------------------------------------------
// Declaration of CKeyFlagsBase
//---------------------------------------------------------------------------

class CKeyFlagsBase {
public:
  using CFlagsType = unsigned char;
  CKeyFlagsBase(CFlagsType Flags = kDefaultFlags);

  CFlagsType getFlags() const;
  bool isPressed() const;
  bool isReleased() const;

protected:
  ~CKeyFlagsBase() = default;
  CFlagsType Flags_;

  static constexpr CFlagsType kDefaultFlags = 0;
};
//---------------------------------------------------------------------------
// Declaration of CKeyVKCodeBase
//---------------------------------------------------------------------------

class CKeyVKCodeBase {
public:
  using CVKCodeType = CVKCode::CVKCodeType;
  CKeyVKCodeBase(CVKCodeType VKCode = kDefaultVKCode);

  bool isLShift() const;
  bool isRShift() const;
  bool isShift() const;
  bool isAnyShift() const;
  bool isLCtrl() const;
  bool isRCtrl() const;
  bool isCtrl() const;
  bool isAnyCtrl() const;
  bool isLAlt() const;
  bool isRAlt() const;
  bool isAlt() const;
  bool isAnyAlt() const;
  bool isEnter() const;
  bool isBackspace() const;
  bool isCapslock() const;
  bool isSpacebar() const;
  bool isEscape() const;
  bool isSystemKey() const;
  bool isSymbolKey() const;
  bool isSymbolOrSpace() const;
  bool isNumber() const;
  bool isEnglishSymbol() const;
  wchar_t getSystemKeySymbol() const;
  CVKCodeType getVKCode() const;
protected:
  ~CKeyVKCodeBase() = default;
  CVKCodeType VKCode_;

  static constexpr CVKCodeType kDefaultVKCode = 0;
};
//---------------------------------------------------------------------------
// Declaration of CKeyVKCodeLangLayoutBase
//---------------------------------------------------------------------------

class CKeyVKCodeLangLayoutBase : public CKeyVKCodeBase {
public:
  using CScanCodeType = CVKCodeType;
  CKeyVKCodeLangLayoutBase( CVKCodeType VKCode = kDefaultVKCode,
                            HKL Layout = kDefaultLayout);
  bool isDeadKey() const;
  CScanCodeType getScanCode() const;
  HKL getLayout() const;
protected:
  ~CKeyVKCodeLangLayoutBase() = default;
#ifdef STORE_LAYOUT_AS_HKL
  HKL Layout_;
#else
  long Layout_;
#endif
  static constexpr HKL kDefaultLayout = nullptr;
  using CKeyVKCodeBase::kDefaultVKCode;
};
//---------------------------------------------------------------------------
// Declaration of CKeyTimeBase
//---------------------------------------------------------------------------

class CKeyTimeBase {
public:
  CKeyTimeBase(microseconds Time = kDefaultTime);
  microseconds getTime() const;
  microseconds& getTime();
protected:
  ~CKeyTimeBase() = default;
  microseconds Time_;
  static constexpr microseconds kDefaultTime = 0;
};
//---------------------------------------------------------------------------
// Declaration of CKeyPressingTimeBase
//---------------------------------------------------------------------------

class CKeyPressingTimeBase : protected CKeyTimeBase {
public:
  CKeyPressingTimeBase(microseconds PressingTime = kDefaultTime);
  microseconds getPressingTime() const;
  bool isPressedBefore(microseconds Time) const;
  bool isPressedAfter(microseconds Time) const;
protected:
  ~CKeyPressingTimeBase() = default;
  using CKeyTimeBase::kDefaultTime;
};
//---------------------------------------------------------------------------
// Declaration of CKeyReleasingTimeBase
//---------------------------------------------------------------------------

class CKeyReleasingTimeBase : protected CKeyTimeBase {
public:
  CKeyReleasingTimeBase(microseconds ReleasingTime = kDefaultTime);
  microseconds getReleasingTime() const;
  void setReleasingTime(microseconds ReleasingTime);
  bool isReleasedBefore(microseconds Time) const;
  bool isReleasedAfter(microseconds Time) const;
protected:
  ~CKeyReleasingTimeBase() = default;
  using CKeyTimeBase::kDefaultTime;
};
//---------------------------------------------------------------------------
} // NSKeyboard
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // KEYPOLICIES_H
