const fs = require('fs');

let jsonFileMod = exports = module.exports;

jsonFileMod.readJSON = (fileName, callback) => {
    return new Promise((fulfill, reject) => {
        if (!fileName) throw "No file name provided.";

        fs.readFile(fileName, "utf-8", (error, data) => {
            if (error) {
                reject(error);
                return;
            }

            try {
                let jsonData = JSON.parse(data);
                fulfill(jsonData);
            } catch (paringError) {
                reject(parsingError);
            }
        });
    })
};

jsonFileMod.writeJSON = (fileName, data, callback) => {
    return new Promise((fulfill, reject) => {
        if (!fileName) throw "No file name provided.";

        fs.writeFile(fileName, JSON.stringify(data, null, 4),(error, callback) => {
            if (error) {
                reject(error);
                return;
            }
            
            fulfill(data);
        }); 
    });
};