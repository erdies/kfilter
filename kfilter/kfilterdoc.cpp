/***************************************************************************
                          kfilterdoc.cpp  -  description
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
#include <qdir.h>
#include <qwidget.h>

// include files for KDE
#include <klocale.h>
#include <kmessagebox.h>
#include <kio/job.h>
#include <kio/netaccess.h>

// application specific includes
#include "resource.h"
#include "kfilterdoc.h"
#include "kfilter.h"
#include "kfilterview.h"
#include "driverinput.h"
#include "networkdialog.h"
#include "volumedialog.h"
#include "wizard.h"

QList<KFilterView> *KFilterDoc::pViewList = 0L;

KFilterDoc::KFilterDoc(QWidget *parent, const char *name) : QObject(parent, name)
{
  if(!pViewList)
  {
    pViewList = new QList<KFilterView>();
  }

  pViewList->setAutoDelete(true);
}

KFilterDoc::~KFilterDoc()
{
}

void KFilterDoc::addView(KFilterView *view)
{
  pViewList->append(view);
}

void KFilterDoc::removeView(KFilterView *view)
{
  pViewList->remove(view);
}
void KFilterDoc::setURL(const KURL &url)
{
  doc_url=url;
}

const KURL& KFilterDoc::URL() const
{
  return doc_url;
}

void KFilterDoc::slotUpdateAllViews(KFilterView *sender)
{
  KFilterView *w;
  if(pViewList)
  {
    for(w=pViewList->first(); w!=0; w=pViewList->next())
    {
      if(w!=sender)
        w->repaint();
    }
  }

}

bool KFilterDoc::saveModified()
{
  bool completed=true;

  if(modified)
  {
    KFilterApp *win=(KFilterApp *) parent();
    int want_save = KMessageBox::warningYesNoCancel(win,
                                         i18n("The current file has been modified.\n"
                                              "Do you want to save it?"),
                                         i18n("Warning"));
    switch(want_save)
    {
      case KMessageBox::Yes:
           if (doc_url.fileName() == i18n("Untitled"))
           {
             win->slotFileSaveAs();
           }
           else
           {
             saveDocument(URL());
       	   };

       	   deleteContents();
           completed=true;
           break;

      case KMessageBox::No:
           setModified(false);
           deleteContents();
           completed=true;
           break;

      case KMessageBox::Cancel:
           completed=false;
           break;

      default:
           completed=false;
           break;
    }
  }

  return completed;
}

void KFilterDoc::closeDocument()
{
  deleteContents();
}

bool KFilterDoc::newDocument()
{
  /////////////////////////////////////////////////
  // TODO: Add your document initialization code here
  /////////////////////////////////////////////////
  modified=false;
  doc_url.setFileName(i18n("Untitled"));
  deleteContents();
  viewrefresh();
  return true;
}

bool KFilterDoc::openDocument(const KURL& url, const char *format /*=0*/)
{
  QString tmpfile;
  KIO::NetAccess::download( url, tmpfile );
  /////////////////////////////////////////////////
  // TODO: Add your document opening code here
  /////////////////////////////////////////////////
	QFile qfileFile( tmpfile );
	if ( qfileFile.exists() )
	{
		qfileFile.open( IO_ReadOnly );
	}
	else
	{
		return 1;
	}
	QTextStream qtextstreamStream( &qfileFile );
	QString qstringLine;
	while ( !qtextstreamStream.eof() )
	{
		qstringLine = qtextstreamStream.readLine();
		if ( qstringLine.find("#") != 0)
		{
			if ( qstringLine.contains ( "Network values", false ) != 0)
			{
				for ( int intI = 0; intI < 4 ; intI++ )
				{
					for (int intZ = 1; intZ < 49 ; intZ++ )
					{
						if ( !qtextstreamStream.eof() )
						{
							qstringLine = qtextstreamStream.readLine();
						}
						else
						{
							truncatedFile( &qfileFile );
							return 1;
						}
						while ( ( qstringLine.find("#") == 0 ) && ( !qtextstreamStream.eof() ) )
						{
							qstringLine = qtextstreamStream.readLine();
						}
						if ( qstringLine.find("[") != 0)
						{
							m_driverDriver[ intI ].setUnit( intZ, atof( qstringLine.data() ));
						}
						else
						{
							intI = 4;
							intZ = 49;
						}
					}
				}
			}
			if ( qstringLine.contains ( "Driver Parameters", false ) != 0 )
			{
				for (int intI = 0; intI < 4; intI++ )
				{
					if ( !qtextstreamStream.eof() )
					{
						qstringLine = qtextstreamStream.readLine();
					}
					else
					{
						truncatedFile( &qfileFile );
						return 1;
					}
					while ( ( qstringLine.find("#") == 0 ) && ( !qtextstreamStream.eof() ) )
					{
						qstringLine = qtextstreamStream.readLine();
					}
					qstringLine.remove( 0, qstringLine.find("=") + 1 );
					m_driverDriver[ intI ].setRdc(atof( qstringLine.data() ));
					if ( !qtextstreamStream.eof() )
					{
						qstringLine = qtextstreamStream.readLine();
					}
					else
					{
						truncatedFile( &qfileFile );
						return 1;
					}
					while ( ( qstringLine.find("#") == 0 ) && ( !qtextstreamStream.eof() ) )
					{
						qstringLine = qtextstreamStream.readLine();
					}
					qstringLine.remove( 0, qstringLine.find("=") + 1 );
					m_driverDriver[ intI ].setLsp(atof( qstringLine.data() ));
					if ( !qtextstreamStream.eof() )
					{
						qstringLine = qtextstreamStream.readLine();
					}
					else
					{
						truncatedFile( &qfileFile );
						return 1;
					}
					while ( ( qstringLine.find("#") == 0 ) && ( !qtextstreamStream.eof() ) )
					{
						qstringLine = qtextstreamStream.readLine();
					}
					qstringLine.remove( 0, qstringLine.find("=") + 1 );
					m_driverDriver[ intI ].setF0(atof( qstringLine.data() ));
					if ( !qtextstreamStream.eof() )
					{
						qstringLine = qtextstreamStream.readLine();
					}
					else
					{
						truncatedFile( &qfileFile );
						return 1;
					}
					while ( ( qstringLine.find("#") == 0 ) && ( !qtextstreamStream.eof() ) )
					{
						qstringLine = qtextstreamStream.readLine();
					}
					qstringLine.remove( 0, qstringLine.find("=") + 1 );
					m_driverDriver[ intI ].setQtc(atof( qstringLine.data() ));
					if ( !qtextstreamStream.eof() )
					{
						qstringLine = qtextstreamStream.readLine();
					}
					else
					{
						truncatedFile( &qfileFile );
						return 1;
					}
					while ( ( qstringLine.find("#") == 0 ) && ( !qtextstreamStream.eof() ) )
					{
						qstringLine = qtextstreamStream.readLine();
					}
					qstringLine.remove( 0, qstringLine.find("=") + 1 );
					m_driverDriver[ intI ].setQes( atof( qstringLine.data() ));
					if ( !qtextstreamStream.eof() )
					{
						qstringLine = qtextstreamStream.readLine();
					}
					else
					{
						truncatedFile( &qfileFile );
						return 1;
					}
					while ( ( qstringLine.find("#") == 0 ) && ( !qtextstreamStream.eof() ) )
					{
						qstringLine = qtextstreamStream.readLine();
					}
					qstringLine.remove( 0, qstringLine.find("=") + 1 );
					m_driverDriver[ intI ].setQms(atof( qstringLine.data() ));
					if ( !qtextstreamStream.eof() )
					{
						qstringLine = qtextstreamStream.readLine();
					}
					else
					{
						truncatedFile( &qfileFile );
						return 1;
					}
					while ( ( qstringLine.find("#") == 0 ) && ( !qtextstreamStream.eof() ) )
					{
						qstringLine = qtextstreamStream.readLine();
					}
					qstringLine.remove( 0, qstringLine.find("=") + 1 );
					m_driverDriver[ intI ].setVas(atof( qstringLine.data() ));
					if ( !qtextstreamStream.eof() )
					{
						qstringLine = qtextstreamStream.readLine();
					}
					else
					{
						truncatedFile( &qfileFile );
						return 1;
					}
					while ( ( qstringLine.find("#") == 0 ) && ( !qtextstreamStream.eof() ) )
					{
						qstringLine = qtextstreamStream.readLine();
					}
					qstringLine.remove( 0, qstringLine.find("=") + 1 );
					m_driverDriver[ intI].setDm(atof( qstringLine.data() ));
					if ( !qtextstreamStream.eof() )
					{
						qstringLine = qtextstreamStream.readLine();
					}
					else
					{
						truncatedFile( &qfileFile );
						return 1;
					}
					while ( ( qstringLine.find("#") == 0 ) && ( !qtextstreamStream.eof() ) )
					{
						qstringLine = qtextstreamStream.readLine();
					}
					qstringLine.remove( 0, qstringLine.find("=") + 1 );
					m_driverDriver[ intI ].Vb = atof( qstringLine.data() );
					if ( !qtextstreamStream.eof() )
					{
						qstringLine = qtextstreamStream.readLine();
					}
					else
					{
						truncatedFile( &qfileFile );
						return 1;
					}
					while ( ( qstringLine.find("#") == 0 ) && ( !qtextstreamStream.eof() ) )
					{
						qstringLine = qtextstreamStream.readLine();
					}
					qstringLine.remove( 0, qstringLine.find("=") + 1 );
					m_driverDriver[ intI ].Fb = atof( qstringLine.data() );
					if ( !qtextstreamStream.eof() )
					{
						qstringLine = qtextstreamStream.readLine();
					}
					else
					{
						truncatedFile( &qfileFile );
						return 1;
					}
					while ( ( qstringLine.find("#") == 0 ) && ( !qtextstreamStream.eof() ) )
					{
						qstringLine = qtextstreamStream.readLine();
					}
					qstringLine.remove( 0, qstringLine.find("=") + 1 );
					m_driverDriver[ intI ].V2 = atof( qstringLine.data() );
					if ( !qtextstreamStream.eof() )
					{
						qstringLine = qtextstreamStream.readLine();
					}
					else
					{
						truncatedFile( &qfileFile );
						return 1;
					}
					while ( ( qstringLine.find("#") == 0 ) && ( !qtextstreamStream.eof() ) )
					{
						qstringLine = qtextstreamStream.readLine();
					}
					qstringLine.remove( 0, qstringLine.find("=") + 1 );
					m_driverDriver[ intI ].GTypProposal  = atoi( qstringLine.data() );
					if ( !qtextstreamStream.eof() )
					{
						qstringLine = qtextstreamStream.readLine();
					}
					else
					{
						truncatedFile( &qfileFile );
						return 1;
					}
					while ( ( qstringLine.find("#") == 0 ) && ( !qtextstreamStream.eof() ) )
					{
						qstringLine = qtextstreamStream.readLine();
					}
					qstringLine.remove( 0, qstringLine.find("=") + 1 );
					m_driverDriver[ intI ].gain  = atof( qstringLine.data() );

					if ( !qtextstreamStream.eof() )
					{
						qstringLine = qtextstreamStream.readLine();
					}
					else
					{
						truncatedFile( &qfileFile );
						return 1;
					}
					while ( ( qstringLine.find("#") == 0 ) && ( !qtextstreamStream.eof() ) )
					{
						qstringLine = qtextstreamStream.readLine();
					}
					qstringLine.remove( 0, qstringLine.find("=") + 1 );
					m_driverDriver[ intI ].PressureisActive  = ( atoi( qstringLine.data() ) == 1 );
					if ( !qtextstreamStream.eof() )
					{
						qstringLine = qtextstreamStream.readLine();
					}
					else
					{
						truncatedFile( &qfileFile );
						return 1;
					}
					while ( ( qstringLine.find("#") == 0 ) && ( !qtextstreamStream.eof() ) )
					{
						qstringLine = qtextstreamStream.readLine();
					}
					qstringLine.remove( 0, qstringLine.find("=") + 1 );
					m_driverDriver[ intI ].ImpedanzisActive  = ( atoi( qstringLine.data() ) == 1 );
					if ( !qtextstreamStream.eof() )
					{
						qstringLine = qtextstreamStream.readLine();
					}
					else
					{
						truncatedFile( &qfileFile );
						return 1;
					}
					while ( ( qstringLine.find("#") == 0 ) && ( !qtextstreamStream.eof() ) )
					{
						qstringLine = qtextstreamStream.readLine();
					}
					qstringLine.remove( 0, qstringLine.find("=") + 1 );
					m_driverDriver[ intI ].SummaryisActive  = ( atoi( qstringLine.data() ) == 1 );
					if ( !qtextstreamStream.eof() )
					{
						qstringLine = qtextstreamStream.readLine();
					}
					else
					{
						truncatedFile( &qfileFile );
						return 1;
					}
					while ( ( qstringLine.find("#") == 0 ) && ( !qtextstreamStream.eof() ) )
					{
						qstringLine = qtextstreamStream.readLine();
					}
					qstringLine.remove( 0, qstringLine.find("=") + 1 );
					m_driverDriver[ intI ].ScalarSummaryisActive  = ( atoi( qstringLine.data() ) == 1 );
					if ( !qtextstreamStream.eof() )
					{
						qstringLine = qtextstreamStream.readLine();
					}
					else
					{
						truncatedFile( &qfileFile );
						return 1;
					}
					while ( ( qstringLine.find("#") == 0 ) && ( !qtextstreamStream.eof() ) )
					{
						qstringLine = qtextstreamStream.readLine();
					}
					qstringLine.remove( 0, qstringLine.find("=") + 1 );
					m_driverDriver[ intI ].ImpedanzSummaryisActive  = ( atoi( qstringLine.data() ) == 1 );
					if ( !qtextstreamStream.eof() )
					{
						qstringLine = qtextstreamStream.readLine();
					}
					else
					{
						truncatedFile( &qfileFile );
						return 1;
					}
					while ( ( qstringLine.find("#") == 0 ) && ( !qtextstreamStream.eof() ) )
					{
						qstringLine = qtextstreamStream.readLine();
					}
					qstringLine.remove( 0, qstringLine.find("=") + 1 );
					m_driverDriver[ intI ].InvertPhase  = ( atoi( qstringLine.data() ) == 1 );

					if ( !qtextstreamStream.eof() )
					{
						qstringLine = qtextstreamStream.readLine();
					}
					else
					{
						truncatedFile( &qfileFile );
						return 1;
					}
					while ( ( qstringLine.find("#") == 0 ) && ( !qtextstreamStream.eof() ) )
					{
						qstringLine = qtextstreamStream.readLine();
          }
					qstringLine.remove( 0, qstringLine.find("=") + 1 );
					m_driverDriver[ intI ].SetTitle( qstringLine.data() );
				}
			}
		}
	}
	qfileFile.close();
	for( int intI = 0; intI < 3; intI++ )
	{
		m_driverDriver[ intI ].Berechneparameter();
		m_driverDriver[ intI ].setmodified();
	}
	forceviewrefresh();
	modified = false;
	return true;
///////////////////////////////////////////////////////////////

  KIO::NetAccess::removeTempFile( tmpfile );

  modified=false;
  return true;
}

