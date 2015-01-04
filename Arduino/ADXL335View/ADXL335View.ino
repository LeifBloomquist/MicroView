// Microview Arduino Code for the ADXL335

#include <MicroView.h>

#define SCALING 20

int center_x = uView.getLCDWidth()/2;
int center_y = uView.getLCDHeight()/2;

void setup() 
{
  uView.begin();		// begin of MicroView  
  uView.setFontType(0);
  uView.clear(ALL);	// erase hardware memory inside the OLED controller
  ClearScreen();
}


void loop()
{   
  int x = analogRead(0);        // read analog input pin 0
  int y = analogRead(1);        // read analog input pin 1
  int z = analogRead(2);        // read analog input pin 2

  float x_scaled = Scale(x, 410, 620);
  float y_scaled = Scale(y, 395, 610);
  float z_scaled = Scale(z, 395, 595);
  
  ClearScreen();
  uView.println("ADXL335\n");
  uView.print("X: ");     uView.println(x_scaled);
  uView.print("Y: ");     uView.println(y_scaled);
  uView.print("Z: ");     uView.println(z_scaled);
  
  uView.circleFill(
               center_x + (x_scaled*SCALING),
               center_y - (z_scaled*SCALING),    // ADXL335 is mounted sideways!
               5, //+        (y_scaled*SCALING)
               WHITE, XOR);
                 
  uView.display();
  delay(50);
}


// Scale one of the inputs to between -1.0 and 1.0
float Scale(long in, long smin, long smax)
{
  // Bound
  if (in > smax) in=smax;
  if (in < smin) in=smin;
  
  // Change zero-offset
  in = in-smin;
  
  // Scale between 0.0 and 1.0    (0.5 would be halfway)
  float temp = (float)in/((float)smax-(float)smin);
  
  float temp2 = (0.5-temp)*2.0;  // Rescale to -1.0 to 1.0
  
  return temp2;   
}

void ClearScreen()
{
  uView.clear(PAGE);	// erase the memory buffer, when next uView.display() is called, the OLED will be cleared.
  uView.setCursor(0,0);
}
