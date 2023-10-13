//
//  csv_manager.hpp
//  CHLDatabaseManager
//
//  Created by Kyle Thompson on 10/10/23.
//

#ifndef csv_manager_hpp
#define csv_manager_hpp

#include <stdio.h>

#include <iostream>
#include <fstream>

#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <string>
#include <string.h>

class CSVManager
{
public:
    struct ItemData{
        std::string id;
        std::string location;
        std::string name;

        bool operator ==(ItemData &a) const{
            return ((id == a.id) && (location == a.location) && (name == a.name));
        }
    };
    
    static bool compareLocation(const ItemData &a, const ItemData &b){
        return a.location < b.location;
    }

    static bool compareName(const ItemData &a, const ItemData &b){
        return a.name < b.name;
    }

    static bool compareId(const ItemData &a, const ItemData &b){
        return a.id < b.id;
    }
        
    CSVManager();
    ~CSVManager();
    
    void setFileInfo(std::string filename1, std::string filname2, std::string output_filename);
    void beginCombineFiles();
    int getNumberDuplicates();
    std::string getDuplicateItem();
    void handleDuplicateItem(bool choice);
    void saveDatabase(std::string key);

private:
    std::vector<ItemData> duplicate_buffer;
    std::vector<ItemData> file_buffer;
    std::vector<ItemData> database;
    std::string filename1;
    std::string filename2;
    std::string output_filename;
    
    int duplicate_count;
    std::string output_timestamp;
    
    std::vector<std::string> split(const std::string &s, char delim);
    bool checkContains(std::vector<ItemData> dataset, ItemData item);
    void removeInternalDuplicates(std::vector<ItemData> &dataset);
    bool softCheck(std::vector<ItemData> dataset, ItemData item);
    void sortPartialMatches(std::vector<ItemData> &dataset, std::vector<ItemData> &partial_matches);
    void sortDatabase(std::string key, std::string filename);
    void writeDatabase(std::string filename);
};

#endif /* csv_manager_hpp */
