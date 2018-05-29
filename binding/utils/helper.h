#ifndef CAFFE_NODEJS_UTIL_HELPER_H_
#define CAFFE_NODEJS_UTIL_HELPER_H_

#include <node_api.h>
#include <vector>
#include <string>

#define DECLARE_NAPI_PROPERTY(name, func) \
  { (name), 0, (func), 0, 0, 0, napi_default, 0 }

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

/**
* @param vec {vector<int>}: int vector
* @param result {napi_value}
**/
inline napi_value* ConverIntVectorToJsArray(napi_env env, std::vector<int>* vec, napi_value* result){
  NAPI_CALL(env, napi_create_array(env, result));
  for (std::vector<int>::size_type i = 0; i != vec->size(); i++) {
    napi_value value;
    NAPI_CALL(env, napi_create_int64(env, (*vec)[i], &value));
    NAPI_CALL(env, napi_set_element(env, *result, i, value));
  }
  return result;
}

/**
* @desc: convert JS array to Vector
* @param env {napi_env}: enviroment variable
* @param jsArray {napi_value}: javascript array
**/
inline std::vector<int>* ConvertJsArrayToVector(napi_env env, napi_value* array_value
                        , std::vector<int>* result){
  uint32_t array_length;
  NAPI_CALL(env, napi_get_array_length(env, *array_value, &array_length));
  for(uint32_t i = 0; i < array_length; i++){
    napi_value value;
    NAPI_CALL(env, napi_get_element(env, *array_value, i, &value));
    int32_t dim;
    NAPI_CALL(env, napi_get_value_int32(env, value, &dim));
    result->push_back((int)dim);
  }
  return result;
}

/**
* @desc: convert string into javascript string
* @param env {napi_env}: enviroment variable
* @param str {string}: c++ string pointer
* @param result {napi_value}: reference of javascript string
**/
inline napi_value ConvertStringToNapiString(napi_env env, std::string str, napi_value* result){
  char * shape_string_array = new char [str.length()];
  strcpy (shape_string_array, str.c_str());
  NAPI_CALL(env, napi_create_string_utf8(env, shape_string_array,str.length(), result));
  return *result;
}

#endif // CAFFE_NODEJS_UTIL_HELPER_H_

