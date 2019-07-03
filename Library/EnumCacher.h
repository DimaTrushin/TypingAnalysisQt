#ifndef ENUMCACHER_H
#define ENUMCACHER_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <tuple> //pch
#include <array> //pch
#include <memory> //pch
#include <cassert> //pch
//---------------------------------------------------------------------------


namespace NSApplication {
namespace NSLibrary {
//---------------------------------------------------------------------------
// Declaration of CTypeAt
//---------------------------------------------------------------------------

template<std::size_t TPosition, class... TTypes>
struct CTypeAt {
  using CType = std::tuple_element_t<TPosition, std::tuple<TTypes...>>;
};
//---------------------------------------------------------------------------

template<std::size_t TPosition, class... TTypes>
using CTypeAt_t = typename CTypeAt<TPosition, TTypes...>::CType;
//---------------------------------------------------------------------------
// Declaration of CIntSeqence
//---------------------------------------------------------------------------

template<std::size_t...>
struct CSizeTSequence {};
//---------------------------------------------------------------------------
// Declaration of CGenerateIntSequence
//---------------------------------------------------------------------------

template<std::size_t TFirst, std::size_t... TSequence>
struct CGenerateIntSequence :
  CGenerateIntSequence<TFirst - 1, TFirst - 1, TSequence...> {};
//---------------------------------------------------------------------------

template<std::size_t... TSequence>
struct CGenerateIntSequence<0, TSequence...> {
  using CType = CSizeTSequence<TSequence...>;
};
//---------------------------------------------------------------------------
// Declaration of CGenerateIntSequenceByTypes
//---------------------------------------------------------------------------

template<class... TTypes>
using CGenerateIntSequenceByTypes =
  typename CGenerateIntSequence<sizeof...(TTypes)>::CType;
//---------------------------------------------------------------------------
// Declaration of CInputPack
//---------------------------------------------------------------------------

template<class TInput, std::size_t... TArgPositions>
struct CInputPack {
  using CInput = TInput;
  using CArgSequence = CSizeTSequence<TArgPositions...>;
};
//---------------------------------------------------------------------------
// Declaration of CInputEnumArgChooser
//---------------------------------------------------------------------------

template<class TInputPack>
class CInputEnumArgChooser {
public:
  using CInput = typename TInputPack::CInput;
  using CArgSequence = typename TInputPack::CArgSequence;

  template<class... TEnums>
  auto operator()(const CInput& Input, TEnums... args) {
    return
      callHelper(Input, std::make_tuple(args...), CArgSequence());
  }
  auto operator()(const CInput& Input) {
    return
      callHelper(Input, CArgSequence());
  }
private:
  template<class... TEnums, std::size_t... TPositions>
  auto callHelper(const CInput& Input,
                  std::tuple<TEnums...>&& ArgPack,
                  CSizeTSequence<TPositions...>) {
    return Input(std::get<TPositions>(ArgPack)...);
  }
  template<std::size_t... TPositions>
  auto callHelper(const CInput& Input,
                  CSizeTSequence<TPositions...>) {
    return Input();
  }
};
//---------------------------------------------------------------------------
// Declaration of CEnumLinearizator
//---------------------------------------------------------------------------

template<class TLiteralType, TLiteralType... TLiterals>
class CEnumLinearizator {
public:
  inline static std::size_t linearize(TLiteralType arg);
private:
  template<TLiteralType TLiteral, TLiteralType... TLiterals>
  inline static
  typename std::enable_if<sizeof...(TLiterals) != 0, std::size_t>::type
  linearize_impl(TLiteralType arg);

  template<TLiteralType TLiteral>
  inline static std::size_t linearize_impl(TLiteralType arg);

  inline static std::size_t assertIfReached();
};
//---------------------------------------------------------------------------
// Declaration of CProduct
//---------------------------------------------------------------------------

template<std::size_t... Targs>
struct CProduct;
//---------------------------------------------------------------------------

template<std::size_t Tfirst, std::size_t... Targs>
struct CProduct<Tfirst, Targs...> {
  static constexpr std::size_t value = Tfirst * CProduct<Targs...>::value;
};
//---------------------------------------------------------------------------

template<>
struct CProduct<> {
  static constexpr const std::size_t value = 1;
};
//---------------------------------------------------------------------------
// Declaration of CParameters
//---------------------------------------------------------------------------

template<class TLiteralType, TLiteralType... TLiterals>
class CParameters {
public:
  using CLiteralType = TLiteralType;
  using CLinearizator = CEnumLinearizator<TLiteralType, TLiterals...>;
  static constexpr const std::size_t kArgumentsNumber = sizeof...(TLiterals);
};
//---------------------------------------------------------------------------
// Declaration of CParameterLinearizator
//---------------------------------------------------------------------------

template<class... TParameters>
class CParameterLinearizator {
public:
  inline static std::size_t
  linearize(typename TParameters::CLiteralType... args);
private:
  template<class... TParameters>
  struct CLinearizeImpl;

