#ifndef PROCESS_TREE_MODEL_H
#define PROCESS_TREE_MODEL_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <gtk/gtk.h>
#include <glib-object.h>

#define XTM_TYPE_PROCESS_TREE_MODEL		(xtm_process_tree_model_get_type ())
#define XTM_PROCESS_TREE_MODEL(obj)		(G_TYPE_CHECK_INSTANCE_CAST ((obj), XTM_TYPE_PROCESS_TREE_MODEL, XtmProcessTreeModel))
#define XTM_PROCESS_TREE_MODE_CLASS(klass)	(G_TYPE_CHECK_CLASS_CAST ((klass), XTM_TYPE_PROCESS_TREE_MODEL, XtmProcessTreeModelClass))
#define XTM_IS_PROCESS_TREE_MODEL(obj)		(G_TYPE_CHECK_INSTANCE_TYPE ((obj), XTM_TYPE_PROCESS_TREE_MODEL))
#define XTM_IS_PROCESS_TREE_MODEL_CLASS(klass)	(G_TYPE_CHECK_CLASS_TYPE ((klass), XTM_TYPE_PROCESS_TREE_MODEL))
#define XTM_PROCESS_TREE_MODEL_GET_CLASS(obj)	(G_TYPE_INSTANCE_GET_CLASS ((obj), XTM_TYPE_PROCESS_TREE_MODEL, XtmProcessTreeModelClass))

typedef struct _XtmProcessTreeModel XtmProcessTreeModel;

GType		xtm_process_tree_model_get_type			(void);
GtkTreeModel *	xtm_process_tree_model_new			(GtkTreeModel *	model);

#endif /* !PROCESS_TREE_MODEL_H */
