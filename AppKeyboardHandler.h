#ifndef APPKEYBOARDHANDLER_H
#define APPKEYBOARDHANDLER_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "Keyboard/KeyboardHandler.h"
//#include "Library/Signals.h"
#include "Interface/AppStatusReader.h"
//---------------------------------------------------------------------------

namespace NSApplication {
//---------------------------------------------------------------------------
// Declaration of CAppKeyboardHandler
//---------------------------------------------------------------------------

class CAppKeyboardHandler {
  using CRawBuffer = NSKeyboard::CRawEventContainer;
  using CRawBufferSignalType = NSLibrary::CSignal<void(CRawBuffer*)>;
  using CConnection = NSLibrary::CConnection;
public:
  using CAppStatusReader = NSInterface::CAppStatusReader;

  CAppKeyboardHandler(HWND ReceiverHandle,
                      CAppStatusReader* pAppStatusReader);
  void handleInput(LPARAM lParam);
  template<class TObject, class TMethod>
  CConnection connectToRawBufferSignal(TObject* pObject, TMethod&& Method);

private:
  void reactToAppActivation(bool Active);
  NSKeyboard::CKeyboardHandler KeyboardHandler_;
  NSLibrary::CConnection AppStatusConnection_;
  CRawBufferSignalType RawBufferReady_;
};
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------

namespace NSApplication {
//---------------------------------------------------------------------------
// Definition of CAppKeyboardHandler
//---------------------------------------------------------------------------

template<class TObject, class TMethod>
CAppKeyboardHandler::CConnection
CAppKeyboardHandler::connectToRawBufferSignal(
  TObject* pObject, TMethod&& Method) {
  return
    RawBufferReady_.
    connectMethod(pObject, std::forward<TMethod>(Method));
}
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // APPKEYBOARDHANDLER_H
