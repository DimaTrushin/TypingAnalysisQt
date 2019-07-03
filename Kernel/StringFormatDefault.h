#ifndef STRINGFORMATDEFAULT_H
#define STRINGFORMATDEFAULT_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "Color.h"
#include <string> //pch
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Using
//---------------------------------------------------------------------------

using CBasicString = std::wstring;
//---------------------------------------------------------------------------
// Declaration of CDefaultStringFormats
//---------------------------------------------------------------------------

struct CDefaultStringFormats {
  static const CColor MainTextColor;
  static const CColor TextBackColor;
  static const CColor DeletedTextAccidentalBackColor;
  static const CColor DeletedTextAccidentalColor;
  static const CColor DeletedTextRequiredBackColor;
  static const CColor DeletedTextRequiredColor;
  static const CColor MistakenSymbolColor;
  static const CColor MistakenBackColor;
  static const CColor SessionDelimiterColor;
  static const CColor SeanceDelimiterColor;
  static const CColor BackSpaceColor;
  static const CColor SystemKeyColor;
  static const CColor ShiftColor;
  static const CColor EssentialShiftColor;
  static const CColor AltColor;
  static const CColor CtrlColor;
  static const CColor CapslockColor;
  static const CColor EssentialCapslockColor;
  static const CColor EnterColor;
};
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // STRINGFORMATDEFAULT_H
