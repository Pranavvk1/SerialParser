#include <Arduino.h>
#include <vector>

/*two inputs- clk and x
*int vector- used to store parsed ints.
*counter used to count till 3 - increment whenever clk goes high
*/

std::vector<int> intVec;
int clk_pin = 0;
int input_pin = 0;
int end_signal_pin = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(clk_pin, INPUT);
  pinMode(input_pin, INPUT);
  pinMode(end_signal_pin, INPUT);
}

int counter = 0;

void loop() {
  // put your main code here, to run repeatedly

}

