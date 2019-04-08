
% Runs the test
function client()
    % Ensure the MATLAB session is shared,
    % otherwise the C++ MATLAB engine can't interface with it
    if(matlab.engine.isEngineShared == 0)
        disp('sharing engine...');
        matlab.engine.shareEngine('IceEngine');
    end

    % Build the mex files if they haven't been generated yet
    if(isempty(dir('ClientI.mex*')))
        disp('Building mex file...');
        % Find a compatible Ice for C++ NuGet package
        packagePaths = dir('../../../cpp11/packages/zeroc.ice.v140.*');
        if(isempty(packagePaths))
            disp('Failed to locate Ice for C++ NuGet packages');
        else
            setenv('IceHome', strcat(packagePaths(1).folder, '/', packagePaths(1).name));
            % Compile the slice files
            !%IceHome%/tools/slice2cpp.exe Callback.ice
            % Build the mex file
            !mex ClientI.cpp Callback.cpp -DICE_CPP11_MAPPING -I. -I%IceHome%/build/native/include -L%IceHome%/build/native/lib/x64/Release -lice37++11
        end
    end

    % Send the request through C++11
    ClientI('addClient');
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
