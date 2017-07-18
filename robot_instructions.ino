#include <NewPing.h>
#include <Servo.h>
#define trigPin 13
#define echoPin 12

int motor_pin1 = 4;
int motor_pin2 = 5;
int motor_pin3 = 6;
int motor_pin4 = 7;
int servopin = 9;
int dist = 0;
int leftdist = 0;
int rightdist = 0;
int object = 35;            //distance at which the robot should look for another route
int pos;
long duration;

Servo myservo;
NewPing sonar(trigPin, echoPin);

void setup()
{
	Serial.begin (9600);
	pinMode(motor_pin1,OUTPUT);
	pinMode(motor_pin2,OUTPUT);
	pinMode(motor_pin3,OUTPUT);
	pinMode(motor_pin4,OUTPUT);
	pinMode(trigPin, OUTPUT);
	pinMode(echoPin, INPUT);
	myservo.attach(servopin);
	myservo.write(90);
	delay(700);
}

void loop()
{
	calc_distance();
	
	if(dist < object)
	{
		forward();
	}
	else
	{
		findroute();
	}
}

void calc_distance()
{
	delay(50);
	int dist = sonar.ping_cm();
	Serial.print(dist);
	Serial.println("cm");
	return;
}

void forward() 
{
	digitalWrite(motor_pin1,HIGH);
	digitalWrite(motor_pin2,LOW);
	digitalWrite(motor_pin3,HIGH);
	digitalWrite(motor_pin4,LOW);
	return;
}
 
void findroute() 
{
	halt();
	backward();
	lookleft();
	lookright();
	                              
	if ( leftdist > rightdist )
	{
		turnleft();
	}
	else
	{
		turnright ();
	}
}

void halt() 
{
	digitalWrite(motor_pin1,LOW);
	digitalWrite(motor_pin2,LOW);
	digitalWrite(motor_pin3,LOW);
	digitalWrite(motor_pin4,LOW);
	delay(500);
	return;
}

void backward() 
{
	digitalWrite(motor_pin1,LOW);
	digitalWrite(motor_pin2,HIGH);
	digitalWrite(motor_pin3,LOW);
	digitalWrite(motor_pin4,HIGH);
	delay(1500);
	halt();
	return;
}
 
void lookleft() 
{
	for(pos = 90; pos < 180; pos += 1)
	{
		myservo.write(pos);
		delay(20);
	}
	calc_distance();
	leftdist = dist;
	return;
}

void lookright()
{
	for(pos = 180; pos>=1; pos-=1)
	{
		myservo.write(pos);
		delay(20);
	}
	calc_distance();
	rightdist = dist;
	for(pos = 0; pos < 90; pos += 1)
	{
		myservo.write(pos);
		delay(20);
	}
	return;
}

void turnleft()
{
	digitalWrite(motor_pin1,HIGH);
	digitalWrite(motor_pin2,LOW);
	digitalWrite(motor_pin3,LOW);
	digitalWrite(motor_pin4,HIGH);
	delay(3000);
	halt();
	return;
}

void turnright()
{
	digitalWrite(motor_pin1,LOW);
	digitalWrite(motor_pin2,HIGH);
	digitalWrite(motor_pin3,HIGH);
	digitalWrite(motor_pin4,LOW);
	delay(3000);
	halt();
	return;
}
