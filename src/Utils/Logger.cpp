#include "Logger.h"

const string Logger::PRIORITY_NAMES[] = {
        "DEBUG",
        "CONFIG",
        "INFO",
        "WARNING",
        "ERROR"
};

void Logger::start(Priority minPriority, const string &logFile) {
    instance.active = true;
    instance.minPriority = minPriority;
    if (logFile != "") {
        instance.fileStream.open(logFile.c_str());
    }
}

void Logger::stop() {
    instance.active = false;
    if (instance.fileStream.is_open()) {
        instance.fileStream.close();
    }
}

void Logger::write(Priority priority, const string &message) {
    if (instance.active && priority >= instance.minPriority) {
        ostream &stream = instance.fileStream.is_open() ? instance.fileStream : std::cout;
        stream << PRIORITY_NAMES[priority] << ": " << message << endl;
    }
}

Logger Logger::instance;

Logger::Logger() : active(false) {}