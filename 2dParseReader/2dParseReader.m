c=1;
globalP=zeros(1,3);
localP=zeros(2,541);
globalPs=zeros(3,541);
mulM=zeros(3,3);
onesM=ones(541,1);
scan=struct('count',c,'globalPose',globalP,'localPose',localP,'globalPoses',globalPs,'mul',mulM);
scan;
filename = 'df.2dparse';
fid = fopen(filename);
N=1055;
for n = 1:N
    scan(n).count = fscanf(fid, '\nScan %d\n\n', 1);
    scan(n).globalPose = fscanf(fid, '%f',[1,3]);
    localP = fscanf(fid, '%f', [2,541]);
    scan(n).localPose=localP';
    scan(n).localPose(:,3:3)=onesM;
    scan(n).localPose=scan(n).localPose';
    for m=1:541
        mulM(3,3)=1;
        mulM(1,3)=scan(n).globalPose(1,1);
        mulM(2,3)=scan(n).globalPose(1,2);
        degree=scan(n).globalPose(1,3)/pi*180;
        alphaDeg=(degree+((m-271)/2));
        alpha=alphaDeg/180*pi;
        mulM(1,1)=cos(alpha);
        mulM(1,2)=sin(alpha);
        mulM(2,1)=-sin(alpha);
        mulM(2,2)=cos(alpha);
        if(m>1)
            scan(n).mul(:,(1+((m-1)*3)):(m*3))=mulM;
        else
            scan(n).mul=mulM;
        end
        scan(n).globalPoses(:,m)=mulM*scan(n).localPose(:,m);
    end
end
fclose(fid);