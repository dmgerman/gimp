begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpwidgets.h  * Copyright (C) 2000 Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
file|<libgimpwidgets/gimpbrowser.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimpbutton.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimpcairo-utils.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimpcellrenderercolor.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimpcellrenderertoggle.h>
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
file|<libgimpwidgets/gimpcolordisplay.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimpcolordisplaystack.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimpcolorhexentry.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimpcolornotebook.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimpcolorprofilecombobox.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimpcolorprofilestore.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimpcolorscale.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimpcolorscales.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimpcolorselector.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimpcolorselect.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimpcolorselection.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimpdialog.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimpenumcombobox.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimpenumlabel.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimpenumstore.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimpenumwidgets.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimpfileentry.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimpframe.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimphelpui.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimphintbox.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimpintcombobox.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimpintstore.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimpmemsizeentry.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimpnumberpairentry.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimpoffsetarea.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimppageselector.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimppatheditor.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimppickbutton.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimppixmap.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimppreview.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimppreviewarea.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimppropwidgets.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimpquerybox.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimpruler.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimpscaleentry.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimpscrolledpreview.h>
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
file|<libgimpwidgets/gimpstringcombobox.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimpunitmenu.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimpwidgets-error.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimpzoommodel.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimpoldwidgets.h>
end_include

begin_decl_stmt
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
comment|/*  *  Widget Constructors  */
name|GtkWidget
modifier|*
name|gimp_int_radio_group_new
argument_list|(
name|gboolean
name|in_frame
argument_list|,
specifier|const
name|gchar
operator|*
name|frame_title
argument_list|,
name|GCallback
name|radio_button_callback
argument_list|,
name|gpointer
name|radio_button_callback_data
argument_list|,
name|gint
name|initial
argument_list|,
comment|/* item_data */
comment|/* specify radio buttons as va_list:                                        *  const gchar  *label,                                        *  gint          item_data,                                        *  GtkWidget   **widget_ptr,                                        */
operator|...
argument_list|)
name|G_GNUC_NULL_TERMINATED
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_int_radio_group_set_active
parameter_list|(
name|GtkRadioButton
modifier|*
name|radio_button
parameter_list|,
name|gint
name|item_data
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
name|GtkWidget
modifier|*
name|gimp_radio_group_new
argument_list|(
name|gboolean
name|in_frame
argument_list|,
specifier|const
name|gchar
operator|*
name|frame_title
argument_list|,
comment|/* specify radio buttons as va_list:                                      *  const gchar    *label,                                      *  GCallback       callback,                                      *  gpointer        callback_data,                                      *  gpointer        item_data,                                      *  GtkWidget     **widget_ptr,                                      *  gboolean        active,                                      */
operator|...
argument_list|)
name|G_GNUC_NULL_TERMINATED
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|GtkWidget
modifier|*
name|gimp_radio_group_new2
argument_list|(
name|gboolean
name|in_frame
argument_list|,
specifier|const
name|gchar
operator|*
name|frame_title
argument_list|,
name|GCallback
name|radio_button_callback
argument_list|,
name|gpointer
name|radio_button_callback_data
argument_list|,
name|gpointer
name|initial
argument_list|,
comment|/* item_data */
comment|/* specify radio buttons as va_list:                                      *  const gchar    *label,                                      *  gpointer        item_data,                                      *  GtkWidget     **widget_ptr,                                      */
operator|...
argument_list|)
name|G_GNUC_NULL_TERMINATED
decl_stmt|;
end_decl_stmt

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
name|gdouble
name|value
parameter_list|,
name|gdouble
name|lower
parameter_list|,
name|gdouble
name|upper
parameter_list|,
name|gdouble
name|step_increment
parameter_list|,
name|gdouble
name|page_increment
parameter_list|,
name|gdouble
name|page_size
parameter_list|,
name|gdouble
name|climb_rate
parameter_list|,
name|guint
name|digits
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/**  * GIMP_RANDOM_SEED_SPINBUTTON:  * @hbox: The #GtkHBox returned by gimp_random_seed_new().  *  * Returns the random_seed's #GtkSpinButton.  **/
end_comment

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

begin_comment
comment|/**  * GIMP_RANDOM_SEED_SPINBUTTON_ADJ:  * @hbox: The #GtkHBox returned by gimp_random_seed_new().  *  * Returns the #GtkAdjustment of the random_seed's #GtkSpinButton.  **/
end_comment

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

begin_comment
comment|/**  * GIMP_RANDOM_SEED_TOGGLE:  * @hbox: The #GtkHBox returned by gimp_random_seed_new().  *  * Returns the random_seed's #GtkToggleButton.  **/
end_comment

begin_define
DECL|macro|GIMP_RANDOM_SEED_TOGGLE (hbox)
define|#
directive|define
name|GIMP_RANDOM_SEED_TOGGLE
parameter_list|(
name|hbox
parameter_list|)
define|\
value|(g_object_get_data (G_OBJECT(hbox), "toggle"))
end_define

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_random_seed_new
parameter_list|(
name|guint32
modifier|*
name|seed
parameter_list|,
name|gboolean
modifier|*
name|random_seed
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/**  * GIMP_COORDINATES_CHAINBUTTON:  * @sizeentry: The #GimpSizeEntry returned by gimp_coordinates_new().  *  * Returns the #GimpChainButton which is attached to the  * #GimpSizeEntry.  **/
end_comment

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

begin_ifndef
ifndef|#
directive|ifndef
name|GIMP_DISABLE_DEPRECATED
end_ifndef

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

begin_endif
endif|#
directive|endif
end_endif

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

begin_function_decl
name|void
name|gimp_label_set_attributes
parameter_list|(
name|GtkLabel
modifier|*
name|label
parameter_list|,
modifier|...
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

