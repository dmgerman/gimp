begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpscaleentry.h  * Copyright (C) 2000 Michael Natterer<mitch@gimp.org>,  *               2008 Bill Skaggs<weskaggs@primate.ucdavis.edu>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_SCALE_ENTRY_H__
end_ifndef

begin_define
DECL|macro|__GIMP_SCALE_ENTRY_H__
define|#
directive|define
name|__GIMP_SCALE_ENTRY_H__
end_define

begin_function_decl
name|G_BEGIN_DECLS
comment|/**  * GIMP_SCALE_ENTRY_LABEL:  * @adj: The #GtkAdjustment returned by gimp_scale_entry_new().  *  * Returns the scale_entry's #GtkLabel.  **/
DECL|macro|GIMP_SCALE_ENTRY_LABEL (adj)
define|#
directive|define
name|GIMP_SCALE_ENTRY_LABEL
parameter_list|(
name|adj
parameter_list|)
define|\
value|(g_object_get_data (G_OBJECT (adj), "label"))
comment|/**  * GIMP_SCALE_ENTRY_SCALE:  * @adj: The #GtkAdjustment returned by gimp_scale_entry_new().  *  * Returns the scale_entry's #GtkHScale.  **/
DECL|macro|GIMP_SCALE_ENTRY_SCALE (adj)
define|#
directive|define
name|GIMP_SCALE_ENTRY_SCALE
parameter_list|(
name|adj
parameter_list|)
define|\
value|(g_object_get_data (G_OBJECT (adj), "scale"))
comment|/**  * GIMP_SCALE_ENTRY_SCALE_ADJ:  * @adj: The #GtkAdjustment returned by gimp_scale_entry_new().  *  * Returns the #GtkAdjustment of the scale_entry's #GtkHScale.  **/
DECL|macro|GIMP_SCALE_ENTRY_SCALE_ADJ (adj)
define|#
directive|define
name|GIMP_SCALE_ENTRY_SCALE_ADJ
parameter_list|(
name|adj
parameter_list|)
define|\
value|gtk_range_get_adjustment \         (GTK_RANGE (g_object_get_data (G_OBJECT (adj), "scale")))
comment|/**  * GIMP_SCALE_ENTRY_SPINBUTTON:  * @adj: The #GtkAdjustment returned by gimp_scale_entry_new().  *  * Returns the scale_entry's #GtkSpinButton.  **/
DECL|macro|GIMP_SCALE_ENTRY_SPINBUTTON (adj)
define|#
directive|define
name|GIMP_SCALE_ENTRY_SPINBUTTON
parameter_list|(
name|adj
parameter_list|)
define|\
value|(g_object_get_data (G_OBJECT (adj), "spinbutton"))
comment|/**  * GIMP_SCALE_ENTRY_SPINBUTTON_ADJ:  * @adj: The #GtkAdjustment returned by gimp_scale_entry_new().  *  * Returns the #GtkAdjustment of the scale_entry's #GtkSpinButton.  **/
DECL|macro|GIMP_SCALE_ENTRY_SPINBUTTON_ADJ (adj)
define|#
directive|define
name|GIMP_SCALE_ENTRY_SPINBUTTON_ADJ
parameter_list|(
name|adj
parameter_list|)
define|\
value|gtk_spin_button_get_adjustment \         (GTK_SPIN_BUTTON (g_object_get_data (G_OBJECT (adj), "spinbutton")))
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
name|guint
name|digits
parameter_list|,
name|gboolean
name|constrain
parameter_list|,
name|gdouble
name|unconstrained_lower
parameter_list|,
name|gdouble
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
name|help_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkObject
modifier|*
name|gimp_color_scale_entry_new
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
name|guint
name|digits
parameter_list|,
specifier|const
name|gchar
modifier|*
name|tooltip
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_scale_entry_set_sensitive
parameter_list|(
name|GtkObject
modifier|*
name|adjustment
parameter_list|,
name|gboolean
name|sensitive
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_scale_entry_set_logarithmic
parameter_list|(
name|GtkObject
modifier|*
name|adjustment
parameter_list|,
name|gboolean
name|logarithmic
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_scale_entry_get_logarithmic
parameter_list|(
name|GtkObject
modifier|*
name|adjustment
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
comment|/* __GIMP_SCALE_ENTRY_H__ */
end_comment

end_unit

