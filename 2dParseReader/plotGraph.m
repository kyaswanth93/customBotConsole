scatter(scan(1).globalPoses(1,:),scan(1).globalPoses(2,:));
hold on;
for n=1:N
    scatter(scan(n).globalPoses(1,:),scan(1).globalPoses(2,:));
end