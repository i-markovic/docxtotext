# DOCX to TXT Converter (docxtotext)

## Introduction

DOCX to TXT Converter is a C++ code project that allows you to extract text from DOCX files and save it as a TXT file. 

## Usage
To add the DOCX to TXT Converter code into your project, follow these steps:

Copy the following 3 files from DTT folder into your project directory:
- dtt.h
- zip_file.h
- zip_file.cpp
 
In your code, include dtt.h and call the function:     
int dtt(const std::filesystem::path& fp)

with the path of the DOCX file you want to convert to TXT.

## Note
Code utilizes the `tfussell/miniz-cpp` library to open DOCX files as ZIP archive

## Example Project

This example project provides an MSVC 2022 solution, which builds the `docxtotxt.exe` tool. 

This tool can be used as follows:

docxtotext [DOCX-file]

where [DOCX-file] is the path to the DOCX file.

Output is a file with the same name and a .txt extension.

## Platform Compatibility
The project is designed to work on Windows, supports UNICODE. For other operating systems, slight modifications may be required for compatibility.

## License
This project is licensed under the MIT License.
