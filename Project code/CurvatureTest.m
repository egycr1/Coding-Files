clear
close all
mNum = input("Muscle Number: ");
TestNum = input("Test Number: ");
FileName = "Muscle" + mNum + "_Test" + TestNum + ".png";
I = imread(FileName); %Open Test Picture file

% I = imread("MuscleSim.png");

imshow(I) % Display picture

[x_s, y_s] = getpts;
xdiff = x_s(2)-x_s(1);
ydiff = y_s(2)-y_s(1);
scale = sqrt((xdiff^2)+(ydiff^2));
close all %Close open figures

imshow(I) % Display picture
[x,y] = getpts; % User inputs points onto opened picture
                % Process terminates once user double-clicks
figure(1);
line(x,y,"linewidth",3) % Display points and connect with line

s = size(x);

x_adj = zeros(s);
y_adj = zeros(s);

for i = 1:s(1)
    x_adj(i) = x(i)-x(1);
    y_adj(i) = y(i)-y(1);
end

figure(2);
line(x_adj/scale,y_adj/scale,"linewidth",3) %Plot adjusted scaled values

% Test code allowing for interpolation between points for smoother curve
% Needs to be refined

% xi=x(1):0.2:x(s(1));
% method='spline';
% yi=interp1(x,y,xi,method);
% figure(2);
% plot(xi,yi)
