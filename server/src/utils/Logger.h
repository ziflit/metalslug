#ifndef METALSLUG_LOGGER_H
#define METALSLUG_LOGGER_H


#define LOGGER_START(MIN_PRIORITY, FILE) Logger::start(MIN_PRIORITY, FILE);
#define LOGGER_STOP() Logger::stop();
#define LOGGER_WRITE(PRIORITY, MESSAGE, CLASSNAME) Logger::write(PRIORITY, MESSAGE, CLASSNAME);

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

/***
 * COMO USAR LOGGER:
 *  LOGGER_START(Logger::INFO, "")
 *  LOGGER_WRITE(Logger::CONFIG, "input file " + inputFileName)
 *  LOGGER_WRITE(Logger::DEBUG, "haciendo una cosa que tiene que loguearse en debug)
 *  LOGGER_WRITE(Logger::ERROR, "exception caught: " + str)
 *  LOGGER_WRITE(Logger::WARNING, "alguna advertencia")
 */

class Logger {
public:
    /**
     * Logging Priorities
     */
    enum Priority {
        DEBUG,
        CONFIG,
        INFO,
        WARNING,
        ERROR
    };

    /**
     * Arranca el log
     * @param minPriority prioridad minima del log. Los mensajes que tengan
     *              menor prioridad no seran mostrados en el archivo de log
     * @param logFile archivo de log
     */
    static void start(Priority minPriority, const string &logFile);

    /**
     * Frena el log
     */

    static void stop();

    /**
     * escribe el mensaje con la prioridad dada
     * @param priority
     * @param message
     */
    static void write(Priority priority, const string &message, const string &className);

private:
    bool active;
    ofstream fileStream;
    Priority minPriority;
    static const string PRIORITY_NAMES[];
    static Logger instance;

    /**
     * constructores privados porque es un patron singleton
     */

    Logger();

    Logger(const Logger &logger) {}

    /**
     * @param logger
     * @return
     */
    Logger &operator=(const Logger &logger) {}


};

#endif //METALSLUG_LOGGER_H
