function A = A10_part2_dice(x)
if x>=0 && x<1/6
    A=1;
elseif x>=1/6 && x<2/6
    A=2;
elseif x>=2/6 && x<3/6
    A=3;
elseif x>=3/6 && x<4/6
    A=4;
elseif x>=4/6 && x<5/6
    A=5;
else 
    A=6;
end
end
