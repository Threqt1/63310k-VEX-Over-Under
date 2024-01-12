#include "main.h"

// Controller link
Controller controller(E_CONTROLLER_MASTER);

MotorGroup catapultIntake(
	{Motor(7, E_MOTOR_GEAR_RED, true),
	 Motor(8, E_MOTOR_GEAR_RED, false)});

ADIDigitalOut sideHang('A');
ADIDigitalOut wings('B');
ADIDigitalOut hang('C');

// Drivetrain motors
Motor leftMotor1(-1, E_MOTOR_GEARSET_18);
Motor leftMotor2(-2, E_MOTOR_GEARSET_18);
Motor leftMotor3(-3, E_MOTOR_GEARSET_18);
Motor rightMotor1(4, E_MOTOR_GEARSET_18);
Motor rightMotor2(5, E_MOTOR_GEARSET_18);
Motor rightMotor3(6, E_MOTOR_GEARSET_18);

// Drivetrain motor groups
MotorGroup leftSideMotors({leftMotor1, leftMotor2, leftMotor3});
MotorGroup rightSideMotors({rightMotor1, rightMotor2, rightMotor3});

// Inertial sensor
IMU inertial(11);

// Rotation sensor
pros::Rotation horiSensor(10);
lemlib::TrackingWheel horizontal(&horiSensor, lemlib::Omniwheel::NEW_275, 3);

// Initialize the LemLib drivetrain settings
lemlib::Drivetrain drivetrain(
	&leftSideMotors,			// left side motors
	&rightSideMotors,			// right side motors
	12.5,						// track width in inches
	lemlib::Omniwheel::NEW_325, // wheel diameter
	333,						// rpm
	8							// chase power (probably for pure pursuit)
);

// Set up linear movement settings (forward/backward)
lemlib::ControllerSettings linearMovementSettings(
	10,	 // P
	0,	 // I
	30,	 // D
	3,	 // antiwindup
	1,	 // small error (use for tuning settling)
	100, // small error timeout
	3,	 // large error (use to quit movement if stuck)
	500, // large error timeout
	20	 // maximum acceleration (slew)
);

// Set up angular movement settings (turning)
lemlib::ControllerSettings angularMovementSettings(
	2,	 // P
	0,	 // I
	10,	 // D
	3,	 // antiwindup
	1,	 // small error (use for tuning settling)
	100, // small error timeout
	3,	 // large error (use to quit movement if stuck)
	500, // large error timeout
	20	 // maximum acceleration (slew)
);

// Set up odometry sensors
lemlib::OdomSensors odometrySensors(
	nullptr,	 // vertical tracking wheel 1
	nullptr,	 // vertical tracking wheel 2
	nullptr,//&horizontal, // horizontal tracking wheel 1
	nullptr,	 // horizontal tracking wheel 2
	&inertial	 // inertial sensor
);

// Configure the lemlib chassis
lemlib::Chassis chassis(drivetrain, linearMovementSettings, angularMovementSettings, odometrySensors);

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
	pros::lcd::initialize(); // initialize brain screen
	chassis.calibrate();	 // calibrate sensors

	// // thread to for brain screen and position logging
	// pros::Task screenTask([&]()
	// 					  {
	//     lemlib::Pose pose(0, 0, 0);
	//     while (true) {
	//         // print robot location to the brain screen
	//         pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
	//         pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
	//         pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
	//         // log position telemetry
	//         lemlib::telemetrySink()->info("Chassis pose: {}", chassis.getPose());
	//         // delay to save resources
	//         pros::delay(50);
	//     } });
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

ASSET(path47_txt);
ASSET(path47b_txt);
ASSET(path52b_txt);
ASSET(path82c_txt);
ASSET(path63d_txt);
ASSET(path66e_txt);
ASSET(path91f_txt);

void autonomous()
{
	//6 ball thats def 5
	// chassis.setPose(-3, 58, 90);
	// chassis.moveToPoint(0, 58, 2000);
	// catapultIntake.move_voltage(12000);
	// delay(250);
	// catapultIntake.move_voltage(-12000);
	// chassis.moveToPoint(-27, 57, 1200, false);
	// chassis.turnTo(-100, 56, 800, true);
	// chassis.follow(path52b_txt, 11, 10000, true, false);
	// catapultIntake.move_voltage(12000);
	// delay(350);
	// catapultIntake.brake();
	// sideHang.set_value(true);
	// delay(200);
	// chassis.turnTo(-200, 65, 1000, false);
	// delay(650);
	// sideHang.set_value(false);
	// chassis.turnTo(-63, 20, 700, false);
	// chassis.moveToPoint(-65, 20, 1000, false);
	// chassis.moveToPoint(-63, 45, 600, true);
	// chassis.turnTo(-40, 45, 800);

	// catapultIntake.move_voltage(-12000);
	
	// chassis.follow(path82c_txt, 11, 1500, true, false);
	// delay(100);
	// chassis.turnTo(-50, 5, 1500, true);
	// delay(500);
	// catapultIntake.move_voltage(12000);
	// delay(350);
	// catapultIntake.move_voltage(-12000);
	// chassis.moveToPoint(1, 2, 1500, true);
	// delay(100);
	// chassis.turnTo(-50, 5, 2000, true);
	// delay(500);
	// wings.set_value(true);
	// chassis.moveToPoint(-50, 0, 1000, true);
	// chassis.moveToPoint(-30, 0, 1000, true);


	//skills
	chassis.setPose(-35, -62, 90); 
	chassis.follow(path63d_txt, 11, 1200, false, false);
	chassis.moveToPoint(-61, -28, 500, false);
	chassis.moveToPoint(-63, -43, 700, true);
	chassis.turnTo(45, 0, 900, true);
	chassis.moveToPoint(-67, -45, 1000, false);
	catapultIntake.move_voltage(12000);
	// delay(26000);

	chassis.moveToPoint(-55, -50, 1500, true);
	chassis.turnTo(-30, -70, 1300, false);

	catapultIntake.move_voltage(10000);
	chassis.follow(path66e_txt, 15, 150000, false, false);
	catapultIntake.brake();

	chassis.moveToPoint(67, -20, 1000, false, 100);
	chassis.moveToPoint(64, -40, 1000, true);
	chassis.moveToPoint(64, -20, 700, false);

	chassis.moveToPoint(35, -36, 1500, true, 80);
	chassis.moveToPoint(12, -33, 1500, true);

	chassis.moveToPoint(14.5, -17, 1500, false);
	wings.set_value(true);
	chassis.moveToPoint(49, -4, 2000, true, 80);
	wings.set_value(false);

	chassis.moveToPoint(14.5, -17, 1500, false);
	chassis.moveToPoint(14.5, 17, 1500, false);
	wings.set_value(true);
	chassis.moveToPoint(49, 5, 3000, true, 80);
	wings.set_value(false);

	chassis.moveToPoint(14.5, 17, 1500, false);
	wings.set_value(true);
	chassis.moveToPoint(49, 0, 3000, true, 80);
	wings.set_value(false);
	chassis.moveToPoint(14.5, 17, 1500, false);
	chassis.turnTo(25, 25, 1000, false);

	chassis.follow(path91f_txt, 15, 4000, false, false);
	chassis.moveToPoint(65, 20, 1000, false, 80);


}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol()
{
	pros::Task drivetrainTask(DrivetrainTask, (void *)"", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "drivetrain");

	pros::Task mechanismsTask(MechanismsTask, (void *)"", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "mechanisms");

	while (true)
	{
		delay(20);
	}
}
