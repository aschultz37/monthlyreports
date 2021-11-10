#include "bloodreport.hpp"

using namespace std;

/*importParser
* Parses a line of the csv file into fields of EntryData struct
*/
void BR::BloodReport::importParser(string lineIn){
    BR::EntryData* tempentry = new BR::EntryData;
    char delimiter = ','; //for a blood report, there are 7 fields separated by 6 commas
    short PNbeg, PNend, SAbeg, SAend, Vbeg, Vend, Oncbeg, Oncend, SIDbeg, SIDend, Recbeg, Recend, Datebeg, Dateend;
    //determine indices for substrings
    int i = 0;
    PNbeg = 0;
    while(lineIn[i] != delimiter){ i++;}
    PNend = i; SAbeg = ++i;
    while(lineIn[i] != delimiter){ i++;}
    SAend = i; Vbeg = ++i;
    while(lineIn[i] != delimiter){ i++;}
    Vend = i; Oncbeg = ++i;
    while(lineIn[i] != delimiter){ i++;}
    Oncend = i; SIDbeg = ++i;
    while(lineIn[i] != delimiter){ i++;}
    SIDend = i; Recbeg = ++i;
    while(lineIn[i] != delimiter){ i++;}
    Recend = i; Datebeg = ++i;
    Dateend = lineIn.length();
    //set struct fields to each substring
    tempentry->PN = lineIn.substr(PNbeg, PNend);
    tempentry->studyArm = lineIn.substr(SAbeg, SAend);
    tempentry->visit = lineIn.substr(Vbeg, Vend);
    tempentry->oncID = lineIn.substr(Oncbeg, Oncend);
    tempentry->subjectID = lineIn.substr(SIDbeg, SIDend);
    tempentry->received = lineIn.substr(Recbeg, Recend);
    tempentry->date = lineIn.substr(Datebeg, Dateend);
    //store entry in vector
    parsedLines.push_back(tempentry);
}

/*bloodMonthFilter
* Filters parsedLines by month and year, putting valid entries into filteredLines
* Returns the number of entries in that month/year
*/
int BR::BloodReport::bloodMonthFilter(int month, int year){
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
void BR::BloodReport::swapSortedLines(int index1, int index2){
    BR::EntryData* tmp = sortedLines.at(index1);
    sortedLines.at(index1) = sortedLines.at(index2);
    sortedLines.at(index2) = tmp;
}

/*extractMonth
* Returns the month (as an integer) as extracted from a date (string) of format m/d/y
*/
int BR::BloodReport::extractMonth(string date){
    char delimiter = '/'; 
    int i = 0; string month = "";
    while(date[i] != delimiter){ month.append(1, date[i++]);}
    return stoi(month);
}

/*extractYear
* Returns the year (as an integer) as extracted from a date (string) of format m/d/y
*/
int BR::BloodReport::extractYear(string date){
    char delimiter = '/'; 
    int i = 0; string year = "";
    while(date[i] != delimiter){i++;} //thru month
    i++; //skip /
    while(date[i] != delimiter){i++;} //thru day
    i++; //skip /
    year = date.substr(i, date.length());
    return stoi(year);
}

BR::BloodReport::BloodReport(){

}

BR::BloodReport::~BloodReport(){
    for(int i = 0; i < parsedLines.size(); i++){
        delete parsedLines[i];
        parsedLines[i] = NULL;
    }
}