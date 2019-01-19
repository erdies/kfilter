#include <kapp.h>
#include "circuitout.h"

//Constructor
CircuitOut::CircuitOut(QWidget *parent=0 ) : QWidget(parent) {
}
CircuitOut::~CircuitOut(){

}

//-------------------------------------
//   Get the value from kfilter
//--------------------------------------
void CircuitOut::setvalues(double unit[] ){
	
	network = unit;
	
	setPalette( QPalette( QColor(255, 255, 255) ) );	
	// now unit is inner the class
	
	// Initialize Widgets
	init();
	place_connector();
	place(1);
	place(2);
	place(3);
	place(4);
	place(5);
	place(6);
	place(7);
	place(8);
	place_driver();

	  
}

//---------------------------------------------------
// Place the value of device if ShowValues is true
//---------------------------------------------------
void CircuitOut::place_value(int x, int y, const char *string){
	
	//str = string;
	
	if(ShowValues){
		QLabel *value=  new QLabel("value",this);		
		value->setText(string);
		value->setAutoResize(true);
		value->move(x,y);
	}

}

//-------------------------------
// Place the connector
//-------------------------------
void CircuitOut::place_connector(){

	place_xy(PixCornerLeftUp,LastX,Yinit);
	LastY += WDim/2;
	place_vert(PixCon);
	LastY += WDim;
	place_vert(PixCon);

	//LastY = WDim + Dim + Yinit;
	place_xy(PixCornerLeftDown,LastX,LastY ); 

	LastX += Dim;
	LastY = Yinit;
}
//-------------------------------
// Place the Driver pixamap
//-------------------------------
void CircuitOut::place_driver(){

	place_horizon(PixCon);
	place_xy(PixCornerRightUp,LastX,Yinit);
	LastY += Dim;
	place_vert(PixCon);
	LastY = WDim + Dim + Yinit;
	place_xy(PixDriver,LastX,LastY);
	LastY += WDim;
	
	place_vert(PixCon);
	place_xy(PixCornerRightDown,LastX,LastY ); 

//	place_xy(PixCornerLeftUp, LastX+20,LastY+20);
		
}

//----------------------------
// Place 1 to 6 columns
// ---------------------------
void CircuitOut::place(int col ){
	int n;
	QString *string =  new QString();
			  
	//adjust the column abstraction
	col=(col-1)*6;
	

	// Place horizon devices

	// place in series ( no capacitor )
	if(!network[2+col]){
		
		if(network[1+col]){
			place_horizon(PixR);
		}	
	
		if(network[3+col])
			place_horizon(PixL);
	}
	
	// place everyone in paralel (there is a capacitor)
	else{
		// place con3up, con3 down or con4
		place_wichcon(col);
		// put inductor if exists
		if(network[3+col]){
			place_horizon_up(PixL);
		}
		// put resitors if exists
		if(network[1+col])
			place_horizon_down(PixR);
		
		// put the capacitor (if exists)
		place_horizon(PixC);
		
		// place con3up, con3 down or con4
		place_wichcon(col);
	}


		if( network[4+col] || network[5+col] || network[6+col] ){
			// beauties
			place_con3_up();
			place_con3_down();

		
			// place the vertical  devices
			if(network[4+col])
				place_vert(PixR);
			else
				place_vert(PixCon);
	
			if(network[5+col])
				place_vert(PixC);
			else
				place_vert(PixCon);
	
			if(network[6+col])
				place_vert(PixL);
			else
				place_vert(PixCon);
		
			LastX+=Dim;
		}

	LastY=Yinit;
	
}

//-----------------------------------
// Place a Pixmap on XY cordinates
//-----------------------------------
void CircuitOut::place_xy(QPixmap *Pix, int x, int y){

	QLabel *dev =  new QLabel("dev1",this);		
	dev->setPixmap(*Pix);
	dev->setAutoResize(true);
	dev->move(x,y);


}

//--------------------------------------------
// Place a pixmap on rigth place in horizon
// -------------------------------------------
void CircuitOut::place_horizon(QPixmap *Pix){

	QLabel *dev =  new QLabel("dev1",this);		
	dev->setPixmap(*Pix);
	dev->setAutoResize(true);
	dev->move(LastX,LastY);

	place_bottom();

	LastX += Pix->width();

}

//-----------------------------------------------
// Place a pixmap up  and  in horizon
// -------------------------------------------
void CircuitOut::place_horizon_up(QPixmap *Pix){

	QLabel *dev1 =  new QLabel("dev1",this);		
	dev1->setPixmap(*PixCornerLeftUp);
	dev1->setAutoResize(true);
	// Move with offset to be up (- height)
	dev1->move(LastX - Pix->height(),LastY - Pix->height() );
		  
	QLabel *dev =  new QLabel("dev1",this);		
	dev->setPixmap(*Pix);
	dev->setAutoResize(true);
	dev->move(LastX,LastY - Pix->height() );

	QLabel *dev2 =  new QLabel("dev1",this);		
	dev2->setPixmap(*PixCornerRightUp);
	dev2->setAutoResize(true);
	dev2->move(LastX + Pix->width(),LastY - Pix->height() );


}

