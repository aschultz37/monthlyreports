#include "reportgenerator.hpp"

using namespace std;

/*importCSV
* Imports lines from CSV and parses it into struct
* Types: 1 = blood, 2 = tissue, 3 = stool
* Requires type of file (blood, tissue, stool) and file name
*/
void RG::ReportGenerator::importCSV(string inFileName){
    ifstream infile; infile.open(inFileName);
    string tmp = "";
    fileLines.clear();
    while(getline(infile, tmp)){
        fileLines.push_back(tmp);
    }
    //now need to parse it depending on filetype
    if(filetype == RG::filetypes::blood){
        for(int i = 0; i < fileLines.size(); i++){
            sheets->bloodreport->importParser(fileLines.at(i));
        }
    }
    else if(filetype == RG::filetypes::tissue){
        for(int i = 0; i < fileLines.size(); i++){
            sheets->tissuereport->importParser(fileLines.at(i));
        }
    }
    else if(filetype == RG::filetypes::stool){
        for(int i = 0; i < fileLines.size(); i++){
            sheets->stoolreport->importParser(fileLines.at(i));
        }
    }
}

/*filterMonth
* Copies only lines from the correct month/yr into filteredLines
* Returns total # entries found
*/
int RG::ReportGenerator::filterMonth(int month, int year){
    if(filetype == RG::filetypes::blood){
        return sheets->bloodreport->bloodMonthFilter(month, year);
    }
    else if(filetype == RG::filetypes::tissue){
        return sheets->tissuereport->tissueMonthFilter(month, year);
    }
    else if(filetype == RG::filetypes::stool){
        return sheets->stoolreport->stoolMonthFilter(month, year);
    }
    return -1;
}

/*copytoSort
* Copies filteredLines to sortedLines
*/
void RG::ReportGenerator::copytoSort(){
    if(filetype == RG::filetypes::blood){
        sheets->bloodreport->clearSort();
        sheets->bloodreport->copytoSortBlood();
    }
    else if(filetype == RG::filetypes::tissue){
        sheets->tissuereport->clearSort();
        sheets->tissuereport->copytoSortTissue();
    }
    else if(filetype == RG::filetypes::stool){
        sheets->stoolreport->clearSort();
        sheets->stoolreport->copytoSortStool();
    }
}

/*displayReport
* Prints resulting/sorted list to terminal
*/
void RG::ReportGenerator::displayReport(){
    if(filetype == RG::filetypes::blood){
        cout << setw(PNWIDTH) << "PN" << setw(ARMWIDTH) << "Arm" << setw(VISITWIDTH) << "Visit" << setw(ONCWIDTH) << "OncID" 
        << setw(STUDYWIDTH) << "StudyID" << setw(RECWIDTH) << "Rec." << setw(DATEWIDTH) << "Date\n";
        for(int i = 0; i < sheets->bloodreport->getSortedLines().size(); i++){
            cout << setw(PNWIDTH) << sheets->bloodreport->getSortedLines().at(i)->PN;
            cout << setw(ARMWIDTH) << sheets->bloodreport->getSortedLines().at(i)->studyArm;
            cout << setw(VISITWIDTH) << sheets->bloodreport->getSortedLines().at(i)->visit;
            cout << setw(ONCWIDTH) << sheets->bloodreport->getSortedLines().at(i)->oncID;
            cout << setw(STUDYWIDTH) << sheets->bloodreport->getSortedLines().at(i)->subjectID;
            cout << setw(RECWIDTH) << sheets->bloodreport->getSortedLines().at(i)->received;
            cout << setw(DATEWIDTH) << sheets->bloodreport->getSortedLines().at(i)->date << '\n';
        }
    }
    else if(filetype == RG::filetypes::tissue){
        cout << setw(PNWIDTH) << "PN" << setw(ARMWIDTH) << "Arm" << setw(VISITWIDTH) << "Visit" << setw(ONCWIDTH) << "OncID" 
        << setw(STUDYWIDTH) << "StudyID" << setw(SAMPLEWIDTH) << "Sample" << setw(BIOPSYWIDTH) << "Biopsy" << setw(DATEWIDTH) << "Date\n";
        for(int i = 0; i < sheets->tissuereport->getSortedLines().size(); i++){
            cout << setw(PNWIDTH) << sheets->tissuereport->getSortedLines().at(i)->PN;
            cout << setw(ARMWIDTH) << sheets->tissuereport->getSortedLines().at(i)->studyArm;
            cout << setw(VISITWIDTH) << sheets->tissuereport->getSortedLines().at(i)->visit;
            cout << setw(ONCWIDTH) << sheets->tissuereport->getSortedLines().at(i)->oncID;
            cout << setw(STUDYWIDTH) <<  sheets->tissuereport->getSortedLines().at(i)->subjectID;
            cout << setw(SAMPLEWIDTH) << sheets->tissuereport->getSortedLines().at(i)->sampleType;
            cout << setw(BIOPSYWIDTH) << sheets->tissuereport->getSortedLines().at(i)->biopsyType;
            cout << setw(DATEWIDTH) << sheets->tissuereport->getSortedLines().at(i)->date << '\n';
        }
    }
    else if(filetype == RG::filetypes::stool){
        cout << setw(PNWIDTH) << "PN" << setw(ARMWIDTH) << "Arm" << setw(VISITWIDTH) << "Visit" << setw(ONCWIDTH) << "OncID" 
        << setw(STUDYWIDTH) << "StudyID" << setw(STOOLWIDTH) << "StoolID" << setw(RECWIDTH) << "Received" << setw(DATEWIDTH) << "Date\n";
        for(int i = 0; i < sheets->stoolreport->getSortedLines().size(); i++){
            cout << setw(PNWIDTH) << sheets->stoolreport->getSortedLines().at(i)->PN;
            cout << setw(ARMWIDTH) << sheets->stoolreport->getSortedLines().at(i)->studyArm;
            cout << setw(VISITWIDTH) << sheets->stoolreport->getSortedLines().at(i)->visit;
            cout << setw(ONCWIDTH) << sheets->stoolreport->getSortedLines().at(i)->oncID;
            cout << setw(STUDYWIDTH) << sheets->stoolreport->getSortedLines().at(i)->subjectID;
            cout << setw(STOOLWIDTH) << sheets->stoolreport->getSortedLines().at(i)->stoolID;
            cout << setw(RECWIDTH) << sheets->stoolreport->getSortedLines().at(i)->received;
            cout << setw(DATEWIDTH) << sheets->stoolreport->getSortedLines().at(i)->date << '\n';
        }
    }
}

