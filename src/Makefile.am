bin_PROGRAMS = hildon-status-menu

hildondesktopconf_DATA = \
	status-menu.conf	\
	status-menu.plugins

hildon_status_menu_CFLAGS = \
	$(HILDON_CFLAGS)							\
	$(LIBHILDONDESKTOP_CFLAGS)						\
	$(GCONF_CFLAGS)								\
	$(X11_CFLAGS)								\
	$(GIO_CFLAGS)								\
	$(GIO_UNIX_CFLAGS)							\
	-DHD_DESKTOP_CONFIG_PATH=\"$(hildondesktopconfdir)\"			\
	$(MAEMO_LAUNCHER_CFLAGS)

hildon_status_menu_built_sources = \
	sn-watcher.h \
	sn-watcher.c

hildon_status_menu_SOURCES = \
	$(hildon_status_menu_built_sources)					\
	hildon-status-menu.c							\
	hd-status-area.c							\
	hd-status-area.h							\
	hd-status-area-box.c							\
	hd-status-area-box.h							\
	hd-status-menu.c							\
	hd-status-menu.h							\
	hd-status-menu-box.c							\
	hd-status-menu-box.h							\
	hd-desktop.c								\
	hd-desktop.h								\
	hd-display.c								\
	sn-backend.h								\
	sn-backend.c								\
	sn-item.h								\
	sn-item.c								\
	systray-applet.h							\
	systray-applet.c

hildon_status_menu_LDFLAGS = \
	$(HILDON_LIBS)	    							\
	$(LIBHILDONDESKTOP_LIBS)						\
	$(GCONF_LIBS)								\
	$(X11_LIBS)								\
	$(GIO_LIBS)								\
	$(GIO_UNIX_LIBS)							\
	$(MAEMO_LAUNCHER_LIBS)

#sn-watcher.h:
#sn-watcher.c: sn-watcher.xml Makefile
#	$(AM_V_GEN) $(GDBUS_CODEGEN) \
#	--interface-prefix org.kde.StatusNotifierWatcher \
#	--generate-c-code sn-watcher \
#	$(srcdir)/sn-watcher.xml
