#include <Arduino.h>
#include <vector>

/*two inputs- clk and x (on input_pin)
*int vector- used to store parsed ints.
*counter used to count till 3 - increment whenever clk goes high
*/

std::vector<int> intVec;
int clk_pin = 2;
int input_pin = 15;
int end_signal_pin = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(clk_pin, INPUT);
  pinMode(input_pin, INPUT);
  pinMode(end_signal_pin, INPUT);
  Serial.begin(115200);
}

int counter = 0;
bool prevClk = false;

void loop() {
  // put your main code here, to run repeatedly:
  int num = 0;
  while (counter <= 2) {
    if(digitalRead(clk_pin) && !prevClk) {
      if(digitalRead(input_pin)) {
        num += 1 << counter;
      }
      counter++;
      prevClk = true;
    } else if(!digitalRead(clk_pin)) {
      prevClk = false;
    }
  }
  intVec.push_back(num);

  if(digitalRead(end_signal_pin)){
    for(int i : intVec) {
      Serial.println(i);
    }
  }
}

