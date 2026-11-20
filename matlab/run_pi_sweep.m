
%% PI Controller Parameter Sweep
% Day 01 - Automated simulation of six PI parameter combinations

clear;
clc;
close all;

%% 1. Locate and load Simulink model

scriptDir = fileparts(mfilename('fullpath'));

modelFile = fullfile(scriptDir, 'PI_Control_Model.slx');

if ~isfile(modelFile)
    error('Cannot find PI_Control_Model.slx');
end

[~, modelName] = fileparts(modelFile);

load_system(modelFile);

pidBlock = [modelName '/PID Controller'];
plantBlock = [modelName '/Transfer Fcn'];

%% 2. Add To Workspace block

dataBlock = [modelName '/To Workspace_Data'];

existingBlock = find_system(modelName, ...
    'SearchDepth', 1, ...
    'Name', 'To Workspace_Data');

if isempty(existingBlock)

    add_block('simulink/Sinks/To Workspace', ...
        dataBlock, ...
        'Position', [700 180 790 210]);

end

% Configure data output format
set_param(dataBlock, ...
    'VariableName', 'yout', ...
    'SaveFormat', 'Timeseries');

% Connect plant output to To Workspace
srcPorts = get_param(plantBlock, 'PortHandles');
dstPorts = get_param(dataBlock, 'PortHandles');

if get_param(dstPorts.Inport(1), 'Line') == -1

    add_line(modelName, ...
        srcPorts.Outport(1), ...
        dstPorts.Inport(1), ...
        'autorouting', 'on');

end

%% 3. Define six parameter combinations

caseNames = { ...
    'A1_Kp1_Ki1', ...
    'A2_Kp2_Ki1', ...
    'A3_Kp5_Ki1', ...
    'B1_Kp2_Ki0.5', ...
    'B2_Kp2_Ki1', ...
    'B3_Kp2_Ki4'};

Kp_values = [1 2 5 2 2 2];

Ki_values = [1 1 1 0.5 1 4];

numCases = length(Kp_values);

%% 4. Prepare output directories

imageDir = fullfile(scriptDir, '..', 'images', 'day01');

dataDir = fullfile(scriptDir, 'results', 'day01');

if ~exist(imageDir, 'dir')
    mkdir(imageDir);
end

if ~exist(dataDir, 'dir')
    mkdir(dataDir);
end

%% 5. Run six simulations automatically

results = struct([]);

for k = 1:numCases

    fprintf('\nRunning experiment %d/%d\n', k, numCases);

    % Create simulation input
    simIn = Simulink.SimulationInput(modelName);


    % Set proportional gain (Kp)
    simIn = simIn.setBlockParameter( ...
        pidBlock, ...
        'P', num2str(Kp_values(k)));
    
    % Set integral gain (Ki)
    simIn = simIn.setBlockParameter( ...
        pidBlock, ...
        'I', num2str(Ki_values(k)));

    % Use the same simulation duration
    simIn = simIn.setModelParameter( ...
        'StopTime', '20', ...
        'MaxStep', '0.01', ...
        'ReturnWorkspaceOutputs', 'on');

    % Run simulation
    simOut = sim(simIn);

    % Extract output data
    ts = simOut.get('yout');

    if isempty(ts)
        error('No output data obtained in experiment %s', caseNames{k});
    end

    t = ts.Time(:);
    y = squeeze(ts.Data);
    y = y(:);

    % Store experiment results
    results(k).name = caseNames{k};
    results(k).Kp = Kp_values(k);
    results(k).Ki = Ki_values(k);
    results(k).Time = t;
    results(k).Output = y;

    fprintf('Kp = %g, Ki = %g: completed\n', ...
        Kp_values(k), Ki_values(k));

end

%% 6. Plot and export comparison figures

% Experiment A: Kp comparison
figure('Color', 'w');
hold on;

for k = 1:3
    plot(results(k).Time, results(k).Output, ...
        'LineWidth', 1.5);
end

yline(1, 'k--', 'Reference');

grid on;
xlabel('Time (s)');
ylabel('Output');
title('PI Controller - Proportional Gain Comparison');

legend(caseNames(1:3), 'Location', 'southeast');

ax = gca;
ax.Toolbar.Visible = 'off';

exportgraphics(ax, ...
    fullfile(imageDir, 'kp_comparison.png'), ...
    'Resolution', 300);

% Experiment B: Ki comparison
figure('Color', 'w');
hold on;

for k = 4:6
    plot(results(k).Time, results(k).Output, ...
        'LineWidth', 1.5);
end

yline(1, 'k--', 'Reference');

grid on;
xlabel('Time (s)');
ylabel('Output');
title('PI Controller - Integral Gain Comparison');

legend(caseNames(4:6), 'Location', 'southeast');

ax = gca;
ax.Toolbar.Visible = 'off';

exportgraphics(ax, ...
    fullfile(imageDir, 'ki_comparison.png'), ...
    'Resolution', 300);

%% 7. Save simulation data

save(fullfile(dataDir, 'pi_sweep_results.mat'), ...
    'results', 'Kp_values', 'Ki_values', 'caseNames');

disp(' ');
disp('===================================');
disp('All six simulations completed!');
disp('Comparison figures exported.');
disp('Simulation data saved.');
disp('===================================');
