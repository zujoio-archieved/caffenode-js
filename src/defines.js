const caffeNodeJsBuild = require('caffenode-js-build');

// fetch all needed libraries and set as DEFINES
if (caffeNodeJsBuild && caffeNodeJsBuild.getLibs) {
    caffeNodeJsBuild.libs.forEach(lib => {
        console.log(`HAVE_${lib.module.toUpperCase()} `);
    })
}