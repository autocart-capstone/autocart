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
segs = [ structures{1}(1:end-1,:) structures{1}(2:end,:) ; structures{2}(1:end-1,:) structures{2}(2:end,:) ; structures{3}(1:end-1,:) structures{3}(2:end,:) ];
test_pos = makeTestGrid(0.1, structures);
[measures,walls] = makeTestData(test_pos, segs);
save('ahmed.mat','measures','walls','test_pos');
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