/*displayTimepointTracker
* Prints a list of timepoints and the number of samples per timepoint to terminal
*/
void RG::ReportGenerator::displayTimepointTracker(){
    cout << setw(16) << "Timepoint" << setw(10) << "Number\n";
    for(int i = 0; i < timepointTracker.size(); i++){
        cout << setw(16) << timepointTracker.at(i)->timepoint << setw(10) << timepointTracker.at(i)->count << "\n";
    }
}

/*totalTimepoints
* Determines the total # of samples per timepoint of the entire report (pre-month filter)
* Fills vector timepointTotal based on parsedLines from <type>report.hpp
*/
void RG::ReportGenerator::totalTimepoints(int month, int year){
    if(filetype == RG::filetypes::blood){
        vector <string> timepoints;
        for(int i = 0; i < sheets->bloodreport->getParsedLines().size(); i++){
            if(timepoints.size() > 0){ //to account for first iteration
                bool found = false;
                for(int j = 0; j < timepoints.size(); j++){
                    if(spacelessHash(sheets->bloodreport->getParsedLines().at(i)->visit) == spacelessHash(timepoints.at(j))){ found = true;}
                }
                if(!found){ 
                    if(!sheets->bloodreport->isEmpty(i)){
                        timepoints.push_back(sheets->bloodreport->getParsedLines().at(i)->visit);
                    }
                }
            }
            else timepoints.push_back(sheets->bloodreport->getParsedLines().at(i)->visit);
        }
        //create vector for each unique timepoint & fill w/ each matching entry
        vector <vector<BR::EntryData*>> timepointVecs(timepoints.size());
        for(int i = 0; i < sheets->bloodreport->getParsedLines().size(); i++){
            if(!sheets->bloodreport->isEmpty(i)){ //check if entry has any info in it
                for(int j = 0; j < timepointVecs.size(); j++){
                    if(spacelessHash(sheets->bloodreport->getParsedLines().at(i)->visit) == spacelessHash(timepoints.at(j))){
                        //check year, month <= parsedLines.at(i)->date; still count return 0 exceptions
                        if(extractYear(sheets->bloodreport->getParsedLines().at(i)->date) <= year){
                            if(extractMonth(sheets->bloodreport->getParsedLines().at(i)->date) <= month || extractYear(sheets->bloodreport->getParsedLines().at(i)->date) < year){
                                timepointVecs.at(j).push_back(sheets->bloodreport->getParsedLines().at(i));
                            }
                        }
                    }
                }
            }
        }
        //fill timepointTotal w/ entry for each timepoint
        for(int i = 0; i < timepoints.size(); i++){
            RG::TimepointCount* tmp = new RG::TimepointCount;
            tmp->timepoint = timepoints.at(i);
            tmp->count = timepointVecs.at(i).size();
            timepointTotal.push_back(tmp);
        }
    }
    else if(filetype == RG::filetypes::tissue){
        vector <string> timepoints;
        for(int i = 0; i < sheets->tissuereport->getParsedLines().size(); i++){
            if(timepoints.size() > 0){ //to account for first iteration
                bool found = false;
                for(int j = 0; j < timepoints.size(); j++){
                    if(spacelessHash(sheets->tissuereport->getParsedLines().at(i)->visit) == spacelessHash(timepoints.at(j))){ found = true;}
                }
                if(!found){ 
                    if(!sheets->tissuereport->isEmpty(i)){
                        timepoints.push_back(sheets->tissuereport->getParsedLines().at(i)->visit);
                    }
                }
            }
            else timepoints.push_back(sheets->tissuereport->getParsedLines().at(i)->visit);
        }
        //create vector for each unique timepoint & fill w/ each matching entry
        vector <vector<TR::EntryData*>> timepointVecs(timepoints.size());
        for(int i = 0; i < sheets->tissuereport->getParsedLines().size(); i++){
            if(!sheets->tissuereport->isEmpty(i)){
                for(int j = 0; j < timepointVecs.size(); j++){
                    if(spacelessHash(sheets->tissuereport->getParsedLines().at(i)->visit) == spacelessHash(timepoints.at(j))){
                        //check year, month <= parsedLines.at(i)->date; check for return 0 exception
                        if(extractYear(sheets->tissuereport->getParsedLines().at(i)->date) <= year){
                            if(extractMonth(sheets->tissuereport->getParsedLines().at(i)->date) <= month || extractYear(sheets->bloodreport->getParsedLines().at(i)->date) < year){
                                timepointVecs.at(j).push_back(sheets->tissuereport->getParsedLines().at(i));
                            }
                        }
                    }
                }
            }
        }
        //fill timepointTotal w/ entry for each timepoint
        for(int i = 0; i < timepoints.size(); i++){
            RG::TimepointCount* tmp = new RG::TimepointCount;
            tmp->timepoint = timepoints.at(i);
            tmp->count = timepointVecs.at(i).size();
            timepointTotal.push_back(tmp);
        }
    }
    else if(filetype == RG::filetypes::stool){
        //list of unique timepoints
        vector <string> timepoints;
        for(int i = 0; i < sheets->stoolreport->getParsedLines().size(); i++){
            if(timepoints.size() > 0){ //to account for first iteration
                bool found = false;
                for(int j = 0; j < timepoints.size(); j++){
                    if(spacelessHash(sheets->stoolreport->getParsedLines().at(i)->visit) == spacelessHash(timepoints.at(j))){ found = true;}
                }
                if(!found){ 
                    if(!sheets->stoolreport->isEmpty(i)){
                        timepoints.push_back(sheets->stoolreport->getParsedLines().at(i)->visit);
                    }
                }
            }
            else timepoints.push_back(sheets->stoolreport->getParsedLines().at(i)->visit);
        }
        //create vector for each unique timepoint & fill w/ each matching entry
        vector <vector<SR::EntryData*>> timepointVecs(timepoints.size());
        for(int i = 0; i < sheets->stoolreport->getParsedLines().size(); i++){
            if(!sheets->stoolreport->isEmpty(i)){
                for(int j = 0; j < timepointVecs.size(); j++){
                    if(spacelessHash(sheets->stoolreport->getParsedLines().at(i)->visit) == spacelessHash(timepoints.at(j))){
                        //check year, month <= parsedLines.at(i)->date; check for return 0 exception
                        if(extractYear(sheets->stoolreport->getParsedLines().at(i)->date) <= year){
                            if(extractMonth(sheets->stoolreport->getParsedLines().at(i)->date) <= month || extractYear(sheets->bloodreport->getParsedLines().at(i)->date) < year){
                                timepointVecs.at(j).push_back(sheets->stoolreport->getParsedLines().at(i));
                            }
                        }
                    }
                }
            }
        }
        //fill timepointTotal w/ entry for each timepoint
        for(int i = 0; i < timepoints.size(); i++){
            RG::TimepointCount* tmp = new RG::TimepointCount;
            tmp->timepoint = timepoints.at(i);
            tmp->count = timepointVecs.at(i).size();
            timepointTotal.push_back(tmp);
        }
    }
}

