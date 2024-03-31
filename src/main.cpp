#include "main.h"

// cata 7 (5.5) 8 (green) (a and b)
// intake r1 r2 10 (5.5)
// wings l1 l2 toggle on X between horiz and vert
// hang is up/down
// drive 600 rpm 333 speed
// cata 100% 5.5 is 200rpm

// Controller link
Controller controller(E_CONTROLLER_MASTER);

MotorGroup intake({Motor(11, E_MOTOR_GEAR_200),
				   Motor(-20, E_MOTOR_GEAR_200)});

// a wings
ADIDigitalOut wings('A');
// b pto
ADIDigitalOut pto('B');
// c hang
ADIDigitalOut hang('C');

// Drivetrain motors
Motor leftMotor1(1);
Motor leftMotor2(2);
Motor leftMotor3(3);
Motor leftMotor4(-7);
Motor rightMotor1(-4);
Motor rightMotor2(-5);
Motor rightMotor3(-6);
Motor rightMotor4(8);

// Drivetrain motor groups
MotorGroup rightSideMotors({leftMotor1, leftMotor2, leftMotor3, leftMotor4});
MotorGroup leftSideMotors({rightMotor1, rightMotor2, rightMotor3, rightMotor4});

// Inertial sensor
IMU inertial(18);

// Rotation sensor
// pros::Rotation horiSensor(10);
// lemlib::TrackingWheel horizontal(&horiSensor, lemlib::Omniwheel::NEW_275, 3);

// Initialize the LemLib drivetrain settings
lemlib::Drivetrain drivetrain(
	&leftSideMotors,			// left side motors
	&rightSideMotors,			// right side motors
	11,						// track width in inches
	lemlib::Omniwheel::NEW_325, // wheel diameter
	450,						// rpm
	8							// chase power (probably for pure pursuit)
);

// Set up linear movement settings (forward/backward)
lemlib::ControllerSettings linearMovementSettings(
	20,	 // P
	0,	 // I
	30,	 // D
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
	// chassis.calibrate();
	
	chassis.setPose(36, 57, 180);

	chassis.turnTo(-25, 5, 700, true);
	chassis.moveToPoint(-25, 5, 2000, true);


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
	pros::Task drivetrainTask(DrivetrainTask, (void *)"", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "drivetrain");

	pros::Task mechanismsTask(MechanismsTask, (void *)"", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "mechanisms");

	while (true)
	{
		delay(20);
	}
}
