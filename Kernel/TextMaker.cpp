//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "TextMaker.h"
#include "TextRover.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Definition of CTextMaker
//---------------------------------------------------------------------------

void CTextMaker::make(const CSession& Session,
                      const CTextDataTree& TextTree,
                      const CShiftsData& ShiftsData,
                      const CCapslocksData& CapslocksData,
                      EOutputMode OutputMode,
                      const CTextMode& TextMode,
                      const CFormatPool& FormatPool,
                      CFormattedString* pText) const {
  // I do not clear pText content assuming it is already empty
  if(OutputMode == EOutputMode::Raw)
    makeRaw(Session, FormatPool, pText);
  else
    makeText(Session,
             TextTree,
             ShiftsData,
             CapslocksData,
             TextMode,
             FormatPool,
             pText);
}
//---------------------------------------------------------------------------

void CTextMaker::makeRaw(const CSession& Session,
                         const CFormatPool& FormatPool,
                         CFormattedString* pText) const {
  CTextRover Rover(Session);
  if (!Rover.empty())
    makeWithRover(FormatPool, &Rover, pText);
}
//---------------------------------------------------------------------------

void CTextMaker::makeText(const CSession& Session,
                          const CTextDataTree& TextTree,
                          const CShiftsData& ShiftsData,
                          const CCapslocksData& CapslocksData,
                          const CTextMode& TextMode,
                          const CFormatPool& FormatPool,
                          CFormattedString* pText) const {
  CTextRover Rover(Session, TextTree, ShiftsData, CapslocksData, TextMode, ESymbolIteratorStart::FromTextBegin);
  if (!Rover.empty())
    makeWithRover(FormatPool, &Rover, pText);
}
//---------------------------------------------------------------------------

void CTextMaker::makeWithRover(const CFormatPool& FormatPool,
                               CTextRover* pRover,
                               CFormattedString* pText) const {
  CBasicString Buffer;
  Buffer += pRover->getSymbol();
  CFormatStructure CurrentFormat = pRover->getTextFormatStructure();
  pRover->setNext();
  while (!pRover->empty()) {
    if (CurrentFormat == pRover->getTextFormatStructure())
      Buffer += pRover->getSymbol();
    else {
      pText->AddText(getStringFormat(FormatPool, CurrentFormat), Buffer);
      CurrentFormat = pRover->getTextFormatStructure();
      Buffer = pRover->getSymbol();
    }
    pRover->setNext();
  }
  pText->AddText(getStringFormat(FormatPool, CurrentFormat), Buffer);
}
//---------------------------------------------------------------------------

CStringFormat CTextMaker::getStringFormat(
  const CFormatPool& FormatPool,
  const CFormatStructure& FormatStructure) const {
  if (FormatStructure.TextFormat == ETextFormat::DeletedTextAccidental ||
      FormatStructure.TextFormat == ETextFormat::DeletedTextRequired ||
      FormatStructure.TextFormat == ETextFormat::MistakenSymbol) {
    CStringFormat StringFormat =
      FormatPool.getStringFormat(FormatStructure.TextFormat);
    StringFormat.makeBackDarker(FormatStructure.Depth);
    return StringFormat;
  }
  if (FormatStructure.TextFormat == ETextFormat::EssentialShiftFormat ||
      FormatStructure.TextFormat == ETextFormat::EssentialCapslockFormat) {
    CStringFormat StringFormat =
      FormatPool.getStringFormat(FormatStructure.TextFormat);
    assert(FormatStructure.Depth > 0);
    StringFormat.makeBackDarker(FormatStructure.Depth - 1);
    return StringFormat;
  }
  return FormatPool.getStringFormat(FormatStructure.TextFormat);
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
