#ifndef KEYEVENT_H
#define KEYEVENT_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "Keyboard/RawKeyEvent.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Declaration of CKeyEvent
//---------------------------------------------------------------------------

class CKeyEvent :
  public NSKeyboard::CKeyVKCodeLangLayoutBase,
  public NSKeyboard::CKeyPressingTimeBase,
  public NSKeyboard::CKeyReleasingTimeBase {
public:
  CKeyEvent() = default;
  CKeyEvent(CVKCodeType VKCode,
            HKL newLayout,
            microseconds PressingTime);
  CKeyEvent(CVKCodeType VKCode,
            HKL newLayout,
            microseconds PressingTime,
            microseconds ReleasingTime);
  explicit CKeyEvent(const NSKeyboard::CRawKey& RawKey);

  void setReleasingTimeByDelay(microseconds HoldingTime);

  bool isReleasedBeforePressed(const CKeyEvent& KeyEvent) const;
  bool isReleasedBeforeReleased(const CKeyEvent& KeyEvent) const;
  bool isPressedBeforePressed(const CKeyEvent& KeyEvent) const;
  bool isPressedBeforeReleased(const CKeyEvent& KeyEvent) const;

  bool isReleasedAfterPressed(const CKeyEvent& KeyEvent) const;
  bool isReleasedAfterReleased(const CKeyEvent& KeyEvent) const;
  bool isPressedAfterPressed(const CKeyEvent& KeyEvent) const;
  bool isPressedAfterReleased(const CKeyEvent& KeyEvent) const;

  microseconds getDurationTime() const;

  wchar_t getKeySymbol(const NSKeyboard::CKeyboardState& KeyboardState) const;
protected:
private:
  constexpr static const microseconds kStandardDuration = 1;
};
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // KEYEVENT_H
