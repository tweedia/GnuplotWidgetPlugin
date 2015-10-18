QT       += gui sql

TARGET = GnuplotWidgetPlugin
TEMPLATE = lib

CONFIG         += plugin
INCLUDEPATH    += ../Tweedia/Tweedia-with-plugins/Tweedia/

SOURCES += \
    gnuplot-widget-plugin.cpp \
    gnuplot-widget.cpp

HEADERS += \
    gnuplot-widget-plugin.h \
    gnuplot-widget.h

FORMS += \
    gnuplot-widget.ui
