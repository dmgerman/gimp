begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"gui/color-notebook.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorpanel.h"
end_include

begin_struct
DECL|struct|_GimpColorPanel
struct|struct
name|_GimpColorPanel
block|{
DECL|member|parent
name|GimpColorButton
name|parent
decl_stmt|;
DECL|member|color_notebook
name|ColorNotebook
modifier|*
name|color_notebook
decl_stmt|;
DECL|member|color_notebook_active
name|gboolean
name|color_notebook_active
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_color_panel_class_init
parameter_list|(
name|GimpColorPanelClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_panel_init
parameter_list|(
name|GimpColorPanel
modifier|*
name|panel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_panel_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_panel_color_changed
parameter_list|(
name|GimpColorButton
modifier|*
name|button
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_panel_clicked
parameter_list|(
name|GtkButton
modifier|*
name|button
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_panel_select_callback
parameter_list|(
name|ColorNotebook
modifier|*
name|notebook
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|ColorNotebookState
name|state
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpColorButtonClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GtkType
DECL|function|gimp_color_panel_get_type (void)
name|gimp_color_panel_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|guint
name|panel_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|panel_type
condition|)
block|{
name|GtkTypeInfo
name|panel_info
init|=
block|{
literal|"GimpColorPanel"
block|,
sizeof|sizeof
argument_list|(
name|GimpColorPanel
argument_list|)
block|,
sizeof|sizeof
argument_list|(
name|GimpColorPanelClass
argument_list|)
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|gimp_color_panel_class_init
block|,
operator|(
name|GtkObjectInitFunc
operator|)
name|gimp_color_panel_init
block|,
comment|/* reserved_1 */
name|NULL
block|,
comment|/* reserved_2 */
name|NULL
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|NULL
block|}
decl_stmt|;
name|panel_type
operator|=
name|gtk_type_unique
argument_list|(
name|GIMP_TYPE_COLOR_BUTTON
argument_list|,
operator|&
name|panel_info
argument_list|)
expr_stmt|;
block|}
return|return
name|panel_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_panel_class_init (GimpColorPanelClass * klass)
name|gimp_color_panel_class_init
parameter_list|(
name|GimpColorPanelClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GtkButtonClass
modifier|*
name|button_class
decl_stmt|;
name|GimpColorButtonClass
modifier|*
name|color_button_class
decl_stmt|;
name|object_class
operator|=
operator|(
name|GtkObjectClass
operator|*
operator|)
name|klass
expr_stmt|;
name|button_class
operator|=
operator|(
name|GtkButtonClass
operator|*
operator|)
name|klass
expr_stmt|;
name|color_button_class
operator|=
operator|(
name|GimpColorButtonClass
operator|*
operator|)
name|klass
expr_stmt|;
name|parent_class
operator|=
name|gtk_type_class
argument_list|(
name|GIMP_TYPE_COLOR_BUTTON
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|destroy
operator|=
name|gimp_color_panel_destroy
expr_stmt|;
name|button_class
operator|->
name|clicked
operator|=
name|gimp_color_panel_clicked
expr_stmt|;
name|color_button_class
operator|->
name|color_changed
operator|=
name|gimp_color_panel_color_changed
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_panel_init (GimpColorPanel * panel)
name|gimp_color_panel_init
parameter_list|(
name|GimpColorPanel
modifier|*
name|panel
parameter_list|)
block|{
name|panel
operator|->
name|color_notebook
operator|=
name|NULL
expr_stmt|;
name|panel
operator|->
name|color_notebook_active
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_panel_destroy (GtkObject * object)
name|gimp_color_panel_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpColorPanel
modifier|*
name|panel
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|object
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_PANEL
argument_list|(
name|object
argument_list|)
argument_list|)
expr_stmt|;
name|panel
operator|=
name|GIMP_COLOR_PANEL
argument_list|(
name|object
argument_list|)
expr_stmt|;
if|if
condition|(
name|panel
operator|->
name|color_notebook
condition|)
block|{
name|color_notebook_hide
argument_list|(
name|panel
operator|->
name|color_notebook
argument_list|)
expr_stmt|;
name|color_notebook_free
argument_list|(
name|panel
operator|->
name|color_notebook
argument_list|)
expr_stmt|;
name|panel
operator|->
name|color_notebook
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
condition|)
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_color_panel_new (const gchar * title,const GimpRGB * color,GimpColorAreaType type,gint width,gint height)
name|gimp_color_panel_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|GimpColorAreaType
name|type
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
block|{
name|GimpColorPanel
modifier|*
name|panel
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|color
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|panel
operator|=
name|gtk_type_new
argument_list|(
name|GIMP_TYPE_COLOR_PANEL
argument_list|)
expr_stmt|;
name|GIMP_COLOR_BUTTON
argument_list|(
name|panel
argument_list|)
operator|->
name|title
operator|=
name|g_strdup
argument_list|(
name|title
argument_list|)
expr_stmt|;
name|gimp_color_button_set_type
argument_list|(
name|GIMP_COLOR_BUTTON
argument_list|(
name|panel
argument_list|)
argument_list|,
name|type
argument_list|)
expr_stmt|;
name|gimp_color_button_set_color
argument_list|(
name|GIMP_COLOR_BUTTON
argument_list|(
name|panel
argument_list|)
argument_list|,
name|color
argument_list|)
expr_stmt|;
name|gtk_widget_set_usize
argument_list|(
name|GTK_WIDGET
argument_list|(
name|panel
argument_list|)
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|panel
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_panel_color_changed (GimpColorButton * button)
name|gimp_color_panel_color_changed
parameter_list|(
name|GimpColorButton
modifier|*
name|button
parameter_list|)
block|{
name|GimpColorPanel
modifier|*
name|panel
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|panel
operator|=
name|GIMP_COLOR_PANEL
argument_list|(
name|button
argument_list|)
expr_stmt|;
if|if
condition|(
name|panel
operator|->
name|color_notebook_active
condition|)
block|{
name|gimp_color_button_get_color
argument_list|(
name|GIMP_COLOR_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|color_notebook_set_color
argument_list|(
name|panel
operator|->
name|color_notebook
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_panel_clicked (GtkButton * button)
name|gimp_color_panel_clicked
parameter_list|(
name|GtkButton
modifier|*
name|button
parameter_list|)
block|{
name|GimpColorPanel
modifier|*
name|panel
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|panel
operator|=
name|GIMP_COLOR_PANEL
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|gimp_color_button_get_color
argument_list|(
name|GIMP_COLOR_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|panel
operator|->
name|color_notebook
condition|)
block|{
name|panel
operator|->
name|color_notebook
operator|=
name|color_notebook_new
argument_list|(
name|GIMP_COLOR_BUTTON
argument_list|(
name|button
argument_list|)
operator|->
name|title
argument_list|,
operator|(
specifier|const
name|GimpRGB
operator|*
operator|)
operator|&
name|color
argument_list|,
name|gimp_color_panel_select_callback
argument_list|,
name|panel
argument_list|,
name|FALSE
argument_list|,
name|gimp_color_button_has_alpha
argument_list|(
name|GIMP_COLOR_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|panel
operator|->
name|color_notebook_active
operator|=
name|TRUE
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
operator|!
name|panel
operator|->
name|color_notebook_active
condition|)
block|{
name|color_notebook_show
argument_list|(
name|panel
operator|->
name|color_notebook
argument_list|)
expr_stmt|;
name|panel
operator|->
name|color_notebook_active
operator|=
name|TRUE
expr_stmt|;
block|}
name|color_notebook_set_color
argument_list|(
name|panel
operator|->
name|color_notebook
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_panel_select_callback (ColorNotebook * notebook,const GimpRGB * color,ColorNotebookState state,gpointer data)
name|gimp_color_panel_select_callback
parameter_list|(
name|ColorNotebook
modifier|*
name|notebook
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|ColorNotebookState
name|state
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpColorPanel
modifier|*
name|panel
decl_stmt|;
name|panel
operator|=
name|GIMP_COLOR_PANEL
argument_list|(
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|panel
operator|->
name|color_notebook
condition|)
block|{
switch|switch
condition|(
name|state
condition|)
block|{
case|case
name|COLOR_NOTEBOOK_UPDATE
case|:
break|break;
case|case
name|COLOR_NOTEBOOK_OK
case|:
name|gimp_color_button_set_color
argument_list|(
name|GIMP_COLOR_BUTTON
argument_list|(
name|panel
argument_list|)
argument_list|,
name|color
argument_list|)
expr_stmt|;
comment|/* Fallthrough */
case|case
name|COLOR_NOTEBOOK_CANCEL
case|:
name|color_notebook_hide
argument_list|(
name|panel
operator|->
name|color_notebook
argument_list|)
expr_stmt|;
name|panel
operator|->
name|color_notebook_active
operator|=
name|FALSE
expr_stmt|;
block|}
block|}
block|}
end_function

end_unit

