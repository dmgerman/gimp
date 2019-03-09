begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-2002 Maurits Rijk  lpeek.mrijk@consunet.nl  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  *  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
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
file|"imap_ui_grid.h"
end_include

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|add_widget_to_grid (GtkWidget * grid,gint row,gint col,GtkWidget * w)
name|add_widget_to_grid
parameter_list|(
name|GtkWidget
modifier|*
name|grid
parameter_list|,
name|gint
name|row
parameter_list|,
name|gint
name|col
parameter_list|,
name|GtkWidget
modifier|*
name|w
parameter_list|)
block|{
name|gtk_grid_attach
argument_list|(
name|GTK_GRID
argument_list|(
name|grid
argument_list|)
argument_list|,
name|w
argument_list|,
name|col
argument_list|,
name|row
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|w
argument_list|)
expr_stmt|;
return|return
name|w
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|create_spin_button_in_grid (GtkWidget * grid,GtkWidget * label,gint row,gint col,gint value,gint min,gint max)
name|create_spin_button_in_grid
parameter_list|(
name|GtkWidget
modifier|*
name|grid
parameter_list|,
name|GtkWidget
modifier|*
name|label
parameter_list|,
name|gint
name|row
parameter_list|,
name|gint
name|col
parameter_list|,
name|gint
name|value
parameter_list|,
name|gint
name|min
parameter_list|,
name|gint
name|max
parameter_list|)
block|{
name|GtkAdjustment
modifier|*
name|adj
init|=
name|gtk_adjustment_new
argument_list|(
name|value
argument_list|,
name|min
argument_list|,
name|max
argument_list|,
literal|1
argument_list|,
literal|10
argument_list|,
literal|0
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|button
init|=
name|gimp_spin_button_new
argument_list|(
name|adj
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|)
decl_stmt|;
name|gtk_spin_button_set_numeric
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
name|label
condition|)
name|gtk_label_set_mnemonic_widget
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|button
argument_list|)
expr_stmt|;
return|return
name|add_widget_to_grid
argument_list|(
name|grid
argument_list|,
name|row
argument_list|,
name|col
argument_list|,
name|button
argument_list|)
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|create_check_button_in_grid (GtkWidget * grid,gint row,gint col,const char * text)
name|create_check_button_in_grid
parameter_list|(
name|GtkWidget
modifier|*
name|grid
parameter_list|,
name|gint
name|row
parameter_list|,
name|gint
name|col
parameter_list|,
specifier|const
name|char
modifier|*
name|text
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|button
init|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|text
argument_list|)
decl_stmt|;
return|return
name|add_widget_to_grid
argument_list|(
name|grid
argument_list|,
name|row
argument_list|,
name|col
argument_list|,
name|button
argument_list|)
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|create_radio_button_in_grid (GtkWidget * grid,GSList * group,gint row,gint col,const char * text)
name|create_radio_button_in_grid
parameter_list|(
name|GtkWidget
modifier|*
name|grid
parameter_list|,
name|GSList
modifier|*
name|group
parameter_list|,
name|gint
name|row
parameter_list|,
name|gint
name|col
parameter_list|,
specifier|const
name|char
modifier|*
name|text
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|button
init|=
name|gtk_radio_button_new_with_mnemonic
argument_list|(
name|group
argument_list|,
name|text
argument_list|)
decl_stmt|;
return|return
name|add_widget_to_grid
argument_list|(
name|grid
argument_list|,
name|row
argument_list|,
name|col
argument_list|,
name|button
argument_list|)
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|create_label_in_grid (GtkWidget * grid,gint row,gint col,const char * text)
name|create_label_in_grid
parameter_list|(
name|GtkWidget
modifier|*
name|grid
parameter_list|,
name|gint
name|row
parameter_list|,
name|gint
name|col
parameter_list|,
specifier|const
name|char
modifier|*
name|text
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|label
init|=
name|gtk_label_new_with_mnemonic
argument_list|(
name|text
argument_list|)
decl_stmt|;
name|gtk_label_set_xalign
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
return|return
name|add_widget_to_grid
argument_list|(
name|grid
argument_list|,
name|row
argument_list|,
name|col
argument_list|,
name|label
argument_list|)
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|create_entry_in_grid (GtkWidget * grid,GtkWidget * label,gint row,gint col)
name|create_entry_in_grid
parameter_list|(
name|GtkWidget
modifier|*
name|grid
parameter_list|,
name|GtkWidget
modifier|*
name|label
parameter_list|,
name|gint
name|row
parameter_list|,
name|gint
name|col
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|entry
init|=
name|gtk_entry_new
argument_list|()
decl_stmt|;
if|if
condition|(
name|label
condition|)
name|gtk_label_set_mnemonic_widget
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|entry
argument_list|)
expr_stmt|;
return|return
name|add_widget_to_grid
argument_list|(
name|grid
argument_list|,
name|row
argument_list|,
name|col
argument_list|,
name|entry
argument_list|)
return|;
block|}
end_function

end_unit

