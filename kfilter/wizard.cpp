/***************************************************************************
wizard.cpp  -  description
-------------------
begin                : Sun Oct 1 2000
copyright            : (C) 2001 by Martin Erdtmann  /  Stefan Okrongli
email                : martin.erdtmann@gmx.de  /  s_okrongli@gmx.net
***************************************************************************/

/***************************************************************************
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
***************************************************************************/
#include "wizard.h"


Wizard::Wizard( QWidget* /*a_pqwidgetParent*/, const char* a_pcharName,
	driver* a_pdriverDriver0, driver* a_pdriverDriver1,
	driver* a_pdriverDriver2, driver* a_pdriverDriver3 )
{
	// screen 1 widgets
	m_pqcomboboxDriverComboBox = 0;
	m_pqcomboboxFilterComboBox = 0;
	m_pqcomboboxOrderComboBox = 0;
	m_pqlabelDriverLabel = 0;
	m_pqlabelFilterLabel = 0;
	m_pqlabelOrderLabel = 0;
	m_pqlabelStepLabel = 0;
	
	// screen 2 widgets
	m_pqcomboboxPositionComboBox = 0;
	m_pqlabelPositionLabel = 0;
	m_pqspinboxHightSpin = 0;
	m_pqspinboxLowSpin = 0;
	m_pqlabelHighSpinLabel = 0;
	m_pqlabelLowSpinLabel = 0;
	m_pqlabelStepLabel1 = 0;
	m_pqlabelQFactorLabel = 0;
	m_pqlineeditQ = 0;
	
	// screen 3 widgets
	m_pqcheckboxCorrection = 0;
	m_pqcheckboxOnly = 0;
	m_pqcheckboxCleanup = 0;
	m_pqlabelCorrectionLabel = 0;
	m_pqlabelOnlyLabel = 0;
	m_pqlabelCleanupLabel = 0;
	m_pqlabelStepLabel2 = 0;
	
	// screen widgets
	m_intCurrentDriver = 0;
	m_intCurrentObject = 0;
	m_intCurrentOrder = 0;
	m_intCurrentPosition = 0;
	m_intCurrentHipass = 400;
	m_intCurrentLowpass = 3000;
	m_boolCorrection = false;
	m_boolImpedanceOnly = false;
	m_boolCleanup = false;
	m_doubleCurrentQFactor = 0.7;
	
	m_pdriverDriver[ 0 ] = a_pdriverDriver0;
	m_pdriverDriver[ 1 ] = a_pdriverDriver1;
	m_pdriverDriver[ 2 ] = a_pdriverDriver2;
	m_pdriverDriver[ 3 ] = a_pdriverDriver3;
	
	setWFlags( WType_Modal );
	setGeometry( 300, 200, 410, 330 );
	setCaption( a_pcharName );
	this->setFixedSize( 410, 330 );
	m_intCurrent = 1;
	
	QGroupBox* pqgroupboxGroup = new QGroupBox( this );
	pqgroupboxGroup->setGeometry( 3, 0, 403, 148 );
	
	QLabel* pqlabelLabel = new QLabel( this );
	QString qstringPath = locate ("data", "kfilter/pics/wizard4.gif");
	pqlabelLabel->setPixmap( QPixmap( qstringPath ) );
	pqlabelLabel->setGeometry( 7, 4, 395, 140 );
	pqlabelLabel->show();
	
	KSeparator* pkseparatorSeparator = new KSeparator( this );
	pkseparatorSeparator->setGeometry( 5, 290, 399, 1 );
	
	m_pqpushbuttonButton[ 0 ] = new QPushButton(i18n("Next >>"),this);
	m_pqpushbuttonButton[ 0 ]->setGeometry( 340, 297, 60, 28 );
	QObject::connect( m_pqpushbuttonButton[ 0 ], SIGNAL(clicked() ), this, SLOT( slotNextButton() ) );
	
	m_pqpushbuttonButton[ 1 ] = new QPushButton(i18n("Cancel"),this);
	m_pqpushbuttonButton[ 1 ]->setGeometry( 260, 297, 60, 28 );
	m_pqpushbuttonButton[ 1 ]->show();
	QObject::connect( m_pqpushbuttonButton[ 1 ], SIGNAL(clicked() ), this, SLOT( slotPreviousButton() ) );
	
	qstringPath= locate ("data", "kfilter/pics/tux.gif");
	m_pqmovieMovie = new QMovie( (const char*)qstringPath );
	m_pqlabelTuxLabel = new QLabel(this);
	
	m_pqlabelTuxLabel->setMovie( *m_pqmovieMovie );
	m_pqlabelTuxLabel->setGeometry(250,190,120,100);
	m_pqlabelTuxLabel->show();
	
	InitializeScreen1();
}

