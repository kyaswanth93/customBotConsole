hold off;
N=50;
hold on;
for i=1:N
    figure(1);
    scatter(scan(i).globalPoses(1,:),scan(i).globalPoses(2,:));
    hold on;
end;
view(70,90);
for i=1:N
    figure(2);
    plot(scan(i).globalPoses(1,:),scan(i).globalPoses(2,:));
    hold on;
end;
view(70,90);