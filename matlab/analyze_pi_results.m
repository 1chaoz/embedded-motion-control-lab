
%% PI Controller Performance Analysis
% Day 01 - Calculate dynamic performance indicators

clear;
clc;
close all;

%% 1. Load simulation results

scriptDir = fileparts(mfilename('fullpath'));

dataDir = fullfile(scriptDir, 'results', 'day01');

dataFile = fullfile(dataDir, 'pi_sweep_results.mat');

if ~isfile(dataFile)
    error('Simulation result file not found!');
end

load(dataFile, 'results');

numCases = length(results);

%% 2. Define reference and thresholds

reference = 1;

riseLow = 0.1 * reference;
riseHigh = 0.9 * reference;

settlingLower = 0.98 * reference;
settlingUpper = 1.02 * reference;

%% 3. Initialize result arrays

riseTime = zeros(numCases, 1);
settlingTime = zeros(numCases, 1);
overshoot = zeros(numCases, 1);
terminalErrorAtStop = zeros(numCases, 1);
finalOutput = zeros(numCases, 1);

%% 4. Calculate performance indicators

for k = 1:numCases

    t = results(k).Time(:);
    y = results(k).Output(:);

    % Rise time: 10% to 90%

    idx10 = find(y >= riseLow, 1, 'first');
    idx90 = find(y >= riseHigh, 1, 'first');

    if isempty(idx10) || isempty(idx90)

        riseTime(k) = NaN;

    else

        t10 = interp1( ...
            y(idx10-1:idx10), ...
            t(idx10-1:idx10), ...
            riseLow);

        t90 = interp1( ...
            y(idx90-1:idx90), ...
            t(idx90-1:idx90), ...
            riseHigh);

        riseTime(k) = t90 - t10;

    end


    % Settling time: 2% band with interpolation
    
    outside = find( ...
        y < settlingLower | y > settlingUpper);
    
    if isempty(outside)
    
        settlingTime(k) = 0;
    
    elseif outside(end) == length(y)
    
        settlingTime(k) = NaN;
    
    else
    
        lastOutside = outside(end);
    
        t1 = t(lastOutside);
        t2 = t(lastOutside + 1);
    
        y1 = y(lastOutside);
        y2 = y(lastOutside + 1);
    
        % Interpolate the final entry into the 2% band
    
        if y1 < settlingLower && y2 >= settlingLower
    
            settlingTime(k) = interp1( ...
                [y1 y2], [t1 t2], settlingLower);
    
        elseif y1 > settlingUpper && y2 <= settlingUpper
    
            settlingTime(k) = interp1( ...
                [y1 y2], [t1 t2], settlingUpper);
    
        else
    
            settlingTime(k) = t2;
    
        end
    
    end

    % Overshoot percentage

    overshoot(k) = max(0, ...
        (max(y) - reference) / abs(reference) * 100);

    % Final output and sterminal-state error

    finalOutput(k) = y(end);

    terminalErrorAtStop(k) = ...
        abs(reference - finalOutput(k)) / abs(reference) * 100;

end

%% 5. Create performance table

experiment = string({results.name})';

Kp = [results.Kp]';
Ki = [results.Ki]';

metricsTable = table( ...
    experiment, ...
    Kp, ...
    Ki, ...
    riseTime, ...
    settlingTime, ...
    overshoot, ...
    terminalErrorAtStop, ...
    finalOutput, ...
    'VariableNames', { ...
    'Experiment', ...
    'Kp', ...
    'Ki', ...
    'RiseTime_s', ...
    'SettlingTime_s', ...
    'Overshoot_percent', ...
    'TerminalErrorAtStop_percent', ...
    'FinalOutput'});

%% 6. Display and save results

disp('PI Controller Performance Analysis');

disp(metricsTable);

writetable(metricsTable, ...
    fullfile(dataDir, 'pi_performance_metrics.csv'));

save(fullfile(dataDir, 'pi_performance_metrics.mat'), ...
    'metricsTable');

disp('Performance analysis completed!');
