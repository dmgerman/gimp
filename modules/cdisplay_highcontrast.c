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
file|"libgimp/gimpmodule.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpcolordisplay.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"gimpmodregister.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_define
DECL|macro|COLOR_DISPLAY_NAME
define|#
directive|define
name|COLOR_DISPLAY_NAME
value|_("High Contrast")
end_define

begin_typedef
DECL|typedef|ContrastContext
typedef|typedef
name|struct
name|_ContrastContext
name|ContrastContext
typedef|;
end_typedef

begin_struct
DECL|struct|_ContrastContext
struct|struct
name|_ContrastContext
block|{
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

begin_function_decl
specifier|static
name|gpointer
name|contrast_new
parameter_list|(
name|gint
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gpointer
name|contrast_clone
parameter_list|(
name|gpointer
name|cd_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|contrast_create_lookup_table
parameter_list|(
name|ContrastContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|contrast_destroy
parameter_list|(
name|gpointer
name|cd_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|contrast_convert
parameter_list|(
name|gpointer
name|cd_ID
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
name|contrast_load
parameter_list|(
name|gpointer
name|cd_ID
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
name|contrast_save
parameter_list|(
name|gpointer
name|cd_ID
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
name|gpointer
name|data
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
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|contrast_configure
parameter_list|(
name|gpointer
name|cd_ID
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
name|contrast_configure_cancel
parameter_list|(
name|gpointer
name|cd_ID
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|methods
specifier|static
name|GimpColorDisplayMethods
name|methods
init|=
block|{
name|NULL
block|,
name|contrast_new
block|,
name|contrast_clone
block|,
name|contrast_convert
block|,
name|contrast_destroy
block|,
name|NULL
block|,
name|contrast_load
block|,
name|contrast_save
block|,
name|contrast_configure
block|,
name|contrast_configure_cancel
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|info
specifier|static
name|GimpModuleInfo
name|info
init|=
block|{
name|NULL
block|,
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

begin_function
name|G_MODULE_EXPORT
name|GimpModuleStatus
DECL|function|module_init (GimpModuleInfo ** inforet)
name|module_init
parameter_list|(
name|GimpModuleInfo
modifier|*
modifier|*
name|inforet
parameter_list|)
block|{
ifndef|#
directive|ifndef
name|__EMX__
if|if
condition|(
name|gimp_color_display_register
argument_list|(
name|COLOR_DISPLAY_NAME
argument_list|,
operator|&
name|methods
argument_list|)
condition|)
else|#
directive|else
if|if
condition|(
name|mod_color_display_register
argument_list|(
name|COLOR_DISPLAY_NAME
argument_list|,
operator|&
name|methods
argument_list|)
condition|)
endif|#
directive|endif
block|{
operator|*
name|inforet
operator|=
operator|&
name|info
expr_stmt|;
return|return
name|GIMP_MODULE_OK
return|;
block|}
else|else
return|return
name|GIMP_MODULE_UNLOAD
return|;
block|}
end_function

begin_function
name|G_MODULE_EXPORT
name|void
DECL|function|module_unload (void * shutdown_data,void (* completed_cb)(void *),void * completed_data)
name|module_unload
parameter_list|(
name|void
modifier|*
name|shutdown_data
parameter_list|,
name|void
function_decl|(
modifier|*
name|completed_cb
function_decl|)
parameter_list|(
name|void
modifier|*
parameter_list|)
parameter_list|,
name|void
modifier|*
name|completed_data
parameter_list|)
block|{
ifndef|#
directive|ifndef
name|__EMX__
name|gimp_color_display_unregister
argument_list|(
name|COLOR_DISPLAY_NAME
argument_list|)
expr_stmt|;
else|#
directive|else
name|mod_color_display_unregister
argument_list|(
name|COLOR_DISPLAY_NAME
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
end_function

begin_function
specifier|static
name|gpointer
DECL|function|contrast_new (gint type)
name|contrast_new
parameter_list|(
name|gint
name|type
parameter_list|)
block|{
name|ContrastContext
modifier|*
name|context
decl_stmt|;
name|context
operator|=
name|g_new0
argument_list|(
name|ContrastContext
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|context
operator|->
name|contrast
operator|=
literal|4.0
expr_stmt|;
name|context
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
name|context
argument_list|)
expr_stmt|;
return|return
name|context
return|;
block|}
end_function

begin_function
specifier|static
name|gpointer
DECL|function|contrast_clone (gpointer cd_ID)
name|contrast_clone
parameter_list|(
name|gpointer
name|cd_ID
parameter_list|)
block|{
name|ContrastContext
modifier|*
name|src_context
init|=
name|cd_ID
decl_stmt|;
name|ContrastContext
modifier|*
name|context
decl_stmt|;
name|context
operator|=
name|contrast_new
argument_list|(
literal|0
argument_list|)
expr_stmt|;
name|context
operator|->
name|contrast
operator|=
name|src_context
operator|->
name|contrast
expr_stmt|;
name|memcpy
argument_list|(
name|context
operator|->
name|lookup
argument_list|,
name|src_context
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
name|context
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|contrast_create_lookup_table (ContrastContext * context)
name|contrast_create_lookup_table
parameter_list|(
name|ContrastContext
modifier|*
name|context
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
if|if
condition|(
name|context
operator|->
name|contrast
operator|==
literal|0.0
condition|)
name|context
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
name|context
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
name|int
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
name|context
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
DECL|function|contrast_destroy (gpointer cd_ID)
name|contrast_destroy
parameter_list|(
name|gpointer
name|cd_ID
parameter_list|)
block|{
name|ContrastContext
modifier|*
name|context
init|=
name|cd_ID
decl_stmt|;
if|if
condition|(
name|context
operator|->
name|shell
condition|)
block|{
if|#
directive|if
literal|0
block|dialog_unregister (context->shell);
endif|#
directive|endif
name|gtk_widget_destroy
argument_list|(
name|context
operator|->
name|shell
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|context
operator|->
name|lookup
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|context
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|contrast_convert (gpointer cd_ID,guchar * buf,gint width,gint height,gint bpp,gint bpl)
name|contrast_convert
parameter_list|(
name|gpointer
name|cd_ID
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
name|guchar
modifier|*
name|lookup
init|=
operator|(
operator|(
name|ContrastContext
operator|*
operator|)
name|cd_ID
operator|)
operator|->
name|lookup
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|j
init|=
name|height
decl_stmt|;
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
DECL|function|contrast_load (gpointer cd_ID,GimpParasite * state)
name|contrast_load
parameter_list|(
name|gpointer
name|cd_ID
parameter_list|,
name|GimpParasite
modifier|*
name|state
parameter_list|)
block|{
name|ContrastContext
modifier|*
name|context
init|=
name|cd_ID
decl_stmt|;
if|#
directive|if
name|G_BYTE_ORDER
operator|==
name|G_BIG_ENDIAN
name|memcpy
argument_list|(
operator|&
name|context
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
name|context
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
endif|#
directive|endif
name|contrast_create_lookup_table
argument_list|(
name|context
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GimpParasite
modifier|*
DECL|function|contrast_save (gpointer cd_ID)
name|contrast_save
parameter_list|(
name|gpointer
name|cd_ID
parameter_list|)
block|{
name|ContrastContext
modifier|*
name|context
init|=
name|cd_ID
decl_stmt|;
name|guint32
name|buf
index|[
literal|2
index|]
decl_stmt|;
name|memcpy
argument_list|(
name|buf
argument_list|,
operator|&
name|context
operator|->
name|contrast
argument_list|,
sizeof|sizeof
argument_list|(
name|gdouble
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
init|=
name|g_htonl
argument_list|(
name|buf
index|[
literal|0
index|]
argument_list|)
decl_stmt|;
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
name|gdouble
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
DECL|function|contrast_configure_ok_callback (GtkWidget * widget,gpointer data)
name|contrast_configure_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|ContrastContext
modifier|*
name|context
init|=
name|data
decl_stmt|;
name|context
operator|->
name|contrast
operator|=
name|gtk_spin_button_get_value
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|context
operator|->
name|spinner
argument_list|)
argument_list|)
expr_stmt|;
name|contrast_create_lookup_table
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|#
directive|if
literal|0
block|dialog_unregister (context->shell);
endif|#
directive|endif
name|gtk_widget_destroy
argument_list|(
name|GTK_WIDGET
argument_list|(
name|context
operator|->
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|context
operator|->
name|shell
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|context
operator|->
name|ok_func
condition|)
name|context
operator|->
name|ok_func
argument_list|(
name|context
argument_list|,
name|context
operator|->
name|ok_data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|contrast_configure_cancel_callback (GtkWidget * widget,gpointer data)
name|contrast_configure_cancel_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|ContrastContext
modifier|*
name|context
init|=
name|data
decl_stmt|;
if|#
directive|if
literal|0
block|dialog_unregister (context->shell);
endif|#
directive|endif
name|gtk_widget_destroy
argument_list|(
name|GTK_WIDGET
argument_list|(
name|context
operator|->
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|context
operator|->
name|shell
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|context
operator|->
name|cancel_func
condition|)
name|context
operator|->
name|cancel_func
argument_list|(
name|context
argument_list|,
name|context
operator|->
name|cancel_data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|contrast_configure (gpointer cd_ID,GFunc ok_func,gpointer ok_data,GFunc cancel_func,gpointer cancel_data)
name|contrast_configure
parameter_list|(
name|gpointer
name|cd_ID
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
name|ContrastContext
modifier|*
name|context
init|=
name|cd_ID
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
if|if
condition|(
operator|!
name|context
operator|->
name|shell
condition|)
block|{
name|context
operator|->
name|ok_func
operator|=
name|ok_func
expr_stmt|;
name|context
operator|->
name|ok_data
operator|=
name|ok_data
expr_stmt|;
name|context
operator|->
name|cancel_func
operator|=
name|cancel_func
expr_stmt|;
name|context
operator|->
name|cancel_data
operator|=
name|cancel_data
expr_stmt|;
name|context
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
literal|"high contrast"
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
name|cd_ID
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
name|cd_ID
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
if|#
directive|if
literal|0
block|dialog_register (context->shell);
endif|#
directive|endif
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
name|context
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
name|context
operator|->
name|contrast
argument_list|,
literal|1.0
argument_list|,
literal|20.0
argument_list|,
literal|0.5
argument_list|,
literal|1.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|context
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
name|gtk_widget_set_size_request
argument_list|(
name|context
operator|->
name|spinner
argument_list|,
literal|100
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
name|context
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
name|context
operator|->
name|shell
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|contrast_configure_cancel (gpointer cd_ID)
name|contrast_configure_cancel
parameter_list|(
name|gpointer
name|cd_ID
parameter_list|)
block|{
name|ContrastContext
modifier|*
name|context
init|=
name|cd_ID
decl_stmt|;
if|if
condition|(
name|context
operator|->
name|shell
condition|)
block|{
if|#
directive|if
literal|0
block|dialog_unregister (context->shell);
endif|#
directive|endif
name|gtk_widget_destroy
argument_list|(
name|context
operator|->
name|shell
argument_list|)
expr_stmt|;
name|context
operator|->
name|shell
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|context
operator|->
name|cancel_func
condition|)
name|context
operator|->
name|cancel_func
argument_list|(
name|context
argument_list|,
name|context
operator|->
name|cancel_data
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

