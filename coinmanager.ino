/* 
 This is the money controller for the raspberry pi slotmachine. 
 115200 BAUDRATE

 Outgoing commands;
 coin :sends a coin pulse

 incoming;
 c :clears bank
 p :cashout
 
 TODO:
 Coin hopper code. ( somewhat complete, works with the 3d printed thing ) 
*/

#include <Servo.h>
Servo servo;

// variables
int coinamt = 0;
const byte coinSig = 2;

bool previousCoinSignal = false;


void setup() {
  Serial.begin(115200);
  pinMode( coinSig, INPUT_PULLUP);
  previousCoinSignal = digitalRead(coinSig);
  servo.attach(9);
  servo.write(60);
}


void cashout() {
  Serial.println("Cashout command received. Paying out.");
    
  coinamt = Serial.parseInt();
  
   delay(50);
   while (coinamt>0) {
   servo.write(10);  // Turn Servo Left to 10 degrees
   delay(200);          // Wait
   servo.write(60);   // Turn Servo Left to 60 degrees
   delay(200);          // Wait
    coinamt--; 
   delay(50);   // wait
   }
   coinamt = 0;
}



void loop() {


  if (Serial.available() > 0) {
    char ch = Serial.read();
    delay(5);
    if (ch == 'c') {
      coinamt = 0;
      Serial.println("Bank Value cleared.");
    }
    if (ch == 'p') {
      cashout();
    }
  }

  byte currentCoinSignal = digitalRead(coinSig);

  if (currentCoinSignal != previousCoinSignal) {
    //save the state for the next iteration
    previousCoinSignal = currentCoinSignal;

    if (currentCoinSignal == HIGH) {
     Serial.println("coin");     
    }
    
  }
}