bool KFilterDoc::saveDocument(const KURL& url, const char *format /*=0*/)
{
  /////////////////////////////////////////////////
  // TODO: Add your document saving code here
  /////////////////////////////////////////////////
	char charBuffer[ 20 ];
	QFile qfileFile( url.path() );
	qfileFile.open( IO_ReadWrite );

	qfileFile.writeBlock( "# KFilter datafile", 18 );
	qfileFile.writeBlock( "\n[Network values]", 17 );

	for (int intI = 0; intI < 4; intI++ )
	{
		qfileFile.writeBlock( "\n# Driver ", 10 );
		sprintf( charBuffer, "%1.0d", intI + 1 );
		qfileFile.writeBlock( charBuffer, 1 );
		for (int intZ = 1; intZ < 49; intZ++ )
		{
			sprintf ( charBuffer, "\n%14.9f", m_driverDriver[ intI ].getUnit( intZ ) );
			qfileFile.writeBlock( charBuffer, 16 );
		}
	}
	qfileFile.writeBlock( "\n[Driver parameters]", 21 );
	for (int intI = 0; intI < 4; intI++ )
	{
		sprintf( charBuffer, "%1.0d", intI + 1 );
		qfileFile.writeBlock( "\n# Driver ", 10 );
		qfileFile.writeBlock( charBuffer, 1 );
		sprintf( charBuffer, "\nRdc=%10.6f", m_driverDriver[ intI ].getRdc() );
		qfileFile.writeBlock( charBuffer, 14 );
		sprintf( charBuffer, "\nLsp=%10.6f", m_driverDriver[ intI ].getLsp() );
		qfileFile.writeBlock( charBuffer, 14 );
		sprintf( charBuffer, "\nF0 =%10.6f", m_driverDriver[ intI ].getF0() );
		qfileFile.writeBlock( charBuffer, 14 );
		sprintf( charBuffer, "\nQts=%10.6f", m_driverDriver[ intI ].getQtc() );
		qfileFile.writeBlock( charBuffer, 14 );
		sprintf( charBuffer, "\nQe =%10.6f", m_driverDriver[ intI ].getQes() );
		qfileFile.writeBlock( charBuffer, 14 );
		sprintf( charBuffer, "\nQms=%10.6f", m_driverDriver[ intI ].getQms() );
		qfileFile.writeBlock( charBuffer, 14 );
		sprintf( charBuffer, "\nVas=%10.6f", m_driverDriver[ intI ].getVas() );
		qfileFile.writeBlock( charBuffer, 14 );
		sprintf( charBuffer, "\nDm =%10.6f", m_driverDriver[ intI ].getDm() );
		qfileFile.writeBlock( charBuffer, 14 );
		sprintf( charBuffer, "\nVb =%10.6f", m_driverDriver[ intI ].Vb );
		qfileFile.writeBlock( charBuffer, 14 );
		sprintf( charBuffer, "\nFb =%10.6f", m_driverDriver[ intI ].Fb );
		qfileFile.writeBlock( charBuffer, 14 );
		sprintf( charBuffer, "\nV2 =%10.6f", m_driverDriver[ intI ].V2 );
		qfileFile.writeBlock( charBuffer, 14 );
		sprintf( charBuffer, "\nGTypProposal =%3.0d", m_driverDriver[ intI ].GTypProposal );
		qfileFile.writeBlock( charBuffer, 18 );
		sprintf( charBuffer, "\nGain =%10.6f", m_driverDriver[ intI ].gain );
		qfileFile.writeBlock( charBuffer, 17 );

		if (m_driverDriver[ intI ].PressureisActive)
		{
			qfileFile.writeBlock( "\nPressure = 1", 14 );
		}
		else
		{
			qfileFile.writeBlock( "\nPressure = 0", 14 );
		}
		if (m_driverDriver[ intI ].ImpedanzisActive)
		{
			qfileFile.writeBlock( "\nImpedanz = 1", 14 );
		}
		else
		{
			qfileFile.writeBlock( "\nImpedanz = 0", 14 );
		}
		if (m_driverDriver[ intI ].SummaryisActive)
		{
			qfileFile.writeBlock( "\nSummary = 1", 13 );
		}
		else
		{
			qfileFile.writeBlock( "\nSummary = 0", 13 );
		}
		if (m_driverDriver[ intI ].ScalarSummaryisActive)
		{
			qfileFile.writeBlock( "\nScalarSummary = 1", 18 );
		}
		else
		{
			qfileFile.writeBlock( "\nScalarSummary = 0", 18 );
		}
		if (m_driverDriver[ intI ].ImpedanzSummaryisActive)
		{
			qfileFile.writeBlock( "\nImpedanzSummary = 1", 20 );
		}
		else
		{
			qfileFile.writeBlock( "\nImpedanzSummary = 0", 20 );
		}
		if (m_driverDriver[ intI ].InvertPhase)
		{
			qfileFile.writeBlock( "\nInvertPhase = 1", 16 );
		}
		else
		{
			qfileFile.writeBlock( "\nInvertPhase = 0", 15 );
		}
		qfileFile.writeBlock( "\nTitle = ", 8);
    QString test = m_driverDriver[ intI ].GetTitle();
		qfileFile.writeBlock( m_driverDriver[ intI ].GetTitle(), test.length() );
	}


	qfileFile.close();
  modified=false;
  return true;
}

