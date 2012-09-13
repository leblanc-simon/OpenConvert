#-------------------------------------------------
#
# Project created by QtCreator 2011-01-07T18:42:03
#
#-------------------------------------------------

QT       += core gui webkit

TARGET = QOpenConvert
TEMPLATE = app

DESTDIR = ../bin


SOURCES += main.cpp\
        convertwindow.cpp \
    about.cpp

HEADERS  += convertwindow.h \
    about.h \
    version.h

FORMS    += convertwindow.ui \
    about.ui

OTHER_FILES += \
    ressources/index.html \
    ressources/css/style.css \
    ressources/js/base64.js \
    ressources/js/beautiful.js \
    ressources/js/html.js \
    ressources/js/jquery.min.js \
    ressources/js/url.js \
    ressources.rc

QMAKE_PRE_LINK += ../utils/build_html.sh

RESOURCES  += ressource.qrc

# Fichier ressource pour windows (num version, auteur, ...)
RC_FILE     = ressources.rc
