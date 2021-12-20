#include "systray-applet.h"

#include <string.h>
#include <gtk/gtk.h>
#include <hildon/hildon.h>
#include <libosso.h>

#include "sn-item.h"

#ifdef HILDON_DISABLE_DEPRECATED
#undef HILDON_DISABLE_DEPRECATED
#endif

#define SYSTRAY_APPLET_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), \
                        SYSTRAY_APPLET_TYPE, SystrayAppletPrivate))
typedef struct _SystrayAppletPrivate SystrayAppletPrivate;

struct _SystrayAppletPrivate
{
  GtkWidget *applet_button;
  SnItem *item;
  GtkWidget *image;
  gint timer;
  bool inhibit_click;
};

enum
{
  PROP_0,
  PROP_ITEM
};


G_DEFINE_TYPE_WITH_PRIVATE (SystrayApplet, systray_applet,
                            HD_TYPE_STATUS_MENU_ITEM)
     static void systray_applet_finalize (GObject * object);
     
static gboolean
systray_applet_on_button_longpressed (void *data)
{
  SystrayAppletPrivate *priv = SYSTRAY_APPLET_GET_PRIVATE (data);
  priv->inhibit_click = true;
  gint wx, wy;
  gint sx, sy;
  gtk_widget_translate_coordinates(GTK_WIDGET(priv->applet_button),
                                   gtk_widget_get_toplevel(GTK_WIDGET(priv->applet_button)), 0, 0, &wx, &wy);
  gdk_window_get_origin (gtk_widget_get_window (GTK_WIDGET(priv->applet_button)), &sx, &sy);
  sn_item_secondary_activate(priv->item, sx+wx, sy+wy);
  return FALSE;
}

/* Setup applet and dialogs: */
static void
systray_applet_on_button_pressed (GtkWidget *button, SystrayApplet *plugin)
{
  SystrayAppletPrivate *priv = SYSTRAY_APPLET_GET_PRIVATE (plugin);
  priv->timer = g_timeout_add_seconds(2, systray_applet_on_button_longpressed, plugin);
}

static void
systray_applet_on_button_clicked (GtkWidget *button, SystrayApplet *plugin)
{
  SystrayAppletPrivate *priv = SYSTRAY_APPLET_GET_PRIVATE (plugin);
  if (!priv->inhibit_click)
    {
      gint wx, wy;
      gint sx, sy;
      gtk_widget_translate_coordinates(GTK_WIDGET(button), gtk_widget_get_toplevel(GTK_WIDGET(button)), 0, 0, &wx, &wy);
      gdk_window_get_origin (gtk_widget_get_window (GTK_WIDGET(button)), &sx, &sy);
      sn_item_activate(priv->item, sx+wx, sy+wy);
       if(priv->timer)
        {
          g_source_remove(priv->timer);
          priv->timer = 0;
        }
    }
  else
    {
      priv->inhibit_click = false;
    }
}

