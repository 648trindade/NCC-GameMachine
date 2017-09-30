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

#include <SDL2/SDL_timer.h>
#include "Timer.h"

Timer::Timer() {
    //Initialize the variables
    mStartTicks = 0;
    mPausedTicks = 0;
    mPaused = false;
    mStarted = false;
}

void Timer::start() {
    //Start the timer
    mStarted = true;
    //Unpause the timer
    mPaused = false;
    //Get the current clock time
    mStartTicks = SDL_GetTicks();
    mPausedTicks = 0;
}

void Timer::stop() {
    //Stop the timer
    mStarted = false;
    //Unpause the timer
    mPaused = false;
    //Clear tick variables
    mStartTicks = 0;
    mPausedTicks = 0;
}

void Timer::pause() {
    //If the timer is running and isn't already paused
    if( mStarted && !mPaused ) {
        //Pause the timer
        mPaused = true;
        //Calculate the paused ticks
        mPausedTicks = SDL_GetTicks() - mStartTicks;
        mStartTicks = 0;
    }
}

void Timer::unpause() {
    //If the timer is running and paused
    if( mStarted && mPaused ) {
        //Unpause the timer
        mPaused = false;
        //Reset the starting ticks
        mStartTicks = SDL_GetTicks() - mPausedTicks;
        //Reset the paused ticks
        mPausedTicks = 0;
    }
}

unsigned Timer::getTicks()
{
    //The actual timer time
    unsigned time = 0;
    //If the timer is running
    if( mStarted ) {
        //If the timer is paused
        if( mPaused )
            //Return the number of ticks when the timer was paused
            time = mPausedTicks;
        else
            //Return the current time minus the start time
            time = SDL_GetTicks() - mStartTicks;
    }
    return time;
}

bool Timer::isStarted() {
    //Timer is running and paused or unpaused
    return mStarted;
}

bool Timer::isPaused() {
    //Timer is running and paused
    return mPaused && mStarted;
}