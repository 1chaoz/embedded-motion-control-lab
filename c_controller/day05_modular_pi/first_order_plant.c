#include "first_order_plant.h"

// 初始化函数
void FirstOrder_Init(FirstOrderPlant *plant,
                     float tau,
                     float ts,
                     float output)
{
    plant->tau = tau;
    plant->ts = ts;
    plant->output = output;
}

// 复位函数
void FirstOrder_Reset(FirstOrderPlant *plant)
{
    plant->output = 0.0f;
}

// 状态更新函数
float FirstOrder_Update(FirstOrderPlant *plant,
                        float input)
{
    float output_next;

    output_next = plant->output
                + plant->ts / plant->tau
                * (input - plant->output);

    plant->output = output_next;

    return output_next;
}