//
//  csv_manager.cpp
//  CHLDatabaseManager
//
//  Created by Kyle Thompson on 10/10/23.
//

#include "csv_manager.hpp"

CSVManager::CSVManager()
{
    
}

CSVManager::~CSVManager()
{
    // Do Nothing
}

void CSVManager::setFileInfo(std::string filename1, std::string filename2, std::string output_filename)
{
    this->filename1 = filename1;
    this->filename2 = filename2;
    this->output_filename = output_filename;
}

void CSVManager::beginCombineFiles()
{
    std::string line;
    std::vector<std::string> line_data;
    ItemData item;

    std::ifstream input_file;
    input_file.open(filename1);
    std::string time1;
    getline(input_file, line);
    line_data = split(line, ',');
    time1 = line_data.at(0);
    
    while (!input_file.eof())
    {
        getline(input_file, line);
        if (line.empty())
        {
            continue;
        }
        line_data = split(line, ',');
        item.id = line_data.at(0);
        item.location = line_data.at(1);
        item.name = line_data.at(2);
        database.push_back(item);
    }
    input_file.close();
    
    input_file.open(filename2);
    std::string time2;

    getline(input_file, line);
    line_data = split(line, ',');
    time2 = line_data.at(0);
    while (!input_file.eof())
    {
        getline(input_file, line);
        if (line.empty())
        {
            continue;
        }
        line_data = split(line, ',');
        item.id = line_data.at(0);
        item.location = line_data.at(1);
        item.name = line_data.at(2);
        database.push_back(item);
    }
    input_file.close();
    
    removeInternalDuplicates(database);
    sortPartialMatches(database, duplicate_buffer);

    if (time1>time2)
    {
        output_timestamp = time1;
    }
    else
    {
        output_timestamp = time2;
    }
}

void CSVManager::removeInternalDuplicates(std::vector<ItemData> &dataset)
{
    std::vector<ItemData> buffer;
    ItemData item;

    for (int i = 0; i < dataset.size(); i++)
    {
        item = dataset.at(i);
        if (!checkContains(buffer, item))
        {
            buffer.push_back(item);
        }
    }
    dataset.clear();
    dataset = buffer;
}

void CSVManager::sortPartialMatches(std::vector<ItemData> &dataset, std::vector<ItemData> &partial_matches)
{
    std::vector<ItemData> buffer1;
    std::vector<ItemData> buffer2;
    ItemData item;

    for (int i = 0; i < dataset.size(); i++)
    {
        item = dataset.at(i);
        if (softCheck(dataset, item))
        {
            buffer2.push_back(item);
        }
        else
        {
            buffer1.push_back(item);
        }
    }

    dataset.clear();
    partial_matches.clear();
    dataset = buffer1;
    partial_matches = buffer2;
}

std::vector<std::string> CSVManager::split(const std::string &s, char delim)
{
    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string item;

    while (getline(ss, item, delim))
    {
        result.push_back(item);
    }

    return result;
}

bool CSVManager::checkContains(std::vector<ItemData> dataset, ItemData item)
{
    for (int i = 0; i < dataset.size(); i++)
    {
        if (item == dataset.at(i))
        {
            return true;
        }
    }
    return false;
}

bool CSVManager::softCheck(std::vector<ItemData> dataset, ItemData item)
{
    for (int i = 0; i < dataset.size(); i++)
    {
        if ((dataset.at(i).id == item.id || dataset.at(i).location == item.location || dataset.at(i).name == item.name) && !(dataset.at(i) == item))
        {
            return true;
        }
    }
    return false;
}

int CSVManager::getNumberDuplicates()
{
    return int(duplicate_buffer.size());
}

std::string CSVManager::getDuplicateItem()
{
    std::string output = duplicate_buffer.at(0).location + "," + duplicate_buffer.at(0).name + "," + duplicate_buffer.at(0).id;
    return output;
}

void CSVManager::handleDuplicateItem(bool choice)
{
    ItemData item;
    item = duplicate_buffer.at(0);
    if (choice)
    {
        database.push_back(item);
    }

    std::vector<ItemData> buffer; 
    for (int i = 1; i < duplicate_buffer.size(); i++)
    {
        buffer.push_back(duplicate_buffer.at(i));
    }

    duplicate_buffer.clear();
    duplicate_buffer = buffer;
}

void CSVManager::sortDatabase(std::string key, std::string filename) 
{
    std::ifstream input_file;
    std::ofstream output_file;
    //std::string filename = "../data.txt";
    std::string holding_filename = "temp.txt";
    std::vector<ItemData> data_vector;
    data_vector.clear();
    ItemData data;

    input_file.clear();
    output_file.clear();

    input_file.open(filename);
    std::string time_buffer;

    getline(input_file, time_buffer);
    std::vector<std::string> temp_buffer;
    temp_buffer = split(time_buffer, ',');
    time_buffer = temp_buffer.at(0);

    std::string line;
    std::vector<std::string> line_data;

    data_vector.clear();
    while (!input_file.eof())
    {
        getline(input_file, line);
        if (line.empty())
        {
            continue;
        }
        line_data.clear();
        line_data = split(line, ',');
        data.id = line_data.at(0);
        data.location = line_data.at(1);
        data.name = line_data.at(2);
        data_vector.push_back(data);
    }

    input_file.close();

    if (key=="location")
    {
        std::sort(data_vector.begin(), data_vector.end(), compareLocation);
    }
    else if(key=="name")
    {
        std::sort(data_vector.begin(), data_vector.end(), compareName);
    }
    else if(key=="id")
    {
        std::sort(data_vector.begin(), data_vector.end(), compareId);
    }

    output_file.open(filename, std::ofstream::trunc);
    output_file << time_buffer + ",\n";

    for (int i = 0; i < data_vector.size(); i++)
    {
        line = "";
        line += data_vector.at(i).id + ",";
        line += data_vector.at(i).location + ",";
        line += data_vector.at(i).name + ",\n";
        output_file << line;
    }

    data_vector.clear();
    output_file.close();

    //updateTimeStamp();

    //return "";
}

void CSVManager::writeDatabase(std::string filename)
{
    std::ofstream file;
    file.open(filename, std::ofstream::trunc);
    file << output_timestamp + ",\n";
    std::string line;
    for (int i = 0; i < database.size(); i++)
    {
        line = "";
        line += database.at(i).id + ",";
        line += database.at(i).location + ",";
        line += database.at(i).name + ",\n";
        file << line;
    }

    file.close();
}

void CSVManager::saveDatabase(std::string key)
{
    writeDatabase(output_filename);
    sortDatabase(key, output_filename);
}