Wizard::~Wizard()
{
	// tidy up
	ClearScreen1();
	ClearScreen2();
	ClearScreen3();
	
	for (int intI = 0; intI < 2; intI++ )
	{
		delete m_pqpushbuttonButton[ intI ];
	}
    m_pqlabelTuxLabel->setMovie( 0 );
	delete m_pqmovieMovie;
	delete m_pqlabelTuxLabel;
}

/** initialization for the first screen */
void Wizard::InitializeScreen1()
{
	m_pqcomboboxDriverComboBox = new QComboBox( false, this );
	m_pqcomboboxDriverComboBox->insertItem( i18n("Driver 1") );
	m_pqcomboboxDriverComboBox->insertItem( i18n("Driver 2") );
	m_pqcomboboxDriverComboBox->insertItem( i18n("Driver 3") );
	m_pqcomboboxDriverComboBox->insertItem( i18n("Driver 4") );
	m_pqcomboboxDriverComboBox->setCurrentItem( m_intCurrentDriver );
	m_pqcomboboxDriverComboBox->setGeometry( 140, 163, 90, 21 );
	m_pqcomboboxDriverComboBox->show();
	QObject::connect( m_pqcomboboxDriverComboBox, SIGNAL(activated(int) ), this, SLOT( slotGetCurrentDriver(int) ) );
	
	m_pqlabelDriverLabel = new QLabel( i18n("Choose Driver:"), this );
	m_pqlabelDriverLabel->setGeometry( 20, 163, 120, 21 );
	m_pqlabelDriverLabel->show();
	
	m_pqcomboboxFilterComboBox = new QComboBox( false, this );
	m_pqcomboboxFilterComboBox->insertItem( i18n("Highpass") );
	m_pqcomboboxFilterComboBox->insertItem( i18n("Lowpass") );
	m_pqcomboboxFilterComboBox->insertItem( i18n("Bandpass") );
	m_pqcomboboxFilterComboBox->setCurrentItem( m_intCurrentObject );
	m_pqcomboboxFilterComboBox->setGeometry( 140, 203, 90, 21 );
	m_pqcomboboxFilterComboBox->show();
	QObject::connect( m_pqcomboboxFilterComboBox, SIGNAL(activated(int) ), this, SLOT( slotGetCurrentObject(int) ) );
	
	m_pqlabelFilterLabel = new QLabel( i18n("Filter Type:"), this );
	m_pqlabelFilterLabel->setGeometry( 20, 203, 120, 21 );
	m_pqlabelFilterLabel->show();
	
	m_pqcomboboxOrderComboBox = new QComboBox( false, this );
	m_pqcomboboxOrderComboBox->insertItem( i18n("1.Order") );
	m_pqcomboboxOrderComboBox->insertItem( i18n("2.Order") );
	m_pqcomboboxOrderComboBox->insertItem( i18n("3.Order") );
	m_pqcomboboxOrderComboBox->insertItem( i18n("4.Order") );
	m_pqcomboboxOrderComboBox->setCurrentItem( m_intCurrentOrder );
	m_pqcomboboxOrderComboBox->setGeometry( 140, 243, 90, 21 );
	m_pqcomboboxOrderComboBox->show();
	QObject::connect( m_pqcomboboxOrderComboBox, SIGNAL(activated(int) ), this, SLOT( slotGetCurrentOrder(int) ) );
	
	m_pqlabelOrderLabel = new QLabel( i18n("Filter Order:"), this );
	m_pqlabelOrderLabel->setGeometry( 20, 243, 120, 21 );
	m_pqlabelOrderLabel->show();
	
	m_pqlabelStepLabel = new QLabel( this );
	QString qstringPath = locate ( "data", "kfilter/pics/step1.xpm" );
	m_pqlabelStepLabel->setPixmap( QPixmap( qstringPath ) );
	m_pqlabelStepLabel->setGeometry( 5, 295, 100, 30 );
	m_pqlabelStepLabel->show();

	m_pqlabelBubbleLabel = new QLabel( this );
	qstringPath = locate ( "data", "kfilter/pics/bubble1.gif" );
	m_pqlabelBubbleLabel->setPixmap( QPixmap( qstringPath ) );
	m_pqlabelBubbleLabel->setGeometry(320,150,80,100);
	m_pqlabelBubbleLabel->show();

}

