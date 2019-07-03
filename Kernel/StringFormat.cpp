//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "StringFormat.h"
#include "ColorManipulator.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Definition of Global Functions
//---------------------------------------------------------------------------

// TO DO
// Probably do not need this!
// commented until I find an application of the function
/*
CBasicString getETextFormatName(ETextFormat TextFormat) {
  if (TextFormat == ETextFormat::MainText)
    return L"MainText";
  if (TextFormat == ETextFormat::DeletedTextAccidental)
    return L"DeletedTextAccidental";
  if (TextFormat == ETextFormat::DeletedTextRequired)
    return L"DeletedTextRequired";
  if (TextFormat == ETextFormat::SystemKey)
    return L"SystemKey";
  if (TextFormat == ETextFormat::MistakenSymbol)
    return L"Mistake";
  if (TextFormat == ETextFormat::SessionDelimiter)
    return L"SessionDelimiter";
  if (TextFormat == ETextFormat::SeanceDelimiter)
    return L"SeanceDelimiter";
  if (TextFormat == ETextFormat::BackspaceFormat)
    return L"Backspace";
  if (TextFormat == ETextFormat::ShiftFormat)
    return L"Shift";
  if (TextFormat == ETextFormat::EssentialShiftFormat)
    return L"EssShift";
  if (TextFormat == ETextFormat::AltFormat)
    return L"Alt";
  if (TextFormat == ETextFormat::CtrlFormat)
    return L"Ctrl";
  if (TextFormat == ETextFormat::CapslockFormat)
    return L"Capslock";
  if (TextFormat == ETextFormat::EssentialCapslockFormat)
    return L"EssCapslock";
  if (TextFormat == ETextFormat::EnterFormat)
    return L"Enter";
  return L"Unknown";
}*/
//---------------------------------------------------------------------------
// Definition of CStringFormat
//---------------------------------------------------------------------------

CStringFormat::CStringFormat(CColor newTextColor, CColor newBackColor)
  : TextColor(newTextColor),
    BackColor(newBackColor) {
}
//---------------------------------------------------------------------------

void CStringFormat::makeBackDarker(unsigned int Depth) {
  BackColor = CColorManipulator::makeColorDarker(BackColor, Depth);
}
//---------------------------------------------------------------------------

void CStringFormat::makeBackLighter(unsigned int Depth) {
  BackColor = CColorManipulator::makeColorLighter(BackColor, Depth);
}
//---------------------------------------------------------------------------

void CStringFormat::makeTextDarker(unsigned int Depth) {
  TextColor = CColorManipulator::makeColorDarker(TextColor, Depth);
}
//---------------------------------------------------------------------------

void CStringFormat::makeTextLighter(unsigned int Depth) {
  TextColor = CColorManipulator::makeColorLighter(TextColor, Depth);
}
//---------------------------------------------------------------------------
// Definition CFormatPool
//---------------------------------------------------------------------------

CFormatPool::CFormatPool() {
  setToDefault();
}
//---------------------------------------------------------------------------

CStringFormat CFormatPool::getStringFormat(ETextFormat Format) const {
  if (find(Format) == end())
    return CStringFormat();
  return find(Format)->second;
}
//---------------------------------------------------------------------------

void CFormatPool::setToDefault() {
  (*this)[ETextFormat::MainText] = CStringFormat();
  (*this)[ETextFormat::DeletedTextAccidental] = CStringFormat(
        CDefaultStringFormats::DeletedTextAccidentalColor,
        CDefaultStringFormats::DeletedTextAccidentalBackColor);
  (*this)[ETextFormat::DeletedTextRequired] = CStringFormat(
        CDefaultStringFormats::DeletedTextRequiredColor,
        CDefaultStringFormats::DeletedTextRequiredBackColor);
  (*this)[ETextFormat::SystemKey] = CStringFormat(
                                      CDefaultStringFormats::SystemKeyColor);
  (*this)[ETextFormat::MistakenSymbol] = CStringFormat(
      CDefaultStringFormats::MistakenSymbolColor,
      CDefaultStringFormats::MistakenBackColor);
  (*this)[ETextFormat::SessionDelimiter] = CStringFormat(
        CDefaultStringFormats::SessionDelimiterColor);
  (*this)[ETextFormat::SeanceDelimiter] = CStringFormat(
      CDefaultStringFormats::SeanceDelimiterColor);
  (*this)[ETextFormat::BackspaceFormat] = CStringFormat(
      CDefaultStringFormats::BackSpaceColor);
  (*this)[ETextFormat::ShiftFormat] = CStringFormat(
                                        CDefaultStringFormats::ShiftColor);
  (*this)[ETextFormat::EssentialShiftFormat] = CStringFormat(
        CDefaultStringFormats::EssentialShiftColor);
  (*this)[ETextFormat::AltFormat] = CStringFormat(
                                      CDefaultStringFormats::AltColor);
  (*this)[ETextFormat::CtrlFormat] = CStringFormat(
                                       CDefaultStringFormats::CtrlColor);
  (*this)[ETextFormat::CapslockFormat] = CStringFormat(
      CDefaultStringFormats::CapslockColor);
  (*this)[ETextFormat::EssentialCapslockFormat] = CStringFormat(
        CDefaultStringFormats::EssentialCapslockColor);
  (*this)[ETextFormat::EnterFormat] = CStringFormat(
                                        CDefaultStringFormats::EnterColor);
}
//---------------------------------------------------------------------------
// Definition of CFormatStructure
//---------------------------------------------------------------------------

CFormatStructure::CFormatStructure(ETextFormat newTextFormat,
                                   unsigned int newDepth)
  : TextFormat(newTextFormat),
    Depth(newDepth) {
}
//---------------------------------------------------------------------------

bool CFormatStructure::operator==(const CFormatStructure& other) const {
  return  TextFormat == other.TextFormat &&
          Depth == other.Depth;
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
