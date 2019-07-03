//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "Color.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Definition of CColor
//---------------------------------------------------------------------------


CColor::CColor(CChannel Red, CChannel Green, CChannel Blue, CChannel Alpha)
  : Red_(Red), Green_(Green), Blue_(Blue), Alpha_(Alpha) {
}
//---------------------------------------------------------------------------

CChannel CColor::Red() const {
  return Red_;
}
//---------------------------------------------------------------------------

CChannel CColor::Green() const {
  return Green_;
}
//---------------------------------------------------------------------------

CChannel CColor::Blue() const {
  return Blue_;
}
//---------------------------------------------------------------------------

CChannel CColor::Alpha() const {
  return Alpha_;
}
//---------------------------------------------------------------------------

CChannel& CColor::Red() {
  return Red_;
}
//---------------------------------------------------------------------------

CChannel& CColor::Green() {
  return Green_;
}
//---------------------------------------------------------------------------

CChannel& CColor::Blue() {
  return Blue_;
}
//---------------------------------------------------------------------------

CChannel& CColor::Alpha() {
  return Alpha_;
}
//---------------------------------------------------------------------------

void CColor::setRGB(
  CChannel Red, CChannel Green, CChannel Blue, CChannel Alpha) {
  Red_ = Red;
  Green_ = Green;
  Blue_ = Blue;
  Alpha_ = Alpha;
}
//---------------------------------------------------------------------------

bool CColor::operator<(const CColor& other) const {
  return
    (Red_ < other.Red_? true:
     (Red_ > other.Red_? false:
      (Green_ < other.Green_? true:
       (Green_ > other.Green_ ? false:
        (Blue_ < other.Blue_ ? true:
         (Blue_ > other.Blue_ ? false:
          Alpha_ < other.Alpha_))))));
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
