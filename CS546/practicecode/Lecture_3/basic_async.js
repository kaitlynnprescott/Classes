/*
 * asynchronous code means code is not printing out as it is run / written
*/

console.log("This is synchronous.");
let x = 25;


for (let i = 0; i < 10; i++) {
    console.log("loop is running");
    process.nextTick(() => {
        console.log(`i is ${i}`);
    });
}

console.log(x / 12);

console.log(`x / 2 is ${x / 2}`);


for (let i = 0; i < 1000; i++) {
    console.log("loop is running");
    console.log(`i is ${i}`);
}
console.log("==========");