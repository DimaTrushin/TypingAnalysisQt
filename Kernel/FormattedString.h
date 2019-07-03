#ifndef FORMATTEDSTRING_H
#define FORMATTEDSTRING_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <list> //pch
#include "StringFormat.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Declaration of CTextWithFormat
//---------------------------------------------------------------------------

// TO DO
// Change the declaration to a custom class with good member names
class CTextWithFormat : public std::pair<CStringFormat, CBasicString> {
  using CBase = std::pair<CStringFormat, CBasicString>;
public:
  // TO DO
  // COMPILER BUG
  // If I use "using CBase::CBase;" I get internal compiler error c1001
  CTextWithFormat(const CStringFormat& StringFormat,
                  const CBasicString& BasicString);
  CTextWithFormat(CStringFormat&& StringFormat,
                  CBasicString&& BasicString);
};
//---------------------------------------------------------------------------
// Declaration of CFormattedString
//---------------------------------------------------------------------------

class CFormattedString : public std::list<CTextWithFormat> {
public:
  void AddText(const CStringFormat& TextFormat,
               const CBasicString& Text);
  void AddText(CStringFormat&& TextFormat,
               CBasicString&& Text);
  void AddFormattedString(const CFormattedString& FormattedString);
  void AddFormattedString(CFormattedString&& FormattedString);
  CBasicString getBasicString() const;
};
//---------------------------------------------------------------------------
} //NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // FORMATTEDSTRING_H
