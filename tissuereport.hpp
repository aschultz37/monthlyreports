#pragma once
#include <string>
#include <sstream>
#include <vector>

namespace TR{
    struct EntryData{
        std::string PN;
        std::string studyArm;
        std::string visit;//aka timepoint
        std::string oncID;
        std::string subjectID;
        std::string sampleType;
        std::string biopsyType;
        std::string date;
    };

    struct TimepointSampleCount{
        std::string timepoint;
        std::vector <std::string> sampleType;
        std::vector <int> count;
    };

    class TissueReport{
        public:
            TissueReport();
            ~TissueReport(); //delete structs from filteredLines and sortedLines
            
            std::vector <TR::EntryData*> const &getFilteredLines(){ return filteredLines;}
            std::vector <TR::EntryData*> const &getSortedLines(){ return sortedLines;}
            std::vector <TR::EntryData*> const &getParsedLines(){ return parsedLines;}
            std::vector <TR::TimepointSampleCount*> const &getSampleSortedLines(){ return sampleSortedLines;}

            void pushSortedLines(TR::EntryData* input){ sortedLines.push_back(input);}

            void importParser(std::string lineIn);
            int tissueMonthFilter(int month, int year);
            void sampleTypeSort();
            void copytoSortTissue();
            void clearSort();
            void clearFiltered();
            void clearSampleSortedLines();
            void swapSortedLines(int index1, int index2);
            bool isEmpty(int index);
        private:
            std::vector <TR::EntryData*> parsedLines;
            std::vector <TR::EntryData*> filteredLines;
            std::vector <TR::EntryData*> sortedLines;
            std::vector <TR::TimepointSampleCount*> sampleSortedLines;

            int extractMonth(std::string date);
            int extractYear(std::string date);
            int spacelessHash(std::string input);
    };
}