begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpwidgets.h  * Copyright (C) 2000 Michael Natterer<mitch@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
file|<libgimpwidgets/gimpwidgetstypes.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimpbutton.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimpchainbutton.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimpcolorarea.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimpcolorbutton.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimpdialog.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimpfileselection.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimphelpui.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimpoffsetarea.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimppatheditor.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimppixmap.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimpquerybox.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimpsizeentry.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimpstock.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimpunitmenu.h>
end_include

begin_function_decl
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
name|void
name|gimp_widgets_init
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  *  Widget Constructors  */
end_comment

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_option_menu_new
parameter_list|(
name|gboolean
name|menu_only
parameter_list|,
comment|/* specify menu items as va_list: 				     *  gchar          *label, 				     *  GCallback       callback, 				     *  gpointer        callback_data, 				     *  gpointer        item_data, 				     *  GtkWidget     **widget_ptr, 				     *  gboolean        active 				     */
modifier|...
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_option_menu_new2
parameter_list|(
name|gboolean
name|menu_only
parameter_list|,
name|GCallback
name|menu_item_callback
parameter_list|,
name|gpointer
name|menu_item_callback_data
parameter_list|,
name|gpointer
name|initial
parameter_list|,
comment|/* item_data */
comment|/* specify menu items as va_list: 				     *  gchar          *label, 				     *  gpointer        item_data, 				     *  GtkWidget     **widget_ptr, 				     */
modifier|...
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_option_menu_set_history
parameter_list|(
name|GtkOptionMenu
modifier|*
name|option_menu
parameter_list|,
name|gpointer
name|item_data
parameter_list|)
function_decl|;
end_function_decl

begin_typedef
DECL|typedef|GimpOptionMenuSensitivityCallback
typedef|typedef
name|gboolean
function_decl|(
modifier|*
name|GimpOptionMenuSensitivityCallback
function_decl|)
parameter_list|(
name|gpointer
name|item_data
parameter_list|,
name|gpointer
name|callback_data
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
name|void
name|gimp_option_menu_set_sensitive
parameter_list|(
name|GtkOptionMenu
modifier|*
name|option_menu
parameter_list|,
name|GimpOptionMenuSensitivityCallback
name|callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_radio_group_new
parameter_list|(
name|gboolean
name|in_frame
parameter_list|,
specifier|const
name|gchar
modifier|*
name|frame_title
parameter_list|,
comment|/* specify radio buttons as va_list: 				     *  const gchar    *label, 				     *  GCallback       callback, 				     *  gpointer        callback_data, 				     *  gpointer        item_data, 				     *  GtkWidget     **widget_ptr, 				     *  gboolean        active, 				     */
modifier|...
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_radio_group_new2
parameter_list|(
name|gboolean
name|in_frame
parameter_list|,
specifier|const
name|gchar
modifier|*
name|frame_title
parameter_list|,
name|GCallback
name|radio_button_callback
parameter_list|,
name|gpointer
name|radio_button_callback_data
parameter_list|,
name|gpointer
name|initial
parameter_list|,
comment|/* item_data */
comment|/* specify radio buttons as va_list: 				     *  const gchar    *label, 				     *  gpointer        item_data, 				     *  GtkWidget     **widget_ptr, 				     */
modifier|...
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_radio_group_set_active
parameter_list|(
name|GtkRadioButton
modifier|*
name|radio_button
parameter_list|,
name|gpointer
name|item_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
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
end_function_decl

begin_define
DECL|macro|GIMP_SCALE_ENTRY_LABEL (adj)
define|#
directive|define
name|GIMP_SCALE_ENTRY_LABEL
parameter_list|(
name|adj
parameter_list|)
define|\
value|(g_object_get_data (G_OBJECT (adj), "label"))
end_define

begin_define
DECL|macro|GIMP_SCALE_ENTRY_SCALE (adj)
define|#
directive|define
name|GIMP_SCALE_ENTRY_SCALE
parameter_list|(
name|adj
parameter_list|)
define|\
value|(g_object_get_data (G_OBJECT (adj), "scale"))
end_define

begin_define
DECL|macro|GIMP_SCALE_ENTRY_SCALE_ADJ (adj)
define|#
directive|define
name|GIMP_SCALE_ENTRY_SCALE_ADJ
parameter_list|(
name|adj
parameter_list|)
define|\
value|gtk_range_get_adjustment \         (GTK_RANGE (g_object_get_data (G_OBJECT (adj), "scale")))
end_define

begin_define
DECL|macro|GIMP_SCALE_ENTRY_SPINBUTTON (adj)
define|#
directive|define
name|GIMP_SCALE_ENTRY_SPINBUTTON
parameter_list|(
name|adj
parameter_list|)
define|\
value|(g_object_get_data (G_OBJECT (adj), "spinbutton"))
end_define

begin_define
DECL|macro|GIMP_SCALE_ENTRY_SPINBUTTON_ADJ (adj)
define|#
directive|define
name|GIMP_SCALE_ENTRY_SPINBUTTON_ADJ
parameter_list|(
name|adj
parameter_list|)
define|\
value|gtk_spin_button_get_adjustment \         (GTK_SPIN_BUTTON (g_object_get_data (G_OBJECT (adj), "spinbutton")))
end_define

begin_function_decl
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
specifier|const
name|gchar
modifier|*
name|text
parameter_list|,
name|gint
name|scale_width
parameter_list|,
name|gint
name|spinbutton_width
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
name|gboolean
name|constrain
parameter_list|,
name|gfloat
name|unconstrained_lower
parameter_list|,
name|gfloat
name|unconstrained_upper
parameter_list|,
specifier|const
name|gchar
modifier|*
name|tooltip
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_data
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|GIMP_RANDOM_SEED_SPINBUTTON (hbox)
define|#
directive|define
name|GIMP_RANDOM_SEED_SPINBUTTON
parameter_list|(
name|hbox
parameter_list|)
define|\
value|(g_object_get_data (G_OBJECT (hbox), "spinbutton"))
end_define

begin_define
DECL|macro|GIMP_RANDOM_SEED_SPINBUTTON_ADJ (hbox)
define|#
directive|define
name|GIMP_RANDOM_SEED_SPINBUTTON_ADJ
parameter_list|(
name|hbox
parameter_list|)
define|\
value|gtk_spin_button_get_adjustment \         (GTK_SPIN_BUTTON (g_object_get_data (G_OBJECT (hbox), "spinbutton")))
end_define

begin_define
DECL|macro|GIMP_RANDOM_SEED_TOGGLEBUTTON (hbox)
define|#
directive|define
name|GIMP_RANDOM_SEED_TOGGLEBUTTON
parameter_list|(
name|hbox
parameter_list|)
define|\
value|(g_object_get_data (G_OBJECT (hbox), "togglebutton"))
end_define

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_random_seed_new
parameter_list|(
name|gint
modifier|*
name|seed
parameter_list|,
name|gint
modifier|*
name|use_time
parameter_list|,
name|gint
name|time_true
parameter_list|,
name|gint
name|time_false
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|GIMP_COORDINATES_CHAINBUTTON (sizeentry)
define|#
directive|define
name|GIMP_COORDINATES_CHAINBUTTON
parameter_list|(
name|sizeentry
parameter_list|)
define|\
value|(g_object_get_data (G_OBJECT (sizeentry), "chainbutton"))
end_define

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_coordinates_new
parameter_list|(
name|GimpUnit
name|unit
parameter_list|,
specifier|const
name|gchar
modifier|*
name|unit_format
parameter_list|,
name|gboolean
name|menu_show_pixels
parameter_list|,
name|gboolean
name|menu_show_percent
parameter_list|,
name|gint
name|spinbutton_width
parameter_list|,
name|GimpSizeEntryUpdatePolicy
name|update_policy
parameter_list|,
name|gboolean
name|chainbutton_active
parameter_list|,
name|gboolean
name|chain_constrains_ratio
parameter_list|,
specifier|const
name|gchar
modifier|*
name|xlabel
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|xres
parameter_list|,
name|gdouble
name|lower_boundary_x
parameter_list|,
name|gdouble
name|upper_boundary_x
parameter_list|,
name|gdouble
name|xsize_0
parameter_list|,
comment|/* % */
name|gdouble
name|xsize_100
parameter_list|,
comment|/* % */
specifier|const
name|gchar
modifier|*
name|ylabel
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gdouble
name|yres
parameter_list|,
name|gdouble
name|lower_boundary_y
parameter_list|,
name|gdouble
name|upper_boundary_y
parameter_list|,
name|gdouble
name|ysize_0
parameter_list|,
comment|/* % */
name|gdouble
name|ysize_100
comment|/* % */
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|GIMP_MEMSIZE_ENTRY_SPINBUTTON (memsize)
define|#
directive|define
name|GIMP_MEMSIZE_ENTRY_SPINBUTTON
parameter_list|(
name|memsize
parameter_list|)
define|\
value|(g_object_get_data (G_OBJECT (memsize), "spinbutton"))
end_define

begin_define
DECL|macro|GIMP_MEMSIZE_ENTRY_SPINBUTTON_ADJ (memsize)
define|#
directive|define
name|GIMP_MEMSIZE_ENTRY_SPINBUTTON_ADJ
parameter_list|(
name|memsize
parameter_list|)
define|\
value|gtk_spin_button_get_adjustment \         (GTK_SPIN_BUTTON (g_object_get_data (G_OBJECT (memsize), "spinbutton")))
end_define

begin_define
DECL|macro|GIMP_MEMSIZE_ENTRY_OPTIONMENU (memsize)
define|#
directive|define
name|GIMP_MEMSIZE_ENTRY_OPTIONMENU
parameter_list|(
name|memsize
parameter_list|)
define|\
value|(g_object_get_data (G_OBJECT (memsize), "optionmenu"))
end_define

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_memsize_entry_new
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_pixmap_button_new
parameter_list|(
name|gchar
modifier|*
modifier|*
name|xpm_data
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  *  Standard Callbacks  */
end_comment

begin_function_decl
name|void
name|gimp_toggle_button_sensitive_update
parameter_list|(
name|GtkToggleButton
modifier|*
name|toggle_button
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
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
end_function_decl

begin_function_decl
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
end_function_decl

begin_function_decl
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
end_function_decl

begin_function_decl
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
end_function_decl

begin_function_decl
name|void
name|gimp_uint_adjustment_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_float_adjustment_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
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
end_function_decl

begin_function_decl
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
end_function_decl

begin_comment
comment|/*  *  Helper Functions  */
end_comment

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_table_attach_aligned
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
specifier|const
name|gchar
modifier|*
name|label_text
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
name|gint
name|colspan
parameter_list|,
name|gboolean
name|left_align
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_WIDGETS_H__ */
end_comment

end_unit

