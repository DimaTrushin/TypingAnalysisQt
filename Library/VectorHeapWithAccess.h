#ifndef VECTORHEAPWITHACCESS_H
#define VECTORHEAPWITHACCESS_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <vector> //pch
#include <algorithm> //pch
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {
//---------------------------------------------------------------------------
// Declaration of CVectorHeapWithAccess
//---------------------------------------------------------------------------

template<class TType, class TWhatOnTop>
class CVectorHeapWithAccess : protected std::vector<TType> {
  using CBase = std::vector<TType>;
public:
  inline void make_heap();
  inline void push_heap(const TType& Element);
  inline void push_heap(TType&& Element);
  inline void pop_heap();
  inline const TType& top() const;
};
//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {

//---------------------------------------------------------------------------
// Definition of CVectorHeapWithAccess
//---------------------------------------------------------------------------

template<class TType, class TWhatOnTop>
void CVectorHeapWithAccess<TType, TWhatOnTop>::make_heap() {
  TWhatOnTop Comparator;
  std::make_heap(CBase::begin(), CBase::end(), Comparator);
}
//---------------------------------------------------------------------------

template<class TType, class TWhatOnTop>
void CVectorHeapWithAccess<TType, TWhatOnTop>::push_heap(const TType& Element) {
  CBase::push_back(Element);
  TWhatOnTop Comparator;
  std::push_heap(CBase::begin(), CBase::end(), Comparator);
}
//---------------------------------------------------------------------------

template<class TType, class TWhatOnTop>
void CVectorHeapWithAccess<TType, TWhatOnTop>::push_heap(TType&& Element) {
  CBase::push_back(Element);
  TWhatOnTop Comparator;
  std::push_heap(CBase::begin(), CBase::end(), Comparator);
}
//---------------------------------------------------------------------------

template<class TType, class TWhatOnTop>
void CVectorHeapWithAccess<TType, TWhatOnTop>::pop_heap() {
  TWhatOnTop Comparator;
  std::pop_heap(CBase::begin(), CBase::end(), Comparator);
  CBase::pop_back();
}
//---------------------------------------------------------------------------

template<class TType, class TWhatOnTop>
const TType& CVectorHeapWithAccess<TType, TWhatOnTop>::top() const {
  return CBase::front();
}
//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // VECTORHEAPWITHACCESS_H
