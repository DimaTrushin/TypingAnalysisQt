//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "AppKeyboardHandler.h"
//---------------------------------------------------------------------------

namespace NSApplication {
//---------------------------------------------------------------------------
// Definition of CAppKeyboardHandler
//---------------------------------------------------------------------------

CAppKeyboardHandler::CAppKeyboardHandler(
  HWND ReceiverHandle, CAppStatusReader* pAppStatusReader)
  : KeyboardHandler_(ReceiverHandle) {
  AppStatusConnection_ =
    pAppStatusReader->
    connectObjectMethod(this,
                        &CAppKeyboardHandler::reactToAppActivation);
}
//---------------------------------------------------------------------------

void CAppKeyboardHandler::handleInput(LPARAM lParam) {
  KeyboardHandler_.handleInput(lParam);
}
//---------------------------------------------------------------------------

void CAppKeyboardHandler::reactToAppActivation(bool Active) {
  if (Active) {
    KeyboardHandler_.deactivate();
    RawBufferReady_(KeyboardHandler_.getRawBuffer());
  } else {
    KeyboardHandler_.activate();
  }
}
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
