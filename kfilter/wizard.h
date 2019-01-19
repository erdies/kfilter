/***************************************************************************
wizard.h  -  description
-------------------
begin                : Sun Oct 1 2000
copyright            : (C) 2000 by Martin Erdtmann
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

#ifndef WIZARD_H
#define WIZARD_H

#include <qdialog.h>
#include <kapp.h>
#include <kstddirs.h>
#include <stdio.h>
#include <qlabel.h>
#include <qpixmap.h>
#include <qgroupbox.h>
#include <klocale.h>
#include <kseparator.h>
#include <qpushbutton.h>
#include <qcombobox.h>
#include <qlabel.h>
#include <qspinbox.h>
#include <qmovie.h>
#include <qcheckbox.h>
#include <qlineedit.h>
#include <stdlib.h>
#include <string.h>
#include <qstring.h>
#include <kmessagebox.h>
#include <math.h>
#include "driver.h"


/**Wizard is the class of the filter wizard
*@author Martin Erdtmann
*/

class Wizard : public QDialog
{
	Q_OBJECT
public: 
	Wizard( QWidget* a_pqwidgetParent, const char* a_pcharName, driver* a_pdriverDriver0 = 0, driver* a_pdriverDriver1 = 0, \
		driver* a_pdriverDriver2 = 0, driver* a_pdriverDriver3 = 0 );
	~Wizard();
	
	
private:

	// Screen 1
	void	InitializeScreen1();
	void	ClearScreen1();
	
	QComboBox*	m_pqcomboboxDriverComboBox;
	QComboBox*	m_pqcomboboxFilterComboBox;
	QComboBox*	m_pqcomboboxOrderComboBox;
	QLabel*		m_pqlabelDriverLabel;
	QLabel*		m_pqlabelFilterLabel;
	QLabel*		m_pqlabelOrderLabel;
	QLabel*		m_pqlabelStepLabel;
	QLabel*		m_pqlabelBubbleLabel;
		
	// Screen 2
	void	InitializeScreen2();
	void	ClearScreen2();
	
	QComboBox*	m_pqcomboboxPositionComboBox;
	QLabel*		m_pqlabelPositionLabel;
	QSpinBox*	m_pqspinboxHightSpin;
	QSpinBox*	m_pqspinboxLowSpin;
	QLabel*		m_pqlabelHighSpinLabel;
	QLabel*		m_pqlabelLowSpinLabel;
	QLabel*		m_pqlabelStepLabel1;
	QLabel*		m_pqlabelQFactorLabel;
	QLineEdit*	m_pqlineeditQ;
	
	
	// Screen 3
	void	InitializeScreen3();
	void	ClearScreen3();
	
	QCheckBox*	m_pqcheckboxCorrection;
	QCheckBox*	m_pqcheckboxOnly;
	QCheckBox*	m_pqcheckboxCleanup;
	QLabel*		m_pqlabelCorrectionLabel;
	QLabel*		m_pqlabelOnlyLabel;
	QLabel*		m_pqlabelCleanupLabel;
	QLabel*		m_pqlabelStepLabel2;
	
	
	QPushButton*	m_pqpushbuttonButton[2];
	QMovie*		m_pqmovieMovie;
	QLabel*		m_pqlabelTuxLabel;
	driver*		m_pdriverDriver[4];
	
	int			m_intCurrentDriver;
	int			m_intCurrentObject;
	int			m_intCurrentOrder;
	int			m_intCurrentPosition;
	int			m_intCurrentHipass;
	int			m_intCurrentLowpass;
	int			m_intCurrent;
		
	bool		m_boolCorrection;
	bool		m_boolImpedanceOnly;
	bool		m_boolCleanup;
	double 		m_doubleCurrentQFactor;
	
	// Private methods
	/** this function evaluates the current
	settings and put it into the network */
	void Evaluation();
	/** creates a hipass with given parameters */
	void CreateHipass(int order,int frequency,double* unit1,double* unit2,double* unit3, double* unit4);
	/** this function creates a lowpass  */
	void CreateLowpass(int order,int frequency,double* unit1,double* unit2,double* unit3,double* unit4);
	/** checks the validation of the position */
	int CheckPosition();
	/** creates an impedance correction */
	void CreateCorrection(int frequency, double* R,double* C);

private slots: // Private slots
			   /** this slot is activated when the nextbutton is
	pressed */
	void slotNextButton();
	/** this is activated, if the prev button
	is pressed. */
	void slotPreviousButton();
	/** this slot is activated if the driver is set
	by the user */
	void slotGetCurrentDriver(int);
	/** this is set if the object ist selected */
	void slotGetCurrentObject(int object);
	/** this is set if the filter order is selected */
	void slotGetCurrentOrder(int);
	/** this is set if the position is set be the 
	user */
	void slotGetCurrentPosition(int);
	/** sets the hipass value */
	void slotGetCurrentHipass(int);
	/** set the lowpass frequency */
	void slotGetCurrentLowpass(int);
	/**  */
	void slotGetCurrentQFactor(const QString&);

signals:

  void isclosed();
};

#endif
