warning off
clc
clear all;
close all;
b=[];
p=[
36.28	20.14	4.61	33.59	29.64	37.36	31.94	19.79	3.72	34.34	36.93	65.91	69.71	75.51	35.78	65.91	39.57	60.12	32.93	26.25	16.71	18.46	12.41	21.7	61.28	55.21	51.54	53.33	28.79	17.98	24.61	21.35	25.74	22.28	17.11	49.01	29.15	25.42	30.39
47.43	59.91	63.07	40	48.17	32.85	55.37	61.78	65.37	49.51	48.09	19.97	24.64	19.71	56.55	27.73	52.44	27.58	59.1	68.25	76.9	53.88	67.14	48.01	26.95	35.31	34.63	23.02	40.28	58.2	49.18	51.34	56.06	62.5	58.46	40.87	56.7	62.4	47.01
];
t=[1.05	0	0	0.21	0	0.71	0	0	0.4	1.41	0	0	0.21	0.15	0.25	0	0.14	0.23	0	0	0	0.44	0	0	0.11	0.25	0.29	0.32	0	0	0	0	0	0.32	0	0	0	0	0.34

];
for i = 1:100
[p1,ps]=mapminmax(p);
[t1,ts]=mapminmax(t);
[trainsample.p,valsample.p,testsample.p] =dividerand(p,0.7,0.15,0.15);
[trainsample.t,valsample.t,testsample.t] =dividerand(t,0.7,0.15,0.15);
TF1='tansig';TF2='purelin';
net=newff(minmax(p),[10,1],{TF1 TF2},'traingdm');%matlab版本差异可能导致此处有警告
net.trainParam.epochs=10000;
net.trainParam.goal=1e-7;
net.trainParam.lr=0.001;
net.trainParam.mc=0.6;
net.trainParam.show=50;
net.trainFcn='trainlm';
[net,tr]=train(net,trainsample.p,trainsample.t);
[normtrainoutput,trainPerf]=sim(net,trainsample.p,[],[],trainsample.t);
[normvalidateoutput,validatePerf]=sim(net,valsample.p,[],[],valsample.t);
[normtestoutput,testPerf]=sim(net,testsample.p,[],[],testsample.t);
trainoutput=mapminmax('reverse',normtrainoutput,ts);
validateoutput=mapminmax('reverse',normvalidateoutput,ts);
testoutput=mapminmax('reverse',normtestoutput,ts);
trainvalue=mapminmax('reverse',trainsample.t,ts);
validatevalue=mapminmax('reverse',valsample.t,ts);
testvalue=mapminmax('reverse',testsample.t,ts);
errors=trainvalue-trainoutput;
%plotregression拟合图
%figure,plotregression(trainvalue,trainoutput)
R = corrcoef(trainvalue,trainoutput);
M = R(1,2);
i=0;
i=i+1;
b=[b;M];
end
disp(b)

Q4:高钾类化学成分关联分析
文件：Q4Ka BP
warning off
clc
clear all;
close all;
b=[];
p=[
96.77 	95.02 	94.29 	92.72 	92.63 	92.35 	87.05 	79.46 	76.68 	69.33 	67.65 	65.88 	65.18 	62.47 	61.71 	61.58 	59.81 	59.01
0.92 	0.59 	1.01 	0.00 	0.00 	0.74 	5.19 	9.42 	0.00 	9.99 	7.37 	9.67 	14.52 	12.28 	12.37 	10.95 	7.68 	12.53
];
t=[0.00 	0.00 	0.00 	0.00 	0.00 	0.00 	0.00 	0.00 	0.00 	0.39 	0.00 	0.36 	0.00 	0.00 	0.00 	0.47 	0.00 	0.00
];
for i = 1:100
[p1,ps]=mapminmax(p);
[t1,ts]=mapminmax(t);
[trainsample.p,valsample.p,testsample.p] =dividerand(p,0.7,0.15,0.15);
[trainsample.t,valsample.t,testsample.t] =dividerand(t,0.7,0.15,0.15);
TF1='tansig';TF2='purelin';
net=newff(minmax(p),[10,1],{TF1 TF2},'traingdm');%matlab版本差异可能导致此处有警告
net.trainParam.epochs=10000;
net.trainParam.goal=1e-7;
net.trainParam.lr=0.001;
net.trainParam.mc=0.6;
net.trainParam.show=50;
net.trainFcn='trainlm';
[net,tr]=train(net,trainsample.p,trainsample.t);
[normtrainoutput,trainPerf]=sim(net,trainsample.p,[],[],trainsample.t);
[normvalidateoutput,validatePerf]=sim(net,valsample.p,[],[],valsample.t);
[normtestoutput,testPerf]=sim(net,testsample.p,[],[],testsample.t);
trainoutput=mapminmax('reverse',normtrainoutput,ts);
validateoutput=mapminmax('reverse',normvalidateoutput,ts);
testoutput=mapminmax('reverse',normtestoutput,ts);
trainvalue=mapminmax('reverse',trainsample.t,ts);
validatevalue=mapminmax('reverse',valsample.t,ts);
testvalue=mapminmax('reverse',testsample.t,ts);
errors=trainvalue-trainoutput;
%plotregression拟合图
%figure,plotregression(trainvalue,trainoutput)
R = corrcoef(trainvalue,trainoutput);
M = R(1,2);
i=0;
i=i+1;
b=[b;M];
end
disp(b)
