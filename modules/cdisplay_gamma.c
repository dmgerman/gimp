begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1999 Manish Singh<yosh@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
DECL|macro|DEFAULT_GAMMA
define|#
directive|define
name|DEFAULT_GAMMA
value|1.0
end_define

begin_define
DECL|macro|CDISPLAY_TYPE_GAMMA
define|#
directive|define
name|CDISPLAY_TYPE_GAMMA
value|(cdisplay_gamma_type)
end_define

begin_define
DECL|macro|CDISPLAY_GAMMA (obj)
define|#
directive|define
name|CDISPLAY_GAMMA
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), CDISPLAY_TYPE_GAMMA, CdisplayGamma))
end_define

begin_define
DECL|macro|CDISPLAY_GAMMA_CLASS (klass)
define|#
directive|define
name|CDISPLAY_GAMMA_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), CDISPLAY_TYPE_GAMMA, CdisplayGammaClass))
end_define

begin_define
DECL|macro|CDISPLAY_IS_GAMMA (obj)
define|#
directive|define
name|CDISPLAY_IS_GAMMA
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CDISPLAY_TYPE_GAMMA))
end_define

begin_define
DECL|macro|CDISPLAY_IS_GAMMA_CLASS (klass)
define|#
directive|define
name|CDISPLAY_IS_GAMMA_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), CDISPLAY_TYPE_GAMMA))
end_define

begin_typedef
DECL|typedef|CdisplayGamma
typedef|typedef
name|struct
name|_CdisplayGamma
name|CdisplayGamma
typedef|;
end_typedef

begin_typedef
DECL|typedef|CdisplayGammaClass
typedef|typedef
name|struct
name|_CdisplayGammaClass
name|CdisplayGammaClass
typedef|;
end_typedef

begin_struct
DECL|struct|_CdisplayGamma
struct|struct
name|_CdisplayGamma
block|{
DECL|member|parent_instance
name|GimpColorDisplay
name|parent_instance
decl_stmt|;
DECL|member|gamma
name|gdouble
name|gamma
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
DECL|struct|_CdisplayGammaClass
struct|struct
name|_CdisplayGammaClass
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
DECL|enum|__anon29bd8fdb0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_GAMMA
name|PROP_GAMMA
block|}
enum|;
end_enum

begin_function_decl
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
function_decl|;
end_function_decl

