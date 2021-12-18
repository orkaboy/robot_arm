function [libName] = setupLib()
    % Add SDK folder plus all subfolders to the path.
    addpath(genpath("../DynamixelSDK"));
    addpath(genpath("lib"));
    libName = '';
    %Determine cpu architecture
    if strcmp(computer, 'PCWIN')
      libName = 'dxl_x86_c';
    elseif strcmp(computer, 'PCWIN64')
      libName = 'dxl_x64_c';
    elseif strcmp(computer, 'GLNX86')
      libName = 'libdxl_x86_c';
    elseif strcmp(computer, 'GLNXA64')
      libName = 'libdxl_x64_c';
    elseif strcmp(computer, 'MACI64')
      libName = 'libdxl_mac_c';
    end
    % Load Libraries
    if ~libisloaded(libName)
        [notfound, warnings] = loadlibrary(libName, 'dynamixel_sdk.h', 'addheader', 'port_handler.h', 'addheader', 'packet_handler.h');
    end
end

