#ifndef USERENVIRONMENT_H
#define USERENVIRONMENT_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UserData.h"
#include "Keyboard/FingerLayout.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Declaration of CUserEnvironment
//---------------------------------------------------------------------------

class CUserEnvironment {
  using CRawBuffer = NSKeyboard::CRawEventContainer;
  using CFingerLayout = NSKeyboard::CFingerLayout;
public:
  CUserEnvironment();
  void addRawBuffer(CRawBuffer* pRawBuffer);
private:
  CUserData UserData_;
  CFingerLayout FingerLayout_;
};
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // USERENVIRONMENT_H
