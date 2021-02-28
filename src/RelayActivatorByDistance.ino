int echoPin = 6;
int triggerPin = 7;
int outputLed = 8;

long duration;
float distance;

float isRoleActive = false;
int roleActivateDistance = 10;
int roleDeactivateDistance = 20;

int infiniteDistance = 500;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(outputLed, OUTPUT);
  digitalWrite(outputLed, HIGH);

  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58.2;
  
  Serial.println(distance);

  checkDistance(distance);
  
  delay(100);
}

void checkDistance(float distance) {
  if (distance > infiniteDistance) {
    return;
  }
  
  if (!isRoleActive) {
    if (distance < roleActivateDistance) {
      // activate
      isRoleActive = true;
      digitalWrite(outputLed, LOW);
    }
  }
  else {
    if (roleDeactivateDistance < distance) {
      // deactivate
      isRoleActive = false;
      digitalWrite(outputLed, HIGH);
    }
  }
}
