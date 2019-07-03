//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "SessionCacher.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Definition of CTextTreeFiller
//---------------------------------------------------------------------------

void CTextTreeFiller::fill(
  const CSession& Session, CTextDataTree* pTree) const {
  CSessionToTreeConverter Converter;
  Converter.convert(Session, pTree);
}
//---------------------------------------------------------------------------
// Definition of CShiftsDataFiller
//---------------------------------------------------------------------------

void CShiftsDataFiller::fill(const CSession& Session,
                             const CTextDataTree& Tree,
                             CShiftsData* pShiftsData) const {
  CShiftsWithDependenciesFiller Filler;
  Filler.fill(Session, Tree, pShiftsData);
}
//---------------------------------------------------------------------------
// Definition of CCapslocksDataFiller
//---------------------------------------------------------------------------

void CCapslocksDataFiller::fill(const CSession& Session,
                                const CTextDataTree& Tree,
                                CCapslocksData* pCapslocksData) const {
  CCapslocksWithDependenciesFiller Filler;
  Filler.fill(Session, Tree, pCapslocksData);
}
//---------------------------------------------------------------------------
// Definition of CSessionCacher
//---------------------------------------------------------------------------

CSessionCacher::CSessionCacher(const CSession* pSession)
  : SessionGetter_(pSession),
    TextTreeGetter_(SessionGetter_),
    ShiftsDataGetter_(SessionGetter_, TextTreeGetter_),
    CapslocksDataGetter_(SessionGetter_, TextTreeGetter_) {
}
//---------------------------------------------------------------------------

const CSession& CSessionCacher::getSession() const {
  return SessionGetter_();
}
//---------------------------------------------------------------------------

const CTextDataTree& CSessionCacher::getTextTree() const {
  return TextTreeGetter_();
}
//---------------------------------------------------------------------------

const CShiftsData& CSessionCacher::getShiftsData() const {
  return ShiftsDataGetter_();
}
//---------------------------------------------------------------------------

const CCapslocksData& CSessionCacher::getCapslocksData() const {
  return CapslocksDataGetter_();
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
