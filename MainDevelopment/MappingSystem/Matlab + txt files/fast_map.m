% Define the walls of the environment as polygons
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

% 
% Convert structure polygons into a big list of line segments
segs = [ structures{1}(1:end-1,:) structures{1}(2:end,:) ; structures{2}(1:end-1,:) structures{2}(2:end,:) ; structures{3}(1:end-1,:) structures{3}(2:end,:) ];
dodraw = true; % 'true' to show graphics
%disp(segs);
tic

% Make the test grid and data
test_pos = makeTestGrid(0.1, structures);
%plot(test_pos(:,1),test_pos(:,2),'g.');
[measures,walls] = makeTestData(test_pos, segs);
%disp(walls(1,:)); always printing right wall
N_testpos = size(test_pos, 1);

% Make the random walk
real_pos = makeRandomWalk(structures);
N_real = size(real_pos, 1);


% Plot the floor plan
if dodraw
    figure(1)
    plot(structures{1}(:,1), structures{1}(:,2), 'k'); % Plot walls
    hold on
    plot(structures{2}(:,1), structures{2}(:,2), 'k'); % Plot walls
    plot(structures{3}(:,1), structures{3}(:,2), 'k'); % Plot walls
    %plot(test_pos(:,1), test_pos(:,2), 'r.')
    % in1 = inpolygon(test_pos(:,1), test_pos(:,2), structures{1}(:,1), structures{1}(:,2));
    % in2 = inpolygon(test_pos(:,1), test_pos(:,2), structures{2}(:,1), structures{2}(:,2));
    % in3 = inpolygon(test_pos(:,1), test_pos(:,2), structures{3}(:,1), structures{3}(:,2));
    % bad = (~in1 | in2 | in3);
   
    %plot(test_pos(:,1), test_pos(:,2), 'g.')
    axis equal;
    hold off
end


% Iterate over lidar positions
real_data = zeros(2, 36); % Initialize real_data for all lidar positions
err = zeros(N_real, 1);
failures = 0;
for np = 1:N_real

    xr = real_pos(np, 1);
    yr = real_pos(np, 2);

    real_data = getLidarMeasures(xr, yr, segs);

    metric = squeeze(sum(sum((measures - real_data).^2)));
    [~,pidx] = min(metric);

    xa1 = walls(1,pidx) + abs(real_data(1, 19));
    xa2 = walls(3,pidx) - abs(real_data(1,  1));
    ya1 = walls(4,pidx) + abs(real_data(2, 28));
    ya2 = walls(2,pidx) - abs(real_data(2, 10));
    xa = (xa1+xa2) / 2;
    ya = (ya1+ya2) / 2;

    if dodraw
        hold on
        plot(xr,yr,'k.');
        plot(xa, ya, 'm.');
        drawnow;
        hold off
    end

    % Find true closest test point
    dist = sum((test_pos - [xr yr]).^2, 2);
    [~,tidx] = min(dist);
    if (tidx ~= pidx)
        failures = failures + 1;
    end

    err(np) = sqrt((xr-xa).^2 + (yr-ya).^2);
end

if true
figure(2)
histogram(err, 200)
xlabel('error (metres)')
ylabel('Number of occurances');
title('Histogram of measurement error');
end

fprintf('RMSE: %g metres\n', sqrt(mean(err.^2)));
fprintf('Number of failures: %d (%g%%)\n', failures, failures/N_real*100);
fprintf('Prob. error <  1mm: %6.3f%%\n', sum(err<0.001)/N_real*100);
fprintf('Prob. error <  1cm: %6.3f%%\n', sum(err<0.010)/N_real*100);
fprintf('Prob. error <  5cm: %6.3f%%\n', sum(err<0.050)/N_real*100);
fprintf('Prob. error < 10cm: %6.3f%%\n', sum(err<0.100)/N_real*100);
fprintf('Prob. error < 50cm: %6.3f%%\n', sum(err<0.500)/N_real*100);

toc

function test_pos = makeTestGrid(space, structures)
    %%% Make the test grid
    %     space: separation between points in the test grid (in metres)

    % Make grid of potential test points at specified grid spacing
    max_x =max(cellfun(@(x) max(x(:,1)), structures));
    max_y = max(cellfun(@(y) max(y(:,2)), structures));

    xv = 0.1:space:max_x;
    yv = 0.1:space:max_y;
    xall = reshape(ones(length(yv),1)*xv, [], 1);
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

function pos = makeRandomWalk(structures)
    %%% Make a random walk around the floor, roughly following the
    %%% specified route, with the nominal step size.
    segments = [
        1.0, 1.0 ; 25.0, 1.0 ; 25.0,22.5 ; 29.0,22.5 ; 29.0,23.5 ; 14.0,23.5 ;
       14.0,23.0 ; 12.5,23.0 ; 12.5,23.5 ;  8.2,23.5 ;  8.2,22.0 ; 16.4,22.0 ;
       16.4,16.5 ; 32.0,16.5 ; 32.0,17.5 ; 27.7,17.5 ; 27.7,18.0 ; 27.4,18.0 ;
       27.4,16.0 ;  7.5,16.0 ;  7.5,15.2 ;  6.9,15.2 ;  6.9,16.0 ;  4.2,16.0 ;
        4.2,18.2 ;  5.0,18.2 ;  5.0,14.5 ;  5.8,14.5 ;  5.8,13.8 ;  5.0,13.5 ;
        5.0, 1.0 ;  1.0, 1.0 ];
    N_segments = size(segments, 1);
    step_size = 0.1;    % distance lidar travels between measurements

    pos = [];
    for seg = 1:N_segments-1
        dv = segments(seg+1,:) - segments(seg,:);  % segment direction vector
        dist = sqrt(sum(dv.^2, 2));                % distance of segment 
        num_steps = ceil(dist / step_size);        % number of steps needed
        nx = (1:num_steps).';
        seg_pos = segments(seg,:) + nx .* dv / num_steps;
        seg_pos = seg_pos + 0.1 * randn(size(seg_pos));
        pos = [pos ; seg_pos];
    end

    % Find all randomly generated points that are inside of each structure
    in1 = inpolygon(pos(:,1), pos(:,2), structures{1}(:,1), structures{1}(:,2));
    in2 = inpolygon(pos(:,1), pos(:,2), structures{2}(:,1), structures{2}(:,2));
    in3 = inpolygon(pos(:,1), pos(:,2), structures{3}(:,1), structures{3}(:,2));

    % Keep only valid points
    good = (in1 & ~in2 & ~in3);
    pos = pos(good,:);
end
