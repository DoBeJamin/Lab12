/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/benja/OneDrive/Desktop/visualStudioCode/summerIOT/Lab12/src/Lab12.ino"
// libraries
#include "MQTT.h"
#include "oled-wing-adafruit.h"

void setup();
void loop();
void format_display ();
#line 5 "c:/Users/benja/OneDrive/Desktop/visualStudioCode/summerIOT/Lab12/src/Lab12.ino"
SYSTEM_THREAD(ENABLED);

void callback(char *topic, byte *payload, unsigned int length);

OledWingAdafruit display;
MQTT client("lab.thewcl.com", 1883, callback);

#define LED D7

void setup()
{
  Serial.begin(9600);
  display.setup();


  pinMode(LED, OUTPUT);

  client.subscribe("benLab12");
}
void loop()
{
  if (client.isConnected())
  {
    client.loop();
  }
  else
  {
    client.connect(System.deviceID());
    client.subscribe("benLab12");

  }
  display.loop();

  if (display.pressedA())
  {
    client.publish("benLab12", "A");
  }
  if (display.pressedB())
  {
    client.publish("benLab12", "B");
  }
  if (display.pressedC())
  {
    client.publish("benLab12", "C");
  }
}
void callback(char *topic, byte *payload, unsigned int length)
{
  char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;

  //lights up LED or prints out value
  if (String(p).equals("1"))
  {
    digitalWrite(LED, HIGH);
  }
  else if (String(p).equals("0"))
  {
    digitalWrite(LED, LOW);
  }
  else {
    format_display();
    display.println(p);
    display.display();    
  }
  

}


void format_display () {
  //sets up basic formatting for when using the display
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE); 
  display.setCursor(0,0);
}