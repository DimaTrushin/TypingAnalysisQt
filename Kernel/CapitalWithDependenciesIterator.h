#ifndef CAPITALWITHDEPENDENCIESITERATOR_H
#define CAPITALWITHDEPENDENCIESITERATOR_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "CapitalWithDependencies.h"
#include "StringFormat.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Declaration of CCapitalWithDependenciesIterator
//---------------------------------------------------------------------------

class CCapitalWithDependenciesIterator {
  using CVKCode = NSKeyboard::CVKCode;
  using CVKCodeType = CVKCode::CVKCodeType;
  using CCapWDepCont = CCapitalWithDependenciesContainer;
public:
  CCapitalWithDependenciesIterator(
    const CCapWDepCont& CapitalContainer,
    const CSession& Session,
    ETextMode textMode,
    ECapitalMode capitalMode,
    ECapitalType capitalType);
  ~CCapitalWithDependenciesIterator() = default;

  ETextFormat getTextFormat() const;
  CFormatStructure getTextFormatStructure() const;
  wchar_t getSymbol() const;
  CVKCodeType getVKCode() const;
  bool isValid() const;
  microseconds getPressingTime() const;
  microseconds getReleasingTime() const;
  void setNext();
  microseconds getPhysicalResponseTime() const;

  bool isEssential() const;
private:
  CCapWDepCont::const_iterator getBegin() const;
  CCapWDepCont::const_iterator getEssentialBegin() const;
  CCapWDepCont::const_iterator getEnd() const;

  void moveUntilEssential(
    ETextMode TextMode,
    CCapWDepCont::const_iterator* pIterator) const;
  unsigned int getDependencyNumber() const;
  // Iterator settings
  const CCapWDepCont* pCapitalContainer_;
  const CSession* pSession_;
  ETextMode TextMode_;
  ECapitalMode CapitalMode_;
  ECapitalType CapitalType_;

  CCapWDepCont::const_iterator CurrentPosition_;
};
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // CAPITALWITHDEPENDENCIESITERATOR_H
