#ifndef TEXTMAKER_H
#define TEXTMAKER_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "FormattedString.h"
#include "CapitalWithDependencies.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Forward Declarations
//---------------------------------------------------------------------------

class CTextDataTree;
class CTextRover;
//---------------------------------------------------------------------------
// Declaration of CTextMaker
//---------------------------------------------------------------------------

class CTextMaker {
  using CKeyboardState = NSKeyboard::CKeyboardState;
public:
  // These functions assume that pText is already empty
  void make(const CSession& Session,
            const CTextDataTree& TextTree,
            const CShiftsData& ShiftsData,
            const CCapslocksData& CapslocksData,
            EOutputMode OutputMode,
            const CTextMode& TextMode,
            const CFormatPool& FormatPool,
            CFormattedString* pText) const;
  void makeRaw(const CSession& Session,
               const CFormatPool& FormatPool,
               CFormattedString* pText) const;
  void makeText(const CSession& Session,
                const CTextDataTree& TextTree,
                const CShiftsData& ShiftsData,
                const CCapslocksData& CapslocksData,
                const CTextMode& TextMode,
                const CFormatPool& FormatPool,
                CFormattedString* pText) const;
private:
  void makeWithRover(const CFormatPool& FormatPool,
                     CTextRover* pRover,
                     CFormattedString* pText) const;
  CStringFormat getStringFormat(
    const CFormatPool& FormatPool,
    const CFormatStructure& FormatStructure) const;
};
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // TEXTMAKER_H
