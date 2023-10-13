//
//  csv_manager_wrapper.m
//  CHLDatabaseManager
//
//  Created by Kyle Thompson on 10/10/23.
//

#import <Foundation/Foundation.h>
#import "csv_manager_wrapper.h"
#import "csv_manager.hpp"

@implementation CSVManagerWrapper

CSVManager* csv_manager;

-(void) initWrapper
{
    if (csv_manager == nullptr)
    {
        csv_manager = new CSVManager();
    }
}

-(void) setFileInfo: (NSString *) filename1 filename2: (NSString *) filename2 output_filename: (NSString *) output_filename
{
    std::string filename1_cpp = std::string([filename1 UTF8String]);
    std::string filename2_cpp = std::string([filename2 UTF8String]);
    std::string output_filename_cpp = std::string([output_filename UTF8String]);
    csv_manager->setFileInfo(filename1_cpp, filename2_cpp, output_filename_cpp);
}

-(void) shutdownWrapper
{
    if (csv_manager != nullptr)
    {
        delete csv_manager;
        csv_manager = nullptr;
    }
}

-(void) beginCombineFiles
{
    csv_manager->beginCombineFiles();
}

-(int) getNumberDuplicates
{
    return csv_manager->getNumberDuplicates();
}

-(NSString *) getDuplicateItem
{
    std::string output;
    output = csv_manager->getDuplicateItem();
    
    return [NSString stringWithCString:output.c_str() encoding:NSUTF8StringEncoding];
}

-(void) handleDuplicateItem: (bool) choice
{
    csv_manager->handleDuplicateItem(choice);
}

-(void) saveDatabase: (NSString *) key
{
    std::string key_cpp = std::string([key UTF8String]);
    csv_manager->saveDatabase(key_cpp);
}

@end
