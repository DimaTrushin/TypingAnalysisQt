#ifndef UIWRITER_H
#define UIWRITER_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <QObject>
#include "Library/Signals.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSInterface {
//---------------------------------------------------------------------------
// Description of usage
//---------------------------------------------------------------------------
//
// In order to use the pattern the base class TUIWriterBase MUST provide
// the following:
//
// 1) using CData is a type of the incomming data for the output
// 2) using CWidget is a type of the Widget to output data on
// 3) bool isReady() const is a method returning true if the Widget
// is ready to recieve the data, for example, if the widget is visible
// by the user
// 4) void output(const CData&) is a method performing the output
// of the data to the Widget
//
// Also, CUIWriter is subject to the following rules:
//
// 5) Before using CUIWriter we MUST connect a data source to it
// via connectDataSource
//
// 6) The data source MUST be callable with the signature:
// const CData*();
// The returning pointer MUST be valid after the call
//
// 7) In order to update the data we MUST connect a signal from
// the data source to the slot:
// void onNewDataReady()
//---------------------------------------------------------------------------
// Declaration of CUIWriter
//---------------------------------------------------------------------------

template<class TUIWriterBase>
class CUIWriter : public QObject, TUIWriterBase {
  using CBase = TUIWriterBase;
  using CData = typename CBase::CData;
  using CWidget = typename CBase::CWidget;
  using CDataSignal = NSLibrary::CGetterSignal<const CData*()>;
  using CConnection = NSLibrary::CConnection;
public:
  template<class TSource, class TSignal>
  CUIWriter(CWidget* pWidget, TSource* pSignalSource, TSignal&& Signal);

  void onNewDataReady();

  template<class TObject, class TMethod>
  CConnection connectDataSource(TObject* pObject, TMethod&& Method);
private:
  void onWidgetReady();

  bool NewData_;
  CDataSignal getData_;
};
//---------------------------------------------------------------------------
} // NSInterface
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSInterface {
//---------------------------------------------------------------------------
// Definition of CUIWriter
//---------------------------------------------------------------------------

template<class TUIWriterBase>
template<class TSource, class TSignal>
CUIWriter<TUIWriterBase>::CUIWriter(
  CWidget* pWidget, TSource* pSignalSource, TSignal&& Signal)
  : CBase(pWidget),
    NewData_(false) {
  if(!QObject::connect(pSignalSource,
                       std::forward<TSignal>(Signal),
                       this,
                       &CUIWriter::onWidgetReady))
    throw std::exception("Cannot connect Signal to CUIWriter slot!");
}
//---------------------------------------------------------------------------

template<class TUIWriterBase>
void CUIWriter<TUIWriterBase>::onNewDataReady() {
  NewData_ = true;
  if(CBase::isReady()) {
    CBase::output(*(getData_()));
    NewData_ = false;
  }
}
//---------------------------------------------------------------------------

template<class TUIWriterBase>
template<class TObject, class TMethod>
typename CUIWriter<TUIWriterBase>::CConnection
CUIWriter<TUIWriterBase>::connectDataSource(
  TObject* pObject, TMethod&& Method) {
  return getData_.connectMethod(pObject, std::forward<TMethod>(Method));
}
//---------------------------------------------------------------------------

template<class TUIWriterBase>
void CUIWriter<TUIWriterBase>::onWidgetReady() {
  if(NewData_) {
    CBase::output(*(getData_()));
    NewData_ = false;
  }
}
//---------------------------------------------------------------------------
} // NSInterface
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // UIWRITER_H
