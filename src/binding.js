const caffeNodeJsBuild = require('caffenode-js-build');

const includeDirs = [
    '/usr/local/opt/openblas/include',
    caffeNodeJsBuild.caffeSrc+'/src',
    caffeNodeJsBuild.caffeInclude,
    caffeNodeJsBuild.caffeProtoDir,
    caffeNodeJsBuild.opencvInclude,
    (caffeNodeJsBuild.isCPU ? '' :caffeNodeJsBuild.cudaInclude)
]
/**
 * console needed include directories
 */
const getIncludeDirs = () => {
    includeDirs.forEach(include => console.log(include));
}

/**
 * console needed ldflags
 */
const getLibraries = () => {
    caffeNodeJsBuild.libs.forEach(lib => console.log(`-l${lib}`));
}

const libDirs = [
    caffeNodeJsBuild.opencvLibDir,
    caffeNodeJsBuild.caffeLibDir,
    (caffeNodeJsBuild.isCPU ? '' : caffeNodeJsBuild.cudaLib),
    (caffeNodeJsBuild.isCPU ? '' : caffeNodeJsBuild.cudaLib64)
]
/**
 * console needed lib directories
 */
const getLibDirs = () => {
    libDirs.forEach(dir => console.log(dir));
}
/**
 * console needed ldflags
 */
const getCflags = () => {
    libDirs.forEach(dir => console.log(`-Wl, -rpath,${dir}`));
}

// extract process arguments 
const argIndex = 2;
//console.log("process.argv", process.argv.length)
const isArg = process.argv && process.argv.length == (argIndex + 1) && process.argv[argIndex];
if (isArg) {
    //console.log("process.argv[argIndex]", process.argv[argIndex])
    switch (process.argv[argIndex]) {
        case '--include_dirs':
            getIncludeDirs();
            break;
        case '--libraries':
            getLibraries();
            break;
        case '--library_dirs':
            getLibDirs();
            break;
        case '--ldflags':
            getCflags();
            break;
    }
}

