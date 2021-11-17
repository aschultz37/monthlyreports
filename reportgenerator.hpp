#include <iostream>
#include <fstream>
#include <iomanip>
#include "bloodreport.hpp"
#include "tissuereport.hpp"
#include "stoolreport.hpp"

/*reportgenerator.hpp
* This class assumes that an input .csv has standard format.
* The .csv should be a standard Blood/Tissue/Stool Processing sheet from BTIL Biospecimens.
* This class can extract and manipulate entries from a given month/year combination.
* Results can be displayed to the terminal or written to a .txt file.
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
            void writeReport(std::string outFileName);
            void sort(int option);

            void setFileType(int inFileType){ filetype = inFileType;}
            int getFileType(){ return filetype;}
            std::vector <RG::TimepointCount*> const &getTimepointTracker(){ return timepointTracker;}
        private:
            std::vector <std::string> fileLines;
            std::vector <RG::TimepointCount*> timepointTracker;
            RG::ReportSheets* sheets;
            int filetype;
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
    };
}