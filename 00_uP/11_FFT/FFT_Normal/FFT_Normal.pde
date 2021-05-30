import processing.serial.*;

Serial myPort;        // The serial port

float xPos = 1;         // horizontal position of the graph

float inByte = 0;
float pre_data = 0;

void setup () {
  // set the window size:
  //size(800, 300);  
  size(1600, 600) ;
  //rect_set();
  // List all the available serial ports
  // if using Processing 2.1 or later, use Serial.printArray()
  printArray(Serial.list());

  // I know that the second port in the serial list on my PC
  // is always my  Arduino, so I open Serial.list()[1].
  // (if first, type Serial.list()[0]).
  // Open whatever port is the one you're using.
  myPort = new Serial(this, Serial.list()[33], 115200);

  // don't generate a serialEvent() unless you get a newline character:
  //myPort.bufferUntil('\n');

  // set inital background:
  background(0);
}
void draw () {
  // draw the line:
  stroke(255,0,0);    //red
  strokeWeight(2);
  line(xPos+100, height-pre_data, xPos+100, height - inByte);
  // at the edge of the screen, go back to the beginning:
  if (xPos >= width) {
    xPos = 0;
    //rect_set();
    background(0);
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
    println(inByte/100);
    inByte = map(inByte, 0, 1023, 0, 100);
  }
}

void rect_set(){
  background(255);
  stroke(0);
  for (int i = 1; i <= 40; i++) {
    line((width - 100) / 32 * i, 0, 10 + (width - 100) / 32 * i, height) ; //column line
  }
  for (int i = 1; i <= 7; i++) {
    line(width - (32 * 45), height / 8 * i, width, height / 8 * i) ; //row line
  }
}

/*
  for (int i = 1; i <= 31; i++) {
    line((width - 100) / 32 * i, 0,(width - 100) / 32 * i, height) ; //column line
  }
  for (int i = 1; i <= 7; i++) {
    line(- 32 * 45, height / 8 * i, width, height / 8 * i) ; //row line
  }  //this one is for all 
  */
