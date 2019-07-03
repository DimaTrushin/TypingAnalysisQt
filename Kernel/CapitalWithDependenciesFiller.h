#ifndef CAPITALWITHDEPENDENCIESFILLER_H
#define CAPITALWITHDEPENDENCIESFILLER_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "CapitalWithDependencies.h"
#include "TextDataTree.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Declaration CCapitalWithDependenciesBeingPressed
//---------------------------------------------------------------------------

class CCapitalWithDependenciesBeingPressed
  : public std::list<CCapitalWithDependenciesContainer::iterator> {
public:
  void increasePrintedDependencies();
  void increaseDeletedDependencies();
private:
};
//---------------------------------------------------------------------------
// Declaration CShiftsWithDependenciesFiller
//---------------------------------------------------------------------------

class CShiftsWithDependenciesFiller {
public:
  void fill(const CSession& Session,
            const CTextDataTree& TextTree,
            CShiftsData* pShifts);
private:
  void fillWithoutDependencies(
    const CSession& Session, CShiftsData* pShifts);
  bool isThereSymbolAndShift(
    const CTextDataTree& TextTree, CShiftsData* pShifts) const;
  void setPressedShifts(CShiftsData* pShifts);
  void updateDependencies();
  void pressCurrentShifts(CShiftsData* pShifts);
  void removeReleasedShifts();
  bool initialize(const CSession& Session,
                  const CTextDataTree& TextTree,
                  CShiftsData* pShifts);

  CCapitalWithDependenciesBeingPressed PressedShifts_;
  CShiftsData::iterator itNextShift_;
  CTextDataTree::CConstFullTextIterator itCurrentSymbol_;
};
//---------------------------------------------------------------------------
// Declaration CCapslocksWithDependenciesFiller
//---------------------------------------------------------------------------

class CCapslocksWithDependenciesFiller {
public:
  void fill(const CSession& Session,
            const CTextDataTree& TextTree,
            CCapslocksData* pCapslocks);
private:
  class CCorrector {
  public:
    CCorrector(
      const CCapslocksData::iterator& itInitialPosition);
    void setToCorrectionPlace(ETextMode TextMode,
                              CCapslocksData* pCapitals);
    CCapslocksData::iterator& getPosition();
    bool needCorrection() const;
  private:
    bool needToMove(ETextMode TextMode) const;
    void moveLeft();
    void makeExceptionalMoveLeft(CCapslocksData* pCapitals);

    CCapslocksData::iterator itCorrectionPosition_;
    unsigned int NumberOfSkippedCapslocks_;
  };
  bool initialize(const CSession& Session,
                  const CTextDataTree& TextTree,
                  CCapslocksData* pCapslocks);

  void correctDependencies(CCapslocksData* pCapslocks);

  void correctDependencies(ETextMode TextMode, CCapslocksData* pCapslocks);
  void correctDependenciesOfOneCapslock(ETextMode TextMode,
                                        CCapslocksData::iterator itCapslock,
                                        CCapslocksData* pCapslocks);
  bool needToUseCorrector(ETextMode TextMode,
                          CCapslocksData::iterator itCapslock,
                          CCapslocksData* pCapslocks) const;

  void fillWithoutDependencies(
    const CSession& Session, CCapslocksData* pCapslocks);
  void moveCurrentSymbolAfterCurrentCapslock(const CTextDataTree& TextTree);
  void setNearestCapslock(CCapslocksData* pCapslocks);
  void updateDependencies();

  CCapslocksData::iterator itCurrentCapslock_;
  CTextDataTree::CConstFullTextIterator itCurrentSymbol_;
};
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // CAPITALWITHDEPENDENCIESFILLER_H
