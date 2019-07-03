#ifndef SESSION_H
#define SESSION_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "KeyEvent.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Declaration of CSession
//---------------------------------------------------------------------------

// Should make it vector but then I need to correct all
// algorithms using iterators and changing CSession
class CSession : protected std::deque<CKeyEvent> {
public:
  using CBase = std::deque<CKeyEvent>;
  using CKeyboardState = NSKeyboard::CKeyboardState;

  using CBase::iterator;
  using CBase::const_iterator;

  CSession() = default;
  CSession(const CKeyboardState& KeyboardState);

  using CBase::push_back;
  using CBase::emplace_back;
  using CBase::back;
  using CBase::front;
  using CBase::empty;
  using CBase::size;
  using CBase::begin;
  using CBase::end;
  using CBase::cbegin;
  using CBase::cend;
  using CBase::operator[];

  void setKeyboardState(const CKeyboardState& newKeyboardState);
  const CKeyboardState& getKeyboardState() const;
  CKeyboardState& getKeyboardState();
  microseconds getDurationTime() const;
  microseconds getFirstPressingTime() const;
  microseconds getLastPressingTime() const;
  microseconds getResponseTime(const const_iterator& index) const;

  //---------------------------------------------------------------------------
  // Declaration of CSession::CFirstReleasedOnTop
  //---------------------------------------------------------------------------
  class CFirstReleasedOnTop {
  public:
    template<class TIterator>
    bool operator()(TIterator first,
                    TIterator second) const;
  };
private:
  CKeyboardState InitialKeyboardState_;
};
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Definition of CSession::CFirstReleasedOnTop
//---------------------------------------------------------------------------

template<class TIterator>
bool CSession::CFirstReleasedOnTop::operator()(
  TIterator first,
  TIterator second) const {
  // TO DO
  // Add verification that TIterator is either iterator or const_iterator

  // The inequality must be strict here
  return first->getReleasingTime() > second->getReleasingTime();
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // SESSION_H
