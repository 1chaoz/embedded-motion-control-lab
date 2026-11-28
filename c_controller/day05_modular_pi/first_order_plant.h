
#ifndef FIRST_ORDER_PLANT_H
#define FIRST_ORDER_PLANT_H

/**
 * @brief 一阶惯性被控对象结构体
 *
 * 连续模型：G(s) = 1 / (tau*s + 1)
 * 模型静态增益为1
 */
typedef struct
{
    float tau;      // 时间常数，单位：s
    float ts;       // 仿真步长，单位：s
    float output;   // 当前系统输出状态
} FirstOrderPlant;


/**
 * @brief 初始化一阶被控对象
 *
 * @param[out] plant 被控对象结构体指针
 * @param[in] tau 系统时间常数，单位：s
 * @param[in] ts 仿真步长，单位：s
 * @param[in] output 系统初始输出值
 *
 * @return 无返回值
 *
 * @pre plant必须指向有效的结构体
 * @pre tau和ts必须大于0
 * @note 支持设置非零初始状态
 * @warning 前向欧拉模型渐近稳定要求0 < ts/tau < 2
 */
void FirstOrder_Init(FirstOrderPlant *plant,
                     float tau,
                     float ts,
                     float output);


/**
 * @brief 复位一阶被控对象
 *
 * @param[in,out] plant 被控对象结构体指针
 *
 * @return 无返回值
 *
 * @pre 被控对象已完成初始化
 * @note 将系统输出清零，保留tau和ts
 * @note 不恢复Init时传入的非零初始输出
 */
void FirstOrder_Reset(FirstOrderPlant *plant);


/**
 * @brief 使用前向欧拉法更新系统状态
 *
 * @param[in,out] plant 被控对象结构体指针
 * @param[in] input 当前控制输入u[k]
 *
 * @return float类型，下一时刻系统输出y[k+1]
 *
 * @pre 被控对象已完成初始化
 *
 * @note 每次调用向前推进一个仿真步长
 * @note 函数会更新plant->output
 * @note 离散模型：
 *       y[k+1] = y[k] + ts/tau * (u[k] - y[k])
 */
float FirstOrder_Update(FirstOrderPlant *plant,
                        float input);

#endif
