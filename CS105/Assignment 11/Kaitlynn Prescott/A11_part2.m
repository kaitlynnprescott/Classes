fid=fopen('A11data.txt','r');
data=[];
msg=fgetl(fid);
count=1;
while msg~=-1
    loca=strfind(msg, ',');
    x=str2num(msg(2:loca-1));
    locb=strfind(msg, ')');
    y=str2num(msg(loca+1:locb-1));
    data(count,1)=x;
    data(count,2)=y;
    count=count+1;
    msg=fgetl(fid);
end
data2=sortrows(data,1);
mean=mean(data2(:,2));
std=std(data2(:,2));
plot(data2(:,1),data2(:,2),'b');
title(['Mean: ', num2str(mean), ' Std: ', num2str(std)]);
fclose(fid);