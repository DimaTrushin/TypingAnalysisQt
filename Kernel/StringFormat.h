#ifndef STRINGFORMAT_H
#define STRINGFORMAT_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "StringFormatDefault.h"
#include <map> //pch
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Enum
//---------------------------------------------------------------------------

enum class ETextFormat : unsigned char {
  MainText, DeletedTextAccidental, DeletedTextRequired,
  SystemKey, MistakenSymbol, SessionDelimiter, SeanceDelimiter,
  BackspaceFormat, ShiftFormat, EssentialShiftFormat, AltFormat,
  CtrlFormat, CapslockFormat, EssentialCapslockFormat, EnterFormat
};
//---------------------------------------------------------------------------
// Declaration of Global Functions
//---------------------------------------------------------------------------

// TO DO
// Probably do not need this!
// commented until I find an application of the function
//CBasicString getETextFormatName(ETextFormat TextFormat);
//---------------------------------------------------------------------------
// Declaration of CStringFormat
//---------------------------------------------------------------------------

class CStringFormat {
  using CDefault = CDefaultStringFormats;
public:
  CStringFormat(CColor newTextColor = CDefault::MainTextColor,
                CColor newBackColor = CDefault::TextBackColor);

  void makeBackDarker(unsigned int Depth);
  void makeBackLighter(unsigned int Depth);
  void makeTextDarker(unsigned int Depth);
  void makeTextLighter(unsigned int Depth);

  CColor TextColor;
  CColor BackColor;
};
//---------------------------------------------------------------------------
// Declaration CFormatPool
//---------------------------------------------------------------------------

class CFormatPool : public std::map<ETextFormat, CStringFormat> {
  using CBase = std::map<ETextFormat, CStringFormat>;
public:
  CFormatPool();
  CStringFormat getStringFormat(ETextFormat Format) const;
private:
  void setToDefault();
};
//---------------------------------------------------------------------------
// Declaration of CFormatStructure
//---------------------------------------------------------------------------

struct CFormatStructure {
  CFormatStructure(ETextFormat newTextFormat, unsigned int newDepth);
  bool operator == (const CFormatStructure& other) const;

  ETextFormat TextFormat;
  unsigned int Depth;
};
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // STRINGFORMAT_H