static void
systray_applet_apply_icon (GtkWidget *image,
                           GtkIconTheme *icon_theme,
                           GtkIconTheme *icon_theme_from_path,
                           const gchar *icon_name,
                           GdkPixbuf *icon_pixbuf, gint icon_size)
{
  GtkIconInfo *icon_info = NULL;
  GdkPixbuf *work_pixbuf = NULL;
  gchar *work_icon_name = NULL;
  gchar *symbolic_icon_name = NULL;
  gboolean use_pixbuf = TRUE;
  gboolean use_symbolic = FALSE;
  gint width, height;
  gchar *s1, *s2;
  gint max_size = icon_size;

  gtk_image_clear (GTK_IMAGE (image));

#define sn_preferred_name() (work_icon_name != NULL ? work_icon_name : icon_name)
#define sn_preferred_pixbuf() (work_pixbuf != NULL ? work_pixbuf : icon_pixbuf)

  if (icon_name != NULL)
    {
      if (icon_name[0] == '/')
        {
          /* it's a path to file */
          if (g_file_test (icon_name, G_FILE_TEST_IS_REGULAR))
            work_pixbuf = gdk_pixbuf_new_from_file (icon_name, NULL);

          if (work_pixbuf == NULL)
            {
              /* try to extract icon name from path */
              s1 = g_strrstr (icon_name, "/");
              s2 = g_strrstr (icon_name, ".");

              if (s2 != NULL)
                work_icon_name = g_strndup (&s1[1], (gint) (s2 - s1) - 1);
              else
                work_icon_name = g_strdup (&s1[1]);
            }
        }

      if (work_pixbuf == NULL && icon_theme_from_path != NULL)
        {
          /* load icon in its real size */
          work_pixbuf = gtk_icon_theme_load_icon (icon_theme_from_path,
                                                  sn_preferred_name (),
                                                  -1, 0, NULL);

          if (work_pixbuf == NULL ||
              (gdk_pixbuf_get_width (work_pixbuf) <= 1
               || gdk_pixbuf_get_height (work_pixbuf) <= 1))
            {
              if (work_pixbuf != NULL)
                g_object_unref (work_pixbuf);

              /* icon size was incorrect, try to pass the desired icon size */
              work_pixbuf = gtk_icon_theme_load_icon (icon_theme_from_path,
                                                      sn_preferred_name (),
                                                      icon_size, 0, NULL);
            }
        }

      if (work_pixbuf == NULL)
        {
          if (icon_info == NULL)
            {
              icon_info = gtk_icon_theme_lookup_icon (icon_theme,
                                                      sn_preferred_name (),
                                                      icon_size, 0);
            }

          if (icon_info != NULL)
            {
              gtk_image_set_from_icon_name (GTK_IMAGE (image),
                                            use_symbolic
                                            ? symbolic_icon_name
                                            : sn_preferred_name (),
                                            GTK_ICON_SIZE_BUTTON);
              g_object_unref (icon_info);
              use_pixbuf = FALSE;
            }
        }
    }

  if (use_pixbuf && sn_preferred_pixbuf () != NULL)
    {
      width = gdk_pixbuf_get_width (sn_preferred_pixbuf ());
      height = gdk_pixbuf_get_height (sn_preferred_pixbuf ());

      if (width > icon_size && height > icon_size)
        {
          /* scale pixbuf */
          if (height > width)
            {
              height = icon_size * height / width;
              width = icon_size;
            }
          else
            {
              width = icon_size * width / height;
              height = icon_size;
            }

          icon_pixbuf = gdk_pixbuf_scale_simple (sn_preferred_pixbuf (),
                                                 width, height,
                                                 GDK_INTERP_BILINEAR);
          gtk_image_set_from_pixbuf (GTK_IMAGE (image), icon_pixbuf);
          g_object_unref (icon_pixbuf);
        }
      else
        {
          gtk_image_set_from_pixbuf (GTK_IMAGE (image),
                                     sn_preferred_pixbuf ());
        }
    }

#undef sn_preferred_pixbuf
#undef sn_preferred_name

  if (work_pixbuf != NULL)
    g_object_unref (work_pixbuf);

  if (work_icon_name != NULL)
    g_free (work_icon_name);

  if (symbolic_icon_name != NULL)
    g_free (symbolic_icon_name);

  gtk_image_set_pixel_size (GTK_IMAGE (image), max_size);
}

static void
systray_applet_setup_icon_changed (SystrayApplet *applet)
{
  SystrayAppletPrivate *priv = SYSTRAY_APPLET_GET_PRIVATE (applet);
  const gchar *icon_name = NULL;
  GdkPixbuf *icon_pixbuf = NULL;
  const gchar *overlay_icon_name = NULL;
  GdkPixbuf *overlay_icon_pixbuf = NULL;
  const gchar *theme_path = NULL;
  GtkIconTheme *icon_theme = NULL;
  GtkIconTheme *icon_theme_from_path = NULL;
  gint icon_size = 32;

  icon_theme =
    gtk_icon_theme_get_for_screen (gtk_widget_get_screen
                                   (GTK_WIDGET (applet)));

  sn_item_get_icon (priv->item, &theme_path,
                    &icon_name, &icon_pixbuf,
                    &overlay_icon_name, &overlay_icon_pixbuf);
  if (theme_path != NULL)
    {
      icon_theme_from_path = gtk_icon_theme_new ();
      gtk_icon_theme_prepend_search_path (icon_theme_from_path, theme_path);
    }

  systray_applet_apply_icon (GTK_WIDGET (priv->image), icon_theme,
                             icon_theme_from_path, icon_name, icon_pixbuf,
                             icon_size);

  if (icon_theme_from_path != NULL)
    g_object_unref (icon_theme_from_path);
}

static char*
systray_applet_truncate_newline_dup (const char* str)
{
  char *n_name = g_strdup(str);
  for(char *i_name = n_name; *i_name != '\0'; ++i_name)
    {
      if(*i_name == '\n')
        *i_name = '\0';
    }
    return n_name;
}

