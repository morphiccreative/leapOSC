// leapOSC v0.5 by Morphic Creative 14-06-2013

//Includes and namespace for Leap
#include <iostream>
#include "Leap.h"
using namespace Leap;

// Includes and defines for oscpack
#include "include/OscOutboundPacketStream.h"
#include "include/UdpSocket.h"
#define ADDRESS "127.0.0.1"
#define PORT 7000
#define OUTPUT_BUFFER_SIZE 8192
using namespace std;

class SampleListener : public Listener {
  public:
    virtual void onInit(const Controller&);
    virtual void onConnect(const Controller&);
    virtual void onDisconnect(const Controller&);
    virtual void onExit(const Controller&);
    virtual void onFrame(const Controller&);
	virtual void onFocusGained(const Controller&);
    virtual void onFocusLost(const Controller&);
};

void SampleListener::onInit(const Controller& controller) {
  std::cout << "Initialized" << std::endl;
}

void SampleListener::onConnect(const Controller& controller) {
  std::cout << "Connected" << std::endl;
  controller.enableGesture(Gesture::TYPE_CIRCLE);
  controller.enableGesture(Gesture::TYPE_KEY_TAP);
  controller.enableGesture(Gesture::TYPE_SCREEN_TAP);
  controller.enableGesture(Gesture::TYPE_SWIPE);
  controller.setPolicyFlags(Controller::POLICY_BACKGROUND_FRAMES);
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
  const Hand handone = frame.hands()[0];
  const Hand handtwo = frame.hands()[1];
  const Hand handthree = frame.hands()[2];
  const Hand handfour = frame.hands()[3];

  // Get the fingers
  const FingerList handonefingers = handone.fingers();
  const FingerList handtwofingers = handtwo.fingers();
  const FingerList handthreefingers = handthree.fingers();
  const FingerList handfourfingers = handfour.fingers();

  // Calculate average finger tip positions
      Vector handonefingersavgPos;
      for (int i = 0; i < handonefingers.count(); ++i) {
        handonefingersavgPos += handonefingers[i].tipPosition();
      }
      handonefingersavgPos /= (float)handonefingers.count();
      Vector handtwofingersavgPos;
      for (int i = 0; i < handtwofingers.count(); ++i) {
        handtwofingersavgPos += handtwofingers[i].tipPosition();
      }
      handtwofingersavgPos /= (float)handtwofingers.count();
      Vector handthreefingersavgPos;
      for (int i = 0; i < handthreefingers.count(); ++i) {
        handthreefingersavgPos += handthreefingers[i].tipPosition();
      }
      handthreefingersavgPos /= (float)handthreefingers.count();
      Vector handfourfingersavgPos;
      for (int i = 0; i < handfourfingers.count(); ++i) {
        handfourfingersavgPos += handfourfingers[i].tipPosition();
      }
      handfourfingersavgPos /= (float)handfourfingers.count();

  // Get the hands normal vectors and directions
  const Vector handonenormalvector = handone.palmNormal();
  const Vector handonedirection = handone.direction();
  const Vector handtwonormalvector = handtwo.palmNormal();
  const Vector handtwodirection = handtwo.direction();
  const Vector handthreenormalvector = handthree.palmNormal();
  const Vector handthreedirection = handthree.direction();
  const Vector handfournormalvector = handfour.palmNormal();
  const Vector handfourdirection = handfour.direction();

  // Output Leap data via OSC
    UdpTransmitSocket transmitSocket( IpEndpointName( ADDRESS, PORT ) );    
    char buffer[OUTPUT_BUFFER_SIZE];
    osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );   
    p << osc::BeginBundleImmediate
  // Frame Data
        << osc::BeginMessage( "/ID:" )	<< frame.id()				<< osc::EndMessage
        << osc::BeginMessage( "/TS:" )	<< frame.timestamp()		<< osc::EndMessage
        << osc::BeginMessage( "/HC:" )	<< frame.hands().count()	<< osc::EndMessage
        << osc::BeginMessage( "/FC:" )	<< frame.fingers().count()	<< osc::EndMessage
        << osc::BeginMessage( "/TC:" )	<< frame.tools().count()	<< osc::EndMessage
  // Hand One Data
        << osc::BeginMessage( "/H1FC:" )		<< handonefingers.count()		<< osc::EndMessage
        << osc::BeginMessage( "/H1PPX:" )		<< handone.palmPosition().x		<< osc::EndMessage				//(mm)
        << osc::BeginMessage( "/H1PPY:" )		<< handone.palmPosition().y		<< osc::EndMessage				//(mm)		
        << osc::BeginMessage( "/H1PPZ:" )		<< handone.palmPosition().z		<< osc::EndMessage				//(mm)
        << osc::BeginMessage( "/H1PVX:" )		<< handone.palmVelocity().x						//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1PVY:" )		<< handone.palmVelocity().y						//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1PVZ:" )		<< handone.palmVelocity().z						//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1NVP:" )		<< handonenormalvector.pitch() * RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1NVR:" )		<< handonenormalvector.roll() * RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1NVY:" )		<< handonenormalvector.yaw() * RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1DP:" )		<< handonedirection.pitch() * RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1DR:" )		<< handonedirection.roll() * RAD_TO_DEG			//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1DY:" )		<< handonedirection.yaw() * RAD_TO_DEG			//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1SCX:" )		<< handone.sphereCenter().x						//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1SCY:" )		<< handone.sphereCenter().y						//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1SCZ:" )		<< handone.sphereCenter().z						//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1SR:" )		<< handone.sphereRadius()						//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1FAPX:" )		<< handonefingersavgPos.x						//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1FAPY:" )		<< handonefingersavgPos.y						//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1FAPZ:" )		<< handonefingersavgPos.z						//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1F0L:" )
		<< handonefingers[0].length()					//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1F0W:" )
		<< handonefingers[0].width()					//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1F0DP:" )
		<< handonefingers[0].direction().pitch() * RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1F0DR:" )
		<< handonefingers[0].direction().roll()	* RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1F0DY:" )
		<< handonefingers[0].direction().yaw() * RAD_TO_DEG			//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1F0TPX:" )
		<< handonefingers[0].tipPosition().x			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1F0TPY:" )
		<< handonefingers[0].tipPosition().y			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1F0TPZ:" )
		<< handonefingers[0].tipPosition().z			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1F0TVX:" )
		<< handonefingers[0].tipVelocity().x			//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1F0TVY:" )
		<< handonefingers[0].tipVelocity().y			//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1F0TVZ:" )
		<< handonefingers[0].tipVelocity().z			//(mm/s)
		<< osc::EndMessage

        << osc::BeginMessage( "/H1F1L:" )
		<< handonefingers[1].length()					//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1F1W:" )
		<< handonefingers[1].width()					//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1F1DP:" )
		<< handonefingers[1].direction().pitch() * RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1F1DR:" )
		<< handonefingers[1].direction().roll()	* RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1F1DY:" )
		<< handonefingers[1].direction().yaw() * RAD_TO_DEG			//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1F1TPX:" )
		<< handonefingers[1].tipPosition().x			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1F1TPY:" )
		<< handonefingers[1].tipPosition().y			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1F1TPZ:" )
		<< handonefingers[1].tipPosition().z			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1F1TVX:" )
		<< handonefingers[1].tipVelocity().x			//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1F1TVY:" )
		<< handonefingers[1].tipVelocity().y			//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1F1TVZ:" )
		<< handonefingers[1].tipVelocity().z			//(mm/s)
		<< osc::EndMessage

        << osc::BeginMessage( "/H1F2L:" )
		<< handonefingers[2].length()					//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1F2W:" )
		<< handonefingers[2].width()					//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1F2DP:" )
		<< handonefingers[2].direction().pitch() * RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1F2DR:" )
		<< handonefingers[2].direction().roll()	* RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1F2DY:" )
		<< handonefingers[2].direction().yaw() * RAD_TO_DEG			//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1F2TPX:" )
		<< handonefingers[2].tipPosition().x			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1F2TPY:" )
		<< handonefingers[2].tipPosition().y			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1F2TPZ:" )
		<< handonefingers[2].tipPosition().z			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1F2TVX:" )
		<< handonefingers[2].tipVelocity().x			//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1F2TVY:" )
		<< handonefingers[2].tipVelocity().y			//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1F2TVZ:" )
		<< handonefingers[2].tipVelocity().z			//(mm/s)
		<< osc::EndMessage

        << osc::BeginMessage( "/H1F3L:" )
		<< handonefingers[3].length()					//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1F3W:" )
		<< handonefingers[3].width()					//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1F3DP:" )
		<< handonefingers[3].direction().pitch() * RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1F3DR:" )
		<< handonefingers[3].direction().roll()	* RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1F3DY:" )
		<< handonefingers[3].direction().yaw() * RAD_TO_DEG			//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1F3TPX:" )
		<< handonefingers[3].tipPosition().x			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1F3TPY:" )
		<< handonefingers[3].tipPosition().y			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1F3TPZ:" )
		<< handonefingers[3].tipPosition().z			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1F3TVX:" )
		<< handonefingers[3].tipVelocity().x			//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1F3TVY:" )
		<< handonefingers[3].tipVelocity().y			//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1F3TVZ:" )
		<< handonefingers[3].tipVelocity().z			//(mm/s)
		<< osc::EndMessage

        << osc::BeginMessage( "/H1F4L:" )
		<< handonefingers[4].length()					//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1F4W:" )
		<< handonefingers[4].width()					//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1F4DP:" )
		<< handonefingers[4].direction().pitch() * RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1F4DR:" )
		<< handonefingers[4].direction().roll()	* RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1F4DY:" )
		<< handonefingers[4].direction().yaw() * RAD_TO_DEG			//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1F4TPX:" )
		<< handonefingers[4].tipPosition().x			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1F4TPY:" )
		<< handonefingers[4].tipPosition().y			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1F4TPZ:" )
		<< handonefingers[4].tipPosition().z			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1F4TVX:" )
		<< handonefingers[4].tipVelocity().x			//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1F4TVY:" )
		<< handonefingers[4].tipVelocity().y			//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H1F4TVZ:" )
		<< handonefingers[4].tipVelocity().z			//(mm/s)
		<< osc::EndMessage
  // Hand Two Data
        << osc::BeginMessage( "/H2FC:" )
		<< handtwofingers.count()
		<< osc::EndMessage
        << osc::BeginMessage( "/H2PPX:" )
		<< handtwo.palmPosition().x						//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2PPY:" )
		<< handtwo.palmPosition().y						//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2PPZ:" )
		<< handtwo.palmPosition().z						//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2PVX:" )
		<< handtwo.palmVelocity().x						//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2PVY:" )
		<< handtwo.palmVelocity().y						//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2PVZ:" )
		<< handtwo.palmVelocity().z						//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2NVP:" )
		<< handtwonormalvector.pitch() * RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2NVR:" )
		<< handtwonormalvector.roll() * RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2NVY:" )
		<< handtwonormalvector.yaw() * RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2DP:" )
		<< handtwodirection.pitch() * RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2DR:" )
		<< handtwodirection.roll() * RAD_TO_DEG			//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2DY:" )
		<< handtwodirection.yaw() * RAD_TO_DEG			//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2SCX:" )
		<< handtwo.sphereCenter().x						//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2SCY:" )
		<< handtwo.sphereCenter().y						//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2SCZ:" )
		<< handtwo.sphereCenter().z						//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2SR:" )
		<< handtwo.sphereRadius()						//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2FAPX:" )
		<< handtwofingersavgPos.x						//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2FAPY:" )
		<< handtwofingersavgPos.y						//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2FAPZ:" )
		<< handtwofingersavgPos.z						//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2F0L:" )
		<< handtwofingers[0].length()					//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2F0W:" )
		<< handtwofingers[0].width()					//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2F0DP:" )
		<< handtwofingers[0].direction().pitch() * RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2F0DR:" )
		<< handtwofingers[0].direction().roll()	* RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2F0DY:" )
		<< handtwofingers[0].direction().yaw() * RAD_TO_DEG			//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2F0TPX:" )
		<< handtwofingers[0].tipPosition().x			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2F0TPY:" )
		<< handtwofingers[0].tipPosition().y			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2F0TPZ:" )
		<< handtwofingers[0].tipPosition().z			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2F0TVX:" )
		<< handtwofingers[0].tipVelocity().x			//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2F0TVY:" )
		<< handtwofingers[0].tipVelocity().y			//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2F0TVZ:" )
		<< handtwofingers[0].tipVelocity().z			//(mm/s)
		<< osc::EndMessage

        << osc::BeginMessage( "/H2F1L:" )
		<< handtwofingers[1].length()					//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2F1W:" )
		<< handtwofingers[1].width()					//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2F1DP:" )
		<< handtwofingers[1].direction().pitch() * RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2F1DR:" )
		<< handtwofingers[1].direction().roll()	* RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2F1DY:" )
		<< handtwofingers[1].direction().yaw() * RAD_TO_DEG			//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2F1TPX:" )
		<< handtwofingers[1].tipPosition().x			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2F1TPY:" )
		<< handtwofingers[1].tipPosition().y			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2F1TPZ:" )
		<< handtwofingers[1].tipPosition().z			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2F1TVX:" )
		<< handtwofingers[1].tipVelocity().x			//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2F1TVY:" )
		<< handtwofingers[1].tipVelocity().y			//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2F1TVZ:" )
		<< handtwofingers[1].tipVelocity().z			//(mm/s)
		<< osc::EndMessage

        << osc::BeginMessage( "/H2F2L:" )
		<< handtwofingers[2].length()					//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2F2W:" )
		<< handtwofingers[2].width()					//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2F2DP:" )
		<< handtwofingers[2].direction().pitch() * RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2F2DR:" )
		<< handtwofingers[2].direction().roll()	* RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2F2DY:" )
		<< handtwofingers[2].direction().yaw() * RAD_TO_DEG			//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2F2TPX:" )
		<< handtwofingers[2].tipPosition().x			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2F2TPY:" )
		<< handtwofingers[2].tipPosition().y			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2F2TPZ:" )
		<< handtwofingers[2].tipPosition().z			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2F2TVX:" )
		<< handtwofingers[2].tipVelocity().x			//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2F2TVY:" )
		<< handtwofingers[2].tipVelocity().y			//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2F2TVZ:" )
		<< handtwofingers[2].tipVelocity().z			//(mm/s)
		<< osc::EndMessage

        << osc::BeginMessage( "/H2F3L:" )
		<< handtwofingers[3].length()					//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2F3W:" )
		<< handtwofingers[3].width()					//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2F3DP:" )
		<< handtwofingers[3].direction().pitch() * RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2F3DR:" )
		<< handtwofingers[3].direction().roll()	* RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2F3DY:" )
		<< handtwofingers[3].direction().yaw() * RAD_TO_DEG			//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2F3TPX:" )
		<< handtwofingers[3].tipPosition().x			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2F3TPY:" )
		<< handtwofingers[3].tipPosition().y			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2F3TPZ:" )
		<< handtwofingers[3].tipPosition().z			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2F3TVX:" )
		<< handtwofingers[3].tipVelocity().x			//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2F3TVY:" )
		<< handtwofingers[3].tipVelocity().y			//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2F3TVZ:" )
		<< handtwofingers[3].tipVelocity().z			//(mm/s)
		<< osc::EndMessage

        << osc::BeginMessage( "/H2F4L:" )
		<< handtwofingers[4].length()					//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2F4W:" )
		<< handtwofingers[4].width()					//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2F4DP:" )
		<< handtwofingers[4].direction().pitch() * RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2F4DR:" )
		<< handtwofingers[4].direction().roll()	* RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2F4DY:" )
		<< handtwofingers[4].direction().yaw() * RAD_TO_DEG			//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2F4TPX:" )
		<< handtwofingers[4].tipPosition().x			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2F4TPY:" )
		<< handtwofingers[4].tipPosition().y			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2F4TPZ:" )
		<< handtwofingers[4].tipPosition().z			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2F4TVX:" )
		<< handtwofingers[4].tipVelocity().x			//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2F4TVY:" )
		<< handtwofingers[4].tipVelocity().y			//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H2F4TVZ:" )
		<< handtwofingers[4].tipVelocity().z			//(mm/s)
		<< osc::EndMessage
  //Hand Three Data
        << osc::BeginMessage( "/H3FC:" )
		<< handthreefingers.count()
		<< osc::EndMessage
        << osc::BeginMessage( "/H3PPX:" )
		<< handthree.palmPosition().x						//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3PPY:" )
		<< handthree.palmPosition().y						//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3PPZ:" )
		<< handthree.palmPosition().z						//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3PVX:" )
		<< handthree.palmVelocity().x						//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3PVY:" )
		<< handthree.palmVelocity().y						//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3PVZ:" )
		<< handthree.palmVelocity().z						//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3NVP:" )
		<< handthreenormalvector.pitch() * RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3NVR:" )
		<< handthreenormalvector.roll() * RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3NVY:" )
		<< handthreenormalvector.yaw() * RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3DP:" )
		<< handthreedirection.pitch() * RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3DR:" )
		<< handthreedirection.roll() * RAD_TO_DEG			//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3DY:" )
		<< handthreedirection.yaw() * RAD_TO_DEG			//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3SCX:" )
		<< handthree.sphereCenter().x						//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3SCY:" )
		<< handthree.sphereCenter().y						//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3SCZ:" )
		<< handthree.sphereCenter().z						//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3SR:" )
		<< handthree.sphereRadius()						//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3FAPX:" )
		<< handthreefingersavgPos.x						//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3FAPY:" )
		<< handthreefingersavgPos.y						//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3FAPZ:" )
		<< handthreefingersavgPos.z						//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3F0L:" )
		<< handthreefingers[0].length()					//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3F0W:" )
		<< handthreefingers[0].width()					//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3F0DP:" )
		<< handthreefingers[0].direction().pitch() * RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3F0DR:" )
		<< handthreefingers[0].direction().roll()	* RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3F0DY:" )
		<< handthreefingers[0].direction().yaw() * RAD_TO_DEG			//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3F0TPX:" )
		<< handthreefingers[0].tipPosition().x			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3F0TPY:" )
		<< handthreefingers[0].tipPosition().y			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3F0TPZ:" )
		<< handthreefingers[0].tipPosition().z			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3F0TVX:" )
		<< handthreefingers[0].tipVelocity().x			//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3F0TVY:" )
		<< handthreefingers[0].tipVelocity().y			//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3F0TVZ:" )
		<< handthreefingers[0].tipVelocity().z			//(mm/s)
		<< osc::EndMessage

        << osc::BeginMessage( "/H3F1L:" )
		<< handthreefingers[1].length()					//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3F1W:" )
		<< handthreefingers[1].width()					//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3F1DP:" )
		<< handthreefingers[1].direction().pitch() * RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3F1DR:" )
		<< handthreefingers[1].direction().roll()	* RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3F1DY:" )
		<< handthreefingers[1].direction().yaw() * RAD_TO_DEG			//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3F1TPX:" )
		<< handthreefingers[1].tipPosition().x			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3F1TPY:" )
		<< handthreefingers[1].tipPosition().y			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3F1TPZ:" )
		<< handthreefingers[1].tipPosition().z			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3F1TVX:" )
		<< handthreefingers[1].tipVelocity().x			//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3F1TVY:" )
		<< handthreefingers[1].tipVelocity().y			//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3F1TVZ:" )
		<< handthreefingers[1].tipVelocity().z			//(mm/s)
		<< osc::EndMessage

        << osc::BeginMessage( "/H3F2L:" )
		<< handthreefingers[2].length()					//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3F2W:" )
		<< handthreefingers[2].width()					//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3F2DP:" )
		<< handthreefingers[2].direction().pitch() * RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3F2DR:" )
		<< handthreefingers[2].direction().roll()	* RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3F2DY:" )
		<< handthreefingers[2].direction().yaw() * RAD_TO_DEG			//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3F2TPX:" )
		<< handthreefingers[2].tipPosition().x			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3F2TPY:" )
		<< handthreefingers[2].tipPosition().y			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3F2TPZ:" )
		<< handthreefingers[2].tipPosition().z			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3F2TVX:" )
		<< handthreefingers[2].tipVelocity().x			//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3F2TVY:" )
		<< handthreefingers[2].tipVelocity().y			//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3F2TVZ:" )
		<< handthreefingers[2].tipVelocity().z			//(mm/s)
		<< osc::EndMessage

        << osc::BeginMessage( "/H3F3L:" )
		<< handthreefingers[3].length()					//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3F3W:" )
		<< handthreefingers[3].width()					//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3F3DP:" )
		<< handthreefingers[3].direction().pitch() * RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3F3DR:" )
		<< handthreefingers[3].direction().roll()	* RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3F3DY:" )
		<< handthreefingers[3].direction().yaw() * RAD_TO_DEG			//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3F3TPX:" )
		<< handthreefingers[3].tipPosition().x			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3F3TPY:" )
		<< handthreefingers[3].tipPosition().y			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3F3TPZ:" )
		<< handthreefingers[3].tipPosition().z			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3F3TVX:" )
		<< handthreefingers[3].tipVelocity().x			//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3F3TVY:" )
		<< handthreefingers[3].tipVelocity().y			//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3F3TVZ:" )
		<< handthreefingers[3].tipVelocity().z			//(mm/s)
		<< osc::EndMessage

        << osc::BeginMessage( "/H3F4L:" )
		<< handthreefingers[4].length()					//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3F4W:" )
		<< handthreefingers[4].width()					//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3F4DP:" )
		<< handthreefingers[4].direction().pitch() * RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3F4DR:" )
		<< handthreefingers[4].direction().roll()	* RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3F4DY:" )
		<< handthreefingers[4].direction().yaw() * RAD_TO_DEG			//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3F4TPX:" )
		<< handthreefingers[4].tipPosition().x			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3F4TPY:" )
		<< handthreefingers[4].tipPosition().y			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3F4TPZ:" )
		<< handthreefingers[4].tipPosition().z			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3F4TVX:" )
		<< handthreefingers[4].tipVelocity().x			//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3F4TVY:" )
		<< handthreefingers[4].tipVelocity().y			//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H3F4TVZ:" )
		<< handthreefingers[4].tipVelocity().z			//(mm/s)
		<< osc::EndMessage
  // Hand Four Data
        << osc::BeginMessage( "/H4FC:" )
		<< handfourfingers.count()
		<< osc::EndMessage
        << osc::BeginMessage( "/H4PPX:" )
		<< handfour.palmPosition().x						//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4PPY:" )
		<< handfour.palmPosition().y						//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4PPZ:" )
		<< handfour.palmPosition().z						//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4PVX:" )
		<< handfour.palmVelocity().x						//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4PVY:" )
		<< handfour.palmVelocity().y						//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4PVZ:" )
		<< handfour.palmVelocity().z						//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4NVP:" )
		<< handfournormalvector.pitch() * RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4NVR:" )
		<< handfournormalvector.roll() * RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4NVY:" )
		<< handfournormalvector.yaw() * RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4DP:" )
		<< handfourdirection.pitch() * RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4DR:" )
		<< handfourdirection.roll() * RAD_TO_DEG			//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4DY:" )
		<< handfourdirection.yaw() * RAD_TO_DEG			//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4SCX:" )
		<< handfour.sphereCenter().x						//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4SCY:" )
		<< handfour.sphereCenter().y						//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4SCZ:" )
		<< handfour.sphereCenter().z						//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4SR:" )
		<< handfour.sphereRadius()						//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4FAPX:" )
		<< handfourfingersavgPos.x						//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4FAPY:" )
		<< handfourfingersavgPos.y						//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4FAPZ:" )
		<< handfourfingersavgPos.z						//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4F0L:" )
		<< handfourfingers[0].length()					//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4F0W:" )
		<< handfourfingers[0].width()					//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4F0DP:" )
		<< handfourfingers[0].direction().pitch() * RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4F0DR:" )
		<< handfourfingers[0].direction().roll()	* RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4F0DY:" )
		<< handfourfingers[0].direction().yaw() * RAD_TO_DEG			//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4F0TPX:" )
		<< handfourfingers[0].tipPosition().x			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4F0TPY:" )
		<< handfourfingers[0].tipPosition().y			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4F0TPZ:" )
		<< handfourfingers[0].tipPosition().z			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4F0TVX:" )
		<< handfourfingers[0].tipVelocity().x			//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4F0TVY:" )
		<< handfourfingers[0].tipVelocity().y			//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4F0TVZ:" )
		<< handfourfingers[0].tipVelocity().z			//(mm/s)
		<< osc::EndMessage

        << osc::BeginMessage( "/H4F1L:" )
		<< handfourfingers[1].length()					//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4F1W:" )
		<< handfourfingers[1].width()					//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4F1DP:" )
		<< handfourfingers[1].direction().pitch() * RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4F1DR:" )
		<< handfourfingers[1].direction().roll()	* RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4F1DY:" )
		<< handfourfingers[1].direction().yaw() * RAD_TO_DEG			//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4F1TPX:" )
		<< handfourfingers[1].tipPosition().x			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4F1TPY:" )
		<< handfourfingers[1].tipPosition().y			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4F1TPZ:" )
		<< handfourfingers[1].tipPosition().z			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4F1TVX:" )
		<< handfourfingers[1].tipVelocity().x			//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4F1TVY:" )
		<< handfourfingers[1].tipVelocity().y			//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4F1TVZ:" )
		<< handfourfingers[1].tipVelocity().z			//(mm/s)
		<< osc::EndMessage

        << osc::BeginMessage( "/H4F2L:" )
		<< handfourfingers[2].length()					//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4F2W:" )
		<< handfourfingers[2].width()					//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4F2DP:" )
		<< handfourfingers[2].direction().pitch() * RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4F2DR:" )
		<< handfourfingers[2].direction().roll()	* RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4F2DY:" )
		<< handfourfingers[2].direction().yaw() * RAD_TO_DEG			//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4F2TPX:" )
		<< handfourfingers[2].tipPosition().x			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4F2TPY:" )
		<< handfourfingers[2].tipPosition().y			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4F2TPZ:" )
		<< handfourfingers[2].tipPosition().z			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4F2TVX:" )
		<< handfourfingers[2].tipVelocity().x			//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4F2TVY:" )
		<< handfourfingers[2].tipVelocity().y			//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4F2TVZ:" )
		<< handfourfingers[2].tipVelocity().z			//(mm/s)
		<< osc::EndMessage

        << osc::BeginMessage( "/H4F3L:" )
		<< handfourfingers[3].length()					//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4F3W:" )
		<< handfourfingers[3].width()					//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4F3DP:" )
		<< handfourfingers[3].direction().pitch() * RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4F3DR:" )
		<< handfourfingers[3].direction().roll()	* RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4F3DY:" )
		<< handfourfingers[3].direction().yaw() * RAD_TO_DEG			//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4F3TPX:" )
		<< handfourfingers[3].tipPosition().x			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4F3TPY:" )
		<< handfourfingers[3].tipPosition().y			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4F3TPZ:" )
		<< handfourfingers[3].tipPosition().z			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4F3TVX:" )
		<< handfourfingers[3].tipVelocity().x			//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4F3TVY:" )
		<< handfourfingers[3].tipVelocity().y			//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4F3TVZ:" )
		<< handfourfingers[3].tipVelocity().z			//(mm/s)
		<< osc::EndMessage

        << osc::BeginMessage( "/H4F4L:" )
		<< handfourfingers[4].length()					//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4F4W:" )
		<< handfourfingers[4].width()					//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4F4DP:" )
		<< handfourfingers[4].direction().pitch() * RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4F4DR:" )
		<< handfourfingers[4].direction().roll()	* RAD_TO_DEG		//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4F4DY:" )
		<< handfourfingers[4].direction().yaw() * RAD_TO_DEG			//(deg)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4F4TPX:" )
		<< handfourfingers[4].tipPosition().x			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4F4TPY:" )
		<< handfourfingers[4].tipPosition().y			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4F4TPZ:" )
		<< handfourfingers[4].tipPosition().z			//(mm)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4F4TVX:" )
		<< handfourfingers[4].tipVelocity().x			//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4F4TVY:" )
		<< handfourfingers[4].tipVelocity().y			//(mm/s)
		<< osc::EndMessage
        << osc::BeginMessage( "/H4F4TVZ:" )
		<< handfourfingers[4].tipVelocity().z			//(mm/s)
		<< osc::EndMessage
		<< osc::EndBundle;  
    transmitSocket.Send( p.Data(), p.Size() );

  // Get gestures
  const GestureList gestures = frame.gestures();
  for (int g = 0; g < gestures.count(); ++g) {
    Gesture gesture = gestures[g];

    switch (gesture.type()) {
      case Gesture::TYPE_CIRCLE:
      {
        CircleGesture circle = gesture;
        std::string clockwiseness;

        if (circle.pointable().direction().angleTo(circle.normal()) <= PI/4) {
          clockwiseness = "clockwise";
        } else {
          clockwiseness = "counterclockwise";
        }

        // Calculate angle swept since last frame
        float sweptAngle = 0;
        if (circle.state() != Gesture::STATE_START) {
          CircleGesture previousUpdate = CircleGesture(controller.frame(1).gesture(circle.id()));
          sweptAngle = (circle.progress() - previousUpdate.progress()) * 2 * PI;
        }

// Transmit CircleGesture OSC Data
	UdpTransmitSocket transmitSocket( IpEndpointName( ADDRESS, PORT ) );    
    char buffer[OUTPUT_BUFFER_SIZE];
    osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );   
    p << osc::BeginBundleImmediate
        << osc::BeginMessage( "/CircleID:" )
		<< gesture.id()
		<< osc::EndMessage
        << osc::BeginMessage( "/CircleState:" )
		<< gesture.state()
		<< osc::EndMessage
        << osc::BeginMessage( "/CircleProgress:" )
		<< circle.progress()
		<< osc::EndMessage
        << osc::BeginMessage( "/CircleRadius:" )
		<< circle.radius()
		<< osc::EndMessage
        << osc::BeginMessage( "/CircleAngle:" )
		<< sweptAngle * RAD_TO_DEG
		<< osc::EndMessage 
//      << osc::BeginMessage( "/CW:" )
//		<< clockwiseness
//		<< osc::EndMessage
		<< osc::EndBundle;  
		transmitSocket.Send( p.Data(), p.Size() );

	break;
      }
      case Gesture::TYPE_SWIPE:
      {
        SwipeGesture swipe = gesture;

// Transmit SwipeGesture OSC Data
	UdpTransmitSocket transmitSocket( IpEndpointName( ADDRESS, PORT ) );    
    char buffer[OUTPUT_BUFFER_SIZE];
    osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );   
    p << osc::BeginBundleImmediate
        << osc::BeginMessage( "/SwipeID:" )
		<< gesture.id()
		<< osc::EndMessage
        << osc::BeginMessage( "/SwipeState:" )
		<< gesture.state()
		<< osc::EndMessage
		<< osc::BeginMessage( "/SwipeDirectionX:" )
		<< swipe.direction().x
		<< osc::EndMessage
		<< osc::BeginMessage( "/SwipeDirectionY:" )
		<< swipe.direction().y
		<< osc::EndMessage
		<< osc::BeginMessage( "/SwipeDirectionZ:" )
		<< swipe.direction().z
		<< osc::EndMessage
        << osc::BeginMessage( "/SwipeSpeed:" )
		<< swipe.speed()
		<< osc::EndMessage
		<< osc::EndBundle;  
    transmitSocket.Send( p.Data(), p.Size() );

        break;
      }
      case Gesture::TYPE_KEY_TAP:
      {
        KeyTapGesture tap = gesture;

// Transmit KeyTapGesture OSC Data
	UdpTransmitSocket transmitSocket( IpEndpointName( ADDRESS, PORT ) );    
    char buffer[OUTPUT_BUFFER_SIZE];
    osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );   
    p << osc::BeginBundleImmediate
        << osc::BeginMessage( "/KeyTapID:" )
		<< gesture.id()
		<< osc::EndMessage
        << osc::BeginMessage( "/KeyTapState:" )
		<< gesture.state()
		<< osc::EndMessage
        << osc::BeginMessage( "/KeyTapPositionX:" )
		<< tap.position().x
		<< osc::EndMessage
        << osc::BeginMessage( "/KeyTapPositionY:" )
		<< tap.position().y
		<< osc::EndMessage
        << osc::BeginMessage( "/KeyTapPositionZ:" )
		<< tap.position().z
		<< osc::EndMessage
        << osc::BeginMessage( "/KeyTapDirectionX:" )
		<< tap.direction().x
		<< osc::EndMessage
        << osc::BeginMessage( "/KeyTapDirectionY:" )
		<< tap.direction().y
		<< osc::EndMessage
        << osc::BeginMessage( "/KeyTapDirectionZ:" )
		<< tap.direction().z
		<< osc::EndMessage
		<< osc::EndBundle;  
    transmitSocket.Send( p.Data(), p.Size() );

        break;
      }
      case Gesture::TYPE_SCREEN_TAP:
      {
        ScreenTapGesture screentap = gesture;

// Transmit ScreenTapGesture OSC Data
	UdpTransmitSocket transmitSocket( IpEndpointName( ADDRESS, PORT ) );    
    char buffer[OUTPUT_BUFFER_SIZE];
    osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );   
    p << osc::BeginBundleImmediate
        << osc::BeginMessage( "/ScreenTapID:" )
		<< gesture.id()
		<< osc::EndMessage
        << osc::BeginMessage( "/ScreenTapState:" )
		<< gesture.state()
		<< osc::EndMessage
        << osc::BeginMessage( "/ScreenTapPositionX:" )
		<< screentap.position().x
		<< osc::EndMessage
        << osc::BeginMessage( "/ScreenTapPositionY:" )
		<< screentap.position().y
		<< osc::EndMessage
        << osc::BeginMessage( "/ScreenTapPositionZ:" )
		<< screentap.position().z
		<< osc::EndMessage
        << osc::BeginMessage( "/ScreenTapDirectionX:" )
		<< screentap.direction().x
		<< osc::EndMessage
        << osc::BeginMessage( "/ScreenTapDirectionY:" )
		<< screentap.direction().y
		<< osc::EndMessage
        << osc::BeginMessage( "/ScreenTapDirectionZ:" )
		<< screentap.direction().z
		<< osc::EndMessage
		<< osc::EndBundle;  
		transmitSocket.Send( p.Data(), p.Size() );
        break;
	  
      }
  }

  if (!frame.hands().empty() || !gestures.empty()) {
  }
}
}

void SampleListener::onFocusGained(const Controller& controller) {
//  std::cout << "Focus Gained" << std::endl;
}

void SampleListener::onFocusLost(const Controller& controller) {
//  std::cout << "Focus Lost" << std::endl;
}

  // 'int argc, char* argv[]' added to 'int main' for oscpack
  int main(int argc, char* argv[]) {

  //Program title and OSC configuration
  std::cout << "leapOSC v0.5 by Morphic Creative   Build: 14-06-2013" << std::endl;
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
