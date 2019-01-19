####### kdevelop will overwrite this part!!! (begin)##########
bin_PROGRAMS = kfilter

## INCLUDES were found outside kdevelop specific part

kfilter_SOURCES = driverinput.cpp driver.cpp wizard.cpp volumedialog.cpp networkdialog.cpp colordialog.cpp circuitout.cpp kfilterview.cpp kfilterdoc.cpp kfilter.cpp main.cpp 
kfilter_LDADD   =  $(LIB_QT) $(LIB_KDECORE) $(LIB_KDEUI) $(LIB_KFILE)  $(LIBSOCKET)


EXTRA_DIST = main.cpp kfilter.cpp kfilter.h kfilterdoc.cpp kfilterdoc.h kfilterview.cpp kfilterview.h kfilterui.rc kfilter.desktop lo32-app-kfilter.png lo16-app-kfilter.png circuitout.cpp circuitout.h colordialog.cpp colordialog.h networkdialog.cpp networkdialog.h volumedialog.cpp volumedialog.h wizard.cpp wizard.h driver.cpp driver.h driverinput.cpp driverinput.h bubble1.gif bubble2.gif bubble3.gif c.xpm con.xpm con3.xpm con4.xpm corner.xpm driver.xpm driverparam.xpm driversym.xpm fill.png filterwiz.xpm l.xpm mini-network.xpm mini-volume.xpm net.xpm net2.xpm net3.xpm r.xpm step1.xpm step2.xpm step3.xpm tux.gif volume0.xpm volume1.xpm volume2.xpm volume3.xpm wizard4.gif kfilter.desktop.mimetype 

