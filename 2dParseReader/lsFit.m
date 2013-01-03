function [lsResult] = lsFit(scan,n1,n2)
timeDone=scan(n2).time-scan(n1).time;
xTolerance=round(timeDone*(scan(n1).velo(1,1)+scan(n2).velo(1,1)));
yTolerance=xTolerance;
thetaTolerance=(timeDone*(scan(n1).velo(1,2)+scan(n2).velo(1,2)));
xB=scan(n2).globalPoses(:,:);
x=scan(n1).robotPose(1,1);
y=scan(n1).robotPose(1,2);
a=scan(n1).robotPose(1,3);
txC=eye(3,3);
minVal=Inf;
lsT=0;
lsX=0;
lsY=0;
for t=-thetaTolerance:thetaTolerance
    theta=(t+a)*pi/180;
    tC=[cos(theta),-sin(theta),0;sin(theta),cos(theta),0;0,0,1];
    for i=-xTolerance:xTolerance
        for j=-yTolerance:yTolerance
            txC(1,3)=i+x;
            txC(2,3)=j+y;
            xC=tC\scan(25).localPoses(:,:);
            xC=txC\xC;
            lsQ=0;
            for k=1:541
                for l=1:541
                    lsQ=lsQ+((xB(1,k)-xC(1,l))^2)+((xB(2,k)-xC(2,l))^2);
                end;
            end;
            if(lsQ<minVal)
                minVal=lsQ;
                xLS=xC;
                lsT=t;
                lsX=i;
                lsY=j;
            end;
        end;
    end;
end;
scatter(xB(1,:),xB(2,:));
hold on;
scatter(xLS(1,:),xLS(2,:));
lsResult=[minVal,lsX,lsY,lsT];
end