#include <Arduino.h>
#include <ServoTimer2.h>
#include <AltSoftSerial.h>

// Variables for the bluetooth communication
AltSoftSerial altSerial;

#define BUFFER_SIZE 10//4
char inData[BUFFER_SIZE];
char inChar=-1;
int i=0;

unsigned long last_data;

//int first_bytes;
int remaining_bytes;

String indata_str;

// ************* Bluetooth ************* //

bool getCtrlSignal(){

  int byte_count = altSerial.available();

  if(byte_count>=BUFFER_SIZE){                          // Om tillräckligt många bytes har kommit
    remaining_bytes=byte_count - BUFFER_SIZE;           // Hur många bytes till övers som kommit
    //first_bytes = BUFFER_SIZE;                        // Hur många bytes vi vill läsa

    // Läs datan som blev skickad
    for(i=0;i<BUFFER_SIZE;i++){
      inChar=altSerial.read();
      inData[i]=inChar;
      }
    inData[i]="\0";
    indata_str = String(inData);

    return true;    // Här har vi alltså fått tillräckligt många bytes
  }
  else{
    return false;   // Här har inte tillräckligt många kommit
  }
}

void cleanBluetooth(){
  // Dags att ta bort de bytes som var överflödiga.
    for(i=0;i<remaining_bytes;i++){
      inChar=altSerial.read();    // Här läser vi bara de bytes som blev över. Tar bort dem så vi inte får buffer overrun.
     }
  }

bool validateRecivedData(String data){
    #TODO: IMPLEMENT THIS
    return true;
}

void updateBaseThrust(){
  // If we have a new controll signal
  if(getCtrlSignal()){
      // If the data is not corrupted
      if(validateRecivedData(indata_str)){
        #TODO: SET FIRE PIN TO HIGH HERE
      }
      cleanBluetooth();
    }
}

// ************* Main Program ************* //

void setup(){
  Serial.println("-------- BLUETOOTH ---------");

  altSerial.begin(9600);

  // Send to the python program that the drone is ready.
  Serial.println("Sending start to python");
  altSerial.println("start");
}

void loop(){
    updateBaseThrust();
 }
