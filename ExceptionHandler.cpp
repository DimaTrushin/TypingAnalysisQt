//---------------------------------------------------------------------------
// include
//---------------------------------------------------------------------------

#include "ExceptionHandler.h"
//---------------------------------------------------------------------------

namespace NSApplication {
//---------------------------------------------------------------------------
// Definition of CExceptionHandler
//---------------------------------------------------------------------------

CExceptionHandler::CExceptionHandler() {
  MessageBox.setIcon(QMessageBox::Critical);
  MessageBox.setText(kUnknownExceptionMsg);
  MessageBox.exec();
}
//---------------------------------------------------------------------------

CExceptionHandler::CExceptionHandler(std::exception& exception) {
  MessageBox.setIcon(QMessageBox::Critical);
  MessageBox.setText(exception.what());
  MessageBox.exec();
}
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
