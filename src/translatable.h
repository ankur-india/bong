/*
 * Copyright/Licensing information.
 */

/* inclusion guard */
#ifndef __TRANSLATABLE_H__
#define __TRANSLATABLE_H__

#include "localestring.h"
#include "type.h"

#include <glib-object.h>

/*
 * Type macros
 */

#define TYPE_TRANSLATABLE               (translatable_get_type())
#define TRANSLATABLE(obj)               (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_TRANSLATABLE, Translatable))
#define IS_TRANSLATABLE(obj)            (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_TRANSLATABLE))
#define TRANSLATABLE_CLASS(klass)       (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_TRANSLATABLE, TranslatableClass))
#define IS_TRANSLATABLE_CLASS(klass)    (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_TRANSLATABLE))
#define TRANSLATABLE_GET_CLASS(obj)     (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_TRANSLATABLE, TranslatableClass))

typedef struct _Translatable Translatable;
typedef struct _TranslatableClass TranslatableClass;

struct _TranslatableClass
{
    GObjectClass parent_class;
    GTypeClass gtypeclass;
};

struct _Translatable
{
    GObject parent_instance;
    GTypeInstance gtype;

    /* private */
    GHashTable *hash_table;
    FileType *file_type;
    void (*read_file) (FileType *file_type, Translatable *self, gchar *fileName);
};

GType translatable_get_type (void);

void translatable_class_init (gpointer klass, gpointer klass_data);
void translatable_instance_init (GTypeInstance *instance, gpointer klass);

/* public functions */
Translatable* translatable_new (void);
void translatable_init (Translatable *self, FileType *file_type);
void translatable_destroy (gpointer data);

void translatable_read_file (Translatable *self, gchar *file_name);

void translatable_add_localestring (Translatable *self, gchar *uik, LocaleString *locale_string);
LocaleString* translatable_find_localestring (Translatable *self, gchar *uik, gchar *locale);

#endif /* __TRANSLATABLE_H__ */