#ifndef CAFFE_NODEJS_UTIL_HELPER_H_
#define CAFFE_NODEJS_UTIL_HELPER_H_

#include <node_api.h>
#include <vector>
#include <string>

#define DECLARE_NAPI_PROPERTY(name, func) \
  { (name), 0, (func), 0, 0, 0, napi_default, 0 }

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))



#endif // CAFFE_NODEJS_UTIL_HELPER_H_

