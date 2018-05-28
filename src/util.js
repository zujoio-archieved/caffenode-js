const fs = require('fs');
const path = require('path');
const caffeNodeJsBuild = require('caffenode-js-build');
/**
 * resolve absolute path to hard file system path
 * @param {string} filePath 
 * @param {string} file 
 * @returns {string}
 */
const resolvePath = (filePath, file) => {
    if (!filePath) return undefined;
    return (file ? path.resolve(filePath, file) : path.resolve(filePath)).replace(/\\/g, '/');
}

module.exports = {
    resolvePath,

    cvIncludePath: resolvePath(caffeNodeJsBuild.opencvInclude),
    cvLibPath: resolvePath(caffeNodeJsBuild.opencvLibDir),
    opencvModules: caffeNodeJsBuild.opencvModules,

    cudaIncludePath: resolvePath(caffeNodeJsBuild.cudaInclude),
    cudaPlateformIncludePath: resolvePath('/usr/local/cuda-9.1/targets/x86_64-linux/include'),
    cudaLib: resolvePath(caffeNodeJsBuild.cudaLib),
    cudnnIncludePath: resolvePath(caffeNodeJsBuild.cuDnnInclude),
    cudaModules: caffeNodeJsBuild.cudaModules,
    cuDnnModules: caffeNodeJsBuild.cuDnnModules,

    ncclIncludePath: resolvePath(caffeNodeJsBuild.ncclInclude),
    ncclLibPath: resolvePath(caffeNodeJsBuild.ncclLibDir),
    ncclModules: caffeNodeJsBuild.ncclModules,


    caffeIncludePath: resolvePath(caffeNodeJsBuild.caffeInclude),
    caffeLibPath: resolvePath(caffeNodeJsBuild.caffeLibDir),
    caffeProtoDir: resolvePath(caffeNodeJsBuild.caffeProtoDir),
    caffeBuildSrc: resolvePath(`${caffeNodeJsBuild.caffeBuild}/src`),
    caffeModules: caffeNodeJsBuild.caffeModules,

    isCPU: caffeNodeJsBuild.isCPU,

    libs: caffeNodeJsBuild.libs
}