/*writeReport
* Writes the resulting/sorted list to csv file
*/
void RG::ReportGenerator::writeReport(std::string outFileName){
    ofstream outfile; outfile.open(outFileName);
    outfile << "Timepoint,Number,TOTAL" << endl;
    for(int i = 0; i < timepointTotal.size(); i++){
        outfile << timepointTotal.at(i)->timepoint << "," << timepointTotal.at(i)->count << endl;
    }
    outfile << "Timepoint,Number,MONTHLY" << endl;
    for(int i = 0; i < timepointTracker.size(); i++){
        outfile << timepointTracker.at(i)->timepoint << "," << timepointTracker.at(i)->count << endl;
    }
    if(filetype == RG::filetypes::blood){
        outfile << "PN,Arm,Visit,OncID,StudyID,Rec.,Date" << endl;
        for(int i = 0; i < sheets->bloodreport->getSortedLines().size(); i++){
            BR::EntryData* tmp = sheets->bloodreport->getSortedLines().at(i);
            outfile << tmp->PN << "," << tmp->studyArm << "," << tmp->visit << "," << tmp->oncID << "," << tmp->subjectID << "," 
                << tmp->received << "," << tmp->date << endl;
        }
    }
    else if(filetype == RG::filetypes::tissue){
        outfile << "PN,Arm,Visit,OncID,StudyID,Sample,Biopsy,Date" << endl;
        for(int i = 0; i < sheets->tissuereport->getSortedLines().size(); i++){
            TR::EntryData* tmp = sheets->tissuereport->getSortedLines().at(i);
            outfile << tmp->PN << "," << tmp->studyArm << "," << tmp->visit << "," << tmp->oncID << "," << tmp->subjectID << "," 
                << tmp->sampleType << "," << tmp->biopsyType << "," << tmp->date << endl;
        }
    }
    else if(filetype == RG::filetypes::stool){
        outfile << "PN,Arm,Visit,OncID,StudyID,StoolID,Rec.,Date" << endl;
        for(int i = 0; i < sheets->stoolreport->getSortedLines().size(); i++){
            SR::EntryData* tmp = sheets->stoolreport->getSortedLines().at(i);
            outfile << tmp->PN << "," << tmp->studyArm << "," << tmp->visit << "," << tmp->oncID << "," << tmp->subjectID << "," 
                << tmp->stoolID << "," << tmp->received << "," << tmp->date << endl;
        }
    }
    outfile.close();
}

