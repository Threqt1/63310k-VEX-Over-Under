#include "main.h"

/**
 * Global Device Initialization
 */
Controller controller(ControllerId::master);
std::shared_ptr<OdomChassisController> chassis =
	ChassisControllerBuilder()
		.withMotors({-2, -4}, {1, 3})
		.withGains(
			{0.001, 0, 0}, // Distance controller gains
			{0.0033, 0, 0.00013},
			// {0.006, 0.001, 0.0002}, // Turn controller gains
			{0, 0, 0} // Angle controller gains (helps drive straight)
			)
		.withDimensions(AbstractMotor::gearset::green, {{4_in, 8_in}, imev5GreenTPR})
		.withOdometry()
		.buildOdometry();
std::shared_ptr<SkidSteerModel>
	drivetrain = std::dynamic_pointer_cast<SkidSteerModel>(chassis->getModel());
Motor intake(10, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
MotorGroup hang(
	{Motor(7, false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees),
	 Motor(8, false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees)});
MotorGroup catapult({Motor(6, false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees), Motor(9, true, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees)});
pros::ADIDigitalOut pistonA('A');
pros::ADIDigitalOut pistonB('H');
// MotorGroup lift(
// 	{Motor(5, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees),
// 	 Motor(8, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees),
// 	 Motor(20, false, AbstractMotor::gearset::green,		 AbstractMotor::encoderUnits::degrees)});
// Motor arm(10, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
// pros::ADIDigitalOut piston('A');

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
	catapult.setBrakeMode(AbstractMotor::brakeMode::hold);
	hang.setBrakeMode(AbstractMotor::brakeMode::hold);
	intake.setBrakeMode(AbstractMotor::brakeMode::coast);
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

// 218_deg is 180
void autonomous()
{
	chassis->setState({0_in, 0_in, 0_deg});

	chassis->turnAngle(218_deg);
	drivetrain->driveVectorVoltage(12000, 0);

	// intake.moveVelocity(-600);
	// drivetrain->driveVectorVoltage(-4000, 0);
	// pros::delay(500);
	// drivetrain->stop();
	// chassis->setMaxVelocity(140);
	// chassis->moveDistance(3.9_ft);
	// chassis->setMaxVelocity(75);
	// chassis->turnAngle(100_deg);
	// drivetrain->driveVectorVoltage(1000, 0);
	// pros::delay(1000);
	// drivetrain->stop();
	// intake.moveVelocity(600);
	// pros::delay(100);
	// intake.moveVelocity(0);
	// chassis->setMaxVelocity(140);
	// chassis->moveDistance(-6_in);
	// intake.moveVelocity(-600);
	// chassis->setMaxVelocity(75);
	// chassis->turnAngle(-235_deg);
	// chassis->setMaxVelocity(140);
	// chassis->moveDistance(1.8_ft);
	// chassis->setMaxVelocity(75);
	// chassis->turnAngle(195_deg);
	// intake.moveVelocity(0);
	// piston.set_value(true);
	// chassis->setMaxVelocity(75);
	// chassis->turnAngle(15_deg);
	// drivetrain->driveVectorVoltage(10000, 0);
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
	chassis->stop();
	pros::Task drivetrainTask(DrivetrainLoop, (void *)"", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "drivetrain");

	pros::Task mechanismsTask(MechanismsLoop, (void *)"", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "mechanisms");

	while (true)
	{
		pros::delay(20);
	}
}
