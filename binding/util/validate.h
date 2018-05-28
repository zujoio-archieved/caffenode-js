#ifndef CAFFE_NODEJS_UTIL_VALIDATE_H_
#define CAFFE_NODEJS_UTIL_VALIDATE_H_

#include <node_api.h>
#include <stdio.h>
#include "debug.h"
#include "status.h"

namespace caffenodejs {

#define IS_OBJECT(env, value) \
  if (!IsObject(env, value, __FILE__, __LINE__)) return;

#define IS_OBJECT_RETURN(env, value, ret_value) \
  if (!IsObject(env, value, __FILE__, __LINE__)) return ret_value;

/**
 *@param {napi_env} env
 *@param {napi_value} value
 *@param {char*} file
 *@param {size_t} lineNumber
 **/
inline bool IsObject(napi_env env, napi_value value, const char* file,
                     const size_t lineNumber) {
  napi_valuetype type;
  NAPI_OK_RETURN(env, napi_typeof(env, value, &type), type);
  bool is_object = type == napi_object;
  if (!is_object) {
    NAPI_THROW_ERROR(env, "Invalid Argument, Object need to be specified!")
  }
  return is_object;
}

#define IS_CONSTRUCTOR_CALL(env, info) \
  if (!isConstructorCall(env, info, __FILE__, __LINE__)) return;
#define IS_CONSTRUCTOR_CALL_RETVAL(env, info, retval) \
  if (!isConstructorCall(env, info, __FILE__, __LINE__)) return retval;

/**
 *@param {napi_env} env
 *@param {napi_callback_info} info
 *@param {char*} file
 *@param {size_t} file
 **/
inline bool isConstructorCall(napi_env env, napi_callback_info info,
                                  const char* file, const size_t line_number) {
  napi_value js_target;
  napi_status nstatus = napi_get_new_target(env, info, &js_target);
  NAPI_OK_RETURN(env, nstatus, false);
  bool is_target = js_target != nullptr;
  if (!is_target) {
    NAPI_THROW_ERROR(env, "Invalid Call, Function can not be used as constructor!!");
  }
  return is_target;
}

}  // namespace caffenodejs
#endif  // CAFFE_NODEJS_UTIL_VALIDATE_H_