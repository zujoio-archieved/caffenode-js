const caffeNodeJsBuild = require('caffenode-js-build');

const {
    resolvePath,
    cvIncludePath,
    cudaIncludePath,
    cuDnnIncludePath,
    ncclIncludePath,
    caffeIncludePath
} = require('./util');

// include CV 
console.log(cvIncludePath);

if (!caffeNodeJsBuild.isCPU) {
    // include CUDA
    console.log(cudaIncludePath);

    // incude CUDNN
    console.log(cuDnnIncludePath);

    // include NCCL
    console.log(ncclIncludePath);
}

// include CAFFE
console.log(caffeIncludePath);