#ifndef CUSTOM_LOGGER_H
#define CUSTOM_LOGGER_H

typedef enum {
  LOG_INFO = 0,
  LOG_WARN = 1,
  LOG_ERROR = 2
} log_level_t;

void log_message(log_level_t level, const char *message);

#endif