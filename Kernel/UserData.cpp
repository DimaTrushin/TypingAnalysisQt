//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UserData.h"
#include "RawBufferToSeanceConverter.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Definition of CUserData
//---------------------------------------------------------------------------

void CUserData::addRawBuffer(CRawBuffer* pRawBuffer) {
  if(empty())
    push_back(CSeance());
  // Always add to the last Seance
  CRawBufferToSeanceConverter Converter;
  Converter.convert(pRawBuffer, &back());
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
