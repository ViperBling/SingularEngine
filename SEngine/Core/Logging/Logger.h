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

        /**
         * setup logger environment
         */
        static void InitLogger(const char* dir, const char* filename);

        static void Info(const char* message, ...);
        static void Warning(const char* message, ...);
        static void Error(const char* message, ...);

        static void InfoScript(const char* message, ...);
        static void WarningScript(const char* message, ...);
        static void ErrorScript(const char* message, ...);


        static void ToConsole(LogLevel level, const char* message);
        static void ToFile(const char* message);


    private:

        static void Log(LogLevel level, const char* tag, const char* message);

        static void SetupConsoleLog();
        static void SetupFileLog(const char* dir, const char* filename);

        static bool mbConsoleEnable;
        static bool mbFileEnable;
    };
}