/** uninitialization of the first screen */
void Wizard::ClearScreen1()
{
	if ( m_pqcomboboxDriverComboBox != 0 )
	{
		delete m_pqcomboboxDriverComboBox;
		m_pqcomboboxDriverComboBox = 0;
	}
	if ( m_pqcomboboxFilterComboBox != 0 )
	{
		delete m_pqcomboboxFilterComboBox;
		m_pqcomboboxFilterComboBox = 0;
	}
	if ( m_pqcomboboxOrderComboBox != 0 )
	{
		delete m_pqcomboboxOrderComboBox;
		m_pqcomboboxOrderComboBox = 0;
	}
	if ( m_pqlabelDriverLabel != 0 )
	{
		delete m_pqlabelDriverLabel;
		m_pqlabelDriverLabel = 0;
	}
	if ( m_pqlabelFilterLabel != 0 )
	{
		delete m_pqlabelFilterLabel;
		m_pqlabelFilterLabel = 0;
	}	
	if ( m_pqlabelOrderLabel != 0 )
	{
		delete m_pqlabelOrderLabel;
		m_pqlabelOrderLabel = 0;
	}
	if ( m_pqlabelStepLabel != 0 )
	{
		delete m_pqlabelStepLabel;
		m_pqlabelStepLabel = 0;
	}
	if ( m_pqlabelBubbleLabel != 0 )
	{
		delete m_pqlabelBubbleLabel;
		m_pqlabelBubbleLabel = 0;
	}
}

/** this creates the second screen */
void Wizard::InitializeScreen2()
{
	m_pqcomboboxPositionComboBox = new QComboBox( false, this );
	m_pqcomboboxPositionComboBox->insertItem( i18n("Position 1") );
	m_pqcomboboxPositionComboBox->insertItem( i18n("Position 2") );
	m_pqcomboboxPositionComboBox->insertItem( i18n("Position 3") );
	m_pqcomboboxPositionComboBox->insertItem( i18n("Position 4") );
	m_pqcomboboxPositionComboBox->insertItem( i18n("Position 5") );
	m_pqcomboboxPositionComboBox->insertItem( i18n("Position 6") );
	m_pqcomboboxPositionComboBox->insertItem( i18n("Position 7") );
	m_pqcomboboxPositionComboBox->insertItem( i18n("Position 8") );
	m_pqcomboboxPositionComboBox->setCurrentItem( m_intCurrentPosition );
	m_pqcomboboxPositionComboBox->setGeometry( 140, 153, 90, 21 );
	m_pqcomboboxPositionComboBox->show();
	QObject::connect( m_pqcomboboxPositionComboBox, SIGNAL(activated(int) ), this, SLOT( slotGetCurrentPosition(int) ) );
	
	m_pqlabelPositionLabel = new QLabel( i18n("Choose Step:"), this );
	m_pqlabelPositionLabel->setGeometry( 20, 153, 120, 21 );
	m_pqlabelPositionLabel->show();
	
	m_pqspinboxHightSpin = new QSpinBox( this );
	m_pqspinboxHightSpin->setRange( 20, 20000 );
	m_pqspinboxHightSpin->setGeometry( 140, 188, 90, 20 );
	m_pqspinboxHightSpin->show();
	m_pqspinboxHightSpin->setValue( m_intCurrentHipass );
	QObject::connect( m_pqspinboxHightSpin, SIGNAL(valueChanged(int) ), this, SLOT( slotGetCurrentHipass(int) ) );
	
	m_pqlabelHighSpinLabel = new QLabel( i18n("Hipass Freq:"), this );
	m_pqlabelHighSpinLabel->setGeometry( 20, 188, 120, 21 );
	m_pqlabelHighSpinLabel->show();
	
	m_pqspinboxLowSpin = new QSpinBox( this );
	m_pqspinboxLowSpin->setRange( 20, 20000 );
	m_pqspinboxLowSpin->setGeometry( 140, 225, 90, 20 );
	m_pqspinboxLowSpin->show();
	m_pqspinboxLowSpin->setValue( m_intCurrentLowpass );
	
	QObject::connect( m_pqspinboxLowSpin, SIGNAL(valueChanged(int) ), this, SLOT( slotGetCurrentLowpass(int) ) );
	
	m_pqlabelLowSpinLabel = new QLabel( i18n("Lowpass Freq:"), this );
	m_pqlabelLowSpinLabel->setGeometry( 20, 225, 120, 21 );
	m_pqlabelLowSpinLabel->show();
	
	m_pqlabelQFactorLabel = new QLabel( i18n("Q - Factor"), this );
	m_pqlabelQFactorLabel->setGeometry( 20, 260, 120, 21 );
	m_pqlabelQFactorLabel->show();
	m_pqlineeditQ = new QLineEdit( this );
	m_pqlineeditQ->setGeometry( 140, 260, 90, 21 );
	m_pqlineeditQ->show();
	char charText[ 20 ];
	sprintf( charText, "%5.2f", m_doubleCurrentQFactor );
	m_pqlineeditQ->setText( charText );
	QObject::connect( m_pqlineeditQ, SIGNAL(textChanged(const QString&) ), this, SLOT( slotGetCurrentQFactor(const QString&) ) );
	
	m_pqlabelStepLabel1 = new QLabel( this );
	QString qstringPath = locate( "data", "kfilter/pics/step2.xpm" );
	m_pqlabelStepLabel1->setPixmap( QPixmap( qstringPath ) );
	m_pqlabelStepLabel1->setGeometry( 5, 298, 100, 30 );
	m_pqlabelStepLabel1->show();

	m_pqlabelBubbleLabel = new QLabel( this );
	qstringPath = locate ( "data", "kfilter/pics/bubble2.gif" );
	m_pqlabelBubbleLabel->setPixmap( QPixmap( qstringPath ) );
	m_pqlabelBubbleLabel->setGeometry(320,150,80,100);
	m_pqlabelBubbleLabel->show();
	
}

