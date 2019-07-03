#ifndef TEXTMODE_H
#define TEXTMODE_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Enum
//---------------------------------------------------------------------------

// Full -- text mode including all symbols with deleted ones
// Printed -- text mode including printed symbols only
enum class ETextMode : unsigned char {
  Full, Printed
};
//---------------------------------------------------------------------------

// Raw -- output the content of session
// Text -- output with respect to CTextMode
enum class EOutputMode : unsigned char {
  Raw, Text
};
//---------------------------------------------------------------------------

enum class ECapitalMode : unsigned char {
  Non, Essential, All
};
//---------------------------------------------------------------------------

enum class ECapitalType : unsigned char {
  Shift, Capslock
};
//---------------------------------------------------------------------------
// Declaration CTextMode
//---------------------------------------------------------------------------

class CTextMode {
public:
  CTextMode(ETextMode TextMode = ETextMode::Full,
            ECapitalMode ShiftMode = ECapitalMode::All,
            ECapitalMode CapslockMode = ECapitalMode::All);

  ETextMode TextMode_;
  ECapitalMode ShiftMode_;
  ECapitalMode CapslockMode_;
};
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // TEXTMODE_H
