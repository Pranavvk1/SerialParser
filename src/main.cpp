#include <Arduino.h>
#include <vector>

/*two inputs- clk and x (on INPUT_PIN)
*int vector- used to store parsed ints.
*counter used to count till 3 - increment whenever clk goes high
*/

int CLK_PIN = 2;
int INPUT_PIN = 15;
int END_SIGNAL_PIN = 4;
int FSM_RST_PIN = 13;

int readMode() {
  digitalWrite(FSM_RST_PIN, LOW);
  delay(1000);
  digitalWrite(FSM_RST_PIN, HIGH);
  digitalWrite(CLK_PIN, HIGH);
  int num = digitalRead(INPUT_PIN);
  while(!digitalRead(END_SIGNAL_PIN)) {
    delay(1000);
    digitalWrite(CLK_PIN, LOW);
    delay(1000);
    digitalWrite(CLK_PIN, HIGH);
  }
  return num;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(CLK_PIN, OUTPUT);
  pinMode(INPUT_PIN, INPUT);
  pinMode(END_SIGNAL_PIN, INPUT);
  pinMode(FSM_RST_PIN, OUTPUT);
  Serial.begin(115200);
}

int counter = 2;
bool prevClk = false;
bool prevEnd = false;

void loop() {
  // put your main code here, to run repeatedly:
  std::vector<int> intVec;
  int isChar = readMode();
  if(isChar) {
    Serial.println("reading chars");
  } else {
    Serial.println("reading ints");
  }
  delay(1000);
  digitalWrite(CLK_PIN, LOW);
  delay(1000);
  digitalWrite(CLK_PIN, HIGH);
  Serial.println("read starting from next cycle");
  delay(1000);
  digitalWrite(CLK_PIN, LOW);

  while(!digitalRead(END_SIGNAL_PIN)) {
    int num = 0;
    while (counter >= 0) { //read num
      delay(1000);
      digitalWrite(CLK_PIN, HIGH);
      if(digitalRead(INPUT_PIN)) {
        num += 1 << counter;
      }
      counter--;
      delay(1000);
      digitalWrite(CLK_PIN, LOW);
    } 
    counter = 2;
    if(num != 1) intVec.push_back(num);
  }

  for(int i : intVec) {
    if(isChar) {
      Serial.print((char) (i + 97));
    } else {
      Serial.print(i);
    }
  }
  Serial.println();
}


