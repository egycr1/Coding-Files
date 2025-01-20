clear
close all
mNum = input("Muscle Number: ");
%TestNum = input("Test Number: ");
FileName1 = "FEA" + mNum + "_Undeformed.png";
FileName2 = "FEA" + mNum + "_Deformed.png";
I1 = imread(FileName1); %Open Test Picture file
I2 = imread(FileName2);

% I = imread("MuscleSim.png");

imshow(I1) % Display picture

l = 141e-3;

% if mNum == "1"
%     l = 141e-3;
% else if mNum == "2"
%         l = ;
% else
%         l = ;
% end

[x_s, y_s] = getpts;
xdiff = x_s(2)-x_s(1);
ydiff = y_s(2)-y_s(1);
scale = sqrt((xdiff^2)+(ydiff^2))/l;
close all %Close open figures

imshow(I2) % Display picture
[x,y] = getpts; % User inputs points onto opened picture
                % Process terminates once user double-clicks
figure(1);
line(x,y,"linewidth",3) % Display points and connect with line

s = size(x);

x_adj = zeros(s);
y_adj = zeros(s);

for i = 1:s(1)
    x_adj(i) = x(1)-x(i);
    y_adj(i) = y(1)-y(i);
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
