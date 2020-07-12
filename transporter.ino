#include <SoftwareSerial.h>

// Setup the software serial
SoftwareSerial serial_connection(10,11);

// Variables for the bluetooth communication
#define BUFFER_SIZE 16;
char inData[BUFFER_SIZE];
char inChar=-1;
int i=0;
int remaining_bytes;
String indata_str;


bool getCtrlSignal(){

  int byte_count = serial_connection.available();

  if(byte_count>=BUFFER_SIZE){                          // Om tillräckligt många bytes har kommit
    remaining_bytes=byte_count - BUFFER_SIZE;           // Hur många bytes till övers som kommit
    //first_bytes = BUFFER_SIZE;                        // Hur många bytes vi vill läsa

    // Läs datan som blev skickad
    for(i=0;i<BUFFER_SIZE;i++){
      inChar=serial_connection.read();
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

void checkForSignal(){
  // If we have a new controll signal
  if(getCtrlSignal()){
      #TODO: SET FIRE PIN TO HIGH HERE IF EQUAL TO 123
      cleanBluetooth();
    }
}

void setup(){
  Serial.begin(9600);
  serial_connection.begin(9600);

  // Send to the python program that the drone is ready.
  Serial.println("Sending ready to python");
  altSerial.println("ready");
}

void loop(){
    checkForSignal();
 }
