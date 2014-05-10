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

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_define
DECL|macro|STRICT
define|#
directive|define
name|STRICT
end_define

begin_include
include|#
directive|include
file|<windows.h>
end_include

begin_define
DECL|macro|LCMS_WIN_TYPES_ALREADY_DEFINED
define|#
directive|define
name|LCMS_WIN_TYPES_ALREADY_DEFINED
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<lcms2.h>
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
name|cmsHTRANSFORM
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
name|cmsHPROFILE
name|cdisplay_lcms_get_rgb_profile
parameter_list|(
name|CdisplayLcms
modifier|*
name|lcms
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|cmsHPROFILE
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
name|cmsHPROFILE
name|cdisplay_lcms_get_printer_profile
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
block|{
name|lcms
operator|->
name|transform
operator|=
name|NULL
expr_stmt|;
block|}
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
name|cmsDeleteTransform
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
name|void
DECL|function|cdisplay_lcms_profile_get_info (cmsHPROFILE profile,gchar ** label,gchar ** summary)
name|cdisplay_lcms_profile_get_info
parameter_list|(
name|cmsHPROFILE
name|profile
parameter_list|,
name|gchar
modifier|*
modifier|*
name|label
parameter_list|,
name|gchar
modifier|*
modifier|*
name|summary
parameter_list|)
block|{
if|if
condition|(
name|profile
condition|)
block|{
operator|*
name|label
operator|=
name|gimp_lcms_profile_get_label
argument_list|(
name|profile
argument_list|)
expr_stmt|;
operator|*
name|summary
operator|=
name|gimp_lcms_profile_get_summary
argument_list|(
name|profile
argument_list|)
expr_stmt|;
block|}
else|else
block|{
operator|*
name|label
operator|=
name|g_strdup
argument_list|(
name|_
argument_list|(
literal|"None"
argument_list|)
argument_list|)
expr_stmt|;
operator|*
name|summary
operator|=
name|NULL
expr_stmt|;
block|}
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
name|GeglBufferIterator
modifier|*
name|iter
decl_stmt|;
if|if
condition|(
operator|!
name|lcms
operator|->
name|transform
condition|)
return|return;
name|iter
operator|=
name|gegl_buffer_iterator_new
argument_list|(
name|buffer
argument_list|,
name|area
argument_list|,
literal|0
argument_list|,
name|babl_format
argument_list|(
literal|"R'G'B'A float"
argument_list|)
argument_list|,
name|GEGL_BUFFER_READWRITE
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
while|while
condition|(
name|gegl_buffer_iterator_next
argument_list|(
name|iter
argument_list|)
condition|)
block|{
name|gfloat
modifier|*
name|data
init|=
name|iter
operator|->
name|data
index|[
literal|0
index|]
decl_stmt|;
name|cmsDoTransform
argument_list|(
name|lcms
operator|->
name|transform
argument_list|,
name|data
argument_list|,
name|data
argument_list|,
name|iter
operator|->
name|length
argument_list|)
expr_stmt|;
block|}
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
name|GimpColorConfig
modifier|*
name|config
init|=
name|gimp_color_display_get_config
argument_list|(
name|display
argument_list|)
decl_stmt|;
name|cmsHPROFILE
name|src_profile
init|=
name|NULL
decl_stmt|;
name|cmsHPROFILE
name|dest_profile
init|=
name|NULL
decl_stmt|;
name|cmsHPROFILE
name|proof_profile
init|=
name|NULL
decl_stmt|;
name|cmsUInt16Number
name|alarmCodes
index|[
name|cmsMAXCHANNELS
index|]
init|=
block|{
literal|0
block|, }
decl_stmt|;
if|if
condition|(
name|lcms
operator|->
name|transform
condition|)
block|{
name|cmsDeleteTransform
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
if|if
condition|(
operator|!
name|config
condition|)
return|return;
switch|switch
condition|(
name|config
operator|->
name|mode
condition|)
block|{
case|case
name|GIMP_COLOR_MANAGEMENT_OFF
case|:
return|return;
case|case
name|GIMP_COLOR_MANAGEMENT_SOFTPROOF
case|:
name|proof_profile
operator|=
name|cdisplay_lcms_get_printer_profile
argument_list|(
name|lcms
argument_list|)
expr_stmt|;
comment|/*  fallthru  */
case|case
name|GIMP_COLOR_MANAGEMENT_DISPLAY
case|:
name|src_profile
operator|=
name|cdisplay_lcms_get_rgb_profile
argument_list|(
name|lcms
argument_list|)
expr_stmt|;
name|dest_profile
operator|=
name|cdisplay_lcms_get_display_profile
argument_list|(
name|lcms
argument_list|)
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|proof_profile
condition|)
block|{
name|cmsUInt32Number
name|softproof_flags
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|src_profile
condition|)
name|src_profile
operator|=
name|gimp_lcms_create_srgb_profile
argument_list|()
expr_stmt|;
if|if
condition|(
operator|!
name|dest_profile
condition|)
name|dest_profile
operator|=
name|gimp_lcms_create_srgb_profile
argument_list|()
expr_stmt|;
name|softproof_flags
operator||=
name|cmsFLAGS_SOFTPROOFING
expr_stmt|;
if|if
condition|(
name|config
operator|->
name|simulation_use_black_point_compensation
condition|)
block|{
name|softproof_flags
operator||=
name|cmsFLAGS_BLACKPOINTCOMPENSATION
expr_stmt|;
block|}
if|if
condition|(
name|config
operator|->
name|simulation_gamut_check
condition|)
block|{
name|guchar
name|r
decl_stmt|,
name|g
decl_stmt|,
name|b
decl_stmt|;
name|softproof_flags
operator||=
name|cmsFLAGS_GAMUTCHECK
expr_stmt|;
name|gimp_rgb_get_uchar
argument_list|(
operator|&
name|config
operator|->
name|out_of_gamut_color
argument_list|,
operator|&
name|r
argument_list|,
operator|&
name|g
argument_list|,
operator|&
name|b
argument_list|)
expr_stmt|;
name|alarmCodes
index|[
literal|0
index|]
operator|=
operator|(
name|cmsUInt16Number
operator|)
name|r
operator|*
literal|256
expr_stmt|;
name|alarmCodes
index|[
literal|1
index|]
operator|=
operator|(
name|cmsUInt16Number
operator|)
name|g
operator|*
literal|256
expr_stmt|;
name|alarmCodes
index|[
literal|2
index|]
operator|=
operator|(
name|cmsUInt16Number
operator|)
name|b
operator|*
literal|256
expr_stmt|;
name|cmsSetAlarmCodes
argument_list|(
name|alarmCodes
argument_list|)
expr_stmt|;
block|}
name|lcms
operator|->
name|transform
operator|=
name|cmsCreateProofingTransform
argument_list|(
name|src_profile
argument_list|,
name|TYPE_RGBA_FLT
argument_list|,
name|dest_profile
argument_list|,
name|TYPE_RGBA_FLT
argument_list|,
name|proof_profile
argument_list|,
name|config
operator|->
name|simulation_intent
argument_list|,
name|config
operator|->
name|display_intent
argument_list|,
name|softproof_flags
argument_list|)
expr_stmt|;
name|cmsCloseProfile
argument_list|(
name|proof_profile
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|src_profile
operator|||
name|dest_profile
condition|)
block|{
name|cmsUInt32Number
name|display_flags
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|src_profile
condition|)
name|src_profile
operator|=
name|gimp_lcms_create_srgb_profile
argument_list|()
expr_stmt|;
if|if
condition|(
operator|!
name|dest_profile
condition|)
name|dest_profile
operator|=
name|gimp_lcms_create_srgb_profile
argument_list|()
expr_stmt|;
if|if
condition|(
name|config
operator|->
name|display_use_black_point_compensation
condition|)
block|{
name|display_flags
operator||=
name|cmsFLAGS_BLACKPOINTCOMPENSATION
expr_stmt|;
block|}
name|lcms
operator|->
name|transform
operator|=
name|cmsCreateTransform
argument_list|(
name|src_profile
argument_list|,
name|TYPE_RGBA_FLT
argument_list|,
name|dest_profile
argument_list|,
name|TYPE_RGBA_FLT
argument_list|,
name|config
operator|->
name|display_intent
argument_list|,
name|display_flags
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|dest_profile
condition|)
name|cmsCloseProfile
argument_list|(
name|dest_profile
argument_list|)
expr_stmt|;
if|if
condition|(
name|src_profile
condition|)
name|cmsCloseProfile
argument_list|(
name|src_profile
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|cmsHPROFILE
DECL|function|cdisplay_lcms_get_rgb_profile (CdisplayLcms * lcms)
name|cdisplay_lcms_get_rgb_profile
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
name|cmsHPROFILE
name|profile
init|=
name|NULL
decl_stmt|;
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
name|managed
condition|)
block|{
name|gsize
name|len
decl_stmt|;
specifier|const
name|guint8
modifier|*
name|data
init|=
name|gimp_color_managed_get_icc_profile
argument_list|(
name|managed
argument_list|,
operator|&
name|len
argument_list|)
decl_stmt|;
if|if
condition|(
name|data
condition|)
name|profile
operator|=
name|cmsOpenProfileFromMem
argument_list|(
operator|(
name|gpointer
operator|)
name|data
argument_list|,
name|len
argument_list|)
expr_stmt|;
if|if
condition|(
name|profile
operator|&&
operator|!
name|gimp_lcms_profile_is_rgb
argument_list|(
name|profile
argument_list|)
condition|)
block|{
name|cmsCloseProfile
argument_list|(
name|profile
argument_list|)
expr_stmt|;
name|profile
operator|=
name|NULL
expr_stmt|;
block|}
block|}
if|if
condition|(
operator|!
name|profile
condition|)
block|{
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
if|if
condition|(
name|config
operator|->
name|rgb_profile
condition|)
name|profile
operator|=
name|cmsOpenProfileFromFile
argument_list|(
name|config
operator|->
name|rgb_profile
argument_list|,
literal|"r"
argument_list|)
expr_stmt|;
if|if
condition|(
name|profile
operator|&&
operator|!
name|gimp_lcms_profile_is_rgb
argument_list|(
name|profile
argument_list|)
condition|)
block|{
name|cmsCloseProfile
argument_list|(
name|profile
argument_list|)
expr_stmt|;
name|profile
operator|=
name|NULL
expr_stmt|;
block|}
block|}
return|return
name|profile
return|;
block|}
end_function

begin_function
specifier|static
name|GdkScreen
modifier|*
DECL|function|cdisplay_lcms_get_screen (CdisplayLcms * lcms,gint * monitor)
name|cdisplay_lcms_get_screen
parameter_list|(
name|CdisplayLcms
modifier|*
name|lcms
parameter_list|,
name|gint
modifier|*
name|monitor
parameter_list|)
block|{
name|GimpColorManaged
modifier|*
name|managed
decl_stmt|;
name|GdkScreen
modifier|*
name|screen
decl_stmt|;
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
name|screen
operator|=
name|gtk_widget_get_screen
argument_list|(
name|GTK_WIDGET
argument_list|(
name|managed
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|screen
operator|=
name|gdk_screen_get_default
argument_list|()
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GDK_IS_SCREEN
argument_list|(
name|screen
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_IS_WIDGET
argument_list|(
name|managed
argument_list|)
operator|&&
name|gtk_widget_get_window
argument_list|(
name|GTK_WIDGET
argument_list|(
name|managed
argument_list|)
argument_list|)
condition|)
block|{
name|GtkWidget
modifier|*
name|widget
init|=
name|GTK_WIDGET
argument_list|(
name|managed
argument_list|)
decl_stmt|;
operator|*
name|monitor
operator|=
name|gdk_screen_get_monitor_at_window
argument_list|(
name|screen
argument_list|,
name|gtk_widget_get_window
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
operator|*
name|monitor
operator|=
literal|0
expr_stmt|;
block|}
return|return
name|screen
return|;
block|}
end_function

begin_function
specifier|static
name|cmsHPROFILE
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
name|cmsHPROFILE
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
if|#
directive|if
name|defined
name|GDK_WINDOWING_X11
if|if
condition|(
name|config
operator|->
name|display_profile_from_gdk
condition|)
block|{
name|GdkScreen
modifier|*
name|screen
decl_stmt|;
name|GdkAtom
name|type
init|=
name|GDK_NONE
decl_stmt|;
name|gint
name|format
init|=
literal|0
decl_stmt|;
name|gint
name|nitems
init|=
literal|0
decl_stmt|;
name|gint
name|monitor
init|=
literal|0
decl_stmt|;
name|gchar
modifier|*
name|atom_name
decl_stmt|;
name|guchar
modifier|*
name|data
init|=
name|NULL
decl_stmt|;
name|screen
operator|=
name|cdisplay_lcms_get_screen
argument_list|(
name|lcms
argument_list|,
operator|&
name|monitor
argument_list|)
expr_stmt|;
if|if
condition|(
name|monitor
operator|>
literal|0
condition|)
name|atom_name
operator|=
name|g_strdup_printf
argument_list|(
literal|"_ICC_PROFILE_%d"
argument_list|,
name|monitor
argument_list|)
expr_stmt|;
else|else
name|atom_name
operator|=
name|g_strdup
argument_list|(
literal|"_ICC_PROFILE"
argument_list|)
expr_stmt|;
if|if
condition|(
name|gdk_property_get
argument_list|(
name|gdk_screen_get_root_window
argument_list|(
name|screen
argument_list|)
argument_list|,
name|gdk_atom_intern
argument_list|(
name|atom_name
argument_list|,
name|FALSE
argument_list|)
argument_list|,
name|GDK_NONE
argument_list|,
literal|0
argument_list|,
literal|64
operator|*
literal|1024
operator|*
literal|1024
argument_list|,
name|FALSE
argument_list|,
operator|&
name|type
argument_list|,
operator|&
name|format
argument_list|,
operator|&
name|nitems
argument_list|,
operator|&
name|data
argument_list|)
operator|&&
name|nitems
operator|>
literal|0
condition|)
block|{
name|profile
operator|=
name|cmsOpenProfileFromMem
argument_list|(
name|data
argument_list|,
name|nitems
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|data
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|atom_name
argument_list|)
expr_stmt|;
block|}
elif|#
directive|elif
name|defined
name|GDK_WINDOWING_QUARTZ
if|if
condition|(
name|config
operator|->
name|display_profile_from_gdk
condition|)
block|{
name|CMProfileRef
name|prof
init|=
name|NULL
decl_stmt|;
name|gint
name|monitor
init|=
literal|0
decl_stmt|;
name|cdisplay_lcms_get_screen
argument_list|(
name|lcms
argument_list|,
operator|&
name|monitor
argument_list|)
expr_stmt|;
name|CMGetProfileByAVID
argument_list|(
name|monitor
argument_list|,
operator|&
name|prof
argument_list|)
expr_stmt|;
if|if
condition|(
name|prof
condition|)
block|{
name|CFDataRef
name|data
decl_stmt|;
name|data
operator|=
name|CMProfileCopyICCData
argument_list|(
name|NULL
argument_list|,
name|prof
argument_list|)
expr_stmt|;
name|CMCloseProfile
argument_list|(
name|prof
argument_list|)
expr_stmt|;
if|if
condition|(
name|data
condition|)
block|{
name|UInt8
modifier|*
name|buffer
init|=
name|g_malloc
argument_list|(
name|CFDataGetLength
argument_list|(
name|data
argument_list|)
argument_list|)
decl_stmt|;
comment|/* We cannot use CFDataGetBytesPtr(), because that returns                * a const pointer where cmsOpenProfileFromMem wants a                * non-const pointer.                */
name|CFDataGetBytes
argument_list|(
name|data
argument_list|,
name|CFRangeMake
argument_list|(
literal|0
argument_list|,
name|CFDataGetLength
argument_list|(
name|data
argument_list|)
argument_list|)
argument_list|,
name|buffer
argument_list|)
expr_stmt|;
name|profile
operator|=
name|cmsOpenProfileFromMem
argument_list|(
name|buffer
argument_list|,
name|CFDataGetLength
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|CFRelease
argument_list|(
name|data
argument_list|)
expr_stmt|;
block|}
block|}
block|}
elif|#
directive|elif
name|defined
name|G_OS_WIN32
if|if
condition|(
name|config
operator|->
name|display_profile_from_gdk
condition|)
block|{
name|HDC
name|hdc
init|=
name|GetDC
argument_list|(
name|NULL
argument_list|)
decl_stmt|;
if|if
condition|(
name|hdc
condition|)
block|{
name|gchar
modifier|*
name|path
decl_stmt|;
name|gint32
name|len
init|=
literal|0
decl_stmt|;
name|GetICMProfile
argument_list|(
name|hdc
argument_list|,
operator|&
name|len
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|path
operator|=
name|g_new
argument_list|(
name|gchar
argument_list|,
name|len
argument_list|)
expr_stmt|;
if|if
condition|(
name|GetICMProfile
argument_list|(
name|hdc
argument_list|,
operator|&
name|len
argument_list|,
name|path
argument_list|)
condition|)
name|profile
operator|=
name|cmsOpenProfileFromFile
argument_list|(
name|path
argument_list|,
literal|"r"
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
name|ReleaseDC
argument_list|(
name|NULL
argument_list|,
name|hdc
argument_list|)
expr_stmt|;
block|}
block|}
endif|#
directive|endif
if|if
condition|(
operator|!
name|profile
operator|&&
name|config
operator|->
name|display_profile
condition|)
name|profile
operator|=
name|cmsOpenProfileFromFile
argument_list|(
name|config
operator|->
name|display_profile
argument_list|,
literal|"r"
argument_list|)
expr_stmt|;
return|return
name|profile
return|;
block|}
end_function

begin_function
specifier|static
name|cmsHPROFILE
DECL|function|cdisplay_lcms_get_printer_profile (CdisplayLcms * lcms)
name|cdisplay_lcms_get_printer_profile
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
if|if
condition|(
name|config
operator|->
name|printer_profile
condition|)
return|return
name|cmsOpenProfileFromFile
argument_list|(
name|config
operator|->
name|printer_profile
argument_list|,
literal|"r"
argument_list|)
return|;
return|return
name|NULL
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
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|cmsHPROFILE
name|profile
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|text
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|tooltip
init|=
name|NULL
decl_stmt|;
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
name|cdisplay_lcms_get_rgb_profile
argument_list|(
name|lcms
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
name|cdisplay_lcms_get_printer_profile
argument_list|(
name|lcms
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_return_if_reached
argument_list|()
expr_stmt|;
block|}
name|cdisplay_lcms_profile_get_info
argument_list|(
name|profile
argument_list|,
operator|&
name|text
argument_list|,
operator|&
name|tooltip
argument_list|)
expr_stmt|;
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
name|g_free
argument_list|(
name|text
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tooltip
argument_list|)
expr_stmt|;
if|if
condition|(
name|profile
condition|)
name|cmsCloseProfile
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

