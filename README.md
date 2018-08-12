# Raw-Data
![Raw Data Application Image](https://i.imgur.com/heLsMj2.png)

## Overview
Raw Data is an application meant to assist in extracting and rebuilding IREM .DAT files. This application can be used with any PS2 game developed by IREM, and the .DAT type is automatically detected when extracting. To build this application, simply open the solution file in Visual Studio 2017 and compile.

## Extracting
To extract a file, press the button labeled "Open File in File Explorer" underneath the extraction textbox. After selecting the file to extract, press "Extract" or "Recursive Extract." "Extract" will only extract the file selected, while "Recursive Extract" will first extract the selected file, then recursively search through the result for other .DAT files to extract and extract those.

The result will be placed in a new folder named the same as the original file, prepended by "@".

## Rebuilding
To rebuild an extracted file, select the folder to rebuild using the "Open Folder Dialog" button then press "Rebuild."
There are two options which will affect the rebuild result. "Large DAT" will generate the header of the .DAT as a separate file (generating a .FAT and .DAT file), and "Use generic header" will recreate the .DAT using the old header format, rather than the Raw Danger format. The resulting file(s) will be placed in the same directory that contains the folder that is being rebuilt.