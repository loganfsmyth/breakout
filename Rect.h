#ifndef INCLUDED_RECT_H
#define INCLUDED_RECT_H

#include <stdio.h>

#define OVERLAP_SW	1
#define OVERLAP_SE	2
#define OVERLAP_NW	4
#define OVERLAP_NE	8


class Rect{
	
	private:
		double x, y, w, h;
	public:
		Rect(double x,double ,double w,double h);
		bool contains(Rect* rect);
		bool containsPoint(double px,double py);
		double getX();
		double getY();
		double getW();
		double getH();
	
	
		//does the specified location in "this" overlap rect 
		bool nOverlap(Rect* rect);
		bool neOverlap(Rect* rect);
		bool eOverlap(Rect* rect);
		bool seOverlap(Rect* rect);
		bool sOverlap(Rect* rect);
		bool swOverlap(Rect* rect);
		bool wOverlap(Rect* rect);
		bool nwOverlap(Rect* rect);
	
		double getNOverlap(Rect* rect);
		double getSOverlap(Rect* rect);
		double getEOverlap(Rect* rect);
		double getWOverlap(Rect* rect);
	
		void display();
};

#endif
