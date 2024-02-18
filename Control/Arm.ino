#include<SoftwareSerial.h>
#include<Servo.h>

// define servos
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

// Below are servos current position and previous position.
int servo1Pos, servo2Pos, servo3Pos, servo4Pos, servo5Pos, servo6Pos;
int servo1PPos, servo2PPos, servo3PPos, servo4PPos, servo5PPos, servo6PPos;

//  Records positions
int servo1SP[30], servo2SP[30], servo3SP[30], servo4SP[30], servo5SP[30], servo6SP[30];
SoftwareSerial Bluetooth(3, 4)   // pin3 is for bluetooth receiving data, 4 for transmittting data

int speedDelay = 20;
int index = 0;
String dataIn = "";


void setup() {
  // put your setup code here, to run once:
  // connect the board to the servos
  servo1.attach(5);
  servo2.attach(6);
  servo3.attach(7);
  servo4.attach(8);
  servo5.attach(9);
  servo6.attach(10);

  Bluetooth.begin(38400);
  Bluetooth.setTimeOut(1);
  delay(20);

  servo1PPos = 90;
  servo1.write(servo1PPos);

  servo2PPos = 150;
  servo2.write(servo2PPos);

  servo3PPos = 35;
  servo3.write(servo3PPos);

  servo4PPos = 140;
  servo4.write(servo4PPos);

  servo5PPos = 85;
  servo5.write(servo5PPos);

  servo6PPos = 80;
  servo6.write(servo6PPos); 
}

void loop() {
  // put your main code here, to run repeatedly:
  
  // check for input
  if (Bluetooth.available() > 0) {
    dataIn = Bluetooth.readString();
  }

  if (dataIn.startsWith("s1")) {
    String dataIn1 = dataIn.substring(2, dataIn.length());
    servo1Pos = dataIn1.toInt();

    // use loop to make the movement of servo smooth
    if (servo1PPos > servo1Pos) {
      for (int i = servo1PPos; i >= servo1Pos; --i) {
        servo1.write(i);
        delay(20);
      }
    }
    if (servo1PPos < servo1Pos) {
      for (int i = servo1PPos; i <= servo1Pos; ++i) {
        servo1.write(i);
        delay(20);
      }
    }
    servo1PPos = servo1Pos;
  }

  if (dataIn.startsWith("s2")) {
    String dataIn1 = dataIn.substring(2, dataIn.length());
    servo2Pos = dataIn.toInt();

    if (servo2PPos > servo2Pos) {
      for (int i = servo2PPos; i >= servo2Pos; --i) {
        servo2.write(i);
        delay(20);
      }
    }
    if (servo2PPos < servo2Pos) {
      for (int i = servo2PPos; i <= servo2Pos; ++i) {
        servo2.write(i);
        delay(20);
      }
    }
    servo2PPos = servo2Pos;
  }


  if (dataIn.startsWith("s3")) {
    String dataIn1 = dataIn.substring(2, dataIn.length());
    servo3Pos = dataIn.toInt();

    if (servo3PPos > servo3Pos) {
      for (int i = servo3PPos; i >= servo3Pos; --i) {
        servo3.write(i);
        delay(20);
      }
    }
    if (servo3PPos < servo3Pos) {
      for (int i = servo3PPos; i <= servo3Pos; ++i) {
        servo3.write(i);
        delay(20);
      }
    }
    servo3PPos = servo3Pos;
  }

  
  if (dataIn.startsWith("s4")) {
    String dataIn1 = dataIn.substring(2, dataIn.length());
    servo4Pos = dataIn.toInt();

    if (servo4PPos > servo4Pos) {
      for (int i = servo4PPos; i >= servo4Pos; --i) {
        servo4.write(i);
        delay(20);
      }
    }
    if (servo4PPos < servo4Pos) {
      for (int i = servo4PPos; i <= servo4Pos; ++i) {
        servo4.write(i);
        delay(20);
      }
    }
    servo4PPos = servo4Pos;
  }


  if (dataIn.startsWith("s5")) {
    String dataIn1 = dataIn.substring(2, dataIn.length());
    servo5Pos = dataIn.toInt();

    if (servo5PPos > servo5Pos) {
      for (int i = servo5PPos; i >= servo5Pos; --i) {
        servo5.write(i);
        delay(20);
      }
    }
    if (servo5PPos < servo5Pos) {
      for (int i = servo5PPos; i <= servo5Pos; ++i) {
        servo5.write(i);
        delay(20);
      }
    }
    servo5PPos = servo5Pos;
  }


  if (dataIn.startsWith("s6")) {
    String dataIn1 = dataIn.substring(2, dataIn.length());
    servo6Pos = dataIn.toInt();

    if (servo6PPos > servo6Pos) {
      for (int i = servo6PPos; i >= servo6Pos; --i) {
        servo6.write(i);
        delay(20);
      }
    }
    if (servo6PPos < servo6Pos) {
      for (int i = servo6PPos; i <= servo6Pos; ++i) {
        servo6.write(i);
        delay(20);
      }
    }
    servo6PPos = servo6Pos;
  }
  
  if (dataIn.startsWith("RUN")) {
    mainRun();
  }

  if (dataIn.startsWith("Save")) {
    servo1SP[index] = servo1PPos;
    servo2SP[index] = servo2PPos;
    servo3SP[index] = servo3PPos;
    servo4SP[index] = servo4PPos;
    servo5SP[index] = servo5PPos;
    servo6SP[index] = servo6PPos;
    index++;  
  }

  if (dataIn.startsWith("RESET")) {
    // free all dataArrays
    memset(servo1SP, 0, sizeof(servo1SP)); 
    memset(servo2SP, 0, sizeof(servo2SP));
    memset(servo3SP, 0, sizeof(servo3SP));
    memset(servo4SP, 0, sizeof(servo4SP));
    memset(servo5SP, 0, sizeof(servo5SP));
    memset(servo6SP, 0, sizeof(servo6SP));
    index = 0;
  }


}

