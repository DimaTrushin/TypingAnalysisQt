//---------------------------------------------------------------------------
// Defines
//---------------------------------------------------------------------------

//#define __DISCRETE_INTERVAL_TEST__
//#define __KEY_INTERVAL_TEST__
//#define __KEY_FILTER_TEST__
//#define __LOW_LEVEL_KEYBOARD_TEST__
//#define __CACHE_BLOCKS_TEST__
//#define __RAW_BUFFER_TO_SEANCE_CONVERTER__
//#define __FINGER_LAYOUT_TEST__
//#define __SESSION_CACHER_TEST__
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "GlobalTester.h"
#ifdef __DISCRETE_INTERVAL_TEST__
#include "Library/DiscreteInterval.h"
#endif
#ifdef __KEY_INTERVAL_TEST__
#include "Keyboard/KeyFilter.h"
#endif
#ifdef __KEY_FILTER_TEST__
#include "Keyboard/KeyFilter.h"
#endif
#ifdef __LOW_LEVEL_KEYBOARD_TEST__
#include "Keyboard/LowLevelKeyboard.h"
#endif
#ifdef __CACHE_BLOCKS_TEST__
#include "Kernel/Session.h"
#include "Kernel/TextDataTree.h"
#include "Kernel/SessionToTreeConverter.h"
#include "Kernel/SessionCacher.h"
#endif
#ifdef __RAW_BUFFER_TO_SEANCE_CONVERTER__
#include "Kernel/RawBufferToSeanceConverter.h"
#endif
#ifdef __FINGER_LAYOUT_TEST__
#include "Keyboard/FingerLayout.h"
#endif
#ifdef __SESSION_CACHER_TEST__
#include "Kernel/SessionCacher.h"
#include "Keyboard/VKCode.h"
#endif
//---------------------------------------------------------------------------
namespace NSApplication {
namespace NSTest {
//---------------------------------------------------------------------------
// Definition of CGlobalTester
//---------------------------------------------------------------------------


CGlobalTester::CGlobalTester() {

}
//---------------------------------------------------------------------------
// Definition of CDiscreteIntervalTester
//---------------------------------------------------------------------------

#ifdef __DISCRETE_INTERVAL_TEST__
using namespace NSLibrary;
class CDiscreteIntervalTester {
public:
  CDiscreteIntervalTester()
    : DebugText_("") {
    DebugText_ = "DiscreteIntervalTest\n";
    makeTest(&DebugText_);
    qDebug() << DebugText_.c_str();
  }
  void makeTest(std::string* pText) {
    CDiscreteInterval<unsigned char> Interval1;
    CDiscreteInterval<unsigned char> Interval2(2, 5);
    CDiscreteInterval<unsigned char> Interval3(2, 4);
    CDiscreteInterval<unsigned char> Interval4(4, 3);
    printInterval(Interval1, pText);
    addNewLine(pText);
    printInterval(Interval2, pText);
    addNewLine(pText);
    printInterval(Interval3, pText);
    addNewLine(pText);
    printInterval(Interval4, pText);
    addNewLine(pText);
    auto Difference = Interval2.getDifference(Interval4);
    printIntervalList(Difference, pText);
    addSpace(pText);
    printNumberOfComponents(Interval2, Interval4, pText);
    //addNewLine(pText);
    //printComparison(Interval2, Interval4, pText);
    //addNewLine(pText);
    //printIfIntersects(Interval2, Interval4, pText);
    //addNewLine(pText);
    //printIfCovered(Interval2, Interval4, pText);
  }
  template<class TType>
  void printComparison(const CDiscreteInterval<TType>& Interval1,
                       const CDiscreteInterval<TType>& Interval2,
                       std::string* pText) {
    printInterval(Interval1, pText);
    *pText += " isStrictlyLess ";
    printInterval(Interval2, pText);
    *pText += " is ";
    *pText += std::to_string(isStrictlyLess(Interval1, Interval2));
  }
  template<class TType>
  void printNumberOfComponents(const CDiscreteInterval<TType>& Interval1,
                               const CDiscreteInterval<TType>& Interval2,
                               std::string* pText) {
    *pText += "cmp = ";
    *pText += std::to_string(Interval1.getNumberOfComponentsInDifference(Interval2));
  }
  template<class TType>
  void printIfCovered(const CDiscreteInterval<TType>& Interval1,
                      const CDiscreteInterval<TType>& Interval2,
                      std::string* pText) {
    printInterval(Interval1, pText);
    if (Interval1.isCoveredBy(Interval2))
      *pText += " is covered by ";
    else
      *pText += " is not covered by ";
    printInterval(Interval2, pText);
  }