void KFilterDoc::deleteContents()
{
  /////////////////////////////////////////////////
  // TODO: Add implementation to delete the document contents
  /////////////////////////////////////////////////
for (int intI = 0; intI < 4; intI++ )
  {
    m_driverDriver[ intI ].initContents();
  }
  modified = false;

}

double KFilterDoc::DB( double a_doubleA )
{
  return ( 8.685889638 * log( a_doubleA ) );
}

void KFilterDoc::initParamDialog()
{
  KFilterApp *pfilterappApplication = (KFilterApp *) parent();
  //pfilterappApplication->DisableCommand( ID_DRIVER_PARAM );

  driverinput* driverinputDialog = new driverinput( i18n("Driver Parameters"), \
    &m_driverDriver[0], &m_driverDriver[1], &m_driverDriver[2], &m_driverDriver[3]);
  driverinputDialog->show();
  QObject::connect( driverinputDialog, SIGNAL( paramchanged() ), this, SLOT( viewrefresh() ) );
  QObject::connect( driverinputDialog, SIGNAL( isclosed() ), pfilterappApplication, SLOT( slotEnableDriverParam() ) );
  QObject::connect( this, SIGNAL( refreshDialog() ), driverinputDialog, SLOT( slot_initnewvalues() ) );
}

void KFilterDoc::initNetworkDialog()
{
	KFilterApp *pfilterappApplication = (KFilterApp *)parent();
	//pfilterappApplication->DisableCommand( ID_DRIVER_NETWORK );

	NetworkDialog* pnetworkdialogDialog = new NetworkDialog( i18n("Frequency Range Network Parameters"),
		&m_driverDriver[0], &m_driverDriver[1], &m_driverDriver[2], &m_driverDriver[3] );
	pnetworkdialogDialog-> show();
	QObject::connect( pnetworkdialogDialog, SIGNAL( paramchanged() ), this, SLOT( viewrefresh() ) );
	QObject::connect( pnetworkdialogDialog, SIGNAL( isclosed() ), pfilterappApplication, SLOT( slotEnableDriverNetwork() ) );
	QObject::connect( this, SIGNAL(refreshDialog() ), pnetworkdialogDialog, SLOT( slot_initnewvalues() ) );
}

