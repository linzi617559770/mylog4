#include "mylog4qt.h"
#include <QCoreApplication>

Log4Qt::Logger * MyLog4qt::logger = NULL;
int MyLog4qt::fileSize = 10*1024 ;
int MyLog4qt::fileNum = 5;
QString MyLog4qt::saveFilePeriod = SAVEFILEPERIOD_DAY;
Log4Qt::PatternLayout *MyLog4qt::playout = NULL;
Log4Qt::SimpleLayout * MyLog4qt::slayout =NULL;
Log4Qt::TTCCLayout * MyLog4qt::tlayout =NULL;

MyLog4qt::MyLog4qt(QObject *parent) : QObject(parent)
{

}

/*************************************************
*@Function: setFileSizeAndFileNum
*@Description:当log日志输出位置为RollingFileAppender（在达到特定大小时滚动日志文件）使用
*@param:
*@Return:
*@Others:  注意：如果log日志输出位置为RollingFileAppender，那么setFileSizeAndFileNum必须在
*               initLog4qt（）函数前调用
*************************************************/
void MyLog4qt::setFileSizeAndFileNum(int file_Size, int file_Num)
{
    fileSize = file_Size;
    fileNum = file_Num;
}

/*************************************************
*@Function: setSaveFilePeriod
*@Description:  当log日志输出位置为DailyRollingFileAppender使用,以指定的频率滚动日志文件。
*@param:        "'.'yyyy-MM-dd-hh-mm"	每分钟
                "'.'yyyy-MM-dd-hh"	每小时
                "'.'yyyy-MM-dd-a"	每半天
                "'.'yyyy-MM-dd"	每天
                "'.'yyyy-ww"	每周
                "'.'yyyy-MM"	每月
*@Return:
*@Others: 注意：如果log日志输出位置为DailyRollingFileAppender，那么setSaveFilePeriod必须在
*               initLog4qt（）函数前调用
*************************************************/
void MyLog4qt::setSaveFilePeriod(const QString &period)
{
    saveFilePeriod = period;
}