static void
systray_applet_setup_tooltip_changed (SystrayApplet * applet)
{
  SystrayAppletPrivate *priv = SYSTRAY_APPLET_GET_PRIVATE (applet);
  const gchar *name = NULL;
  const gchar *secondary = NULL;

  sn_item_get_tooltip (priv->item, &name, &secondary);
  if (name)
    {
      char *n_name = systray_applet_truncate_newline_dup(name);
      hildon_button_set_title (HILDON_BUTTON (priv->applet_button), n_name);
      g_free(n_name);
    }
    
  if (secondary)
    {
      char *n_secondary = systray_applet_truncate_newline_dup(secondary);
      hildon_button_set_value (HILDON_BUTTON (priv->applet_button), n_secondary);
      g_free(n_secondary);
    }
}

static void
systray_applet_setup (SystrayApplet *plugin)
{
  SystrayAppletPrivate *priv = SYSTRAY_APPLET_GET_PRIVATE (plugin);
  GdkPixbuf *pixbuf = NULL;

  priv->applet_button =
    hildon_button_new (HILDON_SIZE_AUTO_WIDTH | HILDON_SIZE_FINGER_HEIGHT,
                       HILDON_BUTTON_ARRANGEMENT_VERTICAL);
    hildon_button_set_style(HILDON_BUTTON (priv->applet_button), HILDON_BUTTON_STYLE_NORMAL);
    hildon_button_set_alignment(HILDON_BUTTON(priv->applet_button), 0.5, 0, 1, 1);
  g_signal_connect (priv->applet_button, "pressed",
                    G_CALLBACK (systray_applet_on_button_pressed), plugin);
  g_signal_connect (priv->applet_button, "released",
                    G_CALLBACK (systray_applet_on_button_clicked), plugin);

  pixbuf =
    gtk_icon_theme_load_icon (gtk_icon_theme_get_default (),
                              "general_brightness", 64, 0, NULL);
  if (pixbuf)
    {
      priv->image = gtk_image_new_from_pixbuf (pixbuf);
      g_object_unref (pixbuf);
      pixbuf = NULL;
    }
  else
    {
      priv->image = gtk_image_new ();
    }
  hildon_button_set_image (HILDON_BUTTON (priv->applet_button), priv->image);
}

static void
systray_applet_set_property (GObject *object,
                             guint prop_id,
                             const GValue *value, GParamSpec *pspec)
{
  SystrayAppletPrivate *priv =
    SYSTRAY_APPLET_GET_PRIVATE (SYSTRAY_APPLET (object));

  switch (prop_id)
    {
    case PROP_ITEM:
      /* The property is CONSTRUCT_ONLY so there is no value yet */
      priv->item = g_value_dup_object (value);
      if (priv->item != NULL)
        {
          g_signal_connect_swapped (priv->item, "icon-changed",
                                    G_CALLBACK
                                    (systray_applet_setup_icon_changed),
                                    object);
          g_signal_connect_swapped (priv->item, "tooltip-changed",
                                    G_CALLBACK
                                    (systray_applet_setup_tooltip_changed),
                                    object);
          systray_applet_setup_icon_changed (SYSTRAY_APPLET (object));
          systray_applet_setup_tooltip_changed (SYSTRAY_APPLET (object));
        }
      else
        g_warning ("item should not be NULL");
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

/* GObject stuff: */
static void
systray_applet_class_init (SystrayAppletClass * klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  object_class->set_property = systray_applet_set_property;

  g_object_class_install_property (object_class,
                                   PROP_ITEM,
                                   g_param_spec_object ("item",
                                                        "item to display",
                                                        "The StatusNotifierItem item to display",
                                                        TYPE_SN_ITEM,
                                                        G_PARAM_WRITABLE |
                                                        G_PARAM_CONSTRUCT_ONLY));
  object_class->finalize = systray_applet_finalize;
}


static void
systray_applet_init (SystrayApplet *plugin)
{
  SystrayAppletPrivate *priv = SYSTRAY_APPLET_GET_PRIVATE (plugin);
  memset (priv, 0, sizeof (SystrayAppletPrivate));

  systray_applet_setup (plugin);

  gtk_container_add (GTK_CONTAINER (plugin),
                     GTK_WIDGET (priv->applet_button));
  gtk_widget_show_all (GTK_WIDGET (plugin));
}

static void
systray_applet_finalize (GObject *object)
{
  G_OBJECT_CLASS (systray_applet_parent_class)->finalize (object);
}

bool
systray_applet_is_item (SystrayApplet *applet, SnItem *item)
{
  SystrayAppletPrivate *priv = SYSTRAY_APPLET_GET_PRIVATE (applet);
  return priv->item == item;
}

SystrayApplet *
systray_applet_new (SnItem *item)
{
  return g_object_new (SYSTRAY_APPLET_TYPE, "item", item, NULL);
}
