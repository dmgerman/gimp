begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpenumstore.c  * Copyright (C) 2004  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpenumstore.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_enum_store_class_init
parameter_list|(
name|GimpEnumStoreClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_enum_store_init
parameter_list|(
name|GimpEnumStore
modifier|*
name|enum_store
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_enum_store_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_enum_store_add_value
parameter_list|(
name|GtkListStore
modifier|*
name|store
parameter_list|,
name|GEnumValue
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GtkListStoreClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_enum_store_get_type (void)
name|gimp_enum_store_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|enum_store_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|enum_store_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|enum_store_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpEnumStoreClass
argument_list|)
block|,
name|NULL
block|,
comment|/* base_init */
name|NULL
block|,
comment|/* base_finalize */
operator|(
name|GClassInitFunc
operator|)
name|gimp_enum_store_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data */
sizeof|sizeof
argument_list|(
name|GimpEnumStore
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_enum_store_init
block|,       }
decl_stmt|;
name|enum_store_type
operator|=
name|g_type_register_static
argument_list|(
name|GTK_TYPE_LIST_STORE
argument_list|,
literal|"GimpEnumStore"
argument_list|,
operator|&
name|enum_store_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|enum_store_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_enum_store_class_init (GimpEnumStoreClass * klass)
name|gimp_enum_store_class_init
parameter_list|(
name|GimpEnumStoreClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_enum_store_finalize
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_enum_store_init (GimpEnumStore * enum_store)
name|gimp_enum_store_init
parameter_list|(
name|GimpEnumStore
modifier|*
name|enum_store
parameter_list|)
block|{
name|GType
name|types
index|[
name|GIMP_ENUM_STORE_NUM_COLUMNS
index|]
init|=
block|{
name|G_TYPE_INT
block|,
comment|/*  GIMP_ENUM_STORE_VALUE      */
name|G_TYPE_STRING
block|,
comment|/*  GIMP_ENUM_STORE_LABEL      */
name|GDK_TYPE_PIXBUF
block|,
comment|/*  GIMP_ENUM_STORE_ICON       */
name|G_TYPE_POINTER
comment|/*  GIMP_ENUM_STORE_USER_DATA  */
block|}
decl_stmt|;
name|enum_store
operator|->
name|enum_class
operator|=
name|NULL
expr_stmt|;
name|gtk_list_store_set_column_types
argument_list|(
name|GTK_LIST_STORE
argument_list|(
name|enum_store
argument_list|)
argument_list|,
name|GIMP_ENUM_STORE_NUM_COLUMNS
argument_list|,
name|types
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_enum_store_finalize (GObject * object)
name|gimp_enum_store_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpEnumStore
modifier|*
name|enum_store
init|=
name|GIMP_ENUM_STORE
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|enum_store
operator|->
name|enum_class
condition|)
name|g_type_class_unref
argument_list|(
name|enum_store
operator|->
name|enum_class
argument_list|)
expr_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_enum_store_new:  * @enum_type: the #GType of an enum.  *  * Creates a new #GimpEnumStore, derived from #GtkListStore and fills  * it with enum values. The enum needs to be registered to the type  * system and should have translatable value names.  *  * Return value: a new #GimpEnumStore.  **/
end_comment

begin_function
name|GtkListStore
modifier|*
DECL|function|gimp_enum_store_new (GType enum_type)
name|gimp_enum_store_new
parameter_list|(
name|GType
name|enum_type
parameter_list|)
block|{
name|GtkListStore
modifier|*
name|store
decl_stmt|;
name|GEnumClass
modifier|*
name|enum_class
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_TYPE_IS_ENUM
argument_list|(
name|enum_type
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|enum_class
operator|=
name|g_type_class_ref
argument_list|(
name|enum_type
argument_list|)
expr_stmt|;
name|store
operator|=
name|gimp_enum_store_new_with_range
argument_list|(
name|enum_type
argument_list|,
name|enum_class
operator|->
name|minimum
argument_list|,
name|enum_class
operator|->
name|maximum
argument_list|)
expr_stmt|;
name|g_type_class_unref
argument_list|(
name|enum_class
argument_list|)
expr_stmt|;
return|return
name|store
return|;
block|}
end_function

begin_function
name|GtkListStore
modifier|*
DECL|function|gimp_enum_store_new_with_range (GType enum_type,gint minimum,gint maximum)
name|gimp_enum_store_new_with_range
parameter_list|(
name|GType
name|enum_type
parameter_list|,
name|gint
name|minimum
parameter_list|,
name|gint
name|maximum
parameter_list|)
block|{
name|GtkListStore
modifier|*
name|store
decl_stmt|;
name|GEnumValue
modifier|*
name|value
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_TYPE_IS_ENUM
argument_list|(
name|enum_type
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|store
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_ENUM_STORE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|GIMP_ENUM_STORE
argument_list|(
name|store
argument_list|)
operator|->
name|enum_class
operator|=
name|g_type_class_ref
argument_list|(
name|enum_type
argument_list|)
expr_stmt|;
for|for
control|(
name|value
operator|=
name|GIMP_ENUM_STORE
argument_list|(
name|store
argument_list|)
operator|->
name|enum_class
operator|->
name|values
init|;
name|value
operator|->
name|value_name
condition|;
name|value
operator|++
control|)
block|{
if|if
condition|(
name|value
operator|->
name|value
operator|<
name|minimum
operator|||
name|value
operator|->
name|value
operator|>
name|maximum
condition|)
continue|continue;
name|gimp_enum_store_add_value
argument_list|(
name|store
argument_list|,
name|value
argument_list|)
expr_stmt|;
block|}
return|return
name|store
return|;
block|}
end_function

begin_function
name|GtkListStore
modifier|*
DECL|function|gimp_enum_store_new_with_values (GType enum_type,gint n_values,...)
name|gimp_enum_store_new_with_values
parameter_list|(
name|GType
name|enum_type
parameter_list|,
name|gint
name|n_values
parameter_list|,
modifier|...
parameter_list|)
block|{
name|GtkListStore
modifier|*
name|store
decl_stmt|;
name|va_list
name|args
decl_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|n_values
argument_list|)
expr_stmt|;
name|store
operator|=
name|gimp_enum_store_new_with_values_valist
argument_list|(
name|enum_type
argument_list|,
name|n_values
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
return|return
name|store
return|;
block|}
end_function

begin_function
name|GtkListStore
modifier|*
DECL|function|gimp_enum_store_new_with_values_valist (GType enum_type,gint n_values,va_list args)
name|gimp_enum_store_new_with_values_valist
parameter_list|(
name|GType
name|enum_type
parameter_list|,
name|gint
name|n_values
parameter_list|,
name|va_list
name|args
parameter_list|)
block|{
name|GtkListStore
modifier|*
name|store
decl_stmt|;
name|GEnumValue
modifier|*
name|value
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_TYPE_IS_ENUM
argument_list|(
name|enum_type
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|n_values
operator|>
literal|1
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|store
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_ENUM_STORE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|GIMP_ENUM_STORE
argument_list|(
name|store
argument_list|)
operator|->
name|enum_class
operator|=
name|g_type_class_ref
argument_list|(
name|enum_type
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_values
condition|;
name|i
operator|++
control|)
block|{
name|value
operator|=
name|g_enum_get_value
argument_list|(
name|GIMP_ENUM_STORE
argument_list|(
name|store
argument_list|)
operator|->
name|enum_class
argument_list|,
name|va_arg
argument_list|(
name|args
argument_list|,
name|gint
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|value
condition|)
name|gimp_enum_store_add_value
argument_list|(
name|store
argument_list|,
name|value
argument_list|)
expr_stmt|;
block|}
return|return
name|store
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_enum_store_lookup_by_value (GimpEnumStore * store,gint value,GtkTreeIter * iter)
name|gimp_enum_store_lookup_by_value
parameter_list|(
name|GimpEnumStore
modifier|*
name|store
parameter_list|,
name|gint
name|value
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|)
block|{
name|GtkTreeModel
modifier|*
name|model
decl_stmt|;
name|gboolean
name|iter_valid
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_ENUM_STORE
argument_list|(
name|store
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|iter
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|model
operator|=
name|GTK_TREE_MODEL
argument_list|(
name|store
argument_list|)
expr_stmt|;
for|for
control|(
name|iter_valid
operator|=
name|gtk_tree_model_get_iter_first
argument_list|(
name|model
argument_list|,
name|iter
argument_list|)
init|;
name|iter_valid
condition|;
name|iter_valid
operator|=
name|gtk_tree_model_iter_next
argument_list|(
name|model
argument_list|,
name|iter
argument_list|)
control|)
block|{
name|gint
name|this
decl_stmt|;
name|gtk_tree_model_get
argument_list|(
name|model
argument_list|,
name|iter
argument_list|,
name|GIMP_ENUM_STORE_VALUE
argument_list|,
operator|&
name|this
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|this
operator|==
name|value
condition|)
break|break;
block|}
return|return
name|iter_valid
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_enum_store_set_icons (GimpEnumStore * store,GtkWidget * widget,const gchar * stock_prefix,GtkIconSize size)
name|gimp_enum_store_set_icons
parameter_list|(
name|GimpEnumStore
modifier|*
name|store
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|gchar
modifier|*
name|stock_prefix
parameter_list|,
name|GtkIconSize
name|size
parameter_list|)
block|{
name|GtkTreeModel
modifier|*
name|model
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
name|gboolean
name|iter_valid
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_ENUM_STORE
argument_list|(
name|store
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|stock_prefix
operator|==
name|NULL
operator|||
name|GTK_IS_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|size
operator|>
name|GTK_ICON_SIZE_INVALID
operator|||
name|size
operator|==
operator|-
literal|1
argument_list|)
expr_stmt|;
name|model
operator|=
name|GTK_TREE_MODEL
argument_list|(
name|store
argument_list|)
expr_stmt|;
for|for
control|(
name|iter_valid
operator|=
name|gtk_tree_model_get_iter_first
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|)
init|;
name|iter_valid
condition|;
name|iter_valid
operator|=
name|gtk_tree_model_iter_next
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|)
control|)
block|{
name|GdkPixbuf
modifier|*
name|pixbuf
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|stock_prefix
condition|)
block|{
name|GEnumValue
modifier|*
name|enum_value
decl_stmt|;
name|gchar
modifier|*
name|stock_id
decl_stmt|;
name|gint
name|value
decl_stmt|;
name|gtk_tree_model_get
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|,
name|GIMP_ENUM_STORE_VALUE
argument_list|,
operator|&
name|value
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|enum_value
operator|=
name|g_enum_get_value
argument_list|(
name|store
operator|->
name|enum_class
argument_list|,
name|value
argument_list|)
expr_stmt|;
name|stock_id
operator|=
name|g_strconcat
argument_list|(
name|stock_prefix
argument_list|,
literal|"-"
argument_list|,
name|enum_value
operator|->
name|value_nick
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|pixbuf
operator|=
name|gtk_widget_render_icon
argument_list|(
name|widget
argument_list|,
name|stock_id
argument_list|,
name|size
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|stock_id
argument_list|)
expr_stmt|;
block|}
name|gtk_list_store_set
argument_list|(
name|GTK_LIST_STORE
argument_list|(
name|store
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|,
name|GIMP_ENUM_STORE_ICON
argument_list|,
name|pixbuf
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|pixbuf
condition|)
name|g_object_unref
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_enum_store_add_value (GtkListStore * store,GEnumValue * value)
name|gimp_enum_store_add_value
parameter_list|(
name|GtkListStore
modifier|*
name|store
parameter_list|,
name|GEnumValue
modifier|*
name|value
parameter_list|)
block|{
name|GtkTreeIter
name|iter
decl_stmt|;
name|gtk_list_store_append
argument_list|(
name|store
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
name|gtk_list_store_set
argument_list|(
name|store
argument_list|,
operator|&
name|iter
argument_list|,
name|GIMP_ENUM_STORE_VALUE
argument_list|,
name|value
operator|->
name|value
argument_list|,
name|GIMP_ENUM_STORE_LABEL
argument_list|,
name|gettext
argument_list|(
name|value
operator|->
name|value_name
argument_list|)
argument_list|,
name|GIMP_ENUM_STORE_ICON
argument_list|,
name|NULL
argument_list|,
name|GIMP_ENUM_STORE_USER_DATA
argument_list|,
name|NULL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

