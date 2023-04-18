
void setup() {

  Serial.begin(9600);
}

void loop() {
  // read the input on analog pin 0:
  int gsr = analogRead(A0);
  // print out the value you read:
  Serial.print(gsr);
  Serial.print(" ");

  int temp = analogRead(A1);
  Serial.print(temp);
    Serial.print(" ");
  int acc = random(300,500);
  Serial.print(acc);
  Serial.println();
  delay(1000);  // delay in between reads for stability
}
