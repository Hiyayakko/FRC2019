/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <frc/smartdashboard/SmartDashboard.h>

Robot::Robot()
{
  m_robotDrive.SetExpiration(0.1);
  m_timer.Start();
}

void Robot::RobotInit()
{
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
  m_shotLeft.SetInverted(true);
  m_armLeft.SetInverted(true);
  frc::CameraServer::GetInstance()->StartAutomaticCapture();
  //encoder setting
  encdrArm.SetMaxPeriod(0.1);
  encdrArm.SetMinRate(10);
  encdrArm.SetDistancePerPulse(1);
  encdrArm.SetReverseDirection(false);
  encdrArm.SetSamplesToAverage(7);
  //PID
  PIDArm->SetInputRange(-1200,100);
  PIDArm->SetOutputRange(-1.00,1.00);
  PIDArm->SetPercentTolerance(3);
  PIDArm->SetSetpoint(0);
  
  
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */

/*
自動初期設定:"FRC Driver Station"で、"Autonomous"を"enable"にした時に一度だけ実行される。
*/

void Robot::AutonomousInit()
{
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  std::cout << "Auto selected: " << m_autoSelected << std::endl;
  m_timer.Reset();
  m_timer.Start();
  if (m_autoSelected == kAutoNameCustom)
  {
    // Custom Auto goes here
  }
  else
  {
    // Default Auto goes here
  }
  com.SetClosedLoopControl(true);
  //PIDArm->Enable();
  //PIDArm->Reset();
}

//自動初期設定:"FRC Driver Station"で、"Autonomous"を"enable"にした時に"AutomasInit()"を実行したあとに"disable"されるまで繰り返し実行される。
void Robot::AutonomousPeriodic()
{
  std::cout << encdrArm.Get() << std::endl;
  //std::cout << PIDArm->IsEnabled() << std::endl;
  m_arm.Set(m_controller.GetY(frc::XboxController::JoystickHand::kRightHand)*0.40);

  if (m_autoSelected == kAutoNameCustom)
  {
    // Custom Auto goes here
  }
  else
  {
    // Default Auto goes here
  }
  if(m_timer.Get() < 5){
    PIDArm->PIDWrite(-500);
    std::cout << "first" << std::endl;
  }else if(m_timer.Get() < 20){
    PIDArm->PIDWrite(-1000);
    std::cout << "second" << std::endl;
  }else{
    //PIDArm->PIDWrite(0);
    std::cout << "third" << std::endl;
  }
  std::cout << "ontarget" << PIDArm->OnTarget() << std::endl;
  if(PIDArm->OnTarget() && PIDArm->IsEnabled()){
    PIDArm->Disable();
  }else if(!PIDArm->OnTarget() && !PIDArm->IsEnabled()){
    PIDArm->Enable();
  }

  if(m_controller.GetStickButtonPressed(frc::XboxController::JoystickHand::kRightHand)){
    jointFlag = true;
    jointLeft.Set(true);
    jointRight.Set(true);
  }else if(m_controller.GetStickButtonPressed(frc::XboxController::JoystickHand::kLeftHand)){
    jointFlag = false;
    jointLeft.Set(false);
    jointRight.Set(false);
  }
}

void Robot::TeleopInit() {
  com.SetClosedLoopControl(true);
}

void Robot::TeleopPeriodic()
{
  m_robotDrive.ArcadeDrive(-m_controller.GetY(frc::XboxController::JoystickHand::kLeftHand)*DriveSpeed, m_controller.GetX(frc::XboxController::JoystickHand::kLeftHand)*DriveSpeed*1.2);
  if(m_controller.GetStartButton()){
    m_rearTire.Set(-m_controller.GetY(frc::XboxController::JoystickHand::kLeftHand)*DriveSpeed);
  }else{
    m_rearTire.Set(0);
  }
  if(m_controller.GetY(frc::XboxController::JoystickHand::kRightHand)>0.5 && IsArmGe && !ArmFlag){
    ArmFlag = true;
    IsArmGe = false;
    IsArmChu = true;
    IsArmJou = false;
    //PIDArm->PIDWrite();
  }else if(m_controller.GetY(frc::XboxController::JoystickHand::kRightHand)>0.5 && IsArmChu && !ArmFlag){
    ArmFlag = true;
    IsArmGe = false;
    IsArmChu = false;
    IsArmJou = true;
    //PIDArm->PIDWrite();
  }else if(m_controller.GetY(frc::XboxController::JoystickHand::kRightHand)<0.5 && ArmFlag){
    ArmFlag = false;
  }
  //m_arm.Set(m_controller.GetY(frc::XboxController::JoystickHand::kRightHand)*0.40);
  
  if(m_controller.GetAButton()){
    DriveSpeed = 0.2;
  }else if(m_controller.GetBButton()){
    DriveSpeed = 0.6;
  }else{
    DriveSpeed = 0.35;
  }

  if(m_controller.GetXButton()){
    m_up.Set(0.3);
  }else if(m_controller.GetYButton()){
    m_up.Set(-0.3);
  }else{
    m_up.Set(0);
  }

  if(m_controller.GetStickButtonPressed(frc::XboxController::JoystickHand::kRightHand)){
    jointFlag = true;
    jointLeft.Set(true);
    jointRight.Set(true);
  }else if(m_controller.GetStickButtonPressed(frc::XboxController::JoystickHand::kLeftHand)){
    jointFlag = false;
    jointLeft.Set(false);
    jointRight.Set(false);
  }

  if(m_controller.GetBumper(frc::XboxController::JoystickHand::kRightHand)){
    pushLeft.Set(true);
    pushRight.Set(true);
  }else{
    pushLeft.Set(false);
    pushRight.Set(false);
  }
  /*
  if(m_controller.GetY()>0.5){
    //sole1.Set(true);
    //sole0.Set(frc::DoubleSolenoid::Value::kForward);
  }else if(m_controller.GetY()<-0.5){
    sole1.Set(false);
    //sole0.Set(frc::DoubleSolenoid::Value::kReverse);
  }else{
    //sole0.Set(frc::DoubleSolenoid::Value::kOff);
  }

  if(m_controller.GetX()>0.5){
    com.SetClosedLoopControl(true);
  }else if(m_controller.GetX()<-0.5){
    com.SetClosedLoopControl(false);
  }
*/
}

void Robot::TestPeriodic()
{
}

#ifndef RUNNING_FRC_TESTS
int main()
{
  return frc::StartRobot<Robot>();
}
#endif
