data=input('Enter Comma Separated Values: ','s');
sum=0;
[token,remainder]=strtok(data, ',');
while ~isempty(remainder)
    tok=str2num(token);
    if ~isempty(tok)
        sum=sum+tok;
    end
    [token,remainder]=strtok(remainder, ',');
end
disp(['The sum is: ', num2str(sum)]);