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
            void displayTimepointTracker();
            void writeReport(std::string outFileName);
            void sort(int option);

            void setFileType(int inFileType){ filetype = inFileType;}
            int getFileType(){ return filetype;}
            void setStudyNumber(std::string studynumberin){ studynumber = studynumberin;}
            std::string getStudyNumber(){ return studynumber;}
            std::vector <RG::TimepointCount*> const &getTimepointTracker(){ return timepointTracker;}
        private:
            std::vector <std::string> fileLines;
            std::vector <RG::TimepointCount*> timepointTracker;
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
            /*
            //list of studies
            std::vector <std::string> studyNums = 
                {"20028", 
                "17455", 
                "13325", 
                "18394", 
                "18634", 
                "20068", 
                "18617", 
                "20166", 
                "20153", 
                "20371", 
                "19672", 
                "93085"};
            //list of timepoints for each study (keyed to studyNums vector)
            std::vector <std::vector <std::string>> timepointsList = 
                {{"baseline", "c2d1", "c4d1", "eot", "recurrence"},
                {"c1d1", "c1d8", "c1d15", "c3d1", "eot", "c7d1", "co-c1d1", "co-c1d15", "co-eot"},
                {"s1", "s2", "s3", "s4", "s5"},
                {"baseline", "pre-op", "post-op", "final 3 months hp", "recurrence"},
                {"baseline", "1 year", "2 year", "3 year", "4 year", "5 year"},
                {"baseline", "c2d1", "c4d1", "post-op", "eot", "recurrence"},
                {"baseline", "on nac", "pre-op", "post-op"},
                {"baseline", "c1d1", "c4d1", "c7d1", "c8d1", "c9d1", "c10d1", "c13d1", "c14d1", "c16d1", "c19d1", "c22d1", "c25d1", "eot"},
                {"baseline", "c1d1", "c4d1", "c7d1", "c8d1", "c9d1", "c10d1", "c13d1", "c14d1", "c16d1", "c19d1", "c22d1", "c25d1", "eot"},
                {"baseline", "c2d1", "c3d1", "c4d1", "c5d1", "c6d1", "pre-op", "eot", "recurrence"},
                {},
                {"s1", "s2", "s3", "s4", "s5"}};*/
    };
}