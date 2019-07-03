//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "KernelSettings.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Definition of CKernelSettings
//---------------------------------------------------------------------------

bool CKernelSettings::setTextMode(EOutputMode OutputMode, ETextMode TextMode) {
  if(OutputMode_ == OutputMode) {
    if(OutputMode == EOutputMode::Text &&
        TextMode_.TextMode_ != TextMode) {
      TextMode_.TextMode_ = TextMode;
      return true;
    } else {
      return false;
    }
  } else {
    OutputMode_ = OutputMode;
    if(OutputMode == EOutputMode::Text)
      TextMode_.TextMode_ = TextMode;
    return true;
  }
}
//---------------------------------------------------------------------------

bool CKernelSettings::setShiftMode(ECapitalMode ShiftMode) {
  if(TextMode_.ShiftMode_ == ShiftMode)
    return false;
  TextMode_.ShiftMode_ = ShiftMode;
  return true;
}
//---------------------------------------------------------------------------

bool CKernelSettings::setCapslockMode(ECapitalMode CapslockMode) {
  if(TextMode_.CapslockMode_ == CapslockMode)
    return false;
  TextMode_.CapslockMode_ = CapslockMode;
  return true;
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
