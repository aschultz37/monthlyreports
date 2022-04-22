#include "tissuereport.hpp"

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

/*sampleTypeSort()
* Counts # of each sample type per timepoint in a month, ex. C1D1 FFPE 5; C1D1 OCT 3; C2D1 FFPE 2
*/
void TR::TissueReport::sampleTypeSort(){
    if(filteredLines.size() > 0){ //if not empty, account for 0th iteration in below for loop
        TimepointSampleCount *tmp = new TimepointSampleCount; //consider using filteredLines instead of sortedLines?
        tmp->timepoint = filteredLines.at(0)->visit;
        tmp->sampleType.push_back(filteredLines.at(0)->sampleType);
        tmp->count.push_back(1);
        sampleSortedLines.push_back(tmp);
    }
    else return; //no need to sort if list is empty
    for(int i = 1; i < filteredLines.size(); i++){ //i filteredLines iterator; already added the first item to vector, start at 1
        bool foundTime = false; bool foundSampleType = false;
        int timepointIndex = 0;
        for(int j = 0; j < sampleSortedLines.size(); j++){ //j sampleSorted iterator; check if timepoint is present
            if(spacelessHash(filteredLines.at(i)->visit) == spacelessHash(sampleSortedLines.at(j)->timepoint)){ 
                foundTime = true; timepointIndex = j;
                for(int r = 0; r < sampleSortedLines.at(j)->sampleType.size(); r++){ //r is sampleType iterator; check if sample type present within timepoint
                    if(spacelessHash(filteredLines.at(i)->sampleType) == spacelessHash(sampleSortedLines.at(j)->sampleType.at(r))){
                        foundSampleType = true;
                        (sampleSortedLines.at(j)->count.at(r))++;
                    }
                }
            }
        }
        if(!foundTime){ //if timepoint not found, need a new entry
            TimepointSampleCount *tmp = new TimepointSampleCount;
            tmp->timepoint = filteredLines.at(i)->visit;
            tmp->sampleType.push_back(filteredLines.at(i)->sampleType);
            tmp->count.push_back(1);
            sampleSortedLines.push_back(tmp);
        }
        else if(foundTime && !foundSampleType){ //if found timepoint but not sample type, add sample type to existing entry
            sampleSortedLines.at(timepointIndex)->sampleType.push_back(filteredLines.at(i)->sampleType);
            sampleSortedLines.at(timepointIndex)->count.push_back(1);
        }
    }
}

/*sampleTypeSortTotal()
* Counts # of each sample type per timepoint over ALL samples, ex. C1D1 FFPE 5; C1D1 OCT 3; C2D1 FFPE 2
*/
void TR::TissueReport::sampleTypeSortTotal(int month, int year){
    //1) check that the entry is <= the current month, similar to totalTimepoints
    //2) same algorithm as sampleTypeSort() but using parsedLines and sampleSortedLinesTotal vector
    if(parsedLines.size() > 0){ //if not empty, account for 0th iteration in below for loop
        //first, locate the first entry that is <= current month/year
        int firstEntry = 0; bool foundFirst = false;
        while(extractYear(parsedLines.at(firstEntry)->date) >= year && !foundFirst){
            if(extractYear(parsedLines.at(firstEntry)->date) == year){
                if(extractMonth(parsedLines.at(firstEntry)->date) <= month){
                    if(!isEmpty(firstEntry)){
                        foundFirst = true;
                    }
                }
            }
            if(!foundFirst){ //firstEntry > year or empty
                firstEntry++;
            }
        }
        TimepointSampleCount *tmp = new TimepointSampleCount; //consider using filteredLines instead of sortedLines?
        tmp->timepoint = parsedLines.at(firstEntry)->visit;
        tmp->sampleType.push_back(parsedLines.at(firstEntry)->sampleType);
        tmp->count.push_back(1);
        sampleSortedLinesTotal.push_back(tmp);
    }
    else return; //no need to sort if list is empty
    for(int i = 1; i < parsedLines.size(); i++){ //i parsededLines iterator; already added the first item to vector, start at 1
        bool foundTime = false; bool foundSampleType = false;
        int timepointIndex = 0;
        bool validEntry = true;
        if(isEmpty(i)){
            validEntry = false;
        }
        if(extractYear(parsedLines.at(i)->date) > year){
            validEntry = false;
        }
        else if(extractYear(parsedLines.at(i)->date) == year){
            if(extractMonth(parsedLines.at(i)->date) > month){
                validEntry = false;
            }
        }
        if(validEntry){
            for(int j = 0; j < sampleSortedLinesTotal.size(); j++){ //j sampleSortedTotal iterator; check if timepoint is present
                if(spacelessHash(parsedLines.at(i)->visit) == spacelessHash(sampleSortedLinesTotal.at(j)->timepoint)){ 
                    foundTime = true; timepointIndex = j;
                    for(int r = 0; r < sampleSortedLinesTotal.at(j)->sampleType.size(); r++){ //r is sampleType iterator; check if sample type present within timepoint
                        if(spacelessHash(parsedLines.at(i)->sampleType) == spacelessHash(sampleSortedLinesTotal.at(j)->sampleType.at(r))){
                            foundSampleType = true;
                            (sampleSortedLinesTotal.at(j)->count.at(r))++;
                        }
                    }
                }
            }
            if(!foundTime){ //if timepoint not found, need a new entry
                TimepointSampleCount *tmp = new TimepointSampleCount;
                tmp->timepoint = parsedLines.at(i)->visit;
                tmp->sampleType.push_back(parsedLines.at(i)->sampleType);
                tmp->count.push_back(1);
                sampleSortedLinesTotal.push_back(tmp);
            }
            else if(foundTime && !foundSampleType){ //if found timepoint but not sample type, add sample type to existing entry
                sampleSortedLinesTotal.at(timepointIndex)->sampleType.push_back(parsedLines.at(i)->sampleType);
                sampleSortedLinesTotal.at(timepointIndex)->count.push_back(1);
            }
        }
    }
}

