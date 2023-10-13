//
//  ContentView.swift
//  CHLDatabaseManager
//
//  Created by Kyle Thompson on 10/10/23.
//

import SwiftUI

struct ContentView: View {
    @State var filename1 = "Filename"
    @State var filename2 = "Filename"
    @State var output_filename = "data.txt"
    @State var output_path = ""
    @State var showFileChooser = false
    @State var csv_manager = CSVManager()
    @State var showConflicts = false
    @State var updateFlag = true
    
    var body: some View {
        VStack{
            HStack{
                Spacer()
                VStack{
                    Text("File Selections")
                    HStack{
                        Text("Data File 1:")
                        Text(filename1)
                        Button("Select File")
                        {
                            let panel = NSOpenPanel()
                            panel.allowsMultipleSelection = false
                            panel.canChooseDirectories = false
                            panel.canChooseFiles = true
                            if panel.runModal() == .OK {
                                self.filename1 = (panel.url?.relativePath ?? "none")
                            }
                        }
                    }
                    HStack{
                        Text("Data File 2:")
                        Text(filename2)
                        Button("Select File")
                        {
                            let panel = NSOpenPanel()
                            panel.allowsMultipleSelection = false
                            panel.canChooseDirectories = false
                            panel.canChooseFiles = true
                            if panel.runModal() == .OK {
                                self.filename2 = (panel.url?.relativePath ?? "none")
                            }
                        }
                    }
                    HStack{
                        Text("Generated File:")
                        Text(output_path + output_filename)
                        Button("Select Path"){
                            let panel = NSOpenPanel()
                            panel.allowsMultipleSelection = false
                            panel.canChooseFiles = false
                            panel.canChooseDirectories = true
                            if panel.runModal() == .OK {
                                self.output_path = (panel.url?.relativePath ?? "") + "/"
                            }
                        }
                    }
                }
                Spacer()
                VStack{
                    if (updateFlag){
                        HStack{
                            Text("Sorting: ")
                            Text(csv_manager.sorting_key)
                        }
                    }
                    Button("Location"){
                        csv_manager.sorting_key = "location"
                        updateFlag = false
                        updateFlag = true
                    }
                    Button("ID"){
                        csv_manager.sorting_key = "id"
                        updateFlag = false
                        updateFlag = true
                    }
                    Button("Name"){
                        csv_manager.sorting_key = "name"
                        updateFlag = false
                        updateFlag = true
                    }
                }
                Spacer()
            }
            
            Button("Combine Files"){
                if (!showConflicts){
                    csv_manager.filename1 = filename1
                    csv_manager.filename2 = filename2
                    csv_manager.output_filename = output_path + output_filename
                    csv_manager.setFileInfo()
                    csv_manager.beginCombineFiles()
                    csv_manager.getNumberDuplicates()
                    if (csv_manager.number_duplicates < 1){
                        csv_manager.saveDatabase()
                    }
                    else{
                        csv_manager.getDuplicateItem()
                        showConflicts = true
                    }
                }
            }
            
            if (showConflicts){
                Group{
                    HStack{
                        Text("Conflicts:")
                        Text(String(csv_manager.number_duplicates))
                    }
                    Text(csv_manager.duplicate_info)
                    HStack{
                        Button("Keep"){
                            csv_manager.duplicate_choice = true
                            csv_manager.handleDuplicateItem()
                            csv_manager.getNumberDuplicates()
                            if (csv_manager.number_duplicates > 0)
                            {
                                csv_manager.getDuplicateItem()
                                showConflicts = false
                                showConflicts = true
                            }
                            else
                            {
                                showConflicts = false
                                csv_manager.saveDatabase()
                            }
                            
                        }
                        Button("Remove"){
                            csv_manager.duplicate_choice = false
                            csv_manager.handleDuplicateItem()
                            csv_manager.getNumberDuplicates()
                            if (csv_manager.number_duplicates > 0)
                            {
                                csv_manager.getDuplicateItem()
                                showConflicts = false
                                showConflicts = true
                            }
                            else
                            {
                                showConflicts = false
                                csv_manager.saveDatabase()
                            }
                        }
                    }
                }
            }
        }
        //.frame(maxWidth: .infinity, maxHeight: .infinity)
    }
}

#Preview {
    ContentView()
}
