//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "FormattedString.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Declaration of CTextWithFormat
//---------------------------------------------------------------------------

CTextWithFormat::CTextWithFormat(const CStringFormat& StringFormat,
                                 const CBasicString& BasicString)
  : CBase(StringFormat, BasicString) {
}
//---------------------------------------------------------------------------

CTextWithFormat::CTextWithFormat(CStringFormat&& StringFormat,
                                 CBasicString&& BasicString)
  : CBase(std::move(StringFormat), std::move(BasicString)) {
}
//---------------------------------------------------------------------------
// Definition of CFormattedString
//---------------------------------------------------------------------------

void CFormattedString::AddText(const CStringFormat& TextFormat,
                               const CBasicString& Text) {
  push_back(CTextWithFormat(TextFormat, Text));
}
//---------------------------------------------------------------------------

void CFormattedString::AddText(CStringFormat&& TextFormat,
                               CBasicString&& Text) {
  emplace_back(std::move(TextFormat), std::move(Text));
}
//---------------------------------------------------------------------------

void CFormattedString::AddFormattedString(
  const CFormattedString& FormattedString) {
  insert(end(), FormattedString.begin(), FormattedString.end());
}
//---------------------------------------------------------------------------

void CFormattedString::AddFormattedString(
  CFormattedString&& FormattedString) {
  splice(end(), std::move(FormattedString));
}
//---------------------------------------------------------------------------

CBasicString CFormattedString::getBasicString() const {
  CBasicString Text = L"";
  for (const auto& Pair : *this)
    Text += Pair.second;
  return Text;
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
