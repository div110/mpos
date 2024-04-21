//DISPLAY
  //D7 - Orange - CLK
  //D6 - Green - DIN
  //D5 - Blue - DC
  //D4 - Brown - RST
  //D3 - Yellow - CS
  //GND - White
  //VCC - Purple
//ENCODER
  //CLK - D9
  //DT - D8
  //SW - D2


#include <SPI.h>
#include "Ucglib.h"

int pos = 0;
const byte clk = 9;
const byte dt = 8;
const byte sw = 2;
Ucglib_ILI9341_18x240x320_SWSPI ucg(/*sclk=*/ 7, /*data=*/ 6, /*cd=*/ 5 , /*cs=*/ 3, /*reset=*/ 4);


//mp3 module
#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"
#include <SoftwareSerial.h>
SoftwareSerial softSerial(/*rx =*/12, /*tx =*/11); //fckin bullshit aka i messed up order
#define FPSerial softSerial

DFRobotDFPlayerMini myDFPlayer;
//---------------------------------------



//void printDetail(uint8_t type, int value);
void setup() {
  FPSerial.begin(9600);
  Serial.println("XXXXXXXXXXXXXXXXXXXXXXXXXxxxx");
  Serial.begin(115200);

  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));


  //TROUBLESHOOT
  if (!myDFPlayer.begin(FPSerial, /*isACK = */true, /*doReset = */true)) {  //Use serial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true){
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }

  
  Serial.println(F("DFPlayer Mini online."));
  
  myDFPlayer.volume(10);  //Set volume value. From 0 to 30
  myDFPlayer.play(1);  //Play the first mp3
  ucg.begin(UCG_FONT_MODE_TRANSPARENT);
  ucg.setFont(ucg_font_helvB08_tr);
  pinMode(clk, INPUT);
  pinMode(dt, INPUT);
  pinMode(sw, INPUT_PULLUP);
  //Serial.begin(9600);
  logo();
  menu();
  topbar_playlists();
  botbar();
  boticons();
  //about();


  
}

