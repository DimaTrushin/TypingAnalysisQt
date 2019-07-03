#ifndef APPLICATIONINTERFACE_H
#define APPLICATIONINTERFACE_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "ApplicationGlobals.h"
#include "Interface/AppStatusReader.h"
#include "Interface/TextModeReader.h"
// TO DO
// uncomment when MainTextBrowser Data maker will be ready
//#include "Interface/TextBrowserWriter.h"
//---------------------------------------------------------------------------

namespace NSApplication {
//---------------------------------------------------------------------------
// Declaration of CApplicationInterface
//---------------------------------------------------------------------------

class CApplicationInterface : public CApplicationGlobals {
  Q_OBJECT
  using CBase = CApplicationGlobals;
public:
  CApplicationInterface();
protected:
  NSInterface::CAppStatusReader AppStatusReader_;
  NSInterface::CTextModeReader TextModeReader_;
  // TO DO
  // uncomment when MainTextBrowser Data maker will be ready
  //NSInterface::CTextBrowserWriter MainTextBrowserWriter_;
};
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // APPLICATIONINTERFACE_H
