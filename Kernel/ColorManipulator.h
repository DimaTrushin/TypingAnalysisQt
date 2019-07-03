#ifndef COLORMANIPULATOR_H
#define COLORMANIPULATOR_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "Color.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Declaration of CColorManipulator
//---------------------------------------------------------------------------

class CColorManipulator {
public:
  static CColor makeColorDarker(CColor Color, unsigned int Depth);
  static CColor makeColorLighter(CColor Color, unsigned int Depth);
  static CColor mixColor(
    CColor MainColor, CColor AddedColor, double Weight);
  static CColor shiftColorToAnother(
    CColor MainColor, CColor AddedColor, unsigned int Depth);
  // These functions are bad. They slightly change the brightness
  // if OneColor is small and significantly change the brightness
  // if OneColor is large
  static CChannel makeOneColorDarker(CChannel OneColor, unsigned int Depth);
  static CChannel makeOneColorLighter(CChannel OneColor, unsigned int Depth);
  static CChannel mixOneColor(
    CChannel MainColor, CChannel AddedColor, double Weight);
  static CChannel shiftOneColorToAnother(
    CChannel MainColor, CChannel AddedColor, unsigned int Depth);
private:
  static constexpr unsigned int kMaxColorSteps = 10;
  static constexpr double kDarkeningCoefficient = 1.1;
  static constexpr double kLighteningCoefficient = 1.1;
  static constexpr double kShiftingCoefficient = 0.1;
};
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // COLORMANIPULATOR_H
