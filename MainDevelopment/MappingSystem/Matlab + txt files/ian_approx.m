tic
% filename = "test475.txt";
% xoff = 24.63;
% yoff = 22.50;
%angle = 91.5
angle = 0;

filename = "test425.txt";
xoff = 24.63;
yoff = 20.98;
% angle = 0;
% 
% filename = "19thjantest2.txt";
% xoff = 24.63;
% yoff =  7.98;
% angle = 0;

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
theta_fixed = mod((360 - theta_raw) - angle, 360);
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
%N_structures = length(structures);


segs = [ structures{1}(1:end-1,:) structures{1}(2:end,:) ; structures{2}(1:end-1,:) structures{2}(2:end,:) ; structures{3}(1:end-1,:) structures{3}(2:end,:) ];
test_pos = load('testPositions.mat').test_pos();
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


%fprintf('The lidar is closest to position %g,%g\n', test_pos(pidx,:));


xa1 = walls(1,pidx) - abs(real_data(1, 1)); %right wall
xa2 = walls(3,pidx) + abs(real_data(1,  19)); %%left wall
ya1 = walls(4,pidx) + abs(real_data(2, 28)); %% bottom wall
ya2 = walls(2,pidx) - abs(real_data(2, 10)); %%top wall


if (real_data(1, 1) == 0 && real_data(1, 19) == 0)
    xapprox = test_pos(pidx,1);
elseif (real_data(1, 1) == 0 && real_data(1, 19) ~= 0)
    xapprox = xa2;
elseif (real_data(1, 1) ~= 0 && real_data(1, 19) == 0)
    xapprox = xa1;
elseif (real_data(1, 1) ~= 0 && real_data(1, 19) ~= 0)
    xapprox = (xa1 + xa2) / 2;
end

if (real_data(2, 28) == 0 && real_data(2, 10) == 0)
    yapprox = test_pos(pidx,2);
elseif (real_data(2, 28) == 0 && real_data(2, 10) ~= 0)
    yapprox = ya2;
elseif (real_data(2, 28) ~= 0 && real_data(2, 10) == 0)
    yapprox = ya1;
elseif (real_data(2, 28) ~= 0 && real_data(2, 10) ~= 0)
    yapprox = (ya1 + ya2) / 2;
end

if angle_list(fidx) == 180
    xa = xoff + xapprox.*cos((angle_list(fidx)/2));
    ya = yoff + yapprox.*sind(-(angle_list(fidx))/2);
else
    xa = xoff + xapprox.*cosd(angle_list(fidx));
    ya = yoff + yapprox.*cosd(angle_list(fidx));
end
% xa = xapprox;
% ya = yapprox;
%fprintf('Our position is actually at %g, %g\n', xa,ya);
dodraw = true;
if angle_list(fidx) == 180
    x_new = xoff + distance.*cosd(theta_fixed+(angle_list(fidx)/2));
    y_new = yoff + distance.*sind(theta_fixed+(angle_list(fidx)/2));
else
    x_new = xoff + distance.*cosd(theta_fixed+angle_list(fidx));
    y_new = yoff + distance.*sind(theta_fixed+angle_list(fidx));
end
if dodraw
    figure(1)
    
    plot(structures{1}(:,1), structures{1}(:,2), 'k', 'LineWidth', 1.5); % Plot walls
    hold on
    plot(structures{2}(:,1), structures{2}(:,2), 'k', 'LineWidth',  1.5); % Plot walls
    plot(structures{3}(:,1), structures{3}(:,2), 'k', 'LineWidth',  1.5); % Plot walls
    plot(x_new,y_new,'r.');
    plot(test_pos(pidx,1),test_pos(pidx,2),'go');
    plot(xa,ya,'mo');
    plot(xoff,yoff,'bo');
    ylim([-5 30]);
    xlim([-5 30]);

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

toc

