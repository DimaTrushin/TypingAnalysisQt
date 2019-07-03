//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "ApplicationInterface.h"
//---------------------------------------------------------------------------

namespace NSApplication {
//---------------------------------------------------------------------------
// Definition of CApplicationInterface
//---------------------------------------------------------------------------

CApplicationInterface::CApplicationInterface()
  : CBase(),
    AppStatusReader_(),
    TextModeReader_(getTextModeButtonGroup(),
                    getShiftModeButtonGroup(),
                    getCapslockModeButtonGroup()) {
  // TO DO
  // uncomment when MainTextBrowser Data maker will be ready
  //,
  //MainTextBrowserWriter_(getMainTextBrowser(),
  //                       getMainWindowPtr(),
  //                       &CMainWindow::onTextBrowserMainTextVisible) {
  // TO DO
  // Move this to the place where the Data maker is located
  // Probably need this in CApplicationLocals ctor
  //MainTextBrowserWriter_.connectDataSource(&gFStrGetter, &CFormattedStringGetter::get);
}
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
