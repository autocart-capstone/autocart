filename = "19thjan.txt";

% Read data file, and skip header and blank line at end
loadedData = readlines(filename);
loadedData = loadedData(7:end-1);

% Extract angle, distance, and quality
data = cellfun(@(S) sscanf(S, "%*[^:]: %g %*[^:]: %g %*[^:]: %g %*[^\n]"), ...
    loadedData, 'UniformOutput', false);
data = reshape(cell2mat(data), 3, []);
theta = data(1,:);
distance = data(2,:);
quality = data(3,:);

% Filter out data points with quality equal to 0
idx = (quality ~= 0);
theta = theta(idx);
distance = distance(idx);

% Sort theta values
[theta, idx] = sort(theta);
distance = distance(idx);

% Convert to Cartesian coordinates
x = distance .* cosd(theta); % Convert degrees to radians internally
y = distance .* sind(theta);

% Extract points for each wall
% Left wall (0 degrees)
target1 = (theta > 359 | theta < 1); % Allow for wraparound
theta1 = theta(target1);
distance1 = distance(target1);
mean_theta1_rad = atan2(mean(sind(theta1)), mean(cosd(theta1))); %%theta is hypotenuse, we need the mean of theta in the x direction, also mean of theta in y
mean_theta1_deg = rad2deg(mean_theta1_rad);%%convert back to degrees
mean_theta1 = mod(mean_theta1_deg, 360);%%handle wraparound -- this just means treat angles between 359 to 360 as in same class as 0 to 1 deg
mean_distance1 = mean(distance1);
x1 = mean_distance1 .* cosd(mean_theta1);
y1 = -mean_distance1 .* sind(mean_theta1);
Left_wall = x1;

% Bottom wall (90 degrees)
target2 = (theta > 89 & theta < 91);
theta2 = theta(target2);
distance2 = distance(target2);
mean_distance2 = sum(distance2)/length(distance2); %%could also use mean(X)
mean_theta2 = sum(theta2)/length(theta2);
x2 = mean_distance2 .* cosd(mean_theta2);
y2 = -mean_distance2 .* sind(mean_theta2);
Bottom_wall = y2;

% Right wall (180 degrees)
target3 = (theta > 179 & theta < 181);
theta3 = theta(target3);
distance3 = distance(target3);
mean_distance3 = sum(distance3)/length(distance3); 
mean_theta3 = sum(theta3)/length(theta3);
x3 = mean_distance3 .* cosd(mean_theta3);
y3 = -mean_distance3 .* sind(mean_theta3);
Right_wall = x3;

% Top wall (270 degrees)
target4 = (theta > 269 & theta < 271);
theta4 = theta(target4);
distance4 = distance(target4);
mean_distance4 = sum(distance4)/length(distance4); 
mean_theta4 = sum(theta4)/length(theta4);
x4 = mean_distance4 .* cosd(mean_theta4);
y4 = -mean_distance4 .* sind(mean_theta4);
Top_wall = y4;

% Plot all points in black
figure(1)
plot(x, y, 'k.');

Real_Walls = [Bottom_wall ;Right_wall ;Left_wall; Top_wall];
disp(Real_Walls);
% Plot wall points in red
hold on;
plot(x1, y1, 'r.');
plot(x2, y2, 'b.');
plot(x3, y3, 'm.');
plot(x4, y4, 'y.');
hold off;

% Set axis equal
axis equal;

% Label the axes and add a title
xlabel('X-axis');
ylabel('Y-axis');
title('Plot of Points');
legend('All Points', 'Bottom Wall', 'Left Wall', 'Top Wall', 'Right Wall');

figure(2)
plot(x1, y1, 'r.');
hold on 
plot(x2, y2, 'b.');
plot(x3, y3, 'm.');
plot(x4, y4, 'y.');
hold off
axis equal;
%%Here is what to do now, We only really care about these 4 absolute
%%points, we need to care at which angle this happens for the simmulated
%%test position, hence why the wall array is set up as is
%%what to do now is to configure all the test_pos and then just compare
%%these 4 points
%%Ex xa1 = walls(1,pidx) + abs(Real_Walls(3, 1)); %left wall
    % xa2 = walls(3,pidx) - abs(real_data(2,  1)); %%right wall
    % ya1 = walls(4,pidx) + abs(real_data(1, 1)); %% bottom wall
    % ya2 = walls(2,pidx) - abs(real_data(4, 1)); %%top wall