void KFilterDoc::initVolumeDialog()
{
	KFilterApp *pfilterappApplication= (KFilterApp *)parent();
	//pfilterappApplication->DisableCommand( ID_DRIVER_VOLUME );

	VolumeDialog* pvolumedialogDialog = new VolumeDialog( i18n("Box and Volume Parameters"),
		&m_driverDriver[0], &m_driverDriver[1], &m_driverDriver[2], &m_driverDriver[3] );
	pvolumedialogDialog-> show();
	QObject::connect( pvolumedialogDialog, SIGNAL( paramchanged() ), this, SLOT( viewrefresh() ) );
	QObject::connect( pvolumedialogDialog, SIGNAL( isclosed() ), pfilterappApplication, SLOT( slotEnableDriverVolume() ) );
}

void KFilterDoc::initToolsWizard()

{
  KFilterApp *pfilterappApplication = (KFilterApp *)parent();
  Wizard* pwizardDialog = new Wizard( pfilterappApplication, "Filter Wizard",
    &m_driverDriver[0], &m_driverDriver[1], &m_driverDriver[2], &m_driverDriver[3] );
  pwizardDialog->show();
  QObject::connect( pwizardDialog, SIGNAL( isclosed() ), this, SLOT( slotUpdateAllDialogs() ) );
}

