#include "logger.h"

namespace structures
{
    Logger& Logger::getInstance()
    {
        static Logger instance;
        return instance;
    }

    void Logger::registerConsumer(ILogConsumer* consumer)
    {
        consumers_.emplace_back(consumer);
    }

    void Logger::logInfo(const std::string& message)
    {
        this->log(LogType::Info, message);
    }

    void Logger::logWarning(const std::string& message)
    {
        this->log(LogType::Warning, message);
    }

    void Logger::logError(const std::string& message)
    {
        this->log(LogType::Error, message);
    }

    //void Logger::logDuration(size_t size, std::chrono::milliseconds duration, const std::string& message)
    void Logger::logDuration(size_t size, DurationType  duration, const std::string& message)
    {
        for (ILogConsumer* consumer : consumers_)
        {
            consumer->logDuration(size, duration, message);
        }
    }
   


    void Logger::log(LogType type, const std::string& message)
    {
        for (ILogConsumer* consumer : consumers_)
        {
            consumer->logMessage(type, message);
        }
    }

    std::string logTypeToString(LogType type)
    {
        switch (type)
        {
        case LogType::Info:
            return "Info";

        case LogType::Warning:
            return "Warning";

        case LogType::Error:
            return "Error";

        case LogType::Duration:
            return "Duration";

        default:
            return "<unknown>";
        }
    }
}