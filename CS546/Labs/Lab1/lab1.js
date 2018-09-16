/************************************************************************************
 * Name        : lab1.js
 * Author      : Kaitlynn Prescott
 * Date        : Jan 22, 2017
 * Description : CS-564 Lab 1: An Intro to Node
 * Pledge      :I pledge my honor that I have abided by the Stevens honor system.
 ************************************************************************************/

// error function
function UserException(message) {
   this.message = message;
   this.name = "UserException";
}

// sum of squares
function sumOfSquares(num1, num2, num3) {
    /* 
     * For your first function, you will calculate the 
     * sum of the squares of 3 numbers and return that result.
     */
    // error check:
    if (isNaN(num1) || isNaN(num2) || isNaN(num3)) {
        throw new UserException("Input must be numbers.");
    } else {
        // find the squares of num1, num2, and num3
        let num1s = num1 * num1;
        let num2s = num2 * num2;
        let num3s = num3 * num3;
        // add the squares together
        return num1s + num2s + num3s;
    }
}

// test sumOfSquares:
console.log(sumOfSquares(5, 3, 10));
console.log(sumOfSquares(3, 6, 9));
console.log(sumOfSquares(10, 15, 18));
console.log(sumOfSquares(2, 4, 6));
console.log();

// say hello to
function sayHelloTo(firstName, lastName, title) {
    /* 
     * For the second function, you will make a simple function 
     * that uses console.log to print hello to someone!
     * The interesting thing about this function is that you 
     * don't have to have all the inputs to run.
     */

    // error check:
    if (!firstName) {
        // throw and error when no name is given.
        throw new UserException("No Name!");
    } else {
        // we're good!
        if (title) {
            // if there is a title, return full name with title at front
            console.log(`Hello, ${title} ${firstName} ${lastName}`);
            console.log();
        } else {
            // if there is no name:
            if (lastName) {
                // if there is a last name, print first and last name
                console.log(`Hello, ${firstName} ${lastName}`);
                console.log();
            } else {
                // if there is only a first name, print first name
                console.log(`Hello, ${firstName}`);
                console.log();
            }
        }
    }
}

// test sayHelloTo:
//console.log(sayHelloTo());
console.log(sayHelloTo("Phil"));
console.log(sayHelloTo("Phil", "Barresi"));
console.log(sayHelloTo("Phil", "Barresi", "Mr."));
console.log();


// cups of coffee
function cupsOfCoffee(howManyCups) {
    /* 
     * For the third function, you will create and return a 
     * simple song called 99 Cups of Coffee on the Desk. 
     * The lyrics of this song grow longer depending on 
     * how many cups of coffee there are on the desk.
     */

    // error check:
    if (isNaN(howManyCups)) {
        throw new UserException("Input must be a number!");
    } else if (howManyCups < 0) {
        throw new UserException("Input must be positive!");
    } else {
        for (let i = howManyCups; i > 1; i--) {
            if (i == 2) {
                // for grammar purposes, if i is 2, ommit s in cups on second line
                console.log(`${i} cups of coffee on the desk! ${i} cups of Coffee!`);
                console.log(`Pick one up, drink the cup, ${i - 1} cup of coffee on the desk!`);
                // add a line break
                console.log();
            } else {
                // print out song lyrics with appropriate numbers
                console.log(`${i} cups of coffee on the desk! ${i} of Coffee!`);
                console.log(`Pick one up, drink the cup, ${i - 1} cups of coffee on the desk!`);
                // add a line break
                console.log();
            }
        }
        console.log("1 cup of coffee on the desk! 1 cup of coffee!");
        return "Pick it up, drink the cup, no more coffee left on the desk!";
    }
}

// test cupsOfCoffee:
console.log(cupsOfCoffee(5));
console.log();

// occurrences of substring
function occurrencesOfSubstring(fullString, subString) {
    /* 
     * For the fourth function, you will calculate how 
     * many times a substring occurs in a given string.
     * However, you must also factor in a case where there are overlaps!
     */

    // error check: 
    if (!isNaN(fullString) || !isNaN(subString)) {
        throw new UserException("Input must be strings!");
    } else {
        if (subString.length <= 0) {
            return fullString.length + 1;
        }
        let n = 0, pos = 0, step = 1;
        while (true) {
            pos = fullString.indexOf(subString, pos);
            if (pos >= 0) {
                ++n; 
                pos += step;
            } else {
                break;
            }
        }
        return n;
    }
}

// test occurrencesOfSubstring:
console.log(occurrencesOfSubstring("hello world!", "o"));
console.log(occurrencesOfSubstring("Helllllllo, class!", "ll"));

// randomize sentences
function randomizeSentences(paragraph) {
    /* 
     * For your final function, you will take in a paragraph 
     * and randomize the sentences in it. This one is tricky! 
     * You'll have to work with string manipulation, and 
     * probably an array or two as well.
     */

    // error check:
    if (!isNaN(paragraph)) {
        throw new UserException("Input can't be a number.");
    } else {
        // use match instead of split to keep deliminator and maintatin integrity of sentence
        var arr_paragraph = paragraph.match(/[^\.!\?]+[\.!\?]+/g);
        var currIndex = arr_paragraph.length, tempVal, randInd;
        // while there are still elements available
        while (0 !== currIndex) {
            // get a remaining element
            randInd = Math.floor(Math.random() * currIndex);
            currIndex -= 1;
            // swap it with current element
            tempVal = arr_paragraph[currIndex];
            arr_paragraph[currIndex] = arr_paragraph[randInd];
            arr_paragraph[randInd] = tempVal;
        }
       console.log(arr_paragraph.join("")); 
       console.log();
    }
}

// test randomizeSentences:
var paragraph = "Hello, world! I am a paragraph. Can you tell that I am a paragraph? You can tell that I am a paragraph because there are multiple sentences that are split up by punctuation marks. Grammar can be funny, so I will only put in paragraphs with periods, exclamation points, and question marks -- no quotations.";
console.log(randomizeSentences(paragraph));
console.log(randomizeSentences(paragraph));
console.log(randomizeSentences(paragraph));
console.log(randomizeSentences(paragraph));
