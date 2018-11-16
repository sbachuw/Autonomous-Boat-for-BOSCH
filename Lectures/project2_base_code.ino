// ========================================================
// File Name: project2_base_code_1.ino
// Discription:
// AUE853 Projet 2: Autonous Boat Naviagation
// This artuino script is used to demo the basic movement 
// of a boat which is configurated as a differential drive
// Author: Max, Yi
// Date: 11/11/2016
// Version: 1.0
//=========================================================

//=========================================================
// Import library
// For our motor driver, we only use the build in libarary
// of Arduino

//=========================================================
// Declare object
// For our motor driver, we only use the build in libarary
// of Arduino

//=========================================================
// Pin definition
// Pins for motor control
// The 6 pins of motor control are  defined here, you need
// to change the value to meet your hardware configuration
// Note: The enable pins of both motors must be a PWM pin
// Others can be normal Digital I/O pin.
#define ML_IN1 2   // For Motor 1 direction
#define ML_IN2 4   // For Motor 1 direction
#define ML_EN 3    // For Motor 1 speed 
#define MR_IN3 7   // For Motor 2 direction
#define MR_IN4 8   // For Motor 2 direction
#define MR_EN 6    // For Motor 2 speed

//=========================================================
// Constant definition
// Index of motor
#define MOTOR_LEFT 1
#define MOTOR_RIGHT 2
// Set a limit for velocity and omega
#define OMEGA_LIMIT 20
#define VEL_LIMIT 235

// Control frequency
#define CONTROL_FREQ 20

//=========================================================.
// Global variables

//=========================================================
// User define functions
void set_motor_speed(int motor, int speed) {
  // The motor left and motor right are used as variables
  // here, but you should change either the code or your 
  // hardware configuration to make the code match the 
  // hardware


  // Set direction and speed for certain motor.
  // constrain speed into [0, 255]
  int vel_cmd = constrain(abs(speed), 0, 255);
  if (motor == MOTOR_LEFT){
    if (speed > 0) {
      // Turn the motor in one direction
      digitalWrite(ML_IN1, LOW);
      digitalWrite(ML_IN2, HIGH);
      analogWrite(ML_EN, vel_cmd);
      Serial.println("vel_left > 0");
    }
    else if (speed < 0) {
      // Turn the motor in another direction
      digitalWrite(ML_IN1, HIGH);
      digitalWrite(ML_IN2, LOW);
      analogWrite(ML_EN, vel_cmd);
      Serial.println("vel_left < 0");
    }
    else
    {
      // Stop the motor
      digitalWrite(ML_IN1, LOW);
      digitalWrite(ML_IN2, LOW);
      analogWrite(ML_EN, 0);
      Serial.println("vel_left = 0");

    }
  }
  else if (motor == MOTOR_RIGHT){
    if (speed > 0) {
      // Turn the motor in one direction
      digitalWrite(MR_IN3, HIGH);
      digitalWrite(MR_IN4, LOW);
      analogWrite(MR_EN,vel_cmd);
      Serial.println("vel_right > 0");     
    }
    else if (speed < 0) {
      // Turn the motor in another direction
      digitalWrite(MR_IN3, LOW);
      digitalWrite(MR_IN4, HIGH);
      analogWrite(ML_EN,  vel_cmd);
      Serial.println("vel_right < 0");     
    }
    else
    {
      // Stop the motor
      digitalWrite(MR_IN3, LOW);
      digitalWrite(MR_IN4, LOW);
      analogWrite(MR_EN, 0);
      Serial.println("vel_right = 0");     

    }
  }
}

void set_boat_move(int vel, int omega){
  // This function is called to set the 
  // linear and angular velocity of the 
  // boat. You cna find the nutural position
  // of your boat by tuning the v and omega.
  
  // Linear and anglular velocity 
  int v=constrain(vel, -VEL_LIMIT, VEL_LIMIT);
  int w=constrain(omega, -OMEGA_LIMIT, OMEGA_LIMIT);
  // Motor velocity command for both motors
  int vel_L = constrain(v+w, -255, 255);
  int vel_R = constrain(v-w, -255, 255);
  // Set speed for both motors
  set_motor_speed(MOTOR_LEFT, vel_L);
  set_motor_speed(MOTOR_RIGHT,vel_R);
  
}

//=========================================================
// Arduino Setup
void setup() {

  // Setup serial port
  Serial.begin(9600);

  // Init Pins
  // Set pin for motor drive
  pinMode(ML_IN1, OUTPUT);
  pinMode(ML_IN2, OUTPUT);
  pinMode(ML_EN, OUTPUT);
  pinMode(MR_IN3, OUTPUT);
  pinMode(MR_IN4, OUTPUT);
  pinMode(MR_EN, OUTPUT);

  // Set both motor speed as zero
  set_motor_speed(MOTOR_LEFT, 0);
  set_motor_speed(MOTOR_RIGHT, 0);

  // Wait for 1 second, let the system become stable
  delay(1000);
  
}

//=========================================================
// Arduino Loop
void loop() {
  //--------------------------------------
  // Test for set_motor_speed()
  // Set both motor speed 
  set_motor_speed(MOTOR_LEFT, 220);
  set_motor_speed(MOTOR_RIGHT, 220);
  Serial.println("+++++");
  delay(3000);
  

  // Set both motor speed
  set_motor_speed(MOTOR_LEFT, -220);
  set_motor_speed(MOTOR_RIGHT, -220);
  Serial.println("----");
  delay(3000);
  //---------------------------------------

  //---------------------------------------
  // Test for set_boat_move()
  // Set both motor speed 
  set_boat_move(200, 0);
  delay(3000);
  
  // Set both motor speed 
  set_boat_move(200, -15);
  delay(3000);
  
  // Set both motor speed 
  set_boat_move(200, 10);
  delay(3000);


}
