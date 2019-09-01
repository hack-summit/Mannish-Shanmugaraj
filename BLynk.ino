//Code From Blynk Which is a Open Source Software TO Implement IoT.
 
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = "RtywU1CZAssSTIWYlItAMvJF60MmwrSB";              //Authentication Token.
char ssid[] = "HUAWEI nova 3e";                                //Network Name.
char pass[] = "789456123";                                     //Network Password.
const int btnPin = 1;
int ldr = A0;
const int btnPin1 = 1;
int ldrStatus = analogRead (ldr);                              //To Read The Value of LDR Sensor.
WidgetLED led3(V3);                                            //Widget for First LED control.
WidgetLED led2(V2);                                            //Widget for Second LED control.
boolean btnState = false;                                       
boolean btnState1 = false;                                                   

//****LED1****
void buttonLedWidget()
{
  boolean isPressed = (digitalRead(btnPin) == LOW);
  if (isPressed != btnState)
  {
    if (isPressed)
    {
      led3.on();
    }
    else
    {
      led3.off();
    }
    btnState = isPressed;
  }
}

//****LED2****

void buttonLedWidget1()
{
  boolean isPressed = (digitalRead(btnPin1) == LOW);
  if (isPressed != btnState1)
  {
    if (isPressed)
    {
      led2.on();
    } else
    {
      led2.off();
    }
    btnState1 = isPressed;
  }
}


void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);  //Connecting via Blynk To Network.
  pinMode(btnPin, INPUT_PULLUP);
}
 // if(ldrStatus > 200)
//{
  //Serial.print("Ambient Light");
//  Blynk.virtualWrite(V0,)
//}

//else if(ldrStatus < 200)
//{
//  Serial.print("Not Ambient Light");
//}
//}

void loop()
{
  Blynk.run();   //To Interface With Blynk.
}
