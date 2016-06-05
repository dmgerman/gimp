begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
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

begin_ifdef
ifdef|#
directive|ifdef
name|GDK_WINDOWING_QUARTZ
end_ifdef

begin_include
include|#
directive|include
file|<Carbon/Carbon.h>
end_include

begin_include
include|#
directive|include
file|<ApplicationServices/ApplicationServices.h>
end_include

begin_include
include|#
directive|include
file|<CoreServices/CoreServices.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmodule/gimpmodule.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/libgimp-intl.h"
end_include

begin_define
DECL|macro|CDISPLAY_TYPE_LCMS
define|#
directive|define
name|CDISPLAY_TYPE_LCMS
value|(cdisplay_lcms_get_type ())
end_define

begin_define
DECL|macro|CDISPLAY_LCMS (obj)
define|#
directive|define
name|CDISPLAY_LCMS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), CDISPLAY_TYPE_LCMS, CdisplayLcms))
end_define

begin_define
DECL|macro|CDISPLAY_LCMS_CLASS (klass)
define|#
directive|define
name|CDISPLAY_LCMS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), CDISPLAY_TYPE_LCMS, CdisplayLcmsClass))
end_define

begin_define
DECL|macro|CDISPLAY_IS_LCMS (obj)
define|#
directive|define
name|CDISPLAY_IS_LCMS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CDISPLAY_TYPE_LCMS))
end_define

begin_define
DECL|macro|CDISPLAY_IS_LCMS_CLASS (klass)
define|#
directive|define
name|CDISPLAY_IS_LCMS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), CDISPLAY_TYPE_LCMS))
end_define

begin_typedef
DECL|typedef|CdisplayLcms
typedef|typedef
name|struct
name|_CdisplayLcms
name|CdisplayLcms
typedef|;
end_typedef

begin_typedef
DECL|typedef|CdisplayLcmsClass
typedef|typedef
name|struct
name|_CdisplayLcmsClass
name|CdisplayLcmsClass
typedef|;
end_typedef

