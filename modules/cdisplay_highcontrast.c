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
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpmodule.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_define
DECL|macro|CDISPLAY_TYPE_CONTRAST
define|#
directive|define
name|CDISPLAY_TYPE_CONTRAST
value|(cdisplay_contrast_type)
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
DECL|member|ok_func
name|GFunc
name|ok_func
decl_stmt|;
DECL|member|ok_data
name|gpointer
name|ok_data
decl_stmt|;
DECL|member|cancel_func
name|GFunc
name|cancel_func
decl_stmt|;
DECL|member|cancel_data
name|gpointer
name|cancel_data
decl_stmt|;
DECL|member|contrast
name|gdouble
name|contrast
decl_stmt|;
DECL|member|lookup
name|guchar
modifier|*
name|lookup
decl_stmt|;
DECL|member|shell
name|GtkWidget
modifier|*
name|shell
decl_stmt|;
DECL|member|spinner
name|GtkWidget
modifier|*
name|spinner
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

begin_function_decl
specifier|static
name|GType
name|cdisplay_contrast_get_type
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
name|cdisplay_contrast_class_init
parameter_list|(
name|CdisplayContrastClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|cdisplay_contrast_init
parameter_list|(
name|CdisplayContrast
modifier|*
name|contrast
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|cdisplay_contrast_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpColorDisplay
modifier|*
name|cdisplay_contrast_clone
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
name|void
name|cdisplay_contrast_load_state
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|,
name|GimpParasite
modifier|*
name|state
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpParasite
modifier|*
name|cdisplay_contrast_save_state
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
name|cdisplay_contrast_configure
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|,
name|GFunc
name|ok_func
parameter_list|,
name|gpointer
name|ok_data
parameter_list|,
name|GFunc
name|cancel_func
parameter_list|,
name|gpointer
name|cancel_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|cdisplay_contrast_configure_cancel
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
name|contrast_create_lookup_table
parameter_list|(
name|CdisplayContrast
modifier|*
name|contrast
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|contrast_configure_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|CdisplayContrast
modifier|*
name|contrast
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|contrast_configure_cancel_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|CdisplayContrast
modifier|*
name|contrast
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
name|N_
argument_list|(
literal|"High Contrast color display filter"
argument_list|)
block|,
literal|"Jay Cox<jaycox@earthlink.net>"
block|,
literal|"v0.2"
block|,
literal|"(c) 2000, released under the GPL"
block|,
literal|"October 14, 2000"
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|cdisplay_contrast_type
specifier|static
name|GType
name|cdisplay_contrast_type
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
name|cdisplay_contrast_get_type
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
DECL|function|cdisplay_contrast_get_type (GTypeModule * module)
name|cdisplay_contrast_get_type
parameter_list|(
name|GTypeModule
modifier|*
name|module
parameter_list|)
block|{
if|if
condition|(
operator|!
name|cdisplay_contrast_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|select_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|CdisplayContrastClass
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
name|cdisplay_contrast_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|CdisplayContrast
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|cdisplay_contrast_init
block|,       }
decl_stmt|;
name|cdisplay_contrast_type
operator|=
name|g_type_module_register_type
argument_list|(
name|module
argument_list|,
name|GIMP_TYPE_COLOR_DISPLAY
argument_list|,
literal|"CdisplayContrast"
argument_list|,
operator|&
name|select_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|cdisplay_contrast_type
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
decl_stmt|;
name|GimpColorDisplayClass
modifier|*
name|display_class
decl_stmt|;
name|object_class
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|display_class
operator|=
name|GIMP_COLOR_DISPLAY_CLASS
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
name|object_class
operator|->
name|finalize
operator|=
name|cdisplay_contrast_finalize
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
name|help_page
operator|=
literal|"modules/contrast.html"
expr_stmt|;
name|display_class
operator|->
name|clone
operator|=
name|cdisplay_contrast_clone
expr_stmt|;
name|display_class
operator|->
name|convert
operator|=
name|cdisplay_contrast_convert
expr_stmt|;
name|display_class
operator|->
name|load_state
operator|=
name|cdisplay_contrast_load_state
expr_stmt|;
name|display_class
operator|->
name|save_state
operator|=
name|cdisplay_contrast_save_state
expr_stmt|;
name|display_class
operator|->
name|configure
operator|=
name|cdisplay_contrast_configure
expr_stmt|;
name|display_class
operator|->
name|configure_cancel
operator|=
name|cdisplay_contrast_configure_cancel
expr_stmt|;
block|}
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
block|{
name|contrast
operator|->
name|contrast
operator|=
literal|4.0
expr_stmt|;
name|contrast
operator|->
name|lookup
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
literal|256
argument_list|)
expr_stmt|;
name|contrast_create_lookup_table
argument_list|(
name|contrast
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|cdisplay_contrast_finalize (GObject * object)
name|cdisplay_contrast_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|CdisplayContrast
modifier|*
name|contrast
decl_stmt|;
name|contrast
operator|=
name|CDISPLAY_CONTRAST
argument_list|(
name|object
argument_list|)
expr_stmt|;
if|if
condition|(
name|contrast
operator|->
name|shell
condition|)
block|{
name|gtk_widget_destroy
argument_list|(
name|contrast
operator|->
name|shell
argument_list|)
expr_stmt|;
name|contrast
operator|->
name|shell
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|contrast
operator|->
name|lookup
condition|)
block|{
name|g_free
argument_list|(
name|contrast
operator|->
name|lookup
argument_list|)
expr_stmt|;
name|contrast
operator|->
name|lookup
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
name|GimpColorDisplay
modifier|*
DECL|function|cdisplay_contrast_clone (GimpColorDisplay * display)
name|cdisplay_contrast_clone
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
block|{
name|CdisplayContrast
modifier|*
name|contrast
decl_stmt|;
name|CdisplayContrast
modifier|*
name|copy
decl_stmt|;
name|contrast
operator|=
name|CDISPLAY_CONTRAST
argument_list|(
name|display
argument_list|)
expr_stmt|;
name|copy
operator|=
name|CDISPLAY_CONTRAST
argument_list|(
name|gimp_color_display_new
argument_list|(
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|contrast
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|copy
operator|->
name|contrast
operator|=
name|contrast
operator|->
name|contrast
expr_stmt|;
name|memcpy
argument_list|(
name|copy
operator|->
name|lookup
argument_list|,
name|contrast
operator|->
name|lookup
argument_list|,
sizeof|sizeof
argument_list|(
name|guchar
argument_list|)
operator|*
literal|256
argument_list|)
expr_stmt|;
return|return
name|GIMP_COLOR_DISPLAY
argument_list|(
name|copy
argument_list|)
return|;
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
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|j
init|=
name|height
decl_stmt|;
name|contrast
operator|=
name|CDISPLAY_CONTRAST
argument_list|(
name|display
argument_list|)
expr_stmt|;
comment|/* You will not be using the entire buffer most of the time.     * Hence, the simplistic code for this is as follows:    *    * for (j = 0; j< height; j++)    *   {    *     for (i = 0; i< width * bpp; i++)    *       buf[i] = lookup[buf[i]];    *     buf += bpl;    *   }    */
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
name|void
DECL|function|cdisplay_contrast_load_state (GimpColorDisplay * display,GimpParasite * state)
name|cdisplay_contrast_load_state
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|,
name|GimpParasite
modifier|*
name|state
parameter_list|)
block|{
name|CdisplayContrast
modifier|*
name|contrast
decl_stmt|;
name|contrast
operator|=
name|CDISPLAY_CONTRAST
argument_list|(
name|display
argument_list|)
expr_stmt|;
if|#
directive|if
name|G_BYTE_ORDER
operator|==
name|G_BIG_ENDIAN
name|memcpy
argument_list|(
operator|&
name|contrast
operator|->
name|contrast
argument_list|,
name|gimp_parasite_data
argument_list|(
name|state
argument_list|)
argument_list|,
sizeof|sizeof
argument_list|(
name|gdouble
argument_list|)
argument_list|)
expr_stmt|;
else|#
directive|else
block|{
name|guint32
name|buf
index|[
literal|2
index|]
decl_stmt|,
modifier|*
name|data
init|=
name|gimp_parasite_data
argument_list|(
name|state
argument_list|)
decl_stmt|;
name|buf
index|[
literal|0
index|]
operator|=
name|g_ntohl
argument_list|(
name|data
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
name|buf
index|[
literal|1
index|]
operator|=
name|g_ntohl
argument_list|(
name|data
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
operator|&
name|contrast
operator|->
name|contrast
argument_list|,
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
name|gdouble
argument_list|)
argument_list|)
expr_stmt|;
block|}
endif|#
directive|endif
name|contrast_create_lookup_table
argument_list|(
name|contrast
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GimpParasite
modifier|*
DECL|function|cdisplay_contrast_save_state (GimpColorDisplay * display)
name|cdisplay_contrast_save_state
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
block|{
name|CdisplayContrast
modifier|*
name|contrast
decl_stmt|;
name|guint32
name|buf
index|[
literal|2
index|]
decl_stmt|;
name|contrast
operator|=
name|CDISPLAY_CONTRAST
argument_list|(
name|display
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|buf
argument_list|,
operator|&
name|contrast
operator|->
name|contrast
argument_list|,
sizeof|sizeof
argument_list|(
name|double
argument_list|)
argument_list|)
expr_stmt|;
if|#
directive|if
name|G_BYTE_ORDER
operator|==
name|G_LITTLE_ENDIAN
block|{
name|guint32
name|tmp
decl_stmt|;
name|tmp
operator|=
name|g_htonl
argument_list|(
name|buf
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
name|buf
index|[
literal|0
index|]
operator|=
name|g_htonl
argument_list|(
name|buf
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
name|buf
index|[
literal|1
index|]
operator|=
name|tmp
expr_stmt|;
block|}
endif|#
directive|endif
return|return
name|gimp_parasite_new
argument_list|(
literal|"Display/Contrast"
argument_list|,
name|GIMP_PARASITE_PERSISTENT
argument_list|,
sizeof|sizeof
argument_list|(
name|double
argument_list|)
argument_list|,
operator|&
name|buf
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|cdisplay_contrast_configure (GimpColorDisplay * display,GFunc ok_func,gpointer ok_data,GFunc cancel_func,gpointer cancel_data)
name|cdisplay_contrast_configure
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|,
name|GFunc
name|ok_func
parameter_list|,
name|gpointer
name|ok_data
parameter_list|,
name|GFunc
name|cancel_func
parameter_list|,
name|gpointer
name|cancel_data
parameter_list|)
block|{
name|CdisplayContrast
modifier|*
name|contrast
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkObject
modifier|*
name|adjustment
decl_stmt|;
name|contrast
operator|=
name|CDISPLAY_CONTRAST
argument_list|(
name|display
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|contrast
operator|->
name|shell
condition|)
block|{
name|contrast
operator|->
name|ok_func
operator|=
name|ok_func
expr_stmt|;
name|contrast
operator|->
name|ok_data
operator|=
name|ok_data
expr_stmt|;
name|contrast
operator|->
name|cancel_func
operator|=
name|cancel_func
expr_stmt|;
name|contrast
operator|->
name|cancel_data
operator|=
name|cancel_data
expr_stmt|;
name|contrast
operator|->
name|shell
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"High Contrast"
argument_list|)
argument_list|,
literal|"high_contrast"
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"modules/highcontrast.html"
argument_list|,
name|GTK_WIN_POS_MOUSE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|contrast_configure_cancel_callback
argument_list|,
name|contrast
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|GTK_STOCK_OK
argument_list|,
name|contrast_configure_ok_callback
argument_list|,
name|contrast
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|hbox
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|contrast
operator|->
name|shell
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|hbox
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Contrast Cycles:"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
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
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|adjustment
operator|=
name|gtk_adjustment_new
argument_list|(
name|contrast
operator|->
name|contrast
argument_list|,
literal|0.01
argument_list|,
literal|10.0
argument_list|,
literal|0.01
argument_list|,
literal|0.1
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|contrast
operator|->
name|spinner
operator|=
name|gtk_spin_button_new
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|adjustment
argument_list|)
argument_list|,
literal|0.1
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
name|contrast
operator|->
name|spinner
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_show_all
argument_list|(
name|contrast
operator|->
name|shell
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|cdisplay_contrast_configure_cancel (GimpColorDisplay * display)
name|cdisplay_contrast_configure_cancel
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
block|{
name|CdisplayContrast
modifier|*
name|contrast
decl_stmt|;
name|contrast
operator|=
name|CDISPLAY_CONTRAST
argument_list|(
name|display
argument_list|)
expr_stmt|;
if|if
condition|(
name|contrast
operator|->
name|shell
condition|)
block|{
name|gtk_widget_destroy
argument_list|(
name|contrast
operator|->
name|shell
argument_list|)
expr_stmt|;
name|contrast
operator|->
name|shell
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|contrast
operator|->
name|cancel_func
condition|)
name|contrast
operator|->
name|cancel_func
argument_list|(
name|contrast
argument_list|,
name|contrast
operator|->
name|cancel_data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|contrast_create_lookup_table (CdisplayContrast * contrast)
name|contrast_create_lookup_table
parameter_list|(
name|CdisplayContrast
modifier|*
name|contrast
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
if|if
condition|(
name|contrast
operator|->
name|contrast
operator|==
literal|0.0
condition|)
name|contrast
operator|->
name|contrast
operator|=
literal|1.0
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
name|contrast
operator|->
name|contrast
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
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|contrast_configure_ok_callback (GtkWidget * widget,CdisplayContrast * contrast)
name|contrast_configure_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|CdisplayContrast
modifier|*
name|contrast
parameter_list|)
block|{
name|contrast
operator|->
name|contrast
operator|=
name|gtk_spin_button_get_value
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|contrast
operator|->
name|spinner
argument_list|)
argument_list|)
expr_stmt|;
name|contrast_create_lookup_table
argument_list|(
name|contrast
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|GTK_WIDGET
argument_list|(
name|contrast
operator|->
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|contrast
operator|->
name|shell
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|contrast
operator|->
name|ok_func
condition|)
name|contrast
operator|->
name|ok_func
argument_list|(
name|contrast
argument_list|,
name|contrast
operator|->
name|ok_data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|contrast_configure_cancel_callback (GtkWidget * widget,CdisplayContrast * contrast)
name|contrast_configure_cancel_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|CdisplayContrast
modifier|*
name|contrast
parameter_list|)
block|{
name|gimp_color_display_configure_cancel
argument_list|(
name|GIMP_COLOR_DISPLAY
argument_list|(
name|contrast
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

