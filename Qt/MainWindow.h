#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <QMainWindow>
#include <memory> //pch
//---------------------------------------------------------------------------
// Foward Declaration of Ui::CMainWindow
//---------------------------------------------------------------------------

namespace Ui {
class CMainWindow;
}
//---------------------------------------------------------------------------

class QTextBrowser;
class QButtonGroup;
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSQt {
//---------------------------------------------------------------------------
// Declaration of CMainWindow
//---------------------------------------------------------------------------

class CMainWindow : public QMainWindow {
  Q_OBJECT
public:
  explicit CMainWindow(QWidget* parent = nullptr);
  ~CMainWindow();
signals:
  void onTextBrowserPerformanceLogVisible();
  void onTextBrowserMainTextVisible();
protected:
  bool eventFilter(QObject* watched, QEvent* event);

  CMainWindow* getMainWindowPtr();
  const CMainWindow* getMainWindowPtr() const;
  QTextBrowser* getMainTextBrowser();
  QButtonGroup* getTextModeButtonGroup();
  QButtonGroup* getShiftModeButtonGroup();
  QButtonGroup* getCapslockModeButtonGroup();
  Ui::CMainWindow* getUIptr();
  const Ui::CMainWindow* getUIptr() const;
private:
  bool textBrowserPerformanceLogEventFilter(QEvent* event);
  bool textBrowserMainTextEventFilter(QEvent* event);
private:
  void installEventFilters();
  void installEventFilterOnTextBrowserPerformanceLog();
  void installEventFilterOnTextBrowserMainText();
private:
  void adjustStaticInterface();
  void adjustSplitters();
  void adjustSplitter();
  void adjustSplitter2();
  void adjustSplitter3();
  void adjustSplitter5();
  void adjustSplitter6();
  void adjustButtonGroups();
  void adjustButtonGroup();
  void adjustButtonGroup2();
  void adjustButtonGroup3();
private:
  std::unique_ptr<Ui::CMainWindow> Interface_;
};
//---------------------------------------------------------------------------
} // NSQt
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // MAINWINDOW_H
