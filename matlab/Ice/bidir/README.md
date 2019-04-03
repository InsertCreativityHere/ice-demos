This demo shows how to use [bidirectional connections][1] for callbacks in
MATLAB by interfacing with a C++ runtime. This is typically used if the
server cannot open a connection to the client to send callbacks, for example,
because firewalls block incoming connections to the client.

This demo uses the MATLAB C++ Engine API, which is only available in MATLAB version 2018b, or
higher. This demo also requires you to of already built the C++11 demos, and have MATLAB mex configured.
To build the C++11 demos, see README.md in the ice-demos/cpp11 directory, and to configure mex
for C++, run the following command from the MATLAB command line:

```
mex -setup cpp
```

Mex requires you to have a MATLAB supported C++ compiler installed; For a list of which compilers are
supported by your version of MATLAB, check [here][2]. This demo doesn't require Ice for MATLAB.

This demo currently supports only client-side functionality, therefore you
must use a bidir server from another language mapping. If you want to get
started quickly, we recommend using the Python server.

After starting the server, navigate to the directory containing this demo in MATLAB, and run the demo:

```
client();
```

[1]: https://doc.zeroc.com/display/Ice37/Bidirectional+Connections
[2]: https://www.mathworks.com/support/requirements/previous-releases.html
