{
    "variables":{
        #'has_gpu': '<!(if which nvidia-smi; then echo true; else echo false; fi)'
        'cv_lib_dir': '/home/arjunkava/Work/caffenode-js/node_modules/caffenode-js-build/opencv/build/lib',
        'caffe_lib_dir': '/home/arjunkava/Work/caffenode-js/node_modules/caffenode-js-build/caffe/caffe/build/lib'
    },
    "targets": [
        {
            "target_name": "caffenodejs",
            "defines":[
                "<!@(node ./src/defines.js)"
            ],
            "sources": [
                "binding/caffenodejs.cc",
                "binding/caffe/caffenode_blob.h",
                "binding/caffe/caffenode_blob.cc",
                "binding/utils/debug.h",
                "binding/utils/status.h"
            ],
            'include_dirs': [
                "<!@(node ./src/includes.js)"
            ],
            'libraries': [
                "<!@(node ./src/libs.js)",
                 "-lboost_system"
            ],
            "ldflags" : [
                "<!@(node ./src/ldflags.js)",
            ],
            #'library_dirs':[
            #    "<!@(node ./src/lib_dir.js)",
            #],
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
