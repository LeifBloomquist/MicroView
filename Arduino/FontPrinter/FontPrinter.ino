/*
     Microview Font Printer
*/
#include <MicroView.h>

void setup()
{
  uView.begin();	// begin of MicroView  
  Serial.begin(2400);
  clearscreen(); 
  uView.print("READY.");
  uView.display();
}

void clearscreen()
{
  uView.clear(ALL);	// erase hardware memory inside the OLED controller
  uView.clear(PAGE);	// erase the memory buffer, when next uView.display() is called, the OLED will be cleared.
  uView.setFontType(1);
  uView.setCursor(0,0);
  uView.display();
}
    
  
char c=0;

void loop() 
{    
    if (Serial.available() > 0)
    {
       char in = Serial.read();       
       if (in == ' ') c++;
       if (in == 'b') c--;
       
       clearscreen();
      
       uView.print((byte)c);
       uView.print(" : ");
       uView.print(c);
       uView.println();
       uView.display();     
    } 
}
