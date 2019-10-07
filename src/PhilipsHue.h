
/* PhilipsHue library by Nolan Dubeau
 */

#ifndef __PhilipsHue_H
#define __PhilipsHue_H

// This will load the definition for common Particle variable types
#include "Particle.h"
#include "HttpClient.h"
#include "JsonParserGeneratorRK.h"

#define LIGHT_ON "{\"on\":true}"
#define LIGHT_OFF "{\"on\":false}"
#define COLOR_LOOP_ON "{\"transitiontime\":0, \"effect\":\"colorloop\"}"
#define COLOR_LOOP_OFF "{\"transitiontime\":0, \"effect\":\"none\"}"
#define MAX_LIGHTS_PER_BRIDGE 50
#define MAX_GROUPS_PER_BRIDGE 64

//#define DEBUG
// This is your main class that users will import into their application
class PhilipsHue
{
public:
	String lightIds[MAX_LIGHTS_PER_BRIDGE] = {}; //50 max# of lights per bridge
	String lightNames[MAX_LIGHTS_PER_BRIDGE] = {}; 
	String groupIds[MAX_GROUPS_PER_BRIDGE] = {}; //64 max# of groups per bridge
	String groupNames[MAX_GROUPS_PER_BRIDGE] = {}; 
	uint8_t numGroups = 0;
	uint8_t numLights = 0;

	PhilipsHue();

	uint8_t begin(const char* hueBridgeIP, int hueBridgePort, const char* userId);
	String registerApp(String username);

	/*Single /light endpoint methods*/
	// String getLightIds(void);
	http_response_t lightOn(uint8_t lightId, uint8_t brightness);
	http_response_t lightOff(uint8_t lightId);
	http_response_t lightBrightness(uint8_t lightId, uint8_t brightness);
	http_response_t lightHue(uint8_t lightId, uint16_t setHue);
	String sat(uint8_t lightId, uint8_t setSat);
	String colorLoop(uint8_t lightId, bool enable);
	String colorTemp(uint8_t lightId, uint16_t temp);
	String alert(uint8_t lightId, String alertState);
	String flash(uint8_t lightId);

	/*When updating light attributes, unless there are a dozen or more lights it is generally more 
	efficient to use the lights API. With larger numbers of lights, it can be more efficient to access 
	them as a group, using the groups API.*/

	/* /groups endpoint methods */
	// void turnAllLightsOn(void);
	// void turnAllLightsOff(void);
	// String getGroupIds(void);
	String groupOn(uint8_t groupId);
	String groupOff(uint8_t groupId);
	String groupBrightness(uint8_t groupId, uint8_t brightness);
	String groupHue(uint8_t groupId, uint16_t setHue);
	String groupSat(uint8_t groupId, uint8_t setSat);
	String groupColorLoop(uint8_t groupId, bool enable);
	String groupColorTemp(uint8_t groupId, uint16_t temp);
	String groupAlert(uint8_t groupId, String alertState);
	String groupFlash(uint8_t groupId);


private:
  
	const char* _userId;
	const char* _hueBridgeIP;
	int _hueBridgePort;

	const char* _lightStateEndpoint(uint8_t lightId);
	String _groupActionEndpoint(uint8_t groupId);
	String _getLights(void);
	String _getGroups(void);

};

#endif /*__PhilipsHue_H */
