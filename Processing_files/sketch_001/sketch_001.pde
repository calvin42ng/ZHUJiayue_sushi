import processing.serial.*;

Serial myPort; 
String receivedData = "";
int number;
PImage[] imgs = new PImage[3];

void setup() {
  size(600, 270);
  printArray(Serial.list());
  myPort = new Serial(this, Serial.list()[2], 9600);
  myPort.bufferUntil('\n');
  imgs[0] = loadImage("01.jpg");
  imgs[1] = loadImage("02.jpg");
  imgs[2] = loadImage("03.jpg");
}

void draw() {
  background(0);
  fill(255);
  number = int(receivedData);
  if(number == 613){
    image(imgs[0], 0, 0);
  }
  if(number == 672){
    image(imgs[1], 0, 0);
  }
  if(number == 100){
    image(imgs[3], 0, 0);
  }   
}


void serialEvent(Serial p) {
  receivedData = p.readStringUntil('\n'); 
  if (receivedData != null) {
    receivedData = trim(receivedData); 
    println(receivedData); 
  }
}
