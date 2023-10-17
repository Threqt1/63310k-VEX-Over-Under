/*
pid_movements.cpp declares functions that utilize PID via an
odometry feedback loop in order to move much more accurately.
*/

#include "main.h"

/**
 * pollOdometryState is a utility function to
 * poll the current odometry state through the
 * appropriate Mutex operations
 */
OdometryState pollOdometryState(MutexOdometryState *state)
{
    OdometryState returnState{};

    state->mutex.take();

    OdometryState currentState = state->state;
    returnState.angle = currentState.angle;
    returnState.x = currentState.x;
    returnState.y = currentState.y;

    state->mutex.give();

    return returnState;
}

void resetOdometryState(MutexOdometryState *state)
{
    state->mutex.take();

    state->state = {
        0_deg,
        0_in,
        0_in};

    state->mutex.give();
}

double MAX_FORWARD_SPEED = 12000;
void moveForwardFor(QLength length, MutexOdometryState *state)
{
    double kP = 0;
    double kI = 0;
    double kD = 0;

    OdometryState currentState = pollOdometryState(state);
    double forwardAmount = length.convert(inch);
    double currentLocation = currentState.y.convert(inch);
    double wantedLocation = currentLocation + forwardAmount;
    double forwardError = std::abs(forwardAmount);
    double currentError = (wantedLocation - currentLocation) / forwardError;
    double lastError = currentError;
    double totalError = 0;
    double currentSpeed = wantedLocation < currentLocation ? -MAX_FORWARD_SPEED : MAX_FORWARD_SPEED;

    while (std::abs(currentError) > .1)
    {
        currentState = pollOdometryState(state);
        currentLocation = currentState.y.convert(inch);
        currentError = (wantedLocation - currentLocation) / forwardError;
        totalError += currentError;
        double errorDiff = currentError - lastError;
        currentSpeed = (currentError * kP + totalError * kI + errorDiff * kD) * MAX_FORWARD_SPEED;
        if (currentSpeed > MAX_FORWARD_SPEED)
            currentSpeed = MAX_FORWARD_SPEED;
        else if (currentSpeed < -MAX_FORWARD_SPEED)
            currentSpeed = -MAX_FORWARD_SPEED;
        lastError = currentError;
        drivetrain->driveVectorVoltage(currentSpeed, 0);

        pros::delay(20);
    }
    drivetrain->stop();
    resetOdometryState(state);
}

double constrainAngle(double angle)
{
    if (angle < 0)
        angle += 360;
    if (angle >= 360)
        angle -= 360;
    return angle;
}

double findError(double wanted, double current)
{
    double errorRight = 0;
    double errorLeft = 0;
    if (current < wanted)
    {
        errorRight = wanted - current;
        errorLeft = 360 - errorRight;
    }
    else
    {
        errorLeft = current - wanted;
        errorRight = 360 - errorLeft;
    }
    if (errorLeft < errorRight)
    {
        return -(errorLeft);
    }
    else
    {
        return (errorRight);
    }
}

double MAX_TURN_SPEED = 12000;
void turnFor(QAngle targetAngle, MutexOdometryState *state)
{
    double kP = .000047;
    double kI = .00000035;

    OdometryState currentState = pollOdometryState(state);
    double turnAmount = targetAngle.convert(degree);
    double currentAngle = constrainAngle(currentState.angle.convert(degree));
    double wantedAngle = constrainAngle(currentAngle + turnAmount);
    double turnError = std::abs(findError(wantedAngle, currentAngle));
    double currentError = findError(wantedAngle, currentAngle) / turnError;
    double totalError = 0;
    double currentSpeed = currentError < 0 ? -MAX_TURN_SPEED : MAX_TURN_SPEED;

    while (abs(currentError) > .1)
    {
        currentState = pollOdometryState(state);
        currentAngle = constrainAngle(currentState.angle.convert(degree));
        currentError = findError(wantedAngle, currentAngle) / turnError;
        totalError += currentError;
        currentSpeed = (currentError * kP + totalError * kI) * MAX_TURN_SPEED;
        if (currentSpeed > MAX_TURN_SPEED)
            currentSpeed = MAX_TURN_SPEED;
        else if (currentSpeed < -MAX_TURN_SPEED)
            currentSpeed = -MAX_TURN_SPEED;
        drivetrain->driveVectorVoltage(0, currentSpeed);
        pros::delay(20);
    }
    drivetrain->stop();
    resetOdometryState(state);
}