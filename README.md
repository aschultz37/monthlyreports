**---Monthly Report Generator---**  
Austin C Schultz, November 2021  
austinc_schultz(at)dfci.harvard.edu  
  
This program generates easy outputs for BTIL monthly reports.  
  
PRE-RUN REQUIREMENTS  
To use the program, a few steps must be followed:  
 1) You must use a standardized BTIL Blood, Tissue, or Stool Processing sheet format.  
 2) You must save a copy of the sheet as a comma-delimited .csv file (not .xlsx or .xls).  
    - Note: There are multiple .csv formats, make sure to use (Comma delimited) option! Not UTF-8! 
 3) Remove unnecessary fields from the sheet.  
    - Only include PN --> Date.  
 4) Run the program.  
  
INITIALIZATION  
Upon startup, the program will prompt for the month and year you wish to view for the report.  
The input should be in number format (e.g., March would be 3 or 03 and the year would be 2021).  
This selection can be changed later via the main menu.  

USING MENUS  
All menus work by taking user input in the console/terminal.  
Selections for corresponding options should be simply a number (e.g., 1) followed by a press of the enter/return key.  
Please do not type the name of the option (e.g., Import File) or any characters other than the number.  

FIRST STEP - IMPORT  
The first step after getting to the main menu should be to Import File. You can select other options, but there isn't much point if there's no data to work with.  
When importing a file, make sure to select the correct type of file (i.e., Blood, Tissue, or Stool). This is critical for the import process, and the program will not work if you select the wrong type.  

PROGRAM FUNCTIONS  
After importing, you can sort, display the file/sorted results, and write the file/sorted results to a spreadsheet (.csv). These options are accessed via the main menu.  
 - Sort is currently able to sort by PN, OncID, Subject ID, Stool ID, Timepoint/Visit, and Date. If a field is unknown, it is treated as the lowest value and will be placed first in the list. Be sure to double-check the grouping of these patients, as patients with IDs listed as "?" could be intermixed.  
 - Timepoint/Visit sort also displays a list of timepoints and the number of samples per timepoint.  

Feel free to re-sort, re-display, or re-write at any time.  
You can also import a different file and/or change the month/year from the main menu. Be aware that doing so will delete the previous report's data, so be sure to write to the file if you need that data later.  
Note that while the program can deal with some formatting and input discrepanices, it is best not to rely on error handling! :)  

SCRIPT USE  
NOTE: There is very limited/no error checking when using script mode.  
Set up the file system:  
 - Make separate source and destination folders for blood, stool, and tissue sheets  
 - Set the variables at the top of generator.sh to these filepaths, ending SOURCE paths with /*  

Create the .csv files:  
 - Copy from the Processing Excel sheets into a .csv (comma-delimited) file.  
 - DO NOT copy the first line/two lines which are only headings; start at first patient.  
 - Copy from PN (leftmost column) through Date - DO NOT copy past date!  

Make sure the .csv files are in the appropriate folder (blood/stool/tissue).  
Change the program location appropriately.  
Run the script: ./generator.sh  
Output will be as a .csv in the destination directory you supplied.  
 - NOTE: If there is not a sheet for a trial that has a source sheet, that means there were no samples that month.  