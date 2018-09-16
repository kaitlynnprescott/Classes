startVal = input('Enter the starting value: ','s');  %submit as a string
startValNum = str2num(startVal);    %try to convert string to a number

if isempty(startValNum)     %test if conversion failed (resulting in empty vector)
    disp('Starting value must be a number');
else
    endVal = input('Enter the ending value: ', 's');  %submit ending value as a string
    endValNum = str2num(endVal);  %try converting to number
    if isempty(endValNum)   %failed converting
        disp('Ending value must be a number');
    elseif endValNum <= startValNum
        disp('Ending value must be greater than starting value');
    else
        stepVal = input('Enter the step value: ', 's');
        stepValNum = str2num(stepVal);
        if isempty(stepValNum)
            disp('Step must be a number');
        elseif stepValNum <= 0
            disp('Step must be a positive number');
        else
            x = startValNum: stepValNum: endValNum;
            y = x.^2;
            plot(x,y);
        end
    end
end
