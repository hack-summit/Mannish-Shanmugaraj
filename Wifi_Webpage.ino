// Code Developed by Team Excalibur's.
//Mannish.S
//Madhumithaa.S
//Hariharan.R
//Prethikaa.M

#include <ESP8266WiFi.h>                                                  // Since We are Using NodeMCU microcontroller.

const char* ssid = "HUAWEI nova 3e";                                      //Predefined Wifi Connection to have Remote Access Wifi name.
const char* password = "789456123";                                       //Predefined Wifi Connection to have Remote Access Wifi password.

int ledPin = 13;                                                          //LED on pin 7 GPIO.

int analogIn = A0;                                                        //LDR Value pin. 
int ledState = LOW;
WiFiServer server(80);

void setup() 

{

  Serial.begin(115200);                                                   
  delay(10);
  ledState = LOW;
  pinMode(ledPin, OUTPUT);                                                 //Setting LED as Output
  digitalWrite(ledPin, ledState);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to... ");
  Serial.println(ssid);             

 //Begining Wifi Connection with SSID and PASSWORD.
 
  WiFi.begin(ssid, password);                                             //connect to wifi with given ssid and password

 
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);                                                          // Checks Every 1 Second.
    Serial.print(".");                                                    //Until Connection.
  }
  Serial.println("");
  Serial.println("WiFi connected");                                       //Wifi Connected.
 
                                                                          // Start the server
  server.begin();
  Serial.println("Server started");
 
                                                                          // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  
  }
 
void loop() 

{

  // Check if a client has connected
  
  WiFiClient client = server.available();
  
  if (!client)
  {
  
    return;
    
  }
 
  // Waiting Till The Client Sends Some Data
  
  Serial.println("new client");
  while(!client.available())
  {
  
    delay(1);
    
  }
 
  // Read the first line of the request
  
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  
  if (request.indexOf("cmd=TURN_ON_LED") != -1)
  {
    
    ledState = HIGH;         //TURNS ON LED.
    
  }
  else if (request.indexOf("cmd=TURN_OFF_LED") != -1)
  {
                     
    ledState = LOW;          //TURNS OFF LED.   
  }
  
  // Updateing The LED Status.
  
  digitalWrite(ledPin, ledState);
    if (request.indexOf("cmd=TURN_ON_LED") != -1)
  {
   
    ledState = HIGH;        //TURNS ON LED.
    
  }
  else if (request.indexOf("cmd=TURN_OFF_LED") != -1)
  {
     
    ledState = LOW;         //TURNS OFF LED.
    
  }
  // Update the LED based on ledState
  digitalWrite(ledPin, ledState);

  int photocell_value = analogRead(analogIn);
  
  client.println("HTTP/1.1 200 OK");                                                  //Approved Request.
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");

  
  //*****HTML CODE******//
  
  
  client.println("<html>");
  client.print("Led pin is now: "); 
  if(ledState == HIGH) {
    client.print("On");             
  } else {
    client.print("Off");
  }
  client.println("<br><br>");
  client.println("<a href=\"?cmd=TURN_ON_LED\"><button>Turn On </button></a>");          //Button to Turn ON.
  client.println("<a href=\"?cmd=TURN_OFF_LED\"><button>Turn Off </button></a>");        //Button to Turn OFF

  client.println("<p>The LDR value: <b> ");
  client.println(photocell_value); 
  client.println("</b></p>");
  client.println("<a href=\"?cmd=RELOAD_PHOTOCELL\"><button>Check for new photocell value</button></a>");
  client.print  ("<body style=background-color:yellow>");                                //set background to Yellow
 
  
  client.println("</html>");
  
 
 //*********END OF HTML CODE************
 
  
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}
