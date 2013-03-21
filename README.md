leapOSC
=======

Leap Motion controller data output via Open Sound Control (OSC). Based upon Sample.cpp from Leap SDK, with oscpack integrated to facilitate sending of OSC packets over UDP protocol.

Working executable and supporting files can be found in /bin. 
OSC output is to 127.0.0.1, port 7000.
Requires the Leap Motion SDK v0.7.3, LeapApp (websocket server) running, and a Leap Motion device connected to your computer.

Compiling from source requires Microsoft Visual Studio 2010, supporting files from the SDK, and addition of winmm.lib, ws2_32.lib and leapd.lib to the projects linker.
