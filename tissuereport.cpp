#include "tissuereport.hpp"
#include <sstream>

using namespace std;

/*importParser
* Parses a line of the csv file into fields of EntryData struct
*/
void TR::TissueReport::importParser(string lineIn){
    TR::EntryData* tempentry = new TR::EntryData;
    char delimiter = ','; //for a blood report, there are 7 fields separated by 6 commas
    vector <string> ar;
    stringstream inlinestream(lineIn);
    string token;

    while(getline(inlinestream, token, delimiter)){
        ar.push_back(token);
    }
    //set struct fields to each substring
    tempentry->PN = ar[0];
    tempentry->studyArm = ar[1];
    tempentry->visit = ar[2];
    tempentry->oncID = ar[3];
    tempentry->subjectID = ar[4];
    tempentry->sampleType = ar[5];
    tempentry->biopsyType = ar[6];
    tempentry->date = ar[7];
    //store entry in vector
    parsedLines.push_back(tempentry);
}

/*tissueMonthFilter
* Filters parsedLines by month and year, putting valid entries into filteredLines
* Returns the number of entries in that month/year
*/
int TR::TissueReport::tissueMonthFilter(int month, int year){
    int counter = 0;
    for(int i = 0; i < parsedLines.size(); i++){
        if(extractMonth(parsedLines.at(i)->date) == month && extractYear(parsedLines.at(i)->date) == year){
            filteredLines.push_back(parsedLines.at(i));
            counter++;
        }
    }
    return counter;
}

/*swapSortedLines
* Swaps the EntryData* at two indices in sortedLines
*/
void TR::TissueReport::swapSortedLines(int index1, int index2){
    TR::EntryData* tmp = sortedLines.at(index1);
    sortedLines.at(index1) = sortedLines.at(index2);
    sortedLines.at(index2) = tmp;
}

/*extractMonth
* Returns the month (as an integer) as extracted from a date (string) of format m/d/y
*/
int TR::TissueReport::extractMonth(string date){
    char delimiter = '/'; 
    int i = 0; string month = "";
    while(date[i] != delimiter){ month.append(1, date[i++]);}
    return stoi(month);
}

/*extractYear
* Returns the year (as an integer) as extracted from a date (string) of format m/d/y
*/
int TR::TissueReport::extractYear(string date){
    char delimiter = '/'; 
    int i = 0; string year = "";
    while(date[i] != delimiter){i++;} //thru month
    i++; //skip /
    while(date[i] != delimiter){i++;} //thru day
    i++; //skip /
    year = date.substr(i, date.length());
    return stoi(year);
}

TR::TissueReport::TissueReport(){

}

TR::TissueReport::~TissueReport(){
    for(int i = 0; i < parsedLines.size(); i++){
        delete parsedLines[i];
        parsedLines[i] = NULL;
    }
}