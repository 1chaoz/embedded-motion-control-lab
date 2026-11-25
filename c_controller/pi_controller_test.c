
#include <stdio.h>

// 1. 定义 PI 控制器结构体
typedef struct
{
    float kp;
    float ki;
    float ts;
    float integral;
} PI_Controller;


// 2. PI 控制器计算函数
float PI_Calculate(PI_Controller *controller,
                   float target,
                   float actual)
{
    float error;
    float integral_trial;
    float output_trial;
    float output;

    // 计算误差
    error = target - actual;

    // 计算试探积分
    integral_trial = controller->integral
                   + error * controller->ts;

    // 计算试探输出
    output_trial = controller->kp * error
                 + controller->ki * integral_trial;

    // 条件积分抗饱和
    if ((output_trial > 100 && error > 0) ||
        (output_trial < 0 && error < 0))
    {
        // 不更新积分，保留原来的积分状态
    }
    else
    {
        // 接受本次积分更新
        controller->integral = integral_trial;
    }

    // 计算最终输出
    output = controller->kp * error
           + controller->ki * controller->integral;

    // 输出限幅
    if (output > 100)
    {
        output = 100;
    }
    else if (output < 0)
    {
        output = 0;
    }

    return output;
}


// 3. 主函数：进行三组测试
int main(void)
{
    float output;

    // 测试1：正向饱和
    PI_Controller pi1 = {2.0f, 1.0f, 1.0f, 40.0f};

    output = PI_Calculate(&pi1, 40.0f, 0.0f);

    printf("Test 1: Positive Saturation\n");
    printf("Integral = %.2f, Output = %.2f\n\n",
           pi1.integral, output);


    // 测试2：负向饱和
    PI_Controller pi2 = {2.0f, 1.0f, 1.0f, -40.0f};

    output = PI_Calculate(&pi2, 0.0f, 40.0f);

    printf("Test 2: Negative Saturation\n");
    printf("Integral = %.2f, Output = %.2f\n\n",
           pi2.integral, output);


    // 测试3：误差反向，积分逐渐释放
    PI_Controller pi3 = {2.0f, 1.0f, 1.0f, 150.0f};

    printf("Test 3: Integral Release\n");

    for (int i = 0; i < 4; i++)
    {
        output = PI_Calculate(&pi3, 0.0f, 10.0f);

        printf("Step %d: Integral = %.2f, Output = %.2f\n",
               i + 1, pi3.integral, output);
    }

    return 0;
}
