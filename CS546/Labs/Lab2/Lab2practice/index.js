/************************************************************************************
 * Name        : index.js
 * Author      : Kaitlynn Prescott
 * Date        : Feb 2, 2017
 * Description : CS-564 Lab 2: Modules and Basic Node
 * Pledge      : I pledge my honor that I have abided by the Stevens honor system.
 ************************************************************************************/

const printShape = require("./printShape");

console.log(printShape.description);

console.log(printShape);
/*
printShape.square(2);
console.log();
printShape.square(3);
console.log();
printShape.square(4);
console.log();
printShape.square(5);
console.log();


printShape.triangle(1);
console.log();
printShape.triangle(2);
console.log();
printShape.triangle(3);
console.log();
printShape.triangle(4);
console.log();
printShape.triangle(5);
console.log();
*/

printShape.rhombus(2);
console.log();
printShape.rhombus(4);
console.log();
printShape.rhombus(6);
console.log();
printShape.rhombus(8);

