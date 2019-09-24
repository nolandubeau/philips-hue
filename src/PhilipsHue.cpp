/* PhilipsHue library by Nolan Dubeau
 */

#include "PhilipsHue.h"
#include "HttpClient.h"

/**
 * Constructor.
 */
PhilipsHue::PhilipsHue(const char* hueBridgeIP, int hueBridgePort)
{
  // be sure not to call anything that requires hardware be initialized here, put those in begin()
  _hueBridgeIP = hueBridgeIP;
  _hueBridgePort = hueBridgePort;
}

uint8_t PhilipsHue::begin(const char* userId)
{	
	HttpClient _restclient;
	_userId = userId;

      // Headers currently need to be set at init, useful for API keys etc.
    http_header_t headers[] = {
        //  { "Content-Type", "application/json" },
        //  { "Accept" , "application/json" },
        { "Accept" , "*/*"},
        { NULL, NULL } // NOTE: Always terminate headers will NULL
    };

    http_request_t request;
    http_response_t response;

    request.hostname = _hueBridgeIP;
    request.port = _hueBridgePort;

    //Check for username
	if(!_userId)
	{
		Serial.println();Serial.println();
		Serial.println("Missing username!");
		Serial.println("Have you ran the 'getUsername' sketch and authorized your app?");
		Serial.println("Don't forge to edit ---> #define hueUser \"yourUsernameHere\"   //ex: \"Ur80SKqRKO0ojlFInzdjAZEHy0kjYWznakufY60m\"");
		while(true){};
	}
	Serial.println();
	Serial.print("Starting PhilipsHue - verifying connection to Phillips Hue Bridge at: ");
	Serial.println(_hueBridgeIP);
	
	//check for static hue webpage served by bridge to make sure
	//we have the correct IP address
	
	uint8_t counter = 0;
	while(response.status != 200)
	{	
		Serial.print("...");
		_restclient.get(request, response, headers);
		delay(200);
		++counter;

		if(counter > 3)
		{
			Serial.print("Can't find Hue Bridge! Is ");
			Serial.print(_hueBridgeIP);
			Serial.println(" the correct IP address?");
            //Serial.println(response.body);
		    while(true){};

		}
	}
	Serial.println("Connected!");
	return 0;
	
}

String PhilipsHue::_lightStateEndpoint(uint8_t lightId)
{
	String endpoint = "/api/";

	endpoint += _userId;
	endpoint += "/lights/";
	endpoint += lightId;
	endpoint += "/state";

	return endpoint;
}

String PhilipsHue::_groupActionEndpoint(uint8_t groupId)
{
	String endpoint = "/api/";

	endpoint += _userId;
	endpoint += "/groups/";
	endpoint += groupId;
	endpoint += "/action";

	return endpoint;
}

String PhilipsHue::_getGroups(void)
{
	String endpoint = "/api/";

	endpoint += _userId;
	endpoint += "/groups";

	//_restclient.get(endpoint);
	//return _restclient.readResponse();

    return "_getGroups";
}

String PhilipsHue::_getLights(void)
{
	String endpoint = "/api/";

	endpoint += _userId;
	endpoint += "/lights";

	//_restclient.get(endpoint);
	//return _restclient.readResponse();

    return "_getLights";
}

String PhilipsHue::registerApp(String username)
{
	String endpoint = "/api";
	String body = "{\"devicetype\":\"";

	body += username;
	body += "\"}";

	//_restclient.post(endpoint, body);

	return "registerApp";
}


String PhilipsHue::lightOn(uint8_t lightId)
{	
	#ifdef DEBUG
		Serial.println();Serial.print("Light ID: ");
		Serial.print(lightId);Serial.println(" ON");
	#endif
   // _restclient.put(_lightStateEndpoint(lightId), LIGHT_ON);
    return "lightOn";
}

String PhilipsHue::lightOff(uint8_t lightId)
{
	#ifdef DEBUG
		Serial.println();Serial.print("Light ID: ");
		Serial.print(lightId);Serial.println(" OFF");
	#endif
    //_restclient.put(_lightStateEndpoint(lightId), LIGHT_OFF);
    return "lightOff";
}


String PhilipsHue::brightness(uint8_t lightId, uint8_t brightness)
{
	#ifdef DEBUG
		Serial.println();Serial.print("Light ID: ");
		Serial.print(lightId);Serial.print(" set brightness to ");
		Serial.println(brightness);
	#endif
	String bri = "{\"transitiontime\":0, \"bri\":";

	bri += String(brightness);
	bri += "}";

    //_restclient.put(_lightStateEndpoint(lightId), bri);
    return "set brightness";
}

String PhilipsHue::hue(uint8_t lightId, uint16_t setHue)
{
	#ifdef DEBUG
		Serial.println();Serial.print("Light ID: ");
		Serial.print(lightId);Serial.print(" set hue to ");
		Serial.println(setHue);
	#endif
	String hue = "{\"transitiontime\":0, \"hue\":";

	hue += String(setHue);
	hue += "}";

   // _restclient.put(_lightStateEndpoint(lightId), hue);
    return "set hue";	
}

