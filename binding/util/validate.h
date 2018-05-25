#ifndef CAFFE_NODEJS_UTIL_VALIDATE_H_
#define CAFFE_NODEJS_UTIL_VALIDATE_H_

#include <node_api.h>
#include <stdio.h>

namespace caffenodejs{

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
} // caffenodejs
#endif // CAFFE_NODEJS_UTIL_VALIDATE_H_