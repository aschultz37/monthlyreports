#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctype.h>
#include "bloodreport.hpp"
#include "tissuereport.hpp"
#include "stoolreport.hpp"

/*reportgenerator.hpp
* This class assumes that an input .csv has standard format.
* The .csv should be a standard Blood/Tissue/Stool Processing sheet from BTIL Biospecimens.
* This class can extract and manipulate entries from a given month/year combination.
* Results can be displayed to the terminal or written to a .csv file.
*/

namespace RG{
    enum filetypes {blood = 1, tissue = 2, stool = 3};

    struct ReportSheets{ //blood, tissue, and stool sheets for each report
        BR::BloodReport* bloodreport;
        TR::TissueReport* tissuereport;
        SR::StoolReport* stoolreport;
    };

    struct TimepointCount{
        std::string timepoint;
        int count;
    };

    class ReportGenerator{
        public:
            ReportGenerator();
            ~ReportGenerator();
            
            void importCSV(std::string inFileName);
            int filterMonth(int month, int year);
            void copytoSort();
            void displayReport();
            void displayTimepointTracker();
            void totalTimepoints(int month, int year);
            void writeReport(std::string outFileName);
            void sort(int option);

            void setFileType(int inFileType){ filetype = inFileType;}
            int getFileType(){ return filetype;}
            void setStudyNumber(std::string studynumberin){ studynumber = studynumberin;}
            std::string getStudyNumber(){ return studynumber;}
            std::vector <RG::TimepointCount*> const &getTimepointTracker(){ return timepointTracker;}
            std::vector <RG::TimepointCount*> const &getTimepointTotal(){ return timepointTotal;}
        private:
            std::vector <std::string> fileLines;
            std::vector <RG::TimepointCount*> timepointTracker;
            std::vector <RG::TimepointCount*> timepointTotal;
            RG::ReportSheets* sheets;
            int filetype; std::string studynumber;
            int PNWIDTH = 5; int ARMWIDTH = 7; int VISITWIDTH = 16; int ONCWIDTH = 8; int STUDYWIDTH = 8; int RECWIDTH = 5; 
            int DATEWIDTH = 12; int SAMPLEWIDTH = 14; int BIOPSYWIDTH = 15; int STOOLWIDTH = 11;
            
            void pnSort();
            void oncSort();
            void subjectSort();
            void stoolSort();
            void timeSort();
            void dateSort();
            int dateCompare(std::string date1, std::string date2);
            int spacelessHash(std::string input);
            long stoolHash(std::string input);
            int extractMonth(std::string date);
            int extractYear(std::string date);
            bool validDate(std::string date, char delimiter);
    };
}