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

//
// Created by rafael on 22/11/16.
// from http://www.lazyfoo.net/tutorials/SDL/23_advanced_timers/index.php
//

#ifndef GAME_TIMER_H
#define GAME_TIMER_H


class Timer {
public:
    //Initializes variables
    Timer();

    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();

    //Gets the timer's time
    unsigned getTicks();

    //Checks the status of the timer
    bool isStarted();
    bool isPaused();

private:
    //The clock time when the timer started
    unsigned mStartTicks;

    //The ticks stored when the timer was paused
    unsigned mPausedTicks;

    //The timer status
    bool mPaused;
    bool mStarted;
};


#endif //GAME_TIMER_H
