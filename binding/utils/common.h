#ifndef CAFFE_NODEJS_UTIL_H_
#define CAFFE_NODEJS_UTIL_H_

#include "debug.h"

#define DECLARE_NAPI_PROPERTY(name, func) \
  { (name), 0, (func), 0, 0, 0, napi_default, 0 }

#endif // CAFFE_NODEJS_UTIL_H_