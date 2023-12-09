# Project-S1
University project for C language.

Quality Control System for Laptop Manufacturing

This is a simple console-based Quality Control System for managing laptop manufacturing data. The program allows users to perform various operations such as adding new laptops, displaying available laptops, checking the quality of laptops, deleting specific laptops, and saving the laptop details to a text file.

Features

Add New Laptop: Users can input details for a new laptop including its model, manufacturing year, CPU, and RAM.
Display Laptops: Displays a list of all available laptops with their details in the console.
Check Laptop Quality: Assesses the quality of each laptop based on defined criteria (manufacturing year, CPU, RAM).
Delete a Laptop: Enables users to delete a specific laptop from the system.
Save Laptops to File: Saves the details of the laptops to a text file in a readable format for user reference.

Instructions

Compile: Compile the code using a C compiler (gcc recommended):

gcc -o laptop_system laptop_system.c
Run: Execute the compiled file:

Operations:

Choose options from the menu to perform specific operations as prompted.
Follow on-screen instructions to add, display, check quality, delete laptops, or save details to a file.
File Descriptions
laptop_system.c: Contains the source code for the Quality Control System.
laptops.txt: Binary file to store laptop data.
laptops_output.txt: Text file containing the human-readable list of laptops.
Usage Notes
The program creates and manages a binary file (laptops.txt) to store raw laptop data.
A text file (laptops_output.txt) is generated to provide a readable snapshot of the current laptop details.
Users can choose various operations from the menu to manage and analyze the laptop data.

Feel free to use, modify, or enhance this system according to your requirements.

