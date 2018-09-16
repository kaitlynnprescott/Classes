function myGlobalFunction()
{
    console.log("I am a global function.");
}

function printThisMessage(message)
{
    console.log("we recieved your message!");
    console.log(message);
}

let doubleup = (x) =>
{
    return x * 2;
};

let addToTheNumber = function(num)
{
    return (addThisMuch) => {
        return num + addThisMuch;
    }
};

myGlobalFunction();
printThisMessage("Hello CS546");
console.log(doubleup(16));

let addToTwelve = addToTheNumber(12);
console.log(addToTwelve);
console.log(addToTwelve(8));

function countToThisNumber(num)
{
    for (let i = 0; i < num; i++)
    {
        console.log(`the number is ${i}`);
    }
}

countToThisNumber(12);

function printSquaresUntil(num)
{
    for (let i = 0; i < num; i++)
    {
        // let allows you to define a variable within a block(if statement or loops)
        // this num is separate from the parameter num.
        // when in doubt, use let
        let num = i * i;
        console.log(`the square of ${i} is ${num}`);
    }
}

printSquaresUntil(12);