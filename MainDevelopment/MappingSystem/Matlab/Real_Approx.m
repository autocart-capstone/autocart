filename = "test475.txt";

% Read data file, and skip header and blank line at end
loadedData = readlines(filename);
loadedData = loadedData(7:end-1);

% Extract angle, distance, and quality
data = cellfun(@(S) sscanf(S, "%*[^:]: %g %*[^:]: %g %*[^:]: %g %*[^\n]"), ...
    loadedData, 'UniformOutput', false);
data = reshape(cell2mat(data), 3, []);
theta_raw = data(1,:);
distance = data(2,:);
quality = data(3,:);

% distance = distance/1000;
% theta_fixed = mod((360 - theta_raw) - 91.5, 360);
% % % Filter out data points with quality equal to 0
% % idx = (quality ~= 0 & distance < 6);
% % theta_fixed = theta_fixed(idx);
% % distance = distance(idx);
% valid_indices = ~isnan(theta_fixed) & ~isinf(theta_fixed) & ~isnan(distance) & ~isinf(distance);
% theta_fixed = theta_fixed(valid_indices);
% distance = distance(valid_indices);

% Convert distances from mm to meters and adjust angles
distance = distance / 1000; % Convert distance to meters
theta_fixed = mod((360 - theta_raw) - 91.5, 360);

% Filter out data points with quality equal to 0 and distance greater than 6 meters
valid_indices = (quality ~= 0) & (distance <= 6);
theta_fixed = theta_fixed(valid_indices);
distance = distance(valid_indices);

% Proceed with sorting and other operations...
[theta_fixed, idx] = sort(theta_fixed);
distance = distance(idx);


% Convert to Cartesian coordinates
% x = distance .* cosd(theta); % Convert degrees to radians internally
% y = distance .* sind(theta);



% Extract points for each wall
% Right wall (0 degrees)
target1 = (theta_fixed > 359 | theta_fixed < 1); % Allow for wraparound
distance1 = distance(target1);
mean_distance1 = mean(distance1);
Right_wall = mean_distance1;
% Up wall (90 degrees)
target2 = (theta_fixed > 89 & theta_fixed < 91);
distance2 = distance(target2);
mean_distance2 = sum(distance2)/length(distance2); %%could also use mean(X)
Top_wall = mean_distance2;
% Left wall (180 degrees)
target3 = (theta_fixed > 179 & theta_fixed < 181);
distance3 = distance(target3);
mean_distance3 = sum(distance3)/length(distance3); 
Left_wall = mean_distance3;
% Left wall (270 degrees)
target4 = (theta_fixed > 269 & theta_fixed < 271);
theta4 = theta_fixed(target4);
distance4 = distance(target4);
mean_distance4 = sum(distance4)/length(distance4); 
Bottom_wall = mean_distance4;
% Plot all points in black

Real_Walls = [Right_wall ;Top_wall ;Left_wall;Bottom_wall];
disp(Real_Walls);
% Plot wall points in red


%%Here is what to do now, We only really care about these 4 absolute
%%points, we need to care at which angle this happens for the simmulated
%%test position, hence why the wall array is set up as is
%%what to do now is to configure all the test_pos and then just compare
%%these 4 points
%%Ex xa1 = walls(1,pidx) + abs(Real_Walls(3, 1)); %left wall
    % xa2 = walls(3,pidx) - abs(real_data(2,  1)); %%right wall
    % ya1 = walls(4,pidx) + abs(real_data(1, 1)); %% bottom wall
    % ya2 = walls(2,pidx) - abs(real_data(4, 1)); %%top wall


structures = {
 [  0.00, 0.00 ;  0.00, 2.13 ;  3.96, 2.13 ;  3.96,18.50 ;  5.24,18.50 ;
    5.24,17.57 ; 15.79,17.57 ; 15.79,17.57 ; 15.79,21.70 ;  8.07,21.70 ;
    8.07,24.07 ; 12.64,24.07 ; 12.64,23.46 ; 13.84,23.46 ; 13.84,24.07 ;
   29.52,24.07 ; 29.52,22.09 ; 25.40,22.09 ; 25.40,17.82 ; 27.33,17.82 ;
   27.33,18.18 ; 27.94,18.18 ; 27.94,17.82 ; 32.44,17.82 ; 32.44,15.94 ;
   25.40,15.94 ; 25.40, 0.00 ; 0.00, 0.00 ] ;
 [  5.25, 1.83 ;  5.25,13.67 ;  6.00,13.67 ;  6.00,14.67 ;  5.25,14.67 ;
    5.25,15.70 ;  6.75,15.70 ;  6.75,14.94 ;  7.75,14.94 ;  7.75,15.70 ;
   23.54,15.70 ; 23.54,14.15 ; 22.79,14.15 ; 22.79,12.82 ; 23.54,12.82 ;
   23.54, 1.83 ; 22.04, 1.83 ; 22.04, 2.59 ; 21.01, 2.59 ; 21.01, 1.83 ;
    5.25, 1.83 ] ;
 [ 17.15,21.70 ; 23.50,21.70 ; 23.50,19.11 ; 24.00,19.11 ; 24.00,17.57 ;
   17.15,17.57 ; 17.15,21.70 ]
};
N_structures = length(structures);

