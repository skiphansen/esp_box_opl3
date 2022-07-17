#ifndef _LOG_H_
#define _LOG_H_
#define LOG_RAW(format, ... ) printf(format,## __VA_ARGS__)

// Bare: No ANSI coloring, no log level, no timestamp
#define LOG(format, ... ) printf("%s: " format ,__FUNCTION__,## __VA_ARGS__)
#define LOGE(format, ... ) printf("%s#%d: " format ,__FUNCTION__,__LINE__,## __VA_ARGS__)
#define LOGW(format, ... ) printf("%s: " format ,__FUNCTION__,## __VA_ARGS__)
#define LOGI(format, ... ) printf("%s: " format ,__FUNCTION__,## __VA_ARGS__)
#define LOGD(format, ... ) printf("%s: " format ,__FUNCTION__,## __VA_ARGS__)
#if VERBOSE_LOGGING
#define LOGV(format, ... ) printf("%s: " format ,__FUNCTION__,## __VA_ARGS__)
#else
#define LOGV(format, ... )
#endif

#endif   // _LOG_H_

