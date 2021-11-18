#pragma once

#include <glib.h>
#include <glib-object.h>
#include <sn-item.h>
#include <stdbool.h>
#include <gtk/gtk.h>
#include <libhildondesktop/libhildondesktop.h>

G_BEGIN_DECLS
#define SYSTRAY_APPLET_TYPE             (systray_applet_get_type ())
#define SYSTRAY_APPLET(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), SYSTRAY_APPLET_TYPE, SystrayApplet))
#define SYSTRAY_APPLET_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), SYSTRAY_APPLET_TYPE, SystrayAppletClass))
#define SYSTRAY_IS_APPLET(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), SYSTRAY_APPLET_TYPE))
#define SYSTRAY_IS_APPLET_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), SYSTRAY_APPLET_TYPE))
#define SYSTRAY_IS_APPLET_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), SYSTRAY_APPLET_TYPE, SystrayAppletClass))
typedef struct _SystrayApplet SystrayApplet;
typedef struct _SystrayAppletClass SystrayAppletClass;

struct _SystrayApplet {
	HDStatusMenuItem parent_instance;
};

struct _SystrayAppletClass {
	HDStatusMenuItemClass parent_class;
};

GType systray_applet_get_type(void);

SystrayApplet *systray_applet_new(SnItem *item);

bool systray_applet_is_item(SystrayApplet *applet, SnItem *item);

G_END_DECLS
