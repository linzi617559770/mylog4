
# 定义 Log4Qt 源码路径
LOG4QT_SRC_PATH = $$PWD/Log4Qt-master/src

# 定义所需的宏
DEFINES += LOG4QT_LIBRARY

# 指定编译项目时应该被搜索的 #include 目录
INCLUDEPATH += $$LOG4QT_SRC_PATH \
               $$LOG4QT_SRC_PATH/log4qt \
               $$LOG4QT_SRC_PATH/log4qt/helpers \
               $$LOG4QT_SRC_PATH/log4qt/spi \
               $$LOG4QT_SRC_PATH/log4qt/varia

# 将 Log4Qt 源代码添加至项目中
include($$LOG4QT_SRC_PATH/log4qt/Log4Qt.pri)
include($$LOG4QT_SRC_PATH/../build.pri)
include($$LOG4QT_SRC_PATH/../g++.pri)

SOURCES += $$PWD/mylog4qt.cpp

HEADERS += $$PWD/mylog4qt.h
