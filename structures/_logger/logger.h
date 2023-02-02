#pragma once

#include "../types.h"
#include <chrono>
#include <string>
#include <vector>

namespace structures
{
    /// <summary>
    /// Typ logovacej spravy.
    /// </summary>
    enum class LogType
    {
        Info,
        Warning,
        Error,
        Duration
    };

    /// <summary>
    /// Prevedie enum na string.
    /// </summary>
    /// <param name="type">Typ logu.</param>
    /// <returns>Retazcova reprezentacia enumu.</returns>
    std::string logTypeToString(LogType type);

    /// <summary>
    /// Rozhranie, ktore musi realizovat trieda,
    /// ktorej instancia chce pocuvat logovacie spravy.
    /// </summary>
    class ILogConsumer
    {
    public:
        virtual void logMessage(LogType type, const std::string& message) = 0;
        virtual void logDuration(size_t size, DurationType duration, const std::string& message) = 0;
    };

    /// <summary>
    /// Singleton logger, ktory umoznuje logovat dane typy sprav,
    /// pricom tieto spravy preposiela vsetkym svojim zaregistrovanym odberatelom.
    /// </summary>
    class Logger
    {
    public:
        static Logger& getInstance();

    public:
        void registerConsumer(ILogConsumer* consumer);

        void logInfo(const std::string& message);
        void logWarning(const std::string& message);
        void logError(const std::string& message);
        //void logDuration(size_t size, std::chrono::milliseconds duration, const std::string& message);
        void logDuration(size_t size, DurationType  duration, const std::string& message);

    private:
        Logger() = default;
        Logger(const Logger&) = delete;

        void log(LogType type, const std::string& message);

    private:
        std::vector<ILogConsumer*> consumers_;
    };
}