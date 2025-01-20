clear
close all

% Define material properties
mu = 0.48; %Poissons ratio
E = 1.5E6; %? YM - both referenced in onenote
rho = 1500; %kg/m^3 - check later.

% Component dimensions
c = 3E-3; %m, Chamber length
w = 107.85E-3;%kg, Actuator weight
H = 20E-3; %m, Chamber height
L = 142E-3; %m, Actuator length
s = L;
l = L/2;
h = 10E-3;
t=3E-3;

s = L;

P = 0;
n=50;
x = zeros(1,n);
K = zeros(1,n);
u = zeros(1,n);
v = zeros(1,n);
x(1)=0;
for i=2:n
    x(i) = (L/n)*i;
end
m=-3.3;
K = m*pi/(2*L);

for i=1:n
    u(i)=(1/K)*sin(K*x(i));
    v(i)=(1/K)*(1-cos(K*x(i)));
end
plot(u,v); grid on;


