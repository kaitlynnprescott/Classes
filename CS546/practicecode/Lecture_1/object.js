let myObj = {
    hello: "World",
    num: 1,
    bool: true,
    myFn: () => {
        return "hello";
    }
};

console.log(myObj);
myObj["newkey"] = "I am a new key!";
myObj.directlyAddedKey = "I've been added!";

let keyName = "myStrKey";
myObj[keyName] = "this was made dynamically";

console.log(myObj);

myObj.hello = "Hello, World!";
console.log(myObj);

console.log(myObj.myFn());
