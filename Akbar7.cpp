//Program creates desired a number of incribed circles
#include "Simple_window.h"
#include "Graph.h"
#include <cstdlib>
#include <iostream>
#include <ctime>
#include<cmath>
#include<sstream>
using namespace Graph_lib;   //  graphics facilities
using namespace std;
int main(){
	srand(time(0));
	double Pi = 3.14159265359; //Pi value
	while(true){
		Point tl(100,100);           // top left  corner of window
		Simple_window win(tl,500,500,"Programming Assignment # 7");// window
		Circle c(Point(250,250),230); win.attach(c);int cycle;//create circle
		cout<<"\nEnter the round of inner circle generations: "; cin>>cycle;
		stringstream ss;ss<<"After "; ss<<cycle;
		ss<<((cycle!=1)?" rings generation":" ring generation");
		Text t(Point(200,495), ss.str()); win.attach(t);//prints text with cycle
		if(cycle<0){break;}//negative # breaks loop			//number
		int x=0; Vector_ref<Circle> vr; //stores and helps display the circle
		while(x!=cycle){//number of circles are generated randomly, limit is
			int radius=rand()%50+2;// 51 circles to promote larger circles
			double numcir= 230.0*(sin(Pi/radius)/(sin(Pi/radius)+1));
			//radius is calculated according to numcir
			for(int i=0; i<numcir;++i){//the folowing calculate angle,x&y value
				const double angle= (i) *2.0* asin(1.0*radius/ (230.0-radius)); //LITERALLY JUST NEEDED THIS!!
				const long double xval= (230.0-radius) * cos( angle ) + 250.0;
				const long double yval= (230.0-radius) * sin( angle ) + 250.0;
				vr.push_back(new Circle(Point(xval,yval),radius));
				int color=rand()%256; //color is random
				if(color>16&&color<53){color+=40;}//skips grey-white colors
				vr[vr.size()-1].set_color(color);win.attach(vr[vr.size()-1]);
			}
			x++; continue;
		}
		win.wait_for_button(); //gives control to next button
	}
	return 0;
}
