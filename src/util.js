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

    cudaIncludePath: resolvePath(caffeNodeJsBuild.cudaInclude),
    // todo - lib path CUDA
    cudnnIncludePath: resolvePath(caffeNodeJsBuild.cuDnnInclude),
    // todo - lib path CUDNN

    ncclIncludePath: resolvePath(caffeNodeJsBuild.ncclInclude),
    ncclLibPath: resolvePath(caffeNodeJsBuild.ncclLibDir),

    protobufIncludePath: resolvePath(caffeNodeJsBuild.protobufInclude),
    prtobufLibPath: resolvePath(caffeNodeJsBuild.protobufLibDir),

    caffeIncludePath: resolvePath(caffeNodeJsBuild.caffeInclude),
    caffeLibPath: resolvePath(caffeNodeJsBuild.caffeLibDir)
}