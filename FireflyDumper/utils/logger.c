#include "logger.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <windows.h>

static bool use_colors = false;

static bool is_running_under_wine(void) {
    HKEY hKey;
    if (RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\Wine", 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        RegCloseKey(hKey);
        return true;
    }
    return false;
}

void logger_init(void) {
    use_colors = !is_running_under_wine();

    AllocConsole();

    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
    freopen("CONIN$", "r", stdin);

    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleMode(out, ENABLE_VIRTUAL_TERMINAL_PROCESSING | ENABLE_PROCESSED_OUTPUT | ENABLE_WRAP_AT_EOL_OUTPUT);
}

void logger_log(LogLevel level, const char *message) {
    if (use_colors) {
        switch (level) {
            case LOG_LEVEL_INFO:
                printf("\033[32m[INFO]\033[0m %s\n", message);
                break;
            case LOG_LEVEL_WARN:
                printf("\033[33m[WARN]\033[0m %s\n", message);
                break;
            case LOG_LEVEL_ERR:
                printf("\033[31m[ERROR]\033[0m %s\n", message);
                break;
        }
    } else {
        switch (level) {
            case LOG_LEVEL_INFO:
                printf("[INFO] %s\n", message);
                break;
            case LOG_LEVEL_WARN:
                printf("[WARN] %s\n", message);
                break;
            case LOG_LEVEL_ERR:
                printf("[ERROR] %s\n", message);
                break;
        }
    }
}

void logger_info(const char *message) {
    logger_log(LOG_LEVEL_INFO, message);
}

void logger_warn(const char *message) {
    logger_log(LOG_LEVEL_WARN, message);
}

void logger_error(const char *message) {
    logger_log(LOG_LEVEL_ERR, message);
}

void logger_infof(const char *fmt, ...) {
    char buffer[1024];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);
    logger_info(buffer);
}

void logger_warnf(const char *fmt, ...) {
    char buffer[1024];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);
    logger_warn(buffer);
}

void logger_errorf(const char *fmt, ...) {
    char buffer[1024];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);
    logger_error(buffer);
}