/*sort
* Sorts by option: 1) PN; 2) OncID; 3) Subject ID; 4) Stool ID; 5) Timepoint; 6) Date
*/
void RG::ReportGenerator::sort(int option){
    switch (option){
        case 1:
            pnSort();
            break;
        case 2:
            oncSort();
            break;
        case 3:
            subjectSort();
            break;
        case 4:
            stoolSort();
            break;
        case 5:
            timeSort();
            displayTimepointTracker();
            break;
        case 6:
            dateSort();
            break;
    }
}

/*pnSort
* Groups unique PN together; NOTE does not account for unique pt w/ same PN
* Sorts alphabetically by PN
*/
void RG::ReportGenerator::pnSort(){
    if(filetype == RG::filetypes::blood){
        sheets->bloodreport->clearSort();
        vector <string> pns;
        for(int i = 0; i < sheets->bloodreport->getFilteredLines().size(); i++){
            if(pns.size() > 0){ //to account for first iteration
                bool found = false;
                for(int j = 0; j < pns.size(); j++){
                    if(spacelessHash(sheets->bloodreport->getFilteredLines().at(i)->PN) == spacelessHash(pns.at(j))){ found = true;}
                }
                if(!found){ pns.push_back(sheets->bloodreport->getFilteredLines().at(i)->PN);}
            }
            else pns.push_back(sheets->bloodreport->getFilteredLines().at(i)->PN);
        }
        //create vector for each unique PN & fill w/ each matching entry
        vector <vector<BR::EntryData*>> pnVecs(pns.size());
        for(int i = 0; i < sheets->bloodreport->getFilteredLines().size(); i++){
            for(int j = 0; j < pnVecs.size(); j++){
                if(spacelessHash(sheets->bloodreport->getFilteredLines().at(i)->PN) == spacelessHash(pns.at(j))){
                    pnVecs.at(j).push_back(sheets->bloodreport->getFilteredLines().at(i));
                }
            }
        }
        //push the vectors back into sortedLines
        for(int i = 0; i < pnVecs.size(); i++){
            for(int j = 0; j < pnVecs.at(i).size(); j++){
                sheets->bloodreport->pushSortedLines(pnVecs.at(i).at(j));
            }
        }
        //do selection sort on sortedLines
        int min;
        for(int i = 0; i < sheets->bloodreport->getSortedLines().size()-1; i++){
            min = i;
            for(int j = i+1; j < sheets->bloodreport->getSortedLines().size(); j++){
                if(sheets->bloodreport->getSortedLines().at(j)->PN.compare(sheets->bloodreport->getSortedLines().at(min)->PN) < 0){
                    min = j;
                }
            }
            sheets->bloodreport->swapSortedLines(i,min);
        }
    }
    else if(filetype == RG::filetypes::tissue){
        sheets->tissuereport->clearSort();
        vector <string> pns;
        for(int i = 0; i < sheets->tissuereport->getFilteredLines().size(); i++){
            if(pns.size() > 0){ //to account for first iteration
                bool found = false;
                for(int j = 0; j < pns.size(); j++){
                    if(spacelessHash(sheets->tissuereport->getFilteredLines().at(i)->PN) == spacelessHash(pns.at(j))){ found = true;}
                }
                if(!found){ pns.push_back(sheets->tissuereport->getFilteredLines().at(i)->PN);}
            }
            else pns.push_back(sheets->tissuereport->getFilteredLines().at(i)->PN);
        }
        //create vector for each unique PN & fill w/ each matching entry
        vector <vector<TR::EntryData*>> pnVecs(pns.size());
        for(int i = 0; i < sheets->tissuereport->getFilteredLines().size(); i++){
            for(int j = 0; j < pnVecs.size(); j++){
                if(spacelessHash(sheets->tissuereport->getFilteredLines().at(i)->PN) == spacelessHash(pns.at(j))){
                    pnVecs.at(j).push_back(sheets->tissuereport->getFilteredLines().at(i));
                }
            }
        }
        //push the vectors back into sortedLines
        for(int i = 0; i < pnVecs.size(); i++){
            for(int j = 0; j < pnVecs.at(i).size(); j++){
                sheets->tissuereport->pushSortedLines(pnVecs.at(i).at(j));
            }
        }
        //do selection sort on sortedLines
        int min;
        for(int i = 0; i < sheets->tissuereport->getSortedLines().size()-1; i++){
            min = i;
            for(int j = i+1; j < sheets->tissuereport->getSortedLines().size(); j++){
                if(sheets->tissuereport->getSortedLines().at(j)->PN.compare(sheets->tissuereport->getSortedLines().at(min)->PN) < 0){
                    min = j;
                }
            }
            sheets->tissuereport->swapSortedLines(i,min);
        }
    }
    else if(filetype == RG::filetypes::stool){
        sheets->stoolreport->clearSort();
        vector <string> pns;
        for(int i = 0; i < sheets->stoolreport->getFilteredLines().size(); i++){
            if(pns.size() > 0){ //to account for first iteration
                bool found = false;
                for(int j = 0; j < pns.size(); j++){
                    if(spacelessHash(sheets->stoolreport->getFilteredLines().at(i)->PN) == spacelessHash(pns.at(j))){ found = true;}
                }
                if(!found){ pns.push_back(sheets->stoolreport->getFilteredLines().at(i)->PN);}
            }
            else pns.push_back(sheets->stoolreport->getFilteredLines().at(i)->PN);
        }
        //create vector for each unique PN & fill w/ each matching entry
        vector <vector<SR::EntryData*>> pnVecs(pns.size());
        for(int i = 0; i < sheets->stoolreport->getFilteredLines().size(); i++){
            for(int j = 0; j < pnVecs.size(); j++){
                if(spacelessHash(sheets->stoolreport->getFilteredLines().at(i)->PN) == spacelessHash(pns.at(j))){
                    pnVecs.at(j).push_back(sheets->stoolreport->getFilteredLines().at(i));
                }
            }
        }
        //push the vectors back into sortedLines
        for(int i = 0; i < pnVecs.size(); i++){
            for(int j = 0; j < pnVecs.at(i).size(); j++){
                sheets->stoolreport->pushSortedLines(pnVecs.at(i).at(j));
            }
        }
        //do selection sort on sortedLines
        int min;
        for(int i = 0; i < sheets->stoolreport->getSortedLines().size()-1; i++){
            min = i;
            for(int j = i+1; j < sheets->stoolreport->getSortedLines().size(); j++){
                if(sheets->stoolreport->getSortedLines().at(j)->PN.compare(sheets->stoolreport->getSortedLines().at(min)->PN) < 0){
                    min = j;
                }
            }
            sheets->stoolreport->swapSortedLines(i,min);
        }
    }
}