/*copytoSortTissue
* Copies filteredLines to sortedLines
*/
void TR::TissueReport::copytoSortTissue(){
    for(int i = 0; i < filteredLines.size(); i++){
        sortedLines.push_back(filteredLines.at(i));
    }
}

/*clearSort()
* Clears the sortLines vector
*/
void TR::TissueReport::clearSort(){
    sortedLines.clear();
}

/*clearFiltered()
* Clears the filteredLines vector
*/
void TR::TissueReport::clearFiltered(){
    filteredLines.clear();
}

/*clearSampleSortedLines()
* Clears the sampleSortedLines vector
*/
void TR::TissueReport::clearSampleSortedLines(){
    sampleSortedLines.clear();
}

/*swapSortedLines
* Swaps the EntryData* at two indices in sortedLines
*/
void TR::TissueReport::swapSortedLines(int index1, int index2){
    TR::EntryData* tmp = sortedLines.at(index1);
    sortedLines.at(index1) = sortedLines.at(index2);
    sortedLines.at(index2) = tmp;
}

/*isEmpty
* Determines if all fields of the struct located at parsedLines(index) are empty
* Returns true if empty, false if filled w/ info
*/
bool TR::TissueReport::isEmpty(int index){
    if(parsedLines.at(index)->date.length() >= 2){ return false;}
    else if(parsedLines.at(index)->PN.length() != 0){ return false;}
    else if(parsedLines.at(index)->studyArm.length() != 0){ return false;}
    else if(parsedLines.at(index)->visit.length() != 0){ return false;}
    else if(parsedLines.at(index)->oncID.length() != 0){ return false;}
    else if(parsedLines.at(index)->subjectID.length() != 0){ return false;}
    else if(parsedLines.at(index)->sampleType.length() != 0){ return false;}
    else if(parsedLines.at(index)->biopsyType.length() != 0){ return false;}
    else return true;
}

/*extractMonth
* Returns the month (as an integer) as extracted from a date (string) of format m/d/y
*/
int TR::TissueReport::extractMonth(string date){
    string delimiter = "/";
    try{
        string month = date.substr(0, date.find(delimiter));
        return stoi(month);
    }
    catch(std::exception){
        return 0; //exclude things with no/invalid date
    }
}

/*extractYear
* Returns the year (as an integer) as extracted from a date (string) of format m/d/y
*/
int TR::TissueReport::extractYear(string date){
    string delimiter = "/";
    try{
        int delimiter1 = date.find_last_of(delimiter);
        string year = date.substr((delimiter1+1), date.length());
        return stoi(year);
    } catch(std::exception){
        return 0; //exclude things with no/invalid date
    }
}

/*spacelessHash
* Computes a value based only on alphanumeric characters in a string (i.e. ignores spaces, special chars)
* For example, " Arm A" would return same value as "Arm A" or "Arm  A "
*/
int TR::TissueReport::spacelessHash(string input){
    int tmp = 0;
    int KEY_SIZE = 37; //1 space, 26 letters, 10 digits (special char ignored completely)
    char key[KEY_SIZE] = {' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
                    't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    for(int i = 0; i < input.length(); i++){
        for(int j = 0; j < KEY_SIZE; j++){
            if(tolower(input[i]) == key[j]){
                if(j > 26){ tmp += (j*j);} //make numbers contribute much more so it is less likely that Baseline == CxD1 for example
                else tmp += j; //note that space is in index 0 so would not count; a is index 1 so does count
            }
        }
    }
    return tmp;
}

TR::TissueReport::TissueReport(){

}

TR::TissueReport::~TissueReport(){
    for(int i = 0; i < parsedLines.size(); i++){ delete parsedLines[i]; parsedLines[i] = NULL;}
    for(int i = 0; i < sampleSortedLines.size(); i++){ delete sampleSortedLines[i]; sampleSortedLines[i] = NULL;}
}