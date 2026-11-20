# Embedded Motion Control Lab

**Embedded Motion Control | MATLAB/Simulink | C | STM32**

A practical learning and engineering project focused on control algorithms, embedded software implementation, and experimental validation.

一个围绕运动控制算法、嵌入式软件实现与实验验证开展的学习和工程实践项目。

## 1. Project Overview

This project aims to build a complete workflow from control system modeling and simulation to embedded implementation.

The main objective is to understand how classical control algorithms can be designed, implemented in C, and deployed on STM32 microcontrollers.

本项目计划建立从控制系统建模、仿真分析到嵌入式实现的完整技术流程。

## 2. Project Objectives

- Understand classical control theory.
- Build control system models using MATLAB/Simulink.
- Design and analyze PI/PID controllers.
- Implement digital controllers using C.
- Deploy control algorithms on STM32.
- Validate control performance through simulation and experiments.

## 3. Technology Stack

| Technology   | Application                               |
| ------------ | ----------------------------------------- |
| MATLAB       | Numerical analysis and data processing    |
| Simulink     | Control system modeling and simulation    |
| C            | Embedded control algorithm implementation |
| STM32        | Embedded control platform                 |
| Git / GitHub | Version control and project management    |

## 4. Repository Structure

```
embedded-motion-control-lab/
├── README.md
├── matlab/
├── c_controller/
├── stm32/
├── docs/
└── images/
```

## 5. Development Roadmap

### Phase 1: Control System Modeling and Simulation

- First-order system modeling
- PI/PID controller design
- Closed-loop response analysis
- Control parameter tuning

### Phase 2: Digital Control Algorithm Implementation

- Continuous-to-discrete conversion
- Discrete PID algorithm
- Integral anti-windup
- Output limitation
- C implementation and testing

### Phase 3: STM32 Implementation

- Timer and interrupt configuration
- PWM generation
- UART communication
- Embedded control task implementation

### Phase 4: Testing and Validation

- Simulation and C implementation comparison
- Embedded system testing
- Performance evaluation
- Technical documentation

## 6. Current Progress

**Status: In Progress**

Completed:

- First-order control system modeling
- PI controller simulation
- Proportional gain and integral gain analysis

Planned:

- Discrete PID implementation
- C language controller development
- STM32 deployment and validation

## 7. Learning Notes and Experiment Reports

Detailed learning notes, simulation results, and experiment reports will be maintained in the `docs/` directory.

## 8. Day 01 — PI Controller Experiment

### Learning Notes
- [Control System Fundamentals](docs/learning-notes/day01_control_basics.md)

### Experiment Report
- [PI Controller Performance Analysis](docs/experiment-reports/experiment_01_pi_analysis.md)

### MATLAB Files
- `matlab/PI_Control_Model.slx` — Simulink model
- `matlab/run_pi_once.m` — Single simulation
- `matlab/run_pi_sweep.m` — Automated parameter sweep
- `matlab/analyze_pi_results.m` — Performance analysis

### Experimental Results
- [Performance Metrics (CSV)](matlab/results/day01/pi_performance_metrics.csv)
- [Kp Comparison](images/day01/kp_comparison.png)
- [Ki Comparison](images/day01/ki_comparison.png)

## 9. Author

GitHub: [1chaoz](https://github.com/1chaoz)

**Note:** This repository is an ongoing engineering learning project. Features and results will be updated as development progresses.