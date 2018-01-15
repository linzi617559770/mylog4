#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <mylog4qt.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //使用控制台
    MyLog4qt::initLog4qt(MyLog4qt::ttccLayout,MyLog4qt::consoleAppender,Log4Qt::Level::DEBUG_INT);
    MyLog4qt::logInfo("hello log4qt");
    MyLog4qt::logDebug("hello ");
    MyLog4qt::logWarn("hello l");
    MyLog4qt::logError("hello lo");

    //使用文件
    /*MyLog4qt::initLog4qt(MyLog4qt::ttccLayout,MyLog4qt::fileAppender,Log4Qt::Level::DEBUG_INT);
    MyLog4qt::logInfo("hello log4qt");
    MyLog4qt::logDebug("hello ");
    MyLog4qt::logWarn("hello l");
    MyLog4qt::logError("hello lo");
    MyLog4qt::shutdownLog();*/

    //以指定的频率滚动日志文件
    /*MyLog4qt::setSaveFilePeriod(SAVEFILEPERIOD_MINUTE);
    MyLog4qt::initLog4qt(MyLog4qt::ttccLayout,MyLog4qt::dailyRollingFileAppender,Log4Qt::Level::DEBUG_INT);

    int count = 0;
    while (count < 100) {
        // 输出信息
         MyLog4qt::logDebug(QString("hello %1").arg(count));
        QThread::sleep(1);
        ++count;
    }*/

    //在达到特定大小时滚动日志文件
    /*MyLog4qt::setFileSizeAndFileNum(100*1024,5);
    MyLog4qt::initLog4qt(MyLog4qt::ttccLayout,MyLog4qt::rollingFileAppender,
                          Log4Qt::Level::DEBUG_INT);
    QFile file("RollingFileAppender.txt");
    if(file.open(QIODevice::ReadOnly))
    {
        QString str = file.readAll();
        MyLog4qt::logDebug("10");
    }
    file.close();*/
}

MainWindow::~MainWindow()
{
    delete ui;
}