void Wizard::ClearScreen2()
{
	if ( m_pqcomboboxPositionComboBox != 0 )
	{
		delete m_pqcomboboxPositionComboBox;
		m_pqcomboboxPositionComboBox = 0;
	}
	if ( m_pqlabelPositionLabel != 0 )
	{
		delete m_pqlabelPositionLabel;
		m_pqlabelPositionLabel = 0;
	}
	if ( m_pqspinboxHightSpin != 0 )
	{
		delete m_pqspinboxHightSpin;
		m_pqspinboxHightSpin = 0;
	}
	if ( m_pqspinboxLowSpin != 0 )
	{
		delete m_pqspinboxLowSpin;
		m_pqspinboxLowSpin = 0;
	}
	if ( m_pqlabelHighSpinLabel != 0 )
	{
		delete m_pqlabelHighSpinLabel;
		m_pqlabelHighSpinLabel = 0;
	}
	if ( m_pqlabelLowSpinLabel != 0 )
	{
		delete m_pqlabelLowSpinLabel;
		m_pqlabelLowSpinLabel = 0;
	}
	if ( m_pqlabelStepLabel1 != 0 )
	{
		delete m_pqlabelStepLabel1;
		m_pqlabelStepLabel1 = 0;
	}
	if ( m_pqlabelQFactorLabel != 0 )
	{
		delete m_pqlabelQFactorLabel;
		m_pqlabelQFactorLabel = 0;
	}
	if ( m_pqlineeditQ != 0 )
	{
		delete m_pqlineeditQ;
		m_pqlineeditQ = 0;
	}
	if ( m_pqlabelBubbleLabel != 0 )
	{
		delete m_pqlabelBubbleLabel;
		m_pqlabelBubbleLabel = 0;
	}
}

