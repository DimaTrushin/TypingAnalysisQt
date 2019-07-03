#ifndef RAWKEYEVENT_H
#define RAWKEYEVENT_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <deque> //pch
#include "KeyboardState.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKeyboard {
//---------------------------------------------------------------------------
// Declaration of CRawKey
//---------------------------------------------------------------------------

class CRawKey
  : public CKeyVKCodeLangLayoutBase,
    public CKeyFlagsBase,
    public CKeyTimeBase {
public:
  CRawKey() = default;
  CRawKey(CVKCodeType VKCode,
          HKL Layout,
          CFlagsType Flags,
          microseconds Time);
};
//---------------------------------------------------------------------------
// Declaration of CRawEventContainer
//---------------------------------------------------------------------------

class CRawEventContainer : protected std::deque<CRawKey> {
public:
  using CBase = std::deque<CRawKey>;

  using CBase::push_back;
  using CBase::empty;
  using CBase::front;
  using CBase::back;
  using CBase::size;
  using CBase::begin;
  using CBase::end;


  void clearKeys();
  void popFirstKey();

  void setToSystemKeyboardState();
  void setKeyboardState(const CKeyboardState& newKeyboardState);
  const CKeyboardState& getInitialKeyboardState() const;
  CKeyboardState& getInitialKeyboardState();
  void setNewKeyboardState(const CRawKey& RawKey);
private:
  CKeyboardState InitialKeyboardState_;
};
//---------------------------------------------------------------------------
} // NSKeyboard
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // RAWKEYEVENT_H
