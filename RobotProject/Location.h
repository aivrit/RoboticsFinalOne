/*
 * Location.h
 *
 *  Created on: Jun 20, 2015
 *      Author: colman
 */

#ifndef LOCATION_H_
#define LOCATION_H_

class Location {
public:
	Location(int row, int col);
	virtual ~Location();
	int row, col;
};

#endif /* LOCATION_H_ */
