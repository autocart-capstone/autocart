filename = "new.txt";

% Read data file, and skip header and blank line at end
loadedData = readlines(filename);
loadedData = loadedData(7:end-1);

% Extract angle and distance
data = cellfun(@(S) sscanf(S, "%*[^:]: %g %*[^:]: %g%*[^\n]"), ...
                    loadedData, UniformOutput=false);
data = reshape(cell2mat(data), 2, []);
theta = data(1,:);
distance = data(2,:);

% Convert to Cartesian coordinates
x = distance .* cos(theta*pi/180);
y = distance .* sin(theta*pi/180);

% Find start of each revolution
starts = [1 find(diff(theta) < 0) length(theta)];

% Group data by revolution
for i = 1:length(starts)-1
    revData(i).rev = i;
    revData(i).x = x(starts(i):starts(i+1)-1);
    revData(i).y = y(starts(i):starts(i+1)-1);
end

% Create a new figure for the animation
figure(1);

for i = 1:length(revData)
    clf
    hold on

    % Show previous revolutions
    for k=1:i-1
        plot(revData(k).x, revData(k).y, 'b.')
    end

    % Show current revolution
    plot(revData(i).x, revData(i).y, 'r.')

    % Show LIDAR position
    plot(0, 0, 'go')
    hold off

    axis('equal')
    title(sprintf('Revolution %d', i))
    drawnow;

    % Pause to create the animation effect
    pause
end

revolutions = length(starts) - 1;
fprintf("Total Revolutions: %d\n", revolutions);
