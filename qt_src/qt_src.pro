#-------------------------------------------------
#
# Project created by QtCreator 2021-08-16T13:13:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fileEncSys.out
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBS += -lcrypto -lssl

SOURCES += \
    ../src/master_key_c.cpp \
        main.cpp \
        mainwindow.cpp \
    dialog_password.cpp\
    ../src/file_enc.cpp\
    ../src/aes_c.cpp\
    ../src/sha_c.cpp \
    ../src/dynamic_mem_c.cpp \
    ../src/key_list_c.cpp \
    ../src/file_ptr_c.cpp \
    ../src/error.cpp\
    ../src/key_gen_c.cpp\
    ../src/device_c.cpp\
    dialog_dec_pass.cpp \
    pass_check.cpp \
    usb_select.cpp

HEADERS += \
    ../include/master_key_c.hpp \
        mainwindow.h \
    dialog_password.h \
    ../include/file_enc.hpp\
    ../include/aes_c.hpp\
    ../include/sha_c.hpp \
    ../include/dynamic_mem_c.hpp \
    ../include/macro.hpp\
    ../include/device_c.hpp\
    dialog_dec_pass.h \
    pass_check.h \
    usb_select.h

FORMS += \
        mainwindow.ui \
    dialog_password.ui \
    dialog_dec_pass.ui \
    pass_check.ui \
    usb_select.ui

DISTFILES +=
