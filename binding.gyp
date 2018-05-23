{
    "variables":{
        #'has_gpu': '<!(if which nvidia-smi; then echo true; else echo false; fi)'
    },
    "targets": [
        {
            "target_name": "caffenodejs",
            "defines":[
                #"<!@(node ./src/defines.js)"
            ],
            "sources": [
                "binding/caffenodejs.cc",
                "binding/common.h"
            ],
            'include_dirs': [
                #"<!@(node ./src/includes.js)"
            ],
            'libraries': [
                #"<!@(node ./src/libs.js)"
            ],
            "cflags" : [
    			#"-std=c++11"
            ],
            "cflags!" : [
                #"-fno-exceptions"
            ],
            "cflags_cc!": [
                #"-fno-rtti",
                #"-fno-exceptions",
                #'-Wno-ignored-qualifiers'
            ],
            "ldflags" : [
                #"-Wl,-rpath,'$$ORIGIN'"
            ],
            "configurations": {
                #"Debug": {
                #    "cflags": ["--coverage"],
                #    "ldflags": ["--coverage"]
                #},
            }
        }
    ]
}
