%% основная функция
%построим график функции
x=-1:0.001:1;
y=2/pi*(x.*asin(x)+sqrt(1-x.^2));
%поворот
x1=x*cosd(-45)-y*sind(-45);
y1=x*sind(-45)+y*cosd(-45);
%нормируем площадь
y1=y1/0.5;

col=dlmread('col.txt');
cx=1:length(col);
cx=cx/sqrt(sum(col));
cy=col/sqrt(sum(col));

plot(x1,y1,cx,cy);
legend('функция','диаграмма');


%% подсчет интеграла
sum1=0;
for i=2:length(y1)
    sum1=sum1+abs((x1(i)-x1(i-1))/2*(y1(i)+y1(i-1)));
end
sum1

sum1=0;
for i=2:length(s)
    sum1=sum1+abs((a(i)-a(i-1))/2*(s(i)+s(i-1)));
end
sum1

%% экперимерн

x=-2:0.001:2;
y=2/pi*(x.*asin(x/2)+sqrt(4-x.^2));
plot(x,y)

%поворот
x2=x*cosd(-45)-y*sind(-45);
y2=x*sind(-45)+y*cosd(-45);
y2=y2/2;

col=dlmread('col-0.371.txt');
cx=1:length(col);
cx=cx/sqrt(sum(col));
cy=col/sqrt(sum(col));

col=dlmread('col-0.37.txt');
cx1=1:length(col);
cx1=cx1/sqrt(sum(col));
cy1=col/sqrt(sum(col));

plot(x1,y1,x2,y2,cx,cy,cx1,cy1);
legend('функция','диаграмма');