//Input range 0-254
String PhilipsHue::sat(uint8_t lightId, uint8_t setSat)
{
	#ifdef DEBUG
		Serial.println();Serial.print("Light ID: ");
		Serial.print(lightId);Serial.print(" set saturation to ");
		Serial.println(setSat);
	#endif
	String sat = "{\"transitiontime\":0, \"sat\":";

	sat += String(setSat);
	sat += "}";

   // _restclient.put(_lightStateEndpoint(lightId), sat);
    return "set saturation";	
}


String PhilipsHue::colorLoop(uint8_t lightId, bool enable)
{	
	#ifdef DEBUG
		Serial.println();Serial.print("Light ID: ");
		Serial.print(lightId);Serial.print(" set color loop to ");
		Serial.println(enable);
	#endif
	if(enable)
	{
		//_restclient.put(_lightStateEndpoint(lightId), COLOR_LOOP_ON);
	}
	else
	{
		//_restclient.put(_lightStateEndpoint(lightId), COLOR_LOOP_OFF);
	}
    
    return "set color loop";
}

//Input Raneg 6500 to 2000
String PhilipsHue::colorTemp(uint8_t lightId, uint16_t temp)
{
	#ifdef DEBUG
		Serial.println();Serial.print("Light ID: ");
		Serial.print(lightId);Serial.print(" set temperature to ");
		Serial.println(temp);
	#endif
	uint16_t ct = map(temp, 2000, 6500, 153, 500); //map to hue API range 153-500
	String ctVal = "{\"transitiontime\":0, \"ct\":";

	ctVal += String(ct);
	ctVal += "}";

	if((ct > 500)||(ct < 153))
	{
		return "Temperature out of range, 2000K-6500K only!";
	}

	//_restclient.put(_lightStateEndpoint(lightId), ctVal);
    
    return "set color temp";
}

//alertState types: none, select, or lselect
String PhilipsHue::alert(uint8_t lightId, String alertState)
{
	#ifdef DEBUG
		Serial.println();Serial.print("Light ID: ");
		Serial.print(lightId);Serial.print(" set alert to ");
		Serial.println(alertState);
	#endif
	String alert = "{\"transitiontime\":0, \"alert\":\"";

	alert += alertState;
	alert += "\"}";

    //_restclient.put(_lightStateEndpoint(lightId), alert);
    return "alert lights";
}

String PhilipsHue::flash(uint8_t lightId)
{
	#ifdef DEBUG
		Serial.println();Serial.print("Light ID: ");
		Serial.print(lightId);Serial.print(" set to flash ");
	#endif
    //_restclient.put(_lightStateEndpoint(lightId), "{\"transitiontime\":0, \"alert\":\"select\"}");
    delay(800);
    return "flash lights";
}


// String PhilipsHue::getLightIds(void)
// {
// 	StaticJsonDocument<4096> doc; //may need to increase static buffer for large # lights
// 	String json = ""; 
	

// 	json = _getLights();
// 	deserializeJson(doc, json);
//     JsonObject root = doc.as<JsonObject>();
	
// 	int j=0;

// 	for(JsonObject::iterator it=root.begin(); it!=root.end(); ++it)
// 	{
// 		lightIds[j] = it->key().c_str();
// 		lightNames[j] = root[lightIds[j]]["name"].as<char*>();

// 		#ifdef DEBUG_IDs
// 			Serial.println();
// 			Serial.print("Light ID: ");
// 			Serial.println(lightIds[j]);
// 			Serial.print("Light Name: ");
// 			Serial.println(lightNames[j]);
// 		#endif

// 		j++; //number of lights
// 	}

// 	numLights = j;

// 	return json;
// }


// void PhilipsHue::turnAllLightsOff(void)
// {
// 	getGroupIds(); //update groupId arrays
// 	delay(1000); //For /groups commands you should keep to a maximum of 1 per second.

// 	for(int i=0; i<numGroups; i++)
// 	{
// 		groupOff(groupIds[i].toInt());
// 		delay(1000); //For /groups commands you should keep to a maximum of 1 per second.
// 		#ifdef DEBUG
// 		Serial.println();
// 		Serial.print("Turning off ");
// 		Serial.println(groupNames[i]);
// 		#endif
// 	}
// }

// void PhilipsHue::turnAllLightsOn(void)
// {
// 	getGroupIds(); //update groupId arrays
// 	delay(1000); //For /groups commands you should keep to a maximum of 1 per second.

// 	for(int i=0; i<numGroups; i++)
// 	{
// 		groupOn(groupIds[i].toInt());
// 		delay(1000); //For /groups commands you should keep to a maximum of 1 per second.
// 		#ifdef DEBUG
// 		Serial.println();
// 		Serial.print("Turning on ");
// 		Serial.println(groupNames[i]);
// 		#endif
// 	}
// }

// String PhilipsHue::getGroupIds(void)
// {
// 	StaticJsonDocument<4096> doc;
// 	String json = ""; 
	

