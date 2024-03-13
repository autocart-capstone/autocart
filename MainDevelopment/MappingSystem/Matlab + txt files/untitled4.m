% Define the port to listen on
server_port = 8081;  % Replace with the port used by the C++ program
% Create TCP/IP object as a server
t = tcpip('0.0.0.0', server_port, 'NetworkRole', 'server');
% set(t, 'InputBufferSize', 12); % Set the size of the receive buffer

% Start listening for connections
fopen(t);

% Accept incoming connection
disp('Waiting for connection...');
while ~strcmp(t.Status, 'open')
    pause(0.1);
end
disp('Connection established.');

% Receive data
disp('Receiving data...');
while true
    data_received = fread(t, 12);
    %disp(data_received);
    num_elements = numel(data_received) / 4; % Assuming int is 4 bytes
    received_struct.x = typecast(uint8(data_received(1:4)), 'single');
    received_struct.y = typecast(uint8(data_received(5:8)), 'single');
    received_struct.z = typecast(uint8(data_received(9:end)), 'int32');
   % fprintf('Angle is %.2f', received_struct.x);
   %array = [array received_struct.x];
    %disp('HELLO');
end


% Process received data
% You can process the received data here

% Close connection
fclose(t);
disp('Connection closed.');