begin_struct
DECL|struct|_CdisplayLcms
struct|struct
name|_CdisplayLcms
block|{
DECL|member|parent_instance
name|GimpColorDisplay
name|parent_instance
decl_stmt|;
DECL|member|transform
name|GimpColorTransform
modifier|*
name|transform
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_CdisplayLcmsClass
struct|struct
name|_CdisplayLcmsClass
block|{
DECL|member|parent_instance
name|GimpColorDisplayClass
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|GType
name|cdisplay_lcms_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|cdisplay_lcms_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GtkWidget
modifier|*
name|cdisplay_lcms_configure
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|cdisplay_lcms_convert_buffer
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|,
name|GeglBuffer
modifier|*
name|buffer
parameter_list|,
name|GeglRectangle
modifier|*
name|area
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|cdisplay_lcms_changed
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpColorProfile
modifier|*
name|cdisplay_lcms_get_display_profile
parameter_list|(
name|CdisplayLcms
modifier|*
name|lcms
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|cdisplay_lcms_attach_labelled
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
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|cdisplay_lcms_update_profile_label
parameter_list|(
name|CdisplayLcms
modifier|*
name|lcms
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|cdisplay_lcms_notify_profile
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|CdisplayLcms
modifier|*
name|lcms
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|cdisplay_lcms_info
specifier|static
specifier|const
name|GimpModuleInfo
name|cdisplay_lcms_info
init|=
block|{
name|GIMP_MODULE_ABI_VERSION
block|,
name|N_
argument_list|(
literal|"Color management display filter using ICC color profiles"
argument_list|)
block|,
literal|"Sven Neumann"
block|,
literal|"v0.3"
block|,
literal|"(c) 2005 - 2007, released under the GPL"
block|,
literal|"2005 - 2007"
block|}
decl_stmt|;
end_decl_stmt

begin_macro
DECL|function|G_DEFINE_DYNAMIC_TYPE (CdisplayLcms,cdisplay_lcms,GIMP_TYPE_COLOR_DISPLAY)
name|G_DEFINE_DYNAMIC_TYPE
argument_list|(
argument|CdisplayLcms
argument_list|,
argument|cdisplay_lcms
argument_list|,
argument|GIMP_TYPE_COLOR_DISPLAY
argument_list|)
end_macro

begin_function
name|G_MODULE_EXPORT
specifier|const
name|GimpModuleInfo
modifier|*
name|gimp_module_query
parameter_list|(
name|GTypeModule
modifier|*
name|module
parameter_list|)
block|{
return|return
operator|&
name|cdisplay_lcms_info
return|;
block|}
end_function

begin_function
name|G_MODULE_EXPORT
name|gboolean
DECL|function|gimp_module_register (GTypeModule * module)
name|gimp_module_register
parameter_list|(
name|GTypeModule
modifier|*
name|module
parameter_list|)
block|{
name|cdisplay_lcms_register_type
argument_list|(
name|module
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|cdisplay_lcms_class_init (CdisplayLcmsClass * klass)
name|cdisplay_lcms_class_init
parameter_list|(
name|CdisplayLcmsClass
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
name|GimpColorDisplayClass
modifier|*
name|display_class
init|=
name|GIMP_COLOR_DISPLAY_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|cdisplay_lcms_finalize
expr_stmt|;
name|display_class
operator|->
name|name
operator|=
name|_
argument_list|(
literal|"Color Management"
argument_list|)
expr_stmt|;
name|display_class
operator|->
name|help_id
operator|=
literal|"gimp-colordisplay-lcms"
expr_stmt|;
name|display_class
operator|->
name|icon_name
operator|=
name|GIMP_STOCK_DISPLAY_FILTER_LCMS
expr_stmt|;
name|display_class
operator|->
name|configure
operator|=
name|cdisplay_lcms_configure
expr_stmt|;
name|display_class
operator|->
name|convert_buffer
operator|=
name|cdisplay_lcms_convert_buffer
expr_stmt|;
name|display_class
operator|->
name|changed
operator|=
name|cdisplay_lcms_changed
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|cdisplay_lcms_class_finalize (CdisplayLcmsClass * klass)
name|cdisplay_lcms_class_finalize
parameter_list|(
name|CdisplayLcmsClass
modifier|*
name|klass
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|cdisplay_lcms_init (CdisplayLcms * lcms)
name|cdisplay_lcms_init
parameter_list|(
name|CdisplayLcms
modifier|*
name|lcms
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|cdisplay_lcms_finalize (GObject * object)
name|cdisplay_lcms_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|CdisplayLcms
modifier|*
name|lcms
init|=
name|CDISPLAY_LCMS
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|lcms
operator|->
name|transform
condition|)
block|{
name|g_object_unref
argument_list|(
name|lcms
operator|->
name|transform
argument_list|)
expr_stmt|;
name|lcms
operator|->
name|transform
operator|=
name|NULL
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|cdisplay_lcms_parent_class
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
name|GtkWidget
modifier|*
DECL|function|cdisplay_lcms_configure (GimpColorDisplay * display)
name|cdisplay_lcms_configure
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
block|{
name|CdisplayLcms
modifier|*
name|lcms
init|=
name|CDISPLAY_LCMS
argument_list|(
name|display
argument_list|)
decl_stmt|;
name|GObject
modifier|*
name|config
init|=
name|G_OBJECT
argument_list|(
name|gimp_color_display_get_config
argument_list|(
name|display
argument_list|)
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|hint
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|gint
name|row
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|config
condition|)
return|return
name|NULL
return|;
name|vbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_VERTICAL
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|hint
operator|=
name|gimp_hint_box_new
argument_list|(
name|_
argument_list|(
literal|"This filter takes its configuration "
literal|"from the Color Management section "
literal|"in the Preferences dialog."
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
name|hint
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
name|hint
argument_list|)
expr_stmt|;
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|5
argument_list|,
literal|2
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
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
name|cdisplay_lcms_attach_labelled
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|row
operator|++
argument_list|,
name|_
argument_list|(
literal|"Mode of operation:"
argument_list|)
argument_list|,
name|gimp_prop_enum_label_new
argument_list|(
name|config
argument_list|,
literal|"mode"
argument_list|)
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gtk_label_set_ellipsize
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|PANGO_ELLIPSIZE_END
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|lcms
argument_list|)
argument_list|,
literal|"rgb-profile"
argument_list|,
name|label
argument_list|)
expr_stmt|;
name|cdisplay_lcms_attach_labelled
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|row
operator|++
argument_list|,
name|_
argument_list|(
literal|"Image profile:"
argument_list|)
argument_list|,
name|label
argument_list|)
expr_stmt|;
name|cdisplay_lcms_update_profile_label
argument_list|(
name|lcms
argument_list|,
literal|"rgb-profile"
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gtk_label_set_ellipsize
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|PANGO_ELLIPSIZE_END
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|lcms
argument_list|)
argument_list|,
literal|"display-profile"
argument_list|,
name|label
argument_list|)
expr_stmt|;
name|cdisplay_lcms_attach_labelled
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|row
operator|++
argument_list|,
name|_
argument_list|(
literal|"Monitor profile:"
argument_list|)
argument_list|,
name|label
argument_list|)
expr_stmt|;
name|cdisplay_lcms_update_profile_label
argument_list|(
name|lcms
argument_list|,
literal|"display-profile"
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gtk_label_set_ellipsize
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|PANGO_ELLIPSIZE_END
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|lcms
argument_list|)
argument_list|,
literal|"printer-profile"
argument_list|,
name|label
argument_list|)
expr_stmt|;
name|cdisplay_lcms_attach_labelled
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|row
operator|++
argument_list|,
name|_
argument_list|(
literal|"Print simulation profile:"
argument_list|)
argument_list|,
name|label
argument_list|)
expr_stmt|;
name|cdisplay_lcms_update_profile_label
argument_list|(
name|lcms
argument_list|,
literal|"printer-profile"
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|config
argument_list|,
literal|"notify"
argument_list|,
name|G_CALLBACK
argument_list|(
name|cdisplay_lcms_notify_profile
argument_list|)
argument_list|,
name|lcms
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|vbox
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|cdisplay_lcms_convert_buffer (GimpColorDisplay * display,GeglBuffer * buffer,GeglRectangle * area)
name|cdisplay_lcms_convert_buffer
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|,
name|GeglBuffer
modifier|*
name|buffer
parameter_list|,
name|GeglRectangle
modifier|*
name|area
parameter_list|)
block|{
name|CdisplayLcms
modifier|*
name|lcms
init|=
name|CDISPLAY_LCMS
argument_list|(
name|display
argument_list|)
decl_stmt|;
if|if
condition|(
name|lcms
operator|->
name|transform
condition|)
name|gimp_color_transform_process_buffer
argument_list|(
name|lcms
operator|->
name|transform
argument_list|,
name|buffer
argument_list|,
name|area
argument_list|,
name|buffer
argument_list|,
name|area
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|cdisplay_lcms_changed (GimpColorDisplay * display)
name|cdisplay_lcms_changed
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
block|{
name|CdisplayLcms
modifier|*
name|lcms
init|=
name|CDISPLAY_LCMS
argument_list|(
name|display
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|widget
init|=
name|NULL
decl_stmt|;
name|GimpColorConfig
modifier|*
name|config
decl_stmt|;
name|GimpColorManaged
modifier|*
name|managed
decl_stmt|;
name|GimpColorProfile
modifier|*
name|src_profile
decl_stmt|;
if|if
condition|(
name|lcms
operator|->
name|transform
condition|)
block|{
name|g_object_unref
argument_list|(
name|lcms
operator|->
name|transform
argument_list|)
expr_stmt|;
name|lcms
operator|->
name|transform
operator|=
name|NULL
expr_stmt|;
block|}
name|config
operator|=
name|gimp_color_display_get_config
argument_list|(
name|display
argument_list|)
expr_stmt|;
name|managed
operator|=
name|gimp_color_display_get_managed
argument_list|(
name|display
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|config
operator|||
operator|!
name|managed
condition|)
return|return;
if|if
condition|(
name|GTK_IS_WIDGET
argument_list|(
name|managed
argument_list|)
condition|)
name|widget
operator|=
name|gtk_widget_get_toplevel
argument_list|(
name|GTK_WIDGET
argument_list|(
name|managed
argument_list|)
argument_list|)
expr_stmt|;
name|src_profile
operator|=
name|gimp_color_managed_get_color_profile
argument_list|(
name|managed
argument_list|)
expr_stmt|;
name|lcms
operator|->
name|transform
operator|=
name|gimp_widget_get_color_transform
argument_list|(
name|widget
argument_list|,
name|config
argument_list|,
name|src_profile
argument_list|,
name|babl_format
argument_list|(
literal|"R'G'B'A float"
argument_list|)
argument_list|,
name|babl_format
argument_list|(
literal|"R'G'B'A float"
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GimpColorProfile
modifier|*
DECL|function|cdisplay_lcms_get_display_profile (CdisplayLcms * lcms)
name|cdisplay_lcms_get_display_profile
parameter_list|(
name|CdisplayLcms
modifier|*
name|lcms
parameter_list|)
block|{
name|GimpColorConfig
modifier|*
name|config
decl_stmt|;
name|GimpColorManaged
modifier|*
name|managed
decl_stmt|;
name|GtkWidget
modifier|*
name|widget
init|=
name|NULL
decl_stmt|;
name|GimpColorProfile
modifier|*
name|profile
init|=
name|NULL
decl_stmt|;
name|config
operator|=
name|gimp_color_display_get_config
argument_list|(
name|GIMP_COLOR_DISPLAY
argument_list|(
name|lcms
argument_list|)
argument_list|)
expr_stmt|;
name|managed
operator|=
name|gimp_color_display_get_managed
argument_list|(
name|GIMP_COLOR_DISPLAY
argument_list|(
name|lcms
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_IS_WIDGET
argument_list|(
name|managed
argument_list|)
condition|)
name|widget
operator|=
name|gtk_widget_get_toplevel
argument_list|(
name|GTK_WIDGET
argument_list|(
name|managed
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|config
operator|->
name|display_profile_from_gdk
condition|)
name|profile
operator|=
name|gimp_widget_get_color_profile
argument_list|(
name|widget
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|profile
condition|)
name|profile
operator|=
name|gimp_color_config_get_display_color_profile
argument_list|(
name|config
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|profile
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|cdisplay_lcms_attach_labelled (GtkTable * table,gint row,const gchar * text,GtkWidget * widget)
name|cdisplay_lcms_attach_labelled
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
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|label
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
name|label
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
name|label
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
name|label
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_IS_LABEL
argument_list|(
name|widget
argument_list|)
condition|)
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|table
argument_list|,
name|widget
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
operator||
name|GTK_EXPAND
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
name|widget
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|cdisplay_lcms_update_profile_label (CdisplayLcms * lcms,const gchar * name)
name|cdisplay_lcms_update_profile_label
parameter_list|(
name|CdisplayLcms
modifier|*
name|lcms
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|GimpColorConfig
modifier|*
name|config
decl_stmt|;
name|GimpColorManaged
modifier|*
name|managed
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GimpColorProfile
modifier|*
name|profile
init|=
name|NULL
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|text
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|tooltip
decl_stmt|;
name|config
operator|=
name|gimp_color_display_get_config
argument_list|(
name|GIMP_COLOR_DISPLAY
argument_list|(
name|lcms
argument_list|)
argument_list|)
expr_stmt|;
name|managed
operator|=
name|gimp_color_display_get_managed
argument_list|(
name|GIMP_COLOR_DISPLAY
argument_list|(
name|lcms
argument_list|)
argument_list|)
expr_stmt|;
name|label
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|lcms
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|label
condition|)
return|return;
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"rgb-profile"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|profile
operator|=
name|gimp_color_managed_get_color_profile
argument_list|(
name|managed
argument_list|)
expr_stmt|;
if|if
condition|(
name|profile
condition|)
name|g_object_ref
argument_list|(
name|profile
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|g_str_has_prefix
argument_list|(
name|name
argument_list|,
literal|"display-profile"
argument_list|)
condition|)
block|{
name|profile
operator|=
name|cdisplay_lcms_get_display_profile
argument_list|(
name|lcms
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"printer-profile"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|profile
operator|=
name|gimp_color_config_get_simulation_color_profile
argument_list|(
name|config
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_return_if_reached
argument_list|()
expr_stmt|;
block|}
if|if
condition|(
name|profile
condition|)
block|{
name|text
operator|=
name|gimp_color_profile_get_label
argument_list|(
name|profile
argument_list|)
expr_stmt|;
name|tooltip
operator|=
name|gimp_color_profile_get_summary
argument_list|(
name|profile
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|text
operator|=
name|_
argument_list|(
literal|"None"
argument_list|)
expr_stmt|;
name|tooltip
operator|=
name|NULL
expr_stmt|;
block|}
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|text
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|label
argument_list|,
name|tooltip
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|profile
condition|)
name|g_object_unref
argument_list|(
name|profile
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|cdisplay_lcms_notify_profile (GObject * config,GParamSpec * pspec,CdisplayLcms * lcms)
name|cdisplay_lcms_notify_profile
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|CdisplayLcms
modifier|*
name|lcms
parameter_list|)
block|{
name|cdisplay_lcms_update_profile_label
argument_list|(
name|lcms
argument_list|,
name|pspec
operator|->
name|name
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

