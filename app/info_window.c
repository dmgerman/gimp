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
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"colormaps.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimpset.h"
end_include

begin_include
include|#
directive|include
file|"gimpui.h"
end_include

begin_include
include|#
directive|include
file|"gximage.h"
end_include

begin_include
include|#
directive|include
file|"info_dialog.h"
end_include

begin_include
include|#
directive|include
file|"info_window.h"
end_include

begin_include
include|#
directive|include
file|"interface.h"
end_include

begin_include
include|#
directive|include
file|"scroll.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpunit.h"
end_include

begin_include
include|#
directive|include
file|"pixmaps/dropper.xpm"
end_include

begin_define
DECL|macro|MAX_BUF
define|#
directive|define
name|MAX_BUF
value|256
end_define

begin_typedef
DECL|typedef|InfoWinData
typedef|typedef
name|struct
name|_InfoWinData
name|InfoWinData
typedef|;
end_typedef

begin_struct
DECL|struct|_InfoWinData
struct|struct
name|_InfoWinData
block|{
DECL|member|dimensions_str
name|gchar
name|dimensions_str
index|[
name|MAX_BUF
index|]
decl_stmt|;
DECL|member|real_dimensions_str
name|gchar
name|real_dimensions_str
index|[
name|MAX_BUF
index|]
decl_stmt|;
DECL|member|scale_str
name|gchar
name|scale_str
index|[
name|MAX_BUF
index|]
decl_stmt|;
DECL|member|color_type_str
name|gchar
name|color_type_str
index|[
name|MAX_BUF
index|]
decl_stmt|;
DECL|member|visual_class_str
name|gchar
name|visual_class_str
index|[
name|MAX_BUF
index|]
decl_stmt|;
DECL|member|visual_depth_str
name|gchar
name|visual_depth_str
index|[
name|MAX_BUF
index|]
decl_stmt|;
DECL|member|resolution_str
name|gchar
name|resolution_str
index|[
name|MAX_BUF
index|]
decl_stmt|;
DECL|member|unit_str
name|gchar
name|unit_str
index|[
name|MAX_BUF
index|]
decl_stmt|;
DECL|member|gdisp
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
DECL|member|labelBvalue
name|GtkWidget
modifier|*
name|labelBvalue
decl_stmt|;
DECL|member|labelGvalue
name|GtkWidget
modifier|*
name|labelGvalue
decl_stmt|;
DECL|member|labelRvalue
name|GtkWidget
modifier|*
name|labelRvalue
decl_stmt|;
DECL|member|labelAvalue
name|GtkWidget
modifier|*
name|labelAvalue
decl_stmt|;
DECL|member|showingPreview
name|gboolean
name|showingPreview
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  The different classes of visuals  */
end_comment

begin_decl_stmt
DECL|variable|visual_classes
specifier|static
name|gchar
modifier|*
name|visual_classes
index|[]
init|=
block|{
name|N_
argument_list|(
literal|"Static Gray"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Grayscale"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Static Color"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Pseudo Color"
argument_list|)
block|,
name|N_
argument_list|(
literal|"True Color"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Direct Color"
argument_list|)
block|, }
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|static
name|gchar
modifier|*
name|info_window_title
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function
specifier|static
name|void
DECL|function|info_window_image_rename_callback (GimpImage * gimage,gpointer data)
name|info_window_image_rename_callback
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|InfoDialog
modifier|*
name|id
decl_stmt|;
name|gchar
modifier|*
name|title
decl_stmt|;
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
name|InfoWinData
modifier|*
name|iwd
decl_stmt|;
name|id
operator|=
operator|(
name|InfoDialog
operator|*
operator|)
name|data
expr_stmt|;
name|iwd
operator|=
operator|(
name|InfoWinData
operator|*
operator|)
name|id
operator|->
name|user_data
expr_stmt|;
name|gdisp
operator|=
operator|(
name|GDisplay
operator|*
operator|)
name|iwd
operator|->
name|gdisp
expr_stmt|;
name|title
operator|=
name|info_window_title
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
name|gtk_window_set_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|id
operator|->
name|shell
argument_list|)
argument_list|,
name|title
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|title
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|info_window_close_callback (GtkWidget * widget,gpointer data)
name|info_window_close_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|info_dialog_popdown
argument_list|(
operator|(
name|InfoDialog
operator|*
operator|)
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|info_window_page_switch (GtkWidget * widget,GtkNotebookPage * page,gint page_num)
name|info_window_page_switch
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkNotebookPage
modifier|*
name|page
parameter_list|,
name|gint
name|page_num
parameter_list|)
block|{
name|InfoDialog
modifier|*
name|info_win
decl_stmt|;
name|InfoWinData
modifier|*
name|iwd
decl_stmt|;
name|info_win
operator|=
operator|(
name|InfoDialog
operator|*
operator|)
name|gtk_object_get_user_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|iwd
operator|=
operator|(
name|InfoWinData
operator|*
operator|)
name|info_win
operator|->
name|user_data
expr_stmt|;
comment|/* Only deal with the second page */
if|if
condition|(
name|page_num
operator|!=
literal|1
condition|)
block|{
name|iwd
operator|->
name|showingPreview
operator|=
name|FALSE
expr_stmt|;
return|return;
block|}
name|iwd
operator|->
name|showingPreview
operator|=
name|TRUE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|info_window_image_preview_book (InfoDialog * info_win)
name|info_window_image_preview_book
parameter_list|(
name|InfoDialog
modifier|*
name|info_win
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|hbox1
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|alignment
decl_stmt|;
name|GtkWidget
modifier|*
name|table2
decl_stmt|;
name|GtkWidget
modifier|*
name|labelBvalue
decl_stmt|;
name|GtkWidget
modifier|*
name|labelGvalue
decl_stmt|;
name|GtkWidget
modifier|*
name|labelRvalue
decl_stmt|;
name|GtkWidget
modifier|*
name|labelAvalue
decl_stmt|;
name|GtkWidget
modifier|*
name|labelB
decl_stmt|;
name|GtkWidget
modifier|*
name|labelG
decl_stmt|;
name|GtkWidget
modifier|*
name|labelR
decl_stmt|;
name|GtkWidget
modifier|*
name|labelA
decl_stmt|;
name|GtkWidget
modifier|*
name|pixmapwid
decl_stmt|;
name|GdkPixmap
modifier|*
name|pixmap
decl_stmt|;
name|GdkBitmap
modifier|*
name|mask
decl_stmt|;
name|GtkStyle
modifier|*
name|style
decl_stmt|;
name|InfoWinData
modifier|*
name|iwd
decl_stmt|;
name|iwd
operator|=
operator|(
name|InfoWinData
operator|*
operator|)
name|info_win
operator|->
name|user_data
expr_stmt|;
name|hbox1
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox1
argument_list|)
expr_stmt|;
name|alignment
operator|=
name|gtk_alignment_new
argument_list|(
literal|0.5
argument_list|,
literal|0.5
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|alignment
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox1
argument_list|)
argument_list|,
name|alignment
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|table2
operator|=
name|gtk_table_new
argument_list|(
literal|5
argument_list|,
literal|2
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|table2
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table2
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|table2
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|alignment
argument_list|)
argument_list|,
name|frame
argument_list|)
expr_stmt|;
name|labelAvalue
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"N/A"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|labelAvalue
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table2
argument_list|)
argument_list|,
name|labelAvalue
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|4
argument_list|,
literal|5
argument_list|,
name|GTK_EXPAND
operator||
name|GTK_FILL
argument_list|,
name|GTK_EXPAND
operator||
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|labelBvalue
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"N/A"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|labelBvalue
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table2
argument_list|)
argument_list|,
name|labelBvalue
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|3
argument_list|,
literal|4
argument_list|,
name|GTK_EXPAND
operator||
name|GTK_FILL
argument_list|,
name|GTK_EXPAND
operator||
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|labelGvalue
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"N/A"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|labelGvalue
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table2
argument_list|)
argument_list|,
name|labelGvalue
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|2
argument_list|,
literal|3
argument_list|,
name|GTK_EXPAND
operator||
name|GTK_FILL
argument_list|,
name|GTK_EXPAND
operator||
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|labelRvalue
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"N/A"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|labelRvalue
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table2
argument_list|)
argument_list|,
name|labelRvalue
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
name|GTK_EXPAND
operator||
name|GTK_FILL
argument_list|,
name|GTK_EXPAND
operator||
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|labelA
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"A:"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|labelA
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table2
argument_list|)
argument_list|,
name|labelA
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|4
argument_list|,
literal|5
argument_list|,
name|GTK_EXPAND
operator||
name|GTK_FILL
argument_list|,
name|GTK_EXPAND
operator||
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|labelB
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"B:"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|labelB
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table2
argument_list|)
argument_list|,
name|labelB
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|3
argument_list|,
literal|4
argument_list|,
name|GTK_EXPAND
operator||
name|GTK_FILL
argument_list|,
name|GTK_EXPAND
operator||
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|labelG
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"G:"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|labelG
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table2
argument_list|)
argument_list|,
name|labelG
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|3
argument_list|,
name|GTK_EXPAND
operator||
name|GTK_FILL
argument_list|,
name|GTK_EXPAND
operator||
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|labelR
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"R:"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|labelR
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table2
argument_list|)
argument_list|,
name|labelR
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
name|GTK_EXPAND
operator||
name|GTK_FILL
argument_list|,
name|GTK_EXPAND
operator||
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_realize
argument_list|(
name|info_win
operator|->
name|shell
argument_list|)
expr_stmt|;
name|style
operator|=
name|gtk_widget_get_style
argument_list|(
name|info_win
operator|->
name|shell
argument_list|)
expr_stmt|;
name|pixmap
operator|=
name|gdk_pixmap_create_from_xpm_d
argument_list|(
name|info_win
operator|->
name|shell
operator|->
name|window
argument_list|,
operator|&
name|mask
argument_list|,
operator|&
name|style
operator|->
name|bg
index|[
name|GTK_STATE_NORMAL
index|]
argument_list|,
name|dropper_xpm
argument_list|)
expr_stmt|;
name|pixmapwid
operator|=
name|gtk_pixmap_new
argument_list|(
name|pixmap
argument_list|,
name|mask
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table2
argument_list|)
argument_list|,
name|pixmapwid
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|GTK_EXPAND
operator||
name|GTK_FILL
argument_list|,
name|GTK_EXPAND
operator||
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|pixmapwid
argument_list|)
expr_stmt|;
name|gtk_notebook_append_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|info_win
operator|->
name|info_notebook
argument_list|)
argument_list|,
name|hbox1
argument_list|,
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Extended"
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
comment|/* Set back to first page */
name|gtk_notebook_set_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|info_win
operator|->
name|info_notebook
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_object_set_user_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|info_win
operator|->
name|info_notebook
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|info_win
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|info_win
operator|->
name|info_notebook
argument_list|)
argument_list|,
literal|"switch_page"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|info_window_page_switch
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|iwd
operator|->
name|labelBvalue
operator|=
name|labelBvalue
expr_stmt|;
name|iwd
operator|->
name|labelGvalue
operator|=
name|labelGvalue
expr_stmt|;
name|iwd
operator|->
name|labelRvalue
operator|=
name|labelRvalue
expr_stmt|;
name|iwd
operator|->
name|labelAvalue
operator|=
name|labelAvalue
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  displays information:  *    image name  *    image width, height  *    zoom ratio  *    image color type  *    Display info:  *      visual class  *      visual depth  */
end_comment

