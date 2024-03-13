% segs = [ structures{1}(1:end-1,:) structures{1}(2:end,:) ; structures{2}(1:end-1,:) structures{2}(2:end,:) ; structures{3}(1:end-1,:) structures{3}(2:end,:) ];
% test_pos = makeTestGrid(0.1, structures);
% [measures,walls] = makeTestData(test_pos, segs);
load('ahmed.mat');
N_testpos = size(test_pos, 1);
N_structures = length(structures);

% t = tcpip('172.20.10.11', 50008);
% fopen(t);

filename = "test475.txt";
xoff = 24.63;
yoff = 22.50;
%angle = 91.5
angle = 0;




% filename = "test425.txt";
% xoff = 24.63;
% yoff = 20.98;
% angle = 89.5;

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
% idx = find(diff(theta_raw));
% idx = idx(1):idx(2);
% theta_raw = data(1,idx);
% distance = data(2,idx);
% quality = data(3,idx);

distance = distance/1000;
theta_fixed = mod((360 - theta_raw) - angle, 360);
% Filter out data points with quality equal to 0
idx = (quality ~= 0 & distance < 6);
theta_fixed = theta_fixed(idx);
distance = distance(idx);

tic
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

X_meas = measures(1,:,:);
Y_meas = measures(2,:,:);

cos_list = cosd(angle_list); 
sin_list = sind(angle_list); 

minmetric = zeros(1, 36);
minidx = zeros(1, 36);
for na = 1:length(angle_list)
    new_counts = circshift(counts, na-1);
    new_mean_distance = circshift(mean_distance, na-1);
    X_coord = new_mean_distance .* cos_list;
    Y_coord = new_mean_distance .* sin_list;
    real_data = [X_coord ; Y_coord];


    metric = squeeze(sum(((X_meas - X_coord).^2 + (Y_meas - Y_coord).^2).*new_counts));

    [minmetric(na),minidx(na)] = min(metric);
end

[~,fidx] = min(minmetric);

pidx = minidx(fidx);
toc


fprintf('The lidar is closest to position %g,%g\n', test_pos(pidx,:));


new_counts = circshift(counts, fidx-1);
new_mean_distance = circshift(mean_distance, fidx-1);
for nx = 1:length(angle_list)
    X_coord = new_mean_distance(nx) .* cosd(angle_list(nx)); 
    Y_coord = new_mean_distance(nx) .* sind(angle_list(nx));
    real_data(:,nx) = [X_coord; Y_coord];
end


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