  template<class TType>
  void printIfIntersects(const CDiscreteInterval<TType>& Interval1,
                         const CDiscreteInterval<TType>& Interval2,
                         std::string* pText) {
    printInterval(Interval1, pText);
    addSpace(pText);
    printInterval(Interval2, pText);
    addSpace(pText);
    if (Interval1.isIntersecting(Interval2)) {
      *pText += "intersect";
    } else {
      *pText += "do not intersect";
    }
  }
  template<class TType>
  void printInterval(const CDiscreteInterval<TType>& Interval,
                     std::string* pText) {
    std::string& Text = *pText;
    Text += "[";
    Text += std::to_string(static_cast<int>(Interval.First()));
    Text += ", ";
    Text += std::to_string(static_cast<int>(Interval.Last()));
    Text += "]";
  }
  template<class TType>
  void printIntervalList(const std::list<CDiscreteInterval<TType>>& IntervalList,
                         std::string* pText) {
    if(IntervalList.empty()) {
      *pText += "EmptyList";
      return;
    }
    std::string& Text = *pText;
    Text += "{";
    for(auto index = IntervalList.cbegin(); index != IntervalList.cend(); ++index) {
      printInterval(*index, &Text);
      Text += ", ";
    }
    Text.pop_back();
    Text.pop_back();
    Text += "}";
  }
  void addNewLine(std::string* pText) {
    *pText += '\n';
  }
  void addSpace(std::string* pText) {
    *pText += ' ';
  }
private:
  std::string DebugText_;
} DiscreteIntervalTester;
#endif
//---------------------------------------------------------------------------
// Definition of CKeyIntervalTester
//---------------------------------------------------------------------------
#ifdef __KEY_INTERVAL_TEST__
using namespace NSKeyboard;
class CKeyIntervalTester {
public:
  CKeyIntervalTester()
    : DebugText_("KeyIntervalTest\n") {
    makeTest(&DebugText_);
    qDebug() << DebugText_.c_str();
  }
  void makeTest(std::string* pText) {
    CKeyInterval Interval1;
    CKeyInterval Interval2(CVKCode::A, CVKCode::Z);
    CKeyInterval Interval3(CVKCode::A);

    printInterval(Interval1, pText);
    addNewLine();
    printInterval(Interval2, pText);
    addNewLine();
    printInterval(Interval3, pText);
    addNewLine();
    printInterval(CKeyInterval::getNumberInterval(), pText);
    addNewLine();
    printInterval(CKeyInterval::getEnglishSymbolInterval(), pText);

  }
  void printInterval(const CKeyInterval& Interval,
                     std::string* pText) {
    std::string& Text = *pText;
    Text += "[";
    Text += std::to_string(static_cast<int>(Interval.First()));
    Text += ", ";
    Text += std::to_string(static_cast<int>(Interval.Last()));
    Text += "]";
  }
  void addNewLine() {
    DebugText_ += '\n';
  }
  void addSpace() {
    DebugText_ += ' ';
  }
private:
  std::string DebugText_;
} KeyIntervalTester;
#endif
//---------------------------------------------------------------------------
// Definition of CKeyFilterTester
//---------------------------------------------------------------------------

#ifdef __KEY_FILTER_TEST__
using namespace NSKeyboard;
class CKeyFilterTester {
public:
  CKeyFilterTester()
    : DebugText_("KeyFilterTest\n") {
    makeTest(&DebugText_);
    qDebug() << DebugText_.c_str();
  }
  void makeTest(std::string* pText) {
    CKeyFilter KeyFilter;
    //KeyFilter.setToDefaultFilter();
    KeyFilter.AddInterval(CKeyInterval(1, 3));
    KeyFilter.AddInterval(CKeyInterval(7, 9));
    KeyFilter.AddInterval(CKeyInterval(12, 18));
    printKeyFilter(KeyFilter, pText);
  }
  void printKeyFilter(const CKeyFilter& KeyFilter,
                      std::string* pText) {
    if (KeyFilter.empty())
      return;
    for(const auto& Interval : KeyFilter) {
      printInterval(Interval, pText);
      *pText += " ";
    }
  }
  void printInterval(const CKeyInterval& Interval,
                     std::string* pText) {
    std::string& Text = *pText;
    Text += "[";
    Text += std::to_string(static_cast<int>(Interval.First()));
    Text += ", ";
    Text += std::to_string(static_cast<int>(Interval.Last()));
    Text += "]";
  }
  void addNewLine() {
    DebugText_ += '\n';
  }
  void addSpace() {
    DebugText_ += ' ';
  }
private:
  std::string DebugText_;
} KeyFilterTester;
#endif
//---------------------------------------------------------------------------
// Definition of CLowLevelKeyboardTester
//---------------------------------------------------------------------------

#ifdef __LOW_LEVEL_KEYBOARD_TEST__
using namespace NSKeyboard;
class CLowLevelKeyboardTester {
public:
  CLowLevelKeyboardTester() : DebugText_("LowLevelKeyboardTest\n") {
    makeTest(&DebugText_);
    qDebug() << DebugText_.c_str();
  }
  void makeTest(std::string* pText) {
    // TO DO
    *pText += "Test Here";
  }
  void addNewLine() {
    DebugText_ += '\n';
  }
  void addSpace() {
    DebugText_ += ' ';
  }
private:
  std::string DebugText_;
} LowLevelKeyboardTester;
#endif
//---------------------------------------------------------------------------
// Definition of CCacheBlocksTester
//---------------------------------------------------------------------------

#ifdef __CACHE_BLOCKS_TEST__
using namespace NSLibrary;
using namespace NSKernel;
using namespace NSKeyboard;
class CFunction {
public:
  int compute(int a, int b) const {
    return 2 * a + b;
  }
};

class CFun0 {
public:
  int compute() const {
    return 42;
  }
};

class CFun1 {
public:
  int compute(int a) const {
    return a;
  }
};

class CCacheBlocksTester {
public:
  class CTreeMaker {
  public:
    CTextDataTree compute(const CSession& Session) const {
      CTextDataTree Tree;
      CSessionToTreeConverter Converter;
      Converter.convert(Session, &Tree);
      return Tree;
    }
  };
  class CTreeFiller {
  public:
    void fill(const CSession& Session, CTextDataTree* pTree) const {
      CSessionToTreeConverter Converter;
      Converter.convert(Session, pTree);
    }
  };

