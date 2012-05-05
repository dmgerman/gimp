begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpcolordisplaystack.c  * Copyright (C) 2003 Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gegl.h>
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

begin_undef
undef|#
directive|undef
name|GIMP_DISABLE_DEPRECATED
end_undef

begin_include
include|#
directive|include
file|"gimpcolordisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolordisplaystack.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgetsmarshal.h"
end_include

begin_comment
comment|/**  * SECTION: gimpcolordisplaystack  * @title: GimpColorDisplayStack  * @short_description: A stack of color correction modules.  * @see_also: #GimpColorDisplay  *  * A stack of color correction modules.  **/
end_comment

begin_enum
enum|enum
DECL|enum|__anon2bd9ab7d0103
block|{
DECL|enumerator|CHANGED
name|CHANGED
block|,
DECL|enumerator|ADDED
name|ADDED
block|,
DECL|enumerator|REMOVED
name|REMOVED
block|,
DECL|enumerator|REORDERED
name|REORDERED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_color_display_stack_dispose
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
name|gimp_color_display_stack_display_changed
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|,
name|GimpColorDisplayStack
modifier|*
name|stack
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_display_stack_display_enabled
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpColorDisplayStack
modifier|*
name|stack
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_display_stack_disconnect
parameter_list|(
name|GimpColorDisplayStack
modifier|*
name|stack
parameter_list|,
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|GimpColorDisplayStack
argument_list|,
argument|gimp_color_display_stack
argument_list|,
argument|G_TYPE_OBJECT
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_color_display_stack_parent_class
end_define

begin_decl_stmt
specifier|static
name|guint
name|stack_signals
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
specifier|static
name|void
DECL|function|gimp_color_display_stack_class_init (GimpColorDisplayStackClass * klass)
name|gimp_color_display_stack_class_init
parameter_list|(
name|GimpColorDisplayStackClass
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
name|stack_signals
index|[
name|CHANGED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"changed"
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
name|GimpColorDisplayStackClass
argument_list|,
name|changed
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|g_cclosure_marshal_VOID__VOID
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|stack_signals
index|[
name|ADDED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"added"
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
name|GimpColorDisplayStackClass
argument_list|,
name|added
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|_gimp_widgets_marshal_VOID__OBJECT_INT
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|2
argument_list|,
name|GIMP_TYPE_COLOR_DISPLAY
argument_list|,
name|G_TYPE_INT
argument_list|)
expr_stmt|;
name|stack_signals
index|[
name|REMOVED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"removed"
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
name|GimpColorDisplayStackClass
argument_list|,
name|removed
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|_gimp_widgets_marshal_VOID__OBJECT
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|GIMP_TYPE_COLOR_DISPLAY
argument_list|)
expr_stmt|;
name|stack_signals
index|[
name|REORDERED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"reordered"
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
name|GimpColorDisplayStackClass
argument_list|,
name|reordered
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|_gimp_widgets_marshal_VOID__OBJECT_INT
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|2
argument_list|,
name|GIMP_TYPE_COLOR_DISPLAY
argument_list|,
name|G_TYPE_INT
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|dispose
operator|=
name|gimp_color_display_stack_dispose
expr_stmt|;
name|klass
operator|->
name|changed
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|added
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|removed
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|reordered
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_display_stack_init (GimpColorDisplayStack * stack)
name|gimp_color_display_stack_init
parameter_list|(
name|GimpColorDisplayStack
modifier|*
name|stack
parameter_list|)
block|{
name|stack
operator|->
name|filters
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_display_stack_dispose (GObject * object)
name|gimp_color_display_stack_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpColorDisplayStack
modifier|*
name|stack
init|=
name|GIMP_COLOR_DISPLAY_STACK
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|stack
operator|->
name|filters
condition|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|stack
operator|->
name|filters
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpColorDisplay
modifier|*
name|display
init|=
name|list
operator|->
name|data
decl_stmt|;
name|gimp_color_display_stack_disconnect
argument_list|(
name|stack
argument_list|,
name|display
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|display
argument_list|)
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|stack
operator|->
name|filters
argument_list|)
expr_stmt|;
name|stack
operator|->
name|filters
operator|=
name|NULL
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|dispose
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpColorDisplayStack
modifier|*
DECL|function|gimp_color_display_stack_new (void)
name|gimp_color_display_stack_new
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_COLOR_DISPLAY_STACK
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpColorDisplayStack
modifier|*
DECL|function|gimp_color_display_stack_clone (GimpColorDisplayStack * stack)
name|gimp_color_display_stack_clone
parameter_list|(
name|GimpColorDisplayStack
modifier|*
name|stack
parameter_list|)
block|{
name|GimpColorDisplayStack
modifier|*
name|clone
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_COLOR_DISPLAY_STACK
argument_list|(
name|stack
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|clone
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_COLOR_DISPLAY_STACK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|stack
operator|->
name|filters
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpColorDisplay
modifier|*
name|display
decl_stmt|;
name|display
operator|=
name|gimp_color_display_clone
argument_list|(
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
name|gimp_color_display_stack_add
argument_list|(
name|clone
argument_list|,
name|display
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|display
argument_list|)
expr_stmt|;
block|}
return|return
name|clone
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_color_display_stack_changed (GimpColorDisplayStack * stack)
name|gimp_color_display_stack_changed
parameter_list|(
name|GimpColorDisplayStack
modifier|*
name|stack
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_DISPLAY_STACK
argument_list|(
name|stack
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|stack
argument_list|,
name|stack_signals
index|[
name|CHANGED
index|]
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_color_display_stack_add (GimpColorDisplayStack * stack,GimpColorDisplay * display)
name|gimp_color_display_stack_add
parameter_list|(
name|GimpColorDisplayStack
modifier|*
name|stack
parameter_list|,
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_DISPLAY_STACK
argument_list|(
name|stack
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_DISPLAY
argument_list|(
name|display
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|g_list_find
argument_list|(
name|stack
operator|->
name|filters
argument_list|,
name|display
argument_list|)
operator|==
name|NULL
argument_list|)
expr_stmt|;
name|stack
operator|->
name|filters
operator|=
name|g_list_append
argument_list|(
name|stack
operator|->
name|filters
argument_list|,
name|g_object_ref
argument_list|(
name|display
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|display
argument_list|,
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_color_display_stack_display_changed
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|stack
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|display
argument_list|,
literal|"notify::enabled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_color_display_stack_display_enabled
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|stack
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|stack
argument_list|,
name|stack_signals
index|[
name|ADDED
index|]
argument_list|,
literal|0
argument_list|,
name|display
argument_list|,
name|g_list_length
argument_list|(
name|stack
operator|->
name|filters
argument_list|)
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gimp_color_display_stack_changed
argument_list|(
name|stack
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_color_display_stack_remove (GimpColorDisplayStack * stack,GimpColorDisplay * display)
name|gimp_color_display_stack_remove
parameter_list|(
name|GimpColorDisplayStack
modifier|*
name|stack
parameter_list|,
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_DISPLAY_STACK
argument_list|(
name|stack
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_DISPLAY
argument_list|(
name|display
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|g_list_find
argument_list|(
name|stack
operator|->
name|filters
argument_list|,
name|display
argument_list|)
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gimp_color_display_stack_disconnect
argument_list|(
name|stack
argument_list|,
name|display
argument_list|)
expr_stmt|;
name|stack
operator|->
name|filters
operator|=
name|g_list_remove
argument_list|(
name|stack
operator|->
name|filters
argument_list|,
name|display
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|stack
argument_list|,
name|stack_signals
index|[
name|REMOVED
index|]
argument_list|,
literal|0
argument_list|,
name|display
argument_list|)
expr_stmt|;
name|gimp_color_display_stack_changed
argument_list|(
name|stack
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|display
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_color_display_stack_reorder_up (GimpColorDisplayStack * stack,GimpColorDisplay * display)
name|gimp_color_display_stack_reorder_up
parameter_list|(
name|GimpColorDisplayStack
modifier|*
name|stack
parameter_list|,
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_DISPLAY_STACK
argument_list|(
name|stack
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_DISPLAY
argument_list|(
name|display
argument_list|)
argument_list|)
expr_stmt|;
name|list
operator|=
name|g_list_find
argument_list|(
name|stack
operator|->
name|filters
argument_list|,
name|display
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|list
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|list
operator|->
name|prev
condition|)
block|{
name|list
operator|->
name|data
operator|=
name|list
operator|->
name|prev
operator|->
name|data
expr_stmt|;
name|list
operator|->
name|prev
operator|->
name|data
operator|=
name|display
expr_stmt|;
name|g_signal_emit
argument_list|(
name|stack
argument_list|,
name|stack_signals
index|[
name|REORDERED
index|]
argument_list|,
literal|0
argument_list|,
name|display
argument_list|,
name|g_list_position
argument_list|(
name|stack
operator|->
name|filters
argument_list|,
name|list
operator|->
name|prev
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_color_display_stack_changed
argument_list|(
name|stack
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_color_display_stack_reorder_down (GimpColorDisplayStack * stack,GimpColorDisplay * display)
name|gimp_color_display_stack_reorder_down
parameter_list|(
name|GimpColorDisplayStack
modifier|*
name|stack
parameter_list|,
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_DISPLAY_STACK
argument_list|(
name|stack
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_DISPLAY
argument_list|(
name|display
argument_list|)
argument_list|)
expr_stmt|;
name|list
operator|=
name|g_list_find
argument_list|(
name|stack
operator|->
name|filters
argument_list|,
name|display
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|list
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|list
operator|->
name|next
condition|)
block|{
name|list
operator|->
name|data
operator|=
name|list
operator|->
name|next
operator|->
name|data
expr_stmt|;
name|list
operator|->
name|next
operator|->
name|data
operator|=
name|display
expr_stmt|;
name|g_signal_emit
argument_list|(
name|stack
argument_list|,
name|stack_signals
index|[
name|REORDERED
index|]
argument_list|,
literal|0
argument_list|,
name|display
argument_list|,
name|g_list_position
argument_list|(
name|stack
operator|->
name|filters
argument_list|,
name|list
operator|->
name|next
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_color_display_stack_changed
argument_list|(
name|stack
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_color_display_stack_convert_surface:  * @stack: a #GimpColorDisplayStack  * @surface: a #cairo_image_surface_t of type ARGB32  *  * Runs all the stack's filters on all pixels in @surface.  *  * Since: GIMP 2.8  **/
end_comment

begin_function
name|void
DECL|function|gimp_color_display_stack_convert_surface (GimpColorDisplayStack * stack,cairo_surface_t * surface)
name|gimp_color_display_stack_convert_surface
parameter_list|(
name|GimpColorDisplayStack
modifier|*
name|stack
parameter_list|,
name|cairo_surface_t
modifier|*
name|surface
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_DISPLAY_STACK
argument_list|(
name|stack
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|surface
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|cairo_surface_get_type
argument_list|(
name|surface
argument_list|)
operator|==
name|CAIRO_SURFACE_TYPE_IMAGE
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|stack
operator|->
name|filters
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpColorDisplay
modifier|*
name|display
init|=
name|list
operator|->
name|data
decl_stmt|;
name|gimp_color_display_convert_surface
argument_list|(
name|display
argument_list|,
name|surface
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_color_display_stack_convert:  * @stack: a #GimpColorDisplayStack  * @buf: the pixel buffer to convert  * @width: the width of the buffer  * @height: the height of the buffer  * @bpp: the number of bytes per pixel  * @bpl: the buffer's rowstride  *  * Converts all pixels in @buf.  *  * Deprecated: GIMP 2.8: Use gimp_color_display_stack_convert_surface() instead.  **/
end_comment

begin_function
name|void
DECL|function|gimp_color_display_stack_convert (GimpColorDisplayStack * stack,guchar * buf,gint width,gint height,gint bpp,gint bpl)
name|gimp_color_display_stack_convert
parameter_list|(
name|GimpColorDisplayStack
modifier|*
name|stack
parameter_list|,
name|guchar
modifier|*
name|buf
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|bpp
parameter_list|,
name|gint
name|bpl
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_DISPLAY_STACK
argument_list|(
name|stack
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|stack
operator|->
name|filters
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpColorDisplay
modifier|*
name|display
init|=
name|list
operator|->
name|data
decl_stmt|;
name|G_GNUC_BEGIN_IGNORE_DEPRECATIONS
name|gimp_color_display_convert
argument_list|(
name|display
argument_list|,
name|buf
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|bpp
argument_list|,
name|bpl
argument_list|)
decl_stmt|;
name|G_GNUC_END_IGNORE_DEPRECATIONS
block|}
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_color_display_stack_display_changed (GimpColorDisplay * display,GimpColorDisplayStack * stack)
name|gimp_color_display_stack_display_changed
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|,
name|GimpColorDisplayStack
modifier|*
name|stack
parameter_list|)
block|{
if|if
condition|(
name|display
operator|->
name|enabled
condition|)
name|gimp_color_display_stack_changed
argument_list|(
name|stack
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_display_stack_display_enabled (GimpColorDisplay * display,GParamSpec * pspec,GimpColorDisplayStack * stack)
name|gimp_color_display_stack_display_enabled
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpColorDisplayStack
modifier|*
name|stack
parameter_list|)
block|{
name|gimp_color_display_stack_changed
argument_list|(
name|stack
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_display_stack_disconnect (GimpColorDisplayStack * stack,GimpColorDisplay * display)
name|gimp_color_display_stack_disconnect
parameter_list|(
name|GimpColorDisplayStack
modifier|*
name|stack
parameter_list|,
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|display
argument_list|,
name|gimp_color_display_stack_display_changed
argument_list|,
name|stack
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|display
argument_list|,
name|gimp_color_display_stack_display_enabled
argument_list|,
name|stack
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

