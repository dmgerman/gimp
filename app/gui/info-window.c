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
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"gui-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpcoreconfig.h"
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
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-projection.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-unit.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptemplate.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpunit.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcolorframe.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpviewabledialog.h"
end_include

begin_include
include|#
directive|include
file|"info-dialog.h"
end_include

begin_include
include|#
directive|include
file|"info-window.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
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
DECL|member|gdisp
name|GimpDisplay
modifier|*
name|gdisp
decl_stmt|;
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
DECL|member|num_layers_str
name|gchar
name|num_layers_str
index|[
name|MAX_BUF
index|]
decl_stmt|;
DECL|member|memsize_str
name|gchar
name|memsize_str
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
DECL|member|pixel_labels
name|GtkWidget
modifier|*
name|pixel_labels
index|[
literal|2
index|]
decl_stmt|;
DECL|member|unit_labels
name|GtkWidget
modifier|*
name|unit_labels
index|[
literal|2
index|]
decl_stmt|;
DECL|member|frame1
name|GtkWidget
modifier|*
name|frame1
decl_stmt|;
DECL|member|frame2
name|GtkWidget
modifier|*
name|frame2
decl_stmt|;
DECL|member|showing_extended
name|gboolean
name|showing_extended
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
specifier|const
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

begin_function
specifier|static
name|void
DECL|function|info_window_response (GtkWidget * widget,gint response_id,InfoDialog * info_win)
name|info_window_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|InfoDialog
modifier|*
name|info_win
parameter_list|)
block|{
name|info_dialog_hide
argument_list|(
name|info_win
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|info_window_page_switch (GtkWidget * widget,GtkNotebookPage * page,gint page_num,InfoDialog * info_win)
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
parameter_list|,
name|InfoDialog
modifier|*
name|info_win
parameter_list|)
block|{
name|InfoWinData
modifier|*
name|iwd
init|=
operator|(
name|InfoWinData
operator|*
operator|)
name|info_win
operator|->
name|user_data
decl_stmt|;
name|iwd
operator|->
name|showing_extended
operator|=
operator|(
name|page_num
operator|==
literal|1
operator|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  displays information:  *    cursor pos  *    cursor pos in real units  *    color under cursor  *  Can't we find a better place for this than in the image window? (Ralf)  */
end_comment

begin_function
specifier|static
name|void
DECL|function|info_window_create_extended (InfoDialog * info_win,Gimp * gimp)
name|info_window_create_extended
parameter_list|(
name|InfoDialog
modifier|*
name|info_win
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|InfoWinData
modifier|*
name|iwd
init|=
operator|(
name|InfoWinData
operator|*
operator|)
name|info_win
operator|->
name|user_data
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
literal|6
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
name|vbox
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
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
comment|/* cursor information */
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|TRUE
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
name|hbox
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
name|hbox
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Pixels"
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
name|frame
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
name|frame
argument_list|)
expr_stmt|;
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|2
argument_list|,
literal|2
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
literal|4
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
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
name|table
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
name|iwd
operator|->
name|pixel_labels
index|[
literal|0
index|]
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"n/a"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|iwd
operator|->
name|pixel_labels
index|[
literal|0
index|]
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gimp_table_attach_aligned
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
literal|"X:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|,
name|iwd
operator|->
name|pixel_labels
index|[
literal|0
index|]
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|iwd
operator|->
name|pixel_labels
index|[
literal|1
index|]
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"n/a"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|iwd
operator|->
name|pixel_labels
index|[
literal|1
index|]
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gimp_table_attach_aligned
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|_
argument_list|(
literal|"Y:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|,
name|iwd
operator|->
name|pixel_labels
index|[
literal|1
index|]
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Units"
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
name|frame
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
name|frame
argument_list|)
expr_stmt|;
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|2
argument_list|,
literal|2
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
literal|4
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
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
name|table
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
name|iwd
operator|->
name|unit_labels
index|[
literal|0
index|]
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"n/a"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|iwd
operator|->
name|unit_labels
index|[
literal|0
index|]
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gimp_table_attach_aligned
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
literal|"X:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|,
name|iwd
operator|->
name|unit_labels
index|[
literal|0
index|]
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|iwd
operator|->
name|unit_labels
index|[
literal|1
index|]
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"n/a"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|iwd
operator|->
name|unit_labels
index|[
literal|1
index|]
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gimp_table_attach_aligned
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|_
argument_list|(
literal|"Y:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|,
name|iwd
operator|->
name|unit_labels
index|[
literal|1
index|]
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/* color information */
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|TRUE
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
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
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
name|iwd
operator|->
name|frame1
operator|=
name|gimp_color_frame_new
argument_list|()
expr_stmt|;
name|gimp_color_frame_set_mode
argument_list|(
name|GIMP_COLOR_FRAME
argument_list|(
name|iwd
operator|->
name|frame1
argument_list|)
argument_list|,
name|GIMP_COLOR_FRAME_MODE_PIXEL
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|iwd
operator|->
name|frame1
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
name|iwd
operator|->
name|frame1
argument_list|)
expr_stmt|;
name|iwd
operator|->
name|frame2
operator|=
name|gimp_color_frame_new
argument_list|()
expr_stmt|;
name|gimp_color_frame_set_mode
argument_list|(
name|GIMP_COLOR_FRAME
argument_list|(
name|iwd
operator|->
name|frame2
argument_list|)
argument_list|,
name|GIMP_COLOR_FRAME_MODE_RGB
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|iwd
operator|->
name|frame2
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
name|iwd
operator|->
name|frame2
argument_list|)
expr_stmt|;
comment|/* Set back to first page */
name|gtk_notebook_set_current_page
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
name|g_signal_connect
argument_list|(
name|info_win
operator|->
name|info_notebook
argument_list|,
literal|"switch_page"
argument_list|,
name|G_CALLBACK
argument_list|(
name|info_window_page_switch
argument_list|)
argument_list|,
name|info_win
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|InfoDialog
modifier|*
DECL|function|info_window_create (GimpDisplay * gdisp)
name|info_window_create
parameter_list|(
name|GimpDisplay
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
name|gint
name|type
decl_stmt|;
name|type
operator|=
name|gimp_image_base_type
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
name|info_win
operator|=
name|info_dialog_notebook_new
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Info Window"
argument_list|)
argument_list|,
literal|"gimp-info-window"
argument_list|,
name|GIMP_STOCK_INFO
argument_list|,
name|_
argument_list|(
literal|"Image Information"
argument_list|)
argument_list|,
name|gdisp
operator|->
name|shell
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|GIMP_HELP_INFO_DIALOG
argument_list|)
expr_stmt|;
name|gtk_dialog_add_button
argument_list|(
name|GTK_DIALOG
argument_list|(
name|info_win
operator|->
name|shell
argument_list|)
argument_list|,
name|GTK_STOCK_CLOSE
argument_list|,
name|GTK_RESPONSE_CLOSE
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|info_win
operator|->
name|shell
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|info_window_response
argument_list|)
argument_list|,
name|info_win
argument_list|)
expr_stmt|;
name|iwd
operator|=
name|g_new0
argument_list|(
name|InfoWinData
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|iwd
operator|->
name|gdisp
operator|=
name|gdisp
expr_stmt|;
name|info_win
operator|->
name|user_data
operator|=
name|iwd
expr_stmt|;
comment|/*  add the information fields  */
name|info_dialog_add_label
argument_list|(
name|info_win
argument_list|,
name|_
argument_list|(
literal|"Pixel Dimensions:"
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
name|_
argument_list|(
literal|"Print Size:"
argument_list|)
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
literal|"Number of Layers:"
argument_list|)
argument_list|,
name|iwd
operator|->
name|num_layers_str
argument_list|)
expr_stmt|;
name|info_dialog_add_label
argument_list|(
name|info_win
argument_list|,
name|_
argument_list|(
literal|"Size in Memory:"
argument_list|)
argument_list|,
name|iwd
operator|->
name|memsize_str
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
comment|/*  Add extra tabs  */
name|info_window_create_extended
argument_list|(
name|info_win
argument_list|,
name|gdisp
operator|->
name|gimage
operator|->
name|gimp
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
name|void
DECL|function|info_window_change_display (GimpContext * context,GimpDisplay * newdisp,gpointer data)
name|info_window_change_display
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpDisplay
modifier|*
name|newdisp
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|gdisp
init|=
name|newdisp
decl_stmt|;
name|GimpDisplay
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
name|GimpDisplay
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
return|return;
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
name|gimp_container_have
argument_list|(
name|context
operator|->
name|gimp
operator|->
name|images
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|gimage
argument_list|)
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
DECL|function|info_window_follow_auto (Gimp * gimp)
name|info_window_follow_auto
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpDisplay
modifier|*
name|gdisp
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|context
operator|=
name|gimp_get_user_context
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|gdisp
operator|=
name|gimp_context_get_display
argument_list|(
name|context
argument_list|)
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
name|gdisp
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|context
argument_list|,
literal|"display_changed"
argument_list|,
name|G_CALLBACK
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
block|}
name|info_dialog_present
argument_list|(
name|info_window_auto
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* Updates all extended information. */
end_comment

begin_function
name|void
DECL|function|info_window_update_extended (GimpDisplay * gdisp,gdouble tx,gdouble ty)
name|info_window_update_extended
parameter_list|(
name|GimpDisplay
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
name|InfoDialog
modifier|*
name|info_win
decl_stmt|;
name|InfoWinData
modifier|*
name|iwd
decl_stmt|;
name|guchar
modifier|*
name|color
decl_stmt|;
name|info_win
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
operator|->
name|info_dialog
expr_stmt|;
if|if
condition|(
operator|!
name|info_win
operator|&&
name|info_window_auto
operator|!=
name|NULL
condition|)
name|info_win
operator|=
name|info_window_auto
expr_stmt|;
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
name|info_window_auto
condition|)
block|{
name|gimp_viewable_dialog_set_viewable
argument_list|(
name|GIMP_VIEWABLE_DIALOG
argument_list|(
name|info_window_auto
operator|->
name|shell
argument_list|)
argument_list|,
name|GIMP_VIEWABLE
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|iwd
operator|->
name|gdisp
operator|!=
name|gdisp
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
if|if
condition|(
operator|!
name|iwd
operator|||
operator|!
name|iwd
operator|->
name|showing_extended
condition|)
return|return;
comment|/* fill in position information */
if|if
condition|(
name|tx
operator|<
literal|0.0
operator|&&
name|ty
operator|<
literal|0.0
condition|)
block|{
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|iwd
operator|->
name|pixel_labels
index|[
literal|0
index|]
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"n/a"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|iwd
operator|->
name|pixel_labels
index|[
literal|1
index|]
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"n/a"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|iwd
operator|->
name|unit_labels
index|[
literal|0
index|]
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"n/a"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|iwd
operator|->
name|unit_labels
index|[
literal|1
index|]
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"n/a"
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gdouble
name|unit_factor
decl_stmt|;
name|gint
name|unit_digits
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|unit_str
decl_stmt|;
name|gchar
name|format_buf
index|[
literal|32
index|]
decl_stmt|;
name|gchar
name|buf
index|[
literal|32
index|]
decl_stmt|;
name|unit_factor
operator|=
name|gimp_image_unit_get_factor
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
name|unit_digits
operator|=
name|gimp_image_unit_get_digits
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
name|unit_str
operator|=
name|gimp_image_unit_get_abbreviation
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
name|buf
argument_list|)
argument_list|,
literal|"%d"
argument_list|,
operator|(
name|gint
operator|)
name|tx
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|iwd
operator|->
name|pixel_labels
index|[
literal|0
index|]
argument_list|)
argument_list|,
name|buf
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
name|buf
argument_list|)
argument_list|,
literal|"%d"
argument_list|,
operator|(
name|gint
operator|)
name|ty
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|iwd
operator|->
name|pixel_labels
index|[
literal|1
index|]
argument_list|)
argument_list|,
name|buf
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
literal|"%%.%df %s"
argument_list|,
name|unit_digits
argument_list|,
name|unit_str
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
name|buf
argument_list|)
argument_list|,
name|format_buf
argument_list|,
name|tx
operator|*
name|unit_factor
operator|/
name|gdisp
operator|->
name|gimage
operator|->
name|xresolution
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|iwd
operator|->
name|unit_labels
index|[
literal|0
index|]
argument_list|)
argument_list|,
name|buf
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
name|buf
argument_list|)
argument_list|,
name|format_buf
argument_list|,
name|ty
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
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|iwd
operator|->
name|unit_labels
index|[
literal|1
index|]
argument_list|)
argument_list|,
name|buf
argument_list|)
expr_stmt|;
block|}
comment|/* fill in color information */
name|color
operator|=
name|gimp_image_projection_get_color_at
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|tx
argument_list|,
name|ty
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|color
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
name|gimp_color_frame_set_invalid
argument_list|(
name|GIMP_COLOR_FRAME
argument_list|(
name|iwd
operator|->
name|frame1
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_color_frame_set_invalid
argument_list|(
name|GIMP_COLOR_FRAME
argument_list|(
name|iwd
operator|->
name|frame2
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GimpImageType
name|sample_type
decl_stmt|;
name|GimpRGB
name|rgb
decl_stmt|;
name|sample_type
operator|=
name|gimp_image_projection_type
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
name|gimp_rgba_set_uchar
argument_list|(
operator|&
name|rgb
argument_list|,
name|color
index|[
name|RED_PIX
index|]
argument_list|,
name|color
index|[
name|GREEN_PIX
index|]
argument_list|,
name|color
index|[
name|BLUE_PIX
index|]
argument_list|,
name|color
index|[
name|ALPHA_PIX
index|]
argument_list|)
expr_stmt|;
name|gimp_color_frame_set_color
argument_list|(
name|GIMP_COLOR_FRAME
argument_list|(
name|iwd
operator|->
name|frame1
argument_list|)
argument_list|,
name|sample_type
argument_list|,
operator|&
name|rgb
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gimp_color_frame_set_color
argument_list|(
name|GIMP_COLOR_FRAME
argument_list|(
name|iwd
operator|->
name|frame2
argument_list|)
argument_list|,
name|sample_type
argument_list|,
operator|&
name|rgb
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|color
argument_list|)
expr_stmt|;
block|}
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
DECL|function|info_window_update (GimpDisplay * gdisp)
name|info_window_update
parameter_list|(
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
init|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
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
name|GimpUnit
name|res_unit
decl_stmt|;
name|gdouble
name|res_unit_factor
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
decl_stmt|;
name|info_win
operator|=
name|shell
operator|->
name|info_dialog
expr_stmt|;
if|if
condition|(
operator|!
name|info_win
operator|&&
name|info_window_auto
operator|!=
name|NULL
condition|)
name|info_win
operator|=
name|info_window_auto
expr_stmt|;
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
name|gimage
operator|=
name|gdisp
operator|->
name|gimage
expr_stmt|;
comment|/*  width and height  */
name|unit_factor
operator|=
name|gimp_image_unit_get_factor
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|unit_digits
operator|=
name|gimp_image_unit_get_digits
argument_list|(
name|gimage
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
name|gimage
operator|->
name|width
argument_list|,
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
name|gimp_image_unit_get_plural
argument_list|(
name|gimage
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
name|gimage
operator|->
name|width
operator|*
name|unit_factor
operator|/
name|gimage
operator|->
name|xresolution
argument_list|,
name|gimage
operator|->
name|height
operator|*
name|unit_factor
operator|/
name|gimage
operator|->
name|yresolution
argument_list|)
expr_stmt|;
comment|/*  image resolution  */
name|res_unit
operator|=
name|gimage
operator|->
name|gimp
operator|->
name|config
operator|->
name|default_image
operator|->
name|resolution_unit
expr_stmt|;
name|res_unit_factor
operator|=
name|_gimp_unit_get_factor
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|,
name|res_unit
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
name|_
argument_list|(
literal|"pixels/%s"
argument_list|)
argument_list|,
name|_gimp_unit_get_abbreviation
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|,
name|res_unit
argument_list|)
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|iwd
operator|->
name|resolution_str
argument_list|,
name|MAX_BUF
argument_list|,
name|_
argument_list|(
literal|"%g x %g %s"
argument_list|)
argument_list|,
name|gimage
operator|->
name|xresolution
operator|/
name|res_unit_factor
argument_list|,
name|gimage
operator|->
name|yresolution
operator|/
name|res_unit_factor
argument_list|,
name|res_unit
operator|==
name|GIMP_UNIT_INCH
condition|?
name|_
argument_list|(
literal|"dpi"
argument_list|)
else|:
name|format_buf
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
literal|"%.2f"
argument_list|,
name|shell
operator|->
name|scale
operator|*
literal|100
argument_list|)
expr_stmt|;
comment|/*  number of layers  */
name|g_snprintf
argument_list|(
name|iwd
operator|->
name|num_layers_str
argument_list|,
name|MAX_BUF
argument_list|,
literal|"%d"
argument_list|,
name|gimp_container_num_children
argument_list|(
name|gimage
operator|->
name|layers
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  size in memory  */
block|{
name|GimpObject
modifier|*
name|object
init|=
name|GIMP_OBJECT
argument_list|(
name|gimage
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|str
decl_stmt|;
name|str
operator|=
name|gimp_memsize_to_string
argument_list|(
name|gimp_object_get_memsize
argument_list|(
name|object
argument_list|,
name|NULL
argument_list|)
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|iwd
operator|->
name|memsize_str
argument_list|,
name|MAX_BUF
argument_list|,
literal|"%s"
argument_list|,
name|str
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|str
argument_list|)
expr_stmt|;
block|}
name|type
operator|=
name|gimp_image_base_type
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
comment|/*  color type  */
switch|switch
condition|(
name|type
condition|)
block|{
case|case
name|GIMP_RGB
case|:
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
break|break;
case|case
name|GIMP_GRAY
case|:
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
break|break;
case|case
name|GIMP_INDEXED
case|:
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
break|break;
block|}
block|{
name|GdkScreen
modifier|*
name|screen
decl_stmt|;
name|GdkVisual
modifier|*
name|visual
decl_stmt|;
name|screen
operator|=
name|gtk_widget_get_screen
argument_list|(
name|GTK_WIDGET
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|visual
operator|=
name|gdk_screen_get_rgb_visual
argument_list|(
name|screen
argument_list|)
expr_stmt|;
comment|/*  visual class  */
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
name|gettext
argument_list|(
name|visual_classes
index|[
name|visual
operator|->
name|type
index|]
argument_list|)
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
name|visual
operator|->
name|depth
argument_list|)
expr_stmt|;
block|}
name|info_dialog_update
argument_list|(
name|info_win
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

