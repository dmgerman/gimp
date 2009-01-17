begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1999 Manish Singh<yosh@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
DECL|macro|DEFAULT_CONTRAST
define|#
directive|define
name|DEFAULT_CONTRAST
value|1.0
end_define

begin_define
DECL|macro|CDISPLAY_TYPE_CONTRAST
define|#
directive|define
name|CDISPLAY_TYPE_CONTRAST
value|(cdisplay_contrast_get_type ())
end_define

begin_define
DECL|macro|CDISPLAY_CONTRAST (obj)
define|#
directive|define
name|CDISPLAY_CONTRAST
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), CDISPLAY_TYPE_CONTRAST, CdisplayContrast))
end_define

begin_define
DECL|macro|CDISPLAY_CONTRAST_CLASS (klass)
define|#
directive|define
name|CDISPLAY_CONTRAST_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), CDISPLAY_TYPE_CONTRAST, CdisplayContrastClass))
end_define

begin_define
DECL|macro|CDISPLAY_IS_CONTRAST (obj)
define|#
directive|define
name|CDISPLAY_IS_CONTRAST
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CDISPLAY_TYPE_CONTRAST))
end_define

begin_define
DECL|macro|CDISPLAY_IS_CONTRAST_CLASS (klass)
define|#
directive|define
name|CDISPLAY_IS_CONTRAST_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), CDISPLAY_TYPE_CONTRAST))
end_define

begin_typedef
DECL|typedef|CdisplayContrast
typedef|typedef
name|struct
name|_CdisplayContrast
name|CdisplayContrast
typedef|;
end_typedef

begin_typedef
DECL|typedef|CdisplayContrastClass
typedef|typedef
name|struct
name|_CdisplayContrastClass
name|CdisplayContrastClass
typedef|;
end_typedef

