filename = "19thjan";
new_filename = strcat(filename, "_filtered.txt")
filename = strcat(filename, ".txt")

% Read data file, and skip header and blank line at end
loadedData = readlines(filename);
loadedData = loadedData(7:end-1);

% Extract angle and distance
data = cellfun(@(S) sscanf(S, "%*[^:]: %g %*[^:]: %g %*[^:]: %g"), ...
                loadedData, 'UniformOutput', false);
data = reshape(cell2mat(data), 3, []);
theta = data(1,:);
distance = data(2,:);
quality = data(3,:);

% Filter out invalid data
validIndices = quality ~= 0;
theta = theta(validIndices);
distance = distance(validIndices);

% Reconstruct lines with filtered data
filteredLines = arrayfun(@(t, d) sprintf("theta: %g distance: %g", t, d), theta, distance, 'UniformOutput', false);

% Open a new file for writing
fid = fopen(new_filename, 'w'); 

% Check if file is opened successfully
if fid == -1
    error('Failed to open file %s for writing.', new_filename);
end

% Write each line to the new file
for i = 1:length(filteredLines)
    fprintf(fid, "%s\n", filteredLines{i});
end

% Close the file
fclose(fid);

fprintf('Filtered data saved to %s\n', new_filename);

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
