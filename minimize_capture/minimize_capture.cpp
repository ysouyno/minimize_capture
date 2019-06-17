// minimize_capture.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <Windows.h>
#include <log4cxx/logger.h>

log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("minimize_capture"));

int main()
{
	LOG4CXX_INFO(logger, "main");
}
