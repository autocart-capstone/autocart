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

save('ahmed.mat','measures','walls')