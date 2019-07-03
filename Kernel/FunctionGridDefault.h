#ifndef CFUNCTIONGRIDDEFAULT_H
#define CFUNCTIONGRIDDEFAULT_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

// need this for size_t definition
#include <wchar.h>
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Declaration of CSpeedGridDefault
//---------------------------------------------------------------------------

class CSpeedGridDefault {
  static constexpr size_t kCoefficient = 5;
public:
  static constexpr double kMinimumValue = 0.0;
  static constexpr double kStep = 1.0 * static_cast<double>(kCoefficient);
  static constexpr size_t kNumberOfSteps = 2500 / kCoefficient;
  static constexpr double kMaximumValue = kMinimumValue + kStep *
                                          static_cast<double>(kNumberOfSteps);
};
//---------------------------------------------------------------------------
// Declaration of CTimeGridDefault
//---------------------------------------------------------------------------

// TO DO
// Need to define all constants here
class CTimeGridDefault;
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // CFUNCTIONGRIDDEFAULT_H
