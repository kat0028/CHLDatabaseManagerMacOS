//
//  CSVManager.swift
//  CHLDatabaseManager
//
//  Created by Kyle Thompson on 10/10/23.
//

import Foundation

class CSVManager: NSObject, ObservableObject{
    private var csv_manager_wrapper = CSVManagerWrapper()
    @Published var filename1: String
    @Published var filename2: String
    @Published var output_filename: String
    
    @Published var number_duplicates: Int
    @Published var duplicate_info: String
    @Published var duplicate_choice: Bool
    
    @Published var sorting_key: String
    
    override init(){
        filename1 = "none.txt"
        filename2 = "none.txt"
        output_filename = "none.txt"
        number_duplicates = 0
        duplicate_info = ""
        duplicate_choice = false
        sorting_key = "location"
        csv_manager_wrapper.initWrapper()
        
        super.init()
    }
    
    deinit{
        csv_manager_wrapper.shutdownWrapper()
    }
    
    func setFileInfo(){
        csv_manager_wrapper.setFileInfo(filename1, filename2: filename2, output_filename: output_filename)
    }
    
    func beginCombineFiles(){
        csv_manager_wrapper.beginCombineFiles()
    }
    
    func getNumberDuplicates(){
        number_duplicates = Int(csv_manager_wrapper.getNumberDuplicates())
    }
 
    func getDuplicateItem(){
        duplicate_info = csv_manager_wrapper.getDuplicateItem()
    }
    
    func handleDuplicateItem(){
        csv_manager_wrapper.handleDuplicateItem(duplicate_choice)
    }
    
    func saveDatabase(){
        csv_manager_wrapper.saveDatabase(sorting_key);
    }
    
}
