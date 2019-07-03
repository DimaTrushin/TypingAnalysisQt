#ifndef BINDFIRST_H
#define BINDFIRST_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <utility> //pch
//#include <type_traits>
//---------------------------------------------------------------------------
namespace NSApplication {
namespace NSLibrary {
//---------------------------------------------------------------------------
// Definition of CBindFirst
//---------------------------------------------------------------------------

template <class TFunction, class TFirstArgType>
auto CBindFirst(TFunction&& f, TFirstArgType&& t) {
  return [f = std::forward<TFunction>(f), t = std::forward<TFirstArgType>(t)]
  (auto&&... args) {
    return f(t, std::forward<decltype(args)>(args)...);
  };
}
//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // BINDFIRST_H
