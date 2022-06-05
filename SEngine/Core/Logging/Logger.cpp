#include <cstdarg>
#include <iostream>
#include <ctime>
#include <filesystem>

#include "Logger.h"

using namespace SingularEngine;

static const std::string TAG_CORE = "[engine]";
static const std::string TAG_SCRIPT = "[mono]";
static const std::string LEVEL_INFO = "[info]";
static const std::string LEVEL_WARNING = "[warning]";
static const std::string LEVEL_ERROR = "[error]";

bool Logger::mbFileEnable = true;
bool Logger::mbConsoleEnable = true;

static std::ofstream logFile;
static char buffer[1024];

void Logger::InitLogger(const std::string &dir, const std::string &filename) {

    SetupConsoleLog();
    SetupFileLog(dir, filename);
}

void Logger::Info(const std::string &msg, ...) {

    va_list args;
    va_start(args, msg.c_str());
    vsprintf_s(buffer, msg.c_str(), args);
    va_end(args);
    Log(LogLevel::info, TAG_CORE, buffer);
}

void Logger::Warning(const std::string &msg, ...) {

    va_list args;
    va_start(args, msg.c_str());
    vsprintf_s(buffer, msg.c_str(), args);
    va_end(args);
    Log(LogLevel::warning, TAG_CORE, buffer);
}

void Logger::Error(const std::string &msg, ...) {

    va_list args;
    va_start(args, msg.c_str());
    vsprintf_s(buffer, msg.c_str(), args);
    va_end(args);
    Log(LogLevel::error, TAG_CORE, buffer);
}

void Logger::InfoScript(const std::string &msg, ...) {

    static char buffer[1024];
    va_list args;
    va_start(args, msg.c_str());
    vsprintf_s(buffer, msg.c_str(), args);
    va_end(args);
    Log(LogLevel::info, TAG_SCRIPT, buffer);
}

void Logger::WarningScript(const std::string &msg, ...) {

    static char buffer[1024];
    va_list args;
    va_start(args, msg.c_str());
    vsprintf_s(buffer, msg.c_str(), args);
    va_end(args);
    Log(LogLevel::warning, TAG_SCRIPT, buffer);
}

void Logger::ErrorScript(const std::string &msg, ...) {

    static char buffer[1024];
    va_list args;
    va_start(args, msg.c_str());
    vsprintf_s(buffer, msg.c_str(), args);
    va_end(args);
    Log(LogLevel::error, TAG_SCRIPT, buffer);
}

void Logger::ToConsole(LogLevel level, const std::string &msg) {

    if (level == LogLevel::error) {
        std::cerr << msg;
    }
    else {
        std::cout << msg;
    }
}

void Logger::ToFile(const std::string &msg) {

    logFile << msg;
    logFile.flush();
}

void Logger::Log(LogLevel level, const std::string &tag, const std::string &msg) {

    static char buffer[1024];
    static char timeBuffer[64];

    struct tm t{};
    time_t now = time(nullptr);
    localtime_s(&t,&now);
    strftime(timeBuffer, 64, "[%Y-%m-%d %H:%M:%S]", &t);

    std::string lvBuffer;
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

    sprintf_s(buffer, "%s%s%s - %s\n", timeBuffer, lvBuffer.c_str(), tag.c_str(), msg.c_str());

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

    setvbuf(stdout, nullptr, _IONBF, 0);

    mbConsoleEnable = true;
}

void Logger::SetupFileLog(const std::string &dir, const std::string &filename) {

    if (!std::filesystem::exists(dir))
    {
        std::filesystem::create_directory(dir);
    }

    auto filePath = std::filesystem::path(dir);
    std::cout << filename << ".log" << std::endl;

    filePath.append(filename);
    logFile.open(filePath.c_str(), std::ios::out | std::ios::app);

    mbFileEnable = true;
}
