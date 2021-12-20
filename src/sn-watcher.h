/*
 * Generated by gdbus-codegen 2.58.3 from sn-watcher.xml. DO NOT EDIT.
 *
 * The license of this code is the same as for the D-Bus interface description
 * it was derived from.
 */

#ifndef __SN_WATCHER_H__
#define __SN_WATCHER_H__

#include <gio/gio.h>

G_BEGIN_DECLS
/* ------------------------------------------------------------------------ */
/* Declarations for org.kde.StatusNotifierWatcher */
#define TYPE_SN_WATCHER (sn_watcher_get_type ())
#define SN_WATCHER(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), TYPE_SN_WATCHER, SnWatcher))
#define IS_SN_WATCHER(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), TYPE_SN_WATCHER))
#define SN_WATCHER_GET_IFACE(o) (G_TYPE_INSTANCE_GET_INTERFACE ((o), TYPE_SN_WATCHER, SnWatcherIface))
  struct _SnWatcher;
typedef struct _SnWatcher SnWatcher;
typedef struct _SnWatcherIface SnWatcherIface;

struct _SnWatcherIface
{
  GTypeInterface parent_iface;



    gboolean (*handle_register_status_notifier_host) (SnWatcher * object,
                                                      GDBusMethodInvocation *
                                                      invocation,
                                                      const gchar *
                                                      arg_service);

    gboolean (*handle_register_status_notifier_item) (SnWatcher * object,
                                                      GDBusMethodInvocation *
                                                      invocation,
                                                      const gchar *
                                                      arg_service);

    gboolean (*get_is_status_notifier_host_registered) (SnWatcher * object);

    gint (*get_protocol_version) (SnWatcher * object);

  const gchar *const *(*get_registered_status_notifier_items) (SnWatcher *
                                                               object);

  void (*status_notifier_host_registered) (SnWatcher * object);

  void (*status_notifier_item_registered) (SnWatcher * object,
                                           const gchar * arg_service);

  void (*status_notifier_item_unregistered) (SnWatcher * object,
                                             const gchar * arg_service);

};

GType
sn_watcher_get_type (void)
  G_GNUC_CONST;

     GDBusInterfaceInfo *sn_watcher_interface_info (void);
     guint sn_watcher_override_properties (GObjectClass * klass,
                                           guint property_id_begin);


/* D-Bus method call completion functions: */
     void sn_watcher_complete_register_status_notifier_item (SnWatcher *
                                                             object,
                                                             GDBusMethodInvocation
                                                             * invocation);

     void sn_watcher_complete_register_status_notifier_host (SnWatcher *
                                                             object,
                                                             GDBusMethodInvocation
                                                             * invocation);



/* D-Bus signal emissions functions: */
     void sn_watcher_emit_status_notifier_item_registered (SnWatcher * object,
                                                           const gchar *
                                                           arg_service);

     void sn_watcher_emit_status_notifier_item_unregistered (SnWatcher *
                                                             object,
                                                             const gchar *
                                                             arg_service);

     void sn_watcher_emit_status_notifier_host_registered (SnWatcher *
                                                           object);



/* D-Bus method calls: */
     void sn_watcher_call_register_status_notifier_item (SnWatcher * proxy,
                                                         const gchar *
                                                         arg_service,
                                                         GCancellable *
                                                         cancellable,
                                                         GAsyncReadyCallback
                                                         callback,
                                                         gpointer user_data);

     gboolean sn_watcher_call_register_status_notifier_item_finish (SnWatcher
                                                                    * proxy,
                                                                    GAsyncResult
                                                                    * res,
                                                                    GError **
                                                                    error);

     gboolean sn_watcher_call_register_status_notifier_item_sync (SnWatcher *
                                                                  proxy,
                                                                  const gchar
                                                                  *
                                                                  arg_service,
                                                                  GCancellable
                                                                  *
                                                                  cancellable,
                                                                  GError **
                                                                  error);

     void sn_watcher_call_register_status_notifier_host (SnWatcher * proxy,
                                                         const gchar *
                                                         arg_service,
                                                         GCancellable *
                                                         cancellable,
                                                         GAsyncReadyCallback
                                                         callback,
                                                         gpointer user_data);

     gboolean sn_watcher_call_register_status_notifier_host_finish (SnWatcher
                                                                    * proxy,
                                                                    GAsyncResult
                                                                    * res,
                                                                    GError **
                                                                    error);

     gboolean sn_watcher_call_register_status_notifier_host_sync (SnWatcher *
                                                                  proxy,
                                                                  const gchar
                                                                  *
                                                                  arg_service,
                                                                  GCancellable
                                                                  *
                                                                  cancellable,
                                                                  GError **
                                                                  error);



