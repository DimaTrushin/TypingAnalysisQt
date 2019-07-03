//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "Seance.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Definition of CSeance
//---------------------------------------------------------------------------

microseconds CSeance::getResponseTime(const const_iterator& index) const {
  if (index == begin())
    return 0;
  auto previous = index;
  --previous;
  return  index->getFirstPressingTime() -
          previous->getLastPressingTime();

}
//---------------------------------------------------------------------------

void CSeance::openNewSession(const CKeyboardState& KeyboardState) {
  push_back(CSession(KeyboardState));
}
//---------------------------------------------------------------------------

void CSeance::deleteLastSession() {
  pop_back();
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
