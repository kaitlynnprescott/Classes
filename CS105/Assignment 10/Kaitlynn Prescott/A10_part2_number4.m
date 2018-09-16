function A=A10_part2_number4(a,mode)
msg=nargchk(1,2,nargin);
if nargin<2
    mode='up';
end
if strcmp(mode,'up')
    for ii=1:length(a)-1
        iptr=ii;
        for jj=ii+1:length(a)
            if a(jj)<a(iptr)
                iptr=jj;
            end
        end
        if ii~=iptr
            temp=a(ii);
            a(ii)=a(iptr);
            a(iptr)=temp;
        end
    end
end
if strcmp(mode,'down')
   for ii=1:length(a)-1
        iptr=ii;
        for jj=ii+1:length(a)
            if a(jj)>a(iptr)
                iptr=jj;
            end
        end
        if ii~=iptr
            temp=a(ii);
            a(ii)=a(iptr);
            a(iptr)=temp;
        end
    end
end 
A=a;
