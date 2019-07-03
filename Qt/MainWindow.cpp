//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "MainWindow.h"
#include "ui_cmainwindow.h"
// TO DO
// DEBUG
#include <QDebug>
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSQt {
//---------------------------------------------------------------------------
// Definition of CMainWindow
//---------------------------------------------------------------------------

CMainWindow::CMainWindow(QWidget* parent) :
  QMainWindow(parent),
  Interface_(std::make_unique<Ui::CMainWindow>()) {
  Interface_->setupUi(this);
  adjustStaticInterface();
  installEventFilters();
}
//---------------------------------------------------------------------------

CMainWindow::~CMainWindow() {
// I need an explicit destructor because the class contains
// a unique_ptr to an incomplete type
}
//---------------------------------------------------------------------------

bool CMainWindow::eventFilter(QObject* watched, QEvent* event) {
  if (watched == Interface_->textBrowser)
    return textBrowserPerformanceLogEventFilter(event);
  if (watched == Interface_->textBrowser_2)
    return textBrowserMainTextEventFilter(event);
  return QMainWindow::eventFilter(watched, event);
}
//---------------------------------------------------------------------------

CMainWindow* CMainWindow::getMainWindowPtr() {
  return this;
}
//---------------------------------------------------------------------------

const CMainWindow* CMainWindow::getMainWindowPtr() const {
  return this;
}
//---------------------------------------------------------------------------

QTextBrowser* CMainWindow::getMainTextBrowser() {
  return Interface_->textBrowser_2;
}
//---------------------------------------------------------------------------

QButtonGroup* CMainWindow::getTextModeButtonGroup() {
  return Interface_->buttonGroup;
}
//---------------------------------------------------------------------------

QButtonGroup* CMainWindow::getShiftModeButtonGroup() {
  return Interface_->buttonGroup_2;
}
//---------------------------------------------------------------------------

QButtonGroup* CMainWindow::getCapslockModeButtonGroup() {
  return Interface_->buttonGroup_3;
}
//---------------------------------------------------------------------------

Ui::CMainWindow* CMainWindow::getUIptr() {
  return Interface_.get();
}
//---------------------------------------------------------------------------

const Ui::CMainWindow* CMainWindow::getUIptr() const {
  return Interface_.get();
}
//---------------------------------------------------------------------------

bool CMainWindow::textBrowserPerformanceLogEventFilter(QEvent* event) {
  if(event->type() == QEvent::Show) {
    qDebug() << "PerformanceLog Visible";
    emit onTextBrowserPerformanceLogVisible();
  }
  return false;
}
//---------------------------------------------------------------------------

bool CMainWindow::textBrowserMainTextEventFilter(QEvent* event) {
  if(event->type() == QEvent::Show) {
    qDebug() << "MainText Visible";
    emit onTextBrowserMainTextVisible();
  }
  return false;
}
//---------------------------------------------------------------------------

void CMainWindow::installEventFilters() {
  // TO DO
  // Install EventFilters on the static interface components
  installEventFilterOnTextBrowserPerformanceLog();
  installEventFilterOnTextBrowserMainText();
}
//---------------------------------------------------------------------------

void CMainWindow::installEventFilterOnTextBrowserPerformanceLog() {
  Interface_->textBrowser->installEventFilter(this);
}
//---------------------------------------------------------------------------

void CMainWindow::installEventFilterOnTextBrowserMainText() {
  Interface_->textBrowser_2->installEventFilter(this);
}
//---------------------------------------------------------------------------

void CMainWindow::adjustStaticInterface() {
  adjustSplitters();
  adjustButtonGroups();
}
//---------------------------------------------------------------------------

void CMainWindow::adjustSplitters() {
  adjustSplitter();
  adjustSplitter2();
  adjustSplitter3();
  adjustSplitter5();
  adjustSplitter6();
}
//---------------------------------------------------------------------------

void CMainWindow::adjustSplitter() {
  Interface_->splitter->setSizes(QList<int>() << 1200 << 8800);
}
//---------------------------------------------------------------------------

void CMainWindow::adjustSplitter2() {
  Interface_->splitter_2->setSizes(QList<int>() << 8000 << 2000);
}
//---------------------------------------------------------------------------

void CMainWindow::adjustSplitter3() {
  Interface_->splitter_3->setSizes(QList<int>() << 8000 << 2000);
}
//---------------------------------------------------------------------------

void CMainWindow::adjustSplitter5() {
  Interface_->splitter_5->setSizes(QList<int>() << 8000 << 2000);
}
//---------------------------------------------------------------------------

void CMainWindow::adjustSplitter6() {
  Interface_->splitter_6->setSizes(QList<int>() << 1200 << 8800);
}
//---------------------------------------------------------------------------

void CMainWindow::adjustButtonGroups() {
  adjustButtonGroup();
  adjustButtonGroup2();
  adjustButtonGroup3();
}
//---------------------------------------------------------------------------

void CMainWindow::adjustButtonGroup() {
  Interface_->buttonGroup->setId(Interface_->radioButton, 0);
  Interface_->buttonGroup->setId(Interface_->radioButton_2, 1);
  Interface_->buttonGroup->setId(Interface_->radioButton_3, 2);
}
//---------------------------------------------------------------------------

void CMainWindow::adjustButtonGroup2() {
  Interface_->buttonGroup_2->setId(Interface_->radioButton_4, 0);
  Interface_->buttonGroup_2->setId(Interface_->radioButton_5, 1);
  Interface_->buttonGroup_2->setId(Interface_->radioButton_6, 2);
}
//---------------------------------------------------------------------------

void CMainWindow::adjustButtonGroup3() {
  Interface_->buttonGroup_3->setId(Interface_->radioButton_7, 0);
  Interface_->buttonGroup_3->setId(Interface_->radioButton_8, 1);
  Interface_->buttonGroup_3->setId(Interface_->radioButton_9, 2);
}
//---------------------------------------------------------------------------
} // NSQt
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
