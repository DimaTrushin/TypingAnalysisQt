//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <QApplication>
//#include "ApplicationImpl.h"
#include "Application.h"
#include "ExceptionHandler.h"
//---------------------------------------------------------------------------
// Main
//---------------------------------------------------------------------------

int main(int argc, char** argv) {
  QApplication AppLoop(argc, argv);
  try {
    NSApplication::CApplication Application;
    AppLoop.exec();
  } catch(std::exception& exception) {
    NSApplication::CExceptionHandler React(exception);
  } catch(...) {
    NSApplication::CExceptionHandler React;
  }
  return 0;
}
//---------------------------------------------------------------------------