/*oncSort
* Sorts numerically by Onc ID
*/
void RG::ReportGenerator::oncSort(){
    if(filetype == RG::filetypes::blood){
        sheets->bloodreport->clearSort();
        //copy filteredLines into sortedLines
        for(int i = 0; i < sheets->bloodreport->getFilteredLines().size(); i++){
            sheets->bloodreport->pushSortedLines(sheets->bloodreport->getFilteredLines().at(i));
        }
        //do selection sort on sortedLines
        int min;
        for(int i = 0; i < sheets->bloodreport->getSortedLines().size()-1; i++){
            min = i;
            for(int j = i+1; j < sheets->bloodreport->getSortedLines().size(); j++){
                try{
                    if(stoolHash(sheets->bloodreport->getSortedLines().at(j)->oncID) < stoolHash(sheets->bloodreport->getSortedLines().at(min)->oncID)){
                        min = j;
                    }
                } catch(invalid_argument){ //defining ? as lowest possible value
                    if(sheets->bloodreport->getSortedLines().at(j)->oncID.compare("?") == 0) min = j;
                }
            }
            sheets->bloodreport->swapSortedLines(i,min);
        }
    }
    else if(filetype == RG::filetypes::tissue){
        sheets->tissuereport->clearSort();
        //copy filteredLines into sortedLines
        for(int i = 0; i < sheets->tissuereport->getFilteredLines().size(); i++){
            sheets->tissuereport->pushSortedLines(sheets->tissuereport->getFilteredLines().at(i));
        }
        //do selection sort on sortedLines
        int min;
        for(int i = 0; i < sheets->tissuereport->getSortedLines().size()-1; i++){
            min = i;
            for(int j = i+1; j < sheets->tissuereport->getSortedLines().size(); j++){
                try{
                    if(stoolHash(sheets->tissuereport->getSortedLines().at(j)->oncID) < stoolHash(sheets->tissuereport->getSortedLines().at(min)->oncID)){
                        min = j;
                    }
                } catch(invalid_argument){ //defining ? as lowest possible value
                    if(sheets->tissuereport->getSortedLines().at(j)->oncID.compare("?") == 0) min = j;
                }
            }
            sheets->tissuereport->swapSortedLines(i,min);
        }
    }
    else if(filetype == RG::filetypes::stool){
        sheets->stoolreport->clearSort();
        //copy filteredLines into sortedLines
        for(int i = 0; i < sheets->stoolreport->getFilteredLines().size(); i++){
            sheets->stoolreport->pushSortedLines(sheets->stoolreport->getFilteredLines().at(i));
        }
        //do selection sort on sortedLines
        int min;
        for(int i = 0; i < sheets->stoolreport->getSortedLines().size()-1; i++){
            min = i;
            for(int j = i+1; j < sheets->stoolreport->getSortedLines().size(); j++){
                try{
                    if(stoolHash(sheets->stoolreport->getSortedLines().at(j)->oncID) < stoolHash(sheets->stoolreport->getSortedLines().at(min)->oncID)){
                        min = j;
                    }
                } catch(invalid_argument){ //defining ? as lowest possible value
                    if(sheets->stoolreport->getSortedLines().at(j)->oncID.compare("?") == 0) min = j;
                }
            }
            sheets->stoolreport->swapSortedLines(i,min);
        }
    }
}

