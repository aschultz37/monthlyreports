#include "bloodreport.hpp"

using namespace std;

/*importParser
* Parses a line of the csv file into fields of EntryData struct
*/
void BR::BloodReport::importParser(string lineIn){
    BR::EntryData* tempentry = new BR::EntryData;
    char delimiter = ','; int numFields = 7; //for a blood report, there are 7 fields separated by 6 commas
    short PNbeg, PNend, SAbeg, SAend, Vbeg, Vend, Oncbeg, Oncend, SIDbeg, SIDend, Recbeg, Recend, Datebeg, Dateend;
    //determine indices for substrings
    PNbeg = 0;
    while(lineIn[i] != ','){ i++;}
    PNend = i; SAbeg = ++i;
    while(lineIn[i] != ','){ i++;}
    SAend = i; Vbeg = ++i;
    while(lineIn[i] != ','){ i++;}
    Vend = i; Oncbeg = ++i;
    while(lineIn[i] != ','){ i++;}
    Oncend = i; SIDbeg = ++i;
    while(lineIn[i] != ','){ i++;}
    SIDend = i; Recbeg = ++i;
    while(lineIn[i] != ','){ i++;}
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

int bloodMonthFilter(string month, string year){
    
}

BR::BloodReport::BloodReport(){

}

BR::BloodReport::~BloodReport(){
    for(int i = 0; i < filteredLines.length(); i++){
        delete filteredLines[i];
        filteredLines[i] = NULL;
    }
    for(int i = 0; i < sortedLines.length(); i++){
        delete sortedLines[i];
        sortedLines[i] = NULL;
    }
}