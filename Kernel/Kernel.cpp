//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "Kernel.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------

bool CKernel::setTextMode(EOutputMode OutputMode, ETextMode TextMode) {
  return KernelSettings_.setTextMode(OutputMode, TextMode);
}
//---------------------------------------------------------------------------

bool CKernel::setShiftMode(ECapitalMode ShiftMode) {
  return KernelSettings_.setShiftMode(ShiftMode);
}
//---------------------------------------------------------------------------

bool CKernel::setCapslockMode(ECapitalMode CapslockMode) {
  return KernelSettings_.setCapslockMode(CapslockMode);
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
