// leapOSC v0.1 by Morphic Creative

//Includes and namespace for Leap
#include <iostream>
#include "Leap.h"
using namespace Leap;

// Includes and defines for oscpack
#include "include/OscOutboundPacketStream.h"
#include "include/UdpSocket.h"
#define ADDRESS "127.0.0.1"
#define PORT 7000
#define OUTPUT_BUFFER_SIZE 2048
using namespace std;

class SampleListener : public Listener {
  public:
    virtual void onInit(const Controller&);
    virtual void onConnect(const Controller&);
    virtual void onDisconnect(const Controller&);
    virtual void onExit(const Controller&);
    virtual void onFrame(const Controller&);
};

void SampleListener::onInit(const Controller& controller) {
  std::cout << "Initialized" << std::endl;
}

void SampleListener::onConnect(const Controller& controller) {
  std::cout << "Connected" << std::endl;
}

void SampleListener::onDisconnect(const Controller& controller) {
  std::cout << "Disconnected" << std::endl;
}

void SampleListener::onExit(const Controller& controller) {
  std::cout << "Exited" << std::endl;
}

void SampleListener::onFrame(const Controller& controller) {

  // Get the most recent frame
  const Frame frame = controller.frame();

  // Get the hands
  const Hand firsthand = frame.hands()[0];
  const Hand secondhand = frame.hands()[1];

  // Check if the hands have any fingers
  const FingerList firstfingers = firsthand.fingers();
  const FingerList secondfingers = secondhand.fingers();

  // Calculate both hand's average finger tip position
      Vector firstavgPos;
      for (int i = 0; i < firstfingers.count(); ++i) {
        firstavgPos += firstfingers[i].tipPosition();
      }
      firstavgPos /= (float)firstfingers.count();

      Vector secondavgPos;
      for (int i = 0; i < secondfingers.count(); ++i) {
        secondavgPos += secondfingers[i].tipPosition();
      }
      secondavgPos /= (float)secondfingers.count();

  // Get both hand's normal vector and direction
  const Vector firstnormal = firsthand.palmNormal();
  const Vector firstdirection = firsthand.direction();
  const Vector secondnormal = secondhand.palmNormal();
  const Vector seconddirection = secondhand.direction();

  // Output Leap data via OSC
    UdpTransmitSocket transmitSocket( IpEndpointName( ADDRESS, PORT ) );    
    char buffer[OUTPUT_BUFFER_SIZE];
    osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );   
    p << osc::BeginBundleImmediate
        << osc::BeginMessage( "/Controller:" )				//OSC CHANNEL NAMES AS FOLLOWS															
		<< frame.id()										//Controller:1
		<< frame.timestamp()								//Controller:2
		<< frame.hands().count()							//Controller:3
		<< frame.fingers().count()							//Controller:4
		<< frame.tools().count()							//Controller:5
		<< osc::EndMessage
        << osc::BeginMessage( "/FirstHand:" )
		<< firstfingers.count()								//FirstHand:1
		<< firsthand.direction().x							//FirstHand:2
		<< firsthand.direction().y							//FirstHand:3
		<< firsthand.direction().z							//FirstHand:4
		<< firsthand.sphereRadius()							//FirstHand:5
		<< firstdirection.pitch() * RAD_TO_DEG				//FirstHand:6
		<< firstdirection.roll() * RAD_TO_DEG				//FirstHand:7
		<< firstdirection.yaw() * RAD_TO_DEG				//FirstHand:8
		<< firsthand.palmPosition().x						//FirstHand:9
		<< firsthand.palmPosition().y						//FirstHand:10
		<< firsthand.palmPosition().z						//FirstHand:11
		<< firsthand.palmPosition().pitch() * RAD_TO_DEG	//FirstHand:12
		<< firsthand.palmPosition().roll() * RAD_TO_DEG		//FirstHand:13
		<< firsthand.palmPosition().yaw() * RAD_TO_DEG		//FirstHand:14
		<< firsthand.palmVelocity().x						//FirstHand:15
		<< firsthand.palmVelocity().y						//FirstHand:16
		<< firsthand.palmVelocity().z						//FirstHand:17
		<< firsthand.palmVelocity().pitch() * RAD_TO_DEG	//FirstHand:18
		<< firsthand.palmVelocity().roll() * RAD_TO_DEG		//FirstHand:19
		<< firsthand.palmVelocity().yaw() * RAD_TO_DEG		//FirstHand:20
		<< firsthand.palmNormal().x							//FirstHand:21
		<< firsthand.palmNormal().y							//FirstHand:22
		<< firsthand.palmNormal().z							//FirstHand:23
		<< firstnormal.pitch() * RAD_TO_DEG					//FirstHand:24
		<< firstnormal.roll() * RAD_TO_DEG					//FirstHand:25
		<< firstnormal.yaw() * RAD_TO_DEG					//FirstHand:26
		<< firstavgPos.x									//FirstHand:27
		<< firstavgPos.y									//FirstHand:28
		<< firstavgPos.z									//FirstHand:29
		<< firstavgPos.pitch() * RAD_TO_DEG					//FirstHand:30
		<< firstavgPos.roll() * RAD_TO_DEG					//FirstHand:31
		<< firstavgPos.yaw() * RAD_TO_DEG					//FirstHand:32
		<< firstfingers[0].tipPosition().x					//FirstHand:33
		<< firstfingers[0].tipPosition().y					//FirstHand:34
		<< firstfingers[0].tipPosition().z					//FirstHand:35
		<< firstfingers[1].tipPosition().x					//FirstHand:36
		<< firstfingers[1].tipPosition().y					//FirstHand:37
		<< firstfingers[1].tipPosition().z 					//FirstHand:38
		<< firstfingers[2].tipPosition().x					//FirstHand:39
		<< firstfingers[2].tipPosition().y					//FirstHand:40
		<< firstfingers[2].tipPosition().z					//FirstHand:41
		<< firstfingers[3].tipPosition().x					//FirstHand:42
		<< firstfingers[3].tipPosition().y					//FirstHand:43
		<< firstfingers[3].tipPosition().z					//FirstHand:44
		<< firstfingers[4].tipPosition().x					//FirstHand:45
		<< firstfingers[4].tipPosition().y					//FirstHand:46
		<< firstfingers[4].tipPosition().z					//FirstHand:47
		<< osc::EndMessage
        << osc::BeginMessage( "/SecondHand:" )
		<< secondfingers.count()							//SecondHand:1
		<< secondhand.direction().x							//SecondHand:2
		<< secondhand.direction().y							//SecondHand:3
		<< secondhand.direction().z							//SecondHand:4
		<< secondhand.sphereRadius()						//SecondHand:5
		<< seconddirection.pitch() * RAD_TO_DEG				//SecondHand:6
		<< seconddirection.roll() * RAD_TO_DEG				//SecondHand:7
		<< seconddirection.yaw() * RAD_TO_DEG				//SecondHand:8
		<< secondhand.palmPosition().x						//SecondHand:9
		<< secondhand.palmPosition().y						//SecondHand:10
		<< secondhand.palmPosition().z						//SecondHand:11
		<< secondhand.palmPosition().pitch() * RAD_TO_DEG	//SecondHand:12
		<< secondhand.palmPosition().roll() * RAD_TO_DEG	//SecondHand:13
		<< secondhand.palmPosition().yaw() * RAD_TO_DEG		//SecondHand:14
		<< secondhand.palmVelocity().x						//SecondHand:15
		<< secondhand.palmVelocity().y						//SecondHand:16
		<< secondhand.palmVelocity().z						//SecondHand:17
		<< secondhand.palmVelocity().pitch() * RAD_TO_DEG	//SecondHand:18
		<< secondhand.palmVelocity().roll() * RAD_TO_DEG	//SecondHand:19
		<< secondhand.palmVelocity().yaw() * RAD_TO_DEG		//SecondHand:20
		<< secondhand.palmNormal().x						//SecondHand:21
		<< secondhand.palmNormal().y						//SecondHand:22
		<< secondhand.palmNormal().z						//SecondHand:23
		<< secondnormal.pitch() * RAD_TO_DEG				//SecondHand:24
		<< secondnormal.roll() * RAD_TO_DEG					//SecondHand:25
		<< secondnormal.yaw() * RAD_TO_DEG					//SecondHand:26
		<< secondavgPos.x									//SecondHand:27
		<< secondavgPos.y									//SecondHand:28
		<< secondavgPos.z									//SecondHand:29
		<< secondavgPos.pitch() * RAD_TO_DEG				//SecondHand:30
		<< secondavgPos.roll() * RAD_TO_DEG					//SecondHand:31
		<< secondavgPos.yaw() * RAD_TO_DEG					//SecondHand:32
		<< secondfingers[0].tipPosition().x					//SecondHand:33
		<< secondfingers[0].tipPosition().y					//SecondHand:34
		<< secondfingers[0].tipPosition().z					//SecondHand:35
		<< secondfingers[1].tipPosition().x					//SecondHand:36
		<< secondfingers[1].tipPosition().y					//SecondHand:37
		<< secondfingers[1].tipPosition().z 				//SecondHand:38
		<< secondfingers[2].tipPosition().x					//SecondHand:39
		<< secondfingers[2].tipPosition().y					//SecondHand:40
		<< secondfingers[2].tipPosition().z					//SecondHand:41
		<< secondfingers[3].tipPosition().x					//SecondHand:42
		<< secondfingers[3].tipPosition().y					//SecondHand:43
		<< secondfingers[3].tipPosition().z					//SecondHand:44
		<< secondfingers[4].tipPosition().x					//SecondHand:45
		<< secondfingers[4].tipPosition().y					//SecondHand:46
		<< secondfingers[4].tipPosition().z					//SecondHand:47
		<< osc::EndMessage
		<< osc::EndBundle;  
    transmitSocket.Send( p.Data(), p.Size() );
}

// 'int argc, char* argv[]' added to 'int main' for oscpack
int main(int argc, char* argv[]) {

  //Program title and OSC configuration
  std::cout << "leapOSC v0.1 by Morphic Creative" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "OSC output to: " << ADDRESS << ", port: " << PORT << ", output buffer size: " << OUTPUT_BUFFER_SIZE << std::endl;
  std::cout << "" << std::endl;

  // Create a sample listener and controller
  SampleListener listener;
  Controller controller;

  // Have the sample listener receive events from the controller
  controller.addListener(listener);

  // Keep this process running until Enter is pressed
  std::cout << "Press Enter to quit..." << std::endl;
  std::cin.get();

  // Remove the sample listener when done
  controller.removeListener(listener);

  return 0;
}