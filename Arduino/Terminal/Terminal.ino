/*
     Teminal Demo
*/


#include <MicroView.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX

void setup()
{
  uView.begin();	// begin of MicroView  
  mySerial.begin(2400);
  clearscreen(); 
}

void clearscreen()
{
  uView.clear(ALL);	// erase hardware memory inside the OLED controller
  uView.clear(PAGE);	// erase the memory buffer, when next uView.display() is called, the OLED will be cleared.
  uView.setFontType(0);
  uView.setCursor(0,0);  
  uView.println("READY."); 
  mySerial.println("READY.");  
  uView.display();
}
  

void loop() 
{    
    if (mySerial.available() > 0)
    {
       char c=mySerial.read();
       
       if (c == 1)  // CTRL-A, clear
       {
         clearscreen();
         return;
       }
       
       if (c == 13)  // Return
       {
          c = 10;
       }
 
       uView.print(c);
       uView.display();
       mySerial.print(c);  // Echo
    }      
}
