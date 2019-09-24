
 
#include "PhilipsHue.h"

//Philips Hue Bridge Settings
#define HUE_USER "" //eg: d8yefWD-pKTXJMD5rsUQXRFe291wh9JlF2Yce4SB
#define HUE_PORT 80
char hueBridge[] = "";  // hue bridge ip address eg: http://192.168.0.138


PhilipsHue hue = PhilipsHue(hueBridge, HUE_PORT);

void setup() {
  Serial.begin(9600);
  //Start Hue
  hue.begin(HUE_USER);
}

void loop() {

    //Blinky!
    hue.turnAllLightsOn();  //turns all hue lights on
    delay(3000);
    hue.turnAllLightsOff(); //turns all hue lights off
    delay(3000);

}