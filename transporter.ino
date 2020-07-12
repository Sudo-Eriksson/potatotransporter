#include <SoftwareSerial.h>

int FIRE_SIGNAL_PIN = 6;

// Setup the software serial
SoftwareSerial serial_connection(10,11);

// Variables for the bluetooth communication
#define BUFFER_SIZE 3                                  //TODO: CHECK IF THIS IS THE CORRECT AMOUNT OF BYTES
char inData[BUFFER_SIZE];
char inChar=-1;
int i=0;
int remaining_bytes;
String indata_str;

//TODO: SETUP THE FIRE PIN

bool getCtrlSignal(){
  /*
  * Check if we have got enough bytes for a message. If so save the message.
  * return: true - If we got a message.
  * return: false - If we have no message.
  */
  int byte_count = serial_connection.available();

  if(byte_count>=BUFFER_SIZE){                          // Om tillräckligt många bytes har kommit
    remaining_bytes=byte_count - BUFFER_SIZE;           // Hur många bytes till övers som kommit
    //first_bytes = BUFFER_SIZE;                        // Hur många bytes vi vill läsa

    // Läs datan som blev skickad
    for(i=0;i<BUFFER_SIZE;i++){
      inChar=serial_connection.read();
      inData[i]=inChar;
      }
    // inData[i]="\0";
    indata_str = String(inData);

    return true;    // Här har vi alltså fått tillräckligt många bytes
  }
  else{
    return false;   // Här har inte tillräckligt många kommit
  }
}

void cleanBluetooth(){
  /*
  * Method for removing unwanted bytes.
  */
    for(i=0;i<remaining_bytes;i++){
      inChar=serial_connection.read();    // Här läser vi bara de bytes som blev över. Tar bort dem så vi inte får buffer overrun.
     }
  }

void checkForSignal(){
  /*
  * Check if we have a new control signal. If so, verify the message and then fire if the message is correct.
  */
  // If we have a new control signal
  if(getCtrlSignal()){
      //TODO: IF MESSAGE EQUAL TO 123, CALL FOR fireTransporter.
      if(indata_str == "123"){
           fireTransporter(10000);
      }
      cleanBluetooth();
    }
}

void fireTransporter(int sparktime){
    /*
    * Fire the transporter.
    * param: sparktime - The amount of milliseconds the spark should be fired.
    */

    digitalWrite(FIRE_SIGNAL_PIN, HIGH);
    delay(sparktime);
    digitalWrite(FIRE_SIGNAL_PIN, LOW);
}

void setup(){
  Serial.begin(9600);
  serial_connection.begin(9600);

  // Send to the python program that the transporter is ready.
  Serial.println("Sending ready to python");
  serial_connection.println("ready");

  pinMode(FIRE_SIGNAL_PIN, OUTPUT);
}

void loop(){
    checkForSignal();
 }