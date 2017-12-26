std=dlmread('alpha_10x100.txt');
std1=dlmread('alpha_10x100_1.txt');
plot(std(:,1),std(:,2),std1(:,1),std1(:,2));
title('График СКР для n=(10k x 100)');