//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "ColorManipulator.h"
#include <algorithm> //pch
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Definition of CColorManipulator
//---------------------------------------------------------------------------

constexpr unsigned int CColorManipulator::kMaxColorSteps;
//---------------------------------------------------------------------------

constexpr double CColorManipulator::kDarkeningCoefficient;
//---------------------------------------------------------------------------

constexpr double CColorManipulator::kLighteningCoefficient;
//---------------------------------------------------------------------------

constexpr double CColorManipulator::kShiftingCoefficient;
//---------------------------------------------------------------------------

CColor CColorManipulator::makeColorDarker(CColor Color, unsigned int Depth) {
  CChannel RColor = makeOneColorDarker(Color.Red(), Depth);
  CChannel GColor = makeOneColorDarker(Color.Green(), Depth);
  CChannel BColor = makeOneColorDarker(Color.Blue(), Depth);
  return CColor(RColor, GColor, BColor);
}
//---------------------------------------------------------------------------

CColor CColorManipulator::makeColorLighter(CColor Color, unsigned int Depth) {
  CChannel RColor = makeOneColorLighter(Color.Red(), Depth);
  CChannel GColor = makeOneColorLighter(Color.Green(), Depth);
  CChannel BColor = makeOneColorLighter(Color.Blue(), Depth);
  return CColor(RColor, GColor, BColor);
}
//---------------------------------------------------------------------------

CColor CColorManipulator::mixColor(
  CColor MainColor, CColor AddedColor, double Weight) {
  CChannel RColor = mixOneColor(MainColor.Red(), AddedColor.Red(), Weight);
  CChannel GColor = mixOneColor(MainColor.Green(), AddedColor.Green(), Weight);
  CChannel BColor = mixOneColor(MainColor.Blue(), AddedColor.Blue(), Weight);
  return CColor(RColor, GColor, BColor);
}
//---------------------------------------------------------------------------

CColor CColorManipulator::shiftColorToAnother(
  CColor MainColor, CColor AddedColor, unsigned int Depth) {
  CChannel RColor = shiftOneColorToAnother(
                      MainColor.Red(), AddedColor.Red(), Depth);
  CChannel GColor = shiftOneColorToAnother(
                      MainColor.Green(), AddedColor.Green(), Depth);
  CChannel BColor = shiftOneColorToAnother(
                      MainColor.Blue(), AddedColor.Blue(), Depth);
  return CColor(RColor, GColor, BColor);
}
//---------------------------------------------------------------------------

CChannel CColorManipulator::makeOneColorLighter(
  CChannel OneColor, unsigned int Depth) {
  unsigned int Steps = std::min(Depth, kMaxColorSteps);
  if (OneColor == 0)
    OneColor = 1;
  OneColor = static_cast<CChannel>(std::min(static_cast<double>(OneColor) *
                                   std::pow(kLighteningCoefficient, Steps),
                                   255.0));
  return OneColor;
}
//---------------------------------------------------------------------------

CChannel CColorManipulator::makeOneColorDarker(
  CChannel OneColor, unsigned int Depth) {
  unsigned int Steps = std::min(Depth, kMaxColorSteps);
  OneColor = static_cast<CChannel>(static_cast<double>(OneColor) /
                                   std::pow(kDarkeningCoefficient, Steps));
  return OneColor;
}
//---------------------------------------------------------------------------

CChannel CColorManipulator::mixOneColor(
  CChannel MainColor, CChannel AddedColor, double Weight) {
  Weight = std::max(Weight, 0.0);
  Weight = std::min(Weight, 1.0);
  return
    static_cast<CChannel>((1 - Weight) * static_cast<double>(MainColor) +
                          Weight * static_cast<double>(AddedColor));
}
//---------------------------------------------------------------------------

CChannel CColorManipulator::shiftOneColorToAnother(
  CChannel MainColor, CChannel AddedColor, unsigned int Depth) {
  double Weight = std::pow(1.0 + kShiftingCoefficient,
                           static_cast<double>(Depth)) - 1.0;
  return mixOneColor(MainColor, AddedColor, Weight);
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
