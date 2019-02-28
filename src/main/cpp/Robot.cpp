/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <iostream>

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
}

void Robot::AutonomousPeriodic()
{
  if (m_timer.Get() < 10.0)
  {
    com.SetClosedLoopControl(true);
    //m_robotDrive.ArcadeDrive(-0.5, 0.0);
  }
  else
  {
    com.SetClosedLoopControl(false);
    //sole0.Set(frc::DoubleSolenoid::Value::kReverse);
    //m_robotDrive.ArcadeDrive(0.0, 0.0);
  }

  if(pin0.Get() == false){
      std::cout << "googogogo" << std::endl;
  }

  if (m_autoSelected == kAutoNameCustom)
  {
    // Custom Auto goes here
  }
  else
  {
    // Default Auto goes here
  }
}

void Robot::TeleopInit() {
  com.SetClosedLoopControl(true);
}

void Robot::TeleopPeriodic()
{
  m_robotDrive.ArcadeDrive(-m_controller.GetY(frc::XboxController::JoystickHand::kLeftHand)*0.35, m_controller.GetX(frc::XboxController::JoystickHand::kLeftHand)*0.45);
  if(m_controller.GetStartButton()){
    m_rearTire.Set(-m_controller.GetY(frc::XboxController::JoystickHand::kLeftHand)*0.35);
  }else{
    m_rearTire.Set(0);
  }

  m_arm.Set(m_controller.GetY(frc::XboxController::JoystickHand::kRightHand)*0.40);
  
  if(m_controller.GetAButton()){
    m_shot.Set(1.00);
  }else if(m_controller.GetBButton()){
    m_shot.Set(-0.3);
  }else{
    m_shot.Set(0);
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
  }else if(m_controller.GetBumper(frc::XboxController::JoystickHand::kLeftHand)){
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
