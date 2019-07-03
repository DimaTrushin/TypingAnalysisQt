#ifndef ANYGLOBALACCESS_H
#define ANYGLOBALACCESS_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <memory> //pch
#include <utility> //pch
#include <cassert> //pch
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {
//---------------------------------------------------------------------------
// Description of usage
//---------------------------------------------------------------------------
//
// The pattern is used to make a global object with non-trivial constructor
// without explicitely defining the object globaly.
//
// In order to use the pattern we must provide:
// 1) TAccessible -- the class for the global object
//
// 2) TID -- identification class. If we want to have several global objects
// of a class Type, we must distinguish them by a dummy class TID. For example,
// CAnyGlobalAccessible<Type, A> and CAnyGlobalAccessible<Type, B> store
// different instances of objects of type Type in static storage.
// Since static objects defined by the class they belong to, classes A and B
// are required to distinguish the instances.
// Example of a dummy class declaration:
// class CGlobalAccessibleID {};
//
// 3) A class for storing the global object. It must be publicly inherited
// from CAnyGlobalAccessible.
// class CGlobalAccessible :
//   public CAnyGlobalAccessible<TAccessible, CGlobalAccessibleID> {};
//
// 4) A class for getting access to the global object must be publicly inherited
// from CAnyGlobalAccess. It has only a default constructor. It asserts if
// the global object has not yet been initialized.
// class CGlobalAccess :
//   public CAnyGlobalAccess<TAccessible, CGlobalAccessibleID> {};
//
// 5) A class for initialization of the global object. It must be publicly
// inherited from CAnyGlobalInitializer.
// The class must inherit all the constructors of the base class.
// class CGlobalInitializer :
//   public CAnyGlobalInitializer<TAccessible, CGlobalAccessibleID> {};
//
// 6) We must define the static object in CGlobalAccess explicitely
// in cpp file in order to link to the global object correctly.
// CGlobalAccessible::CAccessibleType CGlobalAccessible::gObject_ = nullptr;
//---------------------------------------------------------------------------
// Declaration of CAnyGlobalAccessible
//---------------------------------------------------------------------------

template<class TAccessible, class TID>
class CAnyGlobalAccessible {
public:
  inline TAccessible* operator->() const;
  inline TAccessible* ptr() const;
  inline const TAccessible* cptr() const;
  inline TAccessible& ref() const;
  inline const TAccessible& cref() const;
protected:
  ~CAnyGlobalAccessible() = default;
  using CAccessibleType = std::unique_ptr<TAccessible>;
  static CAccessibleType gObject_;
};
//---------------------------------------------------------------------------
// Declaration of CAnyGlobalAccess
//---------------------------------------------------------------------------

template<class TAccessible, class TID>
class CAnyGlobalAccess : public CAnyGlobalAccessible<TAccessible, TID> {
public:
  inline CAnyGlobalAccess();
};
//---------------------------------------------------------------------------
// Declaration of CAnyGlobalInitializer
//---------------------------------------------------------------------------

template<class TAccessible, class TID>
class CAnyGlobalInitializer : public CAnyGlobalAccessible<TAccessible, TID> {
public:
  template<class... TArg>
  inline CAnyGlobalInitializer(TArg&&... Arg);
};
//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {
//---------------------------------------------------------------------------
// Definition of CAnyGlobalAccessible
//---------------------------------------------------------------------------

template<class TAccessible, class TID>
TAccessible* CAnyGlobalAccessible<TAccessible, TID>::operator->() const {
  return ptr();
}
//---------------------------------------------------------------------------

template<class TAccessible, class TID>
TAccessible* CAnyGlobalAccessible<TAccessible, TID>::ptr() const {
  return gObject_.get();
}
//---------------------------------------------------------------------------

template<class TAccessible, class TID>
const TAccessible* CAnyGlobalAccessible<TAccessible, TID>::cptr() const {
  return ptr();
}
//---------------------------------------------------------------------------

template<class TAccessible, class TID>
TAccessible& CAnyGlobalAccessible<TAccessible, TID>::ref() const {
  return *gObject_;
}
//---------------------------------------------------------------------------

template<class TAccessible, class TID>
const TAccessible& CAnyGlobalAccessible<TAccessible, TID>::cref() const {
  return ref();
}
//---------------------------------------------------------------------------
// Definition of CAnyGlobalAccess
//---------------------------------------------------------------------------

template<class TAccessible, class TID>
CAnyGlobalAccess<TAccessible, TID>::CAnyGlobalAccess() {
  assert(gObject_);
}
//---------------------------------------------------------------------------
// Definition of CAnyGlobalInitializer
//---------------------------------------------------------------------------

template<class TAccessible, class TID>
template<class... TArg>
CAnyGlobalInitializer<TAccessible, TID>::
CAnyGlobalInitializer(TArg&&... Arg) {
  if(!gObject_)
    gObject_ = std::make_unique<TAccessible>(std::forward<TArg>(Arg)...);
}
//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // ANYGLOBALACCESS_H
