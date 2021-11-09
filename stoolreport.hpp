#include <string>
#include <vector>

namespace SR{
    struct EntryData{
        std::string PN;
        std::string studyArm;
        std::string visit;
        std::string oncID;
        std::string subjectID;
        std::string stoolID;
        std::string received;
        std::string date;
    };

    class StoolReport{
        public:
            StoolReport();
            ~StoolReport(){ //delete structs from filteredLines and sortedLines

            }

        private:
            std::vector <SR::EntryData*> filteredLines;
            std::vector <SR::EntryData*> sortedLines;

            void importParser(std::string lineIn, SR::EntryData &fieldsOut);
    };
}