# Day 01 — Control System Fundamentals

## 1. Open-loop and Closed-loop Control Systems

### 1.1 Basic Components

A feedback control system mainly consists of three components:

- Plant: $G(s)$
- Controller: $C(s)$
- Feedback element: $H(s)$

### 1.2 Open-loop Transfer Function

For a standard single-loop feedback system, the loop transfer function is:

$$
L(s)=C(s)G(s)H(s)
$$

For a unity feedback system:

$$
H(s)=1
$$

Therefore:

$$
L(s)=C(s)G(s)
$$

### 1.3 Closed-loop Transfer Function

For a negative feedback system:

$$
T(s)=\frac{C(s)G(s)}{1+C(s)G(s)H(s)}
$$

For unity feedback:

$$
T(s)=\frac{L(s)}{1+L(s)}
$$

The closed-loop characteristic equation is:

$$
1+L(s)=0
$$

### 1.4 Applications of Open-loop Transfer Function

The loop transfer function can be used to:

1. Derive the closed-loop transfer function.
2. Obtain the closed-loop characteristic equation.
3. Analyze root locus.
4. Plot Bode diagrams.
5. Evaluate gain margin and phase margin.

## 2. PI Controller

### 2.1 Mathematical Expression

The PI controller is expressed as:

$$
C(s)=K_p+\frac{K_i}{s}
$$

Rearranging:

$$
C(s)=\frac{K_ps+K_i}{s}
$$

Where:

- ($K_p$): Proportional gain
- ($K_i$): Integral gain

### 2.2 Pole and Zero

The PI controller has one pole at the origin:

$$
s=0
$$

Its zero is located at:

$$
s=-\frac{K_i}{K_p}
$$

Changing ($K_p$) and ($K_i$) affects the controller gain and zero location.

## 3. PI Controller Design Based on Pole Placement

### 3.1 Plant Model

The plant used in this experiment is:

$$
G(s)=\frac{1}{0.5s+1}
$$

The controller and plant are connected in series.

For unity negative feedback, the open-loop transfer function is:

$$
L(s)=C(s)G(s)
$$

Substituting the PI controller:

$$
L(s)=
\frac{K_ps+K_i}{s(0.5s+1)}
$$

### 3.2 Closed-loop Transfer Function

Using the unity negative feedback relationship:

$$
T(s)=\frac{L(s)}{1+L(s)}
$$

After simplification:

$$
T(s)=
\frac{K_ps+K_i}
{0.5s^2+(1+K_p)s+K_i}
$$

The closed-loop characteristic equation is:

$$
0.5s^2+(1+K_p)s+K_i=0
$$

### 3.3 Coefficient Matching

The standard second-order characteristic equation is:

$$
s^2+2\zeta\omega_ns+\omega_n^2=0
$$

Where:

- ($\zeta$): Damping ratio
- ($\omega_n$): Natural frequency

Dividing the characteristic equation by 0.5:

$$
s^2+2(1+K_p)s+2K_i=0
$$

Comparing coefficients gives:

$$
K_p=\zeta\omega_n-1
$$

$$
K_i=\frac{\omega_n^2}{2}
$$

**Important:** These equations are derived specifically for the plant used in this experiment. They cannot be directly applied to arbitrary transfer functions.

## 4. System Identification

When the mathematical model of a plant is unknown, system identification can be used to estimate its dynamic characteristics.

A basic approach is step response analysis.

### Basic Procedure

1. Apply a known input signal.
2. Measure the system output.
3. Analyze the response curve.
4. Estimate model parameters.
5. Establish an approximate mathematical model.
6. Validate the model using experimental data.

For example, a first-order system can be approximated as:

$$
G(s)=\frac{K}{\tau s+1}
$$

Where:

- ($K$): System gain
- ($\tau$): Time constant

Other approaches include empirical tuning and automatic controller tuning.

## 5. Controller Design Workflow

The basic controller design workflow is:

1. Analyze the plant.
2. Define control objectives.
3. Select controller structure.
4. Calculate or tune controller parameters.
5. Analyze closed-loop stability.
6. Validate performance through simulation.
7. Test and optimize on the actual system.

When the plant model is unknown, system identification or experimental tuning can be used.

## 6. Experimental Observations

During the Simulink experiments, different proportional and integral gains were tested.

Main observations:

- Increasing proportional gain affected the response speed.
- Changing integral gain affected the response and settling behavior.
- Different parameter combinations produced different dynamic responses.
- No overshoot was observed in the tested cases.

The experiments also demonstrated the importance of controlling variables.

When multiple controller parameters change simultaneously, it is difficult to determine which parameter causes a specific performance change.

Therefore, parameters should be varied separately when studying their individual effects.

**Note:** These observations apply to the tested plant and parameter ranges. They should not be generalized to all control systems.

## 7. Key Learning Outcomes

Today I learned:

- The relationship between open-loop and closed-loop transfer functions.
- How to derive a closed-loop characteristic equation.
- The structure and pole-zero characteristics of a PI controller.
- The basic idea of closed-loop pole placement.
- How to use system identification when the plant model is unknown.
- Why controller tuning should be based on analysis rather than blind trial and error.

The most important takeaway:

**Understand the plant first, define the control objectives, design the controller, and validate the result through simulation and experiments.**

## 8. Next Steps

Day 02:

- Continuous PID and discrete PID.
- Discretization methods.
- Sampling period analysis.
- Digital PID implementation in C.