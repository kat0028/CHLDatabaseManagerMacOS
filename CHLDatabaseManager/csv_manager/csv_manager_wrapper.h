//
//  csv_manager_wrapper.h
//  CHLDatabaseManager
//
//  Created by Kyle Thompson on 10/10/23.
//

#ifndef csv_manager_wrapper_h
#define csv_manager_wrapper_h

#import <Foundation/Foundation.h>

@interface CSVManagerWrapper : NSObject

-(void) initWrapper;

-(void) setFileInfo: (NSString *) filename1 filename2: (NSString *) filename2 output_filename: (NSString *) output_filename;

-(void) shutdownWrapper;

-(void) beginCombineFiles;

-(int) getNumberDuplicates;

-(NSString *) getDuplicateItem;

-(void) handleDuplicateItem: (bool) choice;

-(void) saveDatabase: (NSString *) key;

@end

#endif /* csv_manager_wrapper_h */
