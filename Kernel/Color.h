#ifndef COLOR_H
#define COLOR_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Declaration of CChannel
//---------------------------------------------------------------------------

using CChannel = unsigned char;
//---------------------------------------------------------------------------
// Declaration of CColor
//---------------------------------------------------------------------------

class CColor {
public:
  CColor() = default;
  CColor(CChannel Red,
         CChannel Green,
         CChannel Blue,
         CChannel Alpha = kAlphaDefault);

  CChannel Red() const;
  CChannel Green() const;
  CChannel Blue() const;
  CChannel Alpha() const;

  CChannel& Red();
  CChannel& Green();
  CChannel& Blue();
  CChannel& Alpha();

  void setRGB(CChannel Red,
              CChannel Green,
              CChannel Blue,
              CChannel Alpha = kAlphaDefault);

  bool operator<(const CColor& other) const;

  static constexpr CChannel kAlphaDefault = 255;
  static constexpr CChannel kRedDefault = 0;
  static constexpr CChannel kGreenDefault = 0;
  static constexpr CChannel kBlueDefault = 0;
private:
  CChannel Red_ = kRedDefault;
  CChannel Green_ = kGreenDefault;
  CChannel Blue_ = kBlueDefault;
  CChannel Alpha_ = kAlphaDefault;
};
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // COLOR_H
