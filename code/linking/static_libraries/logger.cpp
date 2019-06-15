#include <iostream>
#include "logger.h"

Logger::Logger() {
  std::cerr << "Logger()" << std::endl;
}

Logger::~Logger() {
  std::cerr << "~Logger()" << std::endl;
}

Logger g_logger;

Logger& GetLogger() {
  return g_logger;
}
