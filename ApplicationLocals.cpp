//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "ApplicationLocals.h"
//---------------------------------------------------------------------------

namespace NSApplication {
//---------------------------------------------------------------------------
// Definition of CApplicationLocals
//---------------------------------------------------------------------------

CApplicationLocals::CApplicationLocals()
  : CBase(),
    AppKeyboardHandler_(getHandle(), &AppStatusReader_),
    AppUserEnvironment_(),
    AppKernel_() {
  connectKeyboardHanderToUserEnvironment();
  connectTextModeReaderToKernel();
  // TO DO
  // need to read the initial TextMode
  // and pass it to the kernel without signaling
  // or vice versa
  // read TextMode from the kernel
  // and pass it to the UI
  // On the second case I have to do this
  // before connecting to the TextModeReader
  // Now I have to rely on the code coherency
}
//---------------------------------------------------------------------------

void CApplicationLocals::handleInput(LPARAM lParam) {
  AppKeyboardHandler_.handleInput(lParam);
}
//---------------------------------------------------------------------------

void CApplicationLocals::connectKeyboardHanderToUserEnvironment() {
  AppKeyboardHandler_.
  connectToRawBufferSignal(&AppUserEnvironment_,
                           &CAppUserEnvironment::addRawBuffer);
}
//---------------------------------------------------------------------------

void CApplicationLocals::connectTextModeReaderToKernel() {
  TextModeReader_.
  connectTextModeSelect(&AppKernel_, &CAppKernel::setTextMode);
  TextModeReader_.
  connectShiftModeSelect(&AppKernel_, &CAppKernel::setShiftMode);
  TextModeReader_.
  connectCapslockModeSelect(&AppKernel_, &CAppKernel::setCapslockMode);
}
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
