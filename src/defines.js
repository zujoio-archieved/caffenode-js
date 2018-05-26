const caffeNodeJsBuild = require('caffenode-js-build');

// fetch all needed libraries and set as DEFINES
if (caffeNodeJsBuild && caffeNodeJsBuild.libs) {
    caffeNodeJsBuild.libs.forEach(lib => {
        console.log(`HAVE_${lib.module.toUpperCase()} `);
    })
}

if(caffeNodeJsBuild.isCPU){
    //console.log("CPU_ONLY 1")
}