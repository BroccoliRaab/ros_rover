//www.elegoo.com

//    The direction of the car's movement
//  ENR   ENL   R1   R2   L1   L2   Description  
//  HIGH  HIGH  HIGH  LOW   LOW   HIGH  Car is runing forward
//  HIGH  HIGH  LOW   HIGH  HIGH  LOW   Car is runing back
//  HIGH  HIGH  LOW   HIGH  LOW   HIGH  Car is turning left
//  HIGH  HIGH  HIGH  LOW   HIGH  LOW   Car is turning right
//  HIGH  HIGH  LOW   LOW   LOW   LOW   Car is stoped
//  HIGH  HIGH  HIGH  HIGH  HIGH  HIGH  Car is stoped
//  LOW   LOW   N/A   N/A   N/A   N/A   Car is stoped
#include <string.h>

//define L298n module IO Pin
#define ENR 5 //Right enable
#define ENL 6 //Left enable
#define R1 7
#define R2 8
#define L1 9
#define L2 11

void forward(int speed){ 
	analogWrite(ENR, speed);
	analogWrite(ENL, speed);
	digitalWrite(R1,LOW); //set R1 hight level
	digitalWrite(R2,HIGH);  //set R2 low level
	digitalWrite(L1,HIGH);  //set L1 low level
	digitalWrite(L2,LOW); //set L2 hight level
}

void back(int speed){
	analogWrite(ENR, speed);
	analogWrite(ENL, speed);
	digitalWrite(R1,HIGH);
	digitalWrite(R2,LOW);
	digitalWrite(L1,LOW);
	digitalWrite(L2,HIGH);
}

void right(int speed){
	analogWrite(ENR, speed);
	analogWrite(ENL, speed);
	digitalWrite(R1,HIGH);
	digitalWrite(R2,LOW);
	digitalWrite(L1,HIGH);
	digitalWrite(L2,LOW); 
}

void left(int speed){
	analogWrite(ENR, speed);
	analogWrite(ENL, speed);
	digitalWrite(R1,LOW);
	digitalWrite(R2,HIGH);
	digitalWrite(L1,LOW);
	digitalWrite(L2,HIGH);
}

void stop(){
	digitalWrite(ENR,LOW);
	digitalWrite(ENL,LOW);
	digitalWrite(R1,LOW);
	digitalWrite(R2,LOW);
	digitalWrite(L1,LOW);
	digitalWrite(L2,LOW);
}

void rightWheel(bool isForward, char speed){
	analogWrite(ENR, abs(speed));
	if (isForward){
		digitalWrite(R1,LOW); //set R1 hight level
		digitalWrite(R2,HIGH);  //set R2 low level
	}
	else {
		digitalWrite(R1,HIGH); //set R1 hight level
		digitalWrite(R2,LOW);  //set R2 low level
	}
}

void leftWheel(bool isForward, char speed){
	analogWrite(ENL, abs(speed));
	if (isForward){
		digitalWrite(L1,HIGH); //set R1 hight level
		digitalWrite(L2,LOW);  //set R2 low level
	}
	else {
		digitalWrite(L1,LOW); //set R1 hight level
		digitalWrite(L2,HIGH);  //set R2 low level
	}
}
//before execute loop() function, 
//setup() function will execute first and only execute once
void setup() {
  Serial.begin(9600);//open serial and set the baudrate
  pinMode(R1,OUTPUT);//before useing io pin, pin mode must be set first 
  pinMode(R2,OUTPUT);
  pinMode(L1,OUTPUT);
  pinMode(L2,OUTPUT);
  pinMode(ENR,OUTPUT);
  pinMode(ENL,OUTPUT);
}

enum direction {Forward, Backward, Left, Right, Stop};
direction dir = Stop;

void loop() {
    bool leftWheel = true;
    bool beginningOfPacket= true;
    bool leftForward;
    bool rightForward;
    char leftWheelSpeed;
    char rightWheelSpeed;
	if (Serial.available() > 0){
		static String controlInput = "";
		int c = Serial.read();
        char data = (char) c;
		if (c != -1){
            if (beginningOfPacket){
                if (data & 0b00000001 == 1){
                    leftForward = true;
                }else{
                    leftForward = false
                }
                if (data & 0b00000010 == 2){
                    rightForward = true;
                } else {
                    rightForward = false;
                }
                beginningOfPacket = false;
            } else{
                if (leftWheel){
                    leftWheelSpeed=data;
                    
                    
                }else {
                    rightWheelSpeed=data;

                    leftWheel(leftForward,leftWheelSpeed);
                    rightWheel(rightForward,rightWheelSpeed);
                    
                    beginningOfPacket=true;
                }
                leftWheel = !leftWheel;

                    
            }
        }
    }
}