/*************************************************
*@Function:
*@Description:
*@param:
*@Return:
*@Others: 注意：1 日志等级建议只使用 DEBUG、INFO、WARN、ERROR
*               日志级别ALL < TRACE < DEBUG < INFO < WARN < ERROR < FATAL
*************************************************/
void MyLog4qt::initLog4qt(LogFormattingType type, AppenderType appenderType, Log4Qt::Level level)
{

    Log4Qt::PatternLayout *playout = NULL;
    Log4Qt::SimpleLayout * slayout =NULL;
    Log4Qt::TTCCLayout * tlayout =NULL;

    switch(type)
    {
        case patternLayout:
        {
            // 创建一个 PatternLayout（根据模式字符串输出日志事件）
            logger = Log4Qt::Logger::rootLogger();
            playout = new Log4Qt::PatternLayout();

            //playout->setHeader("Header");                      // 设置标头信息
            //playout->setFooter("Footer");                      // 设置页脚信息

            //不仅会输出消息内容，还会输出启动时间、线程名称、logger 名称：
            // layout->setConversionPattern(Log4Qt::PatternLayout::TTCC_CONVERSION_PATTERN);
            playout->setName("My Layout");
            playout->activateOptions();
         }
            break;
        case simpleLayout:
        {
            // 创建一个 SimpleLayout（输出日志的级别和消息内容）
            logger = Log4Qt::Logger::rootLogger();
            slayout = new Log4Qt::SimpleLayout();
            slayout->setName("My Layout");
            slayout->activateOptions();
        }
            break;
        case ttccLayout:
        {
            // 创建一个 TTCCLayout（输出时间、线程、Logger 以及消息内容）
             logger = Log4Qt::Logger::rootLogger();
             tlayout = new Log4Qt::TTCCLayout();
             tlayout->setCategoryPrefixing(true);  // 禁用 logger 名称
             tlayout->setContextPrinting(true);  // 使用嵌套的上下文信息
             tlayout->setThreadPrinting(true);  // 使用线程名
             tlayout->setDateFormat("ISO8601");  // 设置日期格式
             tlayout->setName("My Layout");
             tlayout->activateOptions();
        }
            break;
        default:
        {
            logger = Log4Qt::Logger::rootLogger();
            tlayout = new Log4Qt::TTCCLayout();
            tlayout->setCategoryPrefixing(true);  // 禁用 logger 名称
            tlayout->setContextPrinting(true);  // 使用嵌套的上下文信息
            tlayout->setThreadPrinting(true);  // 使用线程名
            tlayout->setDateFormat("ISO8601");  // 设置日期格式
            tlayout->setName("My Layout");
            tlayout->activateOptions();
        }
            break;
    }

    switch (appenderType)
    {
        case consoleAppender:
        {
             // 创建一个 ConsoleAppender（将日志内容输出到控制台上）
            Log4Qt::ConsoleAppender *appender;
            switch(type)
            {
                case patternLayout:
                    appender = new Log4Qt::ConsoleAppender(playout, Log4Qt::ConsoleAppender::STDOUT_TARGET);
                    break;
                case simpleLayout:
                    appender = new Log4Qt::ConsoleAppender(slayout, Log4Qt::ConsoleAppender::STDOUT_TARGET);
                    break;
                case ttccLayout:
                     appender = new Log4Qt::ConsoleAppender(tlayout, Log4Qt::ConsoleAppender::STDOUT_TARGET);
                    break;
                default:
                     appender = new Log4Qt::ConsoleAppender(tlayout, Log4Qt::ConsoleAppender::STDOUT_TARGET);
                    break;
            }


             appender->setName("My Appender");
             appender->activateOptions();

             // 在 logger 上添加 appender
             logger->addAppender(appender);
            break;
        }
        case fileAppender:
        {
            // 创建一个 FileAppender（将日志内容输出到文件中）
             QString file = QCoreApplication::applicationDirPath() + LOGFILE_PATH;

            /*
            *@brief 在构造 FileAppender 时，可以用第三个参数指定文件的打开方式，true 表示以追加的方式打开，
            *       false 表示以截断的方式打开。 除此之外，也可以使用 setAppendFile(bool append)。
            */
             Log4Qt::FileAppender *appender;
             switch(type)
             {
                 case patternLayout:
                      appender = new Log4Qt::FileAppender(playout, file, true);
                     break;
                 case simpleLayout:
                      appender = new Log4Qt::FileAppender(slayout, file, true);
                     break;
                 case ttccLayout:
                       appender = new Log4Qt::FileAppender(tlayout, file, true);
                     break;
                 default:
                       appender = new Log4Qt::FileAppender(tlayout, file, true);
                     break;
             }

             appender->setName("My Appender");
             appender->activateOptions();

             // 在 logger 上添加 appender
             logger->addAppender(appender);
         }
            break;
        case dailyRollingFileAppender:
        {
            // 创建一个 DailyRollingFileAppender（每个周期生成一个新文件）
            QString file = QCoreApplication::applicationDirPath() + LOGFILE_PATH;

            Log4Qt::DailyRollingFileAppender *appender;
            switch(type)
            {
                case patternLayout:
                     appender = new Log4Qt::DailyRollingFileAppender(playout, file, saveFilePeriod);
                    break;
                case simpleLayout:
                     appender = new Log4Qt::DailyRollingFileAppender(slayout, file, saveFilePeriod);
                    break;
                case ttccLayout:
                      appender = new Log4Qt::DailyRollingFileAppender(tlayout, file, saveFilePeriod);
                    break;
                default:
                      appender = new Log4Qt::DailyRollingFileAppender(tlayout, file, saveFilePeriod);
                    break;
            }

            appender->setName("My Appender");
            appender->activateOptions();

            // 在 logger 上添加 appender
            logger->addAppender(appender);
        }
            break;
        case rollingFileAppender:
        {
            // 创建一个 RollingFileAppender
            QString file = QCoreApplication::applicationDirPath() + LOGFILE_PATH;

            Log4Qt::RollingFileAppender *appender;
            switch(type)
            {
                case patternLayout:
                      appender = new Log4Qt::RollingFileAppender(playout, file, true);
                    break;
                case simpleLayout:
                      appender = new Log4Qt::RollingFileAppender(slayout, file, true);
                    break;
                case ttccLayout:
                       appender = new Log4Qt::RollingFileAppender(tlayout, file, true);
                    break;
                default:
                       appender = new Log4Qt::RollingFileAppender(tlayout, file, true);
                    break;
            }

            appender->setName("My Appender");
            appender->setMaximumFileSize(fileSize);            // 文件的最大大小
            appender->setMaxBackupIndex(fileNum);              // 最大文件数个数
            appender->activateOptions();

            // 在 logger 上添加 appender
            logger->addAppender(appender);
        }
            break;
        default:
            break;

    }

    /*
    *@brief设置日志级别  注意：：日志文件级别还可以使用文件设置具体使用参考
    *       http://blog.csdn.net/liang19890820/article/details/78845511
    */
    logger->setLevel(level);

}

void MyLog4qt::logDebug(const QString &message)
{
    logger->debug(message);
}

void MyLog4qt::logWarn(const QString &message)
{
    logger->warn(message);
}

void MyLog4qt::logError(const QString &message)
{
    logger->error(message);
}

void MyLog4qt::logInfo(const QString &message)
{
    logger->info(message);
}

void MyLog4qt::shutdownLog()
{
    // 关闭 logger
      logger->removeAllAppenders();
      logger->loggerRepository()->shutdown();
}
