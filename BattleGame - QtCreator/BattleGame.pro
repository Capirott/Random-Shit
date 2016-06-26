
QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


SOURCES += main.cpp \
    Class/action.cpp \
    Class/piece.cpp \
    Class/Pieces/item.cpp \
    Class/Pieces/Targets/breed.cpp \
    Class/Pieces/Targets/Breeds/human.cpp \
    Class/Pieces/Targets/Breeds/orc.cpp \
    Class/Pieces/Targets/Breeds/Human/rogue.cpp \
    Class/Pieces/Targets/Breeds/Human/barbarian.cpp \
    Class/Pieces/Targets/Breeds/Orc/troll.cpp \
    Class/Pieces/Targets/Breeds/Orc/urukhai.cpp \
    Class/Pieces/chest.cpp \
    Class/Pieces/Items/bomb.cpp \
    Class/Pieces/target.cpp \
    Class/Pieces/Items/onehandeditem.cpp \
    Class/Pieces/Targets/rock.cpp \
    Class/Pieces/Items/potion.cpp \
    Class/Pieces/Items/OneHandedWeapons/axe.cpp \
    Class/Pieces/Items/OneHandedWeapons/sword.cpp \
    Class/Pieces/Items/OneHandedWeapons/bow.cpp \
    Class/Pieces/Items/OneHandedWeapons/shield.cpp \
    Class/game.cpp \
    mainwindow.cpp \
    renderarea.cpp \
    renderareastatus.cpp \
    dialog.cpp \
    configdialog.cpp

HEADERS += \
    Class/action.h \
    Class/piece.h \
    Class/Pieces/item.h \
    Class/Pieces/Targets/breed.h \
    Class/Pieces/Targets/Breeds/orc.h \
    Class/Pieces/Targets/Breeds/human.h \
    Class/Pieces/Targets/Breeds/Human/rogue.h \
    Class/Pieces/Targets/Breeds/Human/barbarian.h \
    Class/Pieces/Targets/Breeds/Orc/troll.h \
    Class/Pieces/Targets/Breeds/Orc/urukhai.h \
    Class/Pieces/chest.h \
    Class/Pieces/Items/bomb.h \
    Class/Pieces/target.h \
    Class/Pieces/Items/onehandeditem.h \
    Class/Pieces/Targets/rock.h \
    Class/Pieces/Items/potion.h \
    Class/Pieces/Items/OneHandedWeapons/sword.h \
    Class/Pieces/Items/OneHandedWeapons/bow.h \
    Class/Pieces/Items/OneHandedWeapons/shield.h \
    Class/Pieces/Items/OneHandedWeapons/axe.h \
    Class/game.h \
    mainwindow.h \
    renderarea.h \
    renderareastatus.h \
    dialog.h \
    configdialog.h

FORMS += \
    mainwindow.ui \
    dialog.ui \
    configdialog.ui

