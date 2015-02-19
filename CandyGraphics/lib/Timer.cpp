/*
 * Timer.cpp
 *
 *  Created on: 25/02/2012
 *      Author: kaseyo
 */

#include "Timer.h"

namespace candy {

sf::Clock Timer::_reloj;

Timer::Timer() {

}

Timer::~Timer() {

}

long int
Timer::getTimeElapsed(){
	return _reloj.GetElapsedTime().AsMilliseconds();
}

long int
Timer::Init(){
	return _reloj.Restart().AsMilliseconds();
}

} /* namespace candy */
