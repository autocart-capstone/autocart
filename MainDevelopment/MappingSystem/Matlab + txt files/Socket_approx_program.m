%{
This is a Mapping file for getting the current points on the cart
Gets the LIDAR from the pi then processes it and send back the approximate
location of the cart 
%}
load('ahmed.mat');
fig=figure(1);
plot(structures{1}(:,1), structures{1}(:,2), 'k'); % Plot walls
hold on
plot(structures{2}(:,1), structures{2}(:,2), 'k'); % Plot walls
xlim([-5 35]);
ylim([-5 30]);
set(gca, 'ButtonDownFcn', @plotClickCallback);
set(fig, 'KeyPressFcn',@ResetMap);

%disp(['You clicked at X:', num2str(x_clicked), ', Y:', num2str(y_clicked)]);
X_meas = measures(1,:,:);
Y_meas = measures(2,:,:);
D_meas = sqrt(X_meas.^2 + Y_meas.^2);
last_pos = nan(1,2);
t = tcpclient('10.42.0.1', 8003, "Timeout", 100000);
a = [0.0,-1.0,0.0,1.0,0.0];
r = a*0.2;
b = [1.0,-1.0,0.0,-1.0,1.0];
pgon = polyshape(a,b);
pgon = scale(pgon,0.3);
angle = 0;
x_new =0;
y_new = 0;
global Reset;
Reset=false;
while true
    size = read(t,1, "int32");
    %disp(size);

    floats = read(t,size,'single');
    floats = reshape(floats, 2, []);
    theta = floats(1,:);
    distance = floats(2,:);
    % if h ~= 0
    %      delete h;
    %  end
    hold on
    [x, y, angle,x_new,y_new] = position(theta,distance,angle,test_pos,measures,walls,D_meas,last_pos,x_new,y_new);
    if Reset == false
        last_pos=[x y];
    else
        last_pos=nan(1,2);
    end
    if exist('n','var')
        delete(n);
    end
    if exist('d','var')
        delete(d);
    end
    phi = -90+angle;
    z = rotate(pgon,phi);
    h = plot(translate(z,x,y));
    c = plot(x_new,y_new,'r.');
    %h = plot(translate(rotate(pgon, x, y,-90+angle));
    %disp(angle);
    write(t,[sprintf('%g %g %g',x,y,angle) newline]);
    hold off;
    n=h;
    d=c;
    %write(t,[x y])
    

end

% Nested callback function definition
function [x_clicked y_clicked] = plotClickCallback(src, ~)
    % Get the coordinates of the mouse click within the axes
    clickCoords = get(src, 'CurrentPoint'); % CurrentPoint returns [x,y] of the click
    x_clicked = clickCoords(1, 1); % X coordinate of the click
    y_clicked = clickCoords(1, 2); % Y coordinate of the click
    
end

function ResetMap(src, event)
    global Reset;
    if strcmp(event.Key, 'space')
        Reset=true;
    end
end



% filename = "test425.txt";
% xoff = 24.63;
% yoff = 20.98;
% angle = 89.5;

%filename = "19thjantest2.txt";
%xoff = 24.63;
%yoff =  7.98;
%angle = 0;

function [xa,ya, angle, x_new,y_new] = position(theta, distances,angle, test_pos,measures,walls,D_meas,last_pos,x_new,y_new)
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
    fidx=1;
    pidx_near =1;
    pidx=1;
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

    minmetric = 1000000.*ones(1, 36);
    minidx = zeros(1, 36);
    if isnan(last_pos)
        for na = 1:length(angle_list)
            new_counts = circshift(counts, na-1);
            new_mean_distance = circshift(mean_distance, na-1);
            %metric = squeeze(sum(((X_meas - X_coord).^2 + (Y_meas - Y_coord).^2).*new_counts));
            metric = squeeze(sum(abs(D_meas - new_mean_distance).*new_counts));
            [minmetric(na),minidx(na)] = min(metric);
    
        end
        [~,fidx] = min(minmetric); % find best orientation
        pidx = minidx(fidx);  % find index of best nearby test position

    else
        test_pos_distance = sum((test_pos - last_pos).^2, 2);
        
        % Find the indices of the test positions that are near the robot
        near_test_pos_idx = find(test_pos_distance < 0.5);
        % Discard all the non-near test positions
        D_meas_near = D_meas(:,:,near_test_pos_idx);
        %angle_list = 0:10:angle_list(fidx);
        %minmetric = zeros(1, 36);
        
        idx_angle= find(angle_list==angle);
        nx = idx_angle - 9;
        %minidx = zeros(1, 36);
        for na = nx:(nx+18)
            new_counts = circshift(counts, na-1);
            new_mean_distance = circshift(mean_distance, na-1);
            %metric = squeeze(sum(((X_meas - X_coord).^2 + (Y_meas - Y_coord).^2).*new_counts));
            metric = squeeze(sum(abs(D_meas_near - new_mean_distance).*new_counts));
            if na<1
                %disp("HELLO");
                [minmetric(na+36),minidx(na+36)] = min(metric);
            elseif na > 36
                [minmetric(na-36),minidx(na-36)] = min(metric);
            else
                [minmetric(na),minidx(na)] = min(metric);
            end
    
        end
        [minima,fidx] = min(minmetric); % find best orientation
        disp(minima);
        %disp(fidx);
        pidx_near = minidx(fidx);  % find index of best nearby test position
        %disp(pidx_near);
        pidx = near_test_pos_idx(pidx_near); % find corresponding test position

       
        % Attempt to find a position within 1 metre of the last
    end
    angle = angle_list(fidx);
    xa = test_pos(pidx,1);
    ya = test_pos(pidx,2);

    %dodraw = true;
    x_new = xa + distance.*cosd(theta_fixed+angle_list(fidx));
    y_new = ya + distance.*sind(theta_fixed+angle_list(fidx));
    
    
    % if dodraw
    % 
    % 
    %     axis equal;
    %     end
end
