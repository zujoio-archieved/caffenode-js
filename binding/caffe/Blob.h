#ifndef CAFFE_NODEJS_BLOB_H_
#define CAFFE_NODEJS_BLOB_H_

#define CPU_ONLY 1

#include <node_api.h>
#include <caffe/caffe.hpp>
#include <string>
#include <vector>

#include "shared.h"

namespace caffenodejs {

    class Blob {
    public:
        static napi_status Init(napi_env env);
        static void Destructor(napi_env env, void* nativeObject, void* finalize_hint);
        static napi_status NewInstance(napi_env env,
                                        napi_value arg,
                                        napi_value* instance);
        double Val() const { return val_; }

    private:
        Blob();
        ~Blob();

        static napi_ref constructor;
        static napi_value New(napi_env env, napi_callback_info info);
        double val_;
        caffe::Blob<Dtype>* blob_;
        napi_env env_;
        napi_ref wrapper_;
    };
}  // caffenodejs

#endif  // CAFFE_NODEJS_BLOB_H_
