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

#include "Stringify.h"
#include <cstring>

std::string Stringify::Int(int x) {
    std::ostringstream o;

    o << x;

    return o.str();
}

std::string Stringify::Char(char* x) {
    std::string o = x;

    return o;
}

std::string Stringify::Float(float x) {
    std::ostringstream o;

    o << x;

    return o.str();
}

std::string Stringify::Double(double x) {
    std::ostringstream o;

    o << x;

    return o.str();
}

int Stringify::toInt(const std::string &String) {
    if(String == "") return 0;

    int X;
    std::stringstream strStream(String);

    strStream >> X;

    return X;
}

float Stringify::toFloat(const std::string &String) {
    if(String == "") return 0;

    float X;
    std::stringstream strStream(String);

    strStream >> X;

    return X;
}

double Stringify::toDouble(const std::string &String) {
    if(String == "") return 0;

    double X;
    std::stringstream strStream(String);

    strStream >> X;

    return X;
}

std::vector<std::string> Stringify::explode(std::string str, const std::string &separator) {
    char* cstr = new char[str.length() + 1];
    memcpy(cstr, str.c_str(), str.length() + 1);
    char* pos = strtok(cstr, separator.c_str());

    std::vector<std::string> Results;
    while(pos){
        Results.push_back(std::string(pos));
        pos = strtok(nullptr, separator.c_str());;
    }
    delete[] cstr;
    return Results;
}
