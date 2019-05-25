/* 
 Written by Jesper Rasehorn https://github.com/TheRealKettu/Raspberry-PiSlots
 
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

// variables and etc
int ledPin = 13; //just to turn off the led.
int coinamt = 0; //Just remembers how many coins are inside
const byte coinSig = 2;

bool previousCoinSignal = false;


void setup() {
  Serial.begin(115200); //Setting the pinmodes and serial.
  pinMode(ledPin, OUTPUT);
  pinMode( coinSig, INPUT_PULLUP);
  previousCoinSignal = digitalRead(coinSig);
  servo.attach(9);
  servo.write(60);
}


void cashout() { //Coin hopper code. Somewhat complete, works with my shitty 3d printed cardboard hopper.
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



void loop() { //Main code


  if (Serial.available() > 0) {
    char ch = Serial.read();
    delay(5);
    if (ch == 'c') { //Clears the bank if needed.
      coinamt = 0;
      Serial.println("Bank Value cleared.");
    }
    if (ch == 'p') { //Cashouts.
      cashout();
    }
  }

  byte currentCoinSignal = digitalRead(coinSig);

  if (currentCoinSignal != previousCoinSignal) {
    //save the state for the next iteration
    previousCoinSignal = currentCoinSignal;

    if (currentCoinSignal == HIGH) { //Send the coin signal to the raspberry pi.
     Serial.println("coin");    
    }
    
  }
}
