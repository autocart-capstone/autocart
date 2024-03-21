% Define the coordinates of three structures in the environment
structure1 = [0, 0; 0, 2.13; 3.96,2.13;3.96,18.50; 5.24,18.50;5.24,17.57;15.79,17.57;15.79,17.57;15.79,21.70;8.07,21.70;8.07,24.07;12.64,24.07;12.64,23.46;13.84,23.46;13.84,24.07;29.52,24.07;29.52,22.09;25.4,22.09;25.4,17.82;27.33,17.82;27.33,18.18;27.94,18.18;27.94,17.82;32.44,17.82
    32.44,15.94;25.4,15.94;25.4,0;0,0];
structure2 = [5.25,1.83;5.25,13.67;6,13.67;6,14.67;5.25,14.67;5.25,15.70;6.75,15.70;6.75,14.94;7.75,14.94;7.75,15.7;23.54,15.70;23.54,14.15;22.79,14.15;22.79,12.82;23.54,12.82;23.54,1.83;22.04,1.83;22.04,2.59;21.01,2.59;21.01,1.83;5.25,1.83];
structure3 = [17.15,21.7;23.5,21.7;23.5,19.11;24,19.11;24,17.57;17.15,17.57;17.15,21.7];

% Define test positions for the LiDAR sensor
test_pos = [5 18; 5 1 ; 5 16.5;10 23; 13 23; 16 23; 19 23;22 23;25 23; 28 23; 7.25 16.5; 10 16.5; 13 16.5; 16 16.5; 19 16.5; 22 16.5; 25 16.5; 27.2 16.5; 30.5 16.5;16.5 20;24.5 20;24.5 15; 24.5 13.5; 24.5 10.5; 24.5 7.5; 24.5 4.5; 24.5 1; 5 14; 5 11; 5 8; 5 5; 5 2.5; 2 1; 8 1; 11 1; 14 1; 17 1; 19 1; 21.25 1; 23 1;21.5,2.2;23,13.49;27.64,18;14.5,23.8;11.3,23.8];
N_positions = size(test_pos, 1);

% Initialize an array to store measurements for each position and angle
measures = zeros(2, 34, N_positions);

% Loop over each test position
for np = 1:N_positions

    lidar_pos = test_pos(np,:);

    % Plotting setup
    figure(1)
    plot(structure1(:,1), structure1(:,2), 'k'); % Plot walls
    hold on
    plot(structure2(:,1),structure2(:,2),'k');
    plot(structure3(:,1),structure3(:,2),'k');
    axis equal;
    
    % Iterate over angles from 0 to 359 degrees in 10-degree increment
    angle_list = 0:10:359;
    for na = 1:length(angle_list)

        angle_deg = angle_list(na);

        % Convert angle from degrees to radians
        angle_rad = deg2rad(angle_deg);
        
        % Calculate endpoint of the LiDAR beam 50 meters away
        x_end = 50 * cos(angle_rad) + lidar_pos(1); 
        y_end = 50 * sin(angle_rad) + lidar_pos(2);
        
        % Find intersection points of the LiDAR beam with each structure
        [x_intersect1, y_intersect1] = polyxpoly([lidar_pos(1),x_end],[lidar_pos(2),y_end], structure1(:,1), structure1(:,2));
        [x_intersect2, y_intersect2] = polyxpoly([lidar_pos(1),x_end],[lidar_pos(2),y_end], structure2(:,1), structure2(:,2));
        [x_intersect3, y_intersect3] = polyxpoly([lidar_pos(1),x_end],[lidar_pos(2),y_end], structure3(:,1), structure3(:,2));
        x_intersect = [ x_intersect1 ; x_intersect2 ; x_intersect3];
        y_intersect = [ y_intersect1 ; y_intersect2 ; y_intersect3];
        
        % MSE/Euclidean Distance
        distance = sqrt((x_intersect-lidar_pos(1)).^2 + (y_intersect-lidar_pos(2)).^2);
        [~,idx] = min(distance);
        x_intersect = x_intersect(idx);
        y_intersect = y_intersect(idx);

        %if (np == 33)
        %plot(x_intersect, y_intersect, 'r.');
        %plot([lidar_pos(1) x_intersect], [lidar_pos(2) y_intersect], 'm');
        %end
        
        % Store the relative position of the closest intersection point
        measures(:,na,np) = [x_intersect ; y_intersect] - test_pos(np,:).';
        
        if (na == 1)  % pointing right
            rightwall(np) = x_intersect;
        elseif (na == 10)   % pointing up
            topwall(np) = y_intersect;
        elseif (na == 19)   % pointing left
            leftwall(np) = x_intersect;
        elseif (na == 28)   % pointing_down
            bottomwall(np) = y_intersect;
        end

    end


    % Plot the current LiDAR position
    plot(lidar_pos(1), lidar_pos(2), 'go');

    xlabel('X-axis (m)');
    ylabel('Y-axis (m)');
    title('Map'); 
    drawnow
    pause(0.1)
    
    %lidar_pos(1) = lidar_pos(1) + 0.1;
