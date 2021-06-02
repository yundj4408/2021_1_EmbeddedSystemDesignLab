import processing.serial.*;

Serial Port;
float xPos = 0;

float xrp = 100;
float yrp = 608;

float inByte = 0;
float pre_data = 0;

int i = 0;

void setup() {
  size(1400, 900);
  background(255);
  
  printArray(Serial.list());
  
  Port = new Serial(this,Serial.list()[33], 115200);
  Port.bufferUntil('\n');
  
}

void draw() {
  
  backGround();
  
  stroke(0,0,255);
  line(xrp+xPos, yrp - pre_data   ,xrp+xPos, yrp - inByte);  //continuous graph
  if (xPos >= width) 
  {
    xPos = 0;
    background(255);        //Reset
    backGround();
  }
  
  else
  {
   xPos++; 
  }
  pre_data = inByte;
  i++;
}

void serialEvent (Serial myPort) {
  String inString = myPort.readStringUntil('\n');
  
  if(inString != null)
  {
    inString = trim(inString);
    inByte = float(inString);
    println(inByte);
    inByte = map(inByte, 0, 1023, 0, 100);
  }
}
  
  
void backGround() {              //Like Arduino Serial Plotter Background Setting
  stroke(0);
  line(100, 10, 100, 800);      //y-axis  line(x1,y1,x2,y2) 
  line(100, 800, 1400, 800);    //x-axis
  
  
  stroke(204);                  //stroke(204,204,204) -> grey
  line(100, 603, 1400, 603);    //0.0
  line(100, 400, 1400, 400);    //10.0
  line(100, 200, 1400, 200);    //20.0
  line(100, 10, 1400, 10);      //30.0
  
  
  fill(0);
  textSize(15);
  text("0.0", 70, 600);
  text("200.0", 55, 400);
  text("400.0", 55, 200);
  text("600.0", 55, 15);
  
}
