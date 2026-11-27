#include <stdio.h>

// 定义 PI 控制器结构体
typedef struct
{
    float kp;
    float ki;
    float ts;
    float integral;
} PI_Position;


// 定义 PI 控制器计算函数
float PI_Calculate(PI_Position *controller,
                   float target,
                   float actual)
{
    float error;
    float output;

    // 1. 计算误差
    error = target - actual;

    // 2. 更新积分状态
    controller->integral += error * controller->ts;

    // 3. 计算控制输出
    output = controller->kp * error
           + controller->ki * controller->integral;

    return output;
}


// 定义一阶系统结构体
typedef struct
{
    float tau;
    float ts;
    float output;
} FirstOrderPlant;


// 定义被控对象计算函数
float FirstOrder_Update(FirstOrderPlant *plant,
                        float input)
{
    float output_next;

    // 计算下一时刻输出
    output_next = plant->output
                + plant->ts / plant->tau
                * (input - plant->output);

    // TODO 1：更新结构体中的系统输出
    plant->output = output_next;

    // TODO 2：返回新的系统输出
    return output_next;

}

int main(void)
{
    
    // 1.实验所用 PI 值
    float parameters[3][2] = {
        {1.0f, 1.0f},
        {2.0f, 1.0f},
        {2.0f, 4.0f}
    };

    // 2. 设置目标值
    float target = 1.0f;

    // 3. 外层循环：切换控制参数
    for (int j = 0; j < 3; j++)
    {
        // TODO 1：初始化 PI 控制器
        // 从 parameters 数组读取 Kp 和 Ki
        PI_Position pi = {
            parameters[j][0],
            parameters[j][1],
            0.01f,
            0.0f
        };
    
        // TODO 2: 初始化一阶被控对象
        FirstOrderPlant plant = {
            0.5f, 0.01f, 0.0f
        };
    
        printf("\nGroup %d: Kp=%.2f, Ki=%.2f\n",
            j + 1, parameters[j][0], parameters[j][1]);
            
            
        // 4. 闭环运行1000次
        for (int i = 0; i < 1000; i++)
        {
            // TODO 3：读取当前实际输出
            float actual = plant.output;
    
            // TODO 4：调用 PI 控制器，计算控制输出
            float control = PI_Calculate(&pi, target, actual);
    
            // TODO 5：调用被控对象，更新系统输出
            float actualNew = FirstOrder_Update(&plant, control);
            
            //float error = target - actual;
            // TODO 6：打印当前误差、控制输出和系统输出
            if ((i + 1) % 100 == 0)
            {
                float time = (i + 1) * plant.ts;
                // 打印数据
                printf("Time=%.2f, Control=%.6f, Output=%.6f\n",
                   time, control, actualNew);
            }
            
        }
    }



    return 0;
}