/** this initializes the 3. screen */
void Wizard::InitializeScreen3()
{
	m_pqcheckboxCorrection = new QCheckBox( this );
	m_pqcheckboxCorrection->setGeometry( 220, 164, 20, 20 );
	m_pqcheckboxCorrection->show();
	m_pqcheckboxCorrection->setChecked( m_boolCorrection );
	
	m_pqcheckboxOnly = new QCheckBox( this );
	m_pqcheckboxOnly->setGeometry( 220, 204, 20, 20 );
	m_pqcheckboxOnly->show();
	m_pqcheckboxOnly->setChecked( m_boolImpedanceOnly );
	
	m_pqcheckboxCleanup = new QCheckBox( this );
	m_pqcheckboxCleanup->setGeometry( 220, 244, 20, 20 );
	m_pqcheckboxCleanup->show();
	m_pqcheckboxCleanup->setChecked( m_boolCleanup );
	
	m_pqlabelCorrectionLabel = new QLabel( i18n("Insert Impedance Correction"), this );
	m_pqlabelCorrectionLabel->setGeometry( 20, 163, 180, 21 );
	m_pqlabelCorrectionLabel->show();
	
	m_pqlabelOnlyLabel = new QLabel( i18n("Only Impedance Correction"), this );
	m_pqlabelOnlyLabel->setGeometry( 20, 203, 180, 21 );
	m_pqlabelOnlyLabel->show();
	
	m_pqlabelCleanupLabel = new QLabel( i18n("Cleanup before Insert"), this );
	m_pqlabelCleanupLabel->setGeometry( 20, 243, 180, 21 );
	m_pqlabelCleanupLabel->show();
	
	m_pqlabelStepLabel2 = new QLabel( this );
	QString qstringPath = locate( "data", "kfilter/pics/step3.xpm" );
	m_pqlabelStepLabel2->setPixmap( QPixmap( qstringPath ) );
	m_pqlabelStepLabel2->setGeometry( 5, 295, 100, 30 );
	m_pqlabelStepLabel2->show();

	m_pqlabelBubbleLabel = new QLabel( this );
	qstringPath = locate ( "data", "kfilter/pics/bubble3.gif" );
	m_pqlabelBubbleLabel->setPixmap( QPixmap( qstringPath ) );
	m_pqlabelBubbleLabel->setGeometry(320,150,80,100);
	m_pqlabelBubbleLabel->show();

}

void Wizard::ClearScreen3()
{
	if ( m_pqcheckboxCorrection != 0 )
	{
		delete m_pqcheckboxCorrection;
		m_pqcheckboxCorrection = 0;
	}
	if ( m_pqcheckboxOnly != 0 )
	{
		delete m_pqcheckboxOnly;
		m_pqcheckboxOnly = 0;
	}
	if ( m_pqcheckboxCleanup != 0 )
	{
		delete m_pqcheckboxCleanup;
		m_pqcheckboxCleanup = 0;
	}
	if ( m_pqlabelCorrectionLabel != 0 )
	{
		delete m_pqlabelCorrectionLabel;
		m_pqlabelCorrectionLabel = 0;
	}
	if ( m_pqlabelOnlyLabel != 0 )
	{
		delete m_pqlabelOnlyLabel;
		m_pqlabelOnlyLabel = 0;
	}
	if ( m_pqlabelCleanupLabel != 0 )
	{
		delete m_pqlabelCleanupLabel;
		m_pqlabelCleanupLabel = 0;
	}
	if ( m_pqlabelStepLabel2 != 0 )
	{
		delete m_pqlabelStepLabel2;
		m_pqlabelStepLabel2 = 0;
	}
	if ( m_pqlabelBubbleLabel != 0 )
	{
		delete m_pqlabelBubbleLabel;
		m_pqlabelBubbleLabel = 0;
	}
}

/** this slot is activated when the nextbutton is
pressed */
void Wizard::slotNextButton()
{
	if ( m_intCurrent == 3 )
	{
		m_boolCorrection = m_pqcheckboxCorrection->isChecked();
		m_boolImpedanceOnly = m_pqcheckboxOnly->isChecked();
		m_boolCleanup = m_pqcheckboxCleanup->isChecked();	
		ClearScreen3();
		Evaluation();
    emit isclosed();
		delete this;
	}
	
	if ( m_intCurrent == 2 )
	{
		m_pqpushbuttonButton[0]->setText( i18n("Finish") );
		m_pqmovieMovie->setSpeed( 200 );
		ClearScreen2();
		InitializeScreen3();
		m_intCurrent = 3;
	}
	
	if ( m_intCurrent == 1 )
	{
		m_pqpushbuttonButton[1]->setText( i18n("<< Prev") );
		m_pqmovieMovie->setSpeed( 150 );
		ClearScreen1();
		InitializeScreen2();
		m_intCurrent = 2;
	}
}
/** this is activated, if the prev button
is pressed. */
void Wizard::slotPreviousButton()
{
	if ( m_intCurrent == 1 )
	{
		ClearScreen1();
		delete this;
	}
	
	if ( m_intCurrent == 2 )
	{
		m_pqpushbuttonButton[1]->setText( i18n("Cancel") );
		m_pqmovieMovie->setSpeed( 100 );
		ClearScreen2();
		InitializeScreen1();
		m_intCurrent = 1;
	}
	
	if ( m_intCurrent == 3 )
	{
		m_boolCorrection = m_pqcheckboxCorrection->isChecked();
		m_boolImpedanceOnly = m_pqcheckboxOnly->isChecked();
		m_boolCleanup = m_pqcheckboxCleanup->isChecked();
		m_pqpushbuttonButton[ 0 ]->setText( i18n("Next >>") );
		m_pqmovieMovie->setSpeed( 150 );
		ClearScreen3();
		InitializeScreen2();
		m_intCurrent = 2;	
	}
}

