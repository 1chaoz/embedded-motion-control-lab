#include <stdio.h>

// Positional PI controller parameters and state
typedef struct
{
    float kp;
    float ki;
    float ts;
    float integral;
} PI_Position;

// Incremental PI controller parameters and state
typedef struct
{
    float kp;
    float ki;
    float ts;
    float error_last;
    float output_last;
} PI_Incremental;

// Positional PI, without output limiting or anti-windup
float PI_Calculate(PI_Position *controller, float target, float actual)
{
    float error = target - actual;
    controller->integral += error * controller->ts;

    float output = controller->kp * error
                 + controller->ki * controller->integral;
    return output;
}

// Incremental PI, without output limiting
float PI_Incremental_Calculate(PI_Incremental *controller,
                               float target, float actual)
{
    float error = target - actual;
    float delta_output =
        controller->kp * (error - controller->error_last)
        + controller->ki * controller->ts * error;
    float output = controller->output_last + delta_output;

    controller->output_last = output;
    controller->error_last = error;

    return output;
}

int main(void)
{
    PI_Position position = {2.0f, 1.0f, 0.01f, 0.0f};
    PI_Incremental incremental = {2.0f, 1.0f, 0.01f, 0.0f, 0.0f};
    float target = 1000.0f;
    float actual[5] = {800.0f, 850.0f, 900.0f, 880.0f, 910.0f};

    for (int i = 0; i < 5; i++)
    {
        float outputPosition = PI_Calculate(&position, target, actual[i]);
        float outputIncremental =
            PI_Incremental_Calculate(&incremental, target, actual[i]);

        printf("Step %d: Position=%.2f, Incremental=%.2f\n",
               i + 1, outputPosition, outputIncremental);
    }

    return 0;
}
