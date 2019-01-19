/***************************************************************************
                          kfilterview.cpp  -  description
                             -------------------
    begin                : Son Jul 28 17:34:18 CEST 2002
    copyright            : (C) 2002 by Martin Erdtmann
    email                : martin.erdtmann@gmx.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

// include files for Qt
#include <qprinter.h>
#include <qpainter.h>

// application specific includes
#include "kfilterview.h"
#include "kfilterdoc.h"
#include "kfilter.h"
#include "math.h"
#include "qfont.h"

KFilterView::KFilterView(QWidget *parent, const char *name) : QWidget(parent, name)
{
  setBackgroundMode(PaletteBase);
	Start = 125.6637061;
	Faktor = 1.047128548;
	m_Schall1 = 0;
	m_Schall2 = 0;
	m_Schall3 = 0;
	initXvalue();
}

KFilterView::~KFilterView()
{
}

KFilterDoc *KFilterView::getDocument() const
{
  KFilterApp *theApp=(KFilterApp *) parentWidget();

  return theApp->getDocument();
}

void KFilterView::print(QPrinter *pPrinter)
{
  QPainter printpainter;
  printpainter.begin(pPrinter);
	
  // TODO: add your printing code here

  printpainter.end();
}

void KFilterView::initXvalue()
{
	Xvalue[0] = Start;
	for (int i=1; i<150; i++)
	{
		Xvalue[i] = Xvalue[i-1] * Faktor;
	}
}

int KFilterView::XK(double x)
{
	double w = width();
	return (int)(w * 0.144764827 * log(x * 0.007957747155) );
	//f*1/20 -> f*1/(20*2*pi) Funktion verwendet Omega statt Frequenz,
	//"Breite* .."  bedeutet  Breite * 1/ln(20000/20) ..
}

int KFilterView::YScale(double x,int flag)   //Scaling on the currend window size in Y direction
{
	double H;
	H = height();
	if (flag==0)
	{
		return (int)(H/6 - x*H/60);
	}
	if (flag==1)
	{
		return (int)(5*H/6 - x*H/60);
	}
	else
	{
		return (int)(H/6 - x*H/60);
	}
}

void KFilterView::paintEvent( QPaintEvent * )

{
	//	printf ("Paint event!\n");
	KFilterDoc* mydoc = getDocument();
	QPainter mypainter;
	mypainter.begin(this);
	QPen pen;
	pen.setColor( cgrid );
	pen.setWidth( 1 );
	mypainter.setPen( pen );

	int i,j;
	for (i=30 ; i<=100; i=i+10)
	{
		j = XK(i*6.28318);
		mypainter.drawLine(j,0,j,height());
	}
	for (i=200 ; i<=1000; i=i+100)
	{
		j = XK(i*6.28318);
		mypainter.drawLine(j,0,j,height());
	}
	for (i=2000 ; i<=10000; i=i+1000)
	{
		j = XK(i*6.28318);
		mypainter.drawLine(j,0,j,height());
	}

	for (i=1;i<=30;i++)
	{
		if ((i!=5)|(i!=10)|(i!=15)|(i!=20)|(i!=25)|(i!=30))
		{
			mypainter.drawLine(0,i*height()/30,width(),i*height()/30);
		}
	}
	pen.setColor( yellow );
	pen.setStyle( DotLine );
	mypainter.setPen( pen );
	for (i=1;i<=5;i++)
	{
		mypainter.drawLine(0,i*height()/6,width(),i*height()/6);
	}
	pen.setColor( black );
	pen.setStyle( SolidLine );
	mypainter.setPen( pen );

	pen.setColor( white );
	pen.setStyle( DotLine );
	mypainter.setPen( pen );
	mypainter.drawLine(0,height()/6,width(),height()/6);

	/////////////////////////// Linien werden gezeichnet

  for (int count=0;count<4;count++)
	{
		if(mydoc->Sound(count))
		{
			pen.setColor( cpressure );
			pen.setStyle( SolidLine );
			mypainter.setPen( pen );
			mypainter.moveTo(XK(Xvalue[0]),YScale(mydoc->m_doubleXContainer[count][0],0));
			for (i=1; i<150; i++)
			{
				mypainter.lineTo(XK(Xvalue[i]),YScale(mydoc->m_doubleXContainer[count][i],0));
			}
		}
		if(mydoc->Impedance(count))
		{
			pen.setColor( cimpedance );
			pen.setStyle( DotLine );
			mypainter.setPen( pen );
			mypainter.moveTo(XK(Xvalue[0]),YScale(mydoc->m_doubleXContainer[count][0],1));
			for (i=1; i<150; i++)
			{
				mypainter.lineTo(XK(Xvalue[i]),YScale(mydoc->m_doubleXContainer[count][i],1));
			}
		}
	}
	if(mydoc->PressureSummary())
	{
		pen.setColor( cpressureS );
		pen.setStyle( SolidLine );
		mypainter.setPen( pen );
		mypainter.moveTo(XK(Xvalue[0]),YScale(mydoc->m_doubleXContainer[0][0],0));
		for (i=1; i<150; i++)
		{
			mypainter.lineTo(XK(Xvalue[i]),YScale(mydoc->m_doubleXContainer[0][i],0));
		}
	}

	if(mydoc->PressureScalarSummary())
	{
		pen.setColor( cscalarpressureS );
		pen.setWidth( 2 ),pen.setStyle( SolidLine );
		mypainter.setPen( pen );
		mypainter.moveTo(XK(Xvalue[0]),YScale(mydoc->m_doubleXContainer[0][0],0));
		for (i=1; i<150; i++)
		{
			mypainter.lineTo(XK(Xvalue[i]),YScale(mydoc->m_doubleXContainer[0][i],0));
		}
	}

	if(mydoc->ImpedanceSummary())
	{
		pen.setColor( cimpedanceS );
		pen.setWidth(1),pen.setStyle( DotLine );
		mypainter.setPen( pen );
		mypainter.moveTo(XK(Xvalue[0]),YScale(mydoc->m_doubleXContainer[0][0],1));
		for (i=1; i<150; i++)
		{
			mypainter.lineTo(XK(Xvalue[i]),YScale(mydoc->m_doubleXContainer[0][i],1));
		}
	}
	/////////////////////////// Ende von Linien

	pen.setColor( lightGray );
	QFont font("times", 10 );
	mypainter.setPen( pen );
	mypainter.setFont( font );

	mypainter.drawText(XK(80*6.28),50*height()/63,"100 Hz");
	mypainter.drawText(XK(800*6.28),50*height()/63,"1 kHz");
	mypainter.drawText(XK(8000*6.28),50*height()/63,"10 kHz");
	mypainter.drawText(5,100*height()/625,  "0 dB");
	mypainter.drawText(1,200*height()/610,"-10 dB");
	mypainter.drawText(1,300*height()/605,"-20 dB");
	mypainter.drawText(1,400*height()/605,"10 Ohm");
	mypainter.drawText(1,500*height()/605,"0 Ohm");

	mypainter.end();
}

/** gives back the gridcolor */
QColor& KFilterView::gridColor()
{
	return cgrid;
}
/** sets the gridcolor */
void KFilterView::setGridColor(QColor& color)
{
	cgrid = color;
}

