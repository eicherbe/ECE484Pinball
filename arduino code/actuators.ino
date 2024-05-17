#include <IRremote.hpp>
#define IR_RECEIVE_PIN 10

int ledg = 6;
int ledy = 11;
int ledr = 8;

//L298N Pins
#define enA 7 //PWM pin
#define in1 6
#define in2 5

#define in3 2
#define in4 4
#define enB 3 //PWM pin


void setup()
{
  Serial.begin(115200);
  pinMode(ledg, OUTPUT);
  pinMode(ledy, OUTPUT);
  pinMode(ledr, OUTPUT);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Start the receiver

  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  digitalWrite(enA, HIGH);

  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  digitalWrite(enB, HIGH);
}

void loop() {
  if (IrReceiver.decode()) {
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX); // Print "old" raw data
    IrReceiver.printIRResultShort(&Serial); // Print complete received data in one line
    IrReceiver.printIRSendUsage(&Serial);   // Print the statement required to send this data
    IrReceiver.resume(); // Enable receiving of the next value

    // Green LED control
    if (IrReceiver.decodedIRData.decodedRawData == 0xB847FF00) { 
      
      // extend the actuator
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      delay(150); // actuator will stop extending automatically when reaching the limit
      // retracts the actuator
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      delay(150); // actuator will stop retracting automatically when reaching the limit 
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      delay(150); // actuator will stop retracting automatically when reaching the limit
    }

    // Yellow LED control
    if (IrReceiver.decodedIRData.decodedRawData == 0xBA45FF00) {
            
      // extend the actuator
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
      delay(150); // actuator will stop extending automatically when reaching the limit
      // retracts the actuator
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      delay(150); // actuator will stop retracting automatically when reaching the limit 
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      delay(150); // actuator will stop retracting automatically when reaching the limit
    } 
  }
}