begin_function
name|InfoDialog
modifier|*
DECL|function|info_window_create (GDisplay * gdisp)
name|info_window_create
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|InfoDialog
modifier|*
name|info_win
decl_stmt|;
name|InfoWinData
modifier|*
name|iwd
decl_stmt|;
name|gchar
modifier|*
name|title
decl_stmt|,
modifier|*
name|title_buf
decl_stmt|;
name|gint
name|type
decl_stmt|;
name|title
operator|=
name|g_basename
argument_list|(
name|gimage_filename
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|type
operator|=
name|gimage_base_type
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
comment|/*  create the info dialog  */
name|title_buf
operator|=
name|info_window_title
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
name|info_win
operator|=
name|info_dialog_notebook_new
argument_list|(
name|title_buf
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"dialogs/info_window.html"
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|title_buf
argument_list|)
expr_stmt|;
comment|/*  create the action area  */
name|gimp_dialog_create_action_area
argument_list|(
name|GTK_DIALOG
argument_list|(
name|info_win
operator|->
name|shell
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Close"
argument_list|)
argument_list|,
name|info_window_close_callback
argument_list|,
name|info_win
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
name|iwd
operator|=
name|g_new
argument_list|(
name|InfoWinData
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|info_win
operator|->
name|user_data
operator|=
name|iwd
expr_stmt|;
name|iwd
operator|->
name|dimensions_str
index|[
literal|0
index|]
operator|=
literal|'\0'
expr_stmt|;
name|iwd
operator|->
name|real_dimensions_str
index|[
literal|0
index|]
operator|=
literal|'\0'
expr_stmt|;
name|iwd
operator|->
name|resolution_str
index|[
literal|0
index|]
operator|=
literal|'\0'
expr_stmt|;
name|iwd
operator|->
name|scale_str
index|[
literal|0
index|]
operator|=
literal|'\0'
expr_stmt|;
name|iwd
operator|->
name|color_type_str
index|[
literal|0
index|]
operator|=
literal|'\0'
expr_stmt|;
name|iwd
operator|->
name|visual_class_str
index|[
literal|0
index|]
operator|=
literal|'\0'
expr_stmt|;
name|iwd
operator|->
name|visual_depth_str
index|[
literal|0
index|]
operator|=
literal|'\0'
expr_stmt|;
name|iwd
operator|->
name|gdisp
operator|=
name|gdisp
expr_stmt|;
name|iwd
operator|->
name|showingPreview
operator|=
name|FALSE
expr_stmt|;
comment|/*  add the information fields  */
name|info_dialog_add_label
argument_list|(
name|info_win
argument_list|,
name|_
argument_list|(
literal|"Dimensions (w x h):"
argument_list|)
argument_list|,
name|iwd
operator|->
name|dimensions_str
argument_list|)
expr_stmt|;
name|info_dialog_add_label
argument_list|(
name|info_win
argument_list|,
literal|'\0'
argument_list|,
name|iwd
operator|->
name|real_dimensions_str
argument_list|)
expr_stmt|;
name|info_dialog_add_label
argument_list|(
name|info_win
argument_list|,
name|_
argument_list|(
literal|"Resolution:"
argument_list|)
argument_list|,
name|iwd
operator|->
name|resolution_str
argument_list|)
expr_stmt|;
name|info_dialog_add_label
argument_list|(
name|info_win
argument_list|,
name|_
argument_list|(
literal|"Scale Ratio:"
argument_list|)
argument_list|,
name|iwd
operator|->
name|scale_str
argument_list|)
expr_stmt|;
name|info_dialog_add_label
argument_list|(
name|info_win
argument_list|,
name|_
argument_list|(
literal|"Display Type:"
argument_list|)
argument_list|,
name|iwd
operator|->
name|color_type_str
argument_list|)
expr_stmt|;
name|info_dialog_add_label
argument_list|(
name|info_win
argument_list|,
name|_
argument_list|(
literal|"Visual Class:"
argument_list|)
argument_list|,
name|iwd
operator|->
name|visual_class_str
argument_list|)
expr_stmt|;
name|info_dialog_add_label
argument_list|(
name|info_win
argument_list|,
name|_
argument_list|(
literal|"Visual Depth:"
argument_list|)
argument_list|,
name|iwd
operator|->
name|visual_depth_str
argument_list|)
expr_stmt|;
comment|/*  update the fields  */
comment|/*gdisp->window_info_dialog = info_win;*/
name|info_window_update
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
comment|/*  Add extra tabs  */
name|info_window_image_preview_book
argument_list|(
name|info_win
argument_list|)
expr_stmt|;
comment|/*  keep track of image name changes  */
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|,
literal|"rename"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|info_window_image_rename_callback
argument_list|)
argument_list|,
name|info_win
argument_list|)
expr_stmt|;
return|return
name|info_win
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|info_window_auto
specifier|static
name|InfoDialog
modifier|*
name|info_window_auto
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|info_window_title (GDisplay * gdisp)
name|info_window_title
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|gchar
modifier|*
name|title
decl_stmt|;
name|gchar
modifier|*
name|title_buf
decl_stmt|;
name|title
operator|=
name|g_basename
argument_list|(
name|gimage_filename
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  create the info dialog  */
name|title_buf
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Info: %s-%d.%d"
argument_list|)
argument_list|,
name|title
argument_list|,
name|pdb_image_to_id
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|,
name|gdisp
operator|->
name|instance
argument_list|)
expr_stmt|;
return|return
name|title_buf
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|info_window_change_display (GimpContext * context,GDisplay * newdisp,gpointer data)
name|info_window_change_display
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
comment|/* NOT USED */
name|GDisplay
modifier|*
name|newdisp
parameter_list|,
name|gpointer
name|data
comment|/* Not used */
parameter_list|)
block|{
name|GDisplay
modifier|*
name|gdisp
init|=
name|newdisp
decl_stmt|;
name|GDisplay
modifier|*
name|old_gdisp
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|InfoWinData
modifier|*
name|iwd
decl_stmt|;
name|iwd
operator|=
operator|(
name|InfoWinData
operator|*
operator|)
name|info_window_auto
operator|->
name|user_data
expr_stmt|;
name|old_gdisp
operator|=
operator|(
name|GDisplay
operator|*
operator|)
name|iwd
operator|->
name|gdisp
expr_stmt|;
if|if
condition|(
operator|!
name|info_window_auto
operator|||
name|gdisp
operator|==
name|old_gdisp
operator|||
operator|!
name|gdisp
condition|)
block|{
return|return;
block|}
name|gimage
operator|=
name|gdisp
operator|->
name|gimage
expr_stmt|;
if|if
condition|(
name|gimage
operator|&&
name|gimp_set_have
argument_list|(
name|image_context
argument_list|,
name|gimage
argument_list|)
condition|)
block|{
name|iwd
operator|->
name|gdisp
operator|=
name|gdisp
expr_stmt|;
name|info_window_update
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|info_window_follow_auto (void)
name|info_window_follow_auto
parameter_list|(
name|void
parameter_list|)
block|{
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
name|gdisp
operator|=
name|gdisplay_active
argument_list|()
expr_stmt|;
if|if
condition|(
operator|!
name|gdisp
condition|)
return|return;
if|if
condition|(
operator|!
name|info_window_auto
condition|)
block|{
name|info_window_auto
operator|=
name|info_window_create
argument_list|(
operator|(
name|void
operator|*
operator|)
name|gdisp
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gimp_context_get_user
argument_list|()
argument_list|)
argument_list|,
literal|"display_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|info_window_change_display
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|info_window_update
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
comment|/* Update to include the info */
block|}
name|info_dialog_popup
argument_list|(
name|info_window_auto
argument_list|)
expr_stmt|;
comment|/*   iwd = (NavWinData *)nav_window_auto->user_data;   gtk_widget_set_sensitive(nav_window_auto->vbox,TRUE);   iwd->frozen = FALSE;   */
block|}
end_function

begin_function
name|void
DECL|function|info_window_update_RGB (GDisplay * gdisp,gdouble tx,gdouble ty)
name|info_window_update_RGB
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|,
name|gdouble
name|tx
parameter_list|,
name|gdouble
name|ty
parameter_list|)
block|{
name|InfoWinData
modifier|*
name|iwd
decl_stmt|;
name|gchar
name|buff
index|[
literal|5
index|]
decl_stmt|;
name|guchar
modifier|*
name|color
decl_stmt|;
name|gint
name|has_alpha
decl_stmt|;
name|gint
name|sample_type
decl_stmt|;
name|InfoDialog
modifier|*
name|info_win
init|=
name|gdisp
operator|->
name|window_info_dialog
decl_stmt|;
name|gboolean
name|force_update
init|=
name|FALSE
decl_stmt|;
if|if
condition|(
operator|!
name|info_win
operator|&&
name|info_window_auto
operator|!=
name|NULL
condition|)
block|{
name|info_win
operator|=
name|info_window_auto
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|info_win
condition|)
return|return;
name|iwd
operator|=
operator|(
name|InfoWinData
operator|*
operator|)
name|info_win
operator|->
name|user_data
expr_stmt|;
if|if
condition|(
name|iwd
operator|->
name|gdisp
operator|!=
name|gdisp
condition|)
name|force_update
operator|=
name|TRUE
expr_stmt|;
name|iwd
operator|->
name|gdisp
operator|=
name|gdisp
expr_stmt|;
if|if
condition|(
name|force_update
operator|==
name|TRUE
condition|)
block|{
name|gchar
modifier|*
name|title_buf
decl_stmt|;
name|info_window_update
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
name|title_buf
operator|=
name|info_window_title
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
name|gtk_window_set_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|info_window_auto
operator|->
name|shell
argument_list|)
argument_list|,
name|title_buf
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|title_buf
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|iwd
operator|||
name|iwd
operator|->
name|showingPreview
operator|==
name|FALSE
condition|)
return|return;
comment|/* gimage_active_drawable (gdisp->gimage) */
if|if
condition|(
operator|!
operator|(
name|color
operator|=
name|gimp_image_get_color_at
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|tx
argument_list|,
name|ty
argument_list|)
operator|)
operator|||
operator|(
name|tx
operator|<
literal|0.0
operator|&&
name|ty
operator|<
literal|0.0
operator|)
condition|)
block|{
name|g_snprintf
argument_list|(
name|buff
argument_list|,
sizeof|sizeof
argument_list|(
name|buff
argument_list|)
argument_list|,
literal|"%4s"
argument_list|,
literal|"N/A"
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|iwd
operator|->
name|labelBvalue
argument_list|)
argument_list|,
name|buff
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|iwd
operator|->
name|labelGvalue
argument_list|)
argument_list|,
name|buff
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|iwd
operator|->
name|labelRvalue
argument_list|)
argument_list|,
name|buff
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|iwd
operator|->
name|labelAvalue
argument_list|)
argument_list|,
name|buff
argument_list|)
expr_stmt|;
return|return;
block|}
name|g_snprintf
argument_list|(
name|buff
argument_list|,
sizeof|sizeof
argument_list|(
name|buff
argument_list|)
argument_list|,
literal|"%4d"
argument_list|,
operator|(
name|gint
operator|)
name|color
index|[
name|BLUE_PIX
index|]
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|iwd
operator|->
name|labelBvalue
argument_list|)
argument_list|,
name|buff
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|buff
argument_list|,
sizeof|sizeof
argument_list|(
name|buff
argument_list|)
argument_list|,
literal|"%4d"
argument_list|,
operator|(
name|gint
operator|)
name|color
index|[
name|GREEN_PIX
index|]
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|iwd
operator|->
name|labelGvalue
argument_list|)
argument_list|,
name|buff
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|buff
argument_list|,
sizeof|sizeof
argument_list|(
name|buff
argument_list|)
argument_list|,
literal|"%4d"
argument_list|,
operator|(
name|gint
operator|)
name|color
index|[
name|RED_PIX
index|]
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|iwd
operator|->
name|labelRvalue
argument_list|)
argument_list|,
name|buff
argument_list|)
expr_stmt|;
name|sample_type
operator|=
name|gimp_image_composite_type
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
name|has_alpha
operator|=
name|TYPE_HAS_ALPHA
argument_list|(
name|sample_type
argument_list|)
expr_stmt|;
if|if
condition|(
name|has_alpha
condition|)
name|g_snprintf
argument_list|(
name|buff
argument_list|,
sizeof|sizeof
argument_list|(
name|buff
argument_list|)
argument_list|,
literal|"%4d"
argument_list|,
operator|(
name|gint
operator|)
name|color
index|[
name|ALPHA_PIX
index|]
argument_list|)
expr_stmt|;
else|else
name|g_snprintf
argument_list|(
name|buff
argument_list|,
sizeof|sizeof
argument_list|(
name|buff
argument_list|)
argument_list|,
literal|"%4s"
argument_list|,
literal|"N/A"
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|iwd
operator|->
name|labelAvalue
argument_list|)
argument_list|,
name|buff
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|color
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|info_window_free (InfoDialog * info_win)
name|info_window_free
parameter_list|(
name|InfoDialog
modifier|*
name|info_win
parameter_list|)
block|{
name|InfoWinData
modifier|*
name|iwd
decl_stmt|;
specifier|extern
name|gint
name|gimage_image_count
argument_list|(
name|void
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|info_win
operator|&&
name|info_window_auto
condition|)
block|{
name|gtk_widget_set_sensitive
argument_list|(
name|info_window_auto
operator|->
name|vbox
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
operator|!
name|info_win
condition|)
return|return;
name|iwd
operator|=
operator|(
name|InfoWinData
operator|*
operator|)
name|info_win
operator|->
name|user_data
expr_stmt|;
name|gtk_signal_disconnect_by_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|iwd
operator|->
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|,
name|info_win
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|iwd
argument_list|)
expr_stmt|;
name|info_dialog_free
argument_list|(
name|info_win
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|info_window_update (GDisplay * gdisp)
name|info_window_update
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|InfoWinData
modifier|*
name|iwd
decl_stmt|;
name|gint
name|type
decl_stmt|;
name|gdouble
name|unit_factor
decl_stmt|;
name|gint
name|unit_digits
decl_stmt|;
name|gchar
name|format_buf
index|[
literal|32
index|]
decl_stmt|;
name|InfoDialog
modifier|*
name|info_win
init|=
name|gdisp
operator|->
name|window_info_dialog
decl_stmt|;
if|if
condition|(
operator|!
name|info_win
operator|&&
name|info_window_auto
operator|!=
name|NULL
condition|)
block|{
name|info_win
operator|=
name|info_window_auto
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|info_win
condition|)
return|return;
name|iwd
operator|=
operator|(
name|InfoWinData
operator|*
operator|)
name|info_win
operator|->
name|user_data
expr_stmt|;
comment|/* Make it sensitive... */
if|if
condition|(
name|info_window_auto
condition|)
name|gtk_widget_set_sensitive
argument_list|(
name|info_window_auto
operator|->
name|vbox
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
comment|/* If doing info_window_auto then return if this display    * is not the one we are showing.    */
if|if
condition|(
name|info_window_auto
operator|&&
name|iwd
operator|->
name|gdisp
operator|!=
name|gdisp
condition|)
return|return;
comment|/*  width and height  */
name|unit_factor
operator|=
name|gimp_unit_get_factor
argument_list|(
name|gdisp
operator|->
name|gimage
operator|->
name|unit
argument_list|)
expr_stmt|;
name|unit_digits
operator|=
name|gimp_unit_get_digits
argument_list|(
name|gdisp
operator|->
name|gimage
operator|->
name|unit
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|iwd
operator|->
name|dimensions_str
argument_list|,
name|MAX_BUF
argument_list|,
name|_
argument_list|(
literal|"%d x %d pixels"
argument_list|)
argument_list|,
operator|(
name|int
operator|)
name|gdisp
operator|->
name|gimage
operator|->
name|width
argument_list|,
operator|(
name|int
operator|)
name|gdisp
operator|->
name|gimage
operator|->
name|height
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|format_buf
argument_list|,
sizeof|sizeof
argument_list|(
name|format_buf
argument_list|)
argument_list|,
literal|"%%.%df x %%.%df %s"
argument_list|,
name|unit_digits
operator|+
literal|1
argument_list|,
name|unit_digits
operator|+
literal|1
argument_list|,
name|gimp_unit_get_plural
argument_list|(
name|gdisp
operator|->
name|gimage
operator|->
name|unit
argument_list|)
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|iwd
operator|->
name|real_dimensions_str
argument_list|,
name|MAX_BUF
argument_list|,
name|format_buf
argument_list|,
name|gdisp
operator|->
name|gimage
operator|->
name|width
operator|*
name|unit_factor
operator|/
name|gdisp
operator|->
name|gimage
operator|->
name|xresolution
argument_list|,
name|gdisp
operator|->
name|gimage
operator|->
name|height
operator|*
name|unit_factor
operator|/
name|gdisp
operator|->
name|gimage
operator|->
name|yresolution
argument_list|)
expr_stmt|;
comment|/*  image resolution  */
name|g_snprintf
argument_list|(
name|iwd
operator|->
name|resolution_str
argument_list|,
name|MAX_BUF
argument_list|,
literal|"%g x %g dpi"
argument_list|,
name|gdisp
operator|->
name|gimage
operator|->
name|xresolution
argument_list|,
name|gdisp
operator|->
name|gimage
operator|->
name|yresolution
argument_list|)
expr_stmt|;
comment|/*  user zoom ratio  */
name|g_snprintf
argument_list|(
name|iwd
operator|->
name|scale_str
argument_list|,
name|MAX_BUF
argument_list|,
literal|"%d:%d"
argument_list|,
name|SCALEDEST
argument_list|(
name|gdisp
argument_list|)
argument_list|,
name|SCALESRC
argument_list|(
name|gdisp
argument_list|)
argument_list|)
expr_stmt|;
name|type
operator|=
name|gimage_base_type
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
comment|/*  color type  */
if|if
condition|(
name|type
operator|==
name|RGB
condition|)
name|g_snprintf
argument_list|(
name|iwd
operator|->
name|color_type_str
argument_list|,
name|MAX_BUF
argument_list|,
literal|"%s"
argument_list|,
name|_
argument_list|(
literal|"RGB Color"
argument_list|)
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|type
operator|==
name|GRAY
condition|)
name|g_snprintf
argument_list|(
name|iwd
operator|->
name|color_type_str
argument_list|,
name|MAX_BUF
argument_list|,
literal|"%s"
argument_list|,
name|_
argument_list|(
literal|"Grayscale"
argument_list|)
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|type
operator|==
name|INDEXED
condition|)
name|g_snprintf
argument_list|(
name|iwd
operator|->
name|color_type_str
argument_list|,
name|MAX_BUF
argument_list|,
literal|"%s (%d %s)"
argument_list|,
name|_
argument_list|(
literal|"Indexed Color"
argument_list|)
argument_list|,
name|gdisp
operator|->
name|gimage
operator|->
name|num_cols
argument_list|,
name|_
argument_list|(
literal|"colors"
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  visual class  */
if|if
condition|(
name|type
operator|==
name|RGB
operator|||
name|type
operator|==
name|INDEXED
condition|)
name|g_snprintf
argument_list|(
name|iwd
operator|->
name|visual_class_str
argument_list|,
name|MAX_BUF
argument_list|,
literal|"%s"
argument_list|,
name|visual_classes
index|[
name|g_visual
operator|->
name|type
index|]
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|type
operator|==
name|GRAY
condition|)
name|g_snprintf
argument_list|(
name|iwd
operator|->
name|visual_class_str
argument_list|,
name|MAX_BUF
argument_list|,
literal|"%s"
argument_list|,
name|visual_classes
index|[
name|g_visual
operator|->
name|type
index|]
argument_list|)
expr_stmt|;
comment|/*  visual depth  */
name|g_snprintf
argument_list|(
name|iwd
operator|->
name|visual_depth_str
argument_list|,
name|MAX_BUF
argument_list|,
literal|"%d"
argument_list|,
name|gdisp
operator|->
name|depth
argument_list|)
expr_stmt|;
name|info_dialog_update
argument_list|(
name|info_win
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

