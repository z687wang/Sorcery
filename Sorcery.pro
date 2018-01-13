#-------------------------------------------------
#
# Project created by QtCreator 2017-07-20T22:02:23
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++14
QMAKE_CXXFLAGS += -std=c++14
QMAKE_CXXFLAGS += -g

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Sorcery
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    ascii_graphics.cc \
    Board.cc \
    Card.cc \
    Deck.cc \
    Enchantment.cc \
    Minion.cc \
    Player.cc \
    randomNum.cc \
    Ritual.cc \
    SorceryDex.cc \
    Spell.cc \
    Trigger.cc \
    Game.cc \
    canvas.cc \
    centercardtemplate.cc \
    cardtemplate.cc \
    enchantmentadcardtemplate.cc \
    enchantmentcardtemplate.cc \
    minionactivatedcardtemplate.cc \
    minioncardtemplate.cc \
    miniontriggeredcardtemplate.cc \
    playercardtemplate.cc \
    ritualcardtemplate.cc \
    spellcardtemplate.cc \
    main.cc

HEADERS += \
        canvas.h \
    cardtemplate.h \
    playercardtemplate.h \
    centercardtemplate.h \
    minioncardtemplate.h \
    ascii_graphics.h \
    Board.h \
    Card.h \
    CardType.h \
    Deck.h \
    Enchantment.h \
    Game.h \
    InvalidMoveException.h \
    Minion.h \
    Player.h \
    randomNum.h \
    Ritual.h \
    SorceryDex.h \
    Spell.h \
    Trigger.h \
    TriggerType.h \
    miniontriggeredcardtemplate.h \
    minionactivatedcardtemplate.h \
    enchantmentcardtemplate.h \
    enchantmentadcardtemplate.h \
    spellcardtemplate.h \
    ritualcardtemplate.h
