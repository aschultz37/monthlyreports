#include "stoolreport.hpp"

using namespace std;

/*importParser
* Parses a line of the csv file into fields of EntryData struct
*/
void SR::StoolReport::importParser(string lineIn, SR::EntryData &fieldsOut){
    SR::EntryData* tempentry = new SR::EntryData;
    char delimiter = ','; //for a blood report, there are 7 fields separated by 6 commas
    short PNbeg, PNend, SAbeg, SAend, Vbeg, Vend, Oncbeg, Oncend, SIDbeg, SIDend, StIDbeg, StIDend, Recbeg, Recend, Datebeg, Dateend;
    //determine indices for substrings
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
    SIDend = i; StIDbeg = ++i;
    while(lineIn[i] != delimiter){ i++;}
    StIDend = i; Recbeg = ++i;
    while(lineIn[i] != delimiter){ i++;}
    Recend = i; Datebeg = ++i;
    Dateend = lineIn.length();
    //set struct fields to each substring
    tempentry->PN = lineIn.substr(PNbeg, PNend);
    tempentry->studyArm = lineIn.substr(SAbeg, SAend);
    tempentry->visit = lineIn.substr(Vbeg, Vend);
    tempentry->oncID = lineIn.substr(Oncbeg, Oncend);
    tempentry->subjectID = lineIn.substr(SIDbeg, SIDend);
    tempentry->stoolID = lineIn.substr(StIDbeg, StIDend);
    tempentry->received = lineIn.substr(Recbeg, Recend);
    tempentry->date = lineIn.substr(Datebeg, Dateend);
    //store entry in vector
    parsedLines.push_back(tempentry);
}

/*stoolMonthFilter
* Filters parsedLines by month and year, putting valid entries into filteredLines
* Returns the number of entries in that month/year
*/
int SR::StoolReport::stoolMonthFilter(int month, int year){
    int counter = 0;
    for(int i = 0; i < parsedLines.length(); i++){
        if(extractMonth(parsedLines.at(i)->date) == month && extractYear(parsedLines.at(i)->date) == year){
            filteredLines.push_back(parsedLines.at(i));
            counter++;
        }
    }
    return counter;
}

/*extractMonth
* Returns the month (as an integer) as extracted from a date (string) of format m/d/y
*/
int SR::StoolReport::extractMonth(string date){
    char delimiter = '/'; 
    int i = 0; string month = "";
    while(date[i] != delimiter){ month.append(date[i++]);}
    return stoi(month);
}

/*extractYear
* Returns the year (as an integer) as extracted from a date (string) of format m/d/y
*/
int SR::StoolReport::extractYear(string date){
    char delimiter = '/'; 
    int i = 0; string year = "";
    while(date[i++] != delimiter){} //thru month
    i++; //skip /
    while(date[i++] != delimiter){} //thru day
    i++; //skip /
    while(date[i] < date.length()){ year.append(date[i++]);}
    return stoi(year);
}

SR::StoolReport::StoolReport(){

}

SR::StoolReport::~StoolReport(){
    for(int i = 0; i < parsedLines.length(); i++){
        delete parsedLines[i];
        parsedLines[i] = NULL;
    }
    for(int i = 0; i < filteredLines.length(); i++){
        delete filteredLines[i];
        filteredLines[i] = NULL;
    }
    for(int i = 0; i < sortedLines.length(); i++){
        delete sortedLines[i];
        sortedLines[i] = NULL;
    }
}