#ifndef CAFFE_NODEJS_UTIL_DEBUG_H_
#define CAFFE_NODEJS_UTIL_DEBUG_H_

#include <node_api.h>
#include <stdio.h>

#define DEBUG 0

namespace caffenodejs
{

#define NAPI_THROW_ERROR(env, message) \
  ThrowError(env, message, __FILE__, __LINE__);

/**
   * @param {char*} message: message to throw bug
   * @param {char*} file: name of file
   * @param {size_t} line_number: number of line
   **/
inline void Log(const char *message, const char *file, const size_t line_number)
{
  if (DEBUG)
  {
    fprintf(stderr, "** -%s:%lu\n-- %s\n", file, line_number, message);
  }
}

/**
   * @param {napi_env} env: napi enviroment
   * @param {char*} message: message to throw bug
   * @param {char*} file: name of file
   * @param {size_t} line_number: number of line
   **/
inline void ThrowError(napi_env env, const char *message, const char *file, const size_t line_number)
{
  Log(message, file, line_number);
  napi_throw_error(env, nullptr, message);
}

} // caffenodejs
#endif // CAFFE_NODEJS_UTIL_DEBUG_H_