bool KFilterDoc::Sound( int a_intIndex )
{
  if (m_driverDriver[ a_intIndex ].PressureisActive )
  {
    m_driverDriver[ a_intIndex ].Schall();
    int intJ = 0;
    for (int intI = 0; intI < 300; intI = intI + 2 )
    {
      m_doubleXContainer[ a_intIndex ][ intJ ] = DB( sqrt( pow( \
        m_driverDriver[ a_intIndex ].ResultSchall[ intI ], 2.0 ) + \
        pow( m_driverDriver[ a_intIndex ].ResultSchall[ intI + 1 ], 2.0 ) ) );
      intJ++;
    }
  }
  return m_driverDriver[ a_intIndex ].PressureisActive;
}

bool KFilterDoc::Impedance( int a_intIndex )
{
	if (m_driverDriver[ a_intIndex ].ImpedanzisActive)
	{
		m_driverDriver[ a_intIndex ].Impedanz();
		int intJ = 0;
		for (int intI = 0; intI < 300; intI = intI + 2 )
		{
			m_doubleXContainer[ a_intIndex ][ intJ ] = sqrt( pow( \
				m_driverDriver[ a_intIndex ].ResultImpedanz[ intI ], 2.0 ) + \
				pow( m_driverDriver[ a_intIndex ].ResultImpedanz[ intI + 1 ], 2.0 ) );
			intJ++;
		}
	}
	return m_driverDriver[ a_intIndex ].ImpedanzisActive;
}

