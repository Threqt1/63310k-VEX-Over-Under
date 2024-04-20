#include "main.h"

// cata 7 (5.5) 8 (green) (a and b)
// intake r1 r2 10 (5.5)
// wings l1 l2 toggle on X between horiz and vert
// hang is up/down
// drive 600 rpm 333 speed
// cata 100% 5.5 is 200rpm

// Controller link
Controller controller(E_CONTROLLER_MASTER);

MotorGroup intake({Motor(12, E_MOTOR_GEAR_200),
				   Motor(-18, E_MOTOR_GEAR_200)});

// a wings
ADIDigitalOut verticalWings('A');
// c hang
ADIDigitalOut horizontalWings('C');

// Drivetrain motors
Motor leftMotor1(1);
Motor leftMotor2(2);
Motor leftMotor3(8);
Motor rightMotor1(-4);
Motor rightMotor2(-5);
Motor rightMotor3(-6);

// Drivetrain motor groups
MotorGroup rightSideMotors({leftMotor1, leftMotor2, leftMotor3});
MotorGroup leftSideMotors({rightMotor1, rightMotor2, rightMotor3});

// Inertial sensor
IMU inertial(18);

// Rotation sensor
// pros::Rotation horiSensor(10);
// lemlib::TrackingWheel horizontal(&horiSensor, lemlib::Omniwheel::NEW_275, 3);

// Initialize the LemLib drivetrain settings
lemlib::Drivetrain drivetrain(
	&leftSideMotors,			// left side motors
	&rightSideMotors,			// right side motors
	11,							// track width in inches
	lemlib::Omniwheel::NEW_325, // wheel diameter
	450,						// rpm
	8							// chase power (probably for pure pursuit)
);

// Set up linear movement settings (forward/backward)
lemlib::ControllerSettings linearMovementSettings(
	20,	 // P
	0,	 // I
	40,	 // D
	3,	 // antiwindup
	1,	 // small error (use for tuning settling)
	60,	 // small error timeout
	3,	 // large error (use to quit movement if stuck)
	500, // large error timeout
	20	 // maximum acceleration (slew)
);

// Set up angular movement settings (turning)
lemlib::ControllerSettings angularMovementSettings(
	7,	 // P
	0,	 // I
	65,	 // D
	3,	 // antiwindup
	2,	 // small error (use for tuning settling)
	60,	 // small error timeout
	3,	 // large error (use to quit movement if stuck)
	500, // large error timeout
	20	 // maximum acceleration (slew)
);

// Set up odometry sensors
lemlib::OdomSensors odometrySensors(
	nullptr,  // vertical tracking wheel 1
	nullptr,  // vertical tracking wheel 2
	nullptr,  //&horizontal, // horizontal tracking wheel 1
	nullptr,  // horizontal tracking wheel 2
	&inertial // inertial sensor
);

// Configure the lemlib chassis
lemlib::Chassis chassis(drivetrain, linearMovementSettings, angularMovementSettings, odometrySensors);

void initialize()
{
	pros::lcd::initialize(); // initialize brain screen
	chassis.calibrate();	 // calibrate sensors
							 //  catapult.set_brake_modes(E_MOTOR_BRAKE_HOLD);
							 // leftSideMotors.set_voltage_limit(5000);
							 // rightSideMotors.set_voltage_limit(5000);
	// leftMotor4.set_voltage_limit(6000);
	// rightMotor4.set_voltage_limit(6000);

	// // thread to for brain screen and position logging
	pros::Task screenTask([&]()
						  {
	    while (true) {
	        // print robot location to the brain screen
	        lemlib::Pose pose = chassis.getPose(); // get the current position of the robot
			pros::lcd::print(0, "x: %f", pose.x); // print the x position
			pros::lcd::print(1, "y: %f", pose.y); // print the y position
			pros::lcd::print(2, "heading: %f", pose.theta); // print the heading
			pros::delay(10);
	    } });
}

void disabled() {}

void competition_initialize() {}

