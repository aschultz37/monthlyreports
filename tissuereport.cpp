#include "tissuereport.hpp"

using namespace std;

/*importParser
* Parses a line of the csv file into fields of EntryData struct
*/
void TR::TissueReport::importParser(string lineIn){
    TR::EntryData* tempentry = new TR::EntryData;
    char delimiter = ','; //for a blood report, there are 7 fields separated by 6 commas
    short PNbeg, PNend, SAbeg, SAend, Vbeg, Vend, Oncbeg, Oncend, SIDbeg, SIDend, STbeg, STend, BTbeg, BTend, Datebeg, Dateend;
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
    SIDend = i; STbeg = ++i;
    while(lineIn[i] != delimiter){ i++;}
    STend = i; BTbeg = ++i;
    while(lineIn[i] != delimiter){ i++;}
    BTend = i; Datebeg = ++i;
    Dateend = lineIn.length();
    //set struct fields to each substring
    tempentry->PN = lineIn.substr(PNbeg, PNend);
    tempentry->studyArm = lineIn.substr(SAbeg, SAend);
    tempentry->visit = lineIn.substr(Vbeg, Vend);
    tempentry->oncID = lineIn.substr(Oncbeg, Oncend);
    tempentry->subjectID = lineIn.substr(SIDbeg, SIDend);
    tempentry->sampleType = lineIn.substr(STbeg, STend);
    tempentry->biopsyType = lineIn.substr(BTbeg, BTend);
    tempentry->date = lineIn.substr(Datebeg, Dateend);
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
    while(date[i++] != delimiter){} //thru month
    i++; //skip /
    while(date[i++] != delimiter){} //thru day
    i++; //skip /
    while(date[i] < date.length()){ year.append(1, date[i++]);}
    return stoi(year);
}

TR::TissueReport::TissueReport(){

}

TR::TissueReport::~TissueReport(){
    for(int i = 0; i < parsedLines.size(); i++){
        delete parsedLines[i];
        parsedLines[i] = NULL;
    }
    for(int i = 0; i < filteredLines.size(); i++){
        delete filteredLines[i];
        filteredLines[i] = NULL;
    }
    for(int i = 0; i < sortedLines.size(); i++){
        delete sortedLines[i];
        sortedLines[i] = NULL;
    }
}