install-data-local:
	$(mkinstalldirs) $(kde_datadir)/kfilter/
	$(INSTALL_DATA) $(srcdir)/kfilterui.rc $(kde_datadir)/kfilter/kfilterui.rc
	$(mkinstalldirs) $(kde_appsdir)/Applications/
	$(INSTALL_DATA) $(srcdir)/kfilter.desktop $(kde_appsdir)/Applications/kfilter.desktop
	$(mkinstalldirs) $(kde_icondir)/
	$(INSTALL_DATA) $(srcdir)/lo32-app-kfilter.png $(kde_icondir)/kfilter32.png
	$(mkinstalldirs) $(kde_icondir)/
	$(INSTALL_DATA) $(srcdir)/lo16-app-kfilter.png $(kde_icondir)/kfilter.png
	$(mkinstalldirs) $(kde_datadir)/kfilter/pics/
	$(INSTALL_DATA) $(srcdir)/bubble1.gif $(kde_datadir)/kfilter/pics/bubble1.gif
	$(mkinstalldirs) $(kde_datadir)/kfilter/pics/
	$(INSTALL_DATA) $(srcdir)/bubble2.gif $(kde_datadir)/kfilter/pics/bubble2.gif
	$(mkinstalldirs) $(kde_datadir)/kfilter/pics/
	$(INSTALL_DATA) $(srcdir)/bubble3.gif $(kde_datadir)/kfilter/pics/bubble3.gif
	$(mkinstalldirs) $(kde_datadir)/kfilter/pics/
	$(INSTALL_DATA) $(srcdir)/c.xpm $(kde_datadir)/kfilter/pics/c.xpm
	$(mkinstalldirs) $(kde_datadir)/kfilter/pics/
	$(INSTALL_DATA) $(srcdir)/con.xpm $(kde_datadir)/kfilter/pics/con.xpm
	$(mkinstalldirs) $(kde_datadir)/kfilter/pics/
	$(INSTALL_DATA) $(srcdir)/con3.xpm $(kde_datadir)/kfilter/pics/con3.xpm
	$(mkinstalldirs) $(kde_datadir)/kfilter/pics/
	$(INSTALL_DATA) $(srcdir)/con4.xpm $(kde_datadir)/kfilter/pics/con4.xpm
	$(mkinstalldirs) $(kde_datadir)/kfilter/pics/
	$(INSTALL_DATA) $(srcdir)/corner.xpm $(kde_datadir)/kfilter/pics/corner.xpm
	$(mkinstalldirs) $(kde_datadir)/kfilter/pics/
	$(INSTALL_DATA) $(srcdir)/driver.xpm $(kde_datadir)/kfilter/pics/driver.xpm
	$(mkinstalldirs) $(kde_datadir)/kfilter/pics/
	$(INSTALL_DATA) $(srcdir)/driverparam.xpm $(kde_datadir)/kfilter/pics/driverparam.xpm
	$(mkinstalldirs) $(kde_datadir)/kfilter/pics/
	$(INSTALL_DATA) $(srcdir)/driversym.xpm $(kde_datadir)/kfilter/pics/driversym.xpm
	$(mkinstalldirs) $(kde_datadir)/kfilter/pics/
	$(INSTALL_DATA) $(srcdir)/fill.png $(kde_datadir)/kfilter/pics/fill.png
	$(mkinstalldirs) $(kde_datadir)/kfilter/pics/
	$(INSTALL_DATA) $(srcdir)/filterwiz.xpm $(kde_datadir)/kfilter/pics/filterwiz.xpm
	$(mkinstalldirs) $(kde_datadir)/kfilter/pics/
	$(INSTALL_DATA) $(srcdir)/l.xpm $(kde_datadir)/kfilter/pics/l.xpm
	$(mkinstalldirs) $(kde_datadir)/kfilter/pics/
	$(INSTALL_DATA) $(srcdir)/mini-network.xpm $(kde_datadir)/kfilter/pics/mini-network.xpm
	$(mkinstalldirs) $(kde_datadir)/kfilter/pics/
	$(INSTALL_DATA) $(srcdir)/mini-volume.xpm $(kde_datadir)/kfilter/pics/mini-volume.xpm
	$(mkinstalldirs) $(kde_datadir)/kfilter/pics/
	$(INSTALL_DATA) $(srcdir)/net.xpm $(kde_datadir)/kfilter/pics/net.xpm
	$(mkinstalldirs) $(kde_datadir)/kfilter/pics/
	$(INSTALL_DATA) $(srcdir)/net2.xpm $(kde_datadir)/kfilter/pics/net2.xpm
	$(mkinstalldirs) $(kde_datadir)/kfilter/pics/
	$(INSTALL_DATA) $(srcdir)/net3.xpm $(kde_datadir)/kfilter/pics/net3.xpm
	$(mkinstalldirs) $(kde_datadir)/kfilter/pics/
	$(INSTALL_DATA) $(srcdir)/r.xpm $(kde_datadir)/kfilter/pics/r.xpm
	$(mkinstalldirs) $(kde_datadir)/kfilter/pics/
	$(INSTALL_DATA) $(srcdir)/step1.xpm $(kde_datadir)/kfilter/pics/step1.xpm
	$(mkinstalldirs) $(kde_datadir)/kfilter/pics/
	$(INSTALL_DATA) $(srcdir)/step2.xpm $(kde_datadir)/kfilter/pics/step2.xpm
	$(mkinstalldirs) $(kde_datadir)/kfilter/pics/
	$(INSTALL_DATA) $(srcdir)/step3.xpm $(kde_datadir)/kfilter/pics/step3.xpm
	$(mkinstalldirs) $(kde_datadir)/kfilter/pics/
	$(INSTALL_DATA) $(srcdir)/tux.gif $(kde_datadir)/kfilter/pics/tux.gif
	$(mkinstalldirs) $(kde_datadir)/kfilter/pics/
	$(INSTALL_DATA) $(srcdir)/volume0.xpm $(kde_datadir)/kfilter/pics/volume0.xpm
	$(mkinstalldirs) $(kde_datadir)/kfilter/pics/
	$(INSTALL_DATA) $(srcdir)/volume1.xpm $(kde_datadir)/kfilter/pics/volume1.xpm
	$(mkinstalldirs) $(kde_datadir)/kfilter/pics/
	$(INSTALL_DATA) $(srcdir)/volume2.xpm $(kde_datadir)/kfilter/pics/volume2.xpm
	$(mkinstalldirs) $(kde_datadir)/kfilter/pics/
	$(INSTALL_DATA) $(srcdir)/volume3.xpm $(kde_datadir)/kfilter/pics/volume3.xpm
	$(mkinstalldirs) $(kde_datadir)/kfilter/pics/
	$(INSTALL_DATA) $(srcdir)/wizard4.gif $(kde_datadir)/kfilter/pics/wizard4.gif
	$(mkinstalldirs) $(kde_mimedir)/application/
	$(INSTALL_DATA) $(srcdir)/kfilter.desktop.mimetype $(kde_mimedir)/application/kfilter.desktop

