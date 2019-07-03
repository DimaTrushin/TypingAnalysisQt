#ifndef TEXTBROWSERWRITER_H
#define TEXTBROWSERWRITER_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <QTextBrowser>
#include "UIWriter.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Forward Declarations
//---------------------------------------------------------------------------

class CFormattedString;
class CStringFormat;
class CTextWithFormat;
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------

namespace NSInterface {
//---------------------------------------------------------------------------
// Declaration of CTextBrowserWriterBase
//---------------------------------------------------------------------------

class CTextBrowserWriterBase {
  using CStringFormat = NSKernel::CStringFormat;
  using CTextWithFormat = NSKernel::CTextWithFormat;
public:
  using CData = NSKernel::CFormattedString;
  using CWidget = QTextBrowser;
  CTextBrowserWriterBase(QTextBrowser* pTextBrowser);
  bool isReady() const;
  void output(const CData& FormattedString);
private:
  void outputTextWithFormat(const CTextWithFormat& TextWithFormat,
                            QTextCursor* pCursor);
  QTextCharFormat getFormat(const CStringFormat& StringFormat);

  QTextBrowser* pTextBrowser_;
};
//---------------------------------------------------------------------------
// Declaration of CTextBrowserWriter
//---------------------------------------------------------------------------

using CTextBrowserWriter = CUIWriter<CTextBrowserWriterBase>;
//---------------------------------------------------------------------------
} // NSInterface
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // TEXTBROWSERWRITER_H
