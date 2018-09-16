/************************************************************************************
 * Name        : app.js
 * Author      : Kaitlynn Prescott
 * Date        : Feb 9, 2017
 * Description : CS-564 Lab 3: Asynchronous Code, Files, and Promises
 * Pledge      : I pledge my honor that I have abided by the Stevens honor system.
 ************************************************************************************/

// what are my requirements? 
const fileData = require("./fileData");
const textMetrics = require("./textMetrics");
const fs = require('fs');

// ugh... it's time to start... 
console.log("start of code");

// check if chapter1.result.json exists
fs.access('chapter1.result.json', fs.constants.R_OK | fs.constants.W_OK, (err) => {
    // file does not exist
    if (err) {  
        let result1 = fileData.getFileAsString("chapter1.txt");
        result1.then((stringReadings) => {
            // simplify the file and save it.
            var debug = textMetrics.simplify(stringReadings);
            fileData.saveStringToFile("chapter1.debug.txt", debug).then((data) => {
                 // successfully saves the string
                if (data) {
                    console.log("Done writing results as simple text");
                    // get the metrics of the file and save it to a json file
                    var results = "chapter1.result.json";
                    var resultMetrics = textMetrics.createMetrics(stringReadings);
                    fileData.saveJSONToFile("chapter1.result.json", resultMetrics).then((data) => {
                        if (data) {
                            // successfully saves it to json file and prints results.
                            console.log("Done writing json results");
                            console.log(JSON.stringify(resultMetrics, null, 4));
                        }
                    });
                }
            });
            // not successful 
        }).catch((error) => {
            // something went wrong! Yikes...
            console.log(error);
        });
        // file exists
    } else {    
        let JSONresult1 = fileData.getFileAsJSON("chapter1.result.json");        
        JSONresult1.then((jsonObj) => {
            // successfully finds the file, and returns it as a string.
            console.log("Reading json results");
            console.log(JSON.stringify(jsonObj, null, 4));
        }).catch((error) => {
            // unsuccessful parse
            // something went wrong! Yikes...
            console.error("There was an error parsing the json file");
            console.error(error);
        });
    }
});

// check if chapter2.result.json exists
fs.access('chapter2.result.json', fs.constants.R_OK | fs.constants.W_OK, (err) => {
    // file does not exist
    if (err) {  
        // get the file
        let result2 = fileData.getFileAsString("chapter2.txt");
        result2.then((stringReadings) => {
            // simplify the file and save it.
            var debug = textMetrics.simplify(stringReadings);
            fileData.saveStringToFile("chapter2.debug.txt", debug).then((data) => {
                // successfully saves the string
                if (data) {
                    console.log("Done writing results as simple text");
                    // get the metrics of the file and save it to a json file
                    var results = "chapter2.result.json";
                    var resultMetrics = textMetrics.createMetrics(stringReadings);
                    fileData.saveJSONToFile("chapter2.result.json", resultMetrics).then((data) => {
                        if (data) {
                            // successfully saves it to json file and prints results.
                            console.log("Done writing json results");
                            console.log(JSON.stringify(resultMetrics, null, 4));
                        }
                    });
                }
            });
            // not successful 
        }).catch((error) => {
            // something went wrong! Yikes...
            console.log(error);
        });
        // file exists
    } else {    
        // get the json file that already exists 
        let JSONresult2 = fileData.getFileAsJSON("chapter2.result.json");        
        JSONresult2.then((jsonObj) => {
            // successfully finds the file, and returns it as a string.
            console.log("Reading json results");
            console.log(JSON.stringify(jsonObj, null, 4));
        }).catch((error) => {
            // unsuccessful parse
            // something went wrong! Yikes...
            console.error("There was an error parsing the json file");
            console.error(error);
        });
    }
});

// check if chapter3.result.json exists 
fs.access('chapter3.result.json', fs.constants.R_OK | fs.constants.W_OK, (err) => {
    // file does not exist
    if (err) {  
        // get the file
        let result3 = fileData.getFileAsString("chapter3.txt");
        result3.then((stringReadings) => {
            // simplify the file and save it.
            var debug = textMetrics.simplify(stringReadings);
            fileData.saveStringToFile("chapter3.debug.txt", debug).then((data) => {
                // successfully saves the string
                if (data) {
                    console.log("Done writing results as simple text");
                    // get the metrics of the file and save it to a json file 
                    var results = "chapter3.result.json";
                    var resultMetrics = textMetrics.createMetrics(stringReadings);
                    fileData.saveJSONToFile("chapter3.result.json", resultMetrics).then((data) => {
                        if (data) {
                            // successfully saves it to json file and prints results.
                            console.log("Done writing json results");
                            console.log(JSON.stringify(resultMetrics, null, 4));
                        }
                    });
                }
            });
            // not successful 
        }).catch((error) => {
            // something went wrong! Yikes...
            console.log(error);
        });
        // file exists
    } else {
        // get the json file that already exists 
        let JSONresult3 = fileData.getFileAsJSON("chapter3.result.json");        
        JSONresult3.then((jsonObj) => {
            // successfully finds the file, and returns it as a string.
            console.log("Reading json results");
            console.log(JSON.stringify(jsonObj, null, 4));
        }).catch((error) => {
            // unsuccessful parse
            // something went wrong! Yikes...
            console.error("There was an error parsing the json file");
            console.error(error);
        });
    }
});
// finally! we done!
console.log("end of file.");