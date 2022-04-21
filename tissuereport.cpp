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

/*copytoSortTissue
* Copies filteredLines to sortedLines
*/
void TR::TissueReport::copytoSortTissue(){
    for(int i = 0; i < filteredLines.size(); i++){
        sortedLines.push_back(filteredLines.at(i));
    }
}

// /*copySortedLines
// * Copies sortedLines to sortedLinesCopy
// */
// void TR::TissueReport::copySortedLines(){
//     for(int i = 0; i < sortedLines.size(); i++){
//         sortedLinesCopy.push_back(sortedLines.at(i));
//     }
// }

// /*copyBackSortedLines
// * Copies sortedLinesCopy back to sortedLines
// */
// void TR::TissueReport::copyBackSortedLines(){
//     for(int i = 0; i < sortedLinesCopy.size(); i++){
//         sortedLines.push_back(sortedLinesCopy.at(i));
//     }
// }

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

// /*clearSortedCopy()
// * Clears the sortedLinesCopy vector
// */
// void TR::TissueReport::clearSortedCopy(){
//     sortedLinesCopy.clear();
// }

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
int TR::TissueReport::extractYear(string date){
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