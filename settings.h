//
// Created by dushn on 4.9.17..
//
#ifndef SETTINGS_H
#define SETTINGS_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <glib-object.h>
#include <stdlib.h>
#define XTM_TYPE_SETTINGS			(xtm_settings_get_type ())
#define XTM_SETTINGS(obj)			(G_TYPE_CHECK_INSTANCE_CAST ((obj), XTM_TYPE_SETTINGS, XtmSettings))
#define XTM_SETTINGS_CLASS(klass)		(G_TYPE_CHECK_CLASS_CAST ((klass), XTM_TYPE_SETTINGS, XtmSettingsClass))
#define XTM_IS_SETTINGS(obj)			(G_TYPE_CHECK_INSTANCE_TYPE ((obj), XTM_TYPE_SETTINGS))
#define XTM_IS_SETTINGS_CLASS(klass)		(G_TYPE_CHECK_CLASS_TYPE ((klass), XTM_TYPE_SETTINGS))
#define XTM_SETTINGS_GET_CLASS(obj)		(G_TYPE_INSTANCE_GET_CLASS ((obj), XTM_TYPE_SETTINGS, XtmSettingsClass))

typedef struct _XtmSettings XtmSettings;

GType		xtm_settings_get_type				(void);
XtmSettings *	xtm_settings_get_default			(void);



typedef enum
{
    XTM_TOOLBAR_STYLE_DEFAULT,
    XTM_TOOLBAR_STYLE_SMALL,
    XTM_TOOLBAR_STYLE_LARGE,
    XTM_TOOLBAR_STYLE_TEXT,
} XtmToolbarStyle;

GType xtm_toolbar_style_get_type (void);
#define XTM_TYPE_TOOLBAR_STYLE (xtm_toolbar_style_get_type ())

#endif /* !SETTINGS_H */

