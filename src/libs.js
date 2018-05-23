const caffeNodeJsBuild = require('caffenode-js-build');

const {
    resolvePath,
    cvLibPath,
    ncclLibPath,
    prtobufLibPath,
    caffeLibPath
} = require('./util');

// import CV Libs
console.log(`-L${cvLibPath}`);
caffeNodeJsBuild.opencvModules.forEach(lib => console.log(`-lopencv_${lib}`));
console.log(`-Wl,-rpath,${cvLibPath}`);

if (!caffeNodeJsBuild.isCPU) {
    // todo: import CUDA libs 

    // todo: import CUDNN libs
}

// import NCCL libs
console.log(`-L${ncclLibPath}`);
caffeNodeJsBuild.ncclModules.forEach(lib => console.log(`-l${lib}`));
console.log(`-Wl,-rpath,${ncclLibPath}`);

// import protobuf libs
console.log(`-L${prtobufLibPath}`);
caffeNodeJsBuild.protobufModules.forEach(lib => console.log(`-l${lib}`));
console.log(`-Wl,-rpath,${prtobufLibPath}`);

// import caffe libs
console.log(`-L${caffeLibPath}`);
caffeNodeJsBuild.caffeModules.forEach(lib => console.log(`-l${lib}`));
console.log(`-Wl,-rpath,${caffeLibPath}`);




