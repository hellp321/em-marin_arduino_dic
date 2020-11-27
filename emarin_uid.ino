#include "U8glib.h"
#include <SoftwareSerial.h>
U8GLIB_SSD1306_128X32 u8g(U8G_I2C_OPT_NONE);  // I2C / TWI 

SoftwareSerial rdm6300(7, 8);
String s = "";
int x=1;
String uid="";
void draw(void) {
  // graphic commands to redraw the complete screen should be placed here  
  u8g.setFont(u8g_font_unifont);
  //u8g.setFont(u8g_font_osb21);
}


void setup() {
  rdm6300.begin(9600);
  Serial.begin(9600);
  // put your setup code here, to run once:
  // assign default color value
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }
  pinMode(8, OUTPUT);
  
}

void loop() {
if (rdm6300.available() > 0) {
   while (rdm6300.available() > 0) {
     char c = rdm6300.read();
     s += c;
     delay(3);
    }

//вывод ключа
if(s.length()==14){
s=s.substring(3, s.length()-3);
//String xxx="";
//xxx=s.substring(3, s.length()-3);

String stringVar = s;
String uid="";
char charBufVar[50];
stringVar.toCharArray(charBufVar, 50);


  uint64_t result = 0;
  for (int i = 0; charBufVar[i]; ++i)
    result = (result<<4) + (charBufVar[i] <= '9' ? charBufVar[i] - '0' : toupper(charBufVar[i]) - 'A' + 10);
   uid=(uint32_t)(result % 10000000), DEC;
   
u8g.firstPage();
do {
      u8g.setFont(u8g_font_unifont);  
      u8g.setPrintPos(0, 20); 
      Serial.print("");
      Serial.print(uid);
      u8g.print(uid);
  } while( u8g.nextPage() );  
  
}
//s=s.substring(3, s.length()-3);

//конец вывода
s = "";     
}
 


 
x=x+1;
}
