#ifndef APPLICATIONLOCALS_H
#define APPLICATIONLOCALS_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "ApplicationInternal.h"
#include "AppKeyboardHandler.h"
#include "AppUserEnvironment.h"
#include "AppKernel.h"
//---------------------------------------------------------------------------

namespace NSApplication {
//---------------------------------------------------------------------------
// Declaration of CApplicationLocals
//---------------------------------------------------------------------------

class CApplicationLocals : public CApplicationInternal {
  Q_OBJECT
  using CBase = CApplicationInternal;
public:
  CApplicationLocals();
protected:
  void handleInput(LPARAM lParam);
private:
  void connectKeyboardHanderToUserEnvironment();
  void connectTextModeReaderToKernel();
private:
  CAppKeyboardHandler AppKeyboardHandler_;
  CAppUserEnvironment AppUserEnvironment_;
  CAppKernel AppKernel_;
};
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // APPLICATIONLOCALS_H
