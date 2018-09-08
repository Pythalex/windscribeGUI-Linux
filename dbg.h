#ifndef __dbg_h__
#define __dbg_h__

#include <stdio.h>
#include <errno.h>
#include <string.h>

#ifdef NDEBUG
#define debug(M, ...)
#else

/**
 * Printf to stderr
 * 
 * The alternative #define debug that translates any use of debug("format", arg1,
 * arg2) into an fprintf call to stderr.
 **/
#define debug(M, ...) fprintf(stderr, "DEBUG %s:%d: " M " \n",\
	__FILE__, __LINE__, ##__VA_ARGS__)

/**
 * Printf to stderr. New line is not added.
 * 
 * The alternative #define debug that translates any use of debug("format", arg1,
 * arg2) into an fprintf call to stderr.
 **/
#define debug_nnl(M, ...) fprintf(stderr, "DEBUG %s:%d: " M,\
	__FILE__, __LINE__, ##__VA_ARGS__)

/**
 * Printf to stderr. Doesn't print debug info.
 * Intended to be used with debug_nnl (e.g. for adding message at the end of previous debug message)
 */
#define debug_noinfo(M, ...) fprintf(stderr, M, ##__VA_ARGS__)

#endif

/**
 * The clean_errno macro that’s used in the others to get a safe, readable version of
 * errno. 
 * 
 * The C library function char *strerror(int errnum) searches an internal array 
 * for the error number errnum and returns a pointer to an error message string. 
 * The error strings produced by strerror depend on the developing platform and compiler.
 */
#define clean_errno() (errno == 0 ? "None" : strerror(errno))

/**
 * The log_err, log_warn, and log_info, macros for logging messages that are
 * meant for the end user. They work like debug but can’t be compiled out.
 */
#define log_err(M, ...) fprintf(stderr,\
	"[ERROR] (%s:%d errno: %s) " M "\n", __FILE__, __LINE__,\
	clean_errno(), ##__VA_ARGS__)

#define log_warn(M, ...) fprintf(stderr,\
	"[WARN] (%s:%d errno: %s) " M "\n",\
	 __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define log_info(M, ...) fprintf(stderr, "[INFO] (%s:%d) " M "\n",\
	__FILE__, __LINE__, ##__VA_ARGS__)

/**
 * This will make sure the condition A is true, and if not, it
 * logs the error M (with variable arguments for log_err), and then jumps to the function’s
 * error: for cleanup
 */
#define check(A, M, ...) if(!(A)) {\
	log_err(M, ##__VA_ARGS__); errno = 0; goto error; }

/**
 * This is placed in any part of a function that
 * shouldn’t run, and if it does, it prints an error message and then jumps to the error:
 * label. You put this in if-statements and switch-statements to catch conditions that
 * shouldn’t happen, like the default:
 */
#define sentinel(M, ...) { log_err(M, ##__VA_ARGS__);\
	errno = 0; goto error; }

/**
 * A short hand macro called check_mem that makes sure a pointer is valid, and if it
 * isn’t, it reports it as an error with ”Out of memory.”
 */
#define check_mem(A) check((A), "Out of memory.");

/**
 * An alternative macro, check_debug, which still checks and handles an error, but if
 * the error is common, then it doesn’t bother reporting it. In this one, it will use debug
 * instead of log_err to report the message. So when you define NDEBUG, the check still
 * happens, and the error jump goes off, but the message isn’t printed.
 */
#define check_debug(A, M, ...) if(!(A)) { debug(M, ##__VA_ARGS__);\
	errno = 0; goto error; }

#endif
	