segs = [ structures{1}(1:end-1,:) structures{1}(2:end,:) ; structures{2}(1:end-1,:) structures{2}(2:end,:) ; structures{3}(1:end-1,:) structures{3}(2:end,:) ];
dodraw = true;
xoff = 24.63;
yoff = 22.50;
x = xoff + distance.*cosd(theta_fixed);
y = yoff + distance.*sind(theta_fixed);

test_pos = makeTestGrid(0.1, structures);
[measures,walls] = makeTestData(test_pos, segs);
N_testpos = size(test_pos, 1);

real_data = zeros(2,36);
angle_list = 0:10:359;
total_count = 0;
for na = 1:length(angle_list)
    current_angle = angle_list(na);
    theta_range = [mod(current_angle-1,360), mod(current_angle+1,360)];
    if current_angle == 0
        idx = (theta_fixed > theta_range(1) | theta_fixed < theta_range(2));
    else
       idx = (theta_fixed > theta_range(1) & theta_fixed < theta_range(2));
    end
    count = sum(idx);
    total_count = total_count + count;

end

for nx = 1:length(angle_list)
    current_angle = angle_list(nx);
    theta_range = [mod(current_angle-1,360), mod(current_angle+1,360)];
    if current_angle == 0
        idx = (theta_fixed > theta_range(1) | theta_fixed < theta_range(2));
    else
       idx = (theta_fixed > theta_range(1) & theta_fixed < theta_range(2));
    end
    if sum(idx) > 0
        mean_distance = mean(distance(idx));
    else
    % Skip this iteration or set a default value for mean_distance
        continue; % or mean_distance = defaultValue;
    end

    %real_data(:,nx) = mean_distance;
    weight = sum(idx)/length(idx);
    %fprintf('Weight of %g degrees is %g%%\n', current_angle,weight*100);
    
    sin_mean = mean(sind(theta_fixed(idx)));
    cos_mean = mean(cosd(theta_fixed(idx)));
    if sin_mean == 0 && cos_mean == 0
    % Handle the special case, e.g., by continuing to the next iteration or setting a default angle
        mean_theta = mean(mod(theta_fixed(idx),360));
    else
        mean_theta_rad = atan2(sin_mean, cos_mean);
        mean_theta_deg = rad2deg(mean_theta_rad);
        mean_theta = mod(mean_theta_rad,360);
    end

    X_coord = mean_distance .*cosd(mean_theta);
    Y_coord = mean_distance .*sind(mean_theta);
    real_data(:,nx) = [X_coord; Y_coord];
    metric = squeeze(sum(sum((measures - real_data).^2)));
    %disp(weight);
    

end
[~,idx] = min(metric);
fprintf('The lidar is closest to position %g,%g\n', test_pos(idx,:));

if dodraw
    figure(1)
    plot(structures{1}(:,1), structures{1}(:,2), 'k'); % Plot walls
    hold on
    plot(structures{2}(:,1), structures{2}(:,2), 'k'); % Plot walls
    plot(structures{3}(:,1), structures{3}(:,2), 'k'); % Plot walls
    plot(x,y,'r.');
    in1 = inpolygon(x, y, structures{1}(:,1), structures{1}(:,2));
    in2 = inpolygon(x, y, structures{2}(:,1), structures{2}(:,2));
    in3 = inpolygon(x, y, structures{3}(:,1), structures{3}(:,2));
    bad = (~in1 | in2 | in3);
    % in1 = inpolygon(test_pos(:,1), test_pos(:,2), structures{1}(:,1), structures{1}(:,2));
    % in2 = inpolygon(test_pos(:,1), test_pos(:,2), structures{2}(:,1), structures{2}(:,2));
    % in3 = inpolygon(test_pos(:,1), test_pos(:,2), structures{3}(:,1), structures{3}(:,2));
    % bad = (~in1 | in2 | in3);

    % x_new = x(~bad);
    % y_new = y(~bad);
    %plot(test_pos(:,1),test_pos(:,2),'go');
    axis equal;
    hold off
