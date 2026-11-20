
%% PI Controller - Automated Simulation Test
% Day 1: First automated simulation

clear;
clc;

%% 1. Locate Simulink model

scriptDir = fileparts(mfilename('fullpath'));

modelFile = fullfile(scriptDir, 'PI_Control_Model.slx');

if ~isfile(modelFile)
    error('Cannot find PI_Control_Model.slx');
end

[~, modelName] = fileparts(modelFile);

%% 2. Load model

load_system(modelFile);

%% 3. Set PI controller parameters

Kp = 1;
Ki = 1;

pidBlock = [modelName '/PID Controller'];

set_param(pidBlock, ...
    'P', num2str(Kp), ...
    'I', num2str(Ki));

%% 4. Set simulation time

set_param(modelName, 'StopTime', '20');

%% 5. Open Scope

open_system([modelName '/Scope']);

%% 6. Run simulation

sim(modelName);

disp('Simulation completed successfully!');
disp(['Kp = ', num2str(Kp)]);
disp(['Ki = ', num2str(Ki)]);