bool KFilterDoc::PressureSummary()
{
	/////////////////////////////init temp variable
	double doubleSum[ 300 ];
	for( int intZ = 0; intZ < 300; intZ++ )
	{
		doubleSum[ intZ ] = 0.0;
	}
	////////////////////////////// calculate vector summary for active drivers
	for( int intIndex = 0; intIndex < 4; intIndex++ )
	{
		if ( m_driverDriver[ intIndex ].SummaryisActive )
		{
			m_driverDriver[ intIndex ].Schall();
			for ( int intI = 0; intI < 300; intI++ )
			{
				doubleSum[ intI ] = doubleSum[ intI ] + \
					m_driverDriver[ intIndex ].ResultSchall[ intI ];
			}
		}
	}
	////////////////////////////// vector summary becomes real summary
	int intZ = 0;
	for (int intI = 0; intI < 300; intI = intI + 2 )
	{
		m_doubleXContainer[ 0 ][ intZ ] = DB( sqrt( pow( doubleSum[ intI ], 2.0 ) + \
			pow( doubleSum[ intI + 1 ], 2.0 ) ) );
		intZ++;
	}
	///////////////////////////////
	return ( m_driverDriver[ 0 ].SummaryisActive || m_driverDriver[ 1 ].SummaryisActive || \
		m_driverDriver[ 2 ].SummaryisActive || m_driverDriver[ 3 ].SummaryisActive);
}

