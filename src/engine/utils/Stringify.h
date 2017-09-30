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

//==============================================================================
/*
	Utility class for converting to and from strings

	3/18/2014
    SDLTutorials.com
    Tim Jones
*/
//==============================================================================

#ifndef GAME_STRINGIFY_H
#define GAME_STRINGIFY_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Stringify {
public:
    static std::string Int(int x);
    static std::string Char(char* x);
    static std::string Float(float x);
    static std::string Double(double x);

    static int toInt(const std::string &String);
    static float toFloat(const std::string &String);
    static double toDouble(const std::string &String);

    static std::vector<std::string> explode(std::string str, const std::string &separator);
};

#endif
