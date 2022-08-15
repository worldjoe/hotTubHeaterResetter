#define FLAMESENSORPIN A1
// lowest and highest sensor readings:
const int sensorMin = 0;     // sensor minimum
const int sensorMax = 1024;  // sensor maximum
const int output =13;

void setup() {
  // put your setup code here, to run once:
  pinMode(FLAMESENSORPIN, INPUT);
  pinMode(output, OUTPUT);
  Serial.begin(9600);
  Serial.println("Joey Setup");
  delay(4000); // wait for 10 seconds before starting
}

void loop() {
  // put your main code here, to run repeatedly:
  float sensorReading = analogRead(FLAMESENSORPIN);
  int range = map(sensorReading, sensorMin, sensorMax, 0, 3);
  //Serial.println(flame);
  // range value:
  switch (range) {
  case 0:    // A fire closer than 1.5 feet away.
    Serial.println("** Close Fire **");
    break;
  case 1:    // A fire between 1-3 feet away.
    Serial.println("** Distant Fire **");
    break;
  case 2:    // No fire detected.
    Serial.println("No Fire. Resetting power");
    // send the signal to turn off the water pump
    digitalWrite(output, HIGH);
    // wait 5 seconds before telling the relay to start the power again
    delay(5000);
    digitalWrite(output, LOW);
    // wait 7 seconds for the pump to start pumping and give the heater time to attemp to relight the flame
    // we want to mke sure we give the system time to work before we attempt to cycle the power again.
    delay(7000);
    Serial.println("done waiting");
    break;
  }
  delay(5000);  // delay 30 seconds between reads
}
