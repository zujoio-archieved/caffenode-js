const {
    resolvePath,

    cvLibPath,
    ncclLibPath,
    cudaLib,
    caffeLibPath,

    opencvModules,
    ncclModules,
    cudaModules,
    cuDnnModules,
    caffeModules,

    isCPU
} = require('./util');


// import CV Libs
console.log(`-L${cvLibPath}`);
opencvModules.forEach(lib => console.log(`-lopencv_${lib}`));
console.log(`-Wl,-rpath,${cvLibPath}`);

if (!isCPU) {
    //import CUDA libs 
    console.log(`-L${cudaLib}`);
    cudaModules.forEach(lib => console.log(`-l${lib}`));
    console.log(`-Wl,-rpath,${cudaLib}`);

    // import CUDNN libs
    console.log(`-L${cudaLib}`);
    cuDnnModules.forEach(lib => console.log(`-l${lib}`));
    console.log(`-Wl,-rpath,${cudaLib}`);

    // import NCCL libs
    console.log(`-L${ncclLibPath}`);
    ncclModules.forEach(lib => console.log(`-l${lib}`));
    console.log(`-Wl,-rpath,${ncclLibPath}`);
}

// import caffe libs
console.log(`-L${caffeLibPath}`);
caffeModules.forEach(lib => console.log(`-l${lib}`));
console.log(`-Wl,-rpath,${caffeLibPath}`);




