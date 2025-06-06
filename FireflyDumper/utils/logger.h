#ifndef LOGGER_H
#define LOGGER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERR
} LogLevel;

void logger_init(void);

void logger_log(LogLevel level, const char *message);

void logger_info(const char *message);
void logger_warn(const char *message);
void logger_error(const char *message);

// Formatted log versions
void logger_infof(const char *fmt, ...);
void logger_warnf(const char *fmt, ...);
void logger_errorf(const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif // LOGGER_H
