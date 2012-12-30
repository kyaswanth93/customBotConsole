globalXY=zeros(1,2);
globalXY2=scan(1).globalPoses(1:2,:)';
N=1055;
figure(1);
for i=1:N
    globalXY=union(globalXY,scan(i).globalPoses(1:2,:)','rows');
    scatter(globalXY(:,1),globalXY(:,2));
end;
figure(2);
for i=1:N
    globalXY2=intersect(globalXY2,scan(i).globalPoses(1:2,:)','rows');
    scatter(globalXY2(:,1),globalXY2(:,2));
end;