/************************************************************************************
 * Name        : index.js
 * Author      : Kaitlynn Prescott
 * Date        : Feb 2, 2017
 * Description : CS-564 Lab 2: Modules and Basic Node
 * Pledge      : I pledge my honor that I have abided by the Stevens honor system.
 ************************************************************************************/
const printShape = require("./printShape");
//const prompt = require("prompt");

// print out 10 of each shape.
for (var num = 1; num <= 10; num++) {
    // print out the triangle of size num
    printShape.triangle(num);
    console.log();
    // print out the square of size num+1 (accounting for minimum size of 2)
    printShape.square(num+1);
    console.log();
    // print out the rhombus of size num*2 (accounting for even size)
    printShape.rhombus(num*2);
    console.log();
}