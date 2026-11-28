
#ifndef PI_CONTROLLER_H
#define PI_CONTROLLER_H

/**
 * @brief 位置式PI控制器结构体
 */
typedef struct
{
    float kp;        // 比例系数
    float ki;        // 积分系数
    float ts;        // 采样周期，单位：s
    float integral;  // 当前累计积分状态
} PI_Position;


/**
 * @brief 初始化位置式PI控制器
 *
 * @param[out] controller PI控制器结构体指针
 * @param[in] kp 比例系数
 * @param[in] ki 积分系数
 * @param[in] ts 采样周期，单位：s
 *
 * @return 无返回值
 *
 * @pre controller必须指向有效的结构体，ts必须大于0
 * @note 设置控制参数，同时将积分状态清零
 */
void PI_Init(PI_Position *controller,
             float kp,
             float ki,
             float ts);


/**
 * @brief 复位PI控制器的历史状态
 *
 * @param[in,out] controller PI控制器结构体指针
 *
 * @return 无返回值
 *
 * @note 仅清零积分状态，不修改kp、ki和ts
 * @pre 控制器已完成初始化
 */
void PI_Reset(PI_Position *controller);


/**
 * @brief 执行一次位置式PI控制计算
 *
 * @param[in,out] controller PI控制器结构体指针
 * @param[in] target 系统目标值
 * @param[in] actual 系统当前反馈值
 *
 * @return float类型，本次计算得到的控制输出
 *
 * @pre 控制器已完成初始化
 *
 * @note 每次调用都会更新内部积分状态
 * @note target与actual必须使用相同单位
 * @note 当前版本不包含输出限幅和抗积分饱和
 * @note 每个采样周期应调用一次
 */
float PI_Calculate(PI_Position *controller,
                   float target,
                   float actual);

#endif
