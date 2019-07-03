#ifndef SIGNALS_H
#define SIGNALS_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <boost/signals2.hpp> //pch
#include "BindMethod.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {
//---------------------------------------------------------------------------
// Implementation: NSSignal
//---------------------------------------------------------------------------

namespace NSSignal {
//---------------------------------------------------------------------------

namespace bs2 = boost::signals2;
namespace bs2k = bs2::keywords;
//---------------------------------------------------------------------------
// Declaration of CBaseSignalNotThreadSafe
//---------------------------------------------------------------------------

template<class TFunction>
using CBaseSignalNotThreadSafe =
  typename
  bs2::signal_type<TFunction, bs2k::mutex_type<bs2::dummy_mutex>>::type;
//---------------------------------------------------------------------------
// Declaration of CBaseSignalThreadSafe
//---------------------------------------------------------------------------

template<class TFunction>
using CBaseSignalThreadSafe = bs2::signal<TFunction>;
//---------------------------------------------------------------------------
// Declaration of COnlyValue
//---------------------------------------------------------------------------

template<class TType>
struct COnlyValue {
  using result_type = TType;
  template<class TIterator>
  result_type operator()(TIterator first, TIterator last) {
    // This one MUST fire if "first == last" since I am asking for a value
    // which does not exist!
    assert(first != last);
    return *first;
  }
};
//---------------------------------------------------------------------------
// Declaration of CResultValue
//---------------------------------------------------------------------------

template<class TFunction>
using CResultValue = typename std::function<TFunction>::result_type;
//---------------------------------------------------------------------------

template<class TFunction>
using CBaseGetterSignalNonThreadSafe =
  typename
  bs2::signal_type<
  TFunction,
  bs2k::mutex_type<bs2::dummy_mutex>,
  bs2k::combiner_type<COnlyValue<CResultValue<TFunction>>>>::type;
//---------------------------------------------------------------------------
} // NSSignal
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
// Declaration of CBaseSignal
//---------------------------------------------------------------------------

template<class TFunction>
using CBaseSignal = NSSignal::CBaseSignalNotThreadSafe<TFunction>;
//---------------------------------------------------------------------------
// Declaration of CBaseGetterSignal
//---------------------------------------------------------------------------

template<class TFunction>
using CBaseGetterSignal = NSSignal::CBaseGetterSignalNonThreadSafe<TFunction>;
//---------------------------------------------------------------------------
// Declaration of CConnection
//---------------------------------------------------------------------------

using CConnection = NSSignal::bs2::connection;
//---------------------------------------------------------------------------
// Declaration of CSignalWithBase
//---------------------------------------------------------------------------

template<class TFunction, template<class> class TBaseSignal>
class CSignalWithBase {
public:
  template<class TArg>
  using CBaseSignal = TBaseSignal<TArg>;
  using result_type = typename CBaseSignal<TFunction>::result_type;
  using slot_function_type = typename CBaseSignal<TFunction>::slot_function_type;
  using slot_type = typename CBaseSignal<TFunction>::slot_type;

  template<class... TArg>
  result_type operator()(TArg&&... arg);

  template<class TObject, class TMethod>
  CConnection connectMethod(TObject* pObject, TMethod&& Method);
protected:
private:
  CBaseSignal<TFunction> Signal_;
};
//---------------------------------------------------------------------------
// Declaration of CSignal
//---------------------------------------------------------------------------

template<class TFunction>
using CSignal = CSignalWithBase<TFunction, CBaseSignal>;
//---------------------------------------------------------------------------
// Declaration of CGetterSignal
//---------------------------------------------------------------------------

template<class TFunction>
using CGetterSignal = CSignalWithBase<TFunction, CBaseGetterSignal>;
//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {
//---------------------------------------------------------------------------
// Definition of CSignal
//---------------------------------------------------------------------------

template<class TFunction, template<class> class TBaseSignal>
template<class TObject, class TMethod>
CConnection
CSignalWithBase<TFunction, TBaseSignal>::connectMethod(TObject* pObject, TMethod&& Method) {
  return Signal_.connect(bindMethod(pObject, std::forward<TMethod>(Method)));
}
//---------------------------------------------------------------------------

template<class TFunction, template<class> class TBaseSignal>
template<class... TArg>
typename CSignalWithBase<TFunction, TBaseSignal>::result_type
CSignalWithBase<TFunction, TBaseSignal>::operator()(TArg&&... arg) {
  return Signal_(std::forward<TArg>(arg)...);
}
//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // SIGNALS_H
