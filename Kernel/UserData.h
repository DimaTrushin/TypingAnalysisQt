#ifndef USERDATA_H
#define USERDATA_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "Seance.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Declaration of CUserData
//---------------------------------------------------------------------------

class CUserData : protected std::deque<CSeance> {
  using CRawBuffer = NSKeyboard::CRawEventContainer;
public:
  using CBase = std::deque<CSeance>;
  void addRawBuffer(CRawBuffer* pRawBuffer);
};
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------

#endif // USERDATA_H
