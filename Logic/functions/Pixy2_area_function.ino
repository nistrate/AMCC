//
// begin license header
//
// This file is part of Pixy CMUcam5 or "Pixy" for short
//
// All Pixy source code is provided under the terms of the
// GNU General Public License v2 (http://www.gnu.org/licenses/gpl-2.0.html).
// Those wishing to use Pixy source code, software and/or
// technologies under different licensing terms should contact us at
// cmucam@cs.cmu.edu. Such licensing terms are available for
// all portions of the Pixy codebase presented here.
//
// end license header
//
// This sketch is a good place to start if you're just getting started with 
// Pixy and Arduino.  This program simply prints the detected object blocks 
// (including color codes) through the serial console.  It uses the Arduino's 
// ICSP SPI port.  For more information go here:
//
// https://docs.pixycam.com/wiki/doku.php?id=wiki:v2:hooking_up_pixy_to_a_microcontroller_-28like_an_arduino-29
//
  
#include <Pixy2.h>

// This is the main Pixy object 
Pixy2 pixy;

int avg_height = 0;
int avg_width = 0;
long area;

void setup()
{
  Serial.begin(115200);
  Serial.print("Starting...\n");
  
  pixy.init();
}

void loop()
{ 
  avg_height = 0;
  avg_width = 0;
  area = 1L;
  int i;

  for (int count = 0; count < 10; count ++)
  { 
    // grab blocks!
    pixy.ccc.getBlocks();
    
    // If there are detect blocks, print them!
    if (pixy.ccc.numBlocks)
    {
      Serial.print("Detected ");
      Serial.println(pixy.ccc.numBlocks);
      for (i=0; i<pixy.ccc.numBlocks; i++)
      {
        Serial.print("  block ");
        Serial.print(i);
        Serial.print(": ");
        pixy.ccc.blocks[i].print();
        Serial.print("height : ");
        Serial.println(pixy.ccc.blocks[0].m_height);
      }
      avg_height = avg_height + pixy.ccc.blocks[0].m_height;
      avg_width = avg_width + pixy.ccc.blocks[0].m_width;
  
      Serial.print("avg_width = ");
      Serial.print(avg_width);
      Serial.print("   avg_height = ");
      Serial.println(avg_height);
    } 
    
  }
  avg_height = avg_height / 10;
  avg_width = avg_width /10;
  area = area * avg_height * avg_width; //area = 1 initially
  Serial.println("#############################################");
  Serial.print("avg_width = ");
  Serial.print(avg_width);
  Serial.print("   avg_height = ");
  Serial.println(avg_height);
    Serial.print("area = ");
  Serial.println(avg_width*avg_height);
  Serial.println("#############################################");
  delay(10000);
} 

////////////////////////////////////////////////////////////////////////
//      int height = pixy.ccc.blocks[0].m_height;
//      int width = pixy.ccc.blocks[0].m_width;
