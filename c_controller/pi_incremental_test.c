#include <stdio.h>

// Incremental PI controller parameters and state
typedef struct
{
    float kp;
    float ki;
    float ts;
    float error_last;
    float output_last;
} PI_Incremental;

float PI_Incremental_Calculate(PI_Incremental *controller,
                               float target, float actual)
{
    float error = target - actual;
    float delta_output =
        controller->kp * (error - controller->error_last)
        + controller->ki * controller->ts * error;
    float output = controller->output_last + delta_output;

    // Limit output to [0, 100].
    if (output > 100.0f)
    {
        output = 100.0f;
    }
    else if (output < 0.0f)
    {
        output = 0.0f;
    }

    // Save the limited output and current error.
    controller->output_last = output;
    controller->error_last = error;

    return output;
}

int main(void)
{
    PI_Incremental pi = {2.0f, 1.0f, 0.01f, 0.0f, 0.0f};
    float target = 1000.0f;
    float actual[5] = {800.0f, 850.0f, 900.0f, 880.0f, 910.0f};

    for (int i = 0; i < 5; i++)
    {
        float output = PI_Incremental_Calculate(&pi, target, actual[i]);
        printf("Step %d: Error=%.2f, Output=%.2f\n",
               i + 1, pi.error_last, output);
    }

    return 0;
}
