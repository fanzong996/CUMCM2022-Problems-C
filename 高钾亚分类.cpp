%支持向量机support vector machine%软间隔soft margin
group1=[
0.92	96.77
0.59	95.02
1.01	94.29
0	92.72
0	92.63
0.74	92.35
5.19	87.05
9.42	79.46
0	76.68
];
group2=[
9.99	69.33
7.37	67.65
9.67	65.88
14.52	65.18
12.28	62.47
12.37	61.71
10.95	61.58
7.68	59.81
12.53	59.01
];
x=[group1;group2];
data=[group1,-1*ones(9,1);group2,1*ones(9,1)];%数据与对应标签
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
[a,fval]=quadprog(h,f,ib,ub,aeq,beq,lb,ub);

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
k=-w(1)./w(2);
bb=-b./w(2);
xx=0:15;
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
legend('group1','group2','separating hyperplane')%分类1，分类2，分离超平面的图例
