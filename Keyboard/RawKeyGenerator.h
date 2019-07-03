#ifndef RAWKEYGENERATOR_H
#define RAWKEYGENERATOR_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "RawKeyEvent.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKeyboard {
//---------------------------------------------------------------------------
// Declaration of CRawKeyGenerator
//---------------------------------------------------------------------------

class CRawKeyGenerator {
public:
  using CFlagsType = CKeyFlagsBase::CFlagsType;
  using CVKCodeType = CVKCode::CVKCodeType;

  static CRawKey make(microseconds Time,
                      HKL Layout,
                      const RAWKEYBOARD& KeyboardData);
private:
  inline static CRawKey GenerateRawKeyShift(
    microseconds Time, HKL Layout, const RAWKEYBOARD& KeyboardData);
  inline static CRawKey GenerateRawKeyLShift(
    microseconds Time, HKL Layout, const RAWKEYBOARD& KeyboardData);
  inline static CRawKey GenerateRawKeyRShift(
    microseconds Time, HKL Layout, const RAWKEYBOARD& KeyboardData);
  inline static CRawKey GenerateRawKeyAlt(
    microseconds Time, HKL Layout, const RAWKEYBOARD& KeyboardData);
  inline static CRawKey GenerateRawKeyCtrl(
    microseconds Time, HKL Layout, const RAWKEYBOARD& KeyboardData);
  inline static CRawKey GenerateRawKeyRegular(
    microseconds Time,HKL Layout, const RAWKEYBOARD& KeyboardData);
  inline static bool isTwoSidedShift(const RAWKEYBOARD& KeyboardData);
  inline static bool isTwoSidedCtrl(const RAWKEYBOARD& KeyboardData);
  inline static bool isTwoSidedAlt(const RAWKEYBOARD& KeyboardData);
  inline static bool isLeftShift(const RAWKEYBOARD& KeyboardData);
  inline static bool isRightShift(const RAWKEYBOARD& KeyboardData);
  inline static bool isLeftCtrl(const RAWKEYBOARD& KeyboardData);
  inline static bool isLeftAlt(const RAWKEYBOARD& KeyboardData);
  inline static bool secondBitIsZero(CFlagsType Flags);
};
//---------------------------------------------------------------------------
} // NSKeyboard
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // RAWKEYGENERATOR_H
