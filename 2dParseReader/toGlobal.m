function [G] = toGlobal(LP,GP)
    mulA=zeros(3,3);
    mulB=zeros(3,3);
    mulB(3,3)=1;
    mulB(1,3)=GP(1,1);
    mulB(2,3)=GP(1,2);
    mulB(1,1)=1;
    mulB(2,2)=1;
    mulA(3,3)=1;
    theta=GP(1,3)/180*pi;
    mulA(1,1)=cos(theta);
    mulA(2,1)=sin(theta);
    mulA(1,2)=-mulA(2,1);
    mulA(2,2)=mulA(1,1);
    G=mulA\LP;
    G=mulB\G;
end

