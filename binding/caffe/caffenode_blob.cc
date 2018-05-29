
#define CPU_ONLY 1

#include <string.h>
#include <caffe/caffe.hpp>
#include <vector>
#include <string>

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

CaffeNode_Blob::CaffeNode_Blob(std::vector<int> &shape) {
  blob_ = new caffe::Blob<Dtype>(shape);
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
      DECLARE_NAPI_PROPERTY("Reshape", Reshape),
      DECLARE_NAPI_PROPERTY("ReshapeLike", ReshapeLike),
      DECLARE_NAPI_PROPERTY("shape", shape),
      DECLARE_NAPI_PROPERTY("shape_string", shape_string),
      DECLARE_NAPI_PROPERTY("num_axes", num_axes),
      DECLARE_NAPI_PROPERTY("count", count),
      DECLARE_NAPI_PROPERTY("CanonicalAxisIndex", CanonicalAxisIndex),
      DECLARE_NAPI_PROPERTY("num", num),
      DECLARE_NAPI_PROPERTY("channels", channels),
      DECLARE_NAPI_PROPERTY("height", height),
      DECLARE_NAPI_PROPERTY("width", width)
  };

  napi_value cons;
  status = napi_define_class(env, "Blob", -1, New, nullptr, ARRAY_SIZE(properties), properties, &cons);
  if (status != napi_ok) return status;

  status = napi_create_reference(env, cons, 1, &constructor);
  if (status != napi_ok) return status;

  return napi_ok;
}

/**
 * @desc: initilize blob object
 **/
napi_value CaffeNode_Blob::New(napi_env env, napi_callback_info info) {
  IS_CONSTRUCTOR_RETVAL(env, info, nullptr);

  size_t argc;
  NAPI_CALL(env, napi_get_cb_info(env, info, &argc, nullptr, nullptr, nullptr));

  napi_value args[argc];
  napi_value _this;
  NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, &_this, nullptr));

  CaffeNode_Blob *blob = nullptr;

  size_t vecNumArg = 1;
  size_t channelsNumArg = 4;

  // new Blob(num, channgels, height, width)
  if(argc == channelsNumArg){
    int indexNum =0;
    int indexChannels =1;
    int indexHeight =2;
    int indexWidth =3;

    IS_NUMBER_RETVALUE(env, args[indexNum], nullptr);
    IS_NUMBER_RETVALUE(env, args[indexChannels], nullptr);
    IS_NUMBER_RETVALUE(env, args[indexHeight], nullptr);
    IS_NUMBER_RETVALUE(env, args[indexWidth], nullptr);

    int32_t num = -1;
    int32_t channels = -1;
    int32_t height = -1;
    int32_t width = -1;
    NAPI_CALL(env, napi_get_value_int32(env, args[indexNum], &num));
    NAPI_CALL(env, napi_get_value_int32(env, args[indexChannels], &channels));
    NAPI_CALL(env, napi_get_value_int32(env, args[indexHeight], &height));
    NAPI_CALL(env, napi_get_value_int32(env, args[indexWidth], &width));

    blob = new CaffeNode_Blob(num, channels, height, width);
  }
  // new Blob(shape)
  else if(argc == vecNumArg){
    napi_value array_value = args[vecNumArg - 1];
    std::vector<int> shape;
    ConvertJsArrayToVector(env, &array_value, &shape);
    blob = new CaffeNode_Blob(shape);
  }
  else 
  {
    NAPI_THROW_ERROR(env, "Invalid Arguments!");
  }

  blob->env_ = env;

  NAPI_CALL(env, napi_wrap(env, 
                          _this, 
                          blob, 
                          CaffeNode_Blob::Destructor,
                          nullptr,  // finalize_hint
                          &blob->wrapper_));
  return _this;
}

/**
* @desc: intialize new instance of Blob()
**/
napi_status CaffeNode_Blob::NewInstance(napi_env env, size_t argc, napi_value args[],
                                        napi_value *instance) {
  napi_status status;

  napi_value cons;
  status = napi_get_reference_value(env, constructor, &cons);
  if (status != napi_ok) return status;

  status = napi_new_instance(env, cons, argc, args, instance);
  if (status != napi_ok) return status;

  return napi_ok;
}

