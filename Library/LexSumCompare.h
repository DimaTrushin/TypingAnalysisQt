#ifndef LEXSUMCOMPARE_H
#define LEXSUMCOMPARE_H
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {
//---------------------------------------------------------------------------
// Declaration of CLexSumCompare
//---------------------------------------------------------------------------

template<class CFirstComparator, class CSecondComparator>
class CLexSumCompare {
public:
  using ArgumentType = typename CFirstComparator::ArgumentType;
  // TO DO
  // add static assert checking that
  // the argument types of the comparators are the same
  bool operator()(const ArgumentType& first,
                  const ArgumentType& second) const;
};
//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {
//---------------------------------------------------------------------------
// Definition of CLexSum
//---------------------------------------------------------------------------

template<class CFirstComparator, class CSecondComparator>
bool
CLexSumCompare<CFirstComparator, CSecondComparator>::operator()(
  const ArgumentType& first, const ArgumentType& second) const {
  if (CFirstComparator()(first, second))
    return true;
  if (CFirstComparator()(second, first))
    return false;
  return CSecondComparator()(first, second);
}
//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // LEXSUMCOMPARE_H
