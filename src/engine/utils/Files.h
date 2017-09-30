//
// Created by rafael on 21/11/16.
//
//==============================================================================
/*
	Class for loading files and reading directories

	Note: To use iOS functions, set your file type to Objective-C++

	3/18/2014
    SDLTutorials.com
    Tim Jones
*/
//==============================================================================


#ifndef GAME_FILEMANAGER_H
#define GAME_FILEMANAGER_H

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>

#ifdef WIN32
    #define DIR_SEPARATOR "\\"
#else
    #define DIR_SEPARATOR "/"
#endif

class Files {
public:
    static bool setContents(std::string filename, std::string content, bool relative = true);

    static std::string getContents(std::string filename, bool relative = true);

    static std::vector<std::string> getFilesInFolder(std::string folder);

    static bool fileExists(std::string filename);

    static std::string getCwd();

    static std::string getFilenameWithoutExt(std::string filename);

    static std::string getFilenameExt(std::string filename);
};

#endif //GAME_FILEMANAGER_H
