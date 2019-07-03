#ifndef APPKERNEL_H
#define APPKERNEL_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "Kernel/Kernel.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Forward Declarations
//---------------------------------------------------------------------------

enum class ETextMode : unsigned char;
enum class EOutputMode : unsigned char;
enum class ECapitalMode : unsigned char;
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Declaration of CAppKernel
//---------------------------------------------------------------------------

class CAppKernel {
  using EOutputMode = NSKernel::EOutputMode;
  using ETextMode = NSKernel::ETextMode;
  using ECapitalMode = NSKernel::ECapitalMode;
public:
  void setTextMode(EOutputMode OutputMode, ETextMode TextMode);
  void setShiftMode(ECapitalMode ShiftMode);
  void setCapslockMode(ECapitalMode CapslockMode);
private:
  NSKernel::CKernel Kernel_;
};
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // APPKERNEL_H
