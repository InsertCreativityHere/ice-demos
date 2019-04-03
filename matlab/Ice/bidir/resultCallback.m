
% This is the function called by the C++11 callback
function res = resultCallback(index, value)
    disp([num2str(index), ':   Value received: ', num2str(value)]);
    res = 0;
end
