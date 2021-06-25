QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cpu.cpp \
    customlist.cpp \
    dialogwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    mytablewidgetitem.cpp \
    tablewidget.cpp

HEADERS += \
    cpu.hpp \
    customlist.hpp \
    dialogwindow.hpp \
    mainwindow.hpp \
    mytablewidgetitem.hpp \
    tablewidget.hpp

FORMS += \
    dialogwindow.ui \
    mainwindow.ui

TRANSLATIONS += \
    coursework_us_US.ts \
    coursework_ru_RU.ts \
    coursework_de_DE.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    DataBase

RESOURCES += \
    icons.qrc
