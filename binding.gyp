{
    "targets": [
        {
            "target_name": "caffenodejs",
            "defines":[
                "CPU_ONLY=1",
                "GLOG_logostderr=1"
            ],
            "sources": [
                "binding/caffenodejs.cc",
                "binding/caffe/caffenode_blob.h",
                "binding/caffe/caffenode_blob.cc",
                "binding/utils/debug.h",
                "binding/utils/status.h"
            ],
            'include_dirs': [
               "<!@(node ./src/binding.js --include_dirs )"
            ],
            'library_dirs' : [
                "<!@(node ./src/binding.js --libraries )"
            ],
            'libraries': [
                "<!@(node ./src/binding.js --library_dirs )"
            ],
            'ldflags':[
                "<!@(node ./src/binding.js --ldflags )"
            ],
            "cflags" : [
    			"-std=c++11"
            ],
            "cflags!" : [
                "-fno-exceptions"
            ],
            "cflags_cc!": [
                #"-fno-rtti",
                "-fno-exceptions",
                '-Wno-ignored-qualifiers'
            ],
            "xcode_settings": {
                "OTHER_CFLAGS": [
                    "-std=c++11",
                    "-stdlib=libc++"
                ],
                "GCC_ENABLE_CPP_EXCEPTIONS": "YES"
            },
            "configurations": {
                "Debug": {
                    "cflags": ["--coverage"],
                    "ldflags": ["--coverage"]
                },
            }
        }
    ]
}
