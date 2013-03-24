leapOSC v0.4

Leap Motion controller data output via Open Sound Control (OSC). Based upon Sample.cpp from Leap SDK, with oscpack integrated to facilitate sending of OSC packets over UDP protocol.

Working executable and supporting files can be found in /bin. OSC output is to 127.0.0.1, port 7000. Requires the Leap Motion SDK v0.7.5, LeapApp (websocket server) running, and a Leap Motion device connected to your computer.

Compiling from source requires Microsoft Visual Studio 2012 Express, supporting files from the SDK, and addition of winmm.lib, ws2_32.lib and leapd.lib to the projects linker.

Currently works with up to 4 hands and 20 fingers(5 fingers per hand). Outputs 305 data values, 5 for the frame data and 75 per hand.

OSC data output is at least 120FPS. Channel names have been optimised to fit all data into a 8KB packet.

Gesture support not yet implemented, but will be on the next build.



TO DO:
Add gesture support, configuration file for settings, Leap Motion data viewer - CLI or GUI based.

