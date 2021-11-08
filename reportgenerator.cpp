#include "reportgenerator.hpp"

using namespace std;

/*importCSV
* Imports lines from CSV and parses it into struct
*/
void importCSV(string inFileName){

}

/*displayReport
* Prints resulting/sorted list to terminal
*/
void displayReport(){

}

/*writeReport
* Writes the resulting/sorted list to txt file
*/
void writeReport(std::string outFileName){

}

/*filterMonth
* Copies only lines from the correct month/yr into filteredLines
* Returns total # entries found
*/
int filterMonth(string month, string year){
    int numEntries;
    return numEntries;
}

/*sort
* Sorts by option: 1) PN; 2) OncID; 3) Subject ID; 4) Timepoint; 5) Date
*/
void sort(int option){
    return 1;
}

/*importParser
* Parses a line of the csv file into fields of EntryData struct
*/
void importParser(std::string lineIn, RG::EntryData &fieldsOut){

}

/*pnSort
* Sorts alphabetically by PN
*/
void pnSort(){

}

/*oncSort
* Sorts numerically by Onc ID
*/
void oncSort(){

}

/*subjectSort
* Sorts numerically by Subject ID
*/
void subjectSort(){

}

/*timeSort
* Sorts from lowest timepoint to highest timepoint
*/
void timeSort(){

}
/*dateSort
* Sorts from oldest date to most recent date
*/
void dateSort(){

}

/*dateCompare
* Compares two dates formatted as mm/dd/yyyy, m/d/yyyy, mm/d/yyyy, or m/dd/yyyy
* Returns 1 if date1 > date2, 0 if =, -1 if date1 < date2
*/
int dateCompare(string date1, string date2){
    int month1, day1, year1; //number of digits in each field of date1
    month1 = day1 = year1 = 0;
    int i = 0;
    while(date1[i++] != '/'){ month1++;}
    while(date1[i++] != '/'){ day1++;}
    for(int j = i; j < date1.length(); j++){ year1++;}

    int month2, day2, year2; //number of digits in each field of date2
    month2 = day2 = year2 = 0;
    i = 0;
    while(date2[i++] != '/'){ month2++;}
    while(date2[i++] != '/'){ day2++;}
    for(int j = i; j < date2.length(); j++){ year2++;}

    //convert the fields of each date to int for easier comparison
    int month1val = stoi(date1.substr(0,month1));
    int day1val = stoi(date1.substr(month1+1,month1+1+day1));
    int year1val = stoi(date1.substr(month1+1+day1+1,date1.length()));

    int month2val = stoi(date2.substr(0,month2));
    int day2val = stoi(date2.substr(month2+1,month2+1+day2));
    int year2val = stoi(date2.substr(month2+1+day2+1,date2.length()));

    //compare years
    if(year1val > year2val) return 1;
    if(year1val < year2val) return -1;
    //i.e. years are ==, compare months
    if(month1val > month2val) return 1;
    if(month1val < month2val) return -1;
    //i.e. months & years are ==, compare days
    if(day1val > day2val) return 1;
    if(day1val < day2val) return -1;
    //i.e. months, years, & days are ==
    return 0;
}