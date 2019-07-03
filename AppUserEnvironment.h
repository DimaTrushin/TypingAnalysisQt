#ifndef APPUSERENVIRONMENT_H
#define APPUSERENVIRONMENT_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "Kernel/UserEnvironment.h"
//---------------------------------------------------------------------------

namespace NSApplication {
//---------------------------------------------------------------------------
// Declaration of CAppUserEnvironment
//---------------------------------------------------------------------------

class CAppUserEnvironment {
  using CRawBuffer = NSKeyboard::CRawEventContainer;
public:
  void addRawBuffer(CRawBuffer* pRawBuffer);
private:
  NSKernel::CUserEnvironment UserEnvironment_;
};
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // APPUSERENVIRONMENT_H
