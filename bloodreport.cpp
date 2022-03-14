#include "bloodreport.hpp"

using namespace std;

/*importParser
* Parses a line of the csv file into fields of EntryData struct
*/
void BR::BloodReport::importParser(const string lineIn){
    BR::EntryData* tempentry = new BR::EntryData;
    char delimiter = ',';
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
    tempentry->received = ar[5];
    tempentry->date = ar[6];
    //store entry in vector
    parsedLines.push_back(tempentry);
}

/*bloodMonthFilter
* Filters parsedLines by month and year, putting valid entries into filteredLines
* Returns the number of entries in that month/year
*/
int BR::BloodReport::bloodMonthFilter(int month, int year){
    clearFiltered();
    int counter = 0;
    for(int i = 0; i < parsedLines.size(); i++){
        if(extractMonth(parsedLines.at(i)->date) == month && extractYear(parsedLines.at(i)->date) == year){
            filteredLines.push_back(parsedLines.at(i));
            counter++;
        }
    }
    return counter;
}

/*copytoSortBlood
* Copies filteredLines to sortedLines
*/
void BR::BloodReport::copytoSortBlood(){
    for(int i = 0; i < filteredLines.size(); i++){
        sortedLines.push_back(filteredLines.at(i));
    }
}

/*clearSort()
* Clears the sortLines vector
*/
void BR::BloodReport::clearSort(){
    sortedLines.clear();
}

/*clearFiltered()
* Clears the filteredLines vector
*/
void BR::BloodReport::clearFiltered(){
    filteredLines.clear();
}

/*swapSortedLines
* Swaps the EntryData* at two indices in sortedLines
*/
void BR::BloodReport::swapSortedLines(int index1, int index2){
    BR::EntryData* tmp = sortedLines.at(index1);
    sortedLines.at(index1) = sortedLines.at(index2);
    sortedLines.at(index2) = tmp;
}

/*isEmpty
* Determines if all fields of the struct located at parsedLines(index) are empty
* Returns true if empty, false if filled w/ info
*/
bool BR::BloodReport::isEmpty(int index){
    if(parsedLines.at(index)->date.length() >= 2){ return false;}
    else if(parsedLines.at(index)->PN.length() != 0){ return false;}
    else if(parsedLines.at(index)->studyArm.length() != 0){ return false;}
    else if(parsedLines.at(index)->visit.length() != 0){ return false;}
    else if(parsedLines.at(index)->oncID.length() != 0){ return false;}
    else if(parsedLines.at(index)->subjectID.length() != 0){ return false;}
    else if(parsedLines.at(index)->received.length() != 0){ return false;}
    else return true;
}
/*extractMonth
* Returns the month (as an integer) as extracted from a date (string) of format m/d/y
*/
int BR::BloodReport::extractMonth(string date){
    char delimiter = '/'; 
    int i = 0; string month = "";
    while(date[i] != delimiter){ month.append(1, date[i++]);}
    try{
        return stoi(month);
    } catch(invalid_argument){
        return 0;
    }
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
    try{
        return stoi(year);
    } catch(invalid_argument){
        return 0;
    }
}

BR::BloodReport::BloodReport(){

}

BR::BloodReport::~BloodReport(){
    for(int i = 0; i < parsedLines.size(); i++){
        delete parsedLines[i];
        parsedLines[i] = NULL;
    }
}