end


% Define the actual position of the LiDAR sensor
lidar_pos = [];

% Define a set of points to simulate the LiDAR path
lidar = [1 1 ; 25 1 ; 25,22.5; 29,22.5; 29, 23.5; 14,23.5;14,23;12.5,23; 
    12.5,23.5;8.2,23.5;8.2,22; 16.4,22;16.4,16.5;32,16.5;32,17.5;27.7,17.5;
    27.7,18;27.4,18;27.4,16;7.5,16;7.5,15.2;6.9,15.2;6.9,16;4.2,16;4.2,18.2;5,18.2;5,14.5;5.8,14.5;5.8,13.8;5,13.5;5,1;1,1];

% Determine the number of positions in the LiDAR path
X_positions = size(lidar,1);

% Number of steps for interpolating between points in the LiDAR path
num_steps = 50;

plot(lidar(:, 1), lidar(:, 2), 'ro', 'MarkerSize', 10, 'DisplayName', 'Points');
lidar_position = lidar(1, :);

% Initialize an empty array to store interpolated LiDAR positions
lidar_position = [];
for seg=1:X_positions-1
    nx = (0:num_steps).';
    lidar_seq = (lidar(seg,:) + nx .* (lidar(seg+1,:) - lidar(seg,:)) / num_steps);
    noise = randn(size(lidar_seq)) * 0.1; % Adjust the noise level as needed
    lidar_seq = lidar_seq + noise;
    %plot(lidar_seq(seg,1),lidar_seq(seg,2),'m.');
    lidar_position = [lidar_position ; lidar_seq];
    lidar_pos = lidar_position;
    disp(lidar_pos);

end
for nx = 1:size(lidar_position,1)
        %plot(lidar_position(nx, 1), lidar_position(nx, 2), 'r.');
        plot(lidar_pos(nx, 1), lidar_pos(nx, 2), 'm.');
        drawnow;
end
return

% Initialize an array to store real LiDAR data for 36 angles (0 to 350 degrees in 10-degree increments)
real_data = zeros(2, 36);

angle_list = 0:10:359;

% Iterate over each angle to simulate LiDAR measurements
for na = 1:length(angle_list)
    angle_deg = angle_list(na);

    % Convert angle from degrees to radians
    angle_rad = deg2rad(angle_deg);

    % Calculate the endpoint of the LiDAR beam 50 meters away
    x_end = 50 * cos(angle_rad) + lidar_pos(1);
    y_end = 50 * sin(angle_rad) + lidar_pos(2);

    % Find intersection points of the LiDAR beam with the structures
    [x_intersect1, y_intersect1] = polyxpoly([lidar_pos(1),x_end],[lidar_pos(2),y_end], structure1(:,1), structure1(:,2));
    [x_intersect2, y_intersect2] = polyxpoly([lidar_pos(1),x_end],[lidar_pos(2),y_end], structure2(:,1), structure2(:,2));
    [x_intersect3, y_intersect3] = polyxpoly([lidar_pos(1),x_end],[lidar_pos(2),y_end], structure3(:,1), structure3(:,2));
    
    % Combine intersections from all structures
    x_intersect = [ x_intersect1 ; x_intersect2 ;x_intersect3];
    y_intersect = [ y_intersect1 ; y_intersect2 ;y_intersect3];
    
    % Calculate distance from LiDAR position to each intersection point
    distance = sqrt((x_intersect-lidar_pos(1)).^2 + (y_intersect-lidar_pos(2)).^2);
    [~,idx] = min(distance);
    x_intersect = x_intersect(idx);
    y_intersect = y_intersect(idx);
    
    % Store the relative position of the closest intersection to the LiDAR position
    real_data(:,na) = [x_intersect ; y_intersect] - lidar_pos.';

    % Plot the LiDAR beam to the closest intersection point
    plot([lidar_pos(1) x_intersect],[lidar_pos(2) y_intersect],'r');
    

