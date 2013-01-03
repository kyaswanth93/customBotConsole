function [returnList] =splitAndMerge(masterList,thresh)
%get number of points
n=size(masterList);
n=n(2);
%setup parameters for split and merge
stop=0;
figure(1);
maxP=zeros(2,1);
dp=0;
i=1;
maxj=0;
figure(1);
%do split and merge
while(stop~=1)
    x1=masterList(1,1);
    x2=masterList(1,n);
    y1=masterList(2,1);
    y2=masterList(2,n);
    Q1=[x1;y1];
    Q2=[x2;y2];
    maxValue=-Inf;
    %find point with max distance from line Q1Q2
    for j=2:n-1
        x3=masterList(1,j);
        y3=masterList(2,j);
        P=[x3;y3];
        %calculate ditance of P from line Q1Q2
        dp=abs(det([Q2-Q1,P-Q1]))/norm(Q2-Q1);
        if(dp>maxValue)
            maxValue=dp;
            maxP=P;
            maxj=j;
        end;
    end;
    returnList=[Q1 Q2]';
    if(maxValue>thresh)
       returnList=intersect(masterList',splitAndMerge(masterList(:,1:j),thresh/2),'rows');
       returnList=union(returnList,intersect(masterList',splitAndMerge(masterList(:,j:n),thresh/2),'rows'),'rows');
    end;
    stop=stop+1;
end;