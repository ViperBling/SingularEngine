#include "Logger.h"

#include <cstdarg>
#include <iostream>
#include <ctime>
#include <filesystem>

using namespace SingularEngine;

static const char* TAG_CORE = "[engine]";
static const char* TAG_SCRIPT = "[mono]";
static const char* LEVEL_INFO = "[info]";
static const char* LEVEL_WARNING = "[warning]";
static const char* LEVEL_ERROR = "[error]";

bool Logger::mbFileEnable = true;
bool Logger::mbConsoleEnable = true;

static std::ofstream log_file_;
static char buffer[1024];

void Logger::InitLogger(const char *dir, const char *filename) {

    SetupConsoleLog();
    SetupFileLog(dir, filename);
}

void Logger::Info(const char *message, ...) {

    va_list args;
        va_start(args, message);
    vsprintf_s(buffer, message, args);
        va_end(args);
    Log(LogLevel::info, TAG_CORE, buffer);
}

void Logger::Warning(const char *message, ...) {

    va_list args;
        va_start(args, message);
    vsprintf_s(buffer, message, args);
        va_end(args);
    Log(LogLevel::warning, TAG_CORE, buffer);
}

void Logger::Error(const char *message, ...) {

    va_list args;
        va_start(args, message);
    vsprintf_s(buffer, message, args);
        va_end(args);
    Log(LogLevel::error, TAG_CORE, buffer);
}

void Logger::InfoScript(const char *message, ...) {

    static char buffer[1024];
    va_list args;
        va_start(args, message);
    vsprintf_s(buffer, message, args);
        va_end(args);
    Log(LogLevel::info, TAG_SCRIPT, buffer);
}

void Logger::WarningScript(const char *message, ...) {

    static char buffer[1024];
    va_list args;
        va_start(args, message);
    vsprintf_s(buffer, message, args);
        va_end(args);
    Log(LogLevel::warning, TAG_SCRIPT, buffer);
}

void Logger::ErrorScript(const char *message, ...) {

    static char buffer[1024];
    va_list args;
        va_start(args, message);
    vsprintf_s(buffer, message, args);
        va_end(args);
    Log(LogLevel::error, TAG_SCRIPT, buffer);
}

void Logger::ToConsole(LogLevel level, const char *message) {

    if (level == LogLevel::error) {
        std::cerr << message;
    }
    else {
        std::cout << message;
    }
}

void Logger::ToFile(const char *message) {

    log_file_ << message;
    log_file_.flush();
}

void Logger::Log(LogLevel level, const char *tag, const char *message) {

    static char buffer[1024];
    static char timeBuffer[64];
    struct tm t;
    time_t now = time(0);
    localtime_s(&t,&now);
    strftime(timeBuffer, 64, "[%Y-%m-%d %H:%M:%S]", &t);

    const char* lvBuffer = nullptr;
    if (LogLevel::info == level)
    {
        lvBuffer = LEVEL_INFO;
    }
    else if (LogLevel::warning == level)
    {
        lvBuffer = LEVEL_WARNING;
    }
    else
    {
        lvBuffer = LEVEL_ERROR;
    }

    sprintf_s(buffer, "%s%s%s - %s\n", timeBuffer, lvBuffer, tag, message);

    if (mbConsoleEnable)
    {
        ToConsole(level, buffer);
    }
    if (mbFileEnable)
    {
        ToFile(buffer);
    }
}

void Logger::SetupConsoleLog() {

    // fix bug of clion internal debug console
    setvbuf(stdout, nullptr, _IONBF, 0);

    mbFileEnable = true;
}

void Logger::SetupFileLog(const char *dir, const char *filename) {

    if (!std::filesystem::exists(dir))
    {
        std::filesystem::create_directory(dir);
    }

    auto file_path = std::filesystem::path(dir);
    char buffer[128];
    sprintf_s(buffer, "%s.log", filename);
    file_path.append(buffer);
    log_file_.open(file_path.c_str(), std::ios::out | std::ios::app);
    mbConsoleEnable = true;
}