/**
* @desc: Reshape blob
**/
napi_value CaffeNode_Blob::Reshape(napi_env env, napi_callback_info info) {
  size_t argc;
  NAPI_CALL(env, napi_get_cb_info(env, info, &argc, nullptr, nullptr, nullptr));

  napi_value args[argc];
  napi_value _this;
  NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, &_this, nullptr));

  CaffeNode_Blob* blob;
  NAPI_CALL(env, napi_unwrap(env, _this, reinterpret_cast<void**>(&blob)));

  size_t vecNumArg = 1;
  size_t channelsNumArg = 4;
  // Reshape(num, channgels, height, width)
  if(argc == channelsNumArg){
    int indexNum =0;
    int indexChannels =1;
    int indexHeight =2;
    int indexWidth =3;

    IS_NUMBER_RETVALUE(env, args[indexNum], nullptr);
    IS_NUMBER_RETVALUE(env, args[indexChannels], nullptr);
    IS_NUMBER_RETVALUE(env, args[indexHeight], nullptr);
    IS_NUMBER_RETVALUE(env, args[indexWidth], nullptr);

    int32_t num = -1;
    int32_t channels = -1;
    int32_t height = -1;
    int32_t width = -1;
    NAPI_CALL(env, napi_get_value_int32(env, args[indexNum], &num));
    NAPI_CALL(env, napi_get_value_int32(env, args[indexChannels], &channels));
    NAPI_CALL(env, napi_get_value_int32(env, args[indexHeight], &height));
    NAPI_CALL(env, napi_get_value_int32(env, args[indexWidth], &width));

    blob->blob_ = new caffe::Blob<Dtype>(num, channels, height, width);
  }
  // Reshape(shape)
  else if(argc == vecNumArg){
    napi_value array_value = args[vecNumArg - 1];
    std::vector<int> shape;
    ConvertJsArrayToVector(env, &array_value, &shape);
    blob->blob_ = new caffe::Blob<Dtype>(shape);
  }
  else 
  {
    NAPI_THROW_ERROR(env, "Invalid Arguments!");
  }
  return nullptr;
}

/**
* @desc: Reshape blob from other blob
**/
napi_value CaffeNode_Blob::ReshapeLike(napi_env env, napi_callback_info info){
  size_t argc;
  NAPI_CALL(env, napi_get_cb_info(env, info, &argc, nullptr, nullptr, nullptr));

  if(argc < 1){
    NAPI_THROW_ERROR(env,"Invalid Argument!");
  }

  napi_value args[argc];
  napi_value _this;
  NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, &_this, nullptr));

  CaffeNode_Blob* blob;
  NAPI_CALL(env, napi_unwrap(env, _this, reinterpret_cast<void**>(&blob)));

  CaffeNode_Blob* other;
  NAPI_CALL(env, napi_unwrap(env, args[0], reinterpret_cast<void**>(&other)));

  blob->blob_->ReshapeLike(*other->blob_);

  return nullptr;
}

/**
* @desc: returns shape of blob
**/
napi_value CaffeNode_Blob::shape(napi_env env, napi_callback_info info) {

  size_t argc;
  NAPI_CALL(env, napi_get_cb_info(env, info, &argc, nullptr, nullptr, nullptr));

  napi_value args[argc];
  napi_value _this;
  NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, &_this, nullptr));

  CaffeNode_Blob *blob;
  NAPI_CALL(env, napi_unwrap(env, _this, reinterpret_cast<void **>(&blob)));

  const int argIndex = 1;

  // shape(index)
  if(argc == argIndex){
    int input = -1;
    ConvertNapiToInt(env, &args[0], &input);
    int valueAtIndex = blob->blob_->shape(input);
    napi_value result;
    ConvertIntToNapi(env, &valueAtIndex, &result);
    return result;
  }
  // shape()
  else{
    std::vector<int> shape = blob->blob_->shape();
    napi_value jsShape;
    ConverIntVectorToJsArray(env, &shape, &jsShape);
    return jsShape;
  }
}

/**
* @desc: return shape in string
**/
napi_value CaffeNode_Blob::shape_string(napi_env env, napi_callback_info info){
  napi_value _this;
  NAPI_CALL(env, napi_get_cb_info(env, info, nullptr, nullptr, &_this, nullptr));

  CaffeNode_Blob *blob;
  NAPI_CALL(env, napi_unwrap(env, _this, reinterpret_cast<void **>(&blob)));
  napi_value jsString;
  ConvertStringToNapiString(env, blob->blob_->shape_string(), &jsString);

  return jsString;
}

/**
* @desc: returns number of axes
**/
napi_value CaffeNode_Blob::num_axes(napi_env env, napi_callback_info info) {

  size_t argc;
  NAPI_CALL(env, napi_get_cb_info(env, info, &argc, nullptr, nullptr, nullptr));

  napi_value args[argc];
  napi_value _this;
  NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, &_this, nullptr));

  CaffeNode_Blob *blob;
  NAPI_CALL(env, napi_unwrap(env, _this, reinterpret_cast<void **>(&blob)));

  int numAxes = blob->blob_->num_axes(); 
  napi_value result;
  ConvertIntToNapi(env, &numAxes, &result);
  return result;
}

