{
    "variables":{
        'default_lib_dir':'/usr/bin/x86_64-linux-gnu-ld',
        'cv_lib_dir': '/home/arjunkava/Work/caffenode-js/node_modules/caffenode-js-build/opencv/build/lib',
        'caffe_lib_dir': '/home/arjunkava/Work/caffenode-js/node_modules/caffenode-js-build/caffe/caffe/build/lib',
        'cv_include':'/home/arjunkava/Work/caffenode-js/node_modules/caffenode-js-build/opencv/build/include',
        'cv_src_include':'/home/arjunkava/Work/caffenode-js/node_modules/caffenode-js-build/caffe/caffe/build/src',
        'caffe_include':'/home/arjunkava/Work/caffenode-js/node_modules/caffenode-js-build/caffe/caffe/include',
        'caffe_proto_include':'/home/arjunkava/Work/caffenode-js/node_modules/caffenode-js-build/caffe/caffe/src/caffe/proto'
    },
    "targets": [
        {
            "target_name": "caffenodejs",
            "sources": [
                "binding/caffenodejs.cc",
                "binding/caffe/caffenode_blob.h",
                "binding/caffe/caffenode_blob.cc",
                "binding/utils/debug.h",
                "binding/utils/status.h"
            ],
            'include_dirs': [
               '<(cv_include)',
               '<(cv_src_include)',
               '<(caffe_include)',
               '<(caffe_proto_include)',
            ],
            'libraries': [
                '-lopencv_core',
                '-lopencv_highgui',
                '-lopencv_imgcodecs',
                '-lopencv_imgproc',
                '-lopencv_features2d',
                '-lopencv_calib3d',
                '-lopencv_photo',
                '-lopencv_objdetect',
                '-lopencv_ml',
                '-lopencv_video',
                '-lopencv_videoio',
                '-lopencv_videostab',
                '-lopencv_dnn',
                '-lopencv_face',
                '-lopencv_text',
                '-lopencv_tracking',
                '-lopencv_xfeatures2d',
                '-lopencv_ximgproc',
                '-lboost_system',
                '-lprotobuf',
                '<@(caffe_lib_dir)/libcaffe.a',
            ],
            'library_dirs' : [
                '<(default_lib_dir)',
                '<(caffe_lib_dir)',
                '<(cv_lib_dir)'
            ],
            "cflags" : [
    			"-std=c++11"
            ],
            "cflags!" : [
                "-fno-exceptions"
            ],
            "cflags_cc!": [
                "-fno-rtti",
                "-fno-exceptions",
                '-Wno-ignored-qualifiers'
            ],
            "configurations": {
                "Debug": {
                    "cflags": ["--coverage"],
                    "ldflags": ["--coverage"]
                },
            }
        }
    ]
}