// The button "RUN" is also "PAUSE"
// Perform all saed steps
void mainRun() {
  while(dataIn != "RESET") {
    for (int i = 0; i < index - 1; ++i) {
      if (Bluetooth.available()) {
        dataIn = Bluetooth.readString();

        if (dataIn == "PAUSE") {           
          while (dataIn != "RUN") {         
            if (Bluetooth.available()) {
              dataIn = Bluetooth.readString();
              if (dataIn == "RESET") {     
                break;
              }
            }
          }
        }

        if (dataIn.startsWith("ss")) {
          String dataInS = dataIn.substring(2, dataIn.length());
          speedDelay = dataInS.toInt(); // Change servo speed by changing speedDelay
        }
      }

      // Servo 1
      if (servo1Pos[i] > servo1Pos[i + 1]) {
        for (int j = servo1Pos[i]; j >= servo1Pos[i + 1]; j--) {
          servo1.write(j);
          delay(speedDelay);
        }
      }
      if (servo1Pos[i] < servo1Pos[i + 1]) {
        for (int j = servo1Pos[i]; j <= servo1Pos[i + 1]; j++) {
          servo1.write(j);
          delay(speedDelay);
        }
      }

      // Servo 2
      if (servo2SP[i] > servo2SP[i + 1]) {
        for ( int j = servo2SP[i]; j >= servo2SP[i + 1]; j--) {
          servo2.write(j);
          delay(speedDelay);
        }
      }
      if (servo2SP[i] < servo2SP[i + 1]) {
        for ( int j = servo2SP[i]; j <= servo2SP[i + 1]; j++) {
          servo2.write(j);
          delay(speedDelay);
        }
      }

      // Servo 3
      if (servo3SP[i] > servo3SP[i + 1]) {
        for (int j = servo3SP[i]; j >= servo3SP[i + 1]; j--) {
          servo3.write(j);
          delay(speedDelay);
        }
      }
      if (servo3SP[i] < servo3SP[i + 1]) {
        for ( int j = servo3SP[i]; j <= servo3SP[i + 1]; j++) {
          servo3.write(j);
          delay(speedDelay);
        }
      }

      // Servo 4
      if (servo4SP[i] > servo4SP[i + 1]) {
        for (int j = servo4SP[i]; j >= servo4SP[i + 1]; j--) {
          servo4.write(j);
          delay(speedDelay);
        }
      }
      if (servo4SP[i] < servo4SP[i + 1]) {
        for (int j = servo4SP[i]; j <= servo4SP[i + 1]; j++) {
          servo4.write(j);
          delay(speedDelay);
        }
      }

      // Servo 5
      if (servo5SP[i] > servo5SP[i + 1]) {
        for (int j = servo5SP[i]; j >= servo5SP[i + 1]; j--) {
          servo5.write(j);
          delay(speedDelay);
        }
      }
      if (servo5SP[i] < servo5SP[i + 1]) {
        for (int j = servo5SP[i]; j <= servo5SP[i + 1]; j++) {
          servo5.write(j);
          delay(speedDelay);
        }
      }

      // Servo 6
      if (servo6SP[i] > servo6SP[i + 1]) {
        for (int j = servo6SP[i]; j >= servo6SP[i + 1]; j--) {
          servo6.write(j);
          delay(speedDelay);
        }
      }
      if (servo6SP[i] < servo6SP[i + 1]) {
        for ( int j = servo6SP[i]; j <= servo6SP[i + 1]; j++) {
          servo6.write(j);
          delay(speedDelay);
        }
      }
    }
  }
}