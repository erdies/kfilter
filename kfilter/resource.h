/***************************************************************************
                          resource.h  -  description
                             -------------------
    begin                : Sun Mar 19 11:30:14 MET 2000
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

#ifndef RESOURCE_H
#define RESOURCE_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
///////////////////////////////////////////////////////////////////
// resource.h  -- contains macros used for commands
///////////////////////////////////////////////////////////////////
// COMMAND VALUES FOR MENUBAR AND TOOLBAR ENTRIES
///////////////////////////////////////////////////////////////////
// File-menu entries

/*
#define ID_FILE_NEW_WINDOW          10010
#define ID_FILE_NEW                 10020
#define ID_FILE_OPEN                10030
#define ID_FILE_OPEN_RECENT         10040
#define ID_FILE_CLOSE               10050
#define ID_FILE_SAVE                10060
#define ID_FILE_SAVE_AS             10070
#define ID_FILE_PRINT               10080
#define ID_FILE_QUIT                10090
///////////////////////////////////////////////////////////////////
// Edit-menu entries
#define ID_EDIT_COPY                11010
#define ID_EDIT_CUT                 11020
#define ID_EDIT_PASTE               11030
///////////////////////////////////////////////////////////////////
// View-menu entries
#define ID_VIEW_TOOLBAR             12010
#define ID_VIEW_STATUSBAR           12020
///////////////////////////////////////////////////////////////////
*/

//driver menue entries
#define ID_DRIVER_PARAM							12030
#define ID_DRIVER_NETWORK						12031
#define ID_DRIVER_VOLUME						12032
///////////////////////////////////////////////////////////////////
//tools menue entries
#define ID_TOOLS_WIZARD							12035
///////////////////////////////////////////////////////////////////
#define ID_OPTIONS_COLORS						12040
//////////////////////////////////////////////////////////////////

/*
// Help-menu entries
#define ID_HELP_CONTENTS            1002
///////////////////////////////////////////////////////////////////
// General application values
#define ID_STATUS_MSG               1001
#define IDS_STATUS_DEFAULT          "Ready."
*/

#endif // RESOURCE_H
