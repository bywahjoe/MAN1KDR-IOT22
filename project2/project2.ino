#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#define BLYNK_NO_BUILTIN
#define BLYNK_NO_FLOAT    
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL_F9xpXCF"
#define BLYNK_DEVICE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "dJLgdN0EJt1shUnKJnEJTbpD1irqhB79"
//PIN
#define led 32
#define ldr 33

//Blynk Wifi Config
char ssid[] = "robotku";
char pass[] = "robot1234";
char auth[] = BLYNK_AUTH_TOKEN;

BlynkTimer timer;
void sendSensorLDR(){
  int val=analogRead(ldr);
  Serial.print("Val LDR:");Serial.println(val);
  Blynk.virtualWrite(V4,val);
}
BLYNK_WRITE(V1) {
  int btn = param.asInt(); //Cek Data Button
  Serial.print("BUTTON:"); Serial.println(btn);

  if (btn == 1)digitalWrite(led, HIGH); //1-ON , 0-OFF
  if (btn == 0)digitalWrite(led, LOW);
}
void setup() {
  Serial.begin(115200);
  pinMode(led, OUTPUT);             //Led Output
  
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);   //Blynk Config
  Serial.println(Blynk.connected());
  Serial.println("OK");
  timer.setInterval(1000L, sendSensorLDR);  //Timer Sensor
}
void loop() {
  Blynk.run();
  timer.run();
}
