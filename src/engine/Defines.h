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

#ifndef GAME_DEFINES_H
#define GAME_DEFINES_H

#include <SDL2/SDL_rect.h>

#define DEBUG 1

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 1024

#define Rect  SDL_Rect
#define PointInRect(p,r) SDL_PointInRect(p,r)

class Point{
public:
    double x, y, z;
    Point();
    Point(double, double);
    Point(int, int);
    Point(SDL_Point);
    Point(double, double, double);
    
    Point operator+ (const Point&) const;
    Point& operator+= (const Point&);
    Point operator- (const Point&) const;
    Point& operator-= (const Point&);

    bool operator== (const Point&);
    bool operator!= (const Point&);
    
    Point operator* (const double& b) const;
    Point& operator*= (const double& b);
    Point operator/ (const double& b) const;
    Point& operator/= (const double& b);
    
    Point operator* (const Point& b);
    Point& operator*= (const Point& b);
    Point operator/ (const Point& b);
    Point& operator/= (const Point& b);
    
    double vec2_dot(const Point&);
    double vec2_lenght();
    double vec3_dot(const Point&);
    double vec3_lenght();

    enum Axis{
        X_AXIS,
        Y_AXIS,
        Z_AXIS
    };

    Point rotate_3d(Axis, double) const;

    operator SDL_Point() const { return SDL_Point{(int)x, (int)y}; }
};

inline double deg2rad(double val){ return val*M_PI / 180.0; }

Point rect_topleft(const Rect&);
Point rect_center(const Rect&);
Rect operator+ (const Rect&, const Point&);
Rect& operator+= (Rect&, const Point&);
Rect operator- (const Rect&, const Point&);
Rect& operator-= (Rect&, const Point&);

bool operator< (const Rect&, const Rect&);

SDL_Point operator-(SDL_Point const&, SDL_Point const&);

#endif //GAME_DEFINES_H
