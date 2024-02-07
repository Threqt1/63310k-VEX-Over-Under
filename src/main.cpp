#include "main.h"

// cata 7 (5.5) 8 (green) (a and b)
// intake r1 r2 10 (5.5)
// wings l1 l2 toggle on X between horiz and vert
// hang is up/down
// drive 600 rpm 333 speed
// cata 100% 5.5 is 200rpm

// Controller link
Controller controller(E_CONTROLLER_MASTER);

MotorGroup catapult(
	{Motor(-7, E_MOTOR_GEAR_200),
	 Motor(8, E_MOTOR_GEAR_GREEN)});

Motor intake(19, E_MOTOR_GEAR_200);

ADIDigitalOut verticalWings('C');
ADIDigitalOut horizontalWings('B');
ADIDigitalOut hang('A');

// Drivetrain motors
Motor leftMotor1(1);
Motor leftMotor2(2);
Motor leftMotor3(3);
Motor rightMotor1(-4);
Motor rightMotor2(-5);
Motor rightMotor3(-6);

// Drivetrain motor groups
MotorGroup rightSideMotors({leftMotor1, leftMotor2, leftMotor3});
MotorGroup leftSideMotors({rightMotor1, rightMotor2, rightMotor3});

// Inertial sensor
IMU inertial(12);

// Rotation sensor
// pros::Rotation horiSensor(10);
// lemlib::TrackingWheel horizontal(&horiSensor, lemlib::Omniwheel::NEW_275, 3);

// Initialize the LemLib drivetrain settings
lemlib::Drivetrain drivetrain(
	&leftSideMotors,			// left side motors
	&rightSideMotors,			// right side motors
	10.6,						// track width in inches
	lemlib::Omniwheel::NEW_325, // wheel diameter
	360,						// rpm
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
							 //  catapult.set_brake_modes(E_MOTOR_BRAKE_HOLD);
							 // leftSideMotors.set_voltage_limit(5000);
							 // rightSideMotors.set_voltage_limit(5000);

	// // thread to for brain screen and position logging
	pros::Task screenTask([&]()
						  {
	    lemlib::Pose pose(0, 0, 0);
	    while (true) {
	        // print robot location to the brain screen
	        pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
	        pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
	        pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
	        // log position telemetry
	        lemlib::telemetrySink()->info("Chassis pose: {}", chassis.getPose());
	        // delay to save resources
	        pros::delay(50);
	    } });
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.51
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

void autonomous()
{
	chassis.setPose(0, 0, 0);
	intake.move_voltage(12000);
	pros::delay(300);
	chassis.moveToPose(0, 10, 0, 800);
	chassis.moveToPose(0, 10, 30, 800);
	intake.move_voltage(12000);
	pros::delay(500);
	intake.move_voltage(0);
	chassis.moveToPose(0, 10, 0, 800);
	verticalWings.set_value(true);
	pros::delay(500);
	chassis.moveToPose(0, 5, 0, 800, {false});
	chassis.turnTo(-30, 30, 800);
	chassis.turnTo(20, -30, 800);
	verticalWings.set_value(false);
	chassis.moveToPoint(16, -30, 2000);
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