  template<class TFirstParameter, class... TParameters>
  struct CLinearizeImpl<TFirstParameter, TParameters...> {
    inline static
    std::size_t compute(typename TFirstParameter::CLiteralType first,
                        typename TParameters::CLiteralType... args);
  };
  template<class TParameter>
  struct CLinearizeImpl<TParameter> {
    inline static std::size_t compute(typename TParameter::CLiteralType arg);
  };
  // TO DO
  // How to move this out?
  template<>
  struct CLinearizeImpl<> {
    static std::size_t compute() {
      return 0;
    }
  };
};
//---------------------------------------------------------------------------
// Declaration of CEnumCacheTable
//---------------------------------------------------------------------------

template<class TValue, class... TParameters>
class CEnumCacheTable {
  static constexpr std::size_t kCacheSize =
    CProduct<TParameters::kArgumentsNumber...>::value;
  using CLinearizator = CParameterLinearizator<TParameters...>;
  using CCacheHolder = std::unique_ptr<TValue>;
  using CCacheTableBase = std::array<CCacheHolder, kCacheSize>;
public:
  inline bool isCached(typename TParameters::CLiteralType... Keys) const;
  inline const TValue& operator()(typename TParameters::CLiteralType... Keys);
  inline void add(TValue&& Value, typename TParameters::CLiteralType... Keys);
  inline TValue* ptr(typename TParameters::CLiteralType... Keys);
  inline void clear();
private:
  CCacheTableBase CacheTableBase_;
};
//---------------------------------------------------------------------------
// Declaration of CParametersPack
//---------------------------------------------------------------------------

template<class... TParameters>
struct CParametersPack {};
//---------------------------------------------------------------------------
// Declaration of CEnumCahcerGetter
//---------------------------------------------------------------------------

template<class TValue, class TParametersPack>
class CEnumCacherGetter;
//---------------------------------------------------------------------------

template<class TValue, class... TParameters>
struct CEnumCacherGetter<TValue, CParametersPack<TParameters...>> {
  using CType = CEnumCacheTable<TValue, TParameters...>;
};
//---------------------------------------------------------------------------
// Declaration of CEnumCacherFromPack
//---------------------------------------------------------------------------

template<class TValue, class TParametersPack>
using CEnumCacherFromPack =
  typename CEnumCacherGetter<TValue, TParametersPack>::CType;
//---------------------------------------------------------------------------
// Declaration of CEnumCacher
//---------------------------------------------------------------------------
//
// In order to use this pattern we must provide:
// 1) TFiller -- a class containing computational method
//
// TFiller MUST contain a method named "fill"
//
// fill MUST be a public method
//
// fill MUST be of the following signature:
// void fill(EType1,..., ETypek, InputRetType1,..., InputRetTypem, RetValue*)
//
// EType1,..., ETypek are k parameters of enum class Type
//
// InputRetType1,..., InputRetTypem are m parameters determining
// the types of Inputs connected to CEnumCacher
//
// RetValue is the type of a cached value, this is also
// a return value of the cacher
//
// TFiller MUST contain using CValue = RetValue; in a public section
//
// CValue MUST be container-like type in the sence
// it is default-constructible and this operation is cheap
//
// 2) TParametersPack -- a class describing enum class parameters
// of CEnumCacher
//
// TParametersPack MUST be of the form
// CParametersPack<CParam1,..., CParamk>
//
// CParam1,..., CParamk are k enum class packages of accepted parameters
//
// CParami MUST be of the form
// CParameters<EType, EType::Value1,..., EType::Valuek>
//
// EType is an enum class
//
// EType::Value1,..., EType::Valuek is a list of k accepted values of
// the enum class EType
//
// 3) TInputPacks -- a variadic list of TInputPack parameters
// this arguments describe all inputs of the CEnumCacher
// and how to transfer TParametersPack to them
//
// Each TInputPack MUST be of the form
// CInputPack<COtherCacher, numb0,...,numbk>
//
// COtherCacher is a cacher connected to the input
//
// numb0,...,numbk is a list of std::size_t numbers describing
// the positions of arguments for COtherCacher in TParametersPack
template<
  class TFiller, class TParametersPack, class... TInputPacks>
class CEnumCacher : protected TFiller {
  using CBase = TFiller;
  using CValue = typename CBase::CValue;
  using CInputPack = std::tuple<typename TInputPacks::CInput*...>;
  using CEnumCacheTable = CEnumCacherFromPack<CValue, TParametersPack>;
public:
  template<class... TInputs>
  inline CEnumCacher(TInputs&&... Inputs);
  template<class... TEnums>
  inline const CValue& operator()(TEnums... args) const;
  inline void clear();
private:
  // TO DO
  // must understand why this method cannot handle
  // protected methods of the base
  template<class TMethod, class... TEnums>
  inline void callAnyMethod(TMethod&& Method, TEnums... args) const;
  template<class TMethod, std::size_t... TSequence, class... TEnums>
  inline void callAnyMethodHelper(TMethod&& Method,
                                  CSizeTSequence<TSequence...>,
                                  TEnums... args) const;
  CInputPack InputPack_;
  // TO DO
  // I do not like this mutable at all
  // Probably this must be non mutable
  // and all the methods changing it must be non const
  mutable CEnumCacheTable Cache_;
};
//---------------------------------------------------------------------------
// Declaration of CEnumCacherNoParam
//---------------------------------------------------------------------------

template<class TFiller, class... TInputs>
using CEnumCacherNoParam =
  CEnumCacher<TFiller, CParametersPack<>, CInputPack<TInputs>...>;
//---------------------------------------------------------------------------
// Declaration of CSimpleGetter
//---------------------------------------------------------------------------

template<class TValue>
class CSimpleGetter {
public:
  CSimpleGetter(const TValue* pValue);
  const TValue& operator() () const;
private:
  const TValue* pValue_;
};
//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {
//---------------------------------------------------------------------------
// Definition of CEnumLinearizator
//---------------------------------------------------------------------------

template<class TLiteralType, TLiteralType... TLiterals>
std::size_t
CEnumLinearizator<TLiteralType, TLiterals...>::linearize(TLiteralType arg) {
  return linearize_impl<TLiterals...>(arg);
}
//---------------------------------------------------------------------------

template<class TLiteralType, TLiteralType... TLiterals>
template<TLiteralType TLiteral, TLiteralType... TOtherLiterals>
typename std::enable_if<sizeof...(TOtherLiterals) != 0, std::size_t>::type
CEnumLinearizator<TLiteralType, TLiterals...>::linearize_impl(
  TLiteralType arg) {
  return (arg == TLiteral ? 0: 1 + linearize_impl<TOtherLiterals...>(arg));
}
//---------------------------------------------------------------------------

template<class TLiteralType, TLiteralType... TLiterals>
template<TLiteralType TLiteral>
std::size_t
CEnumLinearizator<TLiteralType, TLiterals...>::linearize_impl(
  TLiteralType arg) {
  return (arg == TLiteral ? 0: assertIfReached());
}
//---------------------------------------------------------------------------

template<class TLiteralType, TLiteralType... TLiterals>
std::size_t
CEnumLinearizator<TLiteralType, TLiterals...>::assertIfReached() {
  assert(false);
  return 0;
}
//---------------------------------------------------------------------------
// Definition of CParameterLinearizator
//---------------------------------------------------------------------------

template<class... TParameters>
std::size_t
CParameterLinearizator<TParameters...>::linearize(
  typename TParameters::CLiteralType... args) {
  return CLinearizeImpl<TParameters...>::compute(args...);
}
//---------------------------------------------------------------------------

template<class... TParameters>
template<class TFirstParameter, class... TOtherParameters>
std::size_t
CParameterLinearizator<TParameters...>::
CLinearizeImpl<TFirstParameter, TOtherParameters...>::
compute(typename TFirstParameter::CLiteralType first,
        typename TOtherParameters::CLiteralType... args) {
  return TFirstParameter::CLinearizator::linearize(first) *
         CProduct<TOtherParameters::kArgumentsNumber...>::value +
         CLinearizeImpl<TOtherParameters...>::compute(args...);
}
//---------------------------------------------------------------------------

template<class... TParameters>
template<class TParameter>
std::size_t
CParameterLinearizator<TParameters...>::
CLinearizeImpl<TParameter>::
compute(typename TParameter::CLiteralType arg) {
  return TParameter::CLinearizator::linearize(arg);
}
//---------------------------------------------------------------------------
// Definition of CEnumCacheTable
//---------------------------------------------------------------------------

template<class TValue, class... TParameters>
bool
CEnumCacheTable<TValue, TParameters...>::isCached(
  typename TParameters::CLiteralType... Keys) const {
  return CacheTableBase_[CLinearizator::linearize(Keys...)].operator bool();
}
//---------------------------------------------------------------------------

template<class TValue, class... TParameters>
const TValue&
CEnumCacheTable<TValue, TParameters...>::operator() (
  typename TParameters::CLiteralType... Keys) {
  return *CacheTableBase_[CLinearizator::linearize(Keys...)];
}
//---------------------------------------------------------------------------

template<class TValue, class... TParameters>
void
CEnumCacheTable<TValue, TParameters...>::add(
  TValue&& Value, typename TParameters::CLiteralType... Keys) {
  CacheTableBase_[CLinearizator::linearize(Keys...)] =
    std::make_unique<TValue>(Value);
}
//---------------------------------------------------------------------------

template<class TValue, class... TParameters>
TValue*
CEnumCacheTable<TValue, TParameters...>::ptr(
  typename TParameters::CLiteralType... Keys) {
  return CacheTableBase_[CLinearizator::linearize(Keys...)].get();
}
//---------------------------------------------------------------------------

template<class TValue, class... TParameters>
void
CEnumCacheTable<TValue, TParameters...>::clear() {
  std::generate(CacheTableBase_.begin(),
                CacheTableBase_.end(),
  []() {
    return nullptr;
  });
}
//---------------------------------------------------------------------------
// Definition of CEnumCacher
//---------------------------------------------------------------------------

template<
  class TFiller, class TParametersPack, class... TInputPacks>
template<class... TInputs>
CEnumCacher<TFiller, TParametersPack, TInputPacks...>::
CEnumCacher(TInputs&&... Inputs)
  : InputPack_((&Inputs)...) {
}
//---------------------------------------------------------------------------

template<
  class TFiller, class TParametersPack, class... TInputPacks>
template<class... TEnums>
const typename CEnumCacher<TFiller, TParametersPack, TInputPacks...>::CValue&
CEnumCacher<TFiller, TParametersPack, TInputPacks...>::operator()(
  TEnums... args) const {
  if(!Cache_.isCached(args...)) {
    Cache_.add(CValue(), args...);
    callAnyMethod(&CBase::fill, args...);
  }
  return Cache_(args...);
}
//---------------------------------------------------------------------------

template<
  class TFiller, class TParametersPack, class... TInputPacks>
template<class TMethod, class... TEnums>
void
CEnumCacher<TFiller, TParametersPack, TInputPacks...>::
callAnyMethod(
  TMethod&& Method, TEnums... args) const {
  callAnyMethodHelper(
    std::forward<TMethod>(Method),
    CGenerateIntSequenceByTypes<typename TInputPacks::CInput...>(),
    args...);
}
//---------------------------------------------------------------------------

template<
  class TFiller, class TParametersPack, class... TInputPacks>
template<class TMethod, std::size_t... TSequence, class... TEnums>
void
CEnumCacher<TFiller, TParametersPack, TInputPacks...>::
callAnyMethodHelper(
  TMethod&& Method, CSizeTSequence<TSequence...>, TEnums... args) const {
  (this->*Method)(
    args...,
    CInputEnumArgChooser<TInputPacks>()(
      *(std::get<TSequence>(InputPack_)), args...)...,
    Cache_.ptr(args...));
}
//---------------------------------------------------------------------------

template<
  class TFiller, class TParametersPack, class... TInputPacks>
void
CEnumCacher<TFiller, TParametersPack, TInputPacks...>::clear() {
  Cache_.clear();
}
//---------------------------------------------------------------------------
// Declaration of CSimpleGetter
//---------------------------------------------------------------------------

template<class TValue>
CSimpleGetter<TValue>::CSimpleGetter(const TValue* pValue)
  : pValue_(pValue) {
}
//---------------------------------------------------------------------------

template<class TValue>
const TValue& CSimpleGetter<TValue>::operator() () const {
  return *pValue_;
}
//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // ENUMCACHER_H
