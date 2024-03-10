%!python echoserver.py &

% t = tcpip('172.20.10.11', 50008);
% fopen(t);

filename = "test475.txt";
xoff = 24.63;
yoff = 22.50;
%angle = 91.5
angle = 0;

%filename = "test425.txt";
%xoff = 24.63;
%yoff = 20.98;
%angle = 89.5

%filename = "19thjantest2.txt";
%xoff = 24.63;
%yoff =  7.98;
%angle = 0;

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
distance = distance/1000;
theta_fixed = mod((360 - theta_raw) - 91.5, 360);
% Filter out data points with quality equal to 0
idx = (quality ~= 0 & distance < 6);
theta_fixed = theta_fixed(idx);
distance = distance(idx);


% Sort theta values
[theta_fixed, idx] = sort(theta_fixed);
distance = distance(idx);

%%Here is what to do now, We only really care about these 4 absolute
%%points, we need to care at which angle this happens for the simmulated
%%test position, hence why the wall array is set up as is
%%what to do now is to configure all the test_pos and then just compare
%%these 4 points
%%Ex xa1 = walls(1,pidx) + abs(Real_Walls(3, 1)); %left wall
    % xa2 = walls(3,pidx) - abs(real_data(2,  1)); %%right wall
    % ya1 = walls(4,pidx) + abs(real_data(1, 1)); %% bottom wall
    %ya2 = walls(2,pidx) - abs(real_data(4, 1)); %%top wall
structures = {
 [  0.00, 0.00 ;  0.00, 2.13 ;  3.96, 2.13 ;  3.96,18.50 ;  5.81,18.50 ;
    5.81,17.57 ; 15.79,17.57 ; 15.79,17.57 ; 15.79,21.99 ;  8.07,21.99 ;
    8.07,24.07 ; 12.64,24.07 ; 12.64,23.46 ; 13.84,23.46 ; 13.84,24.07 ;
   24.05,24.07 ; 24.05,24.17 ; 24.96,24.17 ; 24.96,24.07 ;
   29.53,24.07 ; 29.53,22.09 ; 25.40,22.09 ; 25.40,17.82 ; 27.33,17.82 ;
   27.33,18.18 ; 27.94,18.18 ; 27.94,17.82 ; 32.44,17.82 ; 32.44,15.38 ;
   25.40,15.38 ; 25.40, 0.00 ; 0.00, 0.00 ] ;
 [  5.81, 1.83 ;  5.81,13.67 ;  6.57,13.67 ;  6.57,14.67 ;  5.81,14.67 ;
    5.81,15.70 ;  7.32,15.70 ;  7.32,14.94 ;  8.32,14.94 ;  8.32,15.70 ;
   23.54,15.70 ; 23.54,14.15 ; 22.79,14.15 ; 22.79,12.82 ; 23.54,12.82 ;
   23.54, 1.83 ; 22.04, 1.83 ; 22.04, 2.59 ; 21.01, 2.59 ; 21.01, 1.83 ;
    5.81, 1.83 ] ;
 [ 17.15,21.99 ; 23.56,21.99 ; 23.56,19.33 ; 24.00,19.33 ; 24.00,17.57 ;
   17.15,17.57 ; 17.15,21.99 ]
};
N_structures = length(structures);


segs = [ structures{1}(1:end-1,:) structures{1}(2:end,:) ; structures{2}(1:end-1,:) structures{2}(2:end,:) ; structures{3}(1:end-1,:) structures{3}(2:end,:) ];
test_pos = makeTestGrid(0.1, structures);
[measures,walls] = makeTestData(test_pos, segs);
N_testpos = size(test_pos, 1);

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
    for nx = 1:length(angle_list)
        X_coord = new_mean_distance(nx) .* cosd(angle_list(nx)); 
        Y_coord = new_mean_distance(nx) .* sind(angle_list(nx));
        real_data(:,nx) = [X_coord; Y_coord];
    end

    weights = new_counts ./ sum(new_counts);

    metric = squeeze(sum(sum((measures - real_data).^2).*weights));

    [minmetric(na),minidx(na)] = min(metric);
end

[~,fidx] = min(minmetric);

pidx = minidx(fidx);


fprintf('The lidar is closest to position %g,%g\n', test_pos(pidx,:));


xa1 = walls(1,pidx) - abs(real_data(1, 1)); %right wall
xa2 = walls(3,pidx) + abs(real_data(1,  19)); %%left wall
ya1 = walls(4,pidx) + abs(real_data(2, 28)); %% bottom wall
ya2 = walls(2,pidx) - abs(real_data(2, 10)); %%top wall


if (real_data(1, 1) == 0 && real_data(1, 19) == 0)
    disp("A1");
    xapprox = test_pos(pidx,1);
elseif (real_data(1, 1) == 0 && real_data(1, 19) ~= 0)
    disp("B1");

    xapprox = xa2;
elseif (real_data(1, 1) ~= 0 && real_data(1, 19) == 0)
    disp("C1");
    xapprox = xa1;
elseif (real_data(1, 1) ~= 0 && real_data(1, 19) ~= 0)
    disp("D1");
    xapprox = (xa1 + xa2) / 2;
end

if (real_data(2, 28) == 0 && real_data(2, 10) == 0)
    disp("E2");
    yapprox = test_pos(pidx,2);
elseif (real_data(2, 28) == 0 && real_data(2, 10) ~= 0)
    disp("F2");
    yapprox = ya2;
elseif (real_data(2, 28) ~= 0 && real_data(2, 10) == 0)
    disp('G2');  
    yapprox = ya1;
elseif (real_data(2, 28) ~= 0 && real_data(2, 10) ~= 0)
    disp("Z2");
    yapprox = (ya1 + ya2) / 2;
end

xa = xapprox;
ya = yapprox;
% tic
% 
% for i = 1:20
%     message = sprintf('[%.2f, %.2f]', xa, ya);
%     fwrite(t,message);
% end 
% 
% message1 = sprintf('%g %g', test_pos(pidx,1), test_pos(pidx,2));
% fwrite(t,message1);
% toc
% bytes3 = fread(t, [1, t.BytesAvailable]);
% char(bytes3)
% fclose(t);

dodraw = true;
x_new = xoff + distance.*cosd(theta_fixed+angle_list(fidx));
y_new = yoff + distance.*sind(theta_fixed+angle_list(fidx));
if dodraw
    figure(1)
    plot(structures{1}(:,1), structures{1}(:,2), 'k'); % Plot walls
    hold on
    plot(structures{2}(:,1), structures{2}(:,2), 'k'); % Plot walls
    plot(structures{3}(:,1), structures{3}(:,2), 'k'); % Plot walls
    plot(x_new,y_new,'r.');
    plot(test_pos(pidx,1),test_pos(pidx,2),'go');
    plot(xa,ya,'mo');
    plot(xoff,yoff,'bo');

    in1 = inpolygon(x_new, y_new, structures{1}(:,1), structures{1}(:,2));
    in2 = inpolygon(x_new, y_new, structures{2}(:,1), structures{2}(:,2));
    in3 = inpolygon(x_new, y_new, structures{3}(:,1), structures{3}(:,2));
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


