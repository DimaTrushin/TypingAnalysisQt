//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "KeyboardHandler.h"
#include "TimerAccess.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKeyboard {

//---------------------------------------------------------------------------
// Definitions of CKeyboardHandler
//---------------------------------------------------------------------------

CKeyboardHandler::CKeyboardHandler(HWND ReceiverHandle)
  : LowLevelKeyboard_(ReceiverHandle) {
  // TO DO
  // Need to pass a KeyFilter as a parameter
  KeyFilter_.setToDefaultFilter();
  activate();
}
//---------------------------------------------------------------------------

void CKeyboardHandler::handleInput(LPARAM lParam) {
  microseconds MessageTime = getMessageTime();
  const RAWKEYBOARD& KeyboardData = getRawKeyboardData(lParam);
  HKL KeyboardLayout = getKeyboardLayout();
  if(isActive())
    HandleDataInput(MessageTime, KeyboardData, KeyboardLayout);
  // TO DO
  // must be done via signals
  //HandleCommandInput(KeyboardData);
}
//---------------------------------------------------------------------------

void CKeyboardHandler::activate() {
  resetRawBuffer();
  ActiveState_ = true;
}
//---------------------------------------------------------------------------

void CKeyboardHandler::deactivate() {
  ActiveState_ = false;
}
//---------------------------------------------------------------------------

bool CKeyboardHandler::isActive() const {
  return ActiveState_;
}
//---------------------------------------------------------------------------

CRawEventContainer* CKeyboardHandler::getRawBuffer() {
  return &RawBuffer_;
}
//---------------------------------------------------------------------------

// TO DO
// This is left commented to remember the structure of the signal
// in the previous vertion of the program
// Should not forget to add the Logger into the signal

//void CKeyboardHandler::transferDataToUser() {
//ThreadIDLogger.Log(L"CKeyboardHandler::transferDataToUser");
//#if !defined(__MASTER__DISABLE__)
//  CPerformanceLogger Performance;
//  Performance->Log( &NSKernel::Master,
//                    L"transferDataToUser")->
//  transferDataToUser(&RawBuffer);
//#endif
//}
//---------------------------------------------------------------------------

microseconds CKeyboardHandler::getMessageTime() const {
  return CTimerAccess()->getTime();
}
//---------------------------------------------------------------------------

RAWKEYBOARD CKeyboardHandler::getRawKeyboardData(LPARAM lParam) const {
  return LowLevelKeyboard_.getRawInputData(lParam);
}
//---------------------------------------------------------------------------

HKL CKeyboardHandler::getKeyboardLayout() const {
  return GetKeyboardLayout(
           GetWindowThreadProcessId(
             GetForegroundWindow(), nullptr));
}
//---------------------------------------------------------------------------

void CKeyboardHandler::HandleDataInput( microseconds MessageTime,
                                        const RAWKEYBOARD& KeyboardData,
                                        HKL KeyboardLayout) {
  if (isProcessable(KeyboardData))
    RawBuffer_.push_back(
      CRawKeyGenerator::make(MessageTime, KeyboardLayout, KeyboardData));
}
//---------------------------------------------------------------------------

// TO DO
// must be done via signals
// must think of how to pass the data to AppKeyboardHandler_
// and what kind of data this should be
//void CKeyboardHandler::HandleCommandInput(const RAWKEYBOARD& KeyboardData) {
//  if (needToTransferData(KeyboardData))
//    transferDataToUser();
//}
//---------------------------------------------------------------------------

bool CKeyboardHandler::isProcessable(const RAWKEYBOARD& KeyboardData) const {
  return KeyFilter_.isProcessable(
           static_cast<CVKCode::CVKCodeType>(KeyboardData.VKey));
}
//---------------------------------------------------------------------------

// TO DO
// must be done via signals
//bool CKeyboardHandler::needToTransferData(const RAWKEYBOARD& KeyboardData) const {
//  return isEscapePressed(KeyboardData);
//}
//---------------------------------------------------------------------------

// TO DO
// must be done via signals
//bool CKeyboardHandler::isEscapePressed(const RAWKEYBOARD& KeyboardData) const {
//  return  KeyboardData.VKey == CVKCode::Esc &&
//          KeyboardData.Flags == RI_KEY_MAKE;
//}
//---------------------------------------------------------------------------

void CKeyboardHandler::resetRawBuffer() {
  RawBuffer_.clearKeys();
  RawBuffer_.setToSystemKeyboardState();
}
//---------------------------------------------------------------------------
} // NSKeyboard
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
