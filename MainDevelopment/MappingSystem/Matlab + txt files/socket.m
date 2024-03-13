% start the echo server
!python echoserver.py &

%%set up server
server = tcpserver('0.0.0.0',5008);


% connect to the server
t = tcpclient('172.20.10.11', 50008);
fopen(t);

% write a message

% if t.BytesAvailable > 0
%     bytes3 = fread(t, [1, t.BytesAvailable]);
%     char(bytes3)
% end

% read the echo
for i = 1:20
    fwrite(t,[sprintf('%g',i) newline]);
end

pause(1);
fwrite(t,'matcha');


lastReceivedTime = tic;
while true
    
    bytes3 = fread(t, [1, sizeof(data)]);
    if ~isempty(bytes3)
        rcvd = char(bytes3);
        fprintf('Rcvd msg: %s',rcvd);
        data = sscanf(rcvd, "%*[^:]: %g %*[^:]: %g %*[^:]: %g %*[^\n]");
        distance = data(1);
        theta = data(2);
        quality = data(3);

        disp(data);
        % str = native2unicode(rcvd,'UTF-8');
        % fprintf('Distance: %g, theta: %g, quality: %g\n', str(:,2), str(:,5),str(:,8));
    end
        if toc(lastReceivedTime) > 10
            break;

        end
end
% bytes3 = fread(t, [1, t.BytesAvailable]);
% char(bytes3)
% 
% 


% close the connection
fclose(t);

