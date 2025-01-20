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

n = 1000;

P = zeros(1,n);
K_new = zeros(1,n);
u = zeros(1,n);
v = zeros(1,n);

x = l;

for i = 1:n
    P(i) = n*i;

    %Equivalent cantilever uniform load
    q = (P(i)*(H^2)*c*w)/(L^3);
    
    %Curvature
    K_new(i) = (1/E)*((3*mu*q)/(4*h^3)+(3*q*(x^2+2*l*x+l^2)/(4*h^3))-(3*q*(8+5*mu)/(5*h)));
    
    %x displacement
    u(i) = (1/K_new(i)).*(sin(K_new(i)*s))-s;
    
    %y displacement
    v(i) = -(1/K_new(i))*(1-cos(K_new(i)*s));
end

figure(1);
plot(P,u,"linewidth",3);
xlabel('Pressure, Pa');
ylabel('x deflection, m');

figure(2);
plot(P,v,"linewidth",3);
xlabel('Pressure, Pa');
ylabel('y deflection, m');


