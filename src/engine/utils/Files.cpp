/**
 * This file is part of NCC-GameMachine.
 * 
 * NCC-GameMachine is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * NCC-GameMachine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with NCC-GameMachine.  If not, see <http://www.gnu.org/licenses/>.
**/

#include "Files.h"
#include "Log.h"
#include "Stringify.h"

#include <sys/param.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

bool Files::setContents(std::string filename, std::string content, bool relative) {
    if(filename == "") return false;

    if(relative) filename = getCwd() + DIR_SEPARATOR  + filename;

    std::ofstream fileHandle;

    fileHandle.open(filename.c_str());
    if(!fileHandle.is_open()) return false;

    fileHandle << content;
    fileHandle.close();

    return true;
}

std::string Files::getContents(std::string filename, bool relative) {
    if(filename == "") return "";

    if(relative) filename = getCwd() + DIR_SEPARATOR  + filename;

    std::string Content;
    std::ifstream fileHandle;

    fileHandle.open(filename.c_str());

    if(fileHandle.is_open()) {
        while(fileHandle.good()) {
            std::string buffer;
            getline(fileHandle, buffer);
            if(buffer == "") continue;

            Content += buffer + "\n";
        }

        fileHandle.close();
    }

    return Content;
}

std::vector<std::string> Files::getFilesInFolder(std::string folder) {
    std::vector<std::string> List;

    std::string CWD  = getCwd();
    std::string Path = CWD;

    if(folder != "") Path += DIR_SEPARATOR  + folder;

#ifdef __APPLE__
    NSError* Error;

		NSString* PathNS			= [NSString stringWithUTF8String:Path.c_str()];
		NSArray* DirectoryContents	= [[NSFileManager defaultManager] contentsOfDirectoryAtPath:PathNS error:&Error];

		for(id File in DirectoryContents) {
			std::string Filename = Path + DIR_SEPARATOR  + [File cStringUsingEncoding:1];

			List.push_back(Filename);
		}
#else
    DIR* DirHandle = nullptr;
    dirent* fileHandle = nullptr;

    // Needs improved
    if((DirHandle = opendir(folder.c_str()))) {
        while((fileHandle = readdir(DirHandle))) {
            if(std::string(fileHandle->d_name) == ".")  continue;
            if(std::string(fileHandle->d_name) == "..") continue;

            std::string Filename = Path + fileHandle->d_name;
            List.push_back(Filename);
        }

        closedir(DirHandle);
    }else{
        Warning("Unable to open directory : %s", Path.c_str());
    }
#endif

    return List;
}

bool Files::fileExists(std::string filename){
    struct stat buffer;   
    return (stat (filename.c_str(), &buffer) == 0);
}

std::string Files::getCwd() {
    std::string CWD;

#ifdef __APPLE__
    NSString* ResourcePath = [[NSBundle mainBundle] resourcePath];
		CWD = [ResourcePath cStringUsingEncoding:1];
#else
    char buffer[MAXPATHLEN];
    CWD = (getcwd(buffer, MAXPATHLEN) ? std::string(buffer) : std::string(""));
#endif

    return CWD;
}

std::string Files::getFilenameWithoutExt(std::string filename) {
    std::vector<std::string> parts = Stringify::explode(filename, DIR_SEPARATOR);
    std::string newFilename = parts[parts.size() - 1];

    // To Do: filename could potentially have one or more dots
    parts		= Stringify::explode(newFilename, ".");
    newFilename	= parts[0];

    return newFilename;
}

std::string Files::getFilenameExt(std::string filename) {
    std::vector<std::string> parts = Stringify::explode(filename, ".");

    return (parts.size() <= 1 ? "" : parts[parts.size() - 1]);
}

