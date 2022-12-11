#include "SoftHalfDuplexSerial.h"
#include "DynamixelAx.h"

#define SCISSOR 1
#define ROCK 2
#define PAPER 14

#define UP_SPEED 200
#define DOWN_SPEED 100
#define UP_POSITION 204
#define DOWN_POSITION 490

softHalfDuplexSerial port(8); // data pin 8
dxlAx dxlCom(&port);


int count = 0;
int old_count = 0;
int distance = 0;
int min_distance = 0;
int max_distance = 12;
long randNumber;

void setup() {
  Serial.begin(57600);
  randomSeed(analogRead(0));
  dxlCom.begin(57600);
  downAllMotors();
  upAllMotors();
  downMotor(SCISSOR);
  downMotor(ROCK);
  downMotor(PAPER);
  Serial.println("ready for start");
}

void loop() {
  ///////////////초음파 센서 인식/////////////
  int volt = map(analogRead(A0), 0, 1023, 0, 5000);
  distance = (27.61 / (volt - 0.1696)) * 1000;
  //Serial.println(distance);

  if (distance >= min_distance && distance <= max_distance)
  {
    count = 1;
  }
  else
  {
    count = 0;
  }

  if (count != old_count)
  {
    if (count && !old_count)
    {
      randNumber = random(1, 4);
      // Serial.println(randNumber);
      if (randNumber == 1)  // 가위
      {
        upMotor(SCISSOR);
      }
      else if (randNumber == 2) // 바위
      {
        upMotor(ROCK);
      }
      else if (randNumber == 3) // 보
      {
        upMotor(PAPER);
      }
      delay(1000);
    }
    else if (!count && old_count) 
    {
      downAllMotors();
    }

    old_count = count;
  }
}

void downMotor(byte id)
{
  dxlCom.setGoalPositionAtSpeed(id, DOWN_POSITION, DOWN_SPEED);
  while(!dxlCom.dxlDataReady());        // waiting the answer of servo
  dxlCom.readDxlError();
  dxlCom.readDxlResult();
  bool isMoving = true;
  while (isMoving)
  {
    unsigned short error = DXL_ERR_SUCCESS;
    while(dxlCom.isBusy()); // waiting the status return delay time (for testing if it is moving)
    dxlCom.isMoving(id);
    while(!dxlCom.dxlDataReady());        // waiting the answer of servo
    error = dxlCom.readDxlError();
    isMoving = dxlCom.readDxlResult();
  }
}

void downAllMotors()
{
  dxlCom.setGoalPositionAtSpeed(1, DOWN_POSITION, DOWN_SPEED);
  while(!dxlCom.dxlDataReady());        // waiting the answer of servo
  dxlCom.readDxlError();
  dxlCom.readDxlResult();
  dxlCom.setGoalPositionAtSpeed(2, DOWN_POSITION, DOWN_SPEED);
  while(!dxlCom.dxlDataReady());        // waiting the answer of servo
  dxlCom.readDxlError();
  dxlCom.readDxlResult();
  dxlCom.setGoalPositionAtSpeed(14, DOWN_POSITION, DOWN_SPEED);
  while(!dxlCom.dxlDataReady());        // waiting the answer of servo
  dxlCom.readDxlError();
  dxlCom.readDxlResult();
  bool isMoving = true;
  while (isMoving)
  {
    unsigned short error = DXL_ERR_SUCCESS;
    while(dxlCom.isBusy()); // waiting the status return delay time (for testing if it is moving)
    dxlCom.isMoving(SCISSOR);
    while(!dxlCom.dxlDataReady());        // waiting the answer of servo
    error = dxlCom.readDxlError();
    isMoving = dxlCom.readDxlResult();
    while(dxlCom.isBusy()); // waiting the status return delay time (for testing if it is moving)
    dxlCom.isMoving(ROCK);
    while(!dxlCom.dxlDataReady());        // waiting the answer of servo
    error = dxlCom.readDxlError();
    isMoving |= dxlCom.readDxlResult();
    while(dxlCom.isBusy()); // waiting the status return delay time (for testing if it is moving)
    dxlCom.isMoving(PAPER);
    while(!dxlCom.dxlDataReady());        // waiting the answer of servo
    error = dxlCom.readDxlError();
    isMoving |= dxlCom.readDxlResult();
  }
}

void upMotor(byte id)
{
  dxlCom.setGoalPositionAtSpeed(id, UP_POSITION, UP_SPEED);
  while(!dxlCom.dxlDataReady());        // waiting the answer of servo
  dxlCom.readDxlError();
  dxlCom.readDxlResult();
  bool isMoving = true;
  while (isMoving)
  {
    unsigned short error = DXL_ERR_SUCCESS;
    while(dxlCom.isBusy()); // waiting the status return delay time (for testing if it is moving)
    dxlCom.isMoving(id);
    while(!dxlCom.dxlDataReady());        // waiting the answer of servo
    error = dxlCom.readDxlError();
    isMoving = dxlCom.readDxlResult();
  }
}

void upAllMotors()
{
  dxlCom.setGoalPositionAtSpeed(1, UP_POSITION, UP_SPEED);
  while(!dxlCom.dxlDataReady());        // waiting the answer of servo
  dxlCom.readDxlError();
  dxlCom.readDxlResult();
  dxlCom.setGoalPositionAtSpeed(2, UP_POSITION, UP_SPEED);
  while(!dxlCom.dxlDataReady());        // waiting the answer of servo
  dxlCom.readDxlError();
  dxlCom.readDxlResult();
  dxlCom.setGoalPositionAtSpeed(14, UP_POSITION, UP_SPEED);
  while(!dxlCom.dxlDataReady());        // waiting the answer of servo
  dxlCom.readDxlError();
  dxlCom.readDxlResult();
  bool isMoving = true;
  while (isMoving)
  {
    unsigned short error = DXL_ERR_SUCCESS;
    while(dxlCom.isBusy()); // waiting the status return delay time (for testing if it is moving)
    dxlCom.isMoving(SCISSOR);
    while(!dxlCom.dxlDataReady());        // waiting the answer of servo
    error = dxlCom.readDxlError();
    isMoving = dxlCom.readDxlResult();
    while(dxlCom.isBusy()); // waiting the status return delay time (for testing if it is moving)
    dxlCom.isMoving(ROCK);
    while(!dxlCom.dxlDataReady());        // waiting the answer of servo
    error = dxlCom.readDxlError();
    isMoving |= dxlCom.readDxlResult();
    while(dxlCom.isBusy()); // waiting the status return delay time (for testing if it is moving)
    dxlCom.isMoving(PAPER);
    while(!dxlCom.dxlDataReady());        // waiting the answer of servo
    error = dxlCom.readDxlError();
    isMoving |= dxlCom.readDxlResult();
  }
}