  CCacheBlocksTester() : DebugText_("CacheBlocksTest\n") {
    makeTest(&DebugText_);
    qDebug() << DebugText_.c_str();
  }
  void makeTest(std::string* pText) {
    Q_UNUSED(pText);
    NSLibrary::CCacheTable<int> SimpleCacher;

    qDebug() << "cached = " << SimpleCacher.isCached();
    SimpleCacher.add(1);
    qDebug() << "cached = " << SimpleCacher.isCached();
    qDebug() << "value = " << SimpleCacher();

    NSLibrary::CCacheTable<int, int> CacherByInt;
    qDebug() << "cached = " << CacherByInt.isCached(0);
    CacherByInt.add(2, 0);
    qDebug() << "cached = " << CacherByInt.isCached(0);
    qDebug() << "value = " << CacherByInt(0);
    //CFunction Fun;
    //qDebug() << "Fun(1, 2) = " << Fun.compute(1, 2);
    //qDebug() << "call Fun(1, 2) = " << callMethod(&Fun, &CFunction::compute, CDataPackage<int, int>(1, 2));
    CSimpleCacher<CFun0, int> Cacher2;
    qDebug() << "execute = " << Cacher2();
    int value = 73;
    CSimpleGetter<int> Getter(&value);
    using CFirstBlock = CSimpleCacher<CFun1, int, CSimpleGetter<int>>;
    CSimpleCacher<CFun1, int, CSimpleGetter<int>> Cacher3(Getter);
    qDebug() << "Fun1 = " << Cacher3();
    qDebug() << "Fun1 = " << Cacher3();
    qDebug() << "Fun1 = " << Cacher3();
    CInput<CFirstBlock> Input3(&Cacher3);
    CSimpleCacher<CFun1, int, CInput<CFirstBlock>> Cacher4(Input3);
    qDebug() << "Fun1Fun1 = " << Cacher4();
    qDebug() << "Fun1Fun1 = " << Cacher4();
    qDebug() << "Fun1Fun1 = " << Cacher4();

    CSession Session;

    Session.push_back(CKeyEvent(CVKCode::A, 0, 0, 10));
    Session.push_back(CKeyEvent(CVKCode::B, 0, 20, 30));
    Session.push_back(CKeyEvent(CVKCode::LeftShift, 0, 35, 45));
    Session.push_back(CKeyEvent(CVKCode::C, 0, 40, 50));
    Session.push_back(CKeyEvent(CVKCode::Backspace, 0, 60, 70));
    Session.push_back(CKeyEvent(CVKCode::D, 0, 80, 90));

    CSimpleGetter<CSession> GetSession(&Session);
    using CTreeCacher =
      CSimpleCacher<CTreeMaker, CTextDataTree, CSimpleGetter<CSession>>;
    using CTreeFillerCacher =
      CFillerCacher<CTreeFiller, CTextDataTree, CSimpleGetter<CSession>>;
    CTreeFillerCacher GetFillTree(GetSession);
    CTreeCacher GetTree(GetSession);
    CTextDataTree Tree = GetTree();
    Tree = GetTree();
    Tree = GetTree();
    Tree = GetFillTree();
    Tree = GetFillTree();
    Tree = GetFillTree();

    for (CTextDataTree::CConstTextIterator it =
           Tree.beginText(ETextMode::Printed);
         it != Tree.endText(ETextMode::Printed);
         ++it) {
      qDebug() << "!";
    }
    qDebug() << "del pl = " << GetTree().getNumberOfPlacesWithDeletion();
    qDebug() << "del pl = " << GetFillTree().getNumberOfPlacesWithDeletion();

    CSessionCacher SessionCacher(&Session);
    const CTextDataTree& SessionTree = SessionCacher.getTextTree();
    qDebug() << "del symb = " << SessionTree.getNumberOfDeletedSymbols();
    qDebug() << "shift f all size = " << SessionCacher.getShiftsData().getSize(ETextMode::Full, ECapitalMode::All);
    qDebug() << "shift f ess size = " << SessionCacher.getShiftsData().getSize(ETextMode::Full, ECapitalMode::Essential);
    qDebug() << "shift f non size = " << SessionCacher.getShiftsData().getSize(ETextMode::Full, ECapitalMode::Non);

    qDebug() << "shift p all size = " << SessionCacher.getShiftsData().getSize(ETextMode::Printed, ECapitalMode::All);
    qDebug() << "shift p ess size = " << SessionCacher.getShiftsData().getSize(ETextMode::Printed, ECapitalMode::Essential);
    qDebug() << "shift p on size = " << SessionCacher.getShiftsData().getSize(ETextMode::Printed, ECapitalMode::Non);
  }


