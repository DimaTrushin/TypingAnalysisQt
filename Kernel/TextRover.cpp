//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "TextRover.h"
#include "SessionIterator.h"
#include "CapitalWithDependenciesIterator.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Definition of CTextRover
//---------------------------------------------------------------------------

CTextRover::CTextRover(const CSession& Session,
                       const CTextDataTree& TextTree,
                       const CShiftsData& ShiftsData,
                       const CCapslocksData& CapslocksData,
                       const CTextMode& TextMode,
                       ESymbolIteratorStart StartFrom) {
  auto SymbolIterator = CSymbolIterator(
                          TextTree, TextMode.TextMode_, StartFrom);
  if (SymbolIterator.isValid())
    push(std::move(SymbolIterator));
  auto ShiftIterator = CCapitalWithDependenciesIterator(
                         ShiftsData,
                         Session,
                         TextMode.TextMode_,
                         TextMode.ShiftMode_,
                         ECapitalType::Shift);
  if (ShiftIterator.isValid())
    push(std::move(ShiftIterator));
  auto CapslockIterator = CCapitalWithDependenciesIterator(
                            CapslocksData,
                            Session,
                            TextMode.TextMode_,
                            TextMode.CapslockMode_,
                            ECapitalType::Capslock);
  if (CapslockIterator.isValid())
    push(std::move(CapslockIterator));
}
//---------------------------------------------------------------------------

CTextRover::CTextRover(const CSession& Session) {
  auto SessionIterator = CSessionIterator(Session);
  if (SessionIterator.isValid())
    push(std::move(SessionIterator));
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
