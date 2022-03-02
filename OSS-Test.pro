QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui
INCLUDEPATH += $$PWD/aliyun-oss-cpp-sdk-1.9.0/sdk/include
#INCLUDEPATH += $$PWD/aliyun-oss-cpp-sdk-1.9.0/third_party/include
#LIBS += -L$$PWD/lib/ -llibcurl
#LIBS += -L$$PWD/lib/ -llibeay32
#LIBS += -L$$PWD/lib/ -lssleay32
#LIBS += -L$$PWD/lib/ -lzlibwapi
LIBS += -L$$PWD/lib/ -lalibabacloud-oss-cpp-sdk
# Default rules for deployment.
