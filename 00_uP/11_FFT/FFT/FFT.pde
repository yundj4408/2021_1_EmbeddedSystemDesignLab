import processing.serial.*;

Serial myPort;        // The serial port

float val;

float xPos = 1;         // horizontal position of the graph

float inByte = 0;
float pre_data = 0;

void setup () {
  // set the window size:
  size(1400, 800) ;
  background(255);
  backGround();
  // List all the available serial ports
  printArray(Serial.list());

  // I know that the second port in the serial list on my PC
  // is always my  Arduino, so I open Serial.list()[1].
  myPort = new Serial(this, Serial.list()[33], 115200);

  // don't generate a serialEvent() unless you get a newline character:
  myPort.bufferUntil('\n');

  // set inital background:
  //background(0);
}
void draw () {
  // draw the line:
  stroke(255,0,0);    //red
  
  line(xPos-100, height-pre_data-100, xPos-100, height - inByte-100);
  // at the edge of the screen, go back to the beginning:
  if (xPos >= width) {
    xPos = 0;
    rect_set();
  } else {
    // increment the horizontal position:
    xPos++;
  }
  pre_data = inByte;
}


void serialEvent (Serial myPort) {
  // get the ASCII string:
  String inString = myPort.readStringUntil('\n');

  if (inString != null) {
    // trim off any whitespace:
    inString = trim(inString);
    // convert to an int and map to the screen height:
    inByte = float(inString);
    println(inByte);
    inByte = map(inByte, 0, 1023, 0, 100);
  }
}

void rect_set(){
  background(255);
  stroke(0);
  for (int i = 1; i <= 31; i++) {
    line((width - 100) / 32 * i, 0, 10 + (width - 100) / 32 * i, height) ; //column line
  }
  for (int i = 1; i <= 7; i++) {
    line(width - (32 * 45), height / 8 * i, width, height / 8 * i) ; //row line
  }
}

void backGround() {
  stroke(0);
  line(100, 10, 100, 800);      //y-axis  line(x1,y1,x2,y2) 
  line(100, 800, 1400, 800);    //x-axis
  
  
  stroke(204);                  //stroke(204,204,204) -> grey
  line(100, 600, 1400, 600);    //0.0
  line(100, 400, 1400, 400);    //10.0
  line(100, 200, 1400, 200);    //20.0
  line(100, 10, 1400, 10);      //30.0
  
  
  fill(0);
  textSize(15);
  text("0.0", 70, 600);
  text("10.0", 60, 400);
  text("20.0", 60, 200);
  text("30.0", 60, 15);
  
}
