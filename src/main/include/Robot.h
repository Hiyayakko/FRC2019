/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string>

#include <frc/TimedRobot.h>
#include <frc/Joystick.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/PWMVictorSPX.hj>
#include <frc/SpeedControllerGroup.h>
#include <frc/Timer.h>
#include <frc/drive/DifferentialDrive.h>


class Robot : public frc::TimedRobot {
 public:
  Robot();
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;

 private:
  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  std::string m_autoSelected;

  frc::PWMVictorSPX m_flontLeft{0};
  frc::PWMVictorSPX m_rearLeft{1};
  frc::SpeedControllerGroup m_left{m_flontLeft,m_rearLeft};
  frc::PWMVictorSPX m_flontRight{2};
  frc::PWMVictorSPX m_rearRight{3};
  frc::SpeedControllerGroup m_right{m_flontRight,m_rearRight};
  frc::DifferentialDrive m_robotDrive{m_left,m_right};
  
  frc::Joystick m_stick{0};
  frc::Timer m_timer;
};
