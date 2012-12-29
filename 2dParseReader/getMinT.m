min=Inf;
max=-Inf;
N=1055;
for i=1:N
    if(scan(i).globalPose(1,3)>max)
        max=scan(i).globalPose(1,3);
    end
    if(min>scan(i).globalPose(1,3))
        min=scan(i).globalPose(1,3);
    end
end
max;
min;