//-----------------------------------------------
// Place a pixmap down and  in horizon
// -------------------------------------------
void CircuitOut::place_horizon_down(QPixmap *Pix){

	QLabel *dev1 =  new QLabel("dev1",this);		
	dev1->setPixmap(*PixCornerLeftDown);
	dev1->setAutoResize(true);
	// Move with offset to be up (- height)
	dev1->move(LastX - Pix->height(),LastY + Pix->height() );
		  
	QLabel *dev =  new QLabel("dev1",this);		
	dev->setPixmap(*Pix);
	dev->setAutoResize(true);
	dev->move(LastX,LastY + Pix->height() );

	QLabel *dev2 =  new QLabel("dev1",this);		
	dev2->setPixmap(*PixCornerRightDown);
	dev2->setAutoResize(true);
	dev2->move(LastX + Pix->width(),LastY + Pix->height() );


}


// ------------------------------------
// Place a pixmap of a vert device
// ------------------------------------
void CircuitOut::place_vert(QPixmap *pix){
	
	
	QLabel *dev =  new QLabel("dev1",this);		
	dev->setPixmap(pix->xForm(*rot90) );
	dev->setAutoResize(true);
	
	dev->move(LastX,LastY);

	LastY+=WDim;

}

//--------------------------------------------
// Place a 3 way conection pixmap rotated up
// -------------------------------------------
void CircuitOut::place_con3_up(){
	
	QLabel *dev =  new QLabel("dev1",this);		
	dev->setPixmap(*PixCon3);
	dev->setAutoResize(true);
	dev->move(LastX,LastY);
	LastY+=Dim;

}


//--------------------------------------------
// Place a 3 way conection pixmap rotated down
// -------------------------------------------
void CircuitOut::place_con3_down(){
	
	QLabel *dev =  new QLabel("dev1",this);		
	dev->setPixmap( PixCon3->xForm(*rot180) );
	dev->setAutoResize(true);
	dev->move(LastX, LastY + 6*Dim);

}

//--------------------------------------------
// Place a 4 way conection pixmap 
// -------------------------------------------
void CircuitOut::place_con4(){
	
	QLabel *dev =  new QLabel("dev1",this);		
	dev->setPixmap( *PixCon4 );
	dev->setAutoResize(true);
	dev->move(LastX, LastY);

	place_bottom();	
	
	LastX += WDim /2;

}
// -------------------------------------------
//  Place a small _ on the botton of the pic
// -------------------------------------------
void CircuitOut::place_bottom(){

	QLabel *dev2 =  new QLabel("dev2",this);
	dev2->setPixmap(*PixCon);
	dev2->setAutoResize(true);
	dev2->move(LastX,LastY+7*Dim);


}
// ---------------------------------------------------
//  Decides if have to put con3up con3 down or con4
// ---------------------------------------------------
void CircuitOut::place_wichcon(int col){

// if theres resistor and inductor put a con4 (cap exists)
	if(network[3+col] && network[1+col]){
		place_con4();
	}
	else{
		// if just resistor con3down (cap exists)
		if(network[1+col]){
			place_horizon(PixCon3);
		}
		else{
			  // if just a inductor con3up (cap exists)
			if(network[3+col]){
				place_horizon(PixCon3Down);
			}
			// if really just a cap, con
			else{
				place_horizon(PixCon);
			}
		}
		
	}

}

//-----------------------
// Initialize widgets
// ----------------------
void CircuitOut::init(){

	rot90 =  new QWMatrix();
	rot180 =  new QWMatrix();
	rot270 =  new QWMatrix();
	
	rot90->rotate(90);
	rot180->rotate(180);
	rot270->rotate(270);

	QString path_r = locate ("data", "kfilter/pics/r.xpm");
	PixR = new QPixmap(path_r);
	QString path_c = locate ("data", "kfilter/pics/c.xpm");
	PixC = new QPixmap(path_c);
	QString path_l = locate ("data", "kfilter/pics/l.xpm");
	PixL = new QPixmap(path_l);
	QString path_con4 = locate ("data", "kfilter/pics/con4.xpm");
	PixCon4 = new QPixmap(path_con4);
	QString path_con = locate ("data", "kfilter/pics/con.xpm");
	PixCon  = new QPixmap(path_con);
	QString path_con3 = locate ("data", "kfilter/pics/con3.xpm");
	PixCon3 = new QPixmap(path_con3);
	PixCon3Down = new QPixmap(PixCon3->xForm(*rot180) );
	
	QString path_corner = locate ("data", "kfilter/pics/corner.xpm");
	PixCornerRightUp  = new QPixmap(path_corner);
	PixCornerRightDown = new QPixmap(PixCornerRightUp->xForm(*rot90));
	PixCornerLeftDown = new QPixmap(PixCornerRightDown->xForm(*rot90));
	PixCornerLeftUp  = new QPixmap(PixCornerLeftDown->xForm(*rot90));
	
	QString path_driversym = locate ("data", "kfilter/pics/driversym.xpm");
	PixDriver= new QPixmap(path_driversym);
	
	
	// Change basic Dimension if pict size  changes
	Dim = PixR->height();
	WDim = 2*Dim;
	HDim = Dim;

	// Initial Position of drawing
	Xinit=50;
	Yinit=50;

	LastX=Xinit;
	LastY=Yinit;
	
	// Show Values if true
	ShowValues = true;
}




