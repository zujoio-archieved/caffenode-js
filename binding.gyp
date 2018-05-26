{
    "variables":{
        #'has_gpu': '<!(if which nvidia-smi; then echo true; else echo false; fi)'
    },
    "targets": [
        {
            "target_name": "caffenodejs",
            "defines":[
                "<!@(node ./src/defines.js)"
            ],
            "sources": [
                "binding/caffenodejs.cc",
                "binding/caffe/Blob.h",
                "binding/caffe/Blob.cc",
                "binding/utils/debug.h",
                "binding/utils/status.h"
            ],
            'include_dirs': [
                
                "<!@(node ./src/includes.js)"
            ],
            'libraries': [
                "<!(echo /home/arjunkava/Work/caffenode-js/node_modules/caffenode-js-build/caffe/caffe/build/lib/libcaffe.so)",
                 "<!(echo /home/arjunkava/Work/caffenode-js/node_modules/caffenode-js-build/caffe/caffe/build/lib/libcaffe.a)",
                 "-lboost_system"
                #"<!@(node ./src/libs.js)"
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
            "ldflags" : [
                "-Wl,-rpath,'$$ORIGIN'"
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
