#ifndef CAFFE_NODEJS_UTIL_H_
#define CAFFE_NODEJS_UTIL_H_

#include <node_api.h>
#include <stdio.h>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <string>

#define ARRAY_SIZE(array)           \
  {                                 \
    sizeof(array), sizeof(array[0]) \
  }

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

#define NAPI_OK(env, status)                   \
  if (NapiOk(env, status, __FILE__, __LINE__)) \
    return;
#define NAPI_OK_RETURN(env, status, ret_val)    \
  if (!NapiOk(env, status, __FILE__, __LINE__)) \
    return ret_val;
/**
   * @param {napi_env} env: napi enviroment
   * @param {napi_status} status: possbile n api status
   * @param {char*} file: name of file
   * @param {size_t} line_number: number of line
   **/
inline bool NapiOk(napi_env env, napi_status status, const char *file, const size_t lineNumber)
{
  if (status != napi_ok)
  {
    const napi_extended_error_info *err = 0;
    napi_get_last_error_info(env, &err);

    std::ostringstream string_stream;
    string_stream << "Invalid Status -> " << err->error_message;
    NAPI_THROW_ERROR(env, string_stream.str().c_str());
  }
  return status == napi_ok;
}

/**
   * @param {napi_env} env: 
   * */
inline bool IsExceptionPending(napi_env env)
{
  bool exception = false;
  NAPI_OK_RETURN(env, napi_is_exception_pending(env, &exception), exception);
  return exception;
}



#define IS_OBJECT(env, value)                    \
  if (!IsObject(env, value, __FILE__, __LINE__)) \
    return;

#define IS_OBJECT_RETURN(env, value, ret_value)  \
  if (!IsObject(env, value, __FILE__, __LINE__)) \
    return ret_value;
/**
   *@param {napi_env} env
   *@param {napi_value} value
   *@param {char*} file
   *@param {size_t} lineNumber
   **/
inline bool IsObject(napi_env env, napi_value value, const char *file, const size_t lineNumber)
{
  napi_valuetype type;
  NAPI_OK_RETURN(env, napi_typeof(env, value, &type), type);
  bool is_object = type == napi_object;
  if (!is_object)
  {
    NAPI_THROW_ERROR(env, "Invalid Argument, Object need to be specified!")
  }
  return is_object;
}





} // namespace caffenodejs

#endif // CAFFE_NODEJS_UTIL_STATUS_H_