/** this slot is activated if the driver is set
by the user */
void Wizard::slotGetCurrentDriver( int a_intCurrentDriver )
{
	m_intCurrentDriver = a_intCurrentDriver;
}

/** this is set if the object ist selected */
void Wizard::slotGetCurrentObject( int a_intCurrentObject )
{
	m_intCurrentObject = a_intCurrentObject;
}

/** this is set if the filter order is selected */
void Wizard::slotGetCurrentOrder( int a_intCurrentOrder )
{
	m_intCurrentOrder = a_intCurrentOrder;
}

/** this is set if the position is set be the
user */
void Wizard::slotGetCurrentPosition( int a_intCurrentPosition )
{
	m_intCurrentPosition = a_intCurrentPosition;
}

/** sets the hipass value */
void Wizard::slotGetCurrentHipass( int a_intHipass )
{
	m_intCurrentHipass = a_intHipass;
}
/** set the lowpass frequency */
void Wizard::slotGetCurrentLowpass( int a_intLowpass )
{
	m_intCurrentLowpass = a_intLowpass;
}

/** this function evaluates the current
settings and put it into the network */
void Wizard::Evaluation()
{
	
	if ( m_boolImpedanceOnly )
	{
// the first version is old - not protected - Martin 09.06.02
/*
		CreateCorrection( m_intCurrentHipass, \
			&m_pdriverDriver[ m_intCurrentDriver]->Unit[ 4 + ( 6 * m_intCurrentPosition ) ], \
			&m_pdriverDriver[ m_intCurrentDriver]->Unit[ 5 + ( 6 * m_intCurrentPosition ) ] );
*/
		double res, cap;
		CreateCorrection( m_intCurrentHipass, &res, &cap );
			m_pdriverDriver[ m_intCurrentDriver]->setUnit( 4 + ( 6 * m_intCurrentPosition ), res);
			m_pdriverDriver[ m_intCurrentDriver]->setUnit( 5 + ( 6 * m_intCurrentPosition ), cap);
		return;
	}
	
	if ( m_boolCleanup )
	{
		for ( int intI = 0; intI < 49; intI++ )
		{
			m_pdriverDriver[ m_intCurrentDriver]->Unit[ intI ] = 0;
		}


//		m_pdriverDriver[ m_intCurrentDriver]->cleanupNetwork();
	}
	
	if (CheckPosition() != 0)
	{
		if ( KMessageBox::warningYesNo( this, \
			i18n("The step position exeeds the end of the network.\n"
			"Should the position be adjusted ?")) == 2 )
		{
			return;
		}
	}
	int intX = 6 * ( m_intCurrentPosition - CheckPosition() );
	
	if ( m_intCurrentObject == 0 )
	{
		CreateHipass( m_intCurrentOrder, m_intCurrentHipass,
			&m_pdriverDriver[ m_intCurrentDriver]->Unit[ 2 + intX ], \
			&m_pdriverDriver[ m_intCurrentDriver]->Unit[ 6 + intX ], \
			&m_pdriverDriver[ m_intCurrentDriver]->Unit[ 8 + intX ], \
			&m_pdriverDriver[ m_intCurrentDriver]->Unit[ 12 + intX ] );
	}
	if ( m_intCurrentObject == 1 )
	{
		CreateLowpass( m_intCurrentOrder, m_intCurrentLowpass,
			&m_pdriverDriver[ m_intCurrentDriver]->Unit[ 3 + intX ], \
			&m_pdriverDriver[ m_intCurrentDriver]->Unit[ 5 + intX ], \
			&m_pdriverDriver[ m_intCurrentDriver]->Unit[ 9 + intX ], \
			&m_pdriverDriver[ m_intCurrentDriver]->Unit[ 11 + intX ] );
	}
	if ( m_intCurrentObject == 2 )
	{
		CreateHipass( m_intCurrentOrder, m_intCurrentHipass,
			&m_pdriverDriver[ m_intCurrentDriver]->Unit[ 2 + intX ], \
			&m_pdriverDriver[ m_intCurrentDriver]->Unit[ 6 + intX ], \
			&m_pdriverDriver[ m_intCurrentDriver]->Unit[ 8 + intX ], \
			&m_pdriverDriver[ m_intCurrentDriver]->Unit[ 12 + intX ] );
		int intY = 0;
		if ( m_intCurrentOrder < 2 )
		{
			intY = 6;
		}
		else
		{
			intY = 12;
		}
		CreateLowpass( m_intCurrentOrder, m_intCurrentLowpass,
			&m_pdriverDriver[ m_intCurrentDriver]->Unit[ 3 + intX + intY ], \
			&m_pdriverDriver[ m_intCurrentDriver]->Unit[ 5 + intX + intY ], \
			&m_pdriverDriver[ m_intCurrentDriver]->Unit[ 9 + intX + intY ], \
			&m_pdriverDriver[ m_intCurrentDriver]->Unit[ 11 + intX + intY ] );
	}
	if ( m_intCurrentOrder == 1 )
	{
		intX += 6;
	}
	if ( m_intCurrentOrder > 1 )
	{
		intX += 12;
	}
	if ( m_intCurrentObject == 2 )
	{
		if ( m_intCurrentOrder == 1 )
		{
			intX += 6;
		}
		if ( m_intCurrentOrder > 1 )
		{
			intX += 12;
		}
	}
	
	if ( m_boolCorrection )
	{
		CreateCorrection( m_intCurrentHipass, \
			&m_pdriverDriver[ m_intCurrentDriver ]->Unit[ 4 + intX ], \
			&m_pdriverDriver[ m_intCurrentDriver ]->Unit[ 5 + intX ] );
	}
	m_pdriverDriver[ m_intCurrentDriver ]->setmodified();
	m_pdriverDriver[ m_intCurrentDriver ]->PressureisActive = 1;
	m_pdriverDriver[ m_intCurrentDriver ]->ImpedanzisActive = 1;
}


