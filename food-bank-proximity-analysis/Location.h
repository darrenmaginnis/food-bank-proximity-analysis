#ifndef __LOCATION_H__
#define __LOCATION_H__

class Location
{
public:
	double Easting, Northing;
	Location(void);
	Location(double,double);
	~Location(void);
};


#endif //__LOCATION_H__