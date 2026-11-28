#include "pi_controller.h"



// 初始化函数
void PI_Init(PI_Position *controller,
             float kp,
             float ki,
             float ts)
{
    controller->kp = kp;
    controller->ki = ki;
    controller->ts = ts;
    controller->integral = 0.0f;
}


// 复位函数
void PI_Reset(PI_Position *controller)
{
    controller->integral = 0.0f;
}



// 控制计算函数
float PI_Calculate(PI_Position *controller,
                   float target,
                   float actual)
{
    float error;
    float output;

    error = target - actual;

    controller->integral += error * controller->ts;

    output = controller->kp * error
           + controller->ki * controller->integral;

    return output;
}