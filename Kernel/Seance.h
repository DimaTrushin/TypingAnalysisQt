#ifndef SEANCE_H
#define SEANCE_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "Session.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Declaration of CSeance
//---------------------------------------------------------------------------

class CSeance : protected std::deque<CSession> {
public:
  using CBase = std::deque<CSession>;
  using CKeyboardState = NSKeyboard::CKeyboardState;
  using CBase::iterator;
  using CBase::const_iterator;

  using CBase::begin;
  using CBase::end;
  using CBase::cbegin;
  using CBase::cend;
  using CBase::back;
  using CBase::front;
  using CBase::size;
  using CBase::empty;
  using CBase::operator[];
  microseconds getResponseTime(const const_iterator& index) const;
  void openNewSession(const CKeyboardState& KeyboardState);
  void deleteLastSession();
};
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // SEANCE_H
