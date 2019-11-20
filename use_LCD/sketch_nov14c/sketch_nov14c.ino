#include <dht11.h>
#include <UTFT.h>




dht11 DHT11;
#define DHT11PIN A2

UTFT myGLCD(QD_TFT180A,7,8,5,4,6);
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];

int autof = 0;

void setup()
{
  Serial.begin(9600);
  myGLCD.InitLCD();

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  int chk = DHT11.read(DHT11PIN);
  
  float humf=(float)DHT11.humidity;
  float tempf=(float)DHT11.temperature;

  Serial.print("Temperature: ");
  Serial.println(tempf);
  Serial.print("Humidity: ");
  Serial.println(humf);
//  Serial.write("\n\n");

  if ((humf>80)&&(autof==1)){
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("WARNING!");
  }
  else if ((humf<=80)&&(autof==1)){
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("NORMAL!");
  }
  myGLCD.clrScr();//clear
  myGLCD.setFont(SmallFont);//参数可以是SmallFont/BigNumbers/SevenSegNumFont
  myGLCD.setColor(255, 255, 0);//字体颜色R,G,B
  myGLCD.setBackColor(0, 0, 255);//字体背景的颜色R,G,B
  myGLCD.print("TEMPERATURE:", LEFT, 1);//显示字符串，参数依次为字符串、RIGHT/CENTER/LEFT、行数
  myGLCD.setFont(BigFont);
  myGLCD.print((String)tempf, RIGHT, 20);
  myGLCD.setFont(SmallFont);
  myGLCD.print("HUMIDITY:", LEFT, 50);
  myGLCD.setFont(BigFont);
  myGLCD.print((String)humf, RIGHT, 60);
  myGLCD.setFont(SmallFont);
  if(autof==0)
    myGLCD.print("Manual", CENTER, 90);
  else if(autof==1)
    myGLCD.print("Auto", CENTER, 90);
//    delay(2000);
  if(Serial.available()){
    char a=Serial.read();
    if ((a=='0')&&(autof==0))
      digitalWrite(LED_BUILTIN, LOW);
    else if ((a=='1')&&(autof==0))
      digitalWrite(LED_BUILTIN, HIGH);
    else if (a=='2'){
      autof=1;
      Serial.println("Set to auto mode!");
    }
    else if (a=='3'){
      autof=0;
      Serial.println("Set to manual mode!");
    }
  }
//  delay(2000);
}

