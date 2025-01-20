close all
clear all
clc

E = 1.5E6;

hc = 20e-3;
wc = 20e-3;
L = 15e-3;
t = 3e-3;
s=5e-3;
P = 50e3;
w = P*wc;

I = (wc*t)/12;

x = hc/2;


n = input("Number of chambers: ");

delta = (((w*x^3)/12)*(hc-x/2)-(w*(hc^3)/24)*x)/(E*I);

theta = (delta-(s/2))/x;

L = L+s/2;

linex = zeros(n,2);
liney = zeros(n,2);
linez = zeros(n,2);
linex(1,2) = L;


for i=2:n
    linex(i,1) = linex((i-1),2);
    linex(i,2) = linex(i,1) + (L)*cos(2*theta*(i-1));
    liney(i,1) = liney((i-1),2);
    liney(i,2) = liney(i,1) + (L)*sin(2*theta*(i-1));
end

for i=1:n
    plot(-linex(i,:), liney(i,:),'k','LineWidth',1); hold on;
end
% ax = gca;
% ax.XAxis.Limits = [-0.03,0.02];
% ax.YAxis.Limits = [-0.05,0];