/** gives back the pressurecolor */
QColor& KFilterView::pressureColor()
{
	return cpressure;
}
/** sets the pressurecolor */
void KFilterView::setPressureColor(QColor& color)
{
	cpressure = color;
}

/** gives back the impedancecolor */
QColor& KFilterView::impedanceColor()
{
	return cimpedance;
}
/** sets the impedancecolor */
void KFilterView::setImpedanceColor(QColor& color)
{
	cimpedance = color;
}

/** gives back the pressuresummarycolor */
QColor& KFilterView::pressureSummaryColor()
{
	return cpressureS;
}
/** sets the pressuresummarycolor */
void KFilterView::setPressureSummaryColor(QColor& color)
{
	cpressureS = color;
}

/** gives back the impedancesummarycolor */
QColor& KFilterView::impedanceSummaryColor()
{
	return cimpedanceS;
}
/** sets the impedancesummarycolor */
void KFilterView::setImpedanceSummaryColor(QColor& color)
{
	cimpedanceS = color;
}

/** gives back the scalarpressuresummarycolor */
QColor& KFilterView::scalarPressureSummaryColor()
{
	return cscalarpressureS;
}
/** sets the scalarpressuresummarycolor */
void KFilterView::setScalarPressureSummaryColor(QColor& color)
{
	cscalarpressureS = color;
}
