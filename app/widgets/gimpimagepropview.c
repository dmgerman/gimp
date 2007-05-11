begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpImagePropView  * Copyright (C) 2005  Michael Natterer<mitch@gimp.org>  * Copyright (C) 2006  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<sys/types.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_UNISTD_H
end_ifdef

begin_include
include|#
directive|include
file|<unistd.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|<glib/gstdio.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
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
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpundostack.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpunit.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp-utils.h"
end_include

begin_include
include|#
directive|include
file|"file/file-procedure.h"
end_include

begin_include
include|#
directive|include
file|"file/file-utils.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/gimppluginmanager.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/gimppluginprocedure.h"
end_include

begin_include
include|#
directive|include
file|"gimpimagepropview.h"
end_include

begin_include
include|#
directive|include
file|"gimppropwidgets.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon28ffe2270103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_IMAGE
name|PROP_IMAGE
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|GObject
modifier|*
name|gimp_image_prop_view_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_prop_view_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_prop_view_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GtkWidget
modifier|*
name|gimp_image_prop_view_add_label
parameter_list|(
name|GtkTable
modifier|*
name|table
parameter_list|,
name|gint
name|row
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_prop_view_undo_event
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpUndoEvent
name|event
parameter_list|,
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpImagePropView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_prop_view_update
parameter_list|(
name|GimpImagePropView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_prop_view_file_update
parameter_list|(
name|GimpImagePropView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpImagePropView,gimp_image_prop_view,GTK_TYPE_TABLE)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpImagePropView
argument_list|,
argument|gimp_image_prop_view
argument_list|,
argument|GTK_TYPE_TABLE
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_image_prop_view_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_image_prop_view_class_init
parameter_list|(
name|GimpImagePropViewClass
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
name|object_class
operator|->
name|constructor
operator|=
name|gimp_image_prop_view_constructor
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_image_prop_view_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_image_prop_view_get_property
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_IMAGE
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"image"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_IMAGE
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_prop_view_init (GimpImagePropView * view)
name|gimp_image_prop_view_init
parameter_list|(
name|GimpImagePropView
modifier|*
name|view
parameter_list|)
block|{
name|GtkTable
modifier|*
name|table
init|=
name|GTK_TABLE
argument_list|(
name|view
argument_list|)
decl_stmt|;
name|gint
name|row
init|=
literal|0
decl_stmt|;
name|gtk_table_resize
argument_list|(
name|table
argument_list|,
literal|14
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacings
argument_list|(
name|table
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacings
argument_list|(
name|table
argument_list|,
literal|3
argument_list|)
expr_stmt|;
name|view
operator|->
name|pixel_size_label
operator|=
name|gimp_image_prop_view_add_label
argument_list|(
name|table
argument_list|,
name|row
operator|++
argument_list|,
name|_
argument_list|(
literal|"Pixel dimensions:"
argument_list|)
argument_list|)
expr_stmt|;
name|view
operator|->
name|print_size_label
operator|=
name|gimp_image_prop_view_add_label
argument_list|(
name|table
argument_list|,
name|row
operator|++
argument_list|,
name|_
argument_list|(
literal|"Print size:"
argument_list|)
argument_list|)
expr_stmt|;
name|view
operator|->
name|resolution_label
operator|=
name|gimp_image_prop_view_add_label
argument_list|(
name|table
argument_list|,
name|row
operator|++
argument_list|,
name|_
argument_list|(
literal|"Resolution:"
argument_list|)
argument_list|)
expr_stmt|;
name|view
operator|->
name|colorspace_label
operator|=
name|gimp_image_prop_view_add_label
argument_list|(
name|table
argument_list|,
name|row
argument_list|,
name|_
argument_list|(
literal|"Color space:"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|view
argument_list|)
argument_list|,
name|row
operator|++
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|view
operator|->
name|filename_label
operator|=
name|gimp_image_prop_view_add_label
argument_list|(
name|table
argument_list|,
name|row
operator|++
argument_list|,
name|_
argument_list|(
literal|"File Name:"
argument_list|)
argument_list|)
expr_stmt|;
name|view
operator|->
name|filesize_label
operator|=
name|gimp_image_prop_view_add_label
argument_list|(
name|table
argument_list|,
name|row
operator|++
argument_list|,
name|_
argument_list|(
literal|"File Size:"
argument_list|)
argument_list|)
expr_stmt|;
name|view
operator|->
name|filetype_label
operator|=
name|gimp_image_prop_view_add_label
argument_list|(
name|table
argument_list|,
name|row
argument_list|,
name|_
argument_list|(
literal|"File Type:"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|view
argument_list|)
argument_list|,
name|row
operator|++
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|view
operator|->
name|memsize_label
operator|=
name|gimp_image_prop_view_add_label
argument_list|(
name|table
argument_list|,
name|row
operator|++
argument_list|,
name|_
argument_list|(
literal|"Size in memory:"
argument_list|)
argument_list|)
expr_stmt|;
name|view
operator|->
name|undo_label
operator|=
name|gimp_image_prop_view_add_label
argument_list|(
name|table
argument_list|,
name|row
operator|++
argument_list|,
name|_
argument_list|(
literal|"Undo steps:"
argument_list|)
argument_list|)
expr_stmt|;
name|view
operator|->
name|redo_label
operator|=
name|gimp_image_prop_view_add_label
argument_list|(
name|table
argument_list|,
name|row
argument_list|,
name|_
argument_list|(
literal|"Redo steps:"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|view
argument_list|)
argument_list|,
name|row
operator|++
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|view
operator|->
name|pixels_label
operator|=
name|gimp_image_prop_view_add_label
argument_list|(
name|table
argument_list|,
name|row
operator|++
argument_list|,
name|_
argument_list|(
literal|"Number of pixels:"
argument_list|)
argument_list|)
expr_stmt|;
name|view
operator|->
name|layers_label
operator|=
name|gimp_image_prop_view_add_label
argument_list|(
name|table
argument_list|,
name|row
operator|++
argument_list|,
name|_
argument_list|(
literal|"Number of layers:"
argument_list|)
argument_list|)
expr_stmt|;
name|view
operator|->
name|channels_label
operator|=
name|gimp_image_prop_view_add_label
argument_list|(
name|table
argument_list|,
name|row
operator|++
argument_list|,
name|_
argument_list|(
literal|"Number of channels:"
argument_list|)
argument_list|)
expr_stmt|;
name|view
operator|->
name|vectors_label
operator|=
name|gimp_image_prop_view_add_label
argument_list|(
name|table
argument_list|,
name|row
operator|++
argument_list|,
name|_
argument_list|(
literal|"Number of paths:"
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_prop_view_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_image_prop_view_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpImagePropView
modifier|*
name|view
init|=
name|GIMP_IMAGE_PROP_VIEW
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_IMAGE
case|:
name|view
operator|->
name|image
operator|=
name|g_value_get_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_prop_view_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_image_prop_view_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpImagePropView
modifier|*
name|view
init|=
name|GIMP_IMAGE_PROP_VIEW
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_IMAGE
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|view
operator|->
name|image
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|GObject
modifier|*
DECL|function|gimp_image_prop_view_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_image_prop_view_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
block|{
name|GimpImagePropView
modifier|*
name|view
decl_stmt|;
name|GObject
modifier|*
name|object
decl_stmt|;
name|object
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructor
argument_list|(
name|type
argument_list|,
name|n_params
argument_list|,
name|params
argument_list|)
expr_stmt|;
name|view
operator|=
name|GIMP_IMAGE_PROP_VIEW
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|view
operator|->
name|image
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|view
operator|->
name|image
argument_list|,
literal|"name-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_image_prop_view_file_update
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|view
argument_list|)
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|view
operator|->
name|image
argument_list|,
literal|"size-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_image_prop_view_update
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|view
argument_list|)
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|view
operator|->
name|image
argument_list|,
literal|"resolution-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_image_prop_view_update
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|view
argument_list|)
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|view
operator|->
name|image
argument_list|,
literal|"unit-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_image_prop_view_update
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|view
argument_list|)
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|view
operator|->
name|image
argument_list|,
literal|"mode-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_image_prop_view_update
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|view
argument_list|)
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|view
operator|->
name|image
argument_list|,
literal|"undo-event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_image_prop_view_undo_event
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|view
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_image_prop_view_update
argument_list|(
name|view
argument_list|)
expr_stmt|;
name|gimp_image_prop_view_file_update
argument_list|(
name|view
argument_list|)
expr_stmt|;
return|return
name|object
return|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_image_prop_view_new (GimpImage * image)
name|gimp_image_prop_view_new
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_IMAGE_PROP_VIEW
argument_list|,
literal|"image"
argument_list|,
name|image
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|gimp_image_prop_view_add_label (GtkTable * table,gint row,const gchar * text)
name|gimp_image_prop_view_add_label
parameter_list|(
name|GtkTable
modifier|*
name|table
parameter_list|,
name|gint
name|row
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|desc
decl_stmt|;
name|desc
operator|=
name|g_object_new
argument_list|(
name|GTK_TYPE_LABEL
argument_list|,
literal|"label"
argument_list|,
name|text
argument_list|,
literal|"xalign"
argument_list|,
literal|1.0
argument_list|,
literal|"yalign"
argument_list|,
literal|0.5
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_label_set_attributes
argument_list|(
name|GTK_LABEL
argument_list|(
name|desc
argument_list|)
argument_list|,
name|PANGO_ATTR_WEIGHT
argument_list|,
name|PANGO_WEIGHT_BOLD
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|table
argument_list|,
name|desc
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|row
argument_list|,
name|row
operator|+
literal|1
argument_list|,
name|GTK_FILL
argument_list|,
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|desc
argument_list|)
expr_stmt|;
name|label
operator|=
name|g_object_new
argument_list|(
name|GTK_TYPE_LABEL
argument_list|,
literal|"xalign"
argument_list|,
literal|0.0
argument_list|,
literal|"yalign"
argument_list|,
literal|0.5
argument_list|,
literal|"selectable"
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|table
argument_list|,
name|label
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
name|row
argument_list|,
name|row
operator|+
literal|1
argument_list|,
name|GTK_FILL
argument_list|,
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
return|return
name|label
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_prop_view_label_set_memsize (GtkWidget * label,GimpObject * object)
name|gimp_image_prop_view_label_set_memsize
parameter_list|(
name|GtkWidget
modifier|*
name|label
parameter_list|,
name|GimpObject
modifier|*
name|object
parameter_list|)
block|{
name|gchar
modifier|*
name|str
init|=
name|gimp_memsize_to_string
argument_list|(
name|gimp_object_get_memsize
argument_list|(
name|object
argument_list|,
name|NULL
argument_list|)
argument_list|)
decl_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|str
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|str
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_prop_view_label_set_filename (GtkWidget * label,GimpImage * image)
name|gimp_image_prop_view_label_set_filename
parameter_list|(
name|GtkWidget
modifier|*
name|label
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|uri
init|=
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|image
argument_list|)
argument_list|)
decl_stmt|;
if|if
condition|(
name|uri
condition|)
block|{
name|gchar
modifier|*
name|name
init|=
name|file_utils_uri_display_basename
argument_list|(
name|uri
argument_list|)
decl_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_prop_view_label_set_filesize (GtkWidget * label,GimpImage * image)
name|gimp_image_prop_view_label_set_filesize
parameter_list|(
name|GtkWidget
modifier|*
name|label
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|gchar
modifier|*
name|filename
init|=
name|gimp_image_get_filename
argument_list|(
name|image
argument_list|)
decl_stmt|;
if|if
condition|(
name|filename
condition|)
block|{
name|struct
name|stat
name|buf
decl_stmt|;
if|if
condition|(
name|g_stat
argument_list|(
name|filename
argument_list|,
operator|&
name|buf
argument_list|)
operator|==
literal|0
condition|)
block|{
name|gchar
modifier|*
name|str
init|=
name|gimp_memsize_to_string
argument_list|(
name|buf
operator|.
name|st_size
argument_list|)
decl_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|str
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|str
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_prop_view_label_set_filetype (GtkWidget * label,GimpImage * image)
name|gimp_image_prop_view_label_set_filetype
parameter_list|(
name|GtkWidget
modifier|*
name|label
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|GimpPlugInManager
modifier|*
name|manager
init|=
name|image
operator|->
name|gimp
operator|->
name|plug_in_manager
decl_stmt|;
name|GimpPlugInProcedure
modifier|*
name|proc
decl_stmt|;
name|proc
operator|=
name|gimp_image_get_save_proc
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|proc
condition|)
block|{
name|gchar
modifier|*
name|filename
init|=
name|gimp_image_get_filename
argument_list|(
name|image
argument_list|)
decl_stmt|;
if|if
condition|(
name|filename
condition|)
block|{
name|proc
operator|=
name|file_procedure_find
argument_list|(
name|manager
operator|->
name|load_procs
argument_list|,
name|filename
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
block|}
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|proc
condition|?
name|gimp_plug_in_procedure_get_label
argument_list|(
name|proc
argument_list|)
else|:
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_prop_view_label_set_undo (GtkWidget * label,GimpUndoStack * stack)
name|gimp_image_prop_view_label_set_undo
parameter_list|(
name|GtkWidget
modifier|*
name|label
parameter_list|,
name|GimpUndoStack
modifier|*
name|stack
parameter_list|)
block|{
name|gint
name|steps
init|=
name|gimp_undo_stack_get_depth
argument_list|(
name|stack
argument_list|)
decl_stmt|;
if|if
condition|(
name|steps
operator|>
literal|0
condition|)
block|{
name|GimpObject
modifier|*
name|object
init|=
name|GIMP_OBJECT
argument_list|(
name|stack
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|str
decl_stmt|;
name|gchar
name|buf
index|[
literal|256
index|]
decl_stmt|;
name|str
operator|=
name|gimp_memsize_to_string
argument_list|(
name|gimp_object_get_memsize
argument_list|(
name|object
argument_list|,
name|NULL
argument_list|)
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
name|buf
argument_list|)
argument_list|,
literal|"%d (%s)"
argument_list|,
name|steps
argument_list|,
name|str
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|str
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|buf
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/*  no undo (or redo) steps available  */
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"None"
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_prop_view_undo_event (GimpImage * image,GimpUndoEvent event,GimpUndo * undo,GimpImagePropView * view)
name|gimp_image_prop_view_undo_event
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpUndoEvent
name|event
parameter_list|,
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpImagePropView
modifier|*
name|view
parameter_list|)
block|{
name|gimp_image_prop_view_update
argument_list|(
name|view
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_prop_view_update (GimpImagePropView * view)
name|gimp_image_prop_view_update
parameter_list|(
name|GimpImagePropView
modifier|*
name|view
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
init|=
name|view
operator|->
name|image
decl_stmt|;
name|GimpImageBaseType
name|type
decl_stmt|;
name|GimpUnit
name|unit
decl_stmt|;
name|gdouble
name|unit_factor
decl_stmt|;
name|gint
name|unit_digits
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|desc
decl_stmt|;
name|gchar
name|format_buf
index|[
literal|32
index|]
decl_stmt|;
name|gchar
name|buf
index|[
literal|256
index|]
decl_stmt|;
comment|/*  pixel size  */
name|g_snprintf
argument_list|(
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
name|buf
argument_list|)
argument_list|,
name|ngettext
argument_list|(
literal|"%d Ã %d pixel"
argument_list|,
literal|"%d Ã %d pixels"
argument_list|,
name|image
operator|->
name|height
argument_list|)
argument_list|,
name|image
operator|->
name|width
argument_list|,
name|image
operator|->
name|height
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|view
operator|->
name|pixel_size_label
argument_list|)
argument_list|,
name|buf
argument_list|)
expr_stmt|;
comment|/*  print size  */
name|unit
operator|=
name|gimp_get_default_unit
argument_list|()
expr_stmt|;
name|unit_factor
operator|=
name|_gimp_unit_get_factor
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|unit
argument_list|)
expr_stmt|;
name|unit_digits
operator|=
name|_gimp_unit_get_digits
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|unit
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|format_buf
argument_list|,
sizeof|sizeof
argument_list|(
name|format_buf
argument_list|)
argument_list|,
literal|"%%.%df Ã %%.%df %s"
argument_list|,
name|unit_digits
operator|+
literal|1
argument_list|,
name|unit_digits
operator|+
literal|1
argument_list|,
name|_gimp_unit_get_plural
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|unit
argument_list|)
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
name|buf
argument_list|)
argument_list|,
name|format_buf
argument_list|,
name|image
operator|->
name|width
operator|*
name|unit_factor
operator|/
name|image
operator|->
name|xresolution
argument_list|,
name|image
operator|->
name|height
operator|*
name|unit_factor
operator|/
name|image
operator|->
name|yresolution
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|view
operator|->
name|print_size_label
argument_list|)
argument_list|,
name|buf
argument_list|)
expr_stmt|;
comment|/*  resolution  */
name|unit
operator|=
name|gimp_image_get_unit
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|unit_factor
operator|=
name|_gimp_unit_get_factor
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|unit
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|format_buf
argument_list|,
sizeof|sizeof
argument_list|(
name|format_buf
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"pixels/%s"
argument_list|)
argument_list|,
name|_gimp_unit_get_abbreviation
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|unit
argument_list|)
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
name|buf
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"%g Ã %g %s"
argument_list|)
argument_list|,
name|image
operator|->
name|xresolution
operator|/
name|unit_factor
argument_list|,
name|image
operator|->
name|yresolution
operator|/
name|unit_factor
argument_list|,
name|unit
operator|==
name|GIMP_UNIT_INCH
condition|?
name|_
argument_list|(
literal|"ppi"
argument_list|)
else|:
name|format_buf
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|view
operator|->
name|resolution_label
argument_list|)
argument_list|,
name|buf
argument_list|)
expr_stmt|;
comment|/*  color type  */
name|type
operator|=
name|gimp_image_base_type
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|gimp_enum_get_value
argument_list|(
name|GIMP_TYPE_IMAGE_BASE_TYPE
argument_list|,
name|type
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|&
name|desc
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|type
condition|)
block|{
case|case
name|GIMP_RGB
case|:
case|case
name|GIMP_GRAY
case|:
name|g_snprintf
argument_list|(
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
name|buf
argument_list|)
argument_list|,
literal|"%s"
argument_list|,
name|desc
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_INDEXED
case|:
name|g_snprintf
argument_list|(
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
name|buf
argument_list|)
argument_list|,
literal|"%s (%d %s)"
argument_list|,
name|desc
argument_list|,
name|image
operator|->
name|num_cols
argument_list|,
name|_
argument_list|(
literal|"colors"
argument_list|)
argument_list|)
expr_stmt|;
break|break;
block|}
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|view
operator|->
name|colorspace_label
argument_list|)
argument_list|,
name|buf
argument_list|)
expr_stmt|;
comment|/*  size in memory  */
name|gimp_image_prop_view_label_set_memsize
argument_list|(
name|view
operator|->
name|memsize_label
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  undo / redo  */
name|gimp_image_prop_view_label_set_undo
argument_list|(
name|view
operator|->
name|undo_label
argument_list|,
name|image
operator|->
name|undo_stack
argument_list|)
expr_stmt|;
name|gimp_image_prop_view_label_set_undo
argument_list|(
name|view
operator|->
name|redo_label
argument_list|,
name|image
operator|->
name|redo_stack
argument_list|)
expr_stmt|;
comment|/*  number of layers  */
name|g_snprintf
argument_list|(
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
name|buf
argument_list|)
argument_list|,
literal|"%d"
argument_list|,
name|image
operator|->
name|width
operator|*
name|image
operator|->
name|height
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|view
operator|->
name|pixels_label
argument_list|)
argument_list|,
name|buf
argument_list|)
expr_stmt|;
comment|/*  number of layers  */
name|g_snprintf
argument_list|(
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
name|buf
argument_list|)
argument_list|,
literal|"%d"
argument_list|,
name|gimp_container_num_children
argument_list|(
name|image
operator|->
name|layers
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|view
operator|->
name|layers_label
argument_list|)
argument_list|,
name|buf
argument_list|)
expr_stmt|;
comment|/*  number of channels  */
name|g_snprintf
argument_list|(
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
name|buf
argument_list|)
argument_list|,
literal|"%d"
argument_list|,
name|gimp_container_num_children
argument_list|(
name|image
operator|->
name|channels
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|view
operator|->
name|channels_label
argument_list|)
argument_list|,
name|buf
argument_list|)
expr_stmt|;
comment|/*  number of vectors  */
name|g_snprintf
argument_list|(
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
name|buf
argument_list|)
argument_list|,
literal|"%d"
argument_list|,
name|gimp_container_num_children
argument_list|(
name|image
operator|->
name|vectors
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|view
operator|->
name|vectors_label
argument_list|)
argument_list|,
name|buf
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_prop_view_file_update (GimpImagePropView * view)
name|gimp_image_prop_view_file_update
parameter_list|(
name|GimpImagePropView
modifier|*
name|view
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
init|=
name|view
operator|->
name|image
decl_stmt|;
comment|/*  filename  */
name|gimp_image_prop_view_label_set_filename
argument_list|(
name|view
operator|->
name|filename_label
argument_list|,
name|image
argument_list|)
expr_stmt|;
comment|/*  filesize  */
name|gimp_image_prop_view_label_set_filesize
argument_list|(
name|view
operator|->
name|filesize_label
argument_list|,
name|image
argument_list|)
expr_stmt|;
comment|/*  filetype  */
name|gimp_image_prop_view_label_set_filetype
argument_list|(
name|view
operator|->
name|filetype_label
argument_list|,
name|image
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