end

% Plot the actual LiDAR position as a yellow circle
plot(lidar_pos(1),lidar_pos(2),'yo');

% Calculate the metric (sum of squared differences) for each test position
metric = squeeze(sum(sum((measures - real_data).^2)));

% Find the test position with the minimum metric value (closest match)
[~,idx] = min(metric);
fprintf('The lidar is closest to position %g,%g\n', test_pos(idx,:));

% Sort the metric values to find the closest and second closest test positions
[p,idx2] = sort(metric);
fprintf('%g %g\n',test_pos(idx2(1),:));
fprintf('%g %g\n', test_pos(idx2(2),:));
%disp(p);
tp = test_pos(idx2(1), :);
%plot(tp(1), tp(2), 'kx')

fprintf('Weight percentage of p(1): %.2f%%\n', weight_percentage_p1 * 100);
fprintf('Weight percentage of p(2): %.2f%%\n', weight_percentage_p2 * 100);


% Plot the closest and second closest test positions as green circles
plot(test_pos(idx2(1),1),test_pos(idx2(1),2),'go');
plot(test_pos(idx2(2),1),test_pos(idx2(2),2),'go');

% Use the closest test position for further calculations
pidx = idx2(1);

% Calculate approximate positions based on distances to the nearest walls
xapprox1 = leftwall(pidx) + abs(real_data(1, 19));
xapprox2 = rightwall(pidx) - abs(real_data(1,1));
yapprox1 = bottomwall(pidx) + abs(real_data(2, 28));
yapprox2 = topwall(pidx) - abs(real_data(2,10));

% Average the approximate positions to find the final estimated position
xapprox = (xapprox1+xapprox2)/2;
yapprox = (yapprox1+yapprox2)/2;
approx_pos = [xapprox, yapprox];

% Plot LiDAR beams from the approximated position to validate the estimation
approx_data = zeros(2,36);
angle_list = 0:10:359;
for nc = 1:length(angle_list)
    angle_deg = angle_list(nc);
    angle_rad = deg2rad(angle_deg);
    x_end = 50 * cos(angle_rad) + approx_pos(1); % 5 meters away in the x direction
    y_end = 50 * sin(angle_rad) + approx_pos(2); % 5 meters away in the y direction
    [x_intersect1, y_intersect1] = polyxpoly([approx_pos(1),x_end],[approx_pos(2),y_end], structure1(:,1), structure1(:,2));
    [x_intersect2, y_intersect2] = polyxpoly([approx_pos(1),x_end],[approx_pos(2),y_end], structure2(:,1), structure2(:,2));
    [x_intersect3, y_intersect3] = polyxpoly([approx_pos(1),x_end],[approx_pos(2),y_end], structure3(:,1), structure3(:,2));

    x_intersect = [ x_intersect1 ; x_intersect2 ; x_intersect3];
    y_intersect = [ y_intersect1 ; y_intersect2 ; y_intersect3];
    distance = sqrt((x_intersect-approx_pos(1)).^2 + (y_intersect-approx_pos(2)).^2);
    [~,idx] = min(distance);
    x_intersect = x_intersect(idx);
    y_intersect = y_intersect(idx);
    %approx_data(:,nc) = [x_intersect ; y_intersect] - approx_pos.';
    plot([approx_pos(1) x_intersect],[approx_pos(2) y_intersect],'m');
end

hold off;
fprintf('Approximated position is : %g,%g\n',approx_pos(1),approx_pos(2));
fprintf('Actual position is : %g, %g \n',lidar_pos(1),lidar_pos(2));