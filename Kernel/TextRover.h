#ifndef TEXTROVER_H
#define TEXTROVER_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "RoverBase.h"
#include "CapitalWithDependencies.h"
#include "SymbolIterator.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Declaration of CTextRover
//---------------------------------------------------------------------------

class CTextRover : public CRoverBase {
public:
  CTextRover(const CSession& Session,
             const CTextDataTree& TextTree,
             const CShiftsData& ShiftsData,
             const CCapslocksData& CapslocksData,
             const CTextMode& TextMode,
             ESymbolIteratorStart StartFrom =
               ESymbolIteratorStart::FromRoot);
  CTextRover(const CSession& Session);
};
//---------------------------------------------------------------------------
} //NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // TEXTROVER_H
