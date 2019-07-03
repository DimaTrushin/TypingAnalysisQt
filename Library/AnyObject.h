#ifndef ANYOBJECT_H
#define ANYOBJECT_H

//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <memory> //pch
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {
//---------------------------------------------------------------------------
// Declaration of IEmpty
//---------------------------------------------------------------------------

class IEmpty {
protected:
  virtual ~IEmpty() = default;
};
//---------------------------------------------------------------------------
// Declaration of CAnyObjectBase
//---------------------------------------------------------------------------

template< template<class>class TInterface,
          template<class, class>class TImplementation>
class CAnyObjectBase {
  class IObjectStored;
  using CStoredPtr = std::unique_ptr<IObjectStored>;
public:
  inline CAnyObjectBase() = default;
  template<class TObject>
  inline CAnyObjectBase(TObject Object);

  inline CAnyObjectBase(const CAnyObjectBase& Other);
  CAnyObjectBase(CAnyObjectBase&& Other) = default;
  inline CAnyObjectBase& operator=(const CAnyObjectBase& Other);
  CAnyObjectBase& operator=(CAnyObjectBase&& Other) = default;

  inline bool isDefined() const;
  inline TInterface<IEmpty>* operator->();
  inline const TInterface<IEmpty>* operator->() const;
protected:
  ~CAnyObjectBase() = default;
private:
  //---------------------------------------------------------------------------
  // Declaration of CAnyObjectBase::IObjectStored
  //---------------------------------------------------------------------------

  class IObjectStored : public TInterface<IEmpty> {
  public:
    ~IObjectStored() override = default;
  protected:
    friend class CAnyObjectBase;
    virtual CStoredPtr _make_copy() const = 0;
  };
  //---------------------------------------------------------------------------
  // Declaration of CAnyObjectBase::CObjectKeeper
  //---------------------------------------------------------------------------

  template<class TObject>
  class CObjectKeeper : public IObjectStored {
  public:
    CObjectKeeper(TObject Object);
    ~CObjectKeeper() override = default;
  protected:
    inline TObject& Object();
    inline const TObject& Object() const;
    using CObjectType = TObject;
  private:
    TObject Object_;
  };
  //---------------------------------------------------------------------------
  // Declaration of CAnyObjectBase::CObjectStored
  //---------------------------------------------------------------------------

  template<class TObject>
  class CObjectStored :
    public TImplementation<CObjectKeeper<TObject>, TObject> {
    using CBase = TImplementation<CObjectKeeper<TObject>, TObject>;
  public:
    using CBase::CBase;
    ~CObjectStored() override = default;
  protected:
    CStoredPtr _make_copy() const override;
  };
  //---------------------------------------------------------------------------
  CStoredPtr pIObject_;
};
//---------------------------------------------------------------------------
// Declaration of CAnyObject
//---------------------------------------------------------------------------

template< template<class>class TAnyImplementation,
          template<class>class TInterface,
          template<class, class>class TImplementation>
class CAnyObject :
  public TAnyImplementation<CAnyObjectBase<TInterface, TImplementation>> {
  using CBase =
    TAnyImplementation<CAnyObjectBase<TInterface, TImplementation>>;
public:
  using CBase::CBase;
};
//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {
//---------------------------------------------------------------------------
// Definition of CAnyObjectBase
//---------------------------------------------------------------------------

template< template<class>class TInterface,
          template<class, class>class TImplementation>
template<class TObject>
CAnyObjectBase<TInterface, TImplementation>::CAnyObjectBase(TObject Object)
  : pIObject_(std::make_unique<CObjectStored<TObject>>(std::move(Object))) {
}
//---------------------------------------------------------------------------

template< template<class>class TInterface,
          template<class, class>class TImplementation>
CAnyObjectBase<TInterface, TImplementation>::CAnyObjectBase(
  const CAnyObjectBase& Other)
  : pIObject_(Other.pIObject_ ? Other.pIObject_->_make_copy() : nullptr) {
}
//---------------------------------------------------------------------------

template< template<class>class TInterface,
          template<class, class>class TImplementation>
CAnyObjectBase<TInterface, TImplementation>&
CAnyObjectBase<TInterface, TImplementation>::operator=(
  const CAnyObjectBase& Other) {
  return *this = CAnyObjectBase(Other);
}
//---------------------------------------------------------------------------

template< template<class>class TInterface,
          template<class, class>class TImplementation>
bool CAnyObjectBase<TInterface, TImplementation>::isDefined() const {
  return pIObject_.operator bool();
}
//---------------------------------------------------------------------------

template< template<class>class TInterface,
          template<class, class>class TImplementation>
TInterface<IEmpty>*
CAnyObjectBase<TInterface, TImplementation>::operator->() {
  return pIObject_.get();
}
//---------------------------------------------------------------------------

template< template<class>class TInterface,
          template<class, class>class TImplementation>
const TInterface<IEmpty>*
CAnyObjectBase<TInterface, TImplementation>::operator->() const {
  return pIObject_.get();
}
//---------------------------------------------------------------------------
// Definition of CAnyObjectBase::CObjectKeeper
//---------------------------------------------------------------------------

template< template<class>class TInterface,
          template<class, class>class TImplementation>
template<class TObject>
CAnyObjectBase<TInterface, TImplementation>::
CObjectKeeper<TObject>::CObjectKeeper(TObject Object)
  : Object_(std::move(Object)) {
}
//---------------------------------------------------------------------------

template< template<class>class TInterface,
          template<class, class>class TImplementation>
template<class TObject>
TObject&
CAnyObjectBase<TInterface, TImplementation>::
CObjectKeeper<TObject>::Object() {
  return Object_;
}
//---------------------------------------------------------------------------

template< template<class>class TInterface,
          template<class, class>class TImplementation>
template<class TObject>
const TObject&
CAnyObjectBase<TInterface, TImplementation>::
CObjectKeeper<TObject>::Object() const {
  return Object_;
}
//---------------------------------------------------------------------------
// Definition of CAnyObjectBase::CObjectStored
//---------------------------------------------------------------------------

template< template<class>class TInterface,
          template<class, class>class TImplementation>
template<class TObject>
std::unique_ptr<
typename CAnyObjectBase<TInterface, TImplementation>::IObjectStored>
CAnyObjectBase<TInterface, TImplementation>::
CObjectStored<TObject>::_make_copy() const {
  return std::make_unique<CObjectStored>(*this);
}
//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // ANYOBJECT_H
