const caffeNodeJsBuild = require('caffenode-js-build');
if (caffeNodeJsBuild && caffeNodeJsBuild.getLibs) {
    caffeNodeJsBuild.getLibs.forEach(lib => {
        console.log(`HAVE_${lib.module.toUpperCase()}`);
    })
}