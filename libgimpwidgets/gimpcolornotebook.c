begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library   * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball                  *  * gimpcolornotebook.c  * Copyright (C) 2002 Michael Natterer<mitch@gimp.org>  *  * based on color_notebook module  * Copyright (C) 1998 Austin Donnelly<austin@greenend.org.uk>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *   * This library is distributed in the hope that it will be useful,   * but WITHOUT ANY WARRANTY; without even the implied warranty of   * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU    * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgetstypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolornotebook.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorscales.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorselector.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgetsmarshal.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2c8626e90103
block|{
DECL|enumerator|COLOR_CHANGED
name|COLOR_CHANGED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_color_notebook_class_init
parameter_list|(
name|GimpColorNotebookClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_notebook_init
parameter_list|(
name|GimpColorNotebook
modifier|*
name|notebook
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_notebook_finalize
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
name|gimp_color_notebook_switch_page
parameter_list|(
name|GtkNotebook
modifier|*
name|gtk_notebook
parameter_list|,
name|GtkNotebookPage
modifier|*
name|page
parameter_list|,
name|guint
name|page_num
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_notebook_update_callback
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
specifier|const
name|GimpHSV
modifier|*
name|hsv
parameter_list|,
name|GimpColorNotebook
modifier|*
name|notebook
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GtkNotebookClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|notebook_signals
specifier|static
name|guint
name|notebook_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_color_notebook_get_type (void)
name|gimp_color_notebook_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|notebook_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|notebook_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|notebook_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpColorNotebookClass
argument_list|)
block|,
operator|(
name|GBaseInitFunc
operator|)
name|NULL
block|,
operator|(
name|GBaseFinalizeFunc
operator|)
name|NULL
block|,
operator|(
name|GClassInitFunc
operator|)
name|gimp_color_notebook_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpColorNotebook
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_color_notebook_init
block|,       }
decl_stmt|;
name|notebook_type
operator|=
name|g_type_register_static
argument_list|(
name|GTK_TYPE_NOTEBOOK
argument_list|,
literal|"GimpColorNotebook"
argument_list|,
operator|&
name|notebook_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|notebook_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_notebook_class_init (GimpColorNotebookClass * klass)
name|gimp_color_notebook_class_init
parameter_list|(
name|GimpColorNotebookClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GtkNotebookClass
modifier|*
name|notebook_class
decl_stmt|;
name|object_class
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|notebook_class
operator|=
name|GTK_NOTEBOOK_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|notebook_signals
index|[
name|COLOR_CHANGED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"color_changed"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpColorNotebookClass
argument_list|,
name|color_changed
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|_gimp_widgets_marshal_VOID__POINTER_POINTER
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|2
argument_list|,
name|G_TYPE_POINTER
argument_list|,
name|G_TYPE_POINTER
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_color_notebook_finalize
expr_stmt|;
name|notebook_class
operator|->
name|switch_page
operator|=
name|gimp_color_notebook_switch_page
expr_stmt|;
name|klass
operator|->
name|color_changed
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_notebook_init (GimpColorNotebook * notebook)
name|gimp_color_notebook_init
parameter_list|(
name|GimpColorNotebook
modifier|*
name|notebook
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|selector
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GType
modifier|*
name|selector_types
decl_stmt|;
name|gint
name|n_selector_types
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gimp_rgba_set
argument_list|(
operator|&
name|notebook
operator|->
name|rgb
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|gimp_rgb_to_hsv
argument_list|(
operator|&
name|notebook
operator|->
name|rgb
argument_list|,
operator|&
name|notebook
operator|->
name|hsv
argument_list|)
expr_stmt|;
name|notebook
operator|->
name|channel
operator|=
name|GIMP_COLOR_SELECTOR_HUE
expr_stmt|;
name|selector_types
operator|=
name|g_type_children
argument_list|(
name|GIMP_TYPE_COLOR_SELECTOR
argument_list|,
operator|&
name|n_selector_types
argument_list|)
expr_stmt|;
if|if
condition|(
name|n_selector_types
operator|==
literal|1
condition|)
block|{
name|gtk_notebook_set_show_tabs
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|notebook
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_notebook_set_show_border
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|notebook
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_selector_types
condition|;
name|i
operator|++
control|)
block|{
comment|/*  skip the "Scales" color selector  */
if|if
condition|(
name|g_type_is_a
argument_list|(
name|selector_types
index|[
name|i
index|]
argument_list|,
name|GIMP_TYPE_COLOR_SCALES
argument_list|)
condition|)
continue|continue;
name|selector
operator|=
name|gimp_color_selector_new
argument_list|(
name|selector_types
index|[
name|i
index|]
argument_list|,
operator|&
name|notebook
operator|->
name|rgb
argument_list|,
operator|&
name|notebook
operator|->
name|hsv
argument_list|,
name|notebook
operator|->
name|channel
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|selector
condition|)
continue|continue;
name|gimp_color_selector_set_show_alpha
argument_list|(
name|GIMP_COLOR_SELECTOR
argument_list|(
name|selector
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|GIMP_COLOR_SELECTOR_GET_CLASS
argument_list|(
name|selector
argument_list|)
operator|->
name|name
argument_list|)
expr_stmt|;
name|gtk_notebook_append_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|notebook
argument_list|)
argument_list|,
name|selector
argument_list|,
name|label
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|notebook
operator|->
name|cur_page
condition|)
name|notebook
operator|->
name|cur_page
operator|=
name|GIMP_COLOR_SELECTOR
argument_list|(
name|selector
argument_list|)
expr_stmt|;
name|notebook
operator|->
name|selectors
operator|=
name|g_list_append
argument_list|(
name|notebook
operator|->
name|selectors
argument_list|,
name|selector
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|selector
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|selector
argument_list|)
argument_list|,
literal|"color_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_color_notebook_update_callback
argument_list|)
argument_list|,
name|notebook
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|selector_types
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_notebook_finalize (GObject * object)
name|gimp_color_notebook_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpColorNotebook
modifier|*
name|notebook
decl_stmt|;
name|notebook
operator|=
name|GIMP_COLOR_NOTEBOOK
argument_list|(
name|object
argument_list|)
expr_stmt|;
if|if
condition|(
name|notebook
operator|->
name|selectors
condition|)
block|{
name|g_list_free
argument_list|(
name|notebook
operator|->
name|selectors
argument_list|)
expr_stmt|;
name|notebook
operator|->
name|selectors
operator|=
name|NULL
expr_stmt|;
block|}
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

begin_function
specifier|static
name|void
DECL|function|gimp_color_notebook_switch_page (GtkNotebook * gtk_notebook,GtkNotebookPage * page,guint page_num)
name|gimp_color_notebook_switch_page
parameter_list|(
name|GtkNotebook
modifier|*
name|gtk_notebook
parameter_list|,
name|GtkNotebookPage
modifier|*
name|page
parameter_list|,
name|guint
name|page_num
parameter_list|)
block|{
name|GimpColorNotebook
modifier|*
name|notebook
decl_stmt|;
name|GtkWidget
modifier|*
name|page_widget
decl_stmt|;
name|notebook
operator|=
name|GIMP_COLOR_NOTEBOOK
argument_list|(
name|gtk_notebook
argument_list|)
expr_stmt|;
name|GTK_NOTEBOOK_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|switch_page
argument_list|(
name|gtk_notebook
argument_list|,
name|page
argument_list|,
name|page_num
argument_list|)
expr_stmt|;
name|page_widget
operator|=
name|gtk_notebook_get_nth_page
argument_list|(
name|gtk_notebook
argument_list|,
name|page_num
argument_list|)
expr_stmt|;
name|notebook
operator|->
name|cur_page
operator|=
name|GIMP_COLOR_SELECTOR
argument_list|(
name|page_widget
argument_list|)
expr_stmt|;
name|g_signal_handlers_block_by_func
argument_list|(
name|G_OBJECT
argument_list|(
name|notebook
operator|->
name|cur_page
argument_list|)
argument_list|,
name|gimp_color_notebook_update_callback
argument_list|,
name|notebook
argument_list|)
expr_stmt|;
name|gimp_color_selector_set_channel
argument_list|(
name|notebook
operator|->
name|cur_page
argument_list|,
name|notebook
operator|->
name|channel
argument_list|)
expr_stmt|;
name|gimp_color_selector_set_color
argument_list|(
name|notebook
operator|->
name|cur_page
argument_list|,
operator|&
name|notebook
operator|->
name|rgb
argument_list|,
operator|&
name|notebook
operator|->
name|hsv
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|G_OBJECT
argument_list|(
name|notebook
operator|->
name|cur_page
argument_list|)
argument_list|,
name|gimp_color_notebook_update_callback
argument_list|,
name|notebook
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_color_notebook_new (void)
name|gimp_color_notebook_new
parameter_list|(
name|void
parameter_list|)
block|{
name|GimpColorNotebook
modifier|*
name|notebook
decl_stmt|;
name|notebook
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_COLOR_NOTEBOOK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|notebook
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_color_notebook_set_color (GimpColorNotebook * notebook,const GimpRGB * rgb,const GimpHSV * hsv)
name|gimp_color_notebook_set_color
parameter_list|(
name|GimpColorNotebook
modifier|*
name|notebook
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
specifier|const
name|GimpHSV
modifier|*
name|hsv
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_NOTEBOOK
argument_list|(
name|notebook
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|rgb
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|hsv
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|notebook
operator|->
name|rgb
operator|=
operator|*
name|rgb
expr_stmt|;
name|notebook
operator|->
name|hsv
operator|=
operator|*
name|hsv
expr_stmt|;
name|g_signal_handlers_block_by_func
argument_list|(
name|G_OBJECT
argument_list|(
name|notebook
operator|->
name|cur_page
argument_list|)
argument_list|,
name|gimp_color_notebook_update_callback
argument_list|,
name|notebook
argument_list|)
expr_stmt|;
name|gimp_color_selector_set_color
argument_list|(
name|notebook
operator|->
name|cur_page
argument_list|,
operator|&
name|notebook
operator|->
name|rgb
argument_list|,
operator|&
name|notebook
operator|->
name|hsv
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|G_OBJECT
argument_list|(
name|notebook
operator|->
name|cur_page
argument_list|)
argument_list|,
name|gimp_color_notebook_update_callback
argument_list|,
name|notebook
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_color_notebook_get_color (GimpColorNotebook * notebook,GimpRGB * rgb,GimpHSV * hsv)
name|gimp_color_notebook_get_color
parameter_list|(
name|GimpColorNotebook
modifier|*
name|notebook
parameter_list|,
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
name|GimpHSV
modifier|*
name|hsv
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_NOTEBOOK
argument_list|(
name|notebook
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|rgb
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|hsv
operator|!=
name|NULL
argument_list|)
expr_stmt|;
operator|*
name|rgb
operator|=
name|notebook
operator|->
name|rgb
expr_stmt|;
operator|*
name|hsv
operator|=
name|notebook
operator|->
name|hsv
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_color_notebook_color_changed (GimpColorNotebook * notebook)
name|gimp_color_notebook_color_changed
parameter_list|(
name|GimpColorNotebook
modifier|*
name|notebook
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_NOTEBOOK
argument_list|(
name|notebook
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|G_OBJECT
argument_list|(
name|notebook
argument_list|)
argument_list|,
name|notebook_signals
index|[
name|COLOR_CHANGED
index|]
argument_list|,
literal|0
argument_list|,
operator|&
name|notebook
operator|->
name|rgb
argument_list|,
operator|&
name|notebook
operator|->
name|hsv
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_color_notebook_set_channel (GimpColorNotebook * notebook,GimpColorSelectorChannel channel)
name|gimp_color_notebook_set_channel
parameter_list|(
name|GimpColorNotebook
modifier|*
name|notebook
parameter_list|,
name|GimpColorSelectorChannel
name|channel
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_NOTEBOOK
argument_list|(
name|notebook
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|channel
operator|!=
name|notebook
operator|->
name|channel
condition|)
block|{
name|notebook
operator|->
name|channel
operator|=
name|channel
expr_stmt|;
name|gimp_color_selector_set_channel
argument_list|(
name|notebook
operator|->
name|cur_page
argument_list|,
name|notebook
operator|->
name|channel
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_color_notebook_update_callback (GimpColorSelector * selector,const GimpRGB * rgb,const GimpHSV * hsv,GimpColorNotebook * notebook)
name|gimp_color_notebook_update_callback
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
specifier|const
name|GimpHSV
modifier|*
name|hsv
parameter_list|,
name|GimpColorNotebook
modifier|*
name|notebook
parameter_list|)
block|{
name|notebook
operator|->
name|rgb
operator|=
operator|*
name|rgb
expr_stmt|;
name|notebook
operator|->
name|hsv
operator|=
operator|*
name|hsv
expr_stmt|;
name|gimp_color_notebook_color_changed
argument_list|(
name|notebook
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