/*subjectSort
* Sorts numerically by Subject ID
*/
void RG::ReportGenerator::subjectSort(){
    if(filetype == RG::filetypes::blood){
        sheets->bloodreport->clearSort();
        //copy filteredLines into sortedLines
        for(int i = 0; i < sheets->bloodreport->getFilteredLines().size(); i++){
            sheets->bloodreport->pushSortedLines(sheets->bloodreport->getFilteredLines().at(i));
        }
        //do selection sort on sortedLines
        int min;
        for(int i = 0; i < sheets->bloodreport->getSortedLines().size()-1; i++){
            min = i;
            for(int j = i+1; j < sheets->bloodreport->getSortedLines().size(); j++){
                try{
                    if(stoolHash(sheets->bloodreport->getSortedLines().at(j)->subjectID) < stoolHash(sheets->bloodreport->getSortedLines().at(min)->subjectID)){
                        min = j;
                    }
                } catch(invalid_argument){ //defining ? as lowest possible value
                        if(sheets->bloodreport->getSortedLines().at(j)->subjectID.compare("?") == 0) min = j;
                }
            }
            sheets->bloodreport->swapSortedLines(i,min);
        }
    }
    else if(filetype == RG::filetypes::tissue){
        sheets->tissuereport->clearSort();
        //copy filteredLines into sortedLines
        for(int i = 0; i < sheets->tissuereport->getFilteredLines().size(); i++){
            sheets->tissuereport->pushSortedLines(sheets->tissuereport->getFilteredLines().at(i));
        }
        //do selection sort on sortedLines
        int min;
        for(int i = 0; i < sheets->tissuereport->getSortedLines().size()-1; i++){
            min = i;
            for(int j = i+1; j < sheets->tissuereport->getSortedLines().size(); j++){
                try{
                    if(stoolHash(sheets->tissuereport->getSortedLines().at(j)->subjectID) < stoolHash(sheets->tissuereport->getSortedLines().at(min)->subjectID)){
                        min = j;
                    }
                } catch(invalid_argument){ //defining ? as lowest possible value
                    if(sheets->tissuereport->getSortedLines().at(j)->subjectID.compare("?") == 0) min = j;
                }
            }
            sheets->tissuereport->swapSortedLines(i,min);
        }
    }
    else if(filetype == RG::filetypes::stool){
        sheets->stoolreport->clearSort();
        //copy filteredLines into sortedLines
        for(int i = 0; i < sheets->stoolreport->getFilteredLines().size(); i++){
            sheets->stoolreport->pushSortedLines(sheets->stoolreport->getFilteredLines().at(i));
        }
        //do selection sort on sortedLines
        int min;
        for(int i = 0; i < sheets->stoolreport->getSortedLines().size()-1; i++){
            min = i;
            for(int j = i+1; j < sheets->stoolreport->getSortedLines().size(); j++){
                try{
                    if(stoolHash(sheets->stoolreport->getSortedLines().at(j)->subjectID) < stoolHash(sheets->stoolreport->getSortedLines().at(min)->subjectID)){
                        min = j;
                    }
                } catch(invalid_argument){ //defining ? as lowest possible value
                    if(sheets->stoolreport->getSortedLines().at(j)->subjectID.compare("?") == 0) min = j;
                }
            }
            sheets->stoolreport->swapSortedLines(i,min);
        }
    }
}

/*stoolSort
* Sorts by Stool ID (groups by site, then numerically)
* Only callable for stoolreport
*/
void RG::ReportGenerator::stoolSort(){
    if(filetype != RG::filetypes::stool){ return;}
    sheets->stoolreport->clearSort();
    //copy filteredLines into sortedLines
    for(int i = 0; i < sheets->stoolreport->getFilteredLines().size(); i++){
        sheets->stoolreport->pushSortedLines(sheets->stoolreport->getFilteredLines().at(i));
    }
    //do selection sort on sortedLines
    int min;
    for(int i = 0; i < sheets->stoolreport->getSortedLines().size()-1; i++){
        min = i;
        for(int j = i+1; j < sheets->stoolreport->getSortedLines().size(); j++){
            try{
                if(stoolHash(sheets->stoolreport->getSortedLines().at(j)->stoolID) < stoolHash(sheets->stoolreport->getSortedLines().at(min)->stoolID)){
                    min = j;
                }
            } catch(invalid_argument){ //defining ? as lowest possible value
                if(sheets->stoolreport->getSortedLines().at(j)->stoolID.compare("?") == 0) min = j;
            }
        }
        sheets->stoolreport->swapSortedLines(i,min);
    }
}

