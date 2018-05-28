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

    isCPU,
    libs
} = require('./util');

// import caffe libs
console.log(`-L${caffeLibPath}`);
console.log(`-L${cvLibPath}`);
caffeModules.forEach(lib => console.log(`-l${lib}`));
//console.log(`-Wl,-rpath,${caffeLibPath}`);

// import CV Libs
//console.log(`-L${cvLibPath}`);
opencvModules.forEach(lib => console.log(`-lopencv_${lib}`));
//console.log(`-Wl,-rpath,${cvLibPath}`);

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


/*libs.forEach(lib => {
    console.log(lib.path);
})*/



