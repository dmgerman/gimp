begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/*  * dbbrowser_utils.c  * 0.08  26th sept 97  by Thomas NOEL<thomas@minet.net>  *  * 98/12/13  Sven Neumann<sven@gimp.org> : added help display  */
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
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpui.h>
end_include

begin_include
include|#
directive|include
file|"gimpprocview.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|GtkWidget
modifier|*
name|gimp_proc_view_create_params
parameter_list|(
name|GimpParamDef
modifier|*
name|params
parameter_list|,
name|gint
name|n_params
parameter_list|,
name|GtkSizeGroup
modifier|*
name|name_group
parameter_list|,
name|GtkSizeGroup
modifier|*
name|type_group
parameter_list|,
name|GtkSizeGroup
modifier|*
name|desc_group
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
specifier|const
name|gchar
modifier|*
name|GParamType_to_string
parameter_list|(
name|GimpPDBArgType
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
specifier|const
name|gchar
modifier|*
name|GimpPDBProcType_to_string
parameter_list|(
name|GimpPDBProcType
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_proc_view_new (const gchar * name,const gchar * menu_path,const gchar * blurb,const gchar * help,const gchar * author,const gchar * copyright,const gchar * date,GimpPDBProcType type,gint n_params,gint n_return_vals,GimpParamDef * params,GimpParamDef * return_vals)
name|gimp_proc_view_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_path
parameter_list|,
specifier|const
name|gchar
modifier|*
name|blurb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help
parameter_list|,
specifier|const
name|gchar
modifier|*
name|author
parameter_list|,
specifier|const
name|gchar
modifier|*
name|copyright
parameter_list|,
specifier|const
name|gchar
modifier|*
name|date
parameter_list|,
name|GimpPDBProcType
name|type
parameter_list|,
name|gint
name|n_params
parameter_list|,
name|gint
name|n_return_vals
parameter_list|,
name|GimpParamDef
modifier|*
name|params
parameter_list|,
name|GimpParamDef
modifier|*
name|return_vals
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|main_vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkSizeGroup
modifier|*
name|name_group
decl_stmt|;
name|GtkSizeGroup
modifier|*
name|type_group
decl_stmt|;
name|GtkSizeGroup
modifier|*
name|desc_group
decl_stmt|;
name|gint
name|row
decl_stmt|;
if|if
condition|(
name|blurb
operator|&&
name|strlen
argument_list|(
name|blurb
argument_list|)
operator|<
literal|2
condition|)
name|blurb
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|help
operator|&&
name|strlen
argument_list|(
name|help
argument_list|)
operator|<
literal|2
condition|)
name|help
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|author
operator|&&
name|strlen
argument_list|(
name|author
argument_list|)
operator|<
literal|2
condition|)
name|author
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|date
operator|&&
name|strlen
argument_list|(
name|date
argument_list|)
operator|<
literal|2
condition|)
name|date
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|copyright
operator|&&
name|strlen
argument_list|(
name|copyright
argument_list|)
operator|<
literal|2
condition|)
name|copyright
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|blurb
operator|&&
name|help
operator|&&
operator|!
name|strcmp
argument_list|(
name|blurb
argument_list|,
name|help
argument_list|)
condition|)
name|help
operator|=
name|NULL
expr_stmt|;
name|main_vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|12
argument_list|)
expr_stmt|;
comment|/* show the name */
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_frame_get_label_widget
argument_list|(
name|GTK_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_label_set_selectable
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
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
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|8
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|GimpPDBProcType_to_string
argument_list|(
name|type
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_label_set_attributes
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|PANGO_ATTR_STYLE
argument_list|,
name|PANGO_STYLE_ITALIC
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
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
if|if
condition|(
name|menu_path
condition|)
block|{
name|label
operator|=
name|gtk_label_new_with_mnemonic
argument_list|(
name|menu_path
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_label_set_line_wrap
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
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
block|}
if|if
condition|(
name|blurb
condition|)
block|{
name|label
operator|=
name|gtk_label_new
argument_list|(
name|blurb
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_label_set_line_wrap
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
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
block|}
name|name_group
operator|=
name|gtk_size_group_new
argument_list|(
name|GTK_SIZE_GROUP_HORIZONTAL
argument_list|)
expr_stmt|;
name|type_group
operator|=
name|gtk_size_group_new
argument_list|(
name|GTK_SIZE_GROUP_HORIZONTAL
argument_list|)
expr_stmt|;
name|desc_group
operator|=
name|gtk_size_group_new
argument_list|(
name|GTK_SIZE_GROUP_HORIZONTAL
argument_list|)
expr_stmt|;
comment|/* in parameters */
if|if
condition|(
name|n_params
condition|)
block|{
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Parameters"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
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
name|table
operator|=
name|gimp_proc_view_create_params
argument_list|(
name|params
argument_list|,
name|n_params
argument_list|,
name|name_group
argument_list|,
name|type_group
argument_list|,
name|desc_group
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
block|}
comment|/* out parameters */
if|if
condition|(
name|n_return_vals
condition|)
block|{
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Return Values"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
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
name|table
operator|=
name|gimp_proc_view_create_params
argument_list|(
name|return_vals
argument_list|,
name|n_return_vals
argument_list|,
name|name_group
argument_list|,
name|type_group
argument_list|,
name|desc_group
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
block|}
if|if
condition|(
operator|!
name|help
operator|&&
operator|!
name|author
operator|&&
operator|!
name|date
operator|&&
operator|!
name|copyright
condition|)
return|return
name|main_vbox
return|;
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Additional Information"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
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
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|8
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
comment|/* show the help */
if|if
condition|(
name|help
condition|)
block|{
name|label
operator|=
name|gtk_label_new
argument_list|(
name|help
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_label_set_line_wrap
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
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
block|}
comment|/* show the author& the copyright */
if|if
condition|(
operator|!
name|author
operator|&&
operator|!
name|date
operator|&&
operator|!
name|copyright
condition|)
return|return
name|main_vbox
return|;
name|table
operator|=
name|gtk_table_new
argument_list|(
operator|(
name|author
operator|!=
literal|0
operator|)
operator|+
operator|(
name|date
operator|!=
literal|0
operator|)
operator|+
operator|(
name|copyright
operator|!=
literal|0
operator|)
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
literal|6
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
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
name|row
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|author
condition|)
block|{
name|label
operator|=
name|gtk_label_new
argument_list|(
name|author
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_label_set_line_wrap
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|TRUE
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
name|row
operator|++
argument_list|,
name|_
argument_list|(
literal|"Author:"
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
name|label
argument_list|,
literal|3
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|date
condition|)
block|{
name|label
operator|=
name|gtk_label_new
argument_list|(
name|date
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_label_set_line_wrap
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|TRUE
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
name|row
operator|++
argument_list|,
name|_
argument_list|(
literal|"Date:"
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
name|label
argument_list|,
literal|3
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|copyright
condition|)
block|{
name|label
operator|=
name|gtk_label_new
argument_list|(
name|copyright
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_label_set_line_wrap
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|TRUE
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
name|row
operator|++
argument_list|,
name|_
argument_list|(
literal|"Copyright:"
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
name|label
argument_list|,
literal|3
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
return|return
name|main_vbox
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|gimp_proc_view_create_params (GimpParamDef * params,gint n_params,GtkSizeGroup * name_group,GtkSizeGroup * type_group,GtkSizeGroup * desc_group)
name|gimp_proc_view_create_params
parameter_list|(
name|GimpParamDef
modifier|*
name|params
parameter_list|,
name|gint
name|n_params
parameter_list|,
name|GtkSizeGroup
modifier|*
name|name_group
parameter_list|,
name|GtkSizeGroup
modifier|*
name|type_group
parameter_list|,
name|GtkSizeGroup
modifier|*
name|desc_group
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|type
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|table
operator|=
name|gtk_table_new
argument_list|(
name|n_params
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
literal|6
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|4
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_params
condition|;
name|i
operator|++
control|)
block|{
comment|/* name */
name|label
operator|=
name|gtk_label_new
argument_list|(
name|params
index|[
name|i
index|]
operator|.
name|name
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_size_group_add_widget
argument_list|(
name|name_group
argument_list|,
name|label
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|label
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|i
argument_list|,
name|i
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
comment|/* type */
name|type
operator|=
name|GParamType_to_string
argument_list|(
name|params
index|[
name|i
index|]
operator|.
name|type
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|type
argument_list|)
expr_stmt|;
name|gimp_label_set_attributes
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|PANGO_ATTR_FAMILY
argument_list|,
literal|"monospace"
argument_list|,
name|PANGO_ATTR_STYLE
argument_list|,
name|PANGO_STYLE_ITALIC
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_size_group_add_widget
argument_list|(
name|type_group
argument_list|,
name|label
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|label
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
name|i
argument_list|,
name|i
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
comment|/* description */
name|label
operator|=
name|gtk_label_new
argument_list|(
name|params
index|[
name|i
index|]
operator|.
name|description
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_label_set_line_wrap
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_size_group_add_widget
argument_list|(
name|desc_group
argument_list|,
name|label
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|label
argument_list|,
literal|2
argument_list|,
literal|3
argument_list|,
name|i
argument_list|,
name|i
operator|+
literal|1
argument_list|,
name|GTK_SHRINK
operator||
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
block|}
return|return
name|table
return|;
block|}
end_function

begin_function
specifier|static
specifier|const
name|gchar
modifier|*
DECL|function|GParamType_to_string (GimpPDBArgType type)
name|GParamType_to_string
parameter_list|(
name|GimpPDBArgType
name|type
parameter_list|)
block|{
switch|switch
condition|(
name|type
condition|)
block|{
case|case
name|GIMP_PDB_INT32
case|:
return|return
literal|"INT32"
return|;
case|case
name|GIMP_PDB_INT16
case|:
return|return
literal|"INT16"
return|;
case|case
name|GIMP_PDB_INT8
case|:
return|return
literal|"INT8"
return|;
case|case
name|GIMP_PDB_FLOAT
case|:
return|return
literal|"FLOAT"
return|;
case|case
name|GIMP_PDB_STRING
case|:
return|return
literal|"STRING"
return|;
case|case
name|GIMP_PDB_INT32ARRAY
case|:
return|return
literal|"INT32ARRAY"
return|;
case|case
name|GIMP_PDB_INT16ARRAY
case|:
return|return
literal|"INT16ARRAY"
return|;
case|case
name|GIMP_PDB_INT8ARRAY
case|:
return|return
literal|"INT8ARRAY"
return|;
case|case
name|GIMP_PDB_FLOATARRAY
case|:
return|return
literal|"FLOATARRAY"
return|;
case|case
name|GIMP_PDB_STRINGARRAY
case|:
return|return
literal|"STRINGARRAY"
return|;
case|case
name|GIMP_PDB_COLOR
case|:
return|return
literal|"COLOR"
return|;
case|case
name|GIMP_PDB_REGION
case|:
return|return
literal|"REGION"
return|;
case|case
name|GIMP_PDB_DISPLAY
case|:
return|return
literal|"DISPLAY"
return|;
case|case
name|GIMP_PDB_IMAGE
case|:
return|return
literal|"IMAGE"
return|;
case|case
name|GIMP_PDB_LAYER
case|:
return|return
literal|"LAYER"
return|;
case|case
name|GIMP_PDB_CHANNEL
case|:
return|return
literal|"CHANNEL"
return|;
case|case
name|GIMP_PDB_DRAWABLE
case|:
return|return
literal|"DRAWABLE"
return|;
case|case
name|GIMP_PDB_SELECTION
case|:
return|return
literal|"SELECTION"
return|;
case|case
name|GIMP_PDB_BOUNDARY
case|:
return|return
literal|"BOUNDARY"
return|;
case|case
name|GIMP_PDB_PATH
case|:
return|return
literal|"PATH"
return|;
case|case
name|GIMP_PDB_PARASITE
case|:
return|return
literal|"PARASITE"
return|;
case|case
name|GIMP_PDB_STATUS
case|:
return|return
literal|"STATUS"
return|;
case|case
name|GIMP_PDB_END
case|:
return|return
literal|"END"
return|;
default|default:
return|return
literal|"UNKNOWN?"
return|;
block|}
block|}
end_function

begin_function
specifier|static
specifier|const
name|gchar
modifier|*
DECL|function|GimpPDBProcType_to_string (GimpPDBProcType type)
name|GimpPDBProcType_to_string
parameter_list|(
name|GimpPDBProcType
name|type
parameter_list|)
block|{
switch|switch
condition|(
name|type
condition|)
block|{
case|case
name|GIMP_INTERNAL
case|:
return|return
name|_
argument_list|(
literal|"Internal GIMP procedure"
argument_list|)
return|;
case|case
name|GIMP_PLUGIN
case|:
return|return
name|_
argument_list|(
literal|"GIMP Plug-In"
argument_list|)
return|;
case|case
name|GIMP_EXTENSION
case|:
return|return
name|_
argument_list|(
literal|"GIMP Extension"
argument_list|)
return|;
case|case
name|GIMP_TEMPORARY
case|:
return|return
name|_
argument_list|(
literal|"Temporary Procedure"
argument_list|)
return|;
default|default:
return|return
literal|"UNKNOWN"
return|;
block|}
block|}
end_function

end_unit

