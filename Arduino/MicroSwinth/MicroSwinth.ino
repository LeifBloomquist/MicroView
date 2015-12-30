/*
     A Swinthy style demo.      
     Leif Bloomquist
*/
#include <MicroView.h>
#include <ByteBuffer.h>

;  // Keep this here to pacify the Arduino pre-processor

#define TAIL_MULT 5

#define C64

#ifdef C64
  #include <SoftwareSerial.h>
  #define BAUD 2400
  SoftwareSerial mySerial(5, 6); // RX, TX
#else
  #define BAUD 38400
  HardwareSerial& mySerial = Serial;
#endif

// Global variables
boolean horizontal_mirror=true;
boolean vertical_mirror=true;
int max_x = uView.getLCDWidth();
int max_y = uView.getLCDHeight();

int max_inc=4;
int min_inc=1;

int tail_count=0;
int tail_length=4;
ByteBuffer buffer;
float x0,x1,y0,y1,dx0,dy0,dx1,dy1;

void setup() 
{
  uView.begin();	// begin of MicroView
  ClearScreen();

  randomSeed(analogRead(0));
  randomizeAll();
  
  uView.setFontType(0);
  uView.setCursor(0,0);
  
  mySerial.begin(BAUD);
  ShowCommands();
  
  // Buffer for the tail
  buffer.init(TAIL_MULT*10*4*sizeof(float));
}


void loop() 
{ 
  // Plot the first line
  PlotLine(x0,y0,x1,y1);
  delay(20);
  
  // Save coords in buffer
  buffer.putFloat(x0);
  buffer.putFloat(y0);
  buffer.putFloat(x1);
  buffer.putFloat(y1);
  
  // Erase "tail"  
  if (tail_count >= (tail_length*TAIL_MULT))
  {
     float temp_x0 = buffer.getFloat();
     float temp_y0 = buffer.getFloat();
     float temp_x1 = buffer.getFloat();
     float temp_y1 = buffer.getFloat();
     
     PlotLine(temp_x0,temp_y0,temp_x1,temp_y1);
  }
  else
  {
    tail_count++;
  }
  
  // Move
  x0 += dx0;
  y0 += dy0;
  x1 += dx1;
  y1 += dy1;
  
  // "Bounce" and then change+negate delta randomly
  if ((x0 >= max_x) || (x0 < 1)) { x0 -= dx0; dx0=-sgn(dx0)*randomize(); }
  if ((y0 >= max_y) || (y0 < 1)) { y0 -= dy0; dy0=-sgn(dy0)*randomize(); }
  if ((x1 >= max_x) || (x1 < 1)) { x1 -= dx1; dx1=-sgn(dx1)*randomize(); }   
  if ((y1 >= max_y) || (y1 < 1)) { y1 -= dy1; dy1=-sgn(dy1)*randomize(); }   

  // Check serial port
  CheckCommands();
}


void PlotLine(float _x0,float _y0,float _x1,float _y1)
{
  uView.line(_x0,_y0,_x1,_y1, WHITE, XOR);		// draw line from x0,y0 to x1,y1 using WHITE color and XOR draw mode
    
  if (horizontal_mirror)
  {
    uView.line(max_x-_x0,_y0,max_x-_x1,_y1, WHITE, XOR);   // Mirror
  }
  
  if (vertical_mirror)
  {
     uView.line(_x0,max_y-_y0,_x1,max_y-_y1, WHITE, XOR);   // Mirror
  }
  
  if (horizontal_mirror && vertical_mirror)
  {
     uView.line(max_x-_x0,max_y-_y0,max_x-_x1,max_y-_y1, WHITE, XOR);   // Mirror
  }
  
  uView.display(); 
}

// Random value between 0.01 and 1.00  (0 would cause point to freeze)
// Multiplied by random increment factor
float randomize()
{
   return (0.01+random(99)/100.0)*random(min_inc,max_inc);
}

void randomizeAll()
{
  x0=random(max_x);
  x1=random(max_x);
  y0=random(max_y);
  y1=random(max_y);
  
  dx0=randomize();
  dy0=randomize();
  dx1=randomize();
  dy1=randomize();
}

void CheckCommands()
{
  if (mySerial.available() > 0)
  {
     char c=mySerial.read();
     
     switch (c)
     {
       case ' ': ShowCommands();
                 ClearScreen();
                 randomizeAll();
                 ClearBuffer();                 
                 break;
                
       case 'h': 
       case 'H': ClearScreen();
                 ClearBuffer();
                 horizontal_mirror = !horizontal_mirror;       
                 break;
                 
       case 'v': 
       case 'V': ClearScreen();
                 ClearBuffer();
                 vertical_mirror = !vertical_mirror;
                 break;  

       case 'i': 
       case 'I': switch (max_inc)
                 {
                    case 4:  max_inc = 8;  break;
                    case 8:  max_inc = 16; break;
                    case 16: max_inc = 32; break;
                    default: max_inc = 4;  break;
                 }
                 break;

       case 'e': 
       case 'E': if (min_inc == 1)
                 {
                   min_inc = 2;
                 }
                 else
                 {
                   min_inc = 1;
                 }                 
                 break;
       
       default: if ((c >= '0') && (c <= '9'))
                {
                  ClearScreen();
                  ClearBuffer();
                  tail_length = (int)c - (int)'0';
                }
                break;
     }
  }
}

void ClearBuffer()
{
  buffer.clear();
  tail_count=0;
}

void ClearScreen()
{
  uView.clear(ALL);	// erase hardware memory inside the OLED controller
  uView.clear(PAGE);	// erase the memory buffer, when next uView.display() is called, the OLED will be cleared.
  uView.display();	// display the content in the buffer memory
}

void ShowCommands()
{
  mySerial.print(
             "MicroSwinth Commands\n\n\r\r"  
             "i     changes max increment 32>16>8>4\n\r" 
             "e     changes min increment 1<->2\n\r" 
             "h     toggles horizonal symmetry\n\r" 
             "v     toggles vertical symmetry\n\r" 
             "0-9   changes length of tail\n\r" 
             "space resets display\n\n\r\r"
          );
  
  mySerial.flush();
}

int sgn(float val) 
{
 if (val < 0) return -1;
 if (val == 0) return 0;
 return 1;
}
