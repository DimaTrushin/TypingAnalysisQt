#ifndef APPLICATIONINTERNAL_H
#define APPLICATIONINTERNAL_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "ApplicationInterface.h"
//---------------------------------------------------------------------------

namespace NSApplication {
//---------------------------------------------------------------------------
// Declaration of CApplicationInternal
//---------------------------------------------------------------------------

class CApplicationInternal : public CApplicationInterface {
  Q_OBJECT
  using CBase = CApplicationInterface;
public:
  CApplicationInternal();
protected:
  HWND getHandle() const;
};
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // APPLICATIONINTERNAL_H
