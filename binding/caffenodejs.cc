
#include <assert.h>
#include <node_api.h>
#include "caffe/caffenode_blob.h"
#include "utils/common.h"

namespace caffenodejs {

    /**
    * @desc: factory class for blob
    **/
    static napi_value CreateBlob(napi_env env, napi_callback_info info) {
        size_t argc;
        NAPI_CALL(env, napi_get_cb_info(env, info, &argc, nullptr, nullptr, nullptr));

        napi_value args[argc];
        NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, nullptr, nullptr));

        napi_value instance;
        NAPI_CALL(env, CaffeNode_Blob::NewInstance(env, argc, args, &instance));

        return instance;
    }


    /**
    * @desc: initialize all factories
    **/
    napi_value Init(napi_env env, napi_value exports) {
        CaffeNode_Blob::Init(env);

        napi_property_descriptor desc[] = {
                {"blob", 0, CreateBlob, 0, 0, 0, napi_default, 0}
        };

        napi_define_properties(env, exports, ARRAY_SIZE(desc), desc);

        return exports;
    }

    NAPI_MODULE(NODE_GYP_MODULE_NAME, Init);
}