/** creates a hipass with given parameters */
void Wizard::CreateHipass( int a_intOrder, int a_intFrequency, \
	double* a_pdoubleUnit1, double* a_pdoubleUnit2, \
	double* a_pdoubleUnit3, double* a_pdoubleUnit4 )
{
	
	double doubleFrequency  = (double)a_intFrequency;
	double doublePi = 3.1415;
	double doubleA2 = 2.613;
	double doubleB = 2.414;
	double doubleC = 1.848;
	
	switch ( a_intOrder )
	{
	case	0 :
		*a_pdoubleUnit1 = 1.0 / ( 2.0 * doublePi * doubleFrequency * \
			m_pdriverDriver[ m_intCurrentDriver ]->getRdc() );
		break;
	case	1 :
		*a_pdoubleUnit1 = m_doubleCurrentQFactor / ( 2.0 * doublePi * doubleFrequency * \
			m_pdriverDriver[ m_intCurrentDriver ]->getRdc() );
		*a_pdoubleUnit2 = m_pdriverDriver[ m_intCurrentDriver ]->getRdc() / ( 2.0 * doublePi * \
			doubleFrequency * m_doubleCurrentQFactor );
		break;
	case	2 :
		*a_pdoubleUnit3 = 2.0 / ( 2.0 * doublePi * doubleFrequency * \
			m_pdriverDriver[ m_intCurrentDriver ]->getRdc() );
		*a_pdoubleUnit2 = 3.0 * m_pdriverDriver[ m_intCurrentDriver ]->getRdc() / ( 8.0 * doublePi * doubleFrequency );
		*a_pdoubleUnit1 = 2.0 / ( 6.0 * doublePi * doubleFrequency * \
			m_pdriverDriver[ m_intCurrentDriver ]->getRdc() );
		break;
	case	3 :
		*a_pdoubleUnit1 = 1.0 / ( 2.0 * doublePi * doubleC * doubleFrequency * \
			m_pdriverDriver[ m_intCurrentDriver ]->getRdc() );
		*a_pdoubleUnit2 = doubleC * m_pdriverDriver[ m_intCurrentDriver ]->getRdc() / ( 2.0 * \
			doublePi * doubleB * doubleFrequency );
		*a_pdoubleUnit3 = doubleB / ( 2.0 * doublePi * doubleA2 * doubleFrequency * \
			m_pdriverDriver[ m_intCurrentDriver ]->getRdc() );
		*a_pdoubleUnit4 = doubleA2 * m_pdriverDriver[ m_intCurrentDriver ]->getRdc() / ( 2.0 * \
			doublePi * doubleFrequency );
		break;
	}
}


