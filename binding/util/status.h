#ifndef CAFFE_NODEJS_UTIL_STATUS_H_
#define CAFFE_NODEJS_UTIL_STATUS_H_

#include <node_api.h>
#include <sstream>

namespace caffenodejs{

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
} // cafenoidejs

#endif // CAFFE_NODEJS_UTIL_STATUS_H_