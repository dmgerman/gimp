begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library                                                     * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball                  *  * gimpwidgets.h  * Copyright (C) 2000 Michael Natterer<mitch@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.               *                                                                                * This library is distributed in the hope that it will be useful,                * but WITHOUT ANY WARRANTY; without even the implied warranty of                 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU              * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_WIDGETS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_WIDGETS_H__
define|#
directive|define
name|__GIMP_WIDGETS_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|__cplusplus
end_ifdef

begin_extern
extern|extern
literal|"C"
block|{
endif|#
directive|endif
comment|/*  *  Widget Constructors  */
name|GtkWidget
modifier|*
name|gimp_option_menu_new
parameter_list|(
name|GtkSignalFunc
name|menu_item_callback
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|gpointer
name|initial
parameter_list|,
comment|/* user_data */
comment|/* specify menu items as va_list: 				     *  gchar          *label, 				     *  gpointer        user_data, 				     *  GtkWidget     **widget_ptr, 				     */
modifier|...
parameter_list|)
function_decl|;
name|GtkWidget
modifier|*
name|gimp_radio_group_new
parameter_list|(
name|gboolean
name|in_frame
parameter_list|,
name|gchar
modifier|*
name|frame_title
parameter_list|,
comment|/* specify radio buttons as va_list: 				     *  gchar          *label, 				     *  GtkSignalFunc   callback, 				     *  gpointer        data, 				     *  gpointer        user_data, 				     *  GtkWidget     **widget_ptr, 				     *  gboolean        active, 				     */
modifier|...
parameter_list|)
function_decl|;
name|GtkWidget
modifier|*
name|gimp_radio_group_new2
parameter_list|(
name|gboolean
name|in_frame
parameter_list|,
name|gchar
modifier|*
name|frame_title
parameter_list|,
name|GtkSignalFunc
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|gpointer
name|initial
parameter_list|,
comment|/* user_data */
comment|/* specify radio buttons as va_list: 				     *  gchar          *label, 				     *  gpointer        user_data, 				     *  GtkWidget     **widget_ptr, 				     */
modifier|...
parameter_list|)
function_decl|;
name|GtkWidget
modifier|*
name|gimp_spin_button_new
parameter_list|(
comment|/* return value: */
name|GtkObject
modifier|*
modifier|*
name|adjustment
parameter_list|,
name|gfloat
name|value
parameter_list|,
name|gfloat
name|lower
parameter_list|,
name|gfloat
name|upper
parameter_list|,
name|gfloat
name|step_increment
parameter_list|,
name|gfloat
name|page_increment
parameter_list|,
name|gfloat
name|page_size
parameter_list|,
name|gfloat
name|climb_rate
parameter_list|,
name|guint
name|digits
parameter_list|)
function_decl|;
name|GtkObject
modifier|*
name|gimp_scale_entry_new
parameter_list|(
name|GtkTable
modifier|*
name|table
parameter_list|,
name|gint
name|column
parameter_list|,
name|gint
name|row
parameter_list|,
name|gchar
modifier|*
name|text
parameter_list|,
name|gint
name|scale_usize
parameter_list|,
name|gint
name|spinbutton_usize
parameter_list|,
name|gfloat
name|value
parameter_list|,
name|gfloat
name|lower
parameter_list|,
name|gfloat
name|upper
parameter_list|,
name|gfloat
name|step_increment
parameter_list|,
name|gfloat
name|page_increment
parameter_list|,
name|guint
name|digits
parameter_list|,
name|gchar
modifier|*
name|tooltip
parameter_list|,
name|gchar
modifier|*
name|private_tip
parameter_list|)
function_decl|;
comment|/*  *  Standard Callbacks  */
name|void
name|gimp_toggle_button_update
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
name|void
name|gimp_menu_item_update
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
name|void
name|gimp_radio_button_update
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
name|void
name|gimp_int_adjustment_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
name|void
name|gimp_double_adjustment_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
name|void
name|gimp_unit_menu_update
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
comment|/*  *  Helper Functions  */
comment|/*  add aligned label& widget to a two-column table  */
name|void
name|gimp_table_attach_aligned
parameter_list|(
name|GtkTable
modifier|*
name|table
parameter_list|,
name|gint
name|row
parameter_list|,
name|gchar
modifier|*
name|text
parameter_list|,
name|gfloat
name|xalign
parameter_list|,
name|gfloat
name|yalign
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gboolean
name|left_adjust
parameter_list|)
function_decl|;
ifdef|#
directive|ifdef
name|__cplusplus
block|}
end_extern

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_WIDGETS_H__ */
end_comment

end_unit

