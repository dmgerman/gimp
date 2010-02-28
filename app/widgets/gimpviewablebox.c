begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"config/gimpconfig-utils.h"
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
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdatafactory.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainerentry.h"
end_include

begin_include
include|#
directive|include
file|"gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"gimppropwidgets.h"
end_include

begin_include
include|#
directive|include
file|"gimpview.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewablebutton.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewablebox.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewrenderergradient.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|GtkWidget
modifier|*
name|gimp_viewable_box_new
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gint
name|spacing
parameter_list|,
name|GimpViewType
name|view_type
parameter_list|,
name|GimpViewType
name|button_view_size
parameter_list|,
name|GimpViewSize
name|view_size
parameter_list|,
specifier|const
name|gchar
modifier|*
name|dialog_identifier
parameter_list|,
specifier|const
name|gchar
modifier|*
name|dialog_stock_id
parameter_list|,
specifier|const
name|gchar
modifier|*
name|dialog_tooltip
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GtkWidget
modifier|*
name|view_props_connect
parameter_list|(
name|GtkWidget
modifier|*
name|box
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|view_type_prop
parameter_list|,
specifier|const
name|gchar
modifier|*
name|view_size_prop
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_gradient_box_reverse_notify
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  brush boxes  */
end_comment

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|brush_box_new (GimpContainer * container,GimpContext * context,gint spacing,GimpViewType view_type,GimpViewSize view_size)
name|brush_box_new
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gint
name|spacing
parameter_list|,
name|GimpViewType
name|view_type
parameter_list|,
name|GimpViewSize
name|view_size
parameter_list|)
block|{
if|if
condition|(
operator|!
name|container
condition|)
name|container
operator|=
name|gimp_data_factory_get_container
argument_list|(
name|context
operator|->
name|gimp
operator|->
name|brush_factory
argument_list|)
expr_stmt|;
return|return
name|gimp_viewable_box_new
argument_list|(
name|container
argument_list|,
name|context
argument_list|,
name|spacing
argument_list|,
name|view_type
argument_list|,
name|GIMP_VIEW_SIZE_SMALL
argument_list|,
name|view_size
argument_list|,
literal|"gimp-brush-grid|gimp-brush-list"
argument_list|,
name|GIMP_STOCK_BRUSH
argument_list|,
name|_
argument_list|(
literal|"Open the brush selection dialog"
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_brush_box_new (GimpContainer * container,GimpContext * context,gint spacing)
name|gimp_brush_box_new
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gint
name|spacing
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|container
operator|==
name|NULL
operator|||
name|GIMP_IS_CONTAINER
argument_list|(
name|container
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|brush_box_new
argument_list|(
name|container
argument_list|,
name|context
argument_list|,
name|spacing
argument_list|,
name|GIMP_VIEW_TYPE_GRID
argument_list|,
name|GIMP_VIEW_SIZE_SMALL
argument_list|)
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_prop_brush_box_new (GimpContainer * container,GimpContext * context,gint spacing,const gchar * view_type_prop,const gchar * view_size_prop)
name|gimp_prop_brush_box_new
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gint
name|spacing
parameter_list|,
specifier|const
name|gchar
modifier|*
name|view_type_prop
parameter_list|,
specifier|const
name|gchar
modifier|*
name|view_size_prop
parameter_list|)
block|{
name|GimpViewType
name|view_type
decl_stmt|;
name|GimpViewSize
name|view_size
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|container
operator|==
name|NULL
operator|||
name|GIMP_IS_CONTAINER
argument_list|(
name|container
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_get
argument_list|(
name|context
argument_list|,
name|view_type_prop
argument_list|,
operator|&
name|view_type
argument_list|,
name|view_size_prop
argument_list|,
operator|&
name|view_size
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|view_props_connect
argument_list|(
name|brush_box_new
argument_list|(
name|container
argument_list|,
name|context
argument_list|,
name|spacing
argument_list|,
name|view_type
argument_list|,
name|view_size
argument_list|)
argument_list|,
name|context
argument_list|,
name|view_type_prop
argument_list|,
name|view_size_prop
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  pattern boxes  */
end_comment

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|pattern_box_new (GimpContainer * container,GimpContext * context,gint spacing,GimpViewType view_type,GimpViewSize view_size)
name|pattern_box_new
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gint
name|spacing
parameter_list|,
name|GimpViewType
name|view_type
parameter_list|,
name|GimpViewSize
name|view_size
parameter_list|)
block|{
if|if
condition|(
operator|!
name|container
condition|)
name|container
operator|=
name|gimp_data_factory_get_container
argument_list|(
name|context
operator|->
name|gimp
operator|->
name|pattern_factory
argument_list|)
expr_stmt|;
return|return
name|gimp_viewable_box_new
argument_list|(
name|container
argument_list|,
name|context
argument_list|,
name|spacing
argument_list|,
name|view_type
argument_list|,
name|GIMP_VIEW_SIZE_SMALL
argument_list|,
name|view_size
argument_list|,
literal|"gimp-pattern-grid|gimp-pattern-list"
argument_list|,
name|GIMP_STOCK_PATTERN
argument_list|,
name|_
argument_list|(
literal|"Open the pattern selection dialog"
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_pattern_box_new (GimpContainer * container,GimpContext * context,gint spacing)
name|gimp_pattern_box_new
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gint
name|spacing
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|container
operator|==
name|NULL
operator|||
name|GIMP_IS_CONTAINER
argument_list|(
name|container
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|pattern_box_new
argument_list|(
name|container
argument_list|,
name|context
argument_list|,
name|spacing
argument_list|,
name|GIMP_VIEW_TYPE_GRID
argument_list|,
name|GIMP_VIEW_SIZE_SMALL
argument_list|)
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_prop_pattern_box_new (GimpContainer * container,GimpContext * context,gint spacing,const gchar * view_type_prop,const gchar * view_size_prop)
name|gimp_prop_pattern_box_new
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gint
name|spacing
parameter_list|,
specifier|const
name|gchar
modifier|*
name|view_type_prop
parameter_list|,
specifier|const
name|gchar
modifier|*
name|view_size_prop
parameter_list|)
block|{
name|GimpViewType
name|view_type
decl_stmt|;
name|GimpViewSize
name|view_size
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|container
operator|==
name|NULL
operator|||
name|GIMP_IS_CONTAINER
argument_list|(
name|container
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_get
argument_list|(
name|context
argument_list|,
name|view_type_prop
argument_list|,
operator|&
name|view_type
argument_list|,
name|view_size_prop
argument_list|,
operator|&
name|view_size
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|view_props_connect
argument_list|(
name|pattern_box_new
argument_list|(
name|container
argument_list|,
name|context
argument_list|,
name|spacing
argument_list|,
name|view_type
argument_list|,
name|view_size
argument_list|)
argument_list|,
name|context
argument_list|,
name|view_type_prop
argument_list|,
name|view_size_prop
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  gradient boxes  */
end_comment

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|gradient_box_new (GimpContainer * container,GimpContext * context,gint spacing,GimpViewType view_type,GimpViewSize view_size,const gchar * reverse_prop)
name|gradient_box_new
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gint
name|spacing
parameter_list|,
name|GimpViewType
name|view_type
parameter_list|,
name|GimpViewSize
name|view_size
parameter_list|,
specifier|const
name|gchar
modifier|*
name|reverse_prop
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
if|if
condition|(
operator|!
name|container
condition|)
name|container
operator|=
name|gimp_data_factory_get_container
argument_list|(
name|context
operator|->
name|gimp
operator|->
name|gradient_factory
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
name|spacing
argument_list|)
expr_stmt|;
name|button
operator|=
name|gimp_viewable_button_new
argument_list|(
name|container
argument_list|,
name|context
argument_list|,
name|view_type
argument_list|,
name|GIMP_VIEW_SIZE_LARGE
argument_list|,
name|view_size
argument_list|,
literal|1
argument_list|,
name|gimp_dialog_factory_get_singleton
argument_list|()
argument_list|,
literal|"gimp-gradient-list|gimp-gradient-grid"
argument_list|,
name|GIMP_STOCK_GRADIENT
argument_list|,
name|_
argument_list|(
literal|"Open the gradient selection dialog"
argument_list|)
argument_list|)
expr_stmt|;
name|GIMP_VIEWABLE_BUTTON
argument_list|(
name|button
argument_list|)
operator|->
name|button_view_size
operator|=
name|GIMP_VIEW_SIZE_SMALL
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|hbox
argument_list|)
argument_list|,
literal|"viewable-button"
argument_list|,
name|button
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|button
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
if|if
condition|(
name|reverse_prop
condition|)
block|{
name|GtkWidget
modifier|*
name|toggle
decl_stmt|;
name|GtkWidget
modifier|*
name|view
decl_stmt|;
name|GtkWidget
modifier|*
name|image
decl_stmt|;
name|gchar
modifier|*
name|signal_name
decl_stmt|;
name|toggle
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|G_OBJECT
argument_list|(
name|context
argument_list|)
argument_list|,
name|reverse_prop
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|toggle
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|toggle
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|toggle
argument_list|,
name|_
argument_list|(
literal|"Reverse"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|image
operator|=
name|gtk_image_new_from_stock
argument_list|(
name|GIMP_STOCK_FLIP_HORIZONTAL
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|toggle
argument_list|)
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|view
operator|=
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|button
argument_list|)
argument_list|)
expr_stmt|;
name|signal_name
operator|=
name|g_strconcat
argument_list|(
literal|"notify::"
argument_list|,
name|reverse_prop
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|context
argument_list|,
name|signal_name
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_gradient_box_reverse_notify
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
name|g_free
argument_list|(
name|signal_name
argument_list|)
expr_stmt|;
name|gimp_gradient_box_reverse_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_VIEW
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
block|}
return|return
name|hbox
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_gradient_box_new (GimpContainer * container,GimpContext * context,gint spacing,const gchar * reverse_prop)
name|gimp_gradient_box_new
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gint
name|spacing
parameter_list|,
specifier|const
name|gchar
modifier|*
name|reverse_prop
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|container
operator|==
name|NULL
operator|||
name|GIMP_IS_CONTAINER
argument_list|(
name|container
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|gradient_box_new
argument_list|(
name|container
argument_list|,
name|context
argument_list|,
name|spacing
argument_list|,
name|GIMP_VIEW_TYPE_LIST
argument_list|,
name|GIMP_VIEW_SIZE_LARGE
argument_list|,
name|reverse_prop
argument_list|)
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_prop_gradient_box_new (GimpContainer * container,GimpContext * context,gint spacing,const gchar * view_type_prop,const gchar * view_size_prop,const gchar * reverse_prop)
name|gimp_prop_gradient_box_new
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gint
name|spacing
parameter_list|,
specifier|const
name|gchar
modifier|*
name|view_type_prop
parameter_list|,
specifier|const
name|gchar
modifier|*
name|view_size_prop
parameter_list|,
specifier|const
name|gchar
modifier|*
name|reverse_prop
parameter_list|)
block|{
name|GimpViewType
name|view_type
decl_stmt|;
name|GimpViewSize
name|view_size
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|container
operator|==
name|NULL
operator|||
name|GIMP_IS_CONTAINER
argument_list|(
name|container
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_get
argument_list|(
name|context
argument_list|,
name|view_type_prop
argument_list|,
operator|&
name|view_type
argument_list|,
name|view_size_prop
argument_list|,
operator|&
name|view_size
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|view_props_connect
argument_list|(
name|gradient_box_new
argument_list|(
name|container
argument_list|,
name|context
argument_list|,
name|spacing
argument_list|,
name|view_type
argument_list|,
name|view_size
argument_list|,
name|reverse_prop
argument_list|)
argument_list|,
name|context
argument_list|,
name|view_type_prop
argument_list|,
name|view_size_prop
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  palette boxes  */
end_comment

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|palette_box_new (GimpContainer * container,GimpContext * context,gint spacing,GimpViewType view_type,GimpViewSize view_size)
name|palette_box_new
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gint
name|spacing
parameter_list|,
name|GimpViewType
name|view_type
parameter_list|,
name|GimpViewSize
name|view_size
parameter_list|)
block|{
if|if
condition|(
operator|!
name|container
condition|)
name|container
operator|=
name|gimp_data_factory_get_container
argument_list|(
name|context
operator|->
name|gimp
operator|->
name|palette_factory
argument_list|)
expr_stmt|;
return|return
name|gimp_viewable_box_new
argument_list|(
name|container
argument_list|,
name|context
argument_list|,
name|spacing
argument_list|,
name|view_type
argument_list|,
name|GIMP_VIEW_SIZE_MEDIUM
argument_list|,
name|view_size
argument_list|,
literal|"gimp-palette-list|gimp-palette-grid"
argument_list|,
name|GIMP_STOCK_PALETTE
argument_list|,
name|_
argument_list|(
literal|"Open the palette selection dialog"
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_palette_box_new (GimpContainer * container,GimpContext * context,gint spacing)
name|gimp_palette_box_new
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gint
name|spacing
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|container
operator|==
name|NULL
operator|||
name|GIMP_IS_CONTAINER
argument_list|(
name|container
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|palette_box_new
argument_list|(
name|container
argument_list|,
name|context
argument_list|,
name|spacing
argument_list|,
name|GIMP_VIEW_TYPE_LIST
argument_list|,
name|GIMP_VIEW_SIZE_MEDIUM
argument_list|)
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_prop_palette_box_new (GimpContainer * container,GimpContext * context,gint spacing,const gchar * view_type_prop,const gchar * view_size_prop)
name|gimp_prop_palette_box_new
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gint
name|spacing
parameter_list|,
specifier|const
name|gchar
modifier|*
name|view_type_prop
parameter_list|,
specifier|const
name|gchar
modifier|*
name|view_size_prop
parameter_list|)
block|{
name|GimpViewType
name|view_type
decl_stmt|;
name|GimpViewSize
name|view_size
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|container
operator|==
name|NULL
operator|||
name|GIMP_IS_CONTAINER
argument_list|(
name|container
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_get
argument_list|(
name|context
argument_list|,
name|view_type_prop
argument_list|,
operator|&
name|view_type
argument_list|,
name|view_size_prop
argument_list|,
operator|&
name|view_size
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|view_props_connect
argument_list|(
name|palette_box_new
argument_list|(
name|container
argument_list|,
name|context
argument_list|,
name|spacing
argument_list|,
name|view_type
argument_list|,
name|view_size
argument_list|)
argument_list|,
name|context
argument_list|,
name|view_type_prop
argument_list|,
name|view_size_prop
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  font boxes  */
end_comment

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|font_box_new (GimpContainer * container,GimpContext * context,gint spacing,GimpViewType view_type,GimpViewSize view_size)
name|font_box_new
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gint
name|spacing
parameter_list|,
name|GimpViewType
name|view_type
parameter_list|,
name|GimpViewSize
name|view_size
parameter_list|)
block|{
if|if
condition|(
operator|!
name|container
condition|)
name|container
operator|=
name|context
operator|->
name|gimp
operator|->
name|fonts
expr_stmt|;
return|return
name|gimp_viewable_box_new
argument_list|(
name|container
argument_list|,
name|context
argument_list|,
name|spacing
argument_list|,
name|view_type
argument_list|,
name|GIMP_VIEW_SIZE_SMALL
argument_list|,
name|view_size
argument_list|,
literal|"gimp-font-list|gimp-font-grid"
argument_list|,
name|GIMP_STOCK_FONT
argument_list|,
name|_
argument_list|(
literal|"Open the font selection dialog"
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_font_box_new (GimpContainer * container,GimpContext * context,gint spacing)
name|gimp_font_box_new
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gint
name|spacing
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|container
operator|==
name|NULL
operator|||
name|GIMP_IS_CONTAINER
argument_list|(
name|container
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|font_box_new
argument_list|(
name|container
argument_list|,
name|context
argument_list|,
name|spacing
argument_list|,
name|GIMP_VIEW_TYPE_LIST
argument_list|,
name|GIMP_VIEW_SIZE_SMALL
argument_list|)
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_prop_font_box_new (GimpContainer * container,GimpContext * context,gint spacing,const gchar * view_type_prop,const gchar * view_size_prop)
name|gimp_prop_font_box_new
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gint
name|spacing
parameter_list|,
specifier|const
name|gchar
modifier|*
name|view_type_prop
parameter_list|,
specifier|const
name|gchar
modifier|*
name|view_size_prop
parameter_list|)
block|{
name|GimpViewType
name|view_type
decl_stmt|;
name|GimpViewSize
name|view_size
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|container
operator|==
name|NULL
operator|||
name|GIMP_IS_CONTAINER
argument_list|(
name|container
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_get
argument_list|(
name|context
argument_list|,
name|view_type_prop
argument_list|,
operator|&
name|view_type
argument_list|,
name|view_size_prop
argument_list|,
operator|&
name|view_size
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|view_props_connect
argument_list|(
name|font_box_new
argument_list|(
name|container
argument_list|,
name|context
argument_list|,
name|spacing
argument_list|,
name|view_type
argument_list|,
name|view_size
argument_list|)
argument_list|,
name|context
argument_list|,
name|view_type_prop
argument_list|,
name|view_size_prop
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
DECL|function|gimp_viewable_box_new (GimpContainer * container,GimpContext * context,gint spacing,GimpViewType view_type,GimpViewType button_view_size,GimpViewSize view_size,const gchar * dialog_identifier,const gchar * dialog_stock_id,const gchar * dialog_tooltip)
name|gimp_viewable_box_new
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gint
name|spacing
parameter_list|,
name|GimpViewType
name|view_type
parameter_list|,
name|GimpViewType
name|button_view_size
parameter_list|,
name|GimpViewSize
name|view_size
parameter_list|,
specifier|const
name|gchar
modifier|*
name|dialog_identifier
parameter_list|,
specifier|const
name|gchar
modifier|*
name|dialog_stock_id
parameter_list|,
specifier|const
name|gchar
modifier|*
name|dialog_tooltip
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|entry
decl_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
name|spacing
argument_list|)
expr_stmt|;
name|button
operator|=
name|gimp_viewable_button_new
argument_list|(
name|container
argument_list|,
name|context
argument_list|,
name|view_type
argument_list|,
name|button_view_size
argument_list|,
name|view_size
argument_list|,
literal|1
argument_list|,
name|gimp_dialog_factory_get_singleton
argument_list|()
argument_list|,
name|dialog_identifier
argument_list|,
name|dialog_stock_id
argument_list|,
name|dialog_tooltip
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|hbox
argument_list|)
argument_list|,
literal|"viewable-button"
argument_list|,
name|button
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|button
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|entry
operator|=
name|gimp_container_entry_new
argument_list|(
name|container
argument_list|,
name|context
argument_list|,
name|view_size
argument_list|,
literal|1
argument_list|)
expr_stmt|;
comment|/*  set a silly smally size request on the entry to disable    *  GtkEntry's minimal width of 150 pixels.    */
name|gtk_widget_set_size_request
argument_list|(
name|entry
argument_list|,
literal|10
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|entry
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|entry
argument_list|)
expr_stmt|;
return|return
name|hbox
return|;
block|}
end_function

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|view_props_connect (GtkWidget * box,GimpContext * context,const gchar * view_type_prop,const gchar * view_size_prop)
name|view_props_connect
parameter_list|(
name|GtkWidget
modifier|*
name|box
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|view_type_prop
parameter_list|,
specifier|const
name|gchar
modifier|*
name|view_size_prop
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|button
init|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|box
argument_list|)
argument_list|,
literal|"viewable-button"
argument_list|)
decl_stmt|;
name|gimp_config_connect_full
argument_list|(
name|G_OBJECT
argument_list|(
name|context
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
name|view_type_prop
argument_list|,
literal|"popup-view-type"
argument_list|)
expr_stmt|;
name|gimp_config_connect_full
argument_list|(
name|G_OBJECT
argument_list|(
name|context
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
name|view_size_prop
argument_list|,
literal|"popup-view-size"
argument_list|)
expr_stmt|;
return|return
name|box
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_gradient_box_reverse_notify (GObject * object,GParamSpec * pspec,GimpView * view)
name|gimp_gradient_box_reverse_notify
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpView
modifier|*
name|view
parameter_list|)
block|{
name|GimpViewRendererGradient
modifier|*
name|rendergrad
decl_stmt|;
name|gboolean
name|reverse
decl_stmt|;
name|rendergrad
operator|=
name|GIMP_VIEW_RENDERER_GRADIENT
argument_list|(
name|view
operator|->
name|renderer
argument_list|)
expr_stmt|;
name|g_object_get
argument_list|(
name|object
argument_list|,
literal|"gradient-reverse"
argument_list|,
operator|&
name|reverse
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_view_renderer_gradient_set_reverse
argument_list|(
name|rendergrad
argument_list|,
name|reverse
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

