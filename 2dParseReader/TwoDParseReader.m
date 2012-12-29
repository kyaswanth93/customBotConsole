c=1;
globalP=zeros(1,3);
localP=zeros(2,541);
globalPs=zeros(3,541);
mulA=zeros(3,3);
mulB=zeros(3,3);
onesM=ones(541,1);
tempPose=zeros(3,1);
originX=0;
originY=0;
originT=0;
scan=struct('count',c,'globalPose',globalP,'localPose',localP,'globalPoses',globalPs);
filename = 'df.2dparse';
fid = fopen(filename);
N=1055;
for n = 1:N
    scan(n).count = fscanf(fid, '\nScan %d', 1);
    scan(n).globalPose = fscanf(fid, '%f',[1,3]);
    localP = fscanf(fid, '%f', [2,541]);
    scan(n).localPose=localP';
    scan(n).localPose(:,3:3)=onesM;
    scan(n).localPose=scan(n).localPose';
    for m=1:541
        mulB(3,3)=1;
        mulB(1,3)=scan(n).globalPose(1,1);
        mulB(2,3)=scan(n).globalPose(1,2);
        mulB(1,1)=1;
        mulB(2,2)=1;
        mulA(3,3)=1;
        theta=scan(n).globalPose(1,3)/180*pi;
        mulA(1,1)=cos(theta);
        mulA(2,1)=sin(theta);
        mulA(1,2)=-mulA(2,1);
        mulA(2,2)=mulA(1,1);
        tempPose=mulA\scan(n).localPose(:,m);
        tempPose=mulB\tempPose;
        scan(n).globalPoses(:,m)=tempPose;
    end
end
fclose(fid);
plotGraph;