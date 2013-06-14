leapOSC v0.5 - now includes gesture support

Leap Motion controller data output via Open Sound Control (OSC). Based upon Sample.cpp from Leap SDK, with oscpack integrated to facilitate sending of OSC packets over UDP protocol.

Working executable and supporting files can be found in /bin. OSC output is to 127.0.0.1, port 7000. Requires the Leap Motion SDK v0.8.0, Leap Application running with background apps enabled, and a Leap Motion device connected to your computer.

Compiling from source requires Microsoft Visual Studio 2012 Express, supporting files from the SDK, and addition of winmm.lib and ws2_32.lib to the projects linker.

Currently works with up to 4 hands and 20 fingers(5 fingers per hand). Outputs 330 data values, 5 for the frame data, 75 per hand and 25 for the gestures.

OSC data output is at least 120FPS. Channel names have been optimised to fit all data into an 8KB packet.


TO DO: Configuration file for settings, Leap Motion data viewer - CLI or GUI based.

