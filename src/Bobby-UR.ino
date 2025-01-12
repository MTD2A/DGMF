// Arduino 7 segment display example software
// http://www.hacktronics.com/Tutorials/arduino-and-7-segment-led.html
// License: http://www.opensource.org/licenses/mit-license.php (Go crazy)
 
// Define the LED digit patters, from 0 - 9
// Note that these patterns are for common cathode displays
// For common anode displays, change the 1's to 0's and 0's to 1's
// 1 = LED on, 0 = LED off, in this order:
//                                    Arduino pin: 2,3,4,5,6,7,8
byte seven_seg_digits[20][7] = { { 0,0,0,0,0,0,1 },  // = 0
                                                           { 1,0,0,1,1,1,1 },  // = 1
                                                           { 0,0,1,0,0,1,0 },  // = 2
                                                           { 0,0,0,0,1,1,0 },  // = 3
                                                           { 1,0,0,1,1,0,0 },  // = 4
                                                           { 0,1,0,0,1,0,0 },  // = 5
                                                           { 0,1,0,0,0,0,0 },  // = 6
                                                           { 0,0,0,1,1,1,1 },  // = 7
                                                           { 0,0,0,0,0,0,0 },  // = 8
                                                           { 0,0,0,1,1,0,0 },  // = 9
                                                           { 1,1,1,1,1,1,1 },  // = BLANK
                                                           { 0,1,1,1,0,0,0 },  // = F
                                                           { 0,1,0,0,1,0,0 },  // = S
                                                           { 1,1,1,0,0,0,1 },  // = L
                                                           { 1,0,0,1,1,1,1 },  // = I
                                                           { 0,0,1,1,0,0,0 },  // = P
                                                           { 0,0,0,1,0,0,0 },  // = A
                                                           { 1,0,0,0,0,0,1 },  // = U
                                                           { 0,1,1,0,0,0,0 },  // = E
                                                           { 1,1,1,1,0,1,0 },  // = r
                                                           };
int seg = 0;
int buttonState0 = 0;
int buttonState1 = 0;
int oneadd = 0;
int zeroadd = 0;
int segtochange = 4;
int clockon = 0;
int timesat = 0;
int faksat = 0;
int faktor = 0;
int pause = 0;

#include <TimerOne.h>

void setup() {
  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);  
  pinMode(6, OUTPUT);   
  pinMode(7, OUTPUT);  
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  //writeDot(0);  // start with the "dot" off
  //digitalWrite(2, 1);
  //digitalWrite(3, 1);
  //digitalWrite(4, 1);
  //digitalWrite(5, 1);
  //digitalWrite(6, 0);

  //Timer1.initialize(130000); //350000 = 8 timer pr 24 ... 130000 = 3 timer pr 24
  //Timer1.attachInterrupt(addtotime);

}

int seg1 = 11;
int seg2 = 10;
int seg3 = 0;
int seg4 = 1;
int seg5 = 0;
int seg6 = 0;

void writeDot(byte dot) {
  digitalWrite(6, dot);
}

void selectsegon(byte seg) {
  digitalWrite(seg, 1);
}

void selectsegoff(byte seg) {
  digitalWrite(seg, 0);
}

void sevenSegWrite(byte digit, int seg) {
  selectsegon(seg);
  byte pin = 7;
  for (byte segCount = 0; segCount < 7; ++segCount) {
    digitalWrite(pin, seven_seg_digits[digit][segCount]);
    ++pin;
  }
  delay(2);
  selectsegoff(seg);
}

void writeforeseg(int seg1, int seg2, int seg3, int seg4) {
 sevenSegWrite(seg1, 2);
 sevenSegWrite(seg2, 3);
 sevenSegWrite(seg3, 4);
 sevenSegWrite(seg4, 5); 
}

void flashseg() {
      if (digitalRead(segtochange+1)== HIGH){
      digitalWrite(segtochange+1, 0);
      }
      else if (digitalRead(segtochange+1)== LOW){
      digitalWrite(segtochange+1, 1);
      }
}

void addtotime(){
  
 if (seg1 > 1 && seg2 > 3)
  {
  seg1=0;
  seg2=0;
  seg3=0;
  seg4=0;
  seg5=0;
  seg6=0;
  }  
  else{
   if (seg6 + 1 > 3)
   {
    writeDot(0);
   }
   else
   {
    writeDot(1);
   }
    if ((seg6 + 1) > 5)
        {
          seg6 = 0;
            if ((seg5 + 1) > 9)
              {
                seg5 = 0;
                 if ((seg4 + 1) > 9)
                  {
                    seg4 = 0;
                    if ((seg3 + 1) > 5)
                      {
                        seg3 = 0;
                          if ((seg2 + 1) > 9)
                            {
                              seg2 = 0;
                                if ((seg1 + 1) > 2)
                                  {
                                    seg1 = 0;
                                   }
                                else
                                  {
                                    seg1 = seg1 + 1;
                                  }
                            }
                          else
                            {
                              seg2 = seg2 + 1;
                            }
                        }
                    else
                      {
                        seg3 = seg3 + 1;
                      }
                    }
                  else
                  {
                    seg4 = seg4 + 1;
                  }
                }
              else
              {
                seg5 = seg5 + 1;
              }
            }
          else
           {
          seg6 = seg6 + 1;
           }
        }
}

