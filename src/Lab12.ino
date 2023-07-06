// libraries
#include "MQTT.h"
#include "oled-wing-adafruit.h"

SYSTEM_THREAD(ENABLED);

void callback(char *topic, byte *payload, unsigned int length);

MQTT client("lab.thewcl.com", 1883, callback);

OledWingAdafruit display;

#define LED D7

void setup(){

  display.setup();

  pinMode(LED, OUTPUT);

  client.subscribe("benLab12");
}
void loop(){

  if (client.isConnected())
  {
    //mantains client
    client.loop();
  }
  else {
    //subscribes and connects if not connected
    client.connect(System.deviceID());
    client.subscribe("benLab12");

  }
  display.loop();

  //publishes information if oled buttons are pressed
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
void callback(char *topic, byte *payload, unsigned int length){
  //function called when something is published to mqtt 

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