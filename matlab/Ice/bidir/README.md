This demo shows how to implement Ice objects in MATLAB, or server-side Ice in MATLAB.

Since Ice for MATLAB is currently client-side only, we actually don't use Ice for MATLAB
for this demo but a manual interfacing using Ice C++ and MATLAB mex.

This demo consists of a MATLAB client that loads a mex library. The mex library uses
Ice C++ to create a servant and register the corresponding proxy with a remote server.
When the remote server calls on this proxy, our MATLAB-mex client dispatches the request
to our MATLAB function.

Requirements
------------

You need:
 - Visual Studio 2015 or 2017
 - MATLAB 2018b or later
 - Configure MATLAB mex with:
    ```
    mex -setup cpp
    ```

Building and running the demo
-----------------------------

 - Build the C++11 Ice/bidir server
 - In a command prompt, start the C++11 Ice/bidir server
 - Start the MATLAB client from this matlab/Ice/bidir folder with:
   ```
   client()
   ```
   
