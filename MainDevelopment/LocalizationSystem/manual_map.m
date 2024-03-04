structure1 = [0, 0; 0, 2.13; 3.96,2.13;3.96,18.50; 5.24,18.50;5.24,17.57;15.79,17.57;15.79,17.57;15.79,21.70;8.07,21.70;8.07,24.07;12.64,24.07;12.64,23.46;13.84,23.46;13.84,24.07;29.52,24.07;29.52,22.09;25.4,22.09;25.4,17.82;27.33,17.82;27.33,18.18;27.94,18.18;27.94,17.82;32.44,17.82
    32.44,15.94;25.4,15.94;25.4,0;0,0];
structure2 = [5.25,1.83;5.25,13.67;6,13.67;6,14.67;5.25,14.67;5.25,15.70;6.75,15.70;6.75,14.94;7.75,14.94;7.75,15.7;23.54,15.70;23.54,14.15;22.79,14.15;22.79,12.82;23.54,12.82;23.54,1.83;22.04,1.83;22.04,2.59;21.01,2.59;21.01,1.83;5.25,1.83];
structure3 = [17.15,21.7;23.5,21.7;23.5,19.11;24,19.11;24,17.57;17.15,17.57;17.15,21.7];
test_pos = [5 18; 5 1 ; 5 16.5;10 23; 13 23; 16 23; 19 23;22 23;25 23; 28 23; 7.25 16.5; 10 16.5; 13 16.5; 16 16.5; 19 16.5; 22 16.5; 25 16.5; 27.2 16.5; 30.5 16.5;16.5 20;24.5 20;24.5 15; 24.5 13.5; 24.5 10.5; 24.5 7.5; 24.5 4.5; 24.5 1; 5 14; 5 11; 5 8; 5 5; 5 2.5; 2 1; 8 1; 11 1; 14 1; 17 1; 19 1; 21.25 1; 23 1];
N_positions = size(test_pos, 1);

measures = zeros(2, 34, N_positions);


for np = 1:N_positions

    lidar_pos = test_pos(np,:);

    % Plot the floor plan
    figure(1)
    plot(structure1(:,1), structure1(:,2), 'k'); % Plot walls
    hold on
    plot(structure2(:,1),structure2(:,2),'k');
    plot(structure3(:,1),structure3(:,2),'k');
    axis equal;
    % Iterate over angles
    angle_list = 0:10:359;
    for na = 1:length(angle_list)
        angle_deg = angle_list(na);

        % Convert angle from degrees to radians
        angle_rad = deg2rad(angle_deg);
        
        % Calculate endpoint coordinates
        x_end = 50 * cos(angle_rad) + lidar_pos(1); % 50 meters away in the x direction
        y_end = 50 * sin(angle_rad) + lidar_pos(2); % 50 meters away in the y direction
        
        % Find the intersection points
        [x_intersect1, y_intersect1] = polyxpoly([lidar_pos(1),x_end],[lidar_pos(2),y_end], structure1(:,1), structure1(:,2));
        [x_intersect2, y_intersect2] = polyxpoly([lidar_pos(1),x_end],[lidar_pos(2),y_end], structure2(:,1), structure2(:,2));
        [x_intersect3, y_intersect3] = polyxpoly([lidar_pos(1),x_end],[lidar_pos(2),y_end], structure3(:,1), structure3(:,2));

        x_intersect = [ x_intersect1 ; x_intersect2 ; x_intersect3];
        y_intersect = [ y_intersect1 ; y_intersect2 ; y_intersect3];
        
        distance = sqrt((x_intersect-lidar_pos(1)).^2 + (y_intersect-lidar_pos(2)).^2);
        [~,idx] = min(distance);
        x_intersect = x_intersect(idx);
        y_intersect = y_intersect(idx);

        %if (np == 33)
        %plot(x_intersect, y_intersect, 'r.');
        %plot([lidar_pos(1) x_intersect], [lidar_pos(2) y_intersect], 'm');
        %end

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


    % Plot the lidar position
    plot(lidar_pos(1), lidar_pos(2), 'go');

    xlabel('X-axis (m)');
    ylabel('Y-axis (m)');
    title('Map'); 
    %drawnow
    %pause(0.1)
    
    %lidar_pos(1) = lidar_pos(1) + 0.1;
end




lidar_pos = [4,18];

real_data = zeros(2, 36);

% Iterate over angles
angle_list = 0:10:359;
for na = 1:length(angle_list)
    angle_deg = angle_list(na);

    % Convert angle from degrees to radians
    angle_rad = deg2rad(angle_deg);

    % Calculate endpoint coordinates
    x_end = 50 * cos(angle_rad) + lidar_pos(1); % 5 meters away in the x direction
    y_end = 50 * sin(angle_rad) + lidar_pos(2); % 5 meters away in the y direction

    % Find the intersection points
    [x_intersect1, y_intersect1] = polyxpoly([lidar_pos(1),x_end],[lidar_pos(2),y_end], structure1(:,1), structure1(:,2));
    [x_intersect2, y_intersect2] = polyxpoly([lidar_pos(1),x_end],[lidar_pos(2),y_end], structure2(:,1), structure2(:,2));
    [x_intersect3, y_intersect3] = polyxpoly([lidar_pos(1),x_end],[lidar_pos(2),y_end], structure3(:,1), structure3(:,2));

    x_intersect = [ x_intersect1 ; x_intersect2 ;x_intersect3];
    y_intersect = [ y_intersect1 ; y_intersect2 ;y_intersect3];

    distance = sqrt((x_intersect-lidar_pos(1)).^2 + (y_intersect-lidar_pos(2)).^2);
    [~,idx] = min(distance);
    x_intersect = x_intersect(idx);
    y_intersect = y_intersect(idx);

    real_data(:,na) = [x_intersect ; y_intersect] - lidar_pos.';
    plot([lidar_pos(1) x_intersect],[lidar_pos(2) y_intersect],'r');
    

end

plot(lidar_pos(1),lidar_pos(2),'yo');
metric = squeeze(sum(sum((measures - real_data).^2)));
[~,idx] = min(metric);
fprintf('The lidar is closest to position %g,%g\n', test_pos(idx,:));

[p,idx2] = sort(metric);
fprintf('%g %g\n',test_pos(idx2(1),:));
%disp(p);
tp = test_pos(idx2(1), :);
plot(tp(1), tp(2), 'kx')

weight_percentage_p1 = p(2) / (p(1) + p(2)); % Percentage of p(1)
weight_percentage_p2 = p(1) / (p(1) + p(2)); % Percentage of p(2)


xapprox = weight_percentage_p1 * test_pos(idx2(1),1) + weight_percentage_p2 * test_pos(idx2(2),1); %%percentage of p(1) * test_pos associated with that-- in x
yapprox = weight_percentage_p1 * test_pos(idx2(1),2) + weight_percentage_p2 * test_pos(idx2(2),2); %%percentage of p(1) * test_pos associated with that-- in y



fprintf('Weight percentage of p(1): %.2f%%\n', weight_percentage_p1 * 100);
plot(test_pos(idx2(1),1),test_pos(idx2(1),2),'go');

pidx = idx2(1);


xapprox1 = leftwall(pidx) + abs(real_data(1, 19));
xapprox2 = rightwall(pidx) - abs(real_data(1,1));
yapprox1 = bottomwall(pidx) + abs(real_data(2, 28));
yapprox2 = topwall(pidx) - abs(real_data(2,10));
xapprox = (xapprox1+xapprox2)/2;
yapprox = (yapprox1+yapprox2)/2;


approx_pos = [xapprox, yapprox];
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
