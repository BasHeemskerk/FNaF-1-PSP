# Compile Guide
This guide will walk you through the process of install everything you need for compile the `Fnaf-1-PSP`. 

It is important to mention that this guide assumes you have experience with programming and already have the `make` command available.

## Installing MinimalistPSPSDK:
- Download the [MinimalistPSPSDK](https://github.com/darksectordds/darksectordds.github.io/releases/download/MinimalistPSPSDK/pspsdk-setup-0.15.0.exe).
- Run the installer by double-clicking the downloaded file.
- Follow the prompts and complete the installation process.
- After installation, add the `pspsdk/bin` to the **PATH**.
- To check if the installation is successful, open PowerShell or Cmd and try using `psp-gcc`. If it shows `"no input files"`, then the pspsdk is working correctly.

## Compiling FNAF1 PSP
- Download the `Fnaf-1-PSP` repository and place it in the desired folder.
- Open PowerShell or Cmd.
- Use the `cd` command to navigate to the folder where the `Fnaf-1-PSP` is located.
- Finally, use the `make` command.
- This should generate an `EBOOT.PBP` file in your folder, which is used by the PSP.
