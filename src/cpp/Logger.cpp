#include "Logger.h"

#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

bool Logger::debugMode = true;

namespace {

std::tm toLocalTime(std::time_t time) {
    std::tm localTime{};
#if defined(_MSC_VER)
    localtime_s(&localTime, &time);
#else
    localTime = *std::localtime(&time);
#endif
    return localTime;
}

}  // namespace

std::string Logger::getTimestamp() {
    auto now = std::time(nullptr);
    auto tm = toLocalTime(now);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

void Logger::logInfo(const std::string& message) {
    std::cout << "[" << getTimestamp() << "] INFO: " << message << std::endl;
}

void Logger::logWarning(const std::string& message) {
    std::cout << "[" << getTimestamp() << "] WARNING: " << message << std::endl;
}

void Logger::logError(const std::string& message) {
    std::cerr << "[" << getTimestamp() << "] ERROR: " << message << std::endl;
}

void Logger::logDebug(const std::string& message) {
    if (debugMode) {
        std::cout << "[" << getTimestamp() << "] DEBUG: " << message << std::endl;
    }
}

void Logger::setDebugMode(bool mode) {
    debugMode = mode;
}

bool Logger::isDebugMode() {
    return debugMode;
}
