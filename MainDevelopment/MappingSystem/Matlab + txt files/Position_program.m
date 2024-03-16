%{
This is a Mapping file for getting the current points on the cart
Gets the LIDAR from the pi then processes it and send back the approximate
location of the cart 
%}
load('ahmed.mat');
figure(1)
plot(structures{1}(:,1), structures{1}(:,2), 'k'); % Plot walls
hold on
plot(structures{2}(:,1), structures{2}(:,2), 'k'); % Plot walls
set(gca, 'ButtonDownFcn', @plotClickCallback);


disp(['You clicked at X:', num2str(x_clicked), ', Y:', num2str(y_clicked)]);
X_meas = measures(1,:,:);
Y_meas = measures(2,:,:);
D_meas = sqrt(X_meas.^2 + Y_meas.^2);
last_two_points = nan(2,2);
t = tcpclient('172.17.152.43', 8003, "Timeout", 100000);

while true
    size = read(t,1, "int32");
    disp(size);

    floats = read(t,size,'single');
    floats = reshape(floats, 2, []);
    theta = floats(1,:);
    distance = floats(2,:);
    % if h ~= 0
    %      delete h;
    %  end
    hold on
    [x, y] = position(theta,distance,test_pos,measures,walls,D_meas,last_two_points);
    h = plot(x,y,'ro');
    write(t,[sprintf('%g %g',x,y) newline]);
    hold off;
    delete(h);
    %write(t,[x y])
    

end

% Nested callback function definition
function [x_clicked y_clicked] = plotClickCallback(src, ~)
    % Get the coordinates of the mouse click within the axes
    clickCoords = get(src, 'CurrentPoint'); % CurrentPoint returns [x,y] of the click
    x_clicked = clickCoords(1, 1); % X coordinate of the click
    y_clicked = clickCoords(1, 2); % Y coordinate of the click
    
end


% filename = "test425.txt";
% xoff = 24.63;
% yoff = 20.98;
% angle = 89.5;

%filename = "19thjantest2.txt";
%xoff = 24.63;
%yoff =  7.98;
%angle = 0;

function [xa,ya] = position(theta, distances,test_pos,measures,walls,D_meas,last_two_points)
% Read data file, and skip header and blank line at end
    xoff = 24.63;
    yoff = 22.50;
    
    % Extract angle, distance, and quality
    theta_raw = theta;
    distance = distances;    
    distance = distance/1000;
    theta_fixed = mod((360 - theta_raw), 360);
    
    % Sort theta values
    [theta_fixed, idx] = sort(theta_fixed);
    distance = distance(idx);
        
    angle_list = 0:10:359;
    real_data = zeros(2,36);
    counts = zeros(1, 36);
    mean_distance = zeros(1, 36);
    
    for nx = 1:length(angle_list)
        current_angle = angle_list(nx);
        theta_range = [mod(current_angle-1,360), mod(current_angle+1,360)];
        if current_angle == 0
            idx = (theta_fixed > theta_range(1) | theta_fixed < theta_range(2));
        else
            idx = (theta_fixed > theta_range(1) & theta_fixed < theta_range(2));
        end
    
        counts(nx) = sum(idx);
        mean_distance(nx) = mean(distance(idx));
        if (counts(nx) == 0)
            mean_distance(nx) = 0.0;
        end
    end
    
    minmetric = zeros(1, 36);
    minidx = zeros(1, 36);
    for na = 1:length(angle_list)
        new_counts = circshift(counts, na-1);
        new_mean_distance = circshift(mean_distance, na-1);   
    
        %metric = squeeze(sum(((X_meas - X_coord).^2 + (Y_meas - Y_coord).^2).*new_counts));
        metric = squeeze(sum(abs(D_meas - new_mean_distance).*new_counts));
    
        [minmetric(na),minidx(na)] = min(metric);
       

    end
    
    [~,Oo] = min(minmetric);
    % sorted_minmetric = sort(minmetric);
    % sorted_metric = sort(metric);
    pidx = minidx(fidx);
    % Attempt to find a position within 1 metre of the last
    found = false; % Flag to indicate if a suitable position has been found
    potential_pidx = find(minmetric == min(minmetric)); % Find indices with the minimum metric
    
    for i = 1:length(potential_pidx)
        pidx = potential_pidx(i);
        potential_x = test_pos(pidx, 1);
        potential_y = test_pos(pidx, 2);
        
        % Check distance from the last point in last_two_points (which is the most recent point)
        if ~isnan(last_two_points(2,1)) % Ensure there is a last point to compare to
            last_x = last_two_points(2, 1);
            last_y = last_two_points(2, 2);
            distance = sqrt((potential_x - last_x)^2 + (potential_y - last_y)^2);
            if distance <= 1
                found = true;
                break; % Exit loop if a suitable position is found
            end
        else
            found = true; % If there's no last point, accept the first suitable position
            break;
        end
    end
    
    if found
        xa = potential_x;
        ya = potential_y;
        fprintf('Accepted position within 1 metre: %g,%g\n', xa, ya);
    else
        % Return NaN if no suitable position is found, we still need to
        % figure out what to do about this
        xa = NaN; 
        ya = NaN;
        fprintf('No position within 1 metre was found.\n');
    end
    
    % Update the last_two_points array
    % Shift the last point to the first slot and insert the new point at the end
    last_two_points(1,:) = last_two_points(2,:);
    last_two_points(2,:) = [xa, ya];
    
    fprintf('The lidar is closest to position %g,%g\n', test_pos(pidx,:));
    
    new_counts = circshift(counts, fidx-1);
    new_mean_distance = circshift(mean_distance, fidx-1);
    for nx = 1:length(angle_list)
        X_coord = new_mean_distance(nx) .* cosd(angle_list(nx)); 
        Y_coord = new_mean_distance(nx) .* sind(angle_list(nx));
        real_data(:,nx) = [X_coord; Y_coord];
    end
   
    
    xa = test_pos(pidx,1);
    ya = test_pos(pidx,2);

    % dodraw = true;
    % x_new = xoff + distance.*cosd(theta_fixed+angle_list(fidx));
    % y_new = yoff + distance.*sind(theta_fixed+angle_list(fidx));
    % if dodraw
    % 
    % 
    %     axis equal;
    %     end
end
