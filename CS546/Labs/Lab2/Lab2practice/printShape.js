/************************************************************************************
 * Name        : printShape.js
 * Author      : Kaitlynn Prescott
 * Date        : Feb 2, 2017
 * Description : CS-564 Lab 2: Modules and Basic Node
 * Pledge      : I pledge my honor that I have abided by the Stevens honor system.
 ************************************************************************************/

module.exports = {
    description: "Print Shapes of certain sizes.",
    triangle: function (lines) {
        // /\
        if (typeof lines !== "number") {
            throw "Error: Input must be a number.";
        } else if (lines < 1) {
            throw "Error: Number of lines must be greater than 0.";
        } else {
            for (var i = 1; i <= lines; i++) {
                let spaces = "";
                for (var j = 0; j < lines - i; j++) {
                    spaces += " ";
                }
                let edge = "";
                for (var e = 0; e < ((i - 1) * 2); e++) {
                    edge += "-";
                }
                let inside = "";
                for (var k = 1; k <= ((i - 1) * 2); k++) {
                    inside += " ";
                }
                if ((i === lines) && (i > 1)) {
                    console.log(`/${edge}\\`);
                } else if (i === 1) {
                    console.log(`${spaces}/\\`);
                } else {
                    console.log(`${spaces}/${inside}\\`);
                }
            }
        }
    },

    square: function (lines) {
        if (typeof lines !== "number") {
            throw "Error: Input must be a number.";
        } else if (lines < 0) {
            throw "Error: Number of lines must be greater than 0.";
        } else {
            var edge = "|";
            var space = "|";
            for (var i = 0; i < lines; i++) {
                edge += "-";
                space += " ";
            }
            edge += "|";
            space += "|";

            // top edge
            console.log(`${edge}`);

            // middle
            for (var i = 1; i < lines-1; i++) {
                console.log(`${space}`); 
            }

            // bottom edge 
            console.log(`${edge}`);
        }
            
    },

    rhombus: function (lines) {
       if (typeof lines !== "number") {
           throw "Error: Input must be a number.";
       } else if (lines < 0) {
            throw "Error: Number of lines must be greater than 0.";
        } else if (lines%2 !== 0) {
            // return error message
            throw "Error: Number of lines must be even.";
        } else if (lines === 2) {
            console.log(`/-\\`);
            console.log(`\\-/`);
        } else {
            for (var i = 1; i <= lines/2; i++) {
                let spaces = "";
                for (var j = 0; j < lines/2 - i; j++) {
                    spaces += " ";
                }
                let inside = "";
                for (var k = 1; k <= ((i - 1) * 2); k++) {
                    inside += " ";
                }
                if (i === lines/2) {
                    console.log(`/${inside} \\`);
                } else if (i === 1) {
                    console.log(`${spaces}/-\\`);
                } else {
                    console.log(`${spaces}/${inside} \\`);
                }
            }
            for (var m = lines/2; m >= 1; m--) {
                let spaces2 = "";
                 for (var n = 0; n < lines/2 - m; n++) {
                     spaces2 += " ";
                 }
                 let inside2 = "";
                 for (var p = 1; p <= ((m - 1) * 2); p++) {
                     inside2 += " ";
                 }
                 if (m === lines/2) {
                     console.log(`\\${inside2} /`);
                 } else if (m === 1) {
                     console.log(`${spaces2}\\-/`);
                 } else {
                     console.log(`${spaces2}\\${inside2} /`);
                 }
            }
        }
    }
};

//todo: 
// what is a promise?