begin_struct
DECL|struct|_CdisplayContrast
struct|struct
name|_CdisplayContrast
block|{
DECL|member|parent_instance
name|GimpColorDisplay
name|parent_instance
decl_stmt|;
DECL|member|contrast
name|gdouble
name|contrast
decl_stmt|;
DECL|member|lookup
name|guchar
name|lookup
index|[
literal|256
index|]
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_CdisplayContrastClass
struct|struct
name|_CdisplayContrastClass
block|{
DECL|member|parent_instance
name|GimpColorDisplayClass
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_enum
enum|enum
DECL|enum|__anon2b888db70103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_CONTRAST
name|PROP_CONTRAST
block|}
enum|;
end_enum

begin_function_decl
name|GType
name|cdisplay_contrast_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|cdisplay_contrast_set_property
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
name|cdisplay_contrast_get_property
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
name|void
name|cdisplay_contrast_convert
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|,
name|guchar
modifier|*
name|buf
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|,
name|gint
name|bpp
parameter_list|,
name|gint
name|bpl
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GtkWidget
modifier|*
name|cdisplay_contrast_configure
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
name|cdisplay_contrast_set_contrast
parameter_list|(
name|CdisplayContrast
modifier|*
name|contrast
parameter_list|,
name|gdouble
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|cdisplay_contrast_info
specifier|static
specifier|const
name|GimpModuleInfo
name|cdisplay_contrast_info
init|=
block|{
name|GIMP_MODULE_ABI_VERSION
block|,
name|N_
argument_list|(
literal|"High Contrast color display filter"
argument_list|)
block|,
literal|"Jay Cox<jaycox@gimp.org>"
block|,
literal|"v0.2"
block|,
literal|"(c) 2000, released under the GPL"
block|,
literal|"October 14, 2000"
block|}
decl_stmt|;
end_decl_stmt

begin_macro
DECL|function|G_DEFINE_DYNAMIC_TYPE (CdisplayContrast,cdisplay_contrast,GIMP_TYPE_COLOR_DISPLAY)
name|G_DEFINE_DYNAMIC_TYPE
argument_list|(
argument|CdisplayContrast
argument_list|,
argument|cdisplay_contrast
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
name|cdisplay_contrast_info
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
name|cdisplay_contrast_register_type
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
DECL|function|cdisplay_contrast_class_init (CdisplayContrastClass * klass)
name|cdisplay_contrast_class_init
parameter_list|(
name|CdisplayContrastClass
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
name|get_property
operator|=
name|cdisplay_contrast_get_property
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|cdisplay_contrast_set_property
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_CONTRAST
argument_list|,
literal|"contrast"
argument_list|,
name|NULL
argument_list|,
literal|0.01
argument_list|,
literal|10.0
argument_list|,
name|DEFAULT_CONTRAST
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|display_class
operator|->
name|name
operator|=
name|_
argument_list|(
literal|"Contrast"
argument_list|)
expr_stmt|;
name|display_class
operator|->
name|help_id
operator|=
literal|"gimp-colordisplay-contrast"
expr_stmt|;
name|display_class
operator|->
name|stock_id
operator|=
name|GIMP_STOCK_DISPLAY_FILTER_CONTRAST
expr_stmt|;
name|display_class
operator|->
name|convert
operator|=
name|cdisplay_contrast_convert
expr_stmt|;
name|display_class
operator|->
name|configure
operator|=
name|cdisplay_contrast_configure
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|cdisplay_contrast_class_finalize (CdisplayContrastClass * klass)
name|cdisplay_contrast_class_finalize
parameter_list|(
name|CdisplayContrastClass
modifier|*
name|klass
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|cdisplay_contrast_init (CdisplayContrast * contrast)
name|cdisplay_contrast_init
parameter_list|(
name|CdisplayContrast
modifier|*
name|contrast
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|cdisplay_contrast_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|cdisplay_contrast_get_property
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
name|CdisplayContrast
modifier|*
name|contrast
init|=
name|CDISPLAY_CONTRAST
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
name|PROP_CONTRAST
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|contrast
operator|->
name|contrast
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
DECL|function|cdisplay_contrast_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|cdisplay_contrast_set_property
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
name|CdisplayContrast
modifier|*
name|contrast
init|=
name|CDISPLAY_CONTRAST
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
name|PROP_CONTRAST
case|:
name|cdisplay_contrast_set_contrast
argument_list|(
name|contrast
argument_list|,
name|g_value_get_double
argument_list|(
name|value
argument_list|)
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
DECL|function|cdisplay_contrast_convert (GimpColorDisplay * display,guchar * buf,gint width,gint height,gint bpp,gint bpl)
name|cdisplay_contrast_convert
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
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
name|CdisplayContrast
modifier|*
name|contrast
init|=
name|CDISPLAY_CONTRAST
argument_list|(
name|display
argument_list|)
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|j
init|=
name|height
decl_stmt|;
comment|/* You will not be using the entire buffer most of the time.    * Hence, the simplistic code for this is as follows:    *    * for (j = 0; j< height; j++)    *   {    *     for (i = 0; i< width * bpp; i++)    *       buf[i] = lookup[buf[i]];    *     buf += bpl;    *   }    */
name|width
operator|*=
name|bpp
expr_stmt|;
name|bpl
operator|-=
name|width
expr_stmt|;
while|while
condition|(
name|j
operator|--
condition|)
block|{
name|i
operator|=
name|width
expr_stmt|;
while|while
condition|(
name|i
operator|--
condition|)
block|{
operator|*
name|buf
operator|=
name|contrast
operator|->
name|lookup
index|[
operator|*
name|buf
index|]
expr_stmt|;
name|buf
operator|++
expr_stmt|;
block|}
name|buf
operator|+=
name|bpl
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|cdisplay_contrast_configure (GimpColorDisplay * display)
name|cdisplay_contrast_configure
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
block|{
name|CdisplayContrast
modifier|*
name|contrast
init|=
name|CDISPLAY_CONTRAST
argument_list|(
name|display
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|spinbutton
decl_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"Contrast c_ycles:"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|label
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
name|label
argument_list|)
expr_stmt|;
name|spinbutton
operator|=
name|gimp_prop_spin_button_new
argument_list|(
name|G_OBJECT
argument_list|(
name|contrast
argument_list|)
argument_list|,
literal|"contrast"
argument_list|,
literal|0.1
argument_list|,
literal|1.0
argument_list|,
literal|3
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|spinbutton
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
name|spinbutton
argument_list|)
expr_stmt|;
name|gtk_label_set_mnemonic_widget
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|spinbutton
argument_list|)
expr_stmt|;
return|return
name|hbox
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|cdisplay_contrast_set_contrast (CdisplayContrast * contrast,gdouble value)
name|cdisplay_contrast_set_contrast
parameter_list|(
name|CdisplayContrast
modifier|*
name|contrast
parameter_list|,
name|gdouble
name|value
parameter_list|)
block|{
if|if
condition|(
name|value
operator|<=
literal|0.0
condition|)
name|value
operator|=
literal|1.0
expr_stmt|;
if|if
condition|(
name|value
operator|!=
name|contrast
operator|->
name|contrast
condition|)
block|{
name|gint
name|i
decl_stmt|;
name|contrast
operator|->
name|contrast
operator|=
name|value
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|256
condition|;
name|i
operator|++
control|)
block|{
name|contrast
operator|->
name|lookup
index|[
name|i
index|]
operator|=
call|(
name|guchar
call|)
argument_list|(
name|gint
argument_list|)
argument_list|(
literal|255
operator|*
literal|.5
operator|*
operator|(
literal|1
operator|+
name|sin
argument_list|(
name|value
operator|*
literal|2
operator|*
name|G_PI
operator|*
name|i
operator|/
literal|255.0
argument_list|)
operator|)
argument_list|)
expr_stmt|;
block|}
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|contrast
argument_list|)
argument_list|,
literal|"contrast"
argument_list|)
expr_stmt|;
name|gimp_color_display_changed
argument_list|(
name|GIMP_COLOR_DISPLAY
argument_list|(
name|contrast
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

