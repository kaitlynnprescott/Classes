c=input('Input positive value: ');
Xold=c;
Xnew=0;
while (true)        
    Xnew=Xold-((Xold^2-c)/(2*Xold));
    if abs(Xold-Xnew)<0.0001
        break;
    else
        Xold=Xnew;
    end
end
disp(['Estimated value of sqrt c is: ', num2str(Xnew)]);
disp(['actual value: ', num2str(sqrt(c))]);