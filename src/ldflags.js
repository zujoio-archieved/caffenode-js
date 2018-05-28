const {
    resolvePath,

    cvLibPath,
    ncclLibPath,
    cudaLib,
    caffeLibPath,

    isCPU,
} = require('./util');


console.log(`-Wl,-rpath,${cvLibPath}`)
console.log(`-Wl,-rpath,${caffeLibPath}`)

