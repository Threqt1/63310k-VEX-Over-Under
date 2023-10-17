#include "main.h"

/**
 * Global Device Initialization
 */
Controller controller(ControllerId::master);
std::shared_ptr<ChassisController> chassis =
	ChassisControllerBuilder()
		.withMotors({-2, -4},
					{1, 3})
		.withDimensions(AbstractMotor::gearset::green, {{4_in, 13_in}, imev5GreenTPR})
		.build();
std::shared_ptr<SkidSteerModel> drivetrain = std::dynamic_pointer_cast<SkidSteerModel>(chassis->getModel());
MotorGroup lift(
	{Motor(5, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees),
	 Motor(8, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees),
	 Motor(20, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees)});

  	pros::ADIDigitalOut piston ('A');
	pros::Imu inertial(6);
	okapi::IntegratedEncoder leftEncoder(2, true);
	okapi::IntegratedEncoder rightEncoder(1);

	 

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
	pros::lcd::initialize();

	inertial.reset(true);
    inertial.set_heading(0);
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
void autonomous() {

	MutexOdometryState state{};
    state.state = {
        0_deg,
        0_in,
        0_in};

    // Initialize a new odometry task
    pros::Task odometryTask(OdometryLoop, (void *)&state, TASK_PRIORITY_DEFAULT + 1, TASK_STACK_DEPTH_DEFAULT, "Odometry");

    // Wait some time for the task to initialize
    pros::delay(100);

	moveForwardFor(6_in, &state);

    // Close the task after all autonomous functions are run
    odometryTask.remove();

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
	pros::Task drivetrainTask(DrivetrainLoop, (void *)"", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "drivetrain");

	pros::Task mechanismsTask(MechanismsLoop, (void *)"", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "mechanisms");

	while (true)
	{
		pros::delay(20);
	}
}
