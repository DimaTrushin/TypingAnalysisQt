//---------------------------------------------------------------------------
// include
//---------------------------------------------------------------------------

#include "RawKeyGenerator.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKeyboard {
//---------------------------------------------------------------------------
// Definition of CRawKeyGenerator
//---------------------------------------------------------------------------

// Windows API distinguishs left and right versions of
// Shift, Ctrl, Alt as follows:
// Shift is signed by MakeCode. Left is 0x2a, Right is 0x36
// Alt and Ctrl are signed by second bit of Flags:
// Left has 0 bit, Right has 1 bit.

// Since Application Kernel does not store MakeCode
// we change VKCode and Flags appropriately.
CRawKey CRawKeyGenerator::make(
  microseconds Time, HKL Layout, const RAWKEYBOARD& KeyboardData) {
  if (isTwoSidedShift(KeyboardData))
    return GenerateRawKeyShift(Time, Layout, KeyboardData);

  if (isTwoSidedCtrl(KeyboardData))
    return GenerateRawKeyCtrl(Time, Layout, KeyboardData);

  if (isTwoSidedAlt(KeyboardData))
    return GenerateRawKeyAlt(Time, Layout, KeyboardData);

  return GenerateRawKeyRegular(Time, Layout, KeyboardData);
}
//---------------------------------------------------------------------------

CRawKey CRawKeyGenerator::GenerateRawKeyShift(
  microseconds Time, HKL Layout, const RAWKEYBOARD& KeyboardData) {
  if (isLeftShift(KeyboardData))
    return GenerateRawKeyLShift(Time, Layout, KeyboardData);
  else
    return GenerateRawKeyRShift(Time, Layout, KeyboardData);
}
//---------------------------------------------------------------------------

CRawKey CRawKeyGenerator::GenerateRawKeyLShift(
  microseconds Time, HKL Layout, const RAWKEYBOARD& KeyboardData) {
  return CRawKey( CVKCode::LeftShift,
                  Layout,
                  static_cast<CFlagsType>(KeyboardData.Flags),
                  Time);
}
//---------------------------------------------------------------------------

CRawKey CRawKeyGenerator::GenerateRawKeyRShift(
  microseconds Time, HKL Layout, const RAWKEYBOARD& KeyboardData) {
  return CRawKey( CVKCode::RightShift,
                  Layout,
                  static_cast<CFlagsType>(KeyboardData.Flags),
                  Time);
}
//---------------------------------------------------------------------------

CRawKey CRawKeyGenerator::GenerateRawKeyAlt(
  microseconds Time, HKL Layout, const RAWKEYBOARD& KeyboardData) {
  CFlagsType newFlags;
  CVKCodeType newVKCode;
  if (isLeftAlt(KeyboardData)) {
    newFlags = static_cast<CFlagsType>(KeyboardData.Flags);
    newVKCode = CVKCode::LeftAlt;
  } else {
    newFlags = static_cast<CFlagsType>(KeyboardData.Flags & 1);
    newVKCode = CVKCode::RightAlt;
  }
  return CRawKey( newVKCode,
                  Layout,
                  newFlags,
                  Time);
}
//---------------------------------------------------------------------------

CRawKey CRawKeyGenerator::GenerateRawKeyCtrl(
  microseconds Time, HKL Layout, const RAWKEYBOARD& KeyboardData) {
  CFlagsType newFlags;
  CVKCodeType newVKCode;
  if (isLeftCtrl(KeyboardData)) {
    newFlags = static_cast<CFlagsType>(KeyboardData.Flags);
    newVKCode = CVKCode::LeftCtrl;
  } else {
    newFlags = static_cast<CFlagsType>(KeyboardData.Flags & 1);
    newVKCode = CVKCode::RightCtrl;
  }
  return CRawKey( newVKCode,
                  Layout,
                  newFlags,
                  Time);
}
//---------------------------------------------------------------------------

CRawKey CRawKeyGenerator::GenerateRawKeyRegular(
  microseconds Time, HKL Layout, const RAWKEYBOARD& KeyboardData) {
  return CRawKey( static_cast<CVKCodeType>(KeyboardData.VKey),
                  Layout,
                  static_cast<CFlagsType>(KeyboardData.Flags),
                  Time);
}
//---------------------------------------------------------------------------

bool CRawKeyGenerator::isTwoSidedShift(const RAWKEYBOARD& KeyboardData) {
  return KeyboardData.VKey == CVKCode::Shift;
}
//---------------------------------------------------------------------------

bool CRawKeyGenerator::isTwoSidedCtrl(const RAWKEYBOARD& KeyboardData) {
  return KeyboardData.VKey == CVKCode::Ctrl;
}
//---------------------------------------------------------------------------

bool CRawKeyGenerator::isTwoSidedAlt(const RAWKEYBOARD& KeyboardData) {
  return KeyboardData.VKey == CVKCode::Alt;
}
//---------------------------------------------------------------------------

bool CRawKeyGenerator::isLeftShift(const RAWKEYBOARD& KeyboardData) {
  return KeyboardData.MakeCode == 0x2a;
}
//---------------------------------------------------------------------------

bool CRawKeyGenerator::isRightShift(const RAWKEYBOARD& KeyboardData) {
  return KeyboardData.MakeCode == 0x36;
}
//---------------------------------------------------------------------------

bool CRawKeyGenerator::isLeftCtrl(const RAWKEYBOARD& KeyboardData) {
  return secondBitIsZero(static_cast<CFlagsType>(KeyboardData.Flags));
}
//---------------------------------------------------------------------------

bool CRawKeyGenerator::isLeftAlt(const RAWKEYBOARD& KeyboardData) {
  return secondBitIsZero(static_cast<CFlagsType>(KeyboardData.Flags));
}
//---------------------------------------------------------------------------

bool CRawKeyGenerator::secondBitIsZero(CFlagsType Flags) {
  return ((Flags >> 1) & 1) == 0;
}
//---------------------------------------------------------------------------
} // NSKeyboard
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
