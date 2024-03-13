% start the echo server
!python echoserver.py &

% connect to the server
% t = tcpclient('192.168.72.12', 8001);
t = tcpip('192.168.72.12', 31175);
fopen(t);
%connect(t);


% Continuously read messages
size = fread(t,1, "int32");
disp(size);


floats = fread(t,[2,size],'float32');

disp(floats);


% while true
%     % theta_bytes = read(t, 1,'single');
%     % dist_bytes = read(t,1,'single');
%     size = fread(t,1,)
%     theta_bytes = fread(t, 1,'float32');
%     dist_bytes = fread(t,1,'float32');
% 
%     dist = dist_bytes;
%     theta = theta_bytes;
%     fprintf('theta message: %.2f\n', theta);
%     fprintf('dist message: %.2f\n', dist);
%     dist_array = [];
%     theta_array = [];
%     if dist ~= -1
%             dist_array = [dist_array dist];
%             theta_array = [theta_array theta];
%     end

        % Check if the received message matches the condition to break the loop
%      if theta == -1
%             continue;
%      end
% end

% close the connection
%clear t;
fclose(t);

