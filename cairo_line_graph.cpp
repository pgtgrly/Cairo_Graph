#include <iostream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <cairo.h>
#include <math.h>
using namespace std;

void sort_coordinates (vector<float>& xcoordi,vector<float>& ycoordi){ //sorts coordinates according to x coordinate 
	int n = xcoordi.size();
	int i, j,temp;
   for (i = 0; i < n-1; i++) //bubble sort         
       for (j = 0; j < n-i-1; j++) 
           if (xcoordi[j] > xcoordi[j+1]){
            	temp=xcoordi[j];
           		xcoordi[j]=xcoordi[j+1];
           		xcoordi[j+1]=temp;
           		temp=ycoordi[j];
           		ycoordi[j]=ycoordi[j+1];
           		ycoordi[j+1]=temp;
           }	
}
float getmax(vector<float> vec){ //Gives maximum element of an array
	float max=vec[0];
	for(int i=1;i<vec.size();i++){
		if(vec[i]>max)
			max=vec[i];
	}
	return max;
}

void linegraph(vector<float> xcoordi, vector<float> ycoordi,int Xsize=540,int Ysize=540,int Margin_size=20) //gives linegraph for Ist Quadrant This acts as function of Pyplot api in MatPlotlib
{
	sort_coordinates(xcoordi,ycoordi);
	cairo_surface_t *surface;
    cairo_t *cr;
    surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, Xsize, Ysize);
    cr = cairo_create (surface);

	//Create white Background
	cairo_set_line_width (cr, 2);
	cairo_set_source_rgb (cr, 255, 255, 255);
	cairo_rectangle (cr, 0, 0,Xsize,Ysize);
	cairo_fill (cr);

	//Create axes. Acts as axes instance of artist class
	cairo_set_source_rgb (cr, 0, 0, 0);
	cairo_move_to (cr, Margin_size, 0);
	cairo_line_to (cr, Margin_size, Ysize);
	cairo_move_to (cr, 0, Ysize-Margin_size);
	cairo_line_to (cr, Xsize, Ysize-Margin_size);
	cairo_move_to (cr, Margin_size,Ysize-Margin_size);
	float origin_x=Margin_size;
	float origin_y=Ysize-Margin_size;
	float current_x=origin_x;
	float current_y=origin_y;
	float y_scaling_factor=(Ysize-2*Margin_size)/getmax(ycoordi); // these act like the transforms
	float x_scaling_factor=(Xsize-2*Margin_size)/getmax(xcoordi); // in the artist layer of matplotlib

	int i;
	// draw notches on axes. Acts as the tick instance in artist layer of MatPlotLib
	for(i=1;i<=10;i++){
		cairo_move_to(cr,current_x+(i*(Xsize-2*Margin_size)/10),current_y-5);
		cairo_line_to(cr,current_x+(i*(Xsize-2*Margin_size)/10),current_y+5);
		cairo_move_to(cr,current_x-5,current_y-(i*(Ysize-2*Margin_size)/10));
		cairo_line_to(cr,current_x+5,current_y-(i*(Ysize-2*Margin_size)/10));
		
		}
	current_x=origin_x;
	current_y=origin_y;

	//draw line graph. Acts as curve instance of artist layer in MatPlotLib
	for(i=0;i<xcoordi.size();i++)
	{
		cairo_move_to(cr,current_x,current_y);
		float new_x=origin_x+(xcoordi[i]*x_scaling_factor);
		float new_y=origin_y-(ycoordi[i]*y_scaling_factor);
		cout<<"line from "<<current_x<<","<<current_y<<" to "<<new_x<<","<<new_y<<endl;
		cairo_line_to(cr,new_x,new_y);
		cairo_arc (cr,new_x, new_y, 2, 0., 2 * M_PI);
		current_x=new_x;
		current_y=new_y;

	}

	cairo_stroke (cr);

    cairo_surface_write_to_png (surface, "graph.png");
    cairo_destroy (cr);
    cairo_surface_destroy (surface);

    


}


int main(){
	int num_coordi;
	vector <float> xcoordi,ycoordi;
	cout<<"\nEnter Number of coordinates: \n";
	cin>>num_coordi;
 	for (int i=0;i<num_coordi;i++){	
  		float temp;
  		cout<<"\nInput x coordinate number "<<i+1<<": ";
  		cin>>temp;
  		xcoordi.push_back(temp);
  		cout<<"\nInput y coordinate number "<<i+1<<": ";
  		cin>>temp;
  		ycoordi.push_back(temp);
  	}
 	linegraph(xcoordi,ycoordi);
 	
return 0;
}