/*
    Sound Detector with the Sparkfun SEN-12642 Sound Detector
*/
#include <MicroView.h>
#include <SoftwareSerial.h>

#define BAUD 2400
#define PIN_ENVELOPE_IN A1

SoftwareSerial mySerial(5, 6);   // RX, TX

MicroViewWidget *widget1 = new MicroViewGauge(25, 24, 0, 600, WIDGETSTYLE1);

void setup() 
{
  uView.begin();	// begin of MicroView
  uView.clear(ALL);	// erase hardware memory inside the OLED controller
  uView.clear(PAGE);	// erase the memory buffer, when next uView.display() is called, the OLED will be cleared.
  uView.setFontType(0);
  uView.setCursor(0,0);	

  widget1->drawFace();
  widget1->draw();

  uView.display();	// display the content in the buffer memory, by default it is the MicroView logo 
  
  mySerial.begin(BAUD);
}

void loop()
{
   int value = analogRead(PIN_ENVELOPE_IN);
   
   uView.clear(PAGE);
   widget1->setValue(value);
   widget1->reDraw();
  
  mySerial.print("Level: ");
  mySerial.println(value);

  uView.display(); 
  delay(50);
}

