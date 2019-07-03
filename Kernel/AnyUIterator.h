#ifndef ANYUITERATOR_H
#define ANYUITERATOR_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "Library/AnyObject.h"
#include "../TimeDefinitions.h"
#include "Keyboard/VKCode.h"
#include "StringFormat.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Delcaration of CAnyIteratorInterface
//---------------------------------------------------------------------------

template<class TBase>
class CAnyIteratorInterface : public TBase {
  using CBase = TBase;
public:
  using CBase::CBase;
  //---------------------------------------------------------------------------
  // Declaration of CAnyIteratorInterface::CFirstPressedOnTop
  //---------------------------------------------------------------------------

  // Time comparison class,
  // required for priority_queue and CVectorHeapWithAccess
  class CFirstPressedOnTop {
  public:
    inline bool operator()( const CAnyIteratorInterface& first,
                            const CAnyIteratorInterface& second) const;
  };
  //---------------------------------------------------------------------------
  // Declaration of CAnyIteratorInterface::CFirstReleasedOnTop
  //---------------------------------------------------------------------------

  // Time comparison class,
  // required for priority_queue and CVectorHeapWithAccess
  class CFirstReleasedOnTop {
  public:
    inline bool operator()( const CAnyIteratorInterface& first,
                            const CAnyIteratorInterface& second) const;
  };
};
//---------------------------------------------------------------------------
// Delcaration of IUIteratorInterface
//---------------------------------------------------------------------------

template<class TBase>
class IUIteratorInterface : public TBase {
  using CVKCode = NSKeyboard::CVKCode;
  using CVKCodeType = CVKCode::CVKCodeType;
public:
  virtual ETextFormat getTextFormat() const = 0;
  virtual CFormatStructure getTextFormatStructure() const = 0;
  virtual wchar_t getSymbol() const = 0;
  virtual CVKCodeType getVKCode() const = 0;
  virtual bool isValid() const = 0;
  virtual microseconds getPressingTime() const = 0;
  virtual microseconds getReleasingTime() const = 0;
  virtual void setNext() = 0;
  virtual microseconds getPhysicalResponseTime() const = 0;
protected:
  ~IUIteratorInterface() = default;
};
//---------------------------------------------------------------------------
// Delcaration of CUIteratorImplementation
//---------------------------------------------------------------------------

template<class TBase, class TObject>
class CUIteratorImplementation : public TBase {
  using CBase = TBase;
  using CVKCode = NSKeyboard::CVKCode;
  using CVKCodeType = CVKCode::CVKCodeType;
public:
  using CBase::CBase;
  ETextFormat getTextFormat() const override;
  CFormatStructure getTextFormatStructure() const override;
  wchar_t getSymbol() const override;
  CVKCodeType getVKCode() const override;
  bool isValid() const override;
  microseconds getPressingTime() const override;
  microseconds getReleasingTime() const override;
  void setNext() override;
  microseconds getPhysicalResponseTime() const override;
};
//---------------------------------------------------------------------------
// Declaration of CAnyUIterator
//---------------------------------------------------------------------------

using CAnyUIterator =
  NSLibrary::CAnyObject<
  CAnyIteratorInterface,
  IUIteratorInterface,
  CUIteratorImplementation>;
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------


namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Definition of CAnyIteratorInterface::CFirstPressedOnTop
//---------------------------------------------------------------------------

template<class TBase>
bool
CAnyIteratorInterface<TBase>::
CFirstPressedOnTop::
operator()( const CAnyIteratorInterface& first,
            const CAnyIteratorInterface& second) const {
  if (!first.isDefined())
    return false;
  if (!second.isDefined())
    return true;
  // The inequality must be strict here, required by STL
  return first->getPressingTime() > second->getPressingTime();
}
//---------------------------------------------------------------------------
// Definition of CAnyIteratorInterface::CFirstReleasedOnTop
//---------------------------------------------------------------------------

template<class TBase>
bool
CAnyIteratorInterface<TBase>::
CFirstReleasedOnTop::
operator()( const CAnyIteratorInterface& first,
            const CAnyIteratorInterface& second) const {
  if (!first.isDefined())
    return false;
  if (!second.isDefined())
    return true;
  // The inequality must be strict here, required by STL
  return first->getReleasingTime() > second->getReleasingTime();
}
//---------------------------------------------------------------------------
// Definition of CUIteratorImplementation
//---------------------------------------------------------------------------

template<class TBase, class TObject>
ETextFormat
CUIteratorImplementation<TBase, TObject>::getTextFormat() const {
  return CBase::Object().getTextFormat();
}
//---------------------------------------------------------------------------

template<class TBase, class TObject>
CFormatStructure
CUIteratorImplementation<TBase, TObject>::getTextFormatStructure() const {
  return CBase::Object().getTextFormatStructure();
}
//---------------------------------------------------------------------------

template<class TBase, class TObject>
wchar_t
CUIteratorImplementation<TBase, TObject>::getSymbol() const {
  return CBase::Object().getSymbol();
}
//---------------------------------------------------------------------------

template<class TBase, class TObject>
typename CUIteratorImplementation<TBase, TObject>::CVKCodeType
CUIteratorImplementation<TBase, TObject>::getVKCode() const {
  return CBase::Object().getVKCode();
}
//---------------------------------------------------------------------------

template<class TBase, class TObject>
bool CUIteratorImplementation<TBase, TObject>::isValid() const {
  return CBase::Object().isValid();
}
//---------------------------------------------------------------------------

template<class TBase, class TObject>
microseconds
CUIteratorImplementation<TBase, TObject>::getPressingTime() const {
  return CBase::Object().getPressingTime();
}
//---------------------------------------------------------------------------

template<class TBase, class TObject>
microseconds
CUIteratorImplementation<TBase, TObject>::getReleasingTime() const {
  return CBase::Object().getReleasingTime();
}
//---------------------------------------------------------------------------

template<class TBase, class TObject>
void CUIteratorImplementation<TBase, TObject>::setNext() {
  CBase::Object().setNext();
}
//---------------------------------------------------------------------------

template<class TBase, class TObject>
microseconds
CUIteratorImplementation<TBase, TObject>::getPhysicalResponseTime() const {
  return CBase::Object().getPhysicalResponseTime();
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // ANYUITERATOR_H
