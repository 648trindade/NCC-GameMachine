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

#include "Defines.h"

Point::Point() : Point(0, 0, 0) {}
Point::Point(double x, double y) : Point(x, y, 0) {}
Point::Point(int x, int y) : Point((double)x, (double)y, 0) {}
Point::Point(SDL_Point p) : Point(p.x, p.y, 0) {}
Point::Point(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

Point Point::operator+ (const Point& b) const{
    return Point(x + b.x, y + b.y, z + b.z);
}

Point& Point::operator+= (const Point& b){
    x += b.x;
    y += b.y;
    z += b.z;
    return *this;
}

Point Point::operator- (const Point& b) const{
    return Point( x - b.x, y - b.y, z - b.z );
}

Point& Point::operator-= (const Point& b){
    x -= b.x;
    y -= b.y;
    z -= b.z;
    return *this;
}

double Point::vec2_dot(const Point& b){
    return x * b.x + y * b.y;
}

double Point::vec2_lenght(){
    return hypot(x, y);
}

double Point::vec3_dot(const Point& b){
    return x * b.x + y * b.y + z * b.z;
}

double Point::vec3_lenght(){
    return sqrt(x*x + y*y + z*z);
}

bool Point::operator== (const Point& b){
    return x == b.x && y == b.y && z == b.z;
}

bool Point::operator!= (const Point& b){
    return x != b.x || y != b.y || z != b.z;
}

Point Point::operator* (const double& b) const{
    return Point(x * b, y *b, z * b);
}

Point& Point::operator*= (const double& b){
    x *= b;
    y *= b;
    z *= b;
    return *this;
}

Point Point::operator/ (const double& b) const{
    return Point(x / b, y / b, z / b);
}

Point& Point::operator/= (const double& b){
    x /= b;
    y /= b;
    z /= b;
    return *this;
}

Point Point::operator* (const Point& b){
    return Point(x * b.x, y * b.y, z * b.z);
}

Point& Point::operator*= (const Point& b){
    x *= b.x;
    y *= b.y;
    z *= b.z;
    return *this;
}

Point Point::operator/ (const Point& b){
    return Point(x / b.x, y / b.y, z / b.z);
}

Point& Point::operator/= (const Point& b){
    x /= b.x;
    y /= b.y;
    z /= b.z;
    return *this;
}

Point Point::rotate_3d(Axis axis, double theta) const{
    double matrix[3][3] = {{1,0,0},{0,1,0},{0,0,1}};
    switch(axis){
        case X_AXIS:
            matrix[1][1] = cos(theta);
            matrix[1][2] = -sin(theta);
            matrix[2][1] = sin(theta);
            matrix[2][2] = cos(theta);
            break;
        case Y_AXIS:
            matrix[0][0] = cos(theta);
            matrix[0][2] = sin(theta);
            matrix[2][0] = -sin(theta);
            matrix[2][2] = cos(theta);
            break;
        case Z_AXIS:
            matrix[0][0] = cos(theta);
            matrix[0][1] = -sin(theta);
            matrix[1][0] = sin(theta);
            matrix[1][1] = cos(theta);
            break;
    }
    return Point(
        matrix[0][0]*x + matrix[0][1] * y + matrix[0][2] * z,
        matrix[1][0]*x + matrix[1][1] * y + matrix[1][2] * z,
        matrix[2][0]*x + matrix[2][1] * y + matrix[2][2] * z
    );
}

//================= Rect ======================

Rect operator+ (const Rect& a, const Point& b){
    return { a.x + (int)b.x, a.y + (int)b.y, a.w, a.h };
}

Rect& operator+= (Rect& a, const Point& b){
    a.x += (int)b.x;
    a.y += (int)b.y;
    return a;
}

Rect operator- (const Rect& a, const Point& b){
    return { a.x - (int)b.x, a.y - (int)b.y, a.w, a.h };
}

Rect& operator-= (Rect& a, const Point& b){
    a.x -= (int)b.x;
    a.y -= (int)b.y;
    return a;
}

Point rect_topleft(const Rect& r){
    return Point(r.x, r.y);
}

Point rect_center(const Rect& r){
    return Point(r.x + (r.w>>1), r.y + (r.h>>1));
}

bool operator<(const SDL_Rect& a, const SDL_Rect& b) {
    return (a.w * a.h) < (b.w * b.h);
}

SDL_Point operator-(SDL_Point const& a, SDL_Point const& b){
    return {a.x -b.x, a.y - b.y};
}