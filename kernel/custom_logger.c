#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "custom_logger.h"

void log_message(log_level_t level, const char *message) {
  switch(level) {
    case LOG_INFO:
      printf("INFO − %s\n", message);
      break;
    case LOG_WARN:
      printf("WARNING − %s\n", message);
      break;
    case LOG_ERROR:
      printf("ERROR − %s\n", message);
      break;
    default:
      printf("UNKNOWN LEVEL − %s\n", message);
  }
}