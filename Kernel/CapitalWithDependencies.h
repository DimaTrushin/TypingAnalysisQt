#ifndef CAPITALWITHDEPENDENCIES_H
#define CAPITALWITHDEPENDENCIES_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "Session.h"
#include "TextMode.h"
#include <list> //pch
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Using
//---------------------------------------------------------------------------

using CapitalEvents = std::list<CSession::const_iterator>;
using ShiftEvents = CapitalEvents;
using CapslockEvents = CapitalEvents;
//---------------------------------------------------------------------------
// Declaration CCapitalWithDependencies
//---------------------------------------------------------------------------

class CCapitalWithDependencies {
public:
  CCapitalWithDependencies( const CSession::const_iterator& Iterator,
                            unsigned int numberOfDependentPrintedKeys = 0,
                            unsigned int numberOfDependentDeletedKeys = 0);

  unsigned int getNumberOfDependentPrintedKeys() const;
  unsigned int getNumberOfDependentDeletedKeys() const;
  unsigned int getNumberOfDependentFullKeys() const;

  unsigned int getNumberOfDependentKeys(ETextMode TextMode) const;
  const CSession::const_iterator& getIterator() const;
  CSession::const_iterator& getIterator();
  void setNumberOfDependentKeys(ETextMode TextMode, unsigned int newValue);

  bool isPrintedEssential() const;
  bool isFullEssential() const;
  bool isEssential(ETextMode TextMode) const;

  void increasePrintedDependencies();
  void increaseDeletedDependencies();

  void increaseNumberOfDependentKeysBy( ETextMode TextMode,
                                        unsigned int amount);
private:
  CSession::const_iterator KeyIterator_;
  unsigned int NumberOfDependentKeysInPrintedMode_;
  unsigned int NumberOfDependentKeysInFullMode_;
};
//---------------------------------------------------------------------------
// Forward Declarations
//---------------------------------------------------------------------------

class CPressedCapitalWithDependencies;
//---------------------------------------------------------------------------
// Declaration CCapitalWithDependenciesContainer
//---------------------------------------------------------------------------

class CCapitalWithDependenciesContainer
  : public std::deque<CCapitalWithDependencies> {
public:
  unsigned int getSize(ETextMode TextMode, ECapitalMode CapitalMode) const;
  bool isEmpty(ETextMode TextMode, ECapitalMode CapitalMode) const;

  const_iterator getFirstCapital(ETextMode TextMode,
                                 ECapitalMode CapitalMode) const;
  const_iterator getLastCapital(ETextMode TextMode,
                                ECapitalMode CapitalMode) const;
  // these return 0 if there were no pressing or releasing
  microseconds getFirstPressingTime(ETextMode TextMode,
                                    ECapitalMode CapitalMode) const;
  microseconds getFirstReleasingTime(ETextMode TextMode,
                                     ECapitalMode CapitalMode) const;
  microseconds getLastPressingTime(ETextMode TextMode,
                                   ECapitalMode CapitalMode) const;
  microseconds getLastReleasingTime(ETextMode TextMode,
                                    ECapitalMode CapitalMode) const;
private:
  unsigned int getNumberOfEssential(ETextMode TextMode) const;

  const_iterator getFirstEssentialCapital(ETextMode TextMode) const;

  const_iterator getLastEssentialCapital(ETextMode TextMode) const;

  microseconds getFirstReleasingTime() const;
  microseconds getFirstEssentialReleasingTime(ETextMode TextMode) const;

  microseconds getLastReleasingTime() const;
  microseconds getLastEssentialReleasingTime(ETextMode TextMode) const;
};
//---------------------------------------------------------------------------
// Declaration of CShiftsData
//---------------------------------------------------------------------------

using CShiftsData = CCapitalWithDependenciesContainer;
//---------------------------------------------------------------------------
// Declaration of CCapslocksData
//---------------------------------------------------------------------------

using CCapslocksData = CCapitalWithDependenciesContainer;
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // CAPITALWITHDEPENDENCIES_H