/**
* @desc: returns volume of specified axes
**/
napi_value CaffeNode_Blob::count(napi_env env, napi_callback_info info) {

  size_t argc;
  NAPI_CALL(env, napi_get_cb_info(env, info, &argc, nullptr, nullptr, nullptr));

  napi_value args[argc];
  napi_value _this;
  NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, &_this, nullptr));

  CaffeNode_Blob *blob;
  NAPI_CALL(env, napi_unwrap(env, _this, reinterpret_cast<void **>(&blob)));

  const int argStart = 1;
  const int argStartEnd = 2;

  // count(start_axis)
  if(argc == argStart){
    int start_axis = -1;
    ConvertNapiToInt(env, &args[argStart - 1], &start_axis);
    int volume = blob->blob_->count(start_axis);
    napi_value result;
    ConvertIntToNapi(env, &volume, &result);
    return result;
  }
  // count(start_axis, end_axis)
  else if(argc == argStartEnd){
    int start_axis = -1;
    ConvertNapiToInt(env, &args[argStart -1], &start_axis);
    int end_axis = -1;
    ConvertNapiToInt(env, &args[argStartEnd -1], &end_axis);
    int volume = blob->blob_->count(start_axis, end_axis);
    napi_value result;
    ConvertIntToNapi(env, &volume, &result);
    return result;
  }
  // count()
  else{
    int volume = blob->blob_->count();
    napi_value result;
    ConvertIntToNapi(env, &volume, &result);
    return result;
  }
}

/**
* @desc: returns
**/
napi_value CaffeNode_Blob::CanonicalAxisIndex(napi_env env, napi_callback_info info){
  size_t argc;
  NAPI_CALL(env, napi_get_cb_info(env, info, &argc, nullptr, nullptr, nullptr));

  napi_value args[argc];
  napi_value _this;
  NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, &_this, nullptr));

  CaffeNode_Blob *blob;
  NAPI_CALL(env, napi_unwrap(env, _this, reinterpret_cast<void **>(&blob)));

  const int argAxisIndex = 1;

  // count(start_axis)
  if(argc == argAxisIndex){
    int start_axis = -1;
    ConvertNapiToInt(env, &args[argAxisIndex - 1], &start_axis);
    int canonical = blob->blob_->CanonicalAxisIndex(start_axis);
    napi_value result;
    ConvertIntToNapi(env, &canonical, &result);
    return result;
  }
  else{
    NAPI_THROW_ERROR(env, "Invalid Arguments!");
    return nullptr;
  }
}

/**
* @desc: returns num of shape
**/
napi_value CaffeNode_Blob::num(napi_env env, napi_callback_info info){
  size_t argc;
  NAPI_CALL(env, napi_get_cb_info(env, info, &argc, nullptr, nullptr, nullptr));

  napi_value args[argc];
  napi_value _this;
  NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, &_this, nullptr));

  CaffeNode_Blob *blob;
  NAPI_CALL(env, napi_unwrap(env, _this, reinterpret_cast<void **>(&blob)));

  int num = blob->blob_->num();
  napi_value result;
  ConvertIntToNapi(env, &num, &result);
  return result;
}

/**
* @desc: returns channels of shape
**/
napi_value CaffeNode_Blob::channels(napi_env env, napi_callback_info info){
  size_t argc;
  NAPI_CALL(env, napi_get_cb_info(env, info, &argc, nullptr, nullptr, nullptr));

  napi_value args[argc];
  napi_value _this;
  NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, &_this, nullptr));

  CaffeNode_Blob *blob;
  NAPI_CALL(env, napi_unwrap(env, _this, reinterpret_cast<void **>(&blob)));

  int channels = blob->blob_->channels();
  napi_value result;
  ConvertIntToNapi(env, &channels, &result);
  return result;
}
/**
* @desc: returns height of shape
**/
napi_value CaffeNode_Blob::height(napi_env env, napi_callback_info info){
  size_t argc;
  NAPI_CALL(env, napi_get_cb_info(env, info, &argc, nullptr, nullptr, nullptr));

  napi_value args[argc];
  napi_value _this;
  NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, &_this, nullptr));

  CaffeNode_Blob *blob;
  NAPI_CALL(env, napi_unwrap(env, _this, reinterpret_cast<void **>(&blob)));

  int height = blob->blob_->height();
  napi_value result;
  ConvertIntToNapi(env, &height, &result);
  return result;
}
/**
* @desc: returns height of shape
**/
napi_value CaffeNode_Blob::width(napi_env env, napi_callback_info info){
  size_t argc;
  NAPI_CALL(env, napi_get_cb_info(env, info, &argc, nullptr, nullptr, nullptr));

  napi_value args[argc];
  napi_value _this;
  NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, &_this, nullptr));

  CaffeNode_Blob *blob;
  NAPI_CALL(env, napi_unwrap(env, _this, reinterpret_cast<void **>(&blob)));

  int width = blob->blob_->width();
  napi_value result;
  ConvertIntToNapi(env, &width, &result);
  return result;
}

}  // namespace caffenodejs
