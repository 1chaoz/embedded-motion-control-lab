#include <stdio.h>
#include "pi_controller.h"
#include "first_order_plant.h"

/**
 * @brief 一阶系统闭环PI控制参数对比实验
 *
 * 实验目的：
 * 比较不同Kp、Ki对闭环系统响应的影响。
 *
 * 实验条件：
 * 时间常数：0.5s
 * 采样周期：0.01s
 * 目标值：1.0
 * 仿真时间：10s
 *
 * 当前版本不包含输出限幅和抗积分饱和。
 */
int main(void)
{
    // 1. 设置实验参数，每行依次为Kp、Ki
    float parameters[3][2] = {
        {1.0f, 1.0f},
        {2.0f, 1.0f},
        {2.0f, 4.0f}
    };

    float target = 1.0f;

    PI_Position pi;
    FirstOrderPlant plant;

    // 2. 遍历三组PI参数，分别进行独立实验
    for (int j = 0; j < 3; j++)
    {
        // 每组实验重新初始化，避免历史状态影响实验结果
        PI_Init(&pi, parameters[j][0],
                parameters[j][1], 0.01f);

        FirstOrder_Init(&plant, 0.5f, 0.01f, 0.0f);

        // 打印控制器实际使用的参数，便于检查参数传递
        printf("\nGroup %d: Kp=%.2f, Ki=%.2f\n",
               j + 1, pi.kp, pi.ki);

        // 3. 闭环仿真：1000个采样周期，共10s
        for (int i = 0; i < 1000; i++)
        {
            // 读取当前反馈值 y[k]
            float actual = plant.output;

            // 计算当前控制输入 u[k]
            float control = PI_Calculate(&pi, target, actual);

            // 更新被控对象，得到下一时刻输出 y[k+1]
            float actual_new = FirstOrder_Update(&plant, control);

            // 4. 每隔1s打印一次数据，不影响控制计算频率
            if ((i + 1) % 100 == 0)
            {
                float time = (i + 1) * plant.ts;

                printf("Time=%.2f, Control=%.6f, Output=%.6f\n",
                       time, control, actual_new);
            }
        }
    }

    return 0;
}