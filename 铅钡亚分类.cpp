group1=[
47.43	0.00
59.91	0.34
63.07	0.07
40.00	0.84
48.17	0.62
32.85	1.14
55.37	0.58
61.78	0.32
65.37	0.06
49.51	0.69
48.09	0.77
56.55	0.63
52.44	0.75
59.10	0.56
68.25	0.38
76.90	0.22
53.88	0.34
67.14	0.18
48.01	0.45
40.28	0.71
58.20	0.31
49.18	0.50
51.34	0.42
56.06	0.46
62.50	0.36
58.46	0.29
40.87	1.20
56.70	0.51
62.40	0.41
47.01	0.65
];
group2=[
28.84	1.87
38.55	1.31
21.18	3.21
14.34	4.41
32.35	1.58
31	1.66
18.83	3.23
27.21	2.01
36.83	1.22
22.65	2.81
];
x=[group1;group2];
data=[group1,-1*ones(30,1);group2,1*ones(10,1)];
y=data(:,end);
h=[];
for i=1:length(x)
for j=1:length(x)
h(i,j)=x(i,:)*(x(j,:))'*y(i)*y(j);
end
end
f=-1*ones(length(x),1);
aeq=y';
beq=zeros(1,1);
ub=[];
ib=[];
lb=zeros(length(x),1);
ub=[];
[a,fval]=quadprog(h,f,ib,ub,aeq,beq,lb,ub);%二次规划问题

for i=1:length(a)
if a(i)<1e-05
a(i)=0;
end
end
w=0;
u = 0;
ff = find(a~=0);
j = ff(1);
for i=1:length(x)
w=w+a(i)*y(i)*x(i,:)';
u=u+a(i)*y(i)*(x(i,:)*x(j,:)');
end
b=y(j)-u;
predict=[];
for i=1:length(x)
uu=0;
for j=1:length(x)
uu=uu+a(j)*y(j)*(x(j,:)*x(i,:)');
end
result=sign(uu+b);
predict(i,1)=result;
end
judge=(predict==y);
score=sum(judge)./length(data);
%画出点以及对应的超平面
scatter(group1(:,1),group1(:,2),'red');
hold on
scatter(group2(:,1),group2(:,2),'blue');
hold on
k=-w(1)./w(2);%将直线改写成斜截式便于作图
bb=-b./w(2);
xx=0:80;
yy=k.*xx+bb;
plot(xx,yy,'-')
hold on
yy=k.*xx+bb+1./w(2);
plot(xx,yy,'--')
hold on
yy=k.*xx+bb-1./w(2);
plot(xx,yy,'--')
title('support vector machine')
xlabel('dimension1')
ylabel('dimension2')
legend('group1','group2','separating hyperplane')