  void addNewLine() {
    DebugText_ += '\n';
  }
  void addSpace() {
    DebugText_ += ' ';
  }
private:
  std::string DebugText_;
} CacheBlocksTester;
#endif
//---------------------------------------------------------------------------
// Definition of CLowLevelKeyboardTester
//---------------------------------------------------------------------------

#ifdef __RAW_BUFFER_TO_SEANCE_CONVERTER__
using namespace NSKeyboard;
using namespace NSKernel;
class CRawBufferToSeanceConverterTest {
  using CRawBuffer = CRawEventContainer;
public:
  CRawBufferToSeanceConverterTest() : DebugText_("RawBufferToSeanceConverterTest\n") {
    qDebug() << DebugText_.c_str();
    makeTest(&DebugText_);
  }
  void makeTest(std::string* pText) {
    (void)pText;
    CRawBuffer RawBuffer;
    RawBuffer.push_back(CRawKey(49, 0, 0, 10));
    RawBuffer.push_back(CRawKey(50, 0, 0, 20));
    RawBuffer.push_back(CRawKey(49, 0, 1, 30));
    RawBuffer.push_back(CRawKey(50, 0, 1, 40));

    CSeance Seance;
    CRawBufferToSeanceConverter Converter;

    qDebug() << "buffer b size = " << RawBuffer.size();
    Converter.convert(&RawBuffer, &Seance);
    qDebug() << "buffer a size = " << RawBuffer.size();
    qDebug() << "seance size = " << Seance.size();

  }
  void addNewLine() {
    DebugText_ += '\n';
  }
  void addSpace() {
    DebugText_ += ' ';
  }
private:
  std::string DebugText_;
} RawBufferToSeanceConverterTest;
#endif
//---------------------------------------------------------------------------
#ifdef __FINGER_LAYOUT_TEST__
using namespace NSKeyboard;
class CFingerLayoutTest {
public:
  CFingerLayoutTest() : DebugText_("FingerLayoutTest\n") {
    qDebug() << DebugText_.c_str();
    makeTest(&DebugText_);
  }
  void makeTest(std::string* pText) {
    (void)pText;
    CFingerLayout Layout;
    CFingerLayout::generateDefaultLayout(&Layout);
    qDebug() << "Layout.size = " << Layout.size();
    for(const auto& finger : Layout) {
      qDebug() << " finger.size() = " << finger.size();
    }

  }
  void addNewLine() {
    DebugText_ += '\n';
  }
  void addSpace() {
    DebugText_ += ' ';
  }
private:
  std::string DebugText_;
} FingerLayoutTester;
#endif
//---------------------------------------------------------------------------

#ifdef __SESSION_CACHER_TEST__
using namespace NSKernel;
using namespace NSKeyboard;
class CSessionCacherTest {
public:
  CSessionCacherTest() : DebugText_("SessionCacherTest\n") {
    qDebug() << DebugText_.c_str();
    makeTest(&DebugText_);
  }
  void makeTest(std::string* pText) {
    (void)pText;
    CSession Session;

    Session.push_back(CKeyEvent(CVKCode::A, 0, 0, 10));
    Session.push_back(CKeyEvent(CVKCode::B, 0, 20, 30));
    Session.push_back(CKeyEvent(CVKCode::LeftShift, 0, 35, 45));
    Session.push_back(CKeyEvent(CVKCode::C, 0, 40, 50));
    Session.push_back(CKeyEvent(CVKCode::Backspace, 0, 60, 70));
    Session.push_back(CKeyEvent(CVKCode::D, 0, 80, 90));

    CSessionCacher SessionCacher(&Session);
    const CTextDataTree& SessionTree = SessionCacher.getTextTree();
    qDebug() << "del symb = " << SessionTree.getNumberOfDeletedSymbols();
    qDebug() << "shift f all size = " << SessionCacher.getShiftsData().getSize(ETextMode::Full, ECapitalMode::All);
    qDebug() << "shift f ess size = " << SessionCacher.getShiftsData().getSize(ETextMode::Full, ECapitalMode::Essential);
    qDebug() << "shift f non size = " << SessionCacher.getShiftsData().getSize(ETextMode::Full, ECapitalMode::Non);

    qDebug() << "shift p all size = " << SessionCacher.getShiftsData().getSize(ETextMode::Printed, ECapitalMode::All);
    qDebug() << "shift p ess size = " << SessionCacher.getShiftsData().getSize(ETextMode::Printed, ECapitalMode::Essential);
    qDebug() << "shift p on size = " << SessionCacher.getShiftsData().getSize(ETextMode::Printed, ECapitalMode::Non);

  }
  void addNewLine() {
    DebugText_ += '\n';
  }
  void addSpace() {
    DebugText_ += ' ';
  }
private:
  std::string DebugText_;
} SessionCacherTest;
#endif
//---------------------------------------------------------------------------
} // NSTest
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
