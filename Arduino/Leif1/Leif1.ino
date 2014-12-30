/*
     A swinthy style demo.
*/
#include <MicroView.h>

void setup() {
	uView.begin();		// begin of MicroView
	uView.clear(ALL);	// erase hardware memory inside the OLED controller
	uView.display();	// display the content in the buffer memory, by default it is the MicroView logo
	delay(700);
	uView.clear(PAGE);	// erase the memory buffer, when next uView.display() is called, the OLED will be cleared.
        randomSeed(analogRead(0));
}


void loop() 
{
	int onDelay=20;
	uView.setFontType(0);
	uView.setCursor(0,0);
	//uView.print("Hello everyone this is Leif's first program!");    
	uView.display();
	delay(500);

        int max_x = 10;
        int max_y = 40;
        
        int x0=random(max_x);
    	int x1=random(max_x);
    	int y0=random(max_y);
    	int y1=random(max_y);
    
        int dx0=1;
        int dy0=1;
        int dx1=1;
        int dy1=1;
        
        while (true)
        {
     //      uView.line(x0,y0,x1,y1, WHITE, XOR);		// draw line from x0,y0 to x1,y1 using WHITE color and XOR draw mode
        //  uView.line(max_x-x0,y0,max_x-x1,y1, WHITE, XOR);   // Mirror

          uView.clear(PAGE);	// erase the memory buffer, when next uView.display() is called, the OLED will be cleared.
      	  uView.setCursor(x0,y0);
          char c = 3;      
          uView.print("Ella ");
          uView.print(c);
          uView.display();
          delay(onDelay);   
       
          //uView.line(x0,y0,x1,y1, WHITE,XOR);
          //uView.line(max_x-x0,y0,max_x-x1,y1, WHITE, XOR);		// Mirror
          //uView.display();
          
          x0 += dx0;
          y0 += dy0;
          x1 += dx1;
          y1 += dy1;

          if ((x0 > max_x) || (x0 < 1)) dx0=-dx0;        
          if ((y0 > max_y) || (y0 < 1)) dy0=-dy0;        
          if ((x1 > max_x) || (x1 < 1)) dx1=-dx1;        
          if ((y1 > max_y) || (y1 < 1)) dy1=-dy1;        
          
	}
}


