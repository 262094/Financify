QT       += core gui sql network charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    charts.cpp \
    databasemanager.cpp \
    databasereader.cpp \
    main.cpp \
    mainwindow.cpp \
    transactions.cpp \
    transactionsWindow.cpp \
    goals.cpp \
    goalswindow.cpp \
    usermanager.cpp \
    usersession.cpp

HEADERS += \
    charts.h \
    databasemanager.h \
    databasereader.h \
    mainwindow.h \
    transactions.h \
    transactionsWindow.h \
    goals.h \
    goalswindow.h \
    usermanager.h \
    usersession.h

FORMS += \
    goalswindow.ui \
    mainwindow.ui \
    transactionsWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

STATECHARTS +=

RESOURCES += \
    icons.qrc


