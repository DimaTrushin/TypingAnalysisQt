//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "TextBrowserWriter.h"
#include "Kernel/FormattedString.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSInterface {
//---------------------------------------------------------------------------
// Definition of CTextBrowserWriterBase
//---------------------------------------------------------------------------

CTextBrowserWriterBase::CTextBrowserWriterBase(QTextBrowser* pTextBrowser)
  : pTextBrowser_(pTextBrowser) {
}
//---------------------------------------------------------------------------

bool CTextBrowserWriterBase::isReady() const {
  return pTextBrowser_->isVisible();
}
//---------------------------------------------------------------------------

void CTextBrowserWriterBase::output(const CData& FormattedString) {
  QTextDocument* pDocument = new QTextDocument(pTextBrowser_);
  QTextCursor Cursor = QTextCursor(pDocument);
  for(const auto& TextWithFormat : FormattedString)
    outputTextWithFormat(TextWithFormat, &Cursor);
  pTextBrowser_->setDocument(pDocument);
}
//---------------------------------------------------------------------------

void CTextBrowserWriterBase::outputTextWithFormat(
  const CTextWithFormat& TextWithFormat, QTextCursor* pCursor) {
  pCursor->insertText(QString::fromStdWString(TextWithFormat.second),
                      getFormat(TextWithFormat.first));
}
//---------------------------------------------------------------------------

QTextCharFormat CTextBrowserWriterBase::getFormat(
  const CStringFormat& StringFormat) {
  QTextCharFormat ChFormat;
  ChFormat.setBackground(
    QBrush(
      QColor(StringFormat.BackColor.Red(),
             StringFormat.BackColor.Green(),
             StringFormat.BackColor.Blue())));
  ChFormat.setForeground(
    QBrush(
      QColor(StringFormat.TextColor.Red(),
             StringFormat.TextColor.Green(),
             StringFormat.TextColor.Blue())));
  return ChFormat;
}
//---------------------------------------------------------------------------
} // NSInterface
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
