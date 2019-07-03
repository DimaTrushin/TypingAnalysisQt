#ifndef KERNEL_H
#define KERNEL_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "KernelSettings.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Declaration of CKernel
//---------------------------------------------------------------------------

class CKernel {
public:
  bool setTextMode(EOutputMode OutputMode, ETextMode TextMode);
  bool setShiftMode(ECapitalMode ShiftMode);
  bool setCapslockMode(ECapitalMode CapslockMode);
private:
  CKernelSettings KernelSettings_;
  // TO DO
  // there also MUST be:
  //KernelState_
  //Cacher_ should be in the KernelState_?
};
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // KERNEL_H
