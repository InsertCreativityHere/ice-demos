This demo implements the simple [filesystem application][1] shown at the
end of the Javascript client-side mapping chapter.

To run the demo, first you need to start a Manual printer server from
another language mapping (Java, C++, C#, or Python). If you want to get
started quickly, we recommend using the Python server.

If you're running the client in a browser, you need to start the server with
WS as it's default protocol. This is done by setting the Ice.Default.Protocol
option. If you're running the python server this would look like:

```
python server.py --Ice.Default.Protocol=ws
```

After starting the server, open a separate window and start the
client:

```
node Client.js
```

[1]: https://doc.zeroc.com/display/Ice37/Example+of+a+File+System+Client+in+Javascript
