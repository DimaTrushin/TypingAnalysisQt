#ifndef ANYLOCALACCESS_H
#define ANYLOCALACCESS_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <memory> //pch
#include <utility> //pch
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {
//---------------------------------------------------------------------------
// Description of usage
//---------------------------------------------------------------------------
//
// The pattern is used to make a local object being built on the heap
// instead of the stack. It is useful for heavy objects.
//
// In order to use the pattern we must provide:
// 1) A handler class must be publicly derived from CAnyLocalAccess
// class CLocalInt : public CAnyLocalAccess<int> {};
// The class must inherit all the constructors of CAnyLocalAcces.
//---------------------------------------------------------------------------
// Declaration of CAnyLocalAccess
//---------------------------------------------------------------------------

template<class TAccessible>
class CAnyLocalAccess {
public:
  template<class... TArg>
  inline CAnyLocalAccess(TArg&&... Arg);
  inline TAccessible* operator->() const;
  inline TAccessible* ptr() const;
  inline const TAccessible* cptr() const;
  inline TAccessible& ref() const;
  inline const TAccessible& cref() const;
protected:
  std::unique_ptr<TAccessible> pObject_;
};
//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {
//---------------------------------------------------------------------------
// Definition of CAnyLocalAccess
//---------------------------------------------------------------------------

template<class TAccessible>
template<class... TArg>
CAnyLocalAccess<TAccessible>::CAnyLocalAccess(TArg&&... Arg)
  : pObject_(std::make_unique<TAccessible>(std::forward<TArg>(Arg)...)) {
}
//---------------------------------------------------------------------------

template<class TAccessible>
TAccessible* CAnyLocalAccess<TAccessible>::operator->() const {
  return ptr();
}
//---------------------------------------------------------------------------

template<class TAccessible>
TAccessible* CAnyLocalAccess<TAccessible>::ptr() const {
  return pObject_.get();
}
//---------------------------------------------------------------------------

template<class TAccessible>
const TAccessible* CAnyLocalAccess<TAccessible>::cptr() const {
  return ptr();
}
//---------------------------------------------------------------------------

template<class TAccessible>
TAccessible& CAnyLocalAccess<TAccessible>::ref() const {
  return *pObject_;
}
//---------------------------------------------------------------------------

template<class TAccessible>
const TAccessible& CAnyLocalAccess<TAccessible>::cref() const {
  return ref();
}
//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} //NSApplication
//---------------------------------------------------------------------------
#endif // ANYLOCALACCESS_H
