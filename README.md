# Philips Hue	 - Particle Library

A Particle.io library for connected devices implementing the [Philips Hue API](https://developers.meethue.com/philips-hue-api) over HTTP. This library handles API calls to the Philips Hue Bridge, which in turn allows you to control your lights from your WiFi enabled Particle device such as an Argon or Xenon! 

Your Particle device can send requests to turn all of your lights off with one command, or set individual light attributes one by one. Functions have been written to manipulate attributes for the [/lights](https://developers.meethue.com/documentation/lights-api) and [/groups](https://developers.meethue.com/documentation/groups-api) endpoints of the Hue API. To learn more about the Hue API check out the [Philips Hue API documentation](https://developers.meethue.com/philips-hue-api). To learn more about how Philips Hue works check out [How Hue Works](https://www.developers.meethue.com/documentation/how-hue-works).

The Philips-Hue Particle library gives you the capability to configure for a single light or assigned group of lights...

* On/Off - also on/off for all lights attached to a bridge
* Hue
* Saturation
* Brightness
* Color Temperature
* Effects - Color Loop
* Alerts - Alert & Flash


# Getting Started

In order to get your Particle device talking to your Philips Hue Lights you're going to need a few things. First...
*   Download and install the ['Philips-Hue' library](https://github.com/nolandubeau/philips-hue/archive/master.zip) to the lib folder of your Particle project.
*   Test out and install your Hue lights using [Philips Hue App](http://www2.meethue.com/en-us/philipshueapp) to ensure everything is working properly first. Currently no endpoints are exposed in the library for registering new lights.
*   You'll need physical access to the Hue Bridge in order to complete the app registration process.

Let's get started!

# App Registration

To start communicating with the Hue Bridge you need to authenticate your application with the Philips Hue bridge. In order to do so you must have physical access to the bridge. Essentially, your application makes an API request for a username hash, you press the button on the top of the bridge, and then request a username again. Your second request returns you this...

```
[
	{
		"success": {
			"username": "WCBrB5gCdiIULlmTCcrbXh1bLjXYDSBmVzx5N2Ue"
		}
	}
]
```
In order to communicate with the bridge you must set the hueUser variable at the top of the example files to your username.

In the example directory you'll find an example named ['getUsername'](https://github.com/nolandubeau/philips-hue/blob/master/examples/getUsername/getUsername.ino). Download this example and fill in your Philips Hue bridge details. You'll also need to fill in the IP address of the Hue Bridge. There a few ways to get this. Either log in to your routers admin page (usually found at http://192.168.1.1) and check the attached/connected devices. Alternatively hop over to the [Philips Hue Bridge Discovery Guide](https://developers.meethue.com/documentation/hue-bridge-discovery) for more ideas to discover the bridge's IP using tools like UPnP

Once you've filled in those details, flash the example, and follow the instructions in the serial terminal. When prompted, press the button on the bridge. Return to your serial terminal and send some data back to the Particle device to break the wait loop. (Literally send anything, a carriage return, a secret message, doesn't matter) This triggers the Particle device to send a second request for your username, which should then return the above success message. Save the hash in a safe spot! You'll need it for the other examples.

That's it! Now you have everything you need to start changing the state of your lights using your Particle device!

# Blinky 

The defacto 'Hello World' of embedded hardware projects. [Here's our example](https://github.com/nolandubeau/philips-hue/blob/master/examples/hueBlinky/hueBlinky.ino). Just fill in your details from the 'getUsername' example and voila! 
```
#define hueUser ""      //ex: "Ur80SKqRKO0ojlFInzdjAZEHy0kjYWznakufY60m"
char hueBridge[] = "";  // hue bridge ip address ex: "192.168.1.3"
```
All the hue lights in your house will start blinking, turning on for 3 seconds, and then off for 3 seconds. The 'hueBlinky' example queries the bridge for all registered 'Groups' and then successively toggles all the lights.


# Things you should know...

* You can safely send about 10 /lights endpoint commands in a row/second before things get strange.
* You can only send 1 /groups targeted command per second! Be careful not to overload the bridge.
* A list of other interesting design decisions and intricacies of the Hue Lights API [can be found here.](https://developers.meethue.com/things-you-need-know)


## Coming Soon
* Additional examples
* Ability to install the plugin through the Particle CLI
* Ability to submit custom JSON to /groups and /lights endpoints
* ex: ``` sendRequestToLights(lightId, "{\"on\":true,\"hue\":50000,\"brightness\":200,\"sat\":254}");```
* More global attribute functions for changing attributes accross all groups

## Contributions
This library was ported from the [hueDino](https://github.com/andium/hueDino) Arduino library by [Brian Carbonette](https://github.com/briancarbs) and [Andium](https://github.com/andium).  Shout out to [Nils Mattisson](https://github.com/nmattisson) for Spark Core [HTTP Client](https://github.com/nmattisson/httpclient) and [Benoit Blanchon](https://github.com/bblanchon) for [ArduinoJson](https://github.com/bblanchon/ArduinoJson).
              