/** this function creates a lowpass  */
void Wizard::CreateLowpass( int a_intOrder, int a_intFrequency, \
	double* a_pdoubleUnit1, double* a_pdoubleUnit2, \
	double* a_pdoubleUnit3, double* a_pdoubleUnit4 )
{
	
	double doubleFrequency  = (double)a_intFrequency;
	double doublePi = 3.1415;
	double doubleA2 = 2.613;
	double doubleB = 2.414;
	double doubleC = 1.848;
	
	switch ( a_intOrder )
	{
	case 0 :
		*a_pdoubleUnit1 = m_pdriverDriver[ m_intCurrentDriver ]->getRdc() / \
			( 2.0 * doublePi * doubleFrequency );
		break;
	case 1 :
		*a_pdoubleUnit1 = m_pdriverDriver[ m_intCurrentDriver ]->getRdc() / \
			( 2.0 * doublePi * m_doubleCurrentQFactor * doubleFrequency );
		*a_pdoubleUnit2 = m_doubleCurrentQFactor / ( 2.0 * doublePi * \
			doubleFrequency *m_pdriverDriver[ m_intCurrentDriver ]->getRdc() );
		break;
	case	2 :
		*a_pdoubleUnit1 = 3.0 * m_pdriverDriver[ m_intCurrentDriver ]->getRdc() / \
			( 4.0 * doublePi * doubleFrequency );
		*a_pdoubleUnit2 = 4.0 / ( 6.0 * doublePi * doubleFrequency * \
			m_pdriverDriver[ m_intCurrentDriver ]->getRdc() );
		*a_pdoubleUnit3 = m_pdriverDriver[ m_intCurrentDriver ]->getRdc() / \
			( 4.0 * doublePi * doubleFrequency );
		break;
	case	3 :
		*a_pdoubleUnit1 = doubleC * m_pdriverDriver[ m_intCurrentDriver ]->getRdc() / \
			( 2.0 * doublePi * doubleFrequency );
		*a_pdoubleUnit2 = doubleB / ( 2.0 * doublePi * doubleC * \
			doubleFrequency *m_pdriverDriver[ m_intCurrentDriver ]->getRdc() );
		*a_pdoubleUnit3 = doubleA2 * m_pdriverDriver[ m_intCurrentDriver ]->getRdc() / \
			( 2.0 * doublePi * doubleB * doubleFrequency );
		*a_pdoubleUnit4 = 1.0 / ( 2.0 * doublePi * doubleA2 * doubleFrequency *\
			m_pdriverDriver[ m_intCurrentDriver ]->getRdc() );
		break;
	}
}

/**  */
void Wizard::slotGetCurrentQFactor( const QString& a_qstringTextParameter )
{
	m_doubleCurrentQFactor = atof( (const char*)a_qstringTextParameter );
}



/** checks the validation of the position */
int Wizard::CheckPosition()
{
	
	int intTest = 0;
	if ( m_intCurrentOrder > 2 )
	{
		intTest++;
	}
	
	if ( m_intCurrentObject == 2 )
	{
		if ( intTest == 0 )
		{
			intTest++;
		}
		if ( intTest  > 0)
		{
			intTest =+ 2;
		}
	}
	
	if ( m_boolCorrection )
	{
		intTest = intTest + 1;
	}
	
	if ( m_intCurrentPosition + intTest < 7 )
	{
		return 0;
	}
	else
	{
		return ( m_intCurrentPosition + intTest - 7 );
	}
}


/** creates an impedance correction */
void Wizard::CreateCorrection( int /*a_intfrequency*/, double* a_pdoubleR, double* a_pdoubleC )
{
	
	*a_pdoubleC = m_pdriverDriver[ m_intCurrentDriver ]->getLsp() / pow( 2.0, m_pdriverDriver[ m_intCurrentDriver ]->getRdc() );
	*a_pdoubleR = m_pdriverDriver[ m_intCurrentDriver ]->getRdc();
}