void loop() {
  while(buttonState0 == LOW && clockon == 0 && faksat == 0 && timesat == 0){
      writeforeseg(18,19,19,10);
      buttonState0 = digitalRead(0);
      buttonState1 = digitalRead(1);
       }
  
  
 writeforeseg(seg1,seg2,seg3,seg4);
 buttonState0 = digitalRead(0);
 buttonState1 = digitalRead(1);
 
   while((buttonState0 == HIGH || buttonState1 == HIGH) && clockon == 0 && faksat == 0){
      writeforeseg(seg1,seg2,seg3,seg4);
      buttonState0 = digitalRead(0);
      buttonState1 = digitalRead(1);
       if(buttonState0 == LOW && zeroadd == 0 && clockon == 0){
         zeroadd = 1;  
       }
       
       if(buttonState0 == HIGH && zeroadd == 1 && clockon == 0){
         if (segtochange == 3){seg3 = seg3 +1;}
         if (segtochange == 4){seg4 = seg4 +1;}
         if (seg3 > 9){seg3 = 0;}
         if (seg4 > 9){seg4 = 0;}
         zeroadd = 0;
       }
         
       if(buttonState1 == LOW && oneadd == 0 && clockon == 0){
           oneadd = 1; 
       }
         
       if(buttonState1 == HIGH && oneadd == 1 && clockon == 0){
         segtochange = segtochange +1;
 
       if (segtochange > 4){segtochange = 3;}
       oneadd = 0;
       }
       faktor = (seg3 * 10) + seg4;
   }
   
   Timer1.initialize(1000000/faktor); //350000 = 8 timer pr 24 ... 130000 = 3 timer pr 24
   faksat = 1;
   
   while(buttonState0 == LOW && buttonState1 == LOW && clockon == 0){
      writeforeseg(12,13,14,15);
      buttonState0 = digitalRead(0);
      buttonState1 = digitalRead(1);
       seg1= 10; seg2 = 10; seg3 = 10; seg4 = 10;
   } 
   while((buttonState0 == HIGH || buttonState1 == HIGH) && clockon == 0 && timesat == 0){
      writeforeseg(seg1,seg2,seg3,seg4);
      buttonState0 = digitalRead(0);
      buttonState1 = digitalRead(1);
       
   
     if(buttonState0 == LOW && zeroadd == 0 && clockon == 0){
       zeroadd = 1;  
     }
     if(buttonState0 == HIGH && zeroadd == 1 && clockon == 0){
       if (segtochange == 1){seg1 = seg1 +1;}
       if (segtochange == 2){seg2 = seg2 +1;}
       if (segtochange == 3){seg3 = seg3 +1;}
       if (segtochange == 4){seg4 = seg4 +1;}
       if (seg1 > 2){seg1 = 0;}
       if (seg2 > 9 || (seg1 > 1 && seg2 > 3)){seg2 = 0;}
       if (seg3 > 5){seg3 = 0;}
       if (seg4 > 9){seg4 = 0;}
       zeroadd = 0;
     }
     
     if(buttonState1 == LOW && oneadd == 0 && clockon == 0){
       oneadd = 1;  
     }
     if(buttonState1 == HIGH && oneadd == 1 && clockon == 0){
       segtochange = segtochange +1;
       if (segtochange > 4){segtochange = 1;}
       oneadd = 0;
     }
   }
   timesat = 1;
 
 if(buttonState0 == LOW && buttonState1 == LOW && clockon == 0 && faksat == 1 && timesat == 1 ){
     while(buttonState0 == LOW && buttonState1 == LOW && clockon == 0){
      writeforeseg(12,13,14,15);
      buttonState0 = digitalRead(0);
      buttonState1 = digitalRead(1);
      } 
     Timer1.attachInterrupt(addtotime);
     clockon = 1;
   }
   
if(buttonState0 == HIGH  && clockon == 1 && pause == 0){
   pause = 1;
   Timer1.attachInterrupt(addtotime);
    while(buttonState0 == LOW ){
      writeforeseg(15,16,17,12);
      buttonState0 = digitalRead(0);
      buttonState1 = digitalRead(1);
     }
   }
//   
if(buttonState0 == LOW && clockon == 1 && pause == 1){
     Timer1.detachInterrupt();
     pause = 0;
     while(buttonState0 == LOW ){
      writeforeseg(15,16,17,12);
      buttonState0 = digitalRead(0);
      buttonState1 = digitalRead(1);
     }
   }
   //writeDot(0);
}
