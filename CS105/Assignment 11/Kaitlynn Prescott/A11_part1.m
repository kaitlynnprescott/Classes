file = input('Enter the filename: ', 's');
fid=fopen(file, 'a');
linenum=1;
x=input('Enter a line or type Goodbye to quit: ','s');
while true
    if strcmp(x,'Goodbye')
        break;
    else 
       fprintf(fid, '%d:%s\n', linenum, x);
       linenum=linenum+1;
       x=input('Enter a line or type Goodbye to quit: ','s');
    end
end
fclose(fid);