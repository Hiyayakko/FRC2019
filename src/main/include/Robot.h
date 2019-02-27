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
#include <frc/PWMVictorSPX.h>
#include <frc/SpeedControllerGroup.h>
#include <frc/Timer.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/Solenoid.h>
#include <frc/DoubleSolenoid.h>
#include <frc/Compressor.h>
#include <frc/DigitalInput.h>
#include <frc/XboxController.h>

//camera
#include <cameraserver/CameraServer.h>
//#include <cs/cscore_oo.h>


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

  bool jointFlag{false};

/*モーター*/
  //足回り
  frc::PWMVictorSPX m_flontLeft{0};
  frc::PWMVictorSPX m_rearLeft{1};
  frc::SpeedControllerGroup m_left{m_flontLeft,m_rearLeft};
  frc::PWMVictorSPX m_flontRight{2};
  frc::PWMVictorSPX m_rearRight{3};
  frc::SpeedControllerGroup m_right{m_flontRight,m_rearRight};

  frc::DifferentialDrive m_robotDrive{m_left,m_right};
  
  //カーゴ
  frc::PWMVictorSPX m_shotRight{4};
  frc::PWMVictorSPX m_shotLeft{5};//invert

  frc::SpeedControllerGroup m_shot{m_shotRight,m_shotLeft};

  //後方上昇
  frc::PWMVictorSPX m_up{6};

  //後方タイヤ
  frc::PWMVictorSPX m_rearTire{7};

  //アーム
  frc::PWMVictorSPX m_armRight{8};
  frc::PWMVictorSPX m_armLeft{9};//invert

  frc::SpeedControllerGroup m_arm{m_armRight,m_armLeft};

  //エアー
  //ハッチパネル
  frc::Solenoid pushLeft{3};
  frc::Solenoid pushRight{0};
  //アーム
  frc::Solenoid jointLeft{2};
  frc::Solenoid jointRight{1};

  
  frc::Compressor com{0};

  frc::DigitalInput pin0{0};

  //コントローラー
  frc::XboxController m_controller{2};

  frc::Timer m_timer;

  //frc::CameraServer cam0;

};
