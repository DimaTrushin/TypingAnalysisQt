#ifndef SESSIONCACHER_H
#define SESSIONCACHER_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "Library/EnumCacher.h"
#include "CapitalWithDependenciesFiller.h"
#include "SessionToTreeConverter.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Declaration of CSessionGetter
//---------------------------------------------------------------------------

using CSessionGetter = NSLibrary::CSimpleGetter<CSession>;
//---------------------------------------------------------------------------
// Declaration of CTextTreeFiller
//---------------------------------------------------------------------------

class CTextTreeFiller {
public:
  using CValue = CTextDataTree;
  void fill(const CSession& Session, CTextDataTree* pTree) const;
};
//---------------------------------------------------------------------------
// Declaration of CTextTreeGetter
//---------------------------------------------------------------------------

using CTextTreeGetter =
  NSLibrary::CEnumCacherNoParam<CTextTreeFiller, CSessionGetter>;
//---------------------------------------------------------------------------
// Declaration of CShiftsDataFiller
//---------------------------------------------------------------------------

class CShiftsDataFiller {
public:
  using CValue = CShiftsData;
  void fill(const CSession& Session,
            const CTextDataTree& Tree,
            CShiftsData* pShiftsData) const;
};
//---------------------------------------------------------------------------
// Declaration of CShiftsDataGetter
//---------------------------------------------------------------------------

using CShiftsDataGetter =
  NSLibrary::CEnumCacherNoParam<
  CShiftsDataFiller, CSessionGetter, CTextTreeGetter>;
//---------------------------------------------------------------------------
// Declaration of CCapslocksDataFiller
//---------------------------------------------------------------------------

class CCapslocksDataFiller {
public:
  using CValue = CCapslocksData;
  void fill(const CSession& Session,
            const CTextDataTree& Tree,
            CCapslocksData* pCapslocksData) const;
};
//---------------------------------------------------------------------------
// Declaration of CCapslocksDataGetter
//---------------------------------------------------------------------------

using CCapslocksDataGetter =
  NSLibrary::CEnumCacherNoParam<
  CCapslocksDataFiller, CSessionGetter, CTextTreeGetter>;
//---------------------------------------------------------------------------
// Declaration of CSessionCacher
//---------------------------------------------------------------------------

class CSessionCacher {
public:
  CSessionCacher(const CSession* pSession);
  const CSession& getSession() const;
  const CTextDataTree& getTextTree() const;
  const CShiftsData& getShiftsData() const;
  const CCapslocksData& getCapslocksData() const;
private:
  CSessionGetter SessionGetter_;
  CTextTreeGetter TextTreeGetter_;
  CShiftsDataGetter ShiftsDataGetter_;
  CCapslocksDataGetter CapslocksDataGetter_;
};
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // SESSIONCACHER_H
