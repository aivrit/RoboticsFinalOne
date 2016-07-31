/*
 * Location.h
 *
 *  Created on: Jun 20, 2015
 *      Author: colman
 */

#ifndef Location_H_
#define Location_H_

class Location {
public:
	Location(int row, int col);
	virtual ~Location();
	int row, col;
};

#endif /* Location_H_ */
