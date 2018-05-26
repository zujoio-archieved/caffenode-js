#include "Blob.h"
#include "../common.h"
#include <node_api.h>
#include <vector>
#include <assert.h>

namespace caffenodejs {
size_t finalize_count = 0;

Blob::Blob(): env_(nullptr), wrapper_(nullptr) {}

Blob::~Blob() {
  finalize_count++;
  napi_delete_reference(env_, wrapper_);
}

void Blob::Destructor(
  napi_env env, void* nativeObject, void* /*finalize_hint*/) {
  Blob* obj = static_cast<Blob*>(nativeObject);
  delete obj;
}

napi_ref Blob::constructor;

napi_status Blob::Init(napi_env env) {
  napi_status status;

  napi_value cons;
  status = napi_define_class(
      env, "Blob", -1, New, nullptr, 0, nullptr, &cons);
  if (status != napi_ok) return status;

  status = napi_create_reference(env, cons, 1, &constructor);
  if (status != napi_ok) return status;

  return napi_ok;
}

napi_value Blob::New(napi_env env, napi_callback_info info) {
  size_t argc = 1;
  napi_value args[1];
  napi_value _this;
  NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, &_this, nullptr));

  Blob* obj = new Blob();

  napi_valuetype valuetype;
  NAPI_CALL(env, napi_typeof(env, args[0], &valuetype));

  if (valuetype == napi_undefined) {
    obj->val_ = 0;
  } else {
    NAPI_CALL(env, napi_get_value_double(env, args[0], &obj->val_));
  }

  obj->env_ = env;

  // It is important that the below call to napi_wrap() be such that we request
  // a reference to the wrapped object via the out-parameter, because this
  // ensures that we test the code path that deals with a reference that is
  // destroyed from its own finalizer.
  NAPI_CALL(env, napi_wrap(env,
                          _this,
                          obj,
                          Blob::Destructor,
                          nullptr,  // finalize_hint
                          &obj->wrapper_));

  return _this;
}

napi_status Blob::NewInstance(napi_env env,
                                  napi_value arg,
                                  napi_value* instance) {
  napi_status status;

  const int argc = 1;
  napi_value argv[argc] = {arg};

  napi_value cons;
  status = napi_get_reference_value(env, constructor, &cons);
  if (status != napi_ok) return status;

  status = napi_new_instance(env, cons, argc, argv, instance);
  if (status != napi_ok) return status;

  return napi_ok;
}
}
