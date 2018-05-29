#ifndef CAFFE_NODEJS_UTIL_VALIDATE_H_
#define CAFFE_NODEJS_UTIL_VALIDATE_H_

#include <node_api.h>
#include "status.h"


#define IS_CONSTRUCTOR(env, info) \
  if (!IsConstructor(env, info, __FILE__, __LINE__)) return true;

#define IS_CONSTRUCTOR_RETVAL(env, info, retval) \
  if (!IsConstructor(env, info, __FILE__, __LINE__)) return retval;

/**
 * @desc: validate valid call of constructor
 **/
inline bool IsConstructor(napi_env env, napi_callback_info info,
                          const char* file, const size_t lineNumber) {
  napi_value target;
  NAPI_CALL(env, napi_get_new_target(env, info, &target));
  bool is_target = target != nullptr;
  if (!is_target) {
      NAPI_THROW_ERROR(env, "Invalid Constructor Call!")
  }
  return is_target;
}

#define IS_NUMBER(env, value) \
    if(!IsNum(env, value, __FILE__, __LINE__)) return;

#define IS_NUMBER_RETVALUE(env, value, retvalue) \
    if(!IsNum(env, value, __FILE__, __LINE__)) return retvalue;

/**
 * @desc: validate valid number
 ***/
inline bool IsNum(napi_env env, napi_value value,
                                const char* file, const size_t lineNumber){
  napi_valuetype type;
  NAPI_CALL(env, napi_typeof(env, value, &type));
  bool is_number = type == napi_number;
  if(!is_number){
    NAPI_THROW_ERROR(env, "Invalid Number!");
  }
  return is_number;
}

#endif  // CAFFE_NODEJS_UTIL_VALIDATE_H_