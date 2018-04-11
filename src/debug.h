#ifndef DEBUG__h_
#define DEBUG__h_

#if 0
#define c_paintf_nrm(...)    c_paintf(_nrm, __VA_ARGS__)
#define c_paintf_red(...)    c_paintf(_red, __VA_ARGS__)
#define c_paintf_grn(...)    c_paintf(_grn, __VA_ARGS__)
#define c_paintf_blk(...)    c_paintf(_blk, __VA_ARGS__)
#define c_paintf_ylw(...)    c_paintf(_ylw, __VA_ARGS__)
#define c_paintf_blu(...)    c_paintf(_blu, __VA_ARGS__)
#define c_paintf_pur(...)    c_paintf(_pur, __VA_ARGS__)
#define c_paintf_cya(...)    c_paintf(_cya, __VA_ARGS__)
#define c_paintf_wht(...)    c_paintf(_wht, __VA_ARGS__)
#define c_paintf_inv(...)    c_paintf(_inv, __VA_ARGS__)
#define c_paintf_udl(...)    c_paintf(_udl, __VA_ARGS__)
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* -------------------------------- options --------------------------------- */
#define DEBUG_ENABLED

#define LL_ERROR_EN    1
#define LL_WARN_EN     1
#define LL_OKAY_EN     1
#define LL_INFO_EN     1
#define LL_DEBUG_EN    1

/* Reserved (not actually, see README) */
#define LL_VINFO_EN    0
#define LL_VDEBUG_EN   0
#define LL_VALL_EN     0

/* NOTE: recommend -not- making these any lower (stdout needs to buffer) */
#define PBUF_SZ      1024*1024*4
#define SYS_PBUF_SZ  1024*1024*8

// #define DEBUG_INFO_ENABLED
// #define DEBUG_MEM_ENABLED
// #define DEBUG_STRUCTORS_ENABLED

#define BLANK(...)

typedef enum {
   LL_ERROR  = 0, // log_level::error
   LL_WARN   = 1, // log_level::warn
   LL_OKAY   = 2, // log_level::okay
   LL_INFO   = 3, // log_level::info
   LL_DEBUG  = 4, // log_level::debug
   LL_VINFO  = 5, // log_level::vinfo
   LL_VDEBUG = 6, // log_level::vdebug
   LL_VALL   = 7, // log_level::vall
   LL_MAX    = 8  // invalid
} MYLOG_LEVELS_T;

/* -------------------------------- macros ---------------------------------- */

#ifdef MYLOG_LFLM
#define __MYLOG_ERROR(msg, file, line)   MYLOG_LFLM(error, file, line, msg )
#define __MYLOG_WARN(msg, file, line)    MYLOG_LFLM(warn, file, line, msg )
#define __MYLOG_OKAY(msg, file, line)    MYLOG_LFLM(okay, file, line, msg )
#define __MYLOG_INFO(msg, file, line)    MYLOG_LFLM(info, file, line, msg )
#define __MYLOG_DEBUG(msg, file, line)   MYLOG_LFLM(debug, file, line, msg )

#define __MYLOG_VINFO(msg, file, line)   MYLOG_LFLM(vinfo, file, line, msg )
#define __MYLOG_VDEBUG(msg, file, line)  MYLOG_LFLM(vdebug, file, line, msg )
#define __MYLOG_VALL(msg, file, line)    MYLOG_LFLM(vall, file, line, msg )
#else
#define __MYLOG_ERROR BLANK
#define __MYLOG_WARN  BLANK
#define __MYLOG_OKAY  BLANK
#define __MYLOG_INFO  BLANK
#define __MYLOG_DEBUG BLANK

#define __MYLOG_VINFO  BLANK
#define __MYLOG_VDEBUG BLANK
#define __MYLOG_VALL   BLANK
#endif /* MYLOG_LFLM */

/* ------------------------------- Vargs Pbuf ------------------------------- */
inline void DBG_PrintImpl(MYLOG_LEVELS_T level, const char * file, const size_t line, const char * format, ...)
{
    char buffer[PBUF_SZ];
    va_list args;
    va_start(args, format);
    vsprintf(buffer, format, args);

#ifdef MYLOG_LFLM

   switch (level) {
      case LL_ERROR: __MYLOG_ERROR(buffer, file, line); break;
      case LL_WARN:  __MYLOG_WARN(buffer, file, line);  break;
      case LL_OKAY:  __MYLOG_OKAY(buffer, file, line);  break;
      case LL_INFO:  __MYLOG_INFO(buffer, file, line);  break;
      case LL_DEBUG: __MYLOG_DEBUG(buffer, file, line); break;
      case LL_VINFO:
      case LL_VDEBUG:
      case LL_VALL:
         break;
      default:
         __MYLOG_ERROR("Uknown log_level", file, line); break;
         break;
   }

#else

   printf("%s", buffer);

#endif
    va_end(args);
}


/* --------------------------------- Debugs --------------------------------- */

/* Top-level defs */
#ifdef DEBUG_ENABLED
#define DBG_IMPL       DBG_PrintImpl
#else
#define DBG_IMPL       BLANK
#endif


/* Level Defines */
#if LL_ERROR_EN
#define logerror(...) DBG_IMPL(LL_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#else
#define logerror      BLANK
#endif

#if LL_WARN_EN
#define logwarn(...)  DBG_IMPL(LL_WARN, __FILE__, __LINE__, __VA_ARGS__)
#else
#define logwarn       BLANK
#endif

#if LL_OKAY_EN
#define logokay(...)    DBG_IMPL(LL_OKAY, __FILE__, __LINE__, __VA_ARGS__)
#else
#define logokay         BLANK
#endif

#if LL_INFO_EN
#define loginfo(...)  DBG_IMPL(LL_INFO, __FILE__, __LINE__, __VA_ARGS__)
#else
#define loginfo       BLANK
#endif

#if LL_DEBUG_EN
#define log(...)      DBG_IMPL(LL_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#else
#define log           BLANK
#endif

/* ----------------------------- Derived Debugs ----------------------------- */

#ifdef DEBUG_MEM_ENABLED
#define logmem        loginfo
#else
#define logmem        BLANK
#endif

#ifdef DEBUG_STRUCTORS_ENABLED
#define logstructor   loginfo
#else
#define logstructor   BLANK
#endif

/* -------------------------------------------------------------------------- */


#ifdef __cplusplus
}
#endif

#endif /* DEBUG__h_ */