bool KFilterDoc::PressureScalarSummary()
{
	///////////////////init m_doubleXContainer
	for ( int intI = 0; intI < 150; intI++ )
	{
		m_doubleXContainer[ 0 ][ intI ] = 0;
	}

	for ( int intIndex = 0; intIndex < 4; intIndex++ )
	{
		if ( m_driverDriver[ intIndex ].ScalarSummaryisActive )
		{
			m_driverDriver[ intIndex ].Schall();
			int intJ = 0;
			for ( int intI = 0; intI < 300; intI = intI + 2 )
			{
				//		turbo pascal version				dB0-round(	ln(sqrt(sqr(qx1)+sqr(qy1)+sqr(qx2)+sqr(qy2)+sqr(qx3)+sqr(qy3))	)
				//  	old C version 				m_doubleXContainer[0][j] = m_doubleXContainer[0][j] + sqrt(pow(m_driverDriver[index].ResultSchall[i],2.0)+pow(m_driverDriver[index].ResultSchall[i+1],2.0));
				m_doubleXContainer[ 0 ][ intJ ] = \
					m_doubleXContainer[ 0 ][ intJ ] + pow( m_driverDriver[ intIndex ].ResultSchall[ intI ], 2.0) + \
					pow( m_driverDriver[ intIndex ].ResultSchall[ intI + 1 ], 2.0 );
				intJ++;
			}
		}
	}
	for (int intI = 0; intI < 150; intI++ )
	{
		m_doubleXContainer[ 0 ][ intI ] = DB( sqrt( m_doubleXContainer[ 0 ][ intI ] ) );
	}
	///////////////////////////////
	return ( m_driverDriver[ 0 ].ScalarSummaryisActive || m_driverDriver[ 1 ].ScalarSummaryisActive || \
		m_driverDriver[ 2 ].ScalarSummaryisActive || m_driverDriver[ 3 ].ScalarSummaryisActive );
}