void autonomous()
{
	leftSideMotors.set_brake_modes(MOTOR_BRAKE_HOLD);
	rightSideMotors.set_brake_modes(MOTOR_BRAKE_HOLD);

	// //left mid
	// chassis.turnTo(-12, 27, 300, true);
	// chassis.moveToPoint(-12, 27, 2000, true);

	// //mid mid
	// chassis.turnTo(-25, 9, 300, true);
	// chassis.moveToPoint(-25, 9, 1000, true);

	// top mid
	//  chassis.turnTo(-2, 9, 300, true);
	//  chassis.moveToPoint(-2, 9, 1000, true);

	// chassis.calibrate();
	intake.move_voltage(12000);
	delay(200);
	// intake.brake();

	// new awp
	intake.move_voltage(-12000);
	chassis.setPose(-33, -54, 0);
	chassis.moveToPoint(-26, -8, 2000, true);
	intake.move_voltage(-12000);
	delay(1100);
	intake.brake();
	chassis.moveToPoint(-26, -20, 2000, false);

	chassis.turnTo(-47, -63, 1000, true);
	chassis.moveToPoint(-47, -63, 2000, true);

	chassis.turnTo(-36, -74, 1000, true);
	delay(1000);
	verticalWings.set_value(true);
	delay(500);
	chassis.turnTo(-10, -47, 500, true);
	chassis.turnTo(-42, -35, 500, true);
	delay(500);
	verticalWings.set_value(false);

	chassis.turnTo(-17, -66, 1000, true);
	intake.move_voltage(12000);
	delay(400);
	horizontalWings.set_value(true);
	chassis.moveToPoint(-17, -66, 1500, true);
	delay(700);
	horizontalWings.set_value(false);
	chassis.turnTo(-7, -60, 1000, true);
	chassis.moveToPoint(-7, -60, 1000, true);
	delay(2000);
	intake.brake();

	// 6 ball thats def 5
	//  chassis.setPose(-5, 58, 90);
	//  chassis.moveToPoint(2, 58, 2000);
	//  intake.move_voltage(-12000);
	//  chassis.moveToPoint(-17, 57, 700, false);
	//  intake.brake();
	//  chassis.moveToPoint(-38, 50, 800, false);
	//  chassis.moveToPoint(-41, 45, 700, false);
	//  delay(400);
	//  horizontalWings.set_value(true);
	//  chassis.turnTo(-10, 0, 800, false, 50);
	//  chassis.turnTo(-52, 43, 700, false);
	//  horizontalWings.set_value(false);
	//  chassis.moveToPoint(-54, 43, 700, false);
	//  chassis.moveToPoint(-54, 20, 700, false);
	//  chassis.moveToPoint(-58, 35, 700, true);
	//  chassis.moveToPoint(-58, 20, 700, false);

	// chassis.moveToPoint(-58, 34, 700, true);
	// chassis.turnTo(-53, 20, 700, true);
	// chassis.turnTo(-56, 20, 400, true);
	// intake.move_voltage(12000);
	// delay(200);
	// chassis.moveToPoint(-56, 20, 600, true);

	// intake.move_voltage(-12000);
	// chassis.moveToPoint(-47, 39, 1000, false);

	// chassis.turnTo(-9, 24, 300, true);
	// chassis.moveToPoint(-9, 24, 2000, true);
	// delay(1100);
	// intake.brake();
	// chassis.turnTo(-47, -2, 1000, true);
	// delay(300);
	// intake.move_voltage(12000);
	// delay(1100);

	// intake.move_voltage(-12000);
	// chassis.turnTo(10, -1, 700, true);
	// chassis.moveToPoint(10, -1, 1000, true);
	// delay(1250);

	// intake.brake();
	// chassis.turnTo(-47, -9, 1000, true);
	// delay(500);
	// horizontalWings.set_value(true);
	// delay(200);
	// intake.move_voltage(12000);
	// chassis.moveToPoint(-47, -9, 800, true);
	// chassis.moveToPoint(0, -9, 1000, false);

	// old fail
	//  verticalWings.set_value(true);
	//  intake.move_voltage(12000);
	//  delay(200);
	//  verticalWings.set_value(false);
	//  intake.brake();

	// intake.move_voltage(-12000);
	// chassis.turnTo(-25, 9, 300, true);
	// chassis.moveToPoint(-25, 9, 1000, true);
	// delay(100);

	// chassis.turnTo(-36, 55, 800, false);
	// chassis.moveToPoint(-36, 55, 1000, false);

	// chassis.turnTo(-58, 25, 500, true);
	// intake.move_voltage(12000);
	// delay(900);
	// intake.move_voltage(-12000);

	// chassis.turnTo(-4, 59, 800, true);
	// chassis.moveToPoint(-4, 59, 1700, true);
	// delay(100);

	// chassis.turnTo(-36, 55, 800, false);
	// chassis.moveToPoint(-36, 55, 1400, false);

	// chassis.moveToPoint(-50, 53, 1500, false);
	// // chassis.moveToPoint(-55, 40, 1000, false);
	// chassis.moveToPoint(-60, 28, 1500, false);

	// chassis.moveToPoint(-57, 40, 1000, true);
	// intake.brake();
	// chassis.moveToPoint(-36, 55, 1200, true);

	// chassis.turnTo(-50, 53, 700, true);
	// intake.move_voltage(-12000);
	// chassis.moveToPoint(-50, 53, 1000, true);
	// chassis.moveToPoint(-60, 47, 700, true);
	// verticalWings.set_value(true);
	// chassis.moveToPoint(-62, 46, 800, true);
	// chassis.moveToPoint(-62, 44, 800, true);
	// chassis.turnTo(28, -8, 800, true);
	// verticalWings.set_value(false);
	// intake.move_voltage(12000);
	// chassis.turnTo(-63, 25, 700, true);
	// chassis.moveToPoint(-63, 25, 900, true);

	// chassis.moveToPoint(-60, 28, 1000, false);
	// chassis.moveToPoint(-50, 43, 1000, false);
	// intake.move_voltage(-12000);

	// skills
	//  chassis.setPose(-35, -62, 90);
	//  chassis.follow(path63d_txt, 11, 1200, false, false);
	//  chassis.moveToPoint(-61, -28, 500, false);
	//  chassis.turnTo(-50, -43, 700, true);
	//  chassis.moveToPoint(-50, -43, 1000, true);
	//  chassis.moveToPoint(-72, -69, 1000, false);
	//  chassis.turnTo(45, -25, 1000, true);
	//  chassis.moveToPoint(-73, -69, 50, false);
	//  chassis.turnTo(45, -25, 1000, true);
	//  catapult.move_voltage(-12000);
	//  delay(26000);

	// chassis.moveToPoint(-55, -50, 1500, true);
	// chassis.turnTo(-30, -70, 1300, false);

	// catapult.move_voltage(-10000);
	// chassis.follow(path6d_txt, 15, 4500, false, false);
	// catapult.brake();

	// chassis.moveToPoint(67, -20, 700, false);
	// chassis.moveToPoint(66, -55, 1000, true);
	// chassis.moveToPoint(66, -20, 700, false);

	// chassis.moveToPoint(35, -36, 1500, true);
	// chassis.moveToPoint(17, -29, 1500, true);

	// chassis.moveToPoint(17, -17, 1500, false);
	// chassis.turnTo(49, -4, 1000, true);
	// delay(1000);
	// horizontalWings.set_value(true);
	// chassis.moveToPoint(49, -4, 1000, true);
	// delay(700);
	// horizontalWings.set_value(false);

	// chassis.moveToPoint(18, -17, 1500, false);
	// chassis.moveToPoint(18, 17, 1500, false);
	// chassis.turnTo(49, -4, 1000, true);
	// horizontalWings.set_value(true);
	// chassis.moveToPoint(49, 5, 1500, true);
	// delay(600);
	// horizontalWings.set_value(false);

	// chassis.moveToPoint(18, 17, 1500, false);
	// chassis.turnTo(49, -4, 1000, true);
	// horizontalWings.set_value(true);
	// chassis.moveToPoint(49, 0, 1500, true);
	// delay(1000);
	// horizontalWings.set_value(false);

	// chassis.moveToPoint(20, 17, 1500, false);
	// chassis.turnTo(25, 25, 1000, false);

	// chassis.follow(path95f_txt, 15, 4000, false, false);
	// chassis.moveToPoint(65, 20, 1000, false);

	// awp
	//  chassis.setPose(-38, -55, 0);
	//  intake.move_voltage(-12000);
	//  chassis.moveToPoint(-23, 2, 1000, true);
	//  delay(400);
	//  chassis.turnTo(-38, -55, 1000, true);
	//  delay(700);
	//  intake.move_voltage(12000);
	//  delay(700);
	//  intake.move_voltage(-12000);
	//  chassis.turnTo(-1, 0, 600, true);
	//  chassis.moveToPoint(-1, 0, 700, true);

	// chassis.turnTo(-55, -57, 700, false);
	// chassis.moveToPoint(-49, -59, 2500, false);
	// chassis.turnTo(-49, -100, 300, false);
	// verticalWings.set_value(true);
	// chassis.turnTo(45, 11, 600, false);
	// chassis.turnTo(0, -70, 600, false);
	// chassis.moveToPoint(0, -70, 1000, false);

	// bad awp
	//  chassis.setPose(0, 0, 0);
	//  intake.move_voltage(12000);
	//  pros::delay(300);
	//  chassis.moveToPose(0, 10, 0, 800);
	//  chassis.moveToPose(0, 10, 30, 800);
	//  intake.move_voltage(12000);
	//  pros::delay(500);
	//  intake.move_voltage(0);
	//  chassis.moveToPose(0, 10, 0, 800);
	//  verticalWings.set_value(true);
	//  pros::delay(500);
	//  chassis.moveToPose(0, 5, 0, 800, {false});
	//  chassis.turnTo(-30, 30, 800);
	//  chassis.turnTo(20, -30, 800);
	//  verticalWings.set_value(false);
	//  intake.move_voltage(120000);
	//  chassis.moveToPoint(16, -37, 2000);
	//  pros::delay(2000);
	//  intake.move_voltage(0);
}

void opcontrol()
{

	leftSideMotors.set_brake_modes(MOTOR_BRAKE_COAST);
	rightSideMotors.set_brake_modes(MOTOR_BRAKE_COAST);

	pros::Task drivetrainTask(DrivetrainTask, (void *)"", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "drivetrain");

	pros::Task mechanismsTask(MechanismsTask, (void *)"", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "mechanisms");

	while (true)
	{
		delay(20);
	}
}
