int sensorPin0 = A0; 
int sensorPin1 = A1;
int sensorPin2 = A2;
int maxV = 0;
int a = 0;
int b = 0;
int c = 0;
String maxName;

long lastSerialTime = 0;     
long timeout = 5000;   // 5000ms

String lastName = "";
long lastNameChangeTime = 0;


int readSensor(int pin, int samples = 30) {
  long sum = 0;
  for (int i = 0; i < samples; i++) {
    sum += analogRead(pin);
    delay(5);
  }
  return sum / samples;
}

void setup() {
  Serial.begin(9600);
  lastSerialTime = millis();
  lastNameChangeTime = millis();
}

void loop() {
  a = readSensor(sensorPin0);
  b = readSensor(sensorPin1);
  c = readSensor(sensorPin2);

  String currentName = "d";  // default d
  int currentV = 0;

  if (a >= b && a >= c && a > 1) {
    currentName = "a";
    currentV = a;
  } else if (b >= a && b >= c && b > 1) {
    currentName = "b";
    currentV = b;
  } else if (c >= a && c >= b && c > 1) {
    currentName = "c";
    currentV = c;
  }

  if (currentName == lastName && currentName != "d") {
    long now = millis();
    if (now - lastNameChangeTime >= timeout) {
      Serial.println("d,0");
      lastSerialTime = now;
      lastName = "d";  
      lastNameChangeTime = now;
      delay(50);
      return; 
    }
  } else {
    lastName = currentName;
    lastNameChangeTime = millis();
  }


  if (currentName == "a" || currentName == "b" || currentName == "c") {
    Serial.print(currentName);
    Serial.print(",");
    Serial.println(currentV);
    lastSerialTime = millis();
  }
  if (currentName == "d") {
    Serial.println("d,0");
    lastSerialTime = millis();
  }

  delay(50);
}
