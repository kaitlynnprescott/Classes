let trueVar = true;
let falseVar = false;
let nullVar = null;
let undefinedVar = undefined;
let zeroVar = 0;
let oneVar = 1;

if (trueVar)
{
    console.log("true is true, it checks out.");
} else {
    console.log("true is not true... this is weird");
}

if (falseVar)
{
    console.log("false is true, no idea why");
}
else{
    console.log("false is false... this is good");
}

if (nullVar)
{
    console.log("nullVar evaluates to true");
}
else 
{
    console.log("nullVar evaluates to false");
}

if (undefinedVar)
{
    console.log("undefinedVar evaluates to true");
}
else 
{
    console.log("undefinedVar evaluates to false");
}

if (zeroVar)
{
    console.log("zeroVar evaluates to true");
}
else 
{
    console.log("zeroVar evaluates to false");
}

if (oneVar)
{
    console.log("oneVar evaluates to true");
}
else 
{
    console.log("oneVar evaluates to false");
}

if (undefinedVar == nullVar)
{
    console.log("undefinedVar == nullVar");
}
else
{
    console.log("undefinedVar != nullVar");
}

if (undefinedVar === nullVar)
{
    console.log("undefinedVar === nullVar");
}
else
{
    console.log("undefinedVar !== nullVar");
}

if (undefinedVar == zeroVar)
{
    console.log("undefinedVar == zeroVar");
}
else
{
    console.log("undefinedVar != zeroVar");
}

if (undefinedVar === zeroVar)
{
    console.log("undefinedVar === zeroVar");
}
else
{
    console.log("undefinedVar !== zeroVar");
}

if ("0" == zeroVar)
{
    console.log("zero the string is equal to 0 the number");
}
else
{
    console.log("they are not equal");
}

if ("0" === zeroVar)
{
    console.log("zero the string is equal to 0 the number");
}
else
{
    console.log("they are not equal");
}