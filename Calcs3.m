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

m_i = -3;
maxiter = 100;
i=1;
err = (((2*L)/(m_i*pi))*sin(m_i*pi/2))+0.0108

while abs(err(i))>1e-3 && i<maxiter
    m_i(i+1) = m_i(i) - (((2*L)/(m_i(i)*pi))*sin(m_i(i)*pi/2))/((L/m_i(i))*cos(m_i(i)*pi/2)-((2*L)/((m_i(i)^2)*pi))*sin(m_i(i)*pi/2));
    err(i+1) = ((2*L)/(m_i(i+1)*pi))*sin(m_i(i+1)*pi/2)+0.0108;
    i=i+1;
end

% (((2*L)/(m_i(i)*pi))*sin(m_i(i)*pi/2))
figure;
plot(m_i, 'o-'); grid on; hold on; xlabel('iterations'); ylabel('m');
figure;
plot(err, 'o-'); grid on; hold on; xlabel('iterations'); ylabel('error');