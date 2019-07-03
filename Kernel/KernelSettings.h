#ifndef KERNELSETTINGS_H
#define KERNELSETTINGS_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "TextMode.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Declaration of CKernelSettings
//---------------------------------------------------------------------------

class CKernelSettings {
public:
  CKernelSettings() = default;
  bool setTextMode(EOutputMode OutputMode, ETextMode TextMode);
  bool setShiftMode(ECapitalMode ShiftMode);
  bool setCapslockMode(ECapitalMode CapslockMode);
private:
  EOutputMode OutputMode_ = EOutputMode::Text;
  CTextMode TextMode_;
  // TO DO
  // FormatPool_ for string formatting
};
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // KERNELSETTINGS_H
