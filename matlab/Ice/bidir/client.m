
% Runs the test
function client()
    % Ensure the MATLAB session is shared,
    % otherwise the C++ MATLAB engine can't interface with it
    if(matlab.engine.isEngineShared == 0)
        disp('sharing engine...');
        matlab.engine.shareEngine('IceEngine');
    end

    % Find a compatible Ice for C++ NuGet package
    packagePaths = dir('../../../cpp11/packages/zeroc.ice.v140.*');
    if(isempty(packagePaths))
        disp('Failed to locate Ice for C++ NuGet packages');
        return;
    else
        % Add the ice bin directory to PATH for the session.
        iceHome = strcat(packagePaths(1).folder, '/', packagePaths(1).name);
        setenv('PATH', strcat(getenv('PATH'), ';', iceHome, '/build/native/bin/x64/Release'));
    end

    % Build the mex files if they haven't been generated yet
    if(isempty(dir('ClientI.mex*')))
        disp('Building mex file...');
        setenv('IceHome', iceHome);
        % Compile the slice files
        !%IceHome%/tools/slice2cpp.exe Callback.ice
        % Build the mex file
        !mex ClientI.cpp Callback.cpp -DICE_CPP11_MAPPING -I. -I%IceHome%/build/native/include -L%IceHome%/build/native/lib/x64/Release -lice37++11
    end

    % Send the request through C++11
    if(ClientI('addClient') ~= 0)
       disp("Failed to add client... Exiting.");
       return;
    end
    disp('Running for 10 seconds...');

    % Let the client run for 10 seconds
    delayTimer = timer;
    delayTimer.startDelay = 10;
    delayTimer.timerFcn = @delayTimerFunc;
    start(delayTimer);
end

function delayTimerFunc(timerObj, timerEvent)
    disp('Destroying communicator...');
    ClientI('destroy');
    stop(timerObj);
    delete(timerObj);
end
