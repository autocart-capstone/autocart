filename = "19thjan.txt";
filename2 = '19thjantest2.txt';

% Read data file and preprocess
loadedData = readlines(filename);
loadedData = loadedData(7:end-1);
data = cellfun(@(S) sscanf(S, "%*[^:]: %g %*[^:]: %g %*[^:]: %g"), ...
                loadedData, 'UniformOutput', false);
data = reshape(cell2mat(data), 3, []);
theta = data(1,:);
distance = data(2,:);
quality = data(3,:);

% Sort data by angle

% Filter out invalid data
validIndices = quality ~= 0;
theta = theta(validIndices);
distance = distance(validIndices);

% Convert to Cartesian coordinates
x = distance .* cos(theta*pi/180);
y = -distance .* sin(theta*pi/180);

%idx = (distance > 6500);
%x(idx) = [];
%y(idx) = [];
% Plot x and y
figure(1);
plot(0, 0, 'go');
hold on
axis equal;

idx = (distance > 6500);
x(idx) = [];
y(idx) = [];
pointDistances = sqrt(diff(x).^2 + diff(y).^2);
x_new = x(pointDistances < 400);
y_new = y(pointDistances < 400);
x_all = [];
y_all = [];
for i = 1:numel(x_new) - 1
    pointDistance2 = sqrt((x_new(i+1) - x_new(i)).^2 + (y_new(i+1) - y_new(i)).^2);
    if pointDistance2 < 400
        x_all = [x_all x_new(i)];
        y_all = [y_all y_new(i)];
        
    else
        if ~isempty(x_all)
            plot(x_all,y_all,'.');
            p = linortfit2(x_all,y_all);
            x_fit2 =linspace(min(x_all), max(x_all), 100);
            y_fit2 = p(1)*x_fit2 + p(2);
            plot(x_fit2,y_fit2,'m-');

            x_all = [];
            y_all = [];
        end
    end
end
% Plot all points in blue
hold off

function [p] = linortfit2(xdata, ydata)
% LINORTFIT2  Fit a line to data by ORTHOGONAL least-squares.
%    P = LINORTFIT2(X,Y) finds the coefficients of a 1st-order polynomial
%    that best fits the data (X,Y) in an ORTHOGONAL least-squares sense.
%    Consider the line P(1)*t + P(2), and the minimum (Euclidean) distance
%    between this line and each datapoint [X(i) Y(i)] -- LINORTFIT2 finds
%    P(1) and P(2) such that the sum of squared distances is minimized.
if ~isequal(size(xdata), size(ydata))
    error('linortfit2:XYSizeMismatch',...
          'X and Y vectors must be the same size.');
end
[N,C] = linortfitn([xdata(:) ydata(:)]);
% The hyperplane given by N * [x; y] + C == 0 is optimal.
% Convert to the form  y = p(1)*x + p(2), just like polyfit(xdata,ydata,1).
p = - [N(1)  C] / N(2);
end

function [hyperplane_normal, hyperplane_offset] = linortfitn(data)
% LINORTFITN  Fit a line to data by ORTHOGONAL least-squares.
%    [N,C] = LINORTFITN(DATA) finds the coefficients of a hyperplane (in
%    Hessian normal form) that best fits the data in an ORTHOGONAL
%    least-squares sense.  Consider the hyperplane
%       H = {x | dot(N,x) + C == 0},
%    and the minimum (Euclidean) distance between this hyperplane and each
%    datapoint DATA(i,:) -- LINORTFITN finds N and C such that the sum of
%    squared distances is minimized.
[M,N] = size(data);
if M <= N,
    error('linortfitn:DegenerateProblem',...
        'There are fewer datapoints than dimensions: the data is perfectly fit by a hyperplane.');
end
[U,S,V] = svd(data - repmat(mean(data),M,1), 0);
hyperplane_normal = V(:,end);
hyperplane_offset = - mean(data * hyperplane_normal);
end