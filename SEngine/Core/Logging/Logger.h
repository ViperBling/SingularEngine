#pragma once

#include <fstream>

namespace SingularEngine
{
    enum LogLevel
    {
        info,
        warning,
        error,
    };

    class Logger
    {
    public:

        static void InitLogger(const std::string& dir, const std::string& filename);

        static void Info(const std::string& msg, ...);
        static void Warning(const std::string& msg, ...);
        static void Error(const std::string& msg, ...);

        static void InfoScript(const std::string& msg, ...);
        static void WarningScript(const std::string& msg, ...);
        static void ErrorScript(const std::string& msg, ...);

        static void ToConsole(LogLevel level, const std::string& msg);
        static void ToFile(const std::string& msg);

    private:
        static void Log(LogLevel level, const std::string& tag, const std::string& msg);

        static void SetupConsoleLog();
        static void SetupFileLog(const std::string& dir, const std::string& filename);

        static bool mbConsoleEnable;
        static bool mbFileEnable;
    };
}