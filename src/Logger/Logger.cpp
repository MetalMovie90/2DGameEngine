#include "Logger.h"

#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <stdlib.h>

std::vector<LogEntry> Logger::messages;

std::string CurrentDateAndTimeToString()
{
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string output(30, '\0');
    std::strftime(&output[0], output.size(), "%d-%b-%Y %H:%M:%S", std::localtime(&now));
    return output;    
}

void Logger::Log(const std::string& message)
{
    LogEntry logEntry;
    logEntry.type = LOG_INFO;
    logEntry.message = "LOG: [" + CurrentDateAndTimeToString() + "]: " + message;
    std::cout << "\x1B[32m" << logEntry.message << "\033[0m" << std::endl;
    messages.push_back(logEntry);
}

void Logger::Err(const std::string& message)
{
    LogEntry logEntry;
    logEntry.type = LOG_ERROR;
    logEntry.message = "ERR: [" + CurrentDateAndTimeToString() + "]: " + message;
    std::cerr << "\x1B[91m" << logEntry.message << "\033[0m" << std::endl;
    messages.push_back(logEntry);
}