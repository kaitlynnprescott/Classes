/************************************************************************************
 * Name        : fileData.js
 * Author      : Kaitlynn Prescott
 * Date        : Feb 9, 2017
 * Description : CS-564 Lab 3: Asynchronous Code, Files, and Promises
 * Pledge      : I pledge my honor that I have abided by the Stevens honor system.
 ************************************************************************************/

// what are my requirements?
const fs = require('fs');

let fileData = exports = module.exports;

fileData.getFileAsString = (path) => {
    /* 
     * This method will, when given a path, return a promise that resolves to 
     * a JavaScript object. You can use the JSON.parse function to convert 
     * a string to a JavaScript object (if it's valid!).
     */
    return new Promise((fulfill, reject) => {
        // If no path is provided, it will return a rejected promise.
        if (!path) reject("No path provided.");
        // If there are any errors reading the file or parsing the file, the returned 
        // promise will reject rather than resolve, passing the error to the 
        // rejection callback.
        fs.readFile(path, "utf-8", (error, data) => {
            // If there are any errors reading the file, the returned promise will 
            // reject rather than resolve, passing the error to the rejection callback.
            if (error) {
                // something went wrong! Yikes...
                reject(error);
                return;
            }
            fulfill(data);
        });
    });
};

fileData.getFileAsJSON = (path) => {
    /* 
     * This method will, when given a path, return a promise that resolves 
     * to a string with the contents of the files.
     */
    return new Promise((fulfill, reject) => {
        // If no path is provided, it will return a rejected promise.
        if (!path) reject("No path provided.");
        fs.readFile(path, "utf-8", (error, data) => {
            // If there are any errors reading the file, the returned promise will 
            // reject rather than resolve, passing the error to the rejection callback.
            if (error) {
                // something went wrong! Yikes...
                reject(error);
                return;
            }
            try {
                let jsonData = JSON.parse(data);
                fulfill(jsonData);
            } catch (parsingError) {
                reject(parsingError);
            }
        });
    })
};

fileData.saveStringToFile = (path, text) => {
    /* 
     * This method will take the text supplied, and store it in the file specified 
     * by path. The function should return a promise that will resolve to 
     *  true when saving is completed.
     */
    // I got a promise to keep
    return new Promise((fulfill, reject) => {
       // If no path or text is provided, it will return a rejected promise.
       if (!path) reject("No path provided.");
       // If there are any errors writing the file, the returned promise will reject 
       // rather than resolve, passing the error to the rejection callback.
       fs.writeFile(path, text, (error, data) => {
            if (error) {
                // something went wrong! Yikes...
                reject(error);
                return;
            }
            fulfill(true);
        });
    });
};

fileData.saveJSONToFile = (path, obj) => {
    /* 
     * This method will take the obj supplied and convert it into a string so that 
     * it may stored as in a file. The function should return a promise that 
     *  will resolve to true when saving is completed.
     */ 
    // I got a promise to keep
    return new Promise((fulfill, reject) => {
        // If no path or obj is provided, it will return a rejected promise.
        if (!path) reject("No path provided.");
        // If there are any errors writing the file, the returned promise will reject 
        // rather than resolve, passing the error to the rejection callback.
        fs.writeFile(path, JSON.stringify(obj, null, 4), (error, data) => {
            if (error) {
                // something went wrong! Yikes...
                reject(error);
                return;
            }
            fulfill(true);
        });
    });
};