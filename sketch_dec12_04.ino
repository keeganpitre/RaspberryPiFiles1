//This is different from the 08_28 version. This one has a different method of reading the string from python as well as more pinouts (and the pinouts changed)
//Keegan Pitre, Sept 22, 2016
#include <HashMap.h>
#define INPUT_SIZE 30

//Pinout with accompanying bool (Just the way the arduino reads the string sent from python)
//const int chargeOnBoardPin1 = 13; //Pin for turning on charging board directly using mosfet on Board 1
const int chargeOnBoardPin2 = 10; //Pin for turning on charging board directly using mosfet on Board 2
//const int chargeRelayPin1 = 11; //Gives positive voltage to capacitor charger 1
const int chargeRelayPin2 = 12; //Gives positive voltage to capacitor charger 2
const int firePin1 = 9; //Firing Pin 1
const int railDischarge = 6; //Rail discharge 
const int vehicleOnPin = 7; //Turns on relay that controls main power
const int emergShutdownPin = 3; 
const int connectedPin = 5; // Lights up LED when program connected
const int connectBank2 = 8; //Connects the second bank of caps to the first 
const int laserPin = 4; //Turns laser on and off
const int chargeValPin = 13;

//Analog Pinout
const int voltageMonitorPin1 = A0; //Monitors capacitor bank 1
const int voltageMonitorPin2 = A1; //Monitor capacitor bank 2 

//Defines assiciative array - The number must reflect the number of elements in the array. 
//Update every time an element is added
CreateHashMap(mypin, char, int, 10);

//Other Necessary Variables
int setOutput=0;
int cap_voltage1;
int cap_voltage2;
char ind;
char on_off_ind;
String send_char;
String send_char2;
bool writeVal;
bool timerVar = 0;
long start=15;
//Safety Value that turns machine off if arduino sees more then X number of volts
int safety_cap_val;
int safety_limit = 50;
int charge_led_ind = 30;  

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(5);
  
//Initializes Pins
  //pinMode(chargeOnBoardPin1, OUTPUT); //$ 13
  pinMode(chargeOnBoardPin2, OUTPUT); //% 12
 // pinMode(chargeRelayPin1, OUTPUT); //( 11
  pinMode(chargeRelayPin2, OUTPUT); //) 10
  pinMode(firePin1, OUTPUT); //& 9
  pinMode(vehicleOnPin, OUTPUT); //* 7
  pinMode(connectBank2, OUTPUT); //: 3
  pinMode(laserPin, OUTPUT); //! 4
  pinMode(railDischarge, OUTPUT); //k 6
  pinMode(chargeValPin, OUTPUT); //High when caps>30V
 
//Pins that turn on the mosfets for the charging board must be started high - this means charging is off. 
//All other pins can start low #logic
//  digitalWrite(chargeOnBoardPin1, 1);
  digitalWrite(chargeOnBoardPin2, 1);
  digitalWrite(railDischarge, 1);

//Sets up associative array
  //mypin['('] = chargeOnBoardPin1;
  mypin['%'] = chargeOnBoardPin2;
  //mypin[')'] = chargeRelayPin1;
  mypin['('] = chargeRelayPin2;
  mypin['&'] = firePin1;
  mypin['*'] = vehicleOnPin;
  mypin['5'] = connectBank2;
  mypin['!'] = laserPin;
  mypin['k'] = railDischarge;
}

void loop() {
//safety feature, if arduino doesn't receive data for more then 3 seconds it shuts down the vehicle
  if (Serial.available() == 0) {
    if (timerVar==0){
      start = millis();
      timerVar = 1;
    }
    long finished=millis();
    long elapsed=finished-start;
    if (elapsed > 2000 & start != 72){
      digitalWrite(10,1);
      //digitalWrite(chargeOnBoardPin1, 1);
      digitalWrite(chargeRelayPin2, 0);
      digitalWrite(vehicleOnPin, 0);
      digitalWrite(connectedPin, 0);
    }
    delay(10);  
  }
  
//When arduino see data on the serial line it performs the following loop
  while (Serial.available() > 0) {
    timerVar=0;
    if (setOutput==0){
//Reads data from serial line
      char input[INPUT_SIZE +1];
      byte size = Serial.readBytes(input,INPUT_SIZE);
      input[size]=0;
//Parses data using ","
      char* command = strtok(input, ",");
//All data will come in the form of an ascii char followed by a 1 or zero (ascii 48 and 49)
//This code seperates it into two variables which are used to determine commands
      while (command != 0){
        char str[2];
        ind = command[0];
        on_off_ind = command[1];
//        Serial.println(ind);
//        Serial.println(on_off_ind);
//        Serial.println(command);

//Every time arduino see "+1" it'll send the voltage values for the capacitor
        if (ind == 43){
          if (on_off_ind == 49){
            cap_voltage1=analogRead(voltageMonitorPin1);
            cap_voltage2=analogRead(voltageMonitorPin2);
            send_char = "+";
            send_char2 = "-";
            Serial.println(","+send_char+cap_voltage1+","+send_char2+cap_voltage2);
//            Serial.println(send_char2+cap_voltage2);
          }
        }

//At the beginning the arduino will ping every port, the arduino responds with an "@" when it receives a "#"
        else if (ind == 35){
          Serial.println("@");
          digitalWrite(connectedPin, HIGH); 
        }
        else {
          if (on_off_ind == 48) {
            writeVal=0;
          }
          else if (on_off_ind == 49) {
            writeVal=1;
          }
//          Serial.println(ind);
//          Serial.println(mypin[ind]);
//          Serial.println(writeVal);
          digitalWrite(mypin[ind],writeVal);
//          Serial.println(mypin[ind], writeVal);
        }
//        Serial.println(command);
        command = strtok(0,","); 
      }
    }
  }
  safety_cap_val = analogRead(voltageMonitorPin1);
  safety_cap_val = safety_cap_val*.43;
  if (safety_cap_val > safety_limit){
      //igitalWrite(chargeOnBoardPin1, 1);
      digitalWrite(chargeRelayPin2, 0);
      digitalWrite(connectedPin, 0);
      digitalWrite(railDischarge, 1);
  }
  if (safety_cap_val > charge_led_ind){
      digitalWrite(chargeValPin,1);
  }
  else {
      digitalWrite(chargeValPin,0);  
  }
}

