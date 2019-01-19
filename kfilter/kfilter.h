/***************************************************************************
                          kfilter.h  -  description
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

#ifndef KFILTER_H
#define KFILTER_H
 

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

// include files for Qt

// include files for KDE 
#include <kapp.h>
#include <kmainwindow.h>
#include <kaccel.h>
#include <kaction.h>
#include <kurl.h>

// forward declaration of the KFilter classes
class KFilterDoc;
class KFilterView;

/**
  * The base class for KFilter application windows. It sets up the main
  * window and reads the config file as well as providing a menubar, toolbar
  * and statusbar. An instance of KFilterView creates your center view, which is connected
  * to the window's Doc object.
  * KFilterApp reimplements the methods that KMainWindow provides for main window handling and supports
  * full session management as well as using KActions.
  * @see KMainWindow
  * @see KApplication
  * @see KConfig
  *
  * @author Source Framework Automatically Generated by KDevelop, (c) The KDevelop Team.
  * @version KDevelop version 1.2 code generation
  */
class KFilterApp : public KMainWindow
{
  Q_OBJECT

  friend class KFilterView;

  public:
    /** construtor of KFilterApp, calls all init functions to create the application.
     */
    KFilterApp(QWidget* parent=0, const char* name=0);
    ~KFilterApp();
    /** opens a file specified by commandline option
     */
    void openDocumentFile(const KURL& url=0);
    /** returns a pointer to the current document connected to the KTMainWindow instance and is used by
     * the View class to access the document object's methods
     */	
    KFilterDoc *getDocument() const;
    /** enables menuentries/toolbar items
    */
    //void EnableCommand(int id_);
    /** disables menuentries/toolbar items
    */
    //void DisableCommand(int id_);

  protected:
    /** save general Options like all bar positions and status as well as the geometry and the recent file list to the configuration
     * file
     */ 	
    void saveOptions();
    /** read general Options again and initialize all variables like the recent file list
     */
    void readOptions();
    /** initializes the KActions of the application */
    void initActions();
    /** sets up the statusbar for the main window by initialzing a statuslabel.
     */
    void initStatusBar();
    /** initializes the document object of the main window that is connected to the view in initView().
     * @see initView();
     */
    void initDocument();
    /** creates the centerwidget of the KTMainWindow instance and sets it as the view
     */
    void initView();
    /** queryClose is called by KTMainWindow on each closeEvent of a window. Against the
     * default implementation (only returns true), this calles saveModified() on the document object to ask if the document shall
     * be saved if Modified; on cancel the closeEvent is rejected.
     * @see KTMainWindow#queryClose
     * @see KTMainWindow#closeEvent
     */
    virtual bool queryClose();
    /** queryExit is called by KTMainWindow when the last window of the application is going to be closed during the closeEvent().
     * Against the default implementation that just returns true, this calls saveOptions() to save the settings of the last window's	
     * properties.
     * @see KTMainWindow#queryExit
     * @see KTMainWindow#closeEvent
     */
    virtual bool queryExit();
    /** saves the window properties for each open window during session end to the session config file, including saving the currently
     * opened file by a temporary filename provided by KApplication.
     * @see KTMainWindow#saveProperties
     */
    virtual void saveProperties(KConfig *_cfg);
    /** reads the session config file and restores the application's state including the last opened files and documents by reading the
     * temporary files saved by saveProperties()
     * @see KTMainWindow#readProperties
     */
    virtual void readProperties(KConfig *_cfg);

  public slots:

    void slotFileNewWindow();
    /** clears the document in the actual view to reuse it as the new document */
    void slotFileNew();
    /** open a file and load it into the document*/
    void slotFileOpen();
    /** opens a file from the recent files menu */
    void slotFileOpenRecent(const KURL& url);
    /** save a document */
    void slotFileSave();
    /** save a document by a new filename*/
    void slotFileSaveAs();
    /** asks for saving if the file is modified, then closes the actual file and window*/
    void slotFileClose();
    /** print the actual file */
    void slotFilePrint();
    /** closes all open windows by calling close() on each memberList item until the list is empty, then quits the application.
     * If queryClose() returns false because the user canceled the saveModified() dialog, the closing breaks.
     */
    void slotFileQuit();
    /** put the marked text/object into the clipboard and remove
     *	it from the document
     */
    void slotEditCut();
    /** put the marked text/object into the clipboard
     */
    void slotEditCopy();
    /** paste the clipboard into the document
     */
    void slotEditPaste();
    /** toggles the toolbar
     */
    void slotViewToolBar();
    /** toggles the statusbar
     */
    void slotViewStatusBar();
    /**
     */
    void slotDriverParam();
    /**
     */
    void slotEnableDriverParam();
    /** 
     */
    void slotDriverNetwork();
    /**
     */
    void slotEnableDriverNetwork();
    /** 
     */
    void slotDriverVolume();
    /**
     */
    void slotEnableDriverVolume();
    /** 
     */
    void slotToolsWizard();
    /**
     */
    void slotOptionsColors();
    /**
     */
    void slotEnableOptionsColors();
    /**
     */
    void slotrefreshview();
    /** changes the statusbar contents for the standard label permanently, used to indicate current actions.
     * @param text the text that is displayed in the statusbar
     */
    void slotStatusMsg(const QString &text);

  private:
    /** the configuration object of the application */
    KConfig *config;
    /** view is the main widget which represents your working area. The View
     * class should handle all events of the view widget.  It is kept empty so
     * you can create your view according to your application's needs by
     * changing the view class.
     */
    KFilterView *view;
    /** doc represents your actual document and is created only once. It keeps
     * information such as filename and does the serialization of your files.
     */
    KFilterDoc *doc;

    // KAction pointers to enable/disable actions
    KAction* fileNewWindow;
    KAction* fileNew;
    KAction* fileOpen;
    KRecentFilesAction* fileOpenRecent;
    KAction* fileSave;
    KAction* fileSaveAs;
    KAction* fileClose;
    KAction* filePrint;
    KAction* fileQuit;
    KAction* editCut;
    KAction* editCopy;
    KAction* editPaste;
    ///selfdefined
    KAction* driverParameter;
    KAction* driverNetwork;
    KAction* driverVolume;
    KAction* toolsWizard;
    KAction* optionsColors;
    ///
    KToggleAction* viewToolBar;
    KToggleAction* viewStatusBar;

    //QPopupMenu* m_DriverMenu;
    //QPopupMenu* m_ToolsMenu;
    //QPopupMenu* m_OptionsMenu;

};
 
#endif // KFILTER_H