/*timeSort
* Groups unique timepoints together
* TODO Sorts from lowest timepoint to highest timepoint; need to have list of priorities since some similar
*/
void RG::ReportGenerator::timeSort(){
    if(filetype == RG::filetypes::blood){
        sheets->bloodreport->clearSort();
        //list of unique timepoints
        vector <string> timepoints;
        for(int i = 0; i < sheets->bloodreport->getFilteredLines().size(); i++){
            if(timepoints.size() > 0){ //to account for first iteration
                bool found = false;
                for(int j = 0; j < timepoints.size(); j++){
                    if(spacelessHash(sheets->bloodreport->getFilteredLines().at(i)->visit) == spacelessHash(timepoints.at(j))){ found = true;}
                }
                if(!found){ timepoints.push_back(sheets->bloodreport->getFilteredLines().at(i)->visit);}
            }
            else timepoints.push_back(sheets->bloodreport->getFilteredLines().at(i)->visit);
        }
        //create vector for each unique timepoint & fill w/ each matching entry
        vector <vector<BR::EntryData*>> timepointVecs(timepoints.size());
        for(int i = 0; i < sheets->bloodreport->getFilteredLines().size(); i++){
            for(int j = 0; j < timepointVecs.size(); j++){
                if(spacelessHash(sheets->bloodreport->getFilteredLines().at(i)->visit) == spacelessHash(timepoints.at(j))){
                    timepointVecs.at(j).push_back(sheets->bloodreport->getFilteredLines().at(i));
                }
            }
        }
        //fill timepointTracker w/ entry for each timepoint
        for(int i = 0; i < timepoints.size(); i++){
            RG::TimepointCount* tmp = new RG::TimepointCount;
            tmp->timepoint = timepoints.at(i);
            tmp->count = timepointVecs.at(i).size();
            timepointTracker.push_back(tmp);
        }
        //push the vectors back into sortedLines
        for(int i = 0; i < timepointVecs.size(); i++){
            for(int j = 0; j < timepointVecs.at(i).size(); j++){
                sheets->bloodreport->pushSortedLines(timepointVecs.at(i).at(j));
            }
        }
    }
    else if(filetype == RG::filetypes::tissue){
        sheets->tissuereport->clearSort();
        //list of unique timepoints
        vector <string> timepoints;
        for(int i = 0; i < sheets->tissuereport->getFilteredLines().size(); i++){
            if(timepoints.size() > 0){ //to account for first iteration
                bool found = false;
                for(int j = 0; j < timepoints.size(); j++){
                    if(spacelessHash(sheets->tissuereport->getFilteredLines().at(i)->visit) == spacelessHash(timepoints.at(j))){ found = true;}
                }
                if(!found){ timepoints.push_back(sheets->tissuereport->getFilteredLines().at(i)->visit);}
            }
            else timepoints.push_back(sheets->tissuereport->getFilteredLines().at(i)->visit);
        }
        //create vector for each unique timepoint & fill w/ each matching entry
        vector <vector<TR::EntryData*>> timepointVecs(timepoints.size());
        for(int i = 0; i < sheets->tissuereport->getFilteredLines().size(); i++){
            for(int j = 0; j < timepointVecs.size(); j++){
                if(spacelessHash(sheets->tissuereport->getFilteredLines().at(i)->visit) == spacelessHash(timepoints.at(j))){
                    timepointVecs.at(j).push_back(sheets->tissuereport->getFilteredLines().at(i));
                }
            }
        }
        //fill timepointTracker w/ entry for each timepoint
        for(int i = 0; i < timepoints.size(); i++){
            RG::TimepointCount* tmp = new RG::TimepointCount;
            tmp->timepoint = timepoints.at(i);
            tmp->count = timepointVecs.at(i).size();
            timepointTracker.push_back(tmp);
        }
        //push the vectors back into sortedLines
        for(int i = 0; i < timepointVecs.size(); i++){
            for(int j = 0; j < timepointVecs.at(i).size(); j++){
                sheets->tissuereport->pushSortedLines(timepointVecs.at(i).at(j));
            }
        }
    }
    else if(filetype == RG::filetypes::stool){
        sheets->stoolreport->clearSort();
        //list of unique timepoints
        vector <string> timepoints;
        for(int i = 0; i < sheets->stoolreport->getFilteredLines().size(); i++){
            if(timepoints.size() > 0){ //to account for first iteration
                bool found = false;
                for(int j = 0; j < timepoints.size(); j++){
                    if(spacelessHash(sheets->stoolreport->getFilteredLines().at(i)->visit) == spacelessHash(timepoints.at(j))){ found = true;}
                }
                if(!found){ timepoints.push_back(sheets->stoolreport->getFilteredLines().at(i)->visit);}
            }
            else timepoints.push_back(sheets->stoolreport->getFilteredLines().at(i)->visit);
        }
        //create vector for each unique timepoint & fill w/ each matching entry
        vector <vector<SR::EntryData*>> timepointVecs(timepoints.size());
        for(int i = 0; i < sheets->stoolreport->getFilteredLines().size(); i++){
            for(int j = 0; j < timepointVecs.size(); j++){
                if(spacelessHash(sheets->stoolreport->getFilteredLines().at(i)->visit) == spacelessHash(timepoints.at(j))){
                    timepointVecs.at(j).push_back(sheets->stoolreport->getFilteredLines().at(i));
                }
            }
        }
        //fill timepointTracker w/ entry for each timepoint
        for(int i = 0; i < timepoints.size(); i++){
            RG::TimepointCount* tmp = new RG::TimepointCount;
            tmp->timepoint = timepoints.at(i);
            tmp->count = timepointVecs.at(i).size();
            timepointTracker.push_back(tmp);
        }
        //push the vectors back into sortedLines
        for(int i = 0; i < timepointVecs.size(); i++){
            for(int j = 0; j < timepointVecs.at(i).size(); j++){
                sheets->stoolreport->pushSortedLines(timepointVecs.at(i).at(j));
            }
        }
    }
}