// 	json = _getGroups();
// 	deserializeJson(doc, json);
//     JsonObject root = doc.as<JsonObject>();
    
	
// 	int j=0;

// 	for(JsonObject::iterator it=root.begin(); it!=root.end(); ++it)
// 	{
// 		groupIds[j] = it->key().c_str();
// 		groupNames[j] = root[groupIds[j]]["name"].as<char*>();

// 		#ifdef DEBUG_IDs
// 			Serial.println();
// 			Serial.print("Group ID: ");
// 			Serial.println(groupIds[j]);
// 			Serial.print("Group Name: ");
// 			Serial.println(groupNames[j]);
// 		#endif

// 		j++; //number of groups
// 	}

// 	numGroups = j;

// 	return json;
// }


String PhilipsHue::groupOn(uint8_t groupId)
{
	#ifdef DEBUG
		Serial.println();Serial.print("Group ID: ");
		Serial.print(groupId);Serial.println(" ON");
	#endif
    //_restclient.put(_groupActionEndpoint(groupId), LIGHT_ON);
    return "groupOn";
}

String PhilipsHue::groupOff(uint8_t groupId)
{
	#ifdef DEBUG
		Serial.println();Serial.print("Group ID: ");
		Serial.print(groupId);Serial.println(" OFF");
	#endif
   // _restclient.put(_groupActionEndpoint(groupId), LIGHT_OFF);
    return "groupOff";
}

String PhilipsHue::groupBrightness(uint8_t groupId, uint8_t brightness)
{
	#ifdef DEBUG
		Serial.println();Serial.print("Group ID: ");
		Serial.print(groupId);Serial.print(" set brightness to ");
		Serial.println(brightness);
	#endif
	String bri = "{\"transitiontime\":0, \"bri\":";

	bri += String(brightness);
	bri += "}";

   // _restclient.put(_groupActionEndpoint(groupId), bri);
    return "groupBrightness";
}

String PhilipsHue::groupHue(uint8_t groupId, uint16_t setHue)
{
	#ifdef DEBUG
		Serial.println();Serial.print("Group ID: ");
		Serial.print(groupId);Serial.print(" set hue to ");
		Serial.println(setHue);
	#endif
	String hue = "{\"transitiontime\":0, \"hue\":";

	hue += String(setHue);
	hue += "}";

    //_restclient.put(_groupActionEndpoint(groupId), hue);
    return "groupHue";	
}

String PhilipsHue::groupSat(uint8_t groupId, uint8_t setSat)
{
	#ifdef DEBUG
		Serial.println();Serial.print("Group ID: ");
		Serial.print(groupId);Serial.print(" set saturation to ");
		Serial.println(setSat);
	#endif
	String sat = "{\"transitiontime\":0, \"sat\":";

	sat += String(setSat);
	sat += "}";

    //_restclient.put(_groupActionEndpoint(groupId), sat);
    return "groupSat";	
}


String PhilipsHue::groupColorLoop(uint8_t groupId, bool enable)
{
	#ifdef DEBUG
		Serial.println();Serial.print("Group ID: ");
		Serial.print(groupId);Serial.print(" set color loop to ");
		Serial.println(enable);
	#endif
	if(enable)
	{
		//_restclient.put(_groupActionEndpoint(groupId), COLOR_LOOP_ON);
	}
	else
	{
		//_restclient.put(_groupActionEndpoint(groupId), COLOR_LOOP_OFF);
	}
    
    return "groupColorLoop";
}

String PhilipsHue::groupColorTemp(uint8_t groupId, uint16_t temp)
{
	#ifdef DEBUG
		Serial.println();Serial.print("Group ID: ");
		Serial.print(groupId);Serial.print(" set temperature to ");
		Serial.println(temp);
	#endif
	uint16_t ct = map(temp, 2000, 6500, 153, 500); //map to hue API range 153-500
	String ctVal = "{\"transitiontime\":0, \"ct\":";

	ctVal += String(ct);
	ctVal += "}";

	if((ct > 500)||(ct < 153))
	{
		return "Temperature out of range, 2000K-6500K only!";
	}

	//_restclient.put(_groupActionEndpoint(groupId), ctVal);
    return "groupColorTemp";
}


String PhilipsHue::groupAlert(uint8_t groupId, String alertState)
{
	#ifdef DEBUG
		Serial.println();Serial.print("Group ID: ");
		Serial.print(groupId);Serial.print(" set alert to ");
		Serial.println(alertState);
	#endif
	String alert = "{\"transitiontime\":0, \"alert\":\"";

	alert += alertState;
	alert += "\"}";

    //_restclient.put(_groupActionEndpoint(groupId), alert);
    return "groupAlert";
}

String PhilipsHue::groupFlash(uint8_t groupId)
{
	#ifdef DEBUG
		Serial.println();Serial.print("Group ID: ");
		Serial.print(groupId);Serial.print(" set to flash");
	#endif
	 //_restclient.put(_groupActionEndpoint(groupId), "{\"transitiontime\":0, \"alert\":\"select\"}");
    delay(800);
    return "groupFlash";
}









