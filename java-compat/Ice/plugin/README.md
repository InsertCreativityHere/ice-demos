This demo illustrates how to write and configure a simple Ice [plug-in][1]
as well as an Ice [Logger plug-in][2].

To run the demo, first start the server:

```
java -jar build/libs/server.jar
```

In a separate window, start the client:

```
java -jar build/libs/client.jar
```

Both the client and server use a custom logger which is loaded as
a logger plugin. The server also uses a plugin to implement the
servant for this demo.

Please review the client and server configuration files to see the
plug-in configuration.

[1]: https://doc.zeroc.com/display/Ice37/Plug-in+Facility
[2]: https://doc.zeroc.com/display/Ice37/Logger+Plug-ins