uninstall-local:
	-rm -f $(kde_datadir)/kfilter/kfilterui.rc
	-rm -f $(kde_appsdir)/Applications/kfilter.desktop
	-rm -f $(kde_icondir)/kfilter32.png
	-rm -f $(kde_icondir)/kfilter.png
	-rm -f $(kde_datadir)/kfilter/pics/bubble1.gif
	-rm -f $(kde_datadir)/kfilter/pics/bubble2.gif
	-rm -f $(kde_datadir)/kfilter/pics/bubble3.gif
	-rm -f $(kde_datadir)/kfilter/pics/c.xpm
	-rm -f $(kde_datadir)/kfilter/pics/con.xpm
	-rm -f $(kde_datadir)/kfilter/pics/con3.xpm
	-rm -f $(kde_datadir)/kfilter/pics/con4.xpm
	-rm -f $(kde_datadir)/kfilter/pics/corner.xpm
	-rm -f $(kde_datadir)/kfilter/pics/driver.xpm
	-rm -f $(kde_datadir)/kfilter/pics/driverparam.xpm
	-rm -f $(kde_datadir)/kfilter/pics/driversym.xpm
	-rm -f $(kde_datadir)/kfilter/pics/fill.png
	-rm -f $(kde_datadir)/kfilter/pics/filterwiz.xpm
	-rm -f $(kde_datadir)/kfilter/pics/l.xpm
	-rm -f $(kde_datadir)/kfilter/pics/mini-network.xpm
	-rm -f $(kde_datadir)/kfilter/pics/mini-volume.xpm
	-rm -f $(kde_datadir)/kfilter/pics/net.xpm
	-rm -f $(kde_datadir)/kfilter/pics/net2.xpm
	-rm -f $(kde_datadir)/kfilter/pics/net3.xpm
	-rm -f $(kde_datadir)/kfilter/pics/r.xpm
	-rm -f $(kde_datadir)/kfilter/pics/step1.xpm
	-rm -f $(kde_datadir)/kfilter/pics/step2.xpm
	-rm -f $(kde_datadir)/kfilter/pics/step3.xpm
	-rm -f $(kde_datadir)/kfilter/pics/tux.gif
	-rm -f $(kde_datadir)/kfilter/pics/volume0.xpm
	-rm -f $(kde_datadir)/kfilter/pics/volume1.xpm
	-rm -f $(kde_datadir)/kfilter/pics/volume2.xpm
	-rm -f $(kde_datadir)/kfilter/pics/volume3.xpm
	-rm -f $(kde_datadir)/kfilter/pics/wizard4.gif
	-rm -f $(kde_mimedir)/application/kfilter.desktop

####### kdevelop will overwrite this part!!! (end)############
# These paths are KDE specific. Use them:
# kde_appsdir         Where your application's menu entry (.desktop) should go to.
# kde_icondir         Where your icon should go to - better use KDE_ICON.
# kde_sounddir        Where your sounds should go to.
# kde_htmldir         Where your docs should go to. (contains lang subdirs)
# kde_datadir         Where you install application data. (Use a subdir)
# kde_locale          Where translation files should go to. (contains lang subdirs)
# kde_cgidir          Where cgi-bin executables should go to.
# kde_confdir         Where config files should go to (system-wide ones with default values).
# kde_mimedir         Where mimetypes .desktop files should go to.
# kde_servicesdir     Where services .desktop files should go to.
# kde_servicetypesdir Where servicetypes .desktop files should go to.
# kde_toolbardir      Where general toolbar icons should go to (deprecated, use KDE_ICON).
# kde_wallpaperdir    Where general wallpapers should go to.
# kde_templatesdir    Where templates for the "New" menu (Konqueror/KDesktop) should go to.
# kde_bindir          Where executables should go to. Use bin_PROGRAMS or bin_SCRIPTS.
# kde_libdir          Where shared libraries should go to. Use lib_LTLIBRARIES.
# kde_moduledir       Where modules (e.g. parts) should go to. Use kde_module_LTLIBRARIES.
# kde_styledir        Where Qt/KDE widget styles should go to (new in KDE 3).
# kde_designerdir     Where Qt Designer plugins should go to (new in KDE 3).

# set the include path for X, qt and KDE
INCLUDES= $(all_includes)

METASOURCES = AUTO

# the library search path. 
kfilter_LDFLAGS = $(all_libraries) $(KDE_RPATH)

rcdir = $(kde_datadir)/kfilter
rc_DATA = kfilterui.rc

messages: rc.cpp
	LIST=`find . -name \*.h -o -name \*.hh -o -name \*.H -o -name \*.hxx -o -name \*.hpp -o -name \*.cpp -o -name \*.cc -o -name \*.cxx -o -name \*.ecpp -o -name \*.C`; \
	if test -n "$$LIST"; then \
	 $(XGETTEXT) $$LIST -o $(podir)/kfilter.pot; \
	fi

