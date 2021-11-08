#include <string>
#include <vector>

namespace BR{
    struct EntryData{
        std::string PN;
        std::string studyArm;
        std::string visit;
        std::string oncID;
        std::string subjectID;
        std::string received;
        std::string date;
    };

    class BloodReport{
        public:

        private:
            std::vector <BR::EntryData> filteredLines;
            std::vector <BR::EntryData> sortedLines;

            void importParser(std::string lineIn, BR::EntryData &fieldsOut);
    };
}