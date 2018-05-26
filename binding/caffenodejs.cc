
#include <assert.h>
#include <node_api.h>
#include "caffe/caffenode_blob.h"
#include "common.h"
namespace caffenodejs{

static napi_value CreateBlob(napi_env env, napi_callback_info info) {
  size_t argc = 1;
  napi_value args[1];
  NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, nullptr, nullptr));

  napi_value instance;
  NAPI_CALL(env, CaffeNode_Blob::NewInstance(env, args[0], &instance));

  return instance;
}


#define DECLARE_NAPI_METHOD(name, func) \
  { name, 0, func, 0, 0, 0, napi_default, 0 }

napi_value Init(napi_env env, napi_value exports) {
  CaffeNode_Blob::Init(env);

  napi_property_descriptor desc[] = {
      {"blob", 0, CreateBlob, 0, 0, 0, napi_default, 0}
      };

  napi_define_properties(env, exports, sizeof(desc) / sizeof(*desc), desc);

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
}