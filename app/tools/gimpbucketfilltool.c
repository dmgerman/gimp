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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|<gdk/gdkkeysyms.h>
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"tools-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable-bucket-fill.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-mask.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"paint/gimppaintoptions.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpenummenu.h"
end_include

begin_include
include|#
directive|include
file|"gimpbucketfilltool.h"
end_include

begin_include
include|#
directive|include
file|"paint_options.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_include
include|#
directive|include
file|"undo.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_typedef
DECL|typedef|BucketOptions
typedef|typedef
name|struct
name|_BucketOptions
name|BucketOptions
typedef|;
end_typedef

begin_struct
DECL|struct|_BucketOptions
struct|struct
name|_BucketOptions
block|{
DECL|member|paint_options
name|GimpPaintOptions
name|paint_options
decl_stmt|;
DECL|member|fill_transparent
name|gboolean
name|fill_transparent
decl_stmt|;
DECL|member|fill_transparent_d
name|gboolean
name|fill_transparent_d
decl_stmt|;
DECL|member|fill_transparent_w
name|GtkWidget
modifier|*
name|fill_transparent_w
decl_stmt|;
DECL|member|sample_merged
name|gboolean
name|sample_merged
decl_stmt|;
DECL|member|sample_merged_d
name|gboolean
name|sample_merged_d
decl_stmt|;
DECL|member|sample_merged_w
name|GtkWidget
modifier|*
name|sample_merged_w
decl_stmt|;
DECL|member|threshold
name|gdouble
name|threshold
decl_stmt|;
comment|/* gdouble          threshold_d; (from gimprc) */
DECL|member|threshold_w
name|GtkObject
modifier|*
name|threshold_w
decl_stmt|;
DECL|member|fill_mode
name|GimpBucketFillMode
name|fill_mode
decl_stmt|;
DECL|member|fill_mode_d
name|GimpBucketFillMode
name|fill_mode_d
decl_stmt|;
DECL|member|fill_mode_w
name|GtkWidget
modifier|*
name|fill_mode_w
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpToolClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_bucket_fill_tool_class_init
parameter_list|(
name|GimpBucketFillToolClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_bucket_fill_tool_init
parameter_list|(
name|GimpBucketFillTool
modifier|*
name|bucket_fill_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_bucket_fill_tool_button_press
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|guint32
name|time
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_bucket_fill_tool_button_release
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|guint32
name|time
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_bucket_fill_tool_modifier_key
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkModifierType
name|key
parameter_list|,
name|gboolean
name|press
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_bucket_fill_tool_cursor_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpToolOptions
modifier|*
name|bucket_options_new
parameter_list|(
name|GimpToolInfo
modifier|*
name|tool_info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|bucket_options_reset
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_bucket_fill_tool_register (GimpToolRegisterCallback callback,gpointer data)
name|gimp_bucket_fill_tool_register
parameter_list|(
name|GimpToolRegisterCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
call|(
modifier|*
name|callback
call|)
argument_list|(
name|GIMP_TYPE_BUCKET_FILL_TOOL
argument_list|,
name|bucket_options_new
argument_list|,
name|TRUE
argument_list|,
literal|"gimp-bucket-fill-tool"
argument_list|,
name|_
argument_list|(
literal|"Bucket Fill"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Fill with a color or pattern"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"/Tools/Paint Tools/Bucket Fill"
argument_list|)
argument_list|,
literal|"<shift>B"
argument_list|,
name|NULL
argument_list|,
literal|"tools/bucket_fill.html"
argument_list|,
name|GIMP_STOCK_TOOL_BUCKET_FILL
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_bucket_fill_tool_get_type (void)
name|gimp_bucket_fill_tool_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|tool_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|tool_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|tool_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpBucketFillToolClass
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
name|gimp_bucket_fill_tool_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpBucketFillTool
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_bucket_fill_tool_init
block|,       }
decl_stmt|;
name|tool_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_TOOL
argument_list|,
literal|"GimpBucketFillTool"
argument_list|,
operator|&
name|tool_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|tool_type
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_bucket_fill_tool_class_init (GimpBucketFillToolClass * klass)
name|gimp_bucket_fill_tool_class_init
parameter_list|(
name|GimpBucketFillToolClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpToolClass
modifier|*
name|tool_class
decl_stmt|;
name|tool_class
operator|=
name|GIMP_TOOL_CLASS
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
name|tool_class
operator|->
name|button_press
operator|=
name|gimp_bucket_fill_tool_button_press
expr_stmt|;
name|tool_class
operator|->
name|button_release
operator|=
name|gimp_bucket_fill_tool_button_release
expr_stmt|;
name|tool_class
operator|->
name|modifier_key
operator|=
name|gimp_bucket_fill_tool_modifier_key
expr_stmt|;
name|tool_class
operator|->
name|cursor_update
operator|=
name|gimp_bucket_fill_tool_cursor_update
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_bucket_fill_tool_init (GimpBucketFillTool * bucket_fill_tool)
name|gimp_bucket_fill_tool_init
parameter_list|(
name|GimpBucketFillTool
modifier|*
name|bucket_fill_tool
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
decl_stmt|;
name|tool
operator|=
name|GIMP_TOOL
argument_list|(
name|bucket_fill_tool
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_scroll_lock
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_tool_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_BUCKET_FILL_TOOL_CURSOR
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_bucket_fill_tool_button_press (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_bucket_fill_tool_button_press
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|guint32
name|time
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|GimpBucketFillTool
modifier|*
name|bucket_tool
decl_stmt|;
name|BucketOptions
modifier|*
name|options
decl_stmt|;
name|bucket_tool
operator|=
name|GIMP_BUCKET_FILL_TOOL
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|options
operator|=
operator|(
name|BucketOptions
operator|*
operator|)
name|tool
operator|->
name|tool_info
operator|->
name|tool_options
expr_stmt|;
name|bucket_tool
operator|->
name|target_x
operator|=
name|coords
operator|->
name|x
expr_stmt|;
name|bucket_tool
operator|->
name|target_y
operator|=
name|coords
operator|->
name|y
expr_stmt|;
if|if
condition|(
operator|!
name|options
operator|->
name|sample_merged
condition|)
block|{
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
name|gimp_drawable_offsets
argument_list|(
name|gimp_image_active_drawable
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
name|bucket_tool
operator|->
name|target_x
operator|-=
name|off_x
expr_stmt|;
name|bucket_tool
operator|->
name|target_y
operator|-=
name|off_y
expr_stmt|;
block|}
name|tool
operator|->
name|gdisp
operator|=
name|gdisp
expr_stmt|;
name|gimp_tool_control_activate
argument_list|(
name|tool
operator|->
name|control
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_bucket_fill_tool_button_release (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_bucket_fill_tool_button_release
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|guint32
name|time
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|GimpBucketFillTool
modifier|*
name|bucket_tool
decl_stmt|;
name|BucketOptions
modifier|*
name|options
decl_stmt|;
name|bucket_tool
operator|=
name|GIMP_BUCKET_FILL_TOOL
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|options
operator|=
operator|(
name|BucketOptions
operator|*
operator|)
name|tool
operator|->
name|tool_info
operator|->
name|tool_options
expr_stmt|;
comment|/*  if the 3rd button isn't pressed, fill the selected region  */
if|if
condition|(
operator|!
operator|(
name|state
operator|&
name|GDK_BUTTON3_MASK
operator|)
condition|)
block|{
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|context
operator|=
name|gimp_get_current_context
argument_list|(
name|gdisp
operator|->
name|gimage
operator|->
name|gimp
argument_list|)
expr_stmt|;
name|gimp_drawable_bucket_fill
argument_list|(
name|gimp_image_active_drawable
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|,
name|options
operator|->
name|fill_mode
argument_list|,
name|gimp_context_get_paint_mode
argument_list|(
name|context
argument_list|)
argument_list|,
name|gimp_context_get_opacity
argument_list|(
name|context
argument_list|)
argument_list|,
name|options
operator|->
name|fill_transparent
argument_list|,
name|options
operator|->
name|threshold
argument_list|,
name|options
operator|->
name|sample_merged
argument_list|,
name|bucket_tool
operator|->
name|target_x
argument_list|,
name|bucket_tool
operator|->
name|target_y
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
block|}
name|gimp_tool_control_halt
argument_list|(
name|tool
operator|->
name|control
argument_list|)
expr_stmt|;
comment|/* sets paused_count to 0 -- is this ok? */
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_bucket_fill_tool_modifier_key (GimpTool * tool,GdkModifierType key,gboolean press,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_bucket_fill_tool_modifier_key
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkModifierType
name|key
parameter_list|,
name|gboolean
name|press
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|BucketOptions
modifier|*
name|options
decl_stmt|;
name|options
operator|=
operator|(
name|BucketOptions
operator|*
operator|)
name|tool
operator|->
name|tool_info
operator|->
name|tool_options
expr_stmt|;
if|if
condition|(
name|key
operator|==
name|GDK_CONTROL_MASK
condition|)
block|{
switch|switch
condition|(
name|options
operator|->
name|fill_mode
condition|)
block|{
case|case
name|GIMP_FG_BUCKET_FILL
case|:
name|gimp_radio_group_set_active
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|options
operator|->
name|fill_mode_w
argument_list|)
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|GIMP_BG_BUCKET_FILL
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_BG_BUCKET_FILL
case|:
name|gimp_radio_group_set_active
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|options
operator|->
name|fill_mode_w
argument_list|)
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|GIMP_FG_BUCKET_FILL
argument_list|)
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_bucket_fill_tool_cursor_update (GimpTool * tool,GimpCoords * coords,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_bucket_fill_tool_cursor_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|BucketOptions
modifier|*
name|options
decl_stmt|;
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
name|GimpCursorModifier
name|cmodifier
init|=
name|GIMP_CURSOR_MODIFIER_NONE
decl_stmt|;
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
name|options
operator|=
operator|(
name|BucketOptions
operator|*
operator|)
name|tool
operator|->
name|tool_info
operator|->
name|tool_options
expr_stmt|;
if|if
condition|(
operator|(
name|layer
operator|=
name|gimp_image_get_active_layer
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
operator|)
condition|)
block|{
name|gimp_drawable_offsets
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
if|if
condition|(
name|coords
operator|->
name|x
operator|>=
name|off_x
operator|&&
name|coords
operator|->
name|y
operator|>=
name|off_y
operator|&&
name|coords
operator|->
name|x
operator|<
operator|(
name|off_x
operator|+
name|gimp_drawable_width
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|)
operator|)
operator|&&
name|coords
operator|->
name|y
operator|<
operator|(
name|off_y
operator|+
name|gimp_drawable_height
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|)
operator|)
condition|)
block|{
comment|/*  One more test--is there a selected region? 	   *  if so, is cursor inside? 	   */
if|if
condition|(
name|gimp_image_mask_is_empty
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
operator|||
name|gimp_image_mask_value
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|coords
operator|->
name|x
argument_list|,
name|coords
operator|->
name|y
argument_list|)
condition|)
block|{
switch|switch
condition|(
name|options
operator|->
name|fill_mode
condition|)
block|{
case|case
name|GIMP_FG_BUCKET_FILL
case|:
name|cmodifier
operator|=
name|GIMP_CURSOR_MODIFIER_FOREGROUND
expr_stmt|;
break|break;
case|case
name|GIMP_BG_BUCKET_FILL
case|:
name|cmodifier
operator|=
name|GIMP_CURSOR_MODIFIER_BACKGROUND
expr_stmt|;
break|break;
case|case
name|GIMP_PATTERN_BUCKET_FILL
case|:
name|cmodifier
operator|=
name|GIMP_CURSOR_MODIFIER_PATTERN
expr_stmt|;
break|break;
block|}
block|}
block|}
block|}
name|gimp_tool_control_set_cursor_modifier
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|cmodifier
argument_list|)
expr_stmt|;
name|GIMP_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|cursor_update
argument_list|(
name|tool
argument_list|,
name|coords
argument_list|,
name|state
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GimpToolOptions
modifier|*
DECL|function|bucket_options_new (GimpToolInfo * tool_info)
name|bucket_options_new
parameter_list|(
name|GimpToolInfo
modifier|*
name|tool_info
parameter_list|)
block|{
name|BucketOptions
modifier|*
name|options
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox2
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|options
operator|=
name|g_new0
argument_list|(
name|BucketOptions
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gimp_paint_options_init
argument_list|(
operator|(
name|GimpPaintOptions
operator|*
operator|)
name|options
argument_list|)
expr_stmt|;
name|paint_options_init
argument_list|(
operator|(
name|GimpPaintOptions
operator|*
operator|)
name|options
argument_list|,
name|tool_info
argument_list|)
expr_stmt|;
operator|(
operator|(
name|GimpToolOptions
operator|*
operator|)
name|options
operator|)
operator|->
name|reset_func
operator|=
name|bucket_options_reset
expr_stmt|;
name|options
operator|->
name|fill_transparent
operator|=
name|options
operator|->
name|fill_transparent_d
operator|=
name|TRUE
expr_stmt|;
name|options
operator|->
name|sample_merged
operator|=
name|options
operator|->
name|sample_merged_d
operator|=
name|FALSE
expr_stmt|;
name|options
operator|->
name|threshold
operator|=
name|gimprc
operator|.
name|default_threshold
expr_stmt|;
name|options
operator|->
name|fill_mode
operator|=
name|options
operator|->
name|fill_mode_d
operator|=
name|GIMP_FG_BUCKET_FILL
expr_stmt|;
comment|/*  the main vbox  */
name|vbox
operator|=
operator|(
operator|(
name|GimpToolOptions
operator|*
operator|)
name|options
operator|)
operator|->
name|main_vbox
expr_stmt|;
comment|/*  fill type  */
name|frame
operator|=
name|gimp_enum_radio_frame_new
argument_list|(
name|GIMP_TYPE_BUCKET_FILL_MODE
argument_list|,
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Fill Type (<Ctrl>)"
argument_list|)
argument_list|)
argument_list|,
literal|2
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_radio_button_update
argument_list|)
argument_list|,
operator|&
name|options
operator|->
name|fill_mode
argument_list|,
operator|&
name|options
operator|->
name|fill_mode_w
argument_list|)
expr_stmt|;
name|gimp_radio_group_set_active
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|options
operator|->
name|fill_mode_w
argument_list|)
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|options
operator|->
name|fill_mode
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|frame
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
name|frame
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|_
argument_list|(
literal|"Finding Similar Colors"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|frame
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
name|frame
argument_list|)
expr_stmt|;
name|vbox2
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox2
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|vbox2
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox2
argument_list|)
expr_stmt|;
comment|/*  the fill transparent areas toggle  */
name|options
operator|->
name|fill_transparent_w
operator|=
name|gtk_check_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Fill Transparent Areas"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|options
operator|->
name|fill_transparent_w
argument_list|)
argument_list|,
name|options
operator|->
name|fill_transparent
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox2
argument_list|)
argument_list|,
name|options
operator|->
name|fill_transparent_w
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
name|options
operator|->
name|fill_transparent_w
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|options
operator|->
name|fill_transparent_w
argument_list|,
name|_
argument_list|(
literal|"Allow completely transparent regions "
literal|"to be filled"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|options
operator|->
name|fill_transparent_w
argument_list|)
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_toggle_button_update
argument_list|)
argument_list|,
operator|&
name|options
operator|->
name|fill_transparent
argument_list|)
expr_stmt|;
comment|/*  the sample merged toggle  */
name|options
operator|->
name|sample_merged_w
operator|=
name|gtk_check_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Sample Merged"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox2
argument_list|)
argument_list|,
name|options
operator|->
name|sample_merged_w
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
name|options
operator|->
name|sample_merged_w
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|options
operator|->
name|sample_merged_w
argument_list|,
name|_
argument_list|(
literal|"Base filled area on all visible layers"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|options
operator|->
name|sample_merged_w
argument_list|)
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_toggle_button_update
argument_list|)
argument_list|,
operator|&
name|options
operator|->
name|sample_merged
argument_list|)
expr_stmt|;
comment|/*  the threshold scale  */
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|1
argument_list|,
literal|3
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox2
argument_list|)
argument_list|,
name|table
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
name|table
argument_list|)
expr_stmt|;
name|options
operator|->
name|threshold_w
operator|=
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Threshold:"
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|,
literal|50
argument_list|,
name|gimprc
operator|.
name|default_threshold
argument_list|,
literal|0.0
argument_list|,
literal|255.0
argument_list|,
literal|1.0
argument_list|,
literal|16.0
argument_list|,
literal|1
argument_list|,
name|TRUE
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
name|_
argument_list|(
literal|"Maximum color difference"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|options
operator|->
name|threshold_w
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|options
operator|->
name|threshold
argument_list|)
expr_stmt|;
name|bucket_options_reset
argument_list|(
operator|(
name|GimpToolOptions
operator|*
operator|)
name|options
argument_list|)
expr_stmt|;
return|return
operator|(
name|GimpToolOptions
operator|*
operator|)
name|options
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|bucket_options_reset (GimpToolOptions * tool_options)
name|bucket_options_reset
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
block|{
name|BucketOptions
modifier|*
name|options
decl_stmt|;
name|options
operator|=
operator|(
name|BucketOptions
operator|*
operator|)
name|tool_options
expr_stmt|;
name|paint_options_reset
argument_list|(
name|tool_options
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|options
operator|->
name|fill_transparent_w
argument_list|)
argument_list|,
name|options
operator|->
name|fill_transparent_d
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|options
operator|->
name|sample_merged_w
argument_list|)
argument_list|,
name|options
operator|->
name|sample_merged_d
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|options
operator|->
name|threshold_w
argument_list|)
argument_list|,
name|gimprc
operator|.
name|default_threshold
argument_list|)
expr_stmt|;
name|gimp_radio_group_set_active
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|options
operator|->
name|fill_mode_w
argument_list|)
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|options
operator|->
name|fill_mode_d
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

