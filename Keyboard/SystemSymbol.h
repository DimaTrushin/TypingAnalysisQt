#ifndef SYSTEMSYMBOL_H
#define SYSTEMSYMBOL_H
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKeyboard {
//---------------------------------------------------------------------------
// Declaration of CSystemSymbol
//---------------------------------------------------------------------------

class CSystemSymbol {
public:
  enum : wchar_t {
    Enter = L'\u2BA0',
    Ctrl = L'\u2353',
    LeftCtrl = L'\u2343',
    RightCtrl = L'\u2344',
    Alt = L'\u2338',
    LeftAlt = L'\u2347',
    RightAlt = L'\u2348',
    Shift = L'\u21E7',
    LeftShift = L'\u2B01',
    RightShift = L'\u2B00',
    Backspace = L'\u232B',
    Capslock = L'\u2B89',
    Unknown = L'\u0000'
  };
};
//---------------------------------------------------------------------------
} // NSKeyboard
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // SYSTEMSYMBOL_H
