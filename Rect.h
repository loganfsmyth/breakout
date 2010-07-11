#ifndef INCLUDED_RECT_H
#define INCLUDED_RECT_H

#include <stdio.h>

#define OVERLAP_SW	1
#define OVERLAP_SE	2
#define OVERLAP_NW	4
#define OVERLAP_NE	8


class Rect{
	
	private:
		int x, y, w, h;
	public:
		Rect(int x,int y,int w,int h);
		bool contains(Rect* rect);
		bool containsPoint(int px,int py);
		int getX();
		int getY();
		int getW();
		int getH();
	
	
		//does the specified location in "this" overlap rect 
		bool nOverlap(Rect* rect);
		bool neOverlap(Rect* rect);
		bool eOverlap(Rect* rect);
		bool seOverlap(Rect* rect);
		bool sOverlap(Rect* rect);
		bool swOverlap(Rect* rect);
		bool wOverlap(Rect* rect);
		bool nwOverlap(Rect* rect);
	
		int getNOverlap(Rect* rect);
		int getSOverlap(Rect* rect);
		int getEOverlap(Rect* rect);
		int getWOverlap(Rect* rect);
	
		void display();
};

#endif
