/************************************************************************************
 * Name        : textMetrics.js
 * Author      : Kaitlynn Prescott
 * Date        : Feb 9, 2017
 * Description : CS-564 Lab 3: Asynchronous Code, Files, and Promises
 * Pledge      : I pledge my honor that I have abided by the Stevens honor system.
 ************************************************************************************/


module.exports = {
    description: "Module to simplify strings and create text metrics.",
    simplify: function (text) {
        // check that input
        if (!text) {
            throw "No input was given."
        }
        var result = "";
        try {
            // convert text to lowercase:
            result = text.toLowerCase();
            // remove non-alphanumeric characters and 
            //convert white space to simple spaces
            var nonAlphaNum = /[^a-z0-9\s]/g;
            var spaces = /[\n\t\s]+/g;
            result = result.replace(nonAlphaNum, '');
            result = result.replace(spaces, ' ');
            // return the result
            return result;
        } catch (error) {
            // something went wrong! Yikes...
            console.error(error);
        }
    },

    createMetrics: function (text) {
        // check that input
        if (!text) {
            throw "No input was given.";
        }
        // simplify text
        var result = module.exports.simplify(text);
        // what is a letter...
        var eachLetter = /[a-z0-9]/g;
        // what is a word...
        var eachWord = /(\w+)/g;
        // get total number of letters
        var totalLetters = result.match(eachLetter).length;
        // get total number of words
        var totalWords = result.match(eachWord).length;
        var words = result.split(/\s/);
        // how many unique words are there?
        var uniqueWords = 0;
        // how many long words are there?
        var longWords = 0;
        // how long is a normal word?
        var averageWordLength = 0;

        // all the words...
        var wordOccurrences = {};
        words.forEach(function(w) {
            if (!wordOccurrences[w]) {
                wordOccurrences[w] = 0;
            }
            wordOccurrences[w] += 1;
        });
        
        // how many unique words can there be?
        for (var key in wordOccurrences) {
            if (wordOccurrences[key] === 1) {
                uniqueWords++;
            }
        }

        // how many UNIQUE long words can there be?
        for (var key in wordOccurrences) {
            if (key.length >= 6 && wordOccurrences[key] === 1) {
                longWords++;
            }
        }
        // So...  what's the average?
        averageWordLength = totalLetters / totalWords;

        // save me! :)
        var jsonObject = new Object();
        jsonObject.fileName = text[0]+text[1]+text[2]+text[3]+text[4]+text[5]+text[6]+text[7]+text[8];
        jsonObject.totalLetters = totalLetters;
        jsonObject.totalWords = totalWords;
        jsonObject.uniqueWords = uniqueWords;
        jsonObject.longWords = longWords;
        jsonObject.averageWordLength = averageWordLength;
        jsonObject.wordOccurrences = wordOccurrences;
        return jsonObject;

    }
};