bool KFilterDoc::ImpedanceSummary()
{

	double doubleSum[ 300 ];
	for ( int intZ = 0; intZ < 300; intZ++ )
	{
		doubleSum[ intZ ] = 0;
	}
	////////////////////////////// calculate vector summary for active drivers
	for ( int intIndex = 0; intIndex < 4; intIndex++ )
	{
		if ( m_driverDriver[ intIndex ].ImpedanzSummaryisActive )
		{
			m_driverDriver[ intIndex ].Impedanz();
			m_driverDriver[ intIndex ].invertImpedanz();
			for ( int intI = 0; intI < 300; intI++ )
			{
				doubleSum[ intI ]= doubleSum[ intI ] + m_driverDriver[ intIndex ].ResultImpedanz[ intI ];
			}
			m_driverDriver[ intIndex ].invertImpedanz();
		}
	}
	////////////////////////////// vector summary becomes real summary
	int intZ = 0;
	for ( int intI = 0; intI < 300; intI = intI + 2 )
	{
		m_doubleXContainer[ 0 ][ intZ ] = 1.0 / ( sqrt( pow( doubleSum[ intI ], 2.0 ) +\
			pow( doubleSum[ intI + 1 ], 2.0 ) ) );
		intZ++;
	}
	///////////////////////////////
	return ( m_driverDriver[ 0 ].ImpedanzSummaryisActive || m_driverDriver[ 1 ].ImpedanzSummaryisActive || \
		m_driverDriver[ 2 ].ImpedanzSummaryisActive || m_driverDriver[ 3 ].ImpedanzSummaryisActive);
}

/** is called when open dialogs
need an update */
void KFilterDoc::slotUpdateAllDialogs()
{
  emit refreshDialog();
  emit forceviewrefresh();
}

void KFilterDoc::viewrefresh()
{
  emit forceviewrefresh();
}


void KFilterDoc::truncatedFile( QFile* a_pqfileFile)
{
	a_pqfileFile->close();
	for ( int intI = 0; intI < 3; intI++ )
	{
		m_driverDriver[ intI ].Berechneparameter();
		m_driverDriver[ intI ].setmodified();
	}
	emit forceviewrefresh();
	modified = false;
}