begin_function_decl
name|G_MODULE_EXPORT
name|gboolean
name|gimp_module_register
parameter_list|(
name|GTypeModule
modifier|*
name|module
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GType
name|cdisplay_gamma_get_type
parameter_list|(
name|GTypeModule
modifier|*
name|module
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|cdisplay_gamma_class_init
parameter_list|(
name|CdisplayGammaClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|cdisplay_gamma_set_property
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
name|cdisplay_gamma_get_property
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
name|cdisplay_gamma_convert
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
name|cdisplay_gamma_configure
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
name|cdisplay_gamma_set_gamma
parameter_list|(
name|CdisplayGamma
modifier|*
name|gamma
parameter_list|,
name|gdouble
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|cdisplay_gamma_info
specifier|static
specifier|const
name|GimpModuleInfo
name|cdisplay_gamma_info
init|=
block|{
name|GIMP_MODULE_ABI_VERSION
block|,
name|N_
argument_list|(
literal|"Gamma color display filter"
argument_list|)
block|,
literal|"Manish Singh<yosh@gimp.org>"
block|,
literal|"v0.2"
block|,
literal|"(c) 1999, released under the GPL"
block|,
literal|"October 14, 2000"
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|cdisplay_gamma_type
specifier|static
name|GType
name|cdisplay_gamma_type
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpColorDisplayClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|G_MODULE_EXPORT
specifier|const
name|GimpModuleInfo
modifier|*
DECL|function|gimp_module_query (GTypeModule * module)
name|gimp_module_query
parameter_list|(
name|GTypeModule
modifier|*
name|module
parameter_list|)
block|{
return|return
operator|&
name|cdisplay_gamma_info
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
name|cdisplay_gamma_get_type
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
name|GType
DECL|function|cdisplay_gamma_get_type (GTypeModule * module)
name|cdisplay_gamma_get_type
parameter_list|(
name|GTypeModule
modifier|*
name|module
parameter_list|)
block|{
if|if
condition|(
operator|!
name|cdisplay_gamma_type
condition|)
block|{
specifier|const
name|GTypeInfo
name|display_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|CdisplayGammaClass
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
name|cdisplay_gamma_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|CdisplayGamma
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
name|NULL
comment|/* instance_init  */
block|}
decl_stmt|;
name|cdisplay_gamma_type
operator|=
name|g_type_module_register_type
argument_list|(
name|module
argument_list|,
name|GIMP_TYPE_COLOR_DISPLAY
argument_list|,
literal|"CdisplayGamma"
argument_list|,
operator|&
name|display_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|cdisplay_gamma_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|cdisplay_gamma_class_init (CdisplayGammaClass * klass)
name|cdisplay_gamma_class_init
parameter_list|(
name|CdisplayGammaClass
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
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|cdisplay_gamma_get_property
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|cdisplay_gamma_set_property
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_GAMMA
argument_list|,
literal|"gamma"
argument_list|,
name|NULL
argument_list|,
literal|0.01
argument_list|,
literal|10.0
argument_list|,
name|DEFAULT_GAMMA
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
literal|"Gamma"
argument_list|)
expr_stmt|;
name|display_class
operator|->
name|help_id
operator|=
literal|"gimp-colordisplay-gamma"
expr_stmt|;
name|display_class
operator|->
name|stock_id
operator|=
name|GIMP_STOCK_DISPLAY_FILTER_GAMMA
expr_stmt|;
name|display_class
operator|->
name|convert
operator|=
name|cdisplay_gamma_convert
expr_stmt|;
name|display_class
operator|->
name|configure
operator|=
name|cdisplay_gamma_configure
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|cdisplay_gamma_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|cdisplay_gamma_get_property
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
name|CdisplayGamma
modifier|*
name|gamma
init|=
name|CDISPLAY_GAMMA
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
name|PROP_GAMMA
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|gamma
operator|->
name|gamma
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
DECL|function|cdisplay_gamma_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|cdisplay_gamma_set_property
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
name|CdisplayGamma
modifier|*
name|gamma
init|=
name|CDISPLAY_GAMMA
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
name|PROP_GAMMA
case|:
name|cdisplay_gamma_set_gamma
argument_list|(
name|gamma
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
DECL|function|cdisplay_gamma_convert (GimpColorDisplay * display,guchar * buf,gint width,gint height,gint bpp,gint bpl)
name|cdisplay_gamma_convert
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
name|CdisplayGamma
modifier|*
name|gamma
init|=
name|CDISPLAY_GAMMA
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
name|gamma
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
DECL|function|cdisplay_gamma_configure (GimpColorDisplay * display)
name|cdisplay_gamma_configure
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
block|{
name|CdisplayGamma
modifier|*
name|gamma
init|=
name|CDISPLAY_GAMMA
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
literal|"_Gamma:"
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
name|gamma
argument_list|)
argument_list|,
literal|"gamma"
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
DECL|function|cdisplay_gamma_set_gamma (CdisplayGamma * gamma,gdouble value)
name|cdisplay_gamma_set_gamma
parameter_list|(
name|CdisplayGamma
modifier|*
name|gamma
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
name|gamma
operator|->
name|gamma
condition|)
block|{
name|gdouble
name|one_over_gamma
init|=
literal|1.0
operator|/
name|value
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gamma
operator|->
name|gamma
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
name|gdouble
name|ind
init|=
operator|(
name|gdouble
operator|)
name|i
operator|/
literal|255.0
decl_stmt|;
name|gamma
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
name|pow
argument_list|(
name|ind
argument_list|,
name|one_over_gamma
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|gamma
argument_list|)
argument_list|,
literal|"gamma"
argument_list|)
expr_stmt|;
name|gimp_color_display_changed
argument_list|(
name|GIMP_COLOR_DISPLAY
argument_list|(
name|gamma
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

