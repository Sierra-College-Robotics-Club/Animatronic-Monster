
#define TrigPin1 4
#define EchoPin1 5
#define TrigPin2 3
#define EchoPin2 2

const unsigned long TIMEOUT_USRF_US = 30000UL; // ~5 m max range

//TODO: cut and bridge solder bridges acording to diagram. Complete this example/test sketch

void setup() {
  pinMode(TrigPin1, OUTPUT);
  pinMode(EchoPin1, INPUT);
  pinMode(TrigPin2, OUTPUT);
  pinMode(EchoPin2, INPUT);

  digitalWrite(TrigPin1, LOW);
  digitalWrite(TrigPin2, LOW);
  
  Serial.begin(115200);

}

void loop() {
  int d1 = getDistance(TrigPin1, EchoPin1);
  delay(50); //a bit of time to avoid crosstalk
  int d2 = getDistance(TrigPin2, EchoPin2);

  Serial.print("Sensor 1: ");
  Serial.print(d1);
  Serial.print(" cm\tSensor 2: ");
  Serial.print(d2);
  Serial.println(" cm");

  delay(100);
}

int getDistance(int trigPin, int echoPin){
  // Trigger a 10 us pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo pulse length in microseconds
  unsigned long duration = pulseIn(echoPin, HIGH, TIMEOUT_USRF_US);

  if (duration == 0) {
    return -1; // timeout / out of range
  }

  // Speed of sound: 343 m/s = 0.0343 cm/us
  // Divide by 2 because the sound travels out and back
  int distanceCm = (int)(duration * 0.0343 / 2.0);

  return distanceCm;
}