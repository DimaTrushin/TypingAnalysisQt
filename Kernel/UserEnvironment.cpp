//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UserEnvironment.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Definition of CUserEnvironment
//---------------------------------------------------------------------------

CUserEnvironment::CUserEnvironment() {
  CFingerLayout::generateDefaultLayout(&FingerLayout_);
}
//---------------------------------------------------------------------------

void CUserEnvironment::addRawBuffer(CRawBuffer* pRawBuffer) {
  UserData_.addRawBuffer(pRawBuffer);
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
