#ifndef CAFFE_NODEJS_UTIL_STATUS_H_
#define CAFFE_NODEJS_UTIL_STATUS_H_

#include <stdio.h>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <string>

class Debug
{
  static void Log(string message, string fileNo)
}

class Status
{
  static bool OK(napi_env env, napi_status status, const char *file, const size_t lineNumber)
  {
  }
};

class Error
{
  static void Throw(napi_env env, const char *message, const char *file, const size_t lineNumber)
  {
  }
};

#endif // CAFFE_NODEJS_UTIL_STATUS_H_