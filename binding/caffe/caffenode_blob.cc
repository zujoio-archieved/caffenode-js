
#define CPU_ONLY 1

#include <string.h>
#include <caffe/caffe.hpp>
#include <vector>

//#include "../common.h"
#include "../utils/common.h"
#include "caffenode_blob.h"
#include "shared.h"

namespace caffenodejs {
size_t finalize_count = 0;

CaffeNode_Blob::~CaffeNode_Blob() {
  finalize_count++;
  delete blob_;
  napi_delete_reference(env_, wrapper_);
}

CaffeNode_Blob::CaffeNode_Blob(const int num, const int channels,
                               const int height, const int width) {
  blob_ = new caffe::Blob<Dtype>(num, channels, height, width);
}

void CaffeNode_Blob::Destructor(napi_env env, void *nativeObject,
                                void * /*finalize_hint*/) {
  CaffeNode_Blob *blob = static_cast<CaffeNode_Blob *>(nativeObject);
  delete blob;
}

napi_ref CaffeNode_Blob::constructor;

napi_status CaffeNode_Blob::Init(napi_env env) {
  napi_status status;
  napi_property_descriptor properties[] = {
      DECLARE_NAPI_PROPERTY("shape", shape)};

  napi_value cons;
  status =
      napi_define_class(env, "Blob", -1, New, nullptr, 1, properties, &cons);
  if (status != napi_ok) return status;

  status = napi_create_reference(env, cons, 1, &constructor);
  if (status != napi_ok) return status;

  return napi_ok;
}

/**
 * @desc: initilize blob object
 **/
napi_value CaffeNode_Blob::New(napi_env env, napi_callback_info info) {
  napi_value target;
  NAPI_CALL(env, napi_get_new_target(env, info, &target));
  bool is_constructor = (target != nullptr);

  size_t argc = 4;
  napi_value args[4];
  napi_value _this;
  NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, &_this, nullptr));

  CaffeNode_Blob *blob;

  /*if (is_constructor) {
    if (argc == 3) {
      napi_valuetype valuetype;
      NAPI_CALL(env, napi_typeof(env, args[0], &valuetype));
      assert(valuetype != napi_undefined);
      NAPI_CALL(env, napi_typeof(env, args[1], &valuetype));
      assert(valuetype != napi_undefined);
      NAPI_CALL(env, napi_typeof(env, args[2], &valuetype));
      assert(valuetype != napi_undefined);
      NAPI_CALL(env, napi_typeof(env, args[3], &valuetype));
      assert(valuetype != napi_undefined);

      int64_t  num = 0;
      int64_t channels = 0;
      int64_t height = 0;
      int64_t width = 0;
      NAPI_CALL(env, napi_get_value_int64(env, args[0], &num));
      NAPI_CALL(env, napi_get_value_int64(env, args[1], &channels));
      NAPI_CALL(env, napi_get_value_int64(env, args[2], &height));
      NAPI_CALL(env, napi_get_value_int64(env, args[3], &width));

      blob->blob_ = new caffe::Blob<Dtype>(num, channels, height, width);
    }
  }
  else{

  }*/

  if (is_constructor) {
    blob = new CaffeNode_Blob(2, 10, 2, 3);

  } else {
    napi_throw_error(env, nullptr, "Invalid Call!");
  }

  blob->env_ = env;

  NAPI_CALL(env, napi_wrap(env, _this, blob, CaffeNode_Blob::Destructor,
                           nullptr,  // finalize_hint
                           &blob->wrapper_));

  return _this;
}

napi_status CaffeNode_Blob::NewInstance(napi_env env, napi_value arg,
                                        napi_value *instance) {
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

napi_value CaffeNode_Blob::shape(napi_env env, napi_callback_info info) {
  napi_value _this;
  NAPI_CALL(env,
            napi_get_cb_info(env, info, nullptr, nullptr, &_this, nullptr));

  CaffeNode_Blob *obj;
  NAPI_CALL(env, napi_unwrap(env, _this, reinterpret_cast<void **>(&obj)));

  std::vector<int> shape = obj->blob_->shape();
  napi_value ret;
  NAPI_CALL(env, napi_create_array(env, &ret));
  for (std::vector<int>::size_type i = 0; i != shape.size(); i++) {
    napi_value shapeVal;
    NAPI_CALL(env, napi_create_int64(env, shape[i], &shapeVal));
    NAPI_CALL(env, napi_set_element(env, ret, i, shapeVal));
  }

  return ret;
}

}  // namespace caffenodejs
