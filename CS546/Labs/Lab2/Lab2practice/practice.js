function triangle(lines){
    if(typeof lines != 'number')
        throw "Error: Input should be of type number.";
    if(lines < 1)
        throw "Error: Input should be a number greater than zero.";
    for(var i = 1; i <= lines; i++){//i is the current line you are on
        let space = 0;
        for(var j = 0; j < lines - i; j++){//j is the spaces on each line
            space++;
        }
        if((i == lines)&&(i > 1)){//if you are at the base of the triangle
            console.log("/%s\\", "-".repeat((i - 1) * 2));
        } else if(i == 1){//if you are at the top of the triangle 
            console.log("%s/%s\\", " ".repeat(space), " ".repeat(0));
        } else{//if you are at the space in between
            console.log("%s/%s\\", " ".repeat(space), " ".repeat((i - 1) * 2));
        }
    }
}


triangle(1);
triangle(2);
triangle(3);
triangle(4); 



 function square(lines){
    if(typeof lines != 'number')
        throw "Error: Input should be of type number.";
    if(lines < 2)
        throw "Error: Input should be a minimum of 2.";
    if(lines >= 2){
        for(var i = 1; i <= lines; i++){
            if((i == 1) || ( i == lines)){
                console.log("|%s|", "-".repeat(lines));
            }else{
                console.log("|%s|", " ".repeat(lines));
            }
        }
    }else{
        throw "Error: Input should be of at least 2.";
    }
 }
 
 square(2);
 square(3);
 square(4);
 
 
 

 function rhombus(lines){
    if(typeof lines != 'number')
        throw "Error: Input should be of type number."; 
    if(lines < 2)
        throw "Error: Input should be a minimum of 2.";
    if((lines % 2) != 0)
        throw "Error: Input should be an even number."
    var half = (lines/2);
    for(var i = 1; i <= lines; i++){//i is the line you are currently on
        var space1 = 1;
        var inside1 = half;
        for(var j = 0; j < half - i; j++){//j is the /\ spaces on each line
            space1++;
            inside1--;
        }
        var space2 = half;
        var inside2 = 0;
        for(var k = 0; k < lines - i; k++){//k is the \/ spaces on each line
            space2--;
            inside2++;
        }
        if(i == 1){
            console.log("%s/%s\\", " ".repeat(space1), "-".repeat(1));
        } else if (i == lines){
            console.log("%s\\%s/", " ".repeat(space2), "-".repeat(1));
        } else{ 
            if(i > half){
                console.log("%s\\%s/", " ".repeat(space2), " ".repeat((k * 2) + 1));
            } else{
                console.log("%s/%s\\", " ".repeat(space1), " ".repeat((i * 2) - 1));
            }
        }
    }
 }
 
rhombus(2);
rhombus(4);
rhombus(6);
rhombus(8);