/*dateSort
* Sorts from oldest date to most recent date
*/
void RG::ReportGenerator::dateSort(){
    if(filetype == RG::filetypes::blood){
        sheets->bloodreport->clearSort();
        //copy filteredLines into sortedLines
        for(int i = 0; i < sheets->bloodreport->getFilteredLines().size(); i++){
            sheets->bloodreport->pushSortedLines(sheets->bloodreport->getFilteredLines().at(i));
        }
        //do selection sort on sortedLines
        int min;
        for(int i = 0; i < sheets->bloodreport->getSortedLines().size()-1; i++){
            min = i;
            for(int j = i+1; j < sheets->bloodreport->getSortedLines().size(); j++){
                if(dateCompare(sheets->bloodreport->getSortedLines().at(j)->date, sheets->bloodreport->getSortedLines().at(min)->date) < 0){
                    min = j;
                }
            }
            sheets->bloodreport->swapSortedLines(i,min);
        }
    }
    else if(filetype == RG::filetypes::tissue){
        sheets->tissuereport->clearSort();
        //copy filteredLines into sortedLines
        for(int i = 0; i < sheets->tissuereport->getFilteredLines().size(); i++){
            sheets->tissuereport->pushSortedLines(sheets->tissuereport->getFilteredLines().at(i));
        }
        //do selection sort on sortedLines
        int min;
        for(int i = 0; i < sheets->tissuereport->getSortedLines().size()-1; i++){
            min = i;
            for(int j = i+1; j < sheets->tissuereport->getSortedLines().size(); j++){
                if(dateCompare(sheets->tissuereport->getSortedLines().at(j)->date, sheets->tissuereport->getSortedLines().at(min)->date) < 0){
                    min = j;
                }
            }
            sheets->tissuereport->swapSortedLines(i, min);
        }
    }
    else if(filetype == RG::filetypes::stool){
        sheets->stoolreport->clearSort();
        //copy filteredLines into sortedLines
        for(int i = 0; i < sheets->stoolreport->getFilteredLines().size(); i++){
            sheets->stoolreport->pushSortedLines(sheets->stoolreport->getFilteredLines().at(i));
        }
        //do selection sort on sortedLines
        int min;
        for(int i = 0; i < sheets->stoolreport->getSortedLines().size()-1; i++){
            min = i;
            for(int j = i+1; j < sheets->stoolreport->getSortedLines().size(); j++){
                if(dateCompare(sheets->stoolreport->getSortedLines().at(j)->date, sheets->stoolreport->getSortedLines().at(min)->date) < 0){
                    min = j;
                }
            }
            sheets->stoolreport->swapSortedLines(i, min);
        }
    }
}

/*dateCompare
* Compares two dates formatted as mm/dd/yyyy, m/d/yyyy, mm/d/yyyy, or m/dd/yyyy
* Returns 1 if date1 > date2, 0 if =, -1 if date1 < date2
*/
int RG::ReportGenerator::dateCompare(string date1, string date2){
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
    if(year1val > year2val){ return 1;}
    if(year1val < year2val){ return -1;}
    //i.e. years are ==, compare months
    if(month1val > month2val){ return 1;}
    if(month1val < month2val){ return -1;}
    //i.e. months & years are ==, compare days
    if(day1val > day2val){ return 1;}
    if(day1val < day2val){ return -1;}
    //i.e. months, years, & days are ==
    return 0;
}

/*spacelessHash
* Computes a value based only on alphanumeric characters in a string (i.e. ignores spaces, special chars)
* For example, " Arm A" would return same value as "Arm A" or "Arm  A "
*/
int RG::ReportGenerator::spacelessHash(string input){
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

/*stoolHash
* Hash function that prioritizes letters as coarse magnitude, then numbers as fine offset
* For example, DF-0091 would have large magnitude based on DF, then offset of 91 from that
* Ignores non-alphanumeric characters
*/
long RG::ReportGenerator::stoolHash(string input){
    long hashvalue = 0;
    int NUM_LETTERS = 26; int NUM_DIGITS = 10;
    char letters[NUM_LETTERS] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
                    't', 'u', 'v', 'w', 'x', 'y', 'z'};
    char numbers[NUM_DIGITS] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    int lettercount = 0; int placevalue = 1;
    for(int i = 0; i < input.length(); i++){ // hashvalue = (letter^3 + letter^3 + ...)
        for(int j = 0; j < NUM_LETTERS; j++){
            if(input[i] == letters[j]){ hashvalue += (j*j*j); lettercount++;}
        }
    }
    hashvalue = hashvalue * (lettercount * lettercount); // hashvalue = hashvalue * (#letters^2)
    for(int i = input.length()-1; i >= 0; i--){ //hashvalue += numeric value from stool ID
        for(int j = 0; j < NUM_DIGITS; j++){
            if(input[i] == numbers[j]){ hashvalue += (j*placevalue); placevalue = placevalue * 10;}
        }
    }
    return hashvalue;
}

/*extractMonth
* Returns the month (as an integer) as extracted from a date (string) of format m/d/y
*/
int RG::ReportGenerator::extractMonth(string date){
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
int RG::ReportGenerator::extractYear(string date){
    string delimiter = "/";
    try{
        int delimiter1 = date.find_last_of(delimiter);
        string year = date.substr((delimiter1+1), date.length());
        return stoi(year);
    } catch(std::exception){
        return 0; //exclude things with no/invalid date
    }
}

RG::ReportGenerator::ReportGenerator(){
    sheets = new RG::ReportSheets;
    sheets->bloodreport = new BR::BloodReport;
    sheets->tissuereport = new TR::TissueReport;
    sheets->stoolreport = new SR::StoolReport;
}

RG::ReportGenerator::~ReportGenerator(){
    if(filetype == RG::filetypes::blood){ delete sheets->bloodreport; sheets->bloodreport = NULL;}
    if(filetype == RG::filetypes::tissue){ delete sheets->tissuereport; sheets->tissuereport = NULL;}
    if(filetype == RG::filetypes::stool){ delete sheets->stoolreport; sheets->stoolreport = NULL;}
    for(int i = 0; i < timepointTracker.size(); i++){ delete timepointTracker.at(i); timepointTracker.at(i) = NULL;}
    for(int i = 0; i < timepointTotal.size(); i++){ delete timepointTotal.at(i); timepointTotal.at(i) = NULL;}
}