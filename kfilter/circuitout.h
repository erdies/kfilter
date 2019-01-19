#include <qwidget.h>
#include <qdialog.h>
#include <qlabel.h>
#include <qpixmap.h>
#include <qwmatrix.h>
#include <qscrollview.h>
#include <qstring.h>
#include <kstddirs.h>

class CircuitOut : public QWidget {

  Q_OBJECT
	
	public:
		CircuitOut(QWidget *parent=0);
		virtual ~CircuitOut();
		void setvalues(double network[]);
	
	private:
	  double *network;
				
		// Basic dimension , in pixels. 
		int Dim; 
		// Width and Height of pictures
		int WDim, HDim; 
		int LastX, LastY;
		// Offset of circuit in window
		int Xinit, Yinit;
		
		// if True values of devices are shown
		bool ShowValues;
				  
		// Pixmaps of Circuit elements and visual aparatus
	   QPixmap *PixR,*PixC,*PixL,*PixCon4,*PixCon3, *PixCon3Up, *PixCon3Down, *PixCon,	*PixDriver;
		QPixmap *PixCornerRightUp, *PixCornerRightDown, *PixCornerLeftUp, *PixCornerLeftDown;
	
		// matrix to rotate pixmaps
		QWMatrix *rot90,*rot180, *rot270;
		 
		// Functions
		//
		//void resizeEvent( QResizeEvent* event );
		void init();
		void place_value(int x, int y, const char *string);
		void place(int col);
		void place_driver();
		void place_connector();
		void place_xy(QPixmap *Pix, int x, int y);
		void place_horizon(QPixmap *pix);
		void place_horizon_up(QPixmap *pix);
		void place_horizon_down(QPixmap *pix);
		void place_vert(QPixmap *pix);
		void place_con3_up();
		void place_con3_down();
		void place_con4();
		void place_bottom();
		void place_wichcon(int col);		
};										  
