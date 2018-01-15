#ifndef MYLOG4QT_H
#define MYLOG4QT_H

#include <QObject>
#include <QString>

#include <log4qt/basicconfigurator.h>
#include <log4qt/logger.h>
#include <log4qt/level.h>
#include <log4qt/logmanager.h>
#include <log4qt/ttcclayout.h>
#include <log4qt/fileappender.h>
#include <log4qt/patternlayout.h>
#include <log4qt/simplelayout.h>
#include <log4qt/consoleappender.h>
#include <log4qt/loggerrepository.h>
#include <log4qt/ttcclayout.h>
#include <log4qt/dailyrollingfileappender.h>
#include <log4qt/rollingfileappender.h>

#define LOGFILE_PATH "/MyLog4qt.log"

#define  SAVEFILEPERIOD_MINUTE  "'.'yyyy-MM-dd-hh-mm"	 //文件每分钟保存一次
#define  SAVEFILEPERIOD_HOUR  "'.'yyyy-MM-dd-hh"       //文件每小时保存一次
#define  SAVEFILEPERIOD_HALFDAY  "'.'yyyy-MM-dd-a"        //文件每半天保存一次
#define  SAVEFILEPERIOD_DAY  "'.'yyyy-MM-dd"          //文件每天保存一次
#define  SAVEFILEPERIOD_WEEK  "'.'yyyy-ww"             //文件每周保存一次
#define  SAVEFILEPERIOD_MONTH  "'.'yyyy-MM"             //文件每月保存一次

class MyLog4qt : public QObject
{
    Q_OBJECT
public:
    enum LogFormattingType{
        patternLayout,       //根据模式字符串输出日志事件
        simpleLayout,        //输出日志的级别和消息内容
        ttccLayout           //输出时间、线程、Logger 以及消息内容
    };

    //日志输出位置（比如控制台，文件等）
    enum AppenderType{
        writerAppender,             //将日志事件附加到 QTextStream
        consoleAppender,            //附加到 stdout 或 stderr
        fileAppender,               //将日志事件附加到文件
        dailyRollingFileAppender,   //以指定的频率滚动日志文件创建一个(每分钟生成一个新文件）
        rollingFileAppender         //在达到特定大小时滚动日志文件
    };

    explicit MyLog4qt(QObject *parent = nullptr);

    //初始化log4qt
    static void setFileSizeAndFileNum(int file_Size ,int file_Num);
    static void setSaveFilePeriod(const QString& period);
    static void initLog4qt(LogFormattingType type,AppenderType appenderType,Log4Qt::Level level);
    static void logDebug(const QString &message);
    static void logWarn(const QString &message);
    static void logError(const QString &message);
    static void logInfo(const QString &message);

    //关闭日志打印
    static void shutdownLog();

private:
     static Log4Qt::Logger *logger;
     static Log4Qt::PatternLayout *playout ;
     static Log4Qt::SimpleLayout * slayout;
     static Log4Qt::TTCCLayout * tlayout;

     //当log日志输出位置为DailyRollingFileAppender（以指定的频率滚动日志文件）使用
     static QString saveFilePeriod;

     //以下两个当log日志输出位置为RollingFileAppender（在达到特定大小时滚动日志文件）使用
     static int fileSize ;
     static int fileNum;

};

#endif // MYLOG4QT_H
