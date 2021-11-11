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
        printf("PN\tArm\tVisit\tOncID\tStudyID\tRec.\tDate\n");
        for(int i = 0; i < sheets->bloodreport->getSortedLines().size(); i++){
            cout << sheets->bloodreport->getSortedLines().at(i)->PN << '\t';
            cout << sheets->bloodreport->getSortedLines().at(i)->studyArm << '\t';
            cout << sheets->bloodreport->getSortedLines().at(i)->visit << '\t';
            cout << sheets->bloodreport->getSortedLines().at(i)->oncID << '\t';
            cout << sheets->bloodreport->getSortedLines().at(i)->subjectID << '\t';
            cout << sheets->bloodreport->getSortedLines().at(i)->received << '\t';
            cout << sheets->bloodreport->getSortedLines().at(i)->date << '\n';
        }
    }
    else if(filetype == RG::filetypes::tissue){
        for(int i = 0; i < sheets->tissuereport->getSortedLines().size(); i++){
            cout << sheets->tissuereport->getSortedLines().at(i) << '\n';
        }
    }
    else if(filetype == RG::filetypes::stool){
        for(int i = 0; i < sheets->stoolreport->getSortedLines().size(); i++){
            cout << sheets->stoolreport->getSortedLines().at(i) << '\n';
        }
    }
}

/*writeReport
* Writes the resulting/sorted list to txt file
*/
void RG::ReportGenerator::writeReport(std::string outFileName){
    ofstream outfile; outfile.open(outFileName);
    if(filetype == RG::filetypes::blood){
        for(int i = 0; i < sheets->bloodreport->getSortedLines().size(); i++){
            outfile << sheets->bloodreport->getSortedLines().at(i) << '\n';
        }
    }
    else if(filetype == RG::filetypes::tissue){
        for(int i = 0; i < sheets->tissuereport->getSortedLines().size(); i++){
            outfile << sheets->tissuereport->getSortedLines().at(i) << '\n';
        }
    }
    else if(filetype == RG::filetypes::stool){
        for(int i = 0; i < sheets->stoolreport->getSortedLines().size(); i++){
            outfile << sheets->stoolreport->getSortedLines().at(i) << '\n';
        }
    }
    outfile.close();
}

/*sort
* Sorts by option: 1) PN; 2) OncID; 3) Subject ID; 4) Timepoint; 5) Date
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
            timeSort();
            break;
        case 5:
            dateSort();
            break;
    }
}

/*pnSort
* Sorts alphabetically by PN
*/
void RG::ReportGenerator::pnSort(){
    if(filetype == RG::filetypes::blood){

    }
    else if(filetype == RG::filetypes::tissue){

    }
    else if(filetype == RG::filetypes::stool){

    }
}

/*oncSort
* Sorts numerically by Onc ID
*/
void RG::ReportGenerator::oncSort(){
    if(filetype == RG::filetypes::blood){

    }
    else if(filetype == RG::filetypes::tissue){

    }
    else if(filetype == RG::filetypes::stool){

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
                if(stoi(sheets->bloodreport->getSortedLines().at(j)->subjectID) < stoi(sheets->bloodreport->getSortedLines().at(min)->subjectID)){
                    min = j;
                }
                sheets->bloodreport->swapSortedLines(i,min);
            }
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
                if(stoi(sheets->tissuereport->getSortedLines().at(j)->subjectID) < stoi(sheets->tissuereport->getSortedLines().at(min)->subjectID)){
                    min = j;
                }
                sheets->tissuereport->swapSortedLines(i,min);
            }
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
                if(stoi(sheets->stoolreport->getSortedLines().at(j)->subjectID) < stoi(sheets->stoolreport->getSortedLines().at(min)->subjectID)){
                    min = j;
                }
                sheets->stoolreport->swapSortedLines(i,min);
            }
        }
    }
}

/*timeSort
* Groups unique timepoints together
* TODO: Sorts from lowest timepoint to highest timepoint; need to have list of priorities since some similar
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
                    if(timepoints.at(j).compare(sheets->bloodreport->getFilteredLines().at(i)->visit) == 0){ found = true;}
                }
                if(!found){ timepoints.push_back(sheets->bloodreport->getFilteredLines().at(i)->visit);}
            }
            else timepoints.push_back(sheets->bloodreport->getFilteredLines().at(i)->visit);
        }
        //create vector for each unique timepoint & fill w/ each matching entry
        vector <vector<BR::EntryData*>> timepointVecs(timepoints.size());
        for(int i = 0; i < sheets->bloodreport->getFilteredLines().size(); i++){
            for(int j = 0; j < timepointVecs.size(); j++){
                if(sheets->bloodreport->getFilteredLines().at(i)->visit.compare(timepoints.at(j)) == 0){
                    timepointVecs.at(j).push_back(sheets->bloodreport->getFilteredLines().at(i));
                }
            }
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
                    if(timepoints.at(j).compare(sheets->tissuereport->getFilteredLines().at(i)->visit) == 0){ found = true;}
                }
                if(!found){ timepoints.push_back(sheets->tissuereport->getFilteredLines().at(i)->visit);}
            }
            else timepoints.push_back(sheets->tissuereport->getFilteredLines().at(i)->visit);
        }
        //create vector for each unique timepoint & fill w/ each matching entry
        vector <vector<TR::EntryData*>> timepointVecs(timepoints.size());
        for(int i = 0; i < sheets->tissuereport->getFilteredLines().size(); i++){
            for(int j = 0; j < timepointVecs.size(); j++){
                if(sheets->tissuereport->getFilteredLines().at(i)->visit.compare(timepoints.at(j)) == 0){
                    timepointVecs.at(j).push_back(sheets->tissuereport->getFilteredLines().at(i));
                }
            }
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
                    if(timepoints.at(j).compare(sheets->stoolreport->getFilteredLines().at(i)->visit) == 0){ found = true;}
                }
                if(!found){ timepoints.push_back(sheets->stoolreport->getFilteredLines().at(i)->visit);}
            }
            else timepoints.push_back(sheets->stoolreport->getFilteredLines().at(i)->visit);
        }
        //create vector for each unique timepoint & fill w/ each matching entry
        vector <vector<SR::EntryData*>> timepointVecs(timepoints.size());
        for(int i = 0; i < sheets->stoolreport->getFilteredLines().size(); i++){
            for(int j = 0; j < timepointVecs.size(); j++){
                if(sheets->stoolreport->getFilteredLines().at(i)->visit.compare(timepoints.at(j)) == 0){
                    timepointVecs.at(j).push_back(sheets->stoolreport->getFilteredLines().at(i));
                }
            }
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
                if(dateCompare(sheets->bloodreport->getSortedLines().at(j)->date, sheets->bloodreport->getSortedLines().at(min)->date) == -1){
                    min = j;
                }
                sheets->bloodreport->swapSortedLines(i,min);
            }
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
                if(dateCompare(sheets->tissuereport->getSortedLines().at(j)->date, sheets->tissuereport->getSortedLines().at(min)->date) == -1){
                    min = j;
                }
                sheets->tissuereport->swapSortedLines(i, min);
            }
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
                if(dateCompare(sheets->stoolreport->getSortedLines().at(j)->date, sheets->stoolreport->getSortedLines().at(min)->date) == -1){
                    min = j;
                }
                sheets->stoolreport->swapSortedLines(i, min);
            }
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
    //delete sheets; sheets = NULL;
}