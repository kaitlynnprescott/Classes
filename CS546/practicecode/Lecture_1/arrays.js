let myStringArray = ["hello", "world", "my", "name", "is", "katie"];
let myNumArray = [1, 2, 3, 4, 5];

myStringArray.forEach((value) => {
    console.log(value);
});

let myNumArraySquared = myNumArray.map((x) => {
    return x * x;
});

console.log(myNumArray);
console.log(myNumArraySquared);


var oddNumbers = myNumArray.filter((num) => {
    return num % 2 === 1;
});

console.log(oddNumbers);
console.log(myNumArray);

var sumOfOdds = oddNumbers.reduce((currentTotal, newValue) => {
    return currentTotal + newValue;
}, 0);

console.log(sumOfOdds);

myNumArray.push(6);
console.log(myNumArray.join(" "));