/* D-Bus property accessors: */
     const gchar *const
       *sn_watcher_get_registered_status_notifier_items (SnWatcher * object);
     gchar **sn_watcher_dup_registered_status_notifier_items (SnWatcher *
                                                              object);
     void sn_watcher_set_registered_status_notifier_items (SnWatcher * object,
                                                           const gchar *
                                                           const *value);

     gboolean sn_watcher_get_is_status_notifier_host_registered (SnWatcher *
                                                                 object);
     void sn_watcher_set_is_status_notifier_host_registered (SnWatcher *
                                                             object,
                                                             gboolean value);

     gint sn_watcher_get_protocol_version (SnWatcher * object);
     void sn_watcher_set_protocol_version (SnWatcher * object, gint value);


/* ---- */

#define TYPE_SN_WATCHER_PROXY (sn_watcher_proxy_get_type ())
#define SN_WATCHER_PROXY(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), TYPE_SN_WATCHER_PROXY, SnWatcherProxy))
#define SN_WATCHER_PROXY_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), TYPE_SN_WATCHER_PROXY, SnWatcherProxyClass))
#define SN_WATCHER_PROXY_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), TYPE_SN_WATCHER_PROXY, SnWatcherProxyClass))
#define IS_SN_WATCHER_PROXY(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), TYPE_SN_WATCHER_PROXY))
#define IS_SN_WATCHER_PROXY_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), TYPE_SN_WATCHER_PROXY))

     typedef struct _SnWatcherProxy SnWatcherProxy;
     typedef struct _SnWatcherProxyClass SnWatcherProxyClass;
     typedef struct _SnWatcherProxyPrivate SnWatcherProxyPrivate;

     struct _SnWatcherProxy
     {
       /*< private > */
       GDBusProxy parent_instance;
       SnWatcherProxyPrivate *priv;
     };

     struct _SnWatcherProxyClass
     {
       GDBusProxyClass parent_class;
     };

     GType sn_watcher_proxy_get_type (void) G_GNUC_CONST;

#if GLIB_CHECK_VERSION(2, 44, 0)
G_DEFINE_AUTOPTR_CLEANUP_FUNC (SnWatcherProxy, g_object_unref)
#endif
     void sn_watcher_proxy_new (GDBusConnection * connection,
                                GDBusProxyFlags flags,
                                const gchar * name,
                                const gchar * object_path,
                                GCancellable * cancellable,
                                GAsyncReadyCallback callback,
                                gpointer user_data);
     SnWatcher *sn_watcher_proxy_new_finish (GAsyncResult * res,
                                             GError ** error);
     SnWatcher *sn_watcher_proxy_new_sync (GDBusConnection * connection,
                                           GDBusProxyFlags flags,
                                           const gchar * name,
                                           const gchar * object_path,
                                           GCancellable * cancellable,
                                           GError ** error);

     void sn_watcher_proxy_new_for_bus (GBusType bus_type,
                                        GDBusProxyFlags flags,
                                        const gchar * name,
                                        const gchar * object_path,
                                        GCancellable * cancellable,
                                        GAsyncReadyCallback callback,
                                        gpointer user_data);
     SnWatcher *sn_watcher_proxy_new_for_bus_finish (GAsyncResult * res,
                                                     GError ** error);
     SnWatcher *sn_watcher_proxy_new_for_bus_sync (GBusType bus_type,
                                                   GDBusProxyFlags flags,
                                                   const gchar * name,
                                                   const gchar * object_path,
                                                   GCancellable * cancellable,
                                                   GError ** error);


/* ---- */

#define TYPE_SN_WATCHER_SKELETON (sn_watcher_skeleton_get_type ())
#define SN_WATCHER_SKELETON(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), TYPE_SN_WATCHER_SKELETON, SnWatcherSkeleton))
#define SN_WATCHER_SKELETON_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), TYPE_SN_WATCHER_SKELETON, SnWatcherSkeletonClass))
#define SN_WATCHER_SKELETON_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), TYPE_SN_WATCHER_SKELETON, SnWatcherSkeletonClass))
#define IS_SN_WATCHER_SKELETON(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), TYPE_SN_WATCHER_SKELETON))
#define IS_SN_WATCHER_SKELETON_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), TYPE_SN_WATCHER_SKELETON))

     typedef struct _SnWatcherSkeleton SnWatcherSkeleton;
     typedef struct _SnWatcherSkeletonClass SnWatcherSkeletonClass;
     typedef struct _SnWatcherSkeletonPrivate SnWatcherSkeletonPrivate;

     struct _SnWatcherSkeleton
     {
       /*< private > */
       GDBusInterfaceSkeleton parent_instance;
       SnWatcherSkeletonPrivate *priv;
     };

     struct _SnWatcherSkeletonClass
     {
       GDBusInterfaceSkeletonClass parent_class;
     };

     GType sn_watcher_skeleton_get_type (void) G_GNUC_CONST;

#if GLIB_CHECK_VERSION(2, 44, 0)
G_DEFINE_AUTOPTR_CLEANUP_FUNC (SnWatcherSkeleton, g_object_unref)
#endif
     SnWatcher *sn_watcher_skeleton_new (void);


G_END_DECLS
#endif /* __SN_WATCHER_H__ */
