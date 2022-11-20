#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "webserv.hpp"

extern pthread_mutex_t g_write;

class Logger {
public:
	Logger() {}
	~Logger() {}
	static void printCriticalMessage(std::stringstream *message_);
	static void printInfoMessage(std::stringstream *message_);
	static void printDebugMessage(std::stringstream *message_);
};

#endif //LOGGER_HPP