void loop() {
  while(digitalRead(clk)==true&&digitalRead(dt)==true&&digitalRead(sw)==true){
  
  delay(2); //netusim proc, ale funguje to s nim liip :///
  if(digitalRead(clk)==true&&digitalRead(dt)==false){

    Serial.println("proti smeru");
    pos = pos-1;
    Serial.println(pos);

    if(pos == 14 || pos == 13){
      //VRACENI FRAMU
      ucg.setColor(100,100,100);
      ucg.drawFrame(1, 202, 239, 12);

      //SMAZA FRAMU IKON
      //SMAZANI FRAMU IKON:
      ucg.setColor(0,0,0);
      ucg.drawFrame(87, 252, 47, 47);
      ucg.drawFrame(177, 252, 47, 47);
      ucg.drawFrame(142, 252, 27, 47);
      ucg.drawFrame(14, 260, 55, 30);
    }
    if(pos >=0 && pos <=14 && pos +1 <=14){
    ucg.setColor(0,0,0);
    ucg.drawFrame(1,(pos+1)*13+20, 239,12);
    
    ucg.setColor(100,100,100);
    ucg.drawFrame(1,pos*13+20, 239,12);
    }
    else{
      ucg.setColor(0,0,0);
      ucg.drawFrame(1, 20, 239, 12);

      Serial.println("mimo");
      if(pos==-1){
        //SMAZANI STARE IKONY
        ucg.setColor(0,0,0);
        ucg.drawFrame(14, 260, 55, 30);
        ucg.setColor(0,0,0);
        ucg.drawFrame(142, 252, 27, 47);




        //NOVA IKONA
        ucg.setColor(100,100,100);
        ucg.drawFrame(177, 252, 47, 47);
        
      }
      else if(pos==-2){
        //SMAZANI STARE IKONY
        ucg.setColor(0,0,0);
        ucg.drawFrame(177, 252, 47, 47);
        ucg.setColor(0,0,0);
        ucg.drawFrame(87, 252, 47, 47);
        //DALSI IKONA
        ucg.setColor(100,100,100);
        ucg.drawFrame(142, 252, 27, 47);
      }
      else if(pos==-3){
        //SMAZANI STARE IKONY
        ucg.setColor(0,0,0);
        ucg.drawFrame(142, 252, 27, 47);
        ucg.setColor(0,0,0);
        ucg.drawFrame(14, 260, 55, 30);



        //DALSI IKONA
        ucg.setColor(100,100,100);
        ucg.drawFrame(87, 252, 47, 47);


      }
      else{
        //SMAZANI STARE IKONY
        ucg.setColor(0,0,0);
        ucg.drawFrame(87, 252, 47, 47);
        ucg.setColor(0,0,0);
        ucg.drawFrame(177, 252, 47, 47);
        //NOVA IKONA
        ucg.setColor(100,100,100);
        ucg.drawFrame(14, 260, 55, 30);
        pos = 14;
      }
    }
    }
  else if(digitalRead(clk)==false&&digitalRead(dt)==true){
    
    Serial.println("po smeru");
    pos = pos+1;
    Serial.println(pos);


    if(pos == 0||pos ==1){
      //VRACENI FRAMU
      ucg.setColor(100,100,100);
      ucg.drawFrame(1, 20, 239, 12);

      //SMAZANI FRAMU IKON:
      ucg.setColor(0,0,0);
      ucg.drawFrame(87, 252, 47, 47);
      ucg.drawFrame(177, 252, 47, 47);
      ucg.drawFrame(142, 252, 27, 47);
      ucg.drawFrame(14, 260, 55, 30);
    }


    if(pos >=0 && pos <=14 && pos -1 >=0){
    
    ucg.setColor(0,0,0);
    ucg.drawFrame(1,(pos-1)*13+20, 239,12);
    ucg.setColor(100,100,100);
    ucg.drawFrame(1,pos*13+20, 239,12);
    }
    else{
      ucg.setColor(0,0,0);
      ucg.drawFrame(1, 202, 239, 12);

      Serial.println("mimo");
      if(pos ==15){
        //SMAZANI STARE IKONY
        ucg.setColor(0,0,0);
        ucg.drawFrame(14, 260, 55, 30);
        ucg.setColor(0,0,0);
        ucg.drawFrame(142, 252, 27, 47);




        //NOVA IKONA
        ucg.setColor(100,100,100);
        ucg.drawFrame(177, 252, 47, 47);
        
      }
      else if(pos == 16){
        //SMAZANI STARE IKONY
        ucg.setColor(0,0,0);
        ucg.drawFrame(177, 252, 47, 47);
        ucg.setColor(0,0,0);
        ucg.drawFrame(87, 252, 47, 47);
        //DALSI IKONA
        ucg.setColor(100,100,100);
        ucg.drawFrame(142, 252, 27, 47);
      }
      else if(pos == 17){
        //SMAZANI STARE IKONY
        ucg.setColor(0,0,0);
        ucg.drawFrame(142, 252, 27, 47);
        ucg.setColor(0,0,0);
        ucg.drawFrame(14, 260, 55, 30);



        //DALSI IKONA
        ucg.setColor(100,100,100);
        ucg.drawFrame(87, 252, 47, 47);


      }
      else{
        //SMAZANI STARE IKONY (VSECH)
        ucg.setColor(0,0,0);
        ucg.drawFrame(87, 252, 47, 47);
        ucg.setColor(0,0,0);
        ucg.drawFrame(177, 252, 47, 47);
        
        //NOVA IKONA
        ucg.setColor(100,100,100);
        ucg.drawFrame(14, 260, 55, 30);
        pos = 0;
      }
    }
    }
  //delay(30);
  if(digitalRead(sw)==LOW){
    Serial.println("tlacitkoo");
    myDFPlayer.next();
    //myDFPlayer.randomAll();
  }
  
  }
}
void menu(){
  ucg.setColor(200, 200, 200);
  ucg.setPrintPos(5,30);
  ucg.print("TWENTY ONE PILOTS");
  ucg.setPrintPos(5,43);
  ucg.print("BOB DYLAN");
  ucg.setPrintPos(5,56);
  ucg.print("KANYE WEST");
  ucg.setPrintPos(5, 69);
  ucg.print("JACK STAUBER");
  ucg.setPrintPos(5, 82);
  ucg.print("AUTOHEART");
  ucg.setPrintPos(5, 95);
  ucg.print("HOLLYWOOD UNDEAD");
  ucg.setPrintPos(5, 108);
  ucg.print("Classical Music");
  ucg.setPrintPos(5, 121);
  ucg.print("LO-FI");
  ucg.setPrintPos(5, 134);
  ucg.print("1######");
  ucg.setPrintPos(5, 147);
  ucg.print("2######");
  ucg.setPrintPos(5, 160);
  ucg.print("3######");
  ucg.setPrintPos(5, 173);
  ucg.print("4######");
  ucg.setPrintPos(5, 186);
  ucg.print("5######");
  ucg.setPrintPos(5, 199);
  ucg.print("VOLUME");
  ucg.setPrintPos(5, 212);
  ucg.print("ABOUT");


}
void topbar_playlists(){
  ucg.setColor(200,200,200);
  ucg.drawBox(0, 0, 320, 20);
  ucg.setColor(0,0,0);
  ucg.setPrintPos(90, 14);
  ucg.print("PLAYLISTS");
}
void botbar(){
  ucg.setColor(200,200,200);
  ucg.drawBox(0, 220, 240, 10);
}
void boticons(){
  ucg.setColor(200,200,200);

  //NEXT
  ucg.drawLine(220, 255, 220, 295);
  ucg.drawLine(180, 255, 220, 275);
  ucg.drawLine(180, 255, 180, 295);
  ucg.drawLine(180, 295, 220, 275);

  //PAUSE
  ucg.drawLine(165, 255, 165, 295);
  ucg.drawLine(160, 255, 160, 295);
  ucg.drawLine(160, 255, 165, 255);
  ucg.drawLine(160, 295, 165, 295);

  ucg.drawLine(145, 255, 145, 295);
  ucg.drawLine(150, 255, 150, 295);
  ucg.drawLine(145, 255, 150, 255);
  ucg.drawLine(145, 295, 150, 295);

  //PREVIOUS
  ucg.drawLine(90, 255, 90, 295);
  ucg.drawLine(90, 275, 130, 295);
  ucg.drawLine(130, 255, 130, 295);
  ucg.drawLine(90, 275, 130, 255);

  //RANDOM
  ucg.setPrintPos(18, 272);
  ucg.print("RANDOM");
  ucg.setPrintPos(23, 285);
  ucg.print("ORDER");
}
void volume(){//int i){
  
}
void logo(){
  ucg.clearScreen();
  ucg.setColor(255,0,0);
  ucg.drawBox(105, 0, 30, 50);
  ucg.setColor(0,0,0);
  ucg.drawBox(105, 0, 30, 50);

  ucg.setColor(0,255,0);
  ucg.drawBox(105, 50, 30, 50);
  ucg.setColor(0,0,0);
  ucg.drawBox(105, 50, 30, 50);

  ucg.setColor(0,0,255);
  ucg.drawBox(105, 100, 30, 50);
  ucg.setColor(0,0,0);
  ucg.drawBox(105, 100, 30, 50);

  ucg.setColor(255,0,0);
  ucg.drawBox(105, 150, 30, 50);
  ucg.setColor(0,0,0);
  ucg.drawBox(105, 150, 30, 50);

  ucg.setColor(0,255,0);
  ucg.drawBox(105, 200, 30, 50);
  ucg.setColor(0,0,0);
  ucg.drawBox(105, 200, 30, 50);

  ucg.setColor(0,0,255);
  ucg.drawBox(105, 250, 30, 50);
  ucg.setColor(0,0,0);
  ucg.drawBox(105, 250, 30, 50);

  ucg.setColor(255,0,0);
  ucg.drawBox(105, 300, 30, 50);
  ucg.setColor(0,0,0);
  ucg.drawBox(105, 300, 30, 50);
}
void about(){
  ucg.clearScreen();

  //HUSTARNA
  ucg.setColor(0,255,255);
  ucg.drawTriangle(105, 134, 135, 134, 120, 160);
  delay(100);
  ucg.setColor(0,0,0);
  ucg.drawTriangle(105, 134, 135, 134, 120, 160);
  ucg.setColor(255,255,0);
  ucg.drawTriangle(100, 160, 140, 160, 120, 125);
  delay(100);
  ucg.setColor(0,0,0);
  ucg.drawTriangle(100, 160, 140, 160, 120, 125);
  ucg.setColor(255,0,255);
  ucg.drawTriangle(95, 160, 145, 160, 120, 117);
  delay(100);
  ucg.setColor(0,0,0);
  ucg.drawTriangle(95, 160, 145, 160, 120, 117);

  //INFO
  ucg.setColor(200,100,100);
  ucg.setPrintPos(50, 50);
  ucg.print("netusim");
}
  

