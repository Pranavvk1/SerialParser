#include <Arduino.h>
#include <vector>

/*two inputs- clk and x (on input_pin)
*int vector- used to store parsed ints.
*counter used to count till 3 - increment whenever clk goes high
*/

std::vector<int> intVec;
int clk_pin = 2;
int input_pin = 15;
int end_signal_pin = 4;
//int clken_pin = 16;

void setup() {
  // put your setup code here, to run once:
  pinMode(clk_pin, OUTPUT);
  pinMode(input_pin, INPUT);
  pinMode(end_signal_pin, INPUT);
 // pinMode(clken_pin, INPUT);
  Serial.begin(115200);
}

int counter = 2;
bool prevClk = false;
bool prevEnd = false;

void loop() {
  // put your main code here, to run repeatedly:
  int num = 0;
  //if(digitalRead(clken_pin)){
    while (counter >= 0) {
      delay(1000);
      digitalWrite(clk_pin, HIGH);
      if(digitalRead(input_pin)) {
        num += 1 << counter;
      }
      counter--;
      delay(1000);
      digitalWrite(clk_pin, LOW);
    }
    Serial.println(num);
  //}
  counter = 2;
  if(num != 1) intVec.push_back(num);

  if(digitalRead(end_signal_pin)){
    if(!prevEnd) {
      for(int i : intVec) {
        Serial.print(i);
      }
      prevEnd = true;
    }
  } else {
    prevEnd = false;
  }

}

