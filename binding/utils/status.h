#ifndef CAFFE_NODEJS_UTIL_DEBUG_H_
#define CAFFE_NODEJS_UTIL_DEBUG_H_

#include <node_api.h>
#include <stdio.h>


#define DEBUG 1

#define NAPI_THROW_ERROR(env, message) \
  ThrowError(env, message, __FILE__, __LINE__);

#define NAPI_CALL_BASE(env, the_call, ret_val)         \
  do {                                                 \
    if ((the_call) != napi_ok) {                       \
      GetAndThrowLastError((env), __FILE__, __LINE__); \
      return ret_val;                                  \
    }                                                  \
  } while (0)

#define NAPI_CALL(env, the_call) NAPI_CALL_BASE(env, the_call, NULL)
/**
 * @param {char*} message: message to throw bug
 * @param {char*} file: name of file
 * @param {size_t} line_number: number of line
 **/
inline void Log(const char *message, const char *file,
                const size_t line_number) {
  if (DEBUG) {
    fprintf(stderr, "** -%s:%lu\n-- %s\n", file, line_number, message);
  }
}
/**
 * @param {napi_env} env: napi enviroment
 * @param {char*} message: message to throw bug
 * @param {char*} file: name of file
 * @param {size_t} line_number: number of line
 **/
inline void ThrowError(napi_env env, const char *message, const char *file,
                       const size_t line_number) {
  Log(message, file, line_number);
  napi_throw_error(env, nullptr, message);
}
/**
 * get last thrown error and rethrow
 **/
inline void GetAndThrowLastError(napi_env env, const char *file,
                                 const size_t line_number) {
  const napi_extended_error_info *error_info;
  napi_get_last_error_info((env), &error_info);
  bool is_pending;        
  napi_is_exception_pending((env), &is_pending);
  /* If an exception is already pending, don't rethrow it */
  if (!is_pending) {
    const char *error_message = error_info->error_message != NULL
                                    ? error_info->error_message
                                    : "empty error message";
    ThrowError(env, error_message, file, line_number);
  }
}



#endif  // CAFFE_NODEJS_UTIL_DEBUG_H_