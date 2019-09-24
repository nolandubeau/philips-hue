
 
#include "PhilipsHue.h"

//Philips Hue Bridge Settings
#define HUE_USER "d8yefWD-pKTXJMD5rsUQXRFe291wh9JlF2Yce4SB" //eg: d8yefWD-pKTXJMD5rsUQXRFe291wh9JlF2Yce4SB
#define HUE_PORT 80
#define HUE_APPNAME "myHueApp"  //your app's name
char hueBridge[] = "http://192.168.0.138";  // hue bridge ip address eg: http://192.168.0.138


PhilipsHue hue = PhilipsHue(hueBridge, HUE_PORT);


void setup() {
  Serial.begin(9600);

  //Start Hue
  hue.begin(HUE_USER);
  
  //Register your app w/ the Hue Bridge
  hue.registerApp(HUE_APPNAME);
  
  //-------------------------------------------------------------------------
  Serial.println();
  Serial.println("Press the button on the center of the Philips Hue Bridge.");
  Serial.println();
  Serial.println("By confirming phyisical access you're authorizing your app to communicate with the bridge");
  Serial.println("Once you've completed this process send a message over serial to your Arduino.");
  Serial.println("Just type anything and hit 'send' or the Enter key.");
  Serial.println();
  
  while (Serial.available() <= 0) 
  {
    delay(300);
    //delay loop which waits giving you a chance to press the Hue Bridge button
    //Sending serial data to your Arduino will break the loop
  }
  
  Serial.println(hue.registerApp(HUE_APPNAME));
  Serial.println("You should've received a message like... [{\"success\":{\"username\":\"bkZV7kAKiERnDi...\"}}]");
  Serial.println("Copy down this username hash in a safe spot! You'll edit the '#define hueUser' with your username in future examples");
  //-------------------------------------------------------------------------

}

void loop() {


}

