#include <WiFi.h>
#include <HCSR04.h>

#include "FirebaseESP32.h"

#define FIREBASE_HOST ""
#define FIREBASE_AUTH ""
#define WIFI_SSID ""
#define WIFI_PASSWORD ""

UltraSonicDistanceSensor distanceSensor(17,5);//initialisation class HCSR04 (trig pin , echo pin)

#define led1 4
#define led2 16
#define ldr 36
#define pir 18

FirebaseData firebaseData;

String path = "/Node1";
int oldDistance;
int newDistance;

int oldAdcLdr;
int newAdcLdr;

int stateMotion = LOW;             // default tidak ada gerakan
int valMotion = 0;                 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(ldr,INPUT);
  pinMode(pir,INPUT);
    
  initWifi();

  oldDistance = distanceSensor.measureDistanceCm();
  oldAdcLdr = analogRead(ldr);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(500);

  valMotion = digitalRead(pir);   // read sensor value
  if (valMotion == HIGH) {           // check if the sensor is HIGH
    if (stateMotion == LOW) {
      Firebase.setInt(firebaseData, path + "/pir", 1);
      stateMotion = HIGH;       // update variable state to HIGH
    }
  } 
  else {
    if (stateMotion == HIGH){
      Firebase.setInt(firebaseData, path + "/pir", 0);
      stateMotion = LOW;       // update variable state to LOW
    }
  }

  //ambil nilai dari sensor ultarsonic dan kirim ke firebase
  newDistance = distanceSensor.measureDistanceCm();
  Serial.println(newDistance);
  if(newDistance != oldDistance){
    Firebase.setInt(firebaseData, path + "/distance", newDistance);
    oldDistance = newDistance; 
  }

  //ambil nilai dari sensor LDR dan kirim ke firebase
  newAdcLdr = analogRead(ldr);
  Serial.println(newAdcLdr);
  if(newAdcLdr != oldAdcLdr){
    Firebase.setDouble(firebaseData, path + "/ldr", newAdcLdr);
    oldAdcLdr = newAdcLdr;
  }
  
  //get value /Node1/lampu1
  if(Firebase.getInt(firebaseData, path + "/lampu1")){
    /*Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.print("VALUE: ");
    Serial.println(firebaseData.intData());
    */
    if(firebaseData.intData() == 0)
      digitalWrite(led1,0);
    else
      digitalWrite(led1,1);    
  }
 

  //get value /Node1/lampu2
  if(Firebase.getInt(firebaseData, path + "/lampu2")){
    /*Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.print("VALUE: ");
    Serial.println(firebaseData.intData());
    */
    if(firebaseData.intData() == 0)
      digitalWrite(led2,0);
    else
      digitalWrite(led2,1);
  }
}

void initWifi(){
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  //tiny, small, medium, large and unlimited.
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
}
