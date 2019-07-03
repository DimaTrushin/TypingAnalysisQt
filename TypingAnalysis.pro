TEMPLATE = app
TARGET = TypingAnalysis

QT = gui core
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += precompile_header
PRECOMPILED_HEADER  = stdafx.h

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

LIBS += User32.lib

# The following define allows linkage against boost
win32-msvc* {
  INCLUDEPATH += C:/boost/boost_1_67_0/boost_msvc2015/include/boost-1_67
  LIBS += "-LC:/boost/boost_1_67_0/boost_msvc2015/lib" \
          #-llibboost_date_time-vc140-mt-gd-x32-1_67 \
          #-llibboost_system-vc140-mt-gd-x32-1_67
}

SOURCES += \
    main.cpp \
    Keyboard/KeyPolicies.cpp \
    Qt/MainWindow.cpp \
    ApplicationGlobals.cpp \
    ApplicationLocals.cpp \
    ExceptionHandler.cpp \
    Timer.cpp \
    TimerAccess.cpp \
    Keyboard/RawKeyEvent.cpp \
    Keyboard/KeyboardState.cpp \
    Keyboard/RawKeyGenerator.cpp \
    Test/GlobalTester.cpp \
    Keyboard/KeyFilter.cpp \
    Keyboard/KeyboardHandler.cpp \
    Keyboard/LowLevelKeyboard.cpp \
    ApplicationInternal.cpp \
    Library/BasicFileLogger.cpp \
    TimedFileLogger.cpp \
    ApplicationInterface.cpp \
    AppKeyboardHandler.cpp \
    Kernel/KeyEvent.cpp \
    Interface/AppStatusReader.cpp \
    Kernel/Session.cpp \
    Kernel/Seance.cpp \
    Kernel/UserData.cpp \
    Kernel/TextMode.cpp \
    Kernel/TextDataTree.cpp \
    Kernel/RawBufferToSeanceConverter.cpp \
    Kernel/SessionToTreeConverter.cpp \
    Kernel/CapitalWithDependencies.cpp \
    Kernel/CapitalWithDependenciesFiller.cpp \
    Kernel/Approximation.cpp \
    Kernel/MarkedInterval.cpp \
    ThreadPool.cpp \
    ThreadPoolAccess.cpp \
    ParallelFor.cpp \
    Kernel/FunctionGrid.cpp \
    Kernel/SessionCacher.cpp \
    Kernel/UserEnvironment.cpp \
    AppUserEnvironment.cpp \
    Kernel/ColorManipulator.cpp \
    Kernel/StringFormatDefault.cpp \
    Kernel/StringFormat.cpp \
    Kernel/FormattedString.cpp \
    Kernel/SymbolIterator.cpp \
    Kernel/SessionIterator.cpp \
    Keyboard/FingerLayout.cpp \
    Kernel/Color.cpp \
    Kernel/CapitalWithDependenciesIterator.cpp \
    Kernel/RoverBase.cpp \
    Kernel/TextRover.cpp \
    Kernel/TextMaker.cpp \
    ApplicationImpl.cpp \
    Application.cpp \
    Interface/TextBrowserWriter.cpp \
    Kernel/KernelSettings.cpp \
    Kernel/Kernel.cpp \
    AppKernel.cpp \
    Interface/TextModeReader.cpp

FORMS += \
    Qt/cmainwindow.ui

HEADERS += \
    Keyboard/VKCode.h \
    Keyboard/SystemSymbol.h \
    Keyboard/KeyPolicies.h \
    Library/AnyGlobalAccess.h \
    Library/AnyLocalAccess.h \
    Qt/MainWindow.h \
    ApplicationGlobals.h \
    ApplicationLocals.h \
    ExceptionHandler.h \
    TimeDefinitions.h \
    Timer.h \
    TimerAccess.h \
    Keyboard/RawKeyEvent.h \
    Keyboard/KeyboardState.h \
    Keyboard/RawKeyGenerator.h \
    Library/DiscreteInterval.h \
    Test/GlobalTester.h \
    Keyboard/KeyFilter.h \
    Keyboard/KeyboardHandler.h \
    Keyboard/LowLevelKeyboard.h \
    ApplicationInternal.h \
    Library/BasicFileLogger.h \
    TimedFileLogger.h \
    ApplicationInterface.h \
    Library/Signals.h \
    Library/BindFirst.h \
    Library/BindMethod.h \
    AppKeyboardHandler.h \
    Kernel/KeyEvent.h \
    Interface/AppStatusReader.h \
    Kernel/Session.h \
    Kernel/Seance.h \
    Kernel/UserData.h \
    Kernel/TextMode.h \
    Kernel/TextSymbol.h \
    Kernel/TextDataTree.h \
    Library/VTree.h \
    Library/VectorHeapWithAccess.h \
    Kernel/RawBufferToSeanceConverter.h \
    Kernel/SessionToTreeConverter.h \
    Kernel/CapitalWithDependencies.h \
    Kernel/FunctionGridDefault.h \
    Library/SmoothFunction.h \
    Kernel/CapitalWithDependenciesFiller.h \
    Kernel/Approximation.h \
    Kernel/MarkedInterval.h \
    ThreadPool.h \
    ThreadPoolAccess.h \
    ParallelFor.h \
    Kernel/FunctionGrid.h \
    Kernel/RootFinder.h \
    Kernel/ExtremumFinder.h \
    Kernel/SessionCacher.h \
    Kernel/UserEnvironment.h \
    AppUserEnvironment.h \
    Kernel/StableZonesFiller.h \
    Kernel/ColorManipulator.h \
    Kernel/StringFormatDefault.h \
    Kernel/StringFormat.h \
    Kernel/FormattedString.h \
    Library/AnyObject.h \
    Kernel/AnyUIterator.h \
    Kernel/SymbolIterator.h \
    Kernel/SessionIterator.h \
    Keyboard/FingerLayout.h \
    Library/LexSumCompare.h \
    Library/EnumCacher.h \
    Kernel/Color.h \
    Kernel/CapitalWithDependenciesIterator.h \
    Kernel/RoverBase.h \
    Kernel/TextRover.h \
    Kernel/TextMaker.h \
    ApplicationImpl.h \
    Application.h \
    Interface/UIWriter.h \
    Interface/TextBrowserWriter.h \
    Kernel/KernelSettings.h \
    Kernel/Kernel.h \
    AppKernel.h \
    Interface/TextModeReader.h \
    stdafx.h
