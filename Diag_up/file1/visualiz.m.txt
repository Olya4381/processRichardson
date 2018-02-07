%% основная функция
%построим график функции
x=-1:0.001:1;
y=2/pi*(x.*asin(x)+sqrt(1-x.^2));
%поворот
x1=x+y;
y1=-x+y;
%нормируем площадь

col=dlmread('col10x100_-0.420000.txt');
cx=1:length(col);
cx=cx/sqrt(sum(col));
cy=col/sqrt(sum(col));

col=dlmread('col10x100_-0.375000.txt');
cx1=1:length(col);
cx1=cx1/sqrt(sum(col));
cy1=col/sqrt(sum(col));


plot(x1,y1,cx,cy,cx1,cy1);
legend('функция','диграмма');
grid on

%% подсчет интеграла
sum1=0;
for i=2:length(y1)
    sum1=sum1+abs((x1(i)-x1(i-1))/2*(y1(i)+y1(i-1)));
end

sum1=0;
for i=2:length(s)
    sum1=sum1+abs((a(i)-a(i-1))/2*(s(i)+s(i-1)));
end
sum1

