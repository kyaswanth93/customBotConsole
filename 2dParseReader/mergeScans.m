globalPose=zeros(3,1);
tempPose=zeros(3,541);
scanMerged=struct('globalPose',globalPose);
N=2;
for i=1:N
    if(i==1)
        scanMerged.globalPose(:,1)=scan(i).globalPoses;
    else
        for j=1:scanMerged.length(globalPose(1))
            for k=1:541
                tempPose=scan(n).globalPoses;
                for l=1:tempPose.globalPoses(1,
    
    