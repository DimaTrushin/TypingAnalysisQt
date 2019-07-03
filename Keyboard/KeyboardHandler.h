#ifndef KEYBOARDHANDLER_H
#define KEYBOARDHANDLER_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "KeyFilter.h"
#include "RawKeyGenerator.h"
#include "LowLevelKeyboard.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKeyboard {
//---------------------------------------------------------------------------
// Declaration of CKeyboardHandler
//---------------------------------------------------------------------------

class CKeyboardHandler {
public:
  CKeyboardHandler(HWND ReceiverHandle);

  void handleInput(LPARAM lParam);
  void activate();
  void deactivate();

  bool isActive() const;
  CRawEventContainer* getRawBuffer();

  CKeyboardHandler(const CKeyboardHandler&) = delete;
  CKeyboardHandler(CKeyboardHandler&&) = delete;
  CKeyboardHandler& operator=(const CKeyboardHandler&) = delete;
  CKeyboardHandler& operator=(CKeyboardHandler&&) = delete;

private:
  inline microseconds getMessageTime() const;
  inline RAWKEYBOARD getRawKeyboardData(LPARAM lParam) const;
  inline HKL getKeyboardLayout() const;
  inline void HandleDataInput(microseconds MessageTime,
                              const RAWKEYBOARD& KeyboardData,
                              HKL KeyboardLayout);
  //inline void HandleCommandInput(const RAWKEYBOARD& KeyboardData);
  inline bool isProcessable(const RAWKEYBOARD& KeyboardData) const;
  //inline bool needToTransferData(const RAWKEYBOARD& KeyboardData) const;
  //inline bool isEscapePressed(const RAWKEYBOARD& KeyboardData) const;
  inline void resetRawBuffer();

  bool ActiveState_;
  CRawEventContainer RawBuffer_;
  CLowLevelKeyboard LowLevelKeyboard_;
  CKeyFilter KeyFilter_;
};
//---------------------------------------------------------------------------
} // NSKeyboard
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // KEYBOARDHANDLER_H