end

function test_pos = makeTestGrid(space, structures)
    %%% Make the test grid
    %     space: separation between points in the test grid (in metres)

    % Make grid of potential test points at specified grid spacing
    max_x =max(cellfun(@(x) max(x(:,1)), structures));
    max_y = max(cellfun(@(y) max(y(:,2)), structures));
    % min_x =min(cellfun(@(x) min(x(:,1)), structures));
    % min_y =min(cellfun(@(y) min(y(:,1)), structures));

    xv = 0.1:space:max_x;
    yv = 0.1:space:max_y;
    xall = reshape(ones(length(yv),1)*xv, [], 1);%%converting 2 dimension array to 1dimension* Multiply 1s length of yv by xv so you just xv for yv times, which is the same as xv
    yall = reshape(yv'*ones(1,length(xv)), [], 1);

    % Find valid test points (must be in a hallway)
    in1 = inpolygon(xall, yall, structures{1}(:,1), structures{1}(:,2));
    in2 = inpolygon(xall, yall, structures{2}(:,1), structures{2}(:,2));
    in3 = inpolygon(xall, yall, structures{3}(:,1), structures{3}(:,2));
    good = (in1 & ~in2 & ~in3);

    % Keep only valid test points
    test_pos = [ xall(good) yall(good) ];
end

function [measures,walls] = makeTestData(test_pos, segs)
    %%% Generate the expected lidar output at each test position
    N_testpos = size(test_pos, 1);

    measures = zeros(2, 36, N_testpos);
    walls = zeros(4, N_testpos);
    for np = 1:N_testpos
        xt = test_pos(np,1);    % test position x-value
        yt = test_pos(np,2);    % test position y-value

        measures(:,:,np) = getLidarMeasures(xt, yt, segs);

        walls(1,np) = measures(1, 1,np) + xt; % right wall
        walls(2,np) = measures(2,10,np) + yt; % top wall
        walls(3,np) = measures(1,19,np) + xt; % left wall
        walls(4,np) = measures(2,28,np) + yt; % bottom wall
    end
end

function measures = getLidarMeasures(xs, ys, segs)
    % Get xy-coordinates of the point where each lidar beam hits an object
    angle_deg = 0:10:359;
    angle_rad = deg2rad(angle_deg);

    % Find the distance to the nearest intersection point with the structures
    d = myintersect(xs,ys, cos(angle_rad),sin(angle_rad), segs);
    measures = [ d.*cos(angle_rad) ; ...
                 d.*sin(angle_rad) ];
end

function d = myintersect(xs,ys, dx,dy, segs)
    % Find distance to where line from (xs,ys) in direction (dx,dy)
    % intersects the line segment from p1=(x1,y1) to p2=(x2,y2)
    % Returns infinity if they do not intersect.

    % Shift origin and shape into column vectors
    x1 = reshape(segs(:,1), [], 1) - xs;
    y1 = reshape(segs(:,2), [], 1) - ys;
    x2 = reshape(segs(:,3), [], 1) - xs;
    y2 = reshape(segs(:,4), [], 1) - ys;

    % Convert beam directions into row vectors
    dx = reshape(dx, 1, []); %%ROW VECTOR [dx1 dx2 dx3..... dxN]
    dy = reshape(dy, 1, []); %%ROW VECTOR [dy1 dy2 dy3..... dyN]

    % Calculate projections
    d1 = x1.*dx + y1.*dy;       % distance along beam to closest point to p1 %%multiply column by row
    d2 = x2.*dx + y2.*dy;       % distance along beam to closest point to p2

    % Calculate projection error
    b1 = y1.*dx - x1.*dy;       % distance from beam to p1
    b2 = y2.*dx - x2.*dy;       % distance from beam to p2

    % Calculate distance to intersection point
    r = abs(b2) ./ (abs(b1) + abs(b2));
    d = d2 + r.*(d1-d2);
    d(b1.*b2 > 0) = inf;        % beam misses if errors have same sign
    d(d < 0) = inf;             % beam misses if distance is negative

    % Find nearest intersection point for each beam
    d = min(d);
    %disp(d);
end
