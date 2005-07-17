begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2005 Peter Mattis and Spencer Kimball  *  * gimpresolutionentry.h  * Copyright (C) 1999-2005 Sven Neumann<sven@gimp.org>  *                         Michael Natterer<mitch@gimp.org>  *                         Nathan Summers<rock@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_RESOLUTION_ENTRY_H__
end_ifndef

begin_define
DECL|macro|__GIMP_RESOLUTION_ENTRY_H__
define|#
directive|define
name|__GIMP_RESOLUTION_ENTRY_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look into the C source or the html documentation */
end_comment

begin_define
DECL|macro|GIMP_TYPE_RESOLUTION_ENTRY
define|#
directive|define
name|GIMP_TYPE_RESOLUTION_ENTRY
value|(gimp_resolution_entry_get_type ())
end_define

begin_define
DECL|macro|GIMP_RESOLUTION_ENTRY (obj)
define|#
directive|define
name|GIMP_RESOLUTION_ENTRY
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_RESOLUTION_ENTRY, GimpResolutionEntry))
end_define

begin_define
DECL|macro|GIMP_RESOLUTION_ENTRY_CLASS (klass)
define|#
directive|define
name|GIMP_RESOLUTION_ENTRY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_RESOLUTION_ENTRY, GimpResolutionEntryClass))
end_define

begin_define
DECL|macro|GIMP_IS_RESOLUTION_ENTRY (obj)
define|#
directive|define
name|GIMP_IS_RESOLUTION_ENTRY
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE (obj, GIMP_TYPE_RESOLUTION_ENTRY))
end_define

begin_define
DECL|macro|GIMP_IS_RESOLUTION_ENTRY_CLASS (klass)
define|#
directive|define
name|GIMP_IS_RESOLUTION_ENTRY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_RESOLUTION_ENTRY))
end_define

begin_define
DECL|macro|GIMP_RESOLUTION_ENTRY_GET_CLASS (obj)
define|#
directive|define
name|GIMP_RESOLUTION_ENTRY_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_RESOLUTION_ENTRY, GimpResolutionEntryClass))
end_define

begin_typedef
DECL|typedef|GimpResolutionEntryClass
typedef|typedef
name|struct
name|_GimpResolutionEntryClass
name|GimpResolutionEntryClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpResolutionEntryField
typedef|typedef
name|struct
name|_GimpResolutionEntryField
name|GimpResolutionEntryField
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpResolutionEntryField
struct|struct
name|_GimpResolutionEntryField
block|{
DECL|member|gre
name|GimpResolutionEntry
modifier|*
name|gre
decl_stmt|;
DECL|member|corresponding
name|GimpResolutionEntryField
modifier|*
name|corresponding
decl_stmt|;
DECL|member|size
name|gboolean
name|size
decl_stmt|;
DECL|member|label
name|GtkWidget
modifier|*
name|label
decl_stmt|;
DECL|member|changed_signal
name|guint
name|changed_signal
decl_stmt|;
DECL|member|adjustment
name|GtkObject
modifier|*
name|adjustment
decl_stmt|;
DECL|member|spinbutton
name|GtkWidget
modifier|*
name|spinbutton
decl_stmt|;
DECL|member|phy_size
name|gdouble
name|phy_size
decl_stmt|;
DECL|member|value
name|gdouble
name|value
decl_stmt|;
DECL|member|min_value
name|gdouble
name|min_value
decl_stmt|;
DECL|member|max_value
name|gdouble
name|max_value
decl_stmt|;
DECL|member|stop_recursion
name|gint
name|stop_recursion
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpResolutionEntry
struct|struct
name|_GimpResolutionEntry
block|{
DECL|member|parent_instance
name|GtkTable
name|parent_instance
decl_stmt|;
DECL|member|size_unit
name|GimpUnit
name|size_unit
decl_stmt|;
DECL|member|unit
name|GimpUnit
name|unit
decl_stmt|;
DECL|member|independent
name|gboolean
name|independent
decl_stmt|;
DECL|member|unitmenu
name|GtkWidget
modifier|*
name|unitmenu
decl_stmt|;
DECL|member|chainbutton
name|GtkWidget
modifier|*
name|chainbutton
decl_stmt|;
DECL|member|width
name|GimpResolutionEntryField
name|width
decl_stmt|;
DECL|member|height
name|GimpResolutionEntryField
name|height
decl_stmt|;
DECL|member|x
name|GimpResolutionEntryField
name|x
decl_stmt|;
DECL|member|y
name|GimpResolutionEntryField
name|y
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpResolutionEntryClass
struct|struct
name|_GimpResolutionEntryClass
block|{
DECL|member|parent_class
name|GtkTableClass
name|parent_class
decl_stmt|;
DECL|member|value_changed
name|void
function_decl|(
modifier|*
name|value_changed
function_decl|)
parameter_list|(
name|GimpResolutionEntry
modifier|*
name|gse
parameter_list|)
function_decl|;
DECL|member|refval_changed
name|void
function_decl|(
modifier|*
name|refval_changed
function_decl|)
parameter_list|(
name|GimpResolutionEntry
modifier|*
name|gse
parameter_list|)
function_decl|;
DECL|member|unit_changed
name|void
function_decl|(
modifier|*
name|unit_changed
function_decl|)
parameter_list|(
name|GimpResolutionEntry
modifier|*
name|gse
parameter_list|)
function_decl|;
comment|/* Padding for future expansion */
DECL|member|_gimp_reserved1
name|void
function_decl|(
modifier|*
name|_gimp_reserved1
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved2
name|void
function_decl|(
modifier|*
name|_gimp_reserved2
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved3
name|void
function_decl|(
modifier|*
name|_gimp_reserved3
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved4
name|void
function_decl|(
modifier|*
name|_gimp_reserved4
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_comment
comment|/* For information look into the C source or the html documentation */
end_comment

begin_decl_stmt
name|GType
name|gimp_resolution_entry_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_resolution_entry_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|width_label
parameter_list|,
name|gdouble
name|width
parameter_list|,
specifier|const
name|gchar
modifier|*
name|height_label
parameter_list|,
name|gdouble
name|height
parameter_list|,
name|GimpUnit
name|size_unit
parameter_list|,
specifier|const
name|gchar
modifier|*
name|x_label
parameter_list|,
name|gdouble
name|initial_x
parameter_list|,
specifier|const
name|gchar
modifier|*
name|y_label
parameter_list|,
name|gdouble
name|initial_y
parameter_list|,
name|GimpUnit
name|intial_unit
parameter_list|,
name|gboolean
name|independent
parameter_list|,
name|gint
name|spinbutton_width
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_resolution_entry_attach_label
parameter_list|(
name|GimpResolutionEntry
modifier|*
name|gre
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text
parameter_list|,
name|gint
name|row
parameter_list|,
name|gint
name|column
parameter_list|,
name|gfloat
name|alignment
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_resolution_entry_set_width_boundaries
parameter_list|(
name|GimpResolutionEntry
modifier|*
name|gre
parameter_list|,
name|gdouble
name|lower
parameter_list|,
name|gdouble
name|upper
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_resolution_entry_set_height_boundaries
parameter_list|(
name|GimpResolutionEntry
modifier|*
name|gre
parameter_list|,
name|gdouble
name|lower
parameter_list|,
name|gdouble
name|upper
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_resolution_entry_set_x_boundaries
parameter_list|(
name|GimpResolutionEntry
modifier|*
name|gre
parameter_list|,
name|gdouble
name|lower
parameter_list|,
name|gdouble
name|upper
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_resolution_entry_set_y_boundaries
parameter_list|(
name|GimpResolutionEntry
modifier|*
name|gre
parameter_list|,
name|gdouble
name|lower
parameter_list|,
name|gdouble
name|upper
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_resolution_entry_get_width
parameter_list|(
name|GimpResolutionEntry
modifier|*
name|gre
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_resolution_entry_get_height
parameter_list|(
name|GimpResolutionEntry
modifier|*
name|gre
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_resolution_entry_get_x
parameter_list|(
name|GimpResolutionEntry
modifier|*
name|gre
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_resolution_entry_get_x_in_dpi
parameter_list|(
name|GimpResolutionEntry
modifier|*
name|gre
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_resolution_entry_get_y
parameter_list|(
name|GimpResolutionEntry
modifier|*
name|gre
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_resolution_entry_get_y_in_dpi
parameter_list|(
name|GimpResolutionEntry
modifier|*
name|gre
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_resolution_entry_set_width
parameter_list|(
name|GimpResolutionEntry
modifier|*
name|gre
parameter_list|,
name|gdouble
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_resolution_entry_set_height
parameter_list|(
name|GimpResolutionEntry
modifier|*
name|gre
parameter_list|,
name|gdouble
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_resolution_entry_set_x
parameter_list|(
name|GimpResolutionEntry
modifier|*
name|gre
parameter_list|,
name|gdouble
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_resolution_entry_set_y
parameter_list|(
name|GimpResolutionEntry
modifier|*
name|gre
parameter_list|,
name|gdouble
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpUnit
name|gimp_resolution_entry_get_unit
parameter_list|(
name|GimpResolutionEntry
modifier|*
name|gre
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_resolution_entry_set_unit
parameter_list|(
name|GimpResolutionEntry
modifier|*
name|gre
parameter_list|,
name|GimpUnit
name|unit
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_resolution_entry_show_unit_menu
parameter_list|(
name|GimpResolutionEntry
modifier|*
name|gre
parameter_list|,
name|gboolean
name|show
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_resolution_entry_set_pixel_digits
parameter_list|(
name|GimpResolutionEntry
modifier|*
name|gre
parameter_list|,
name|gint
name|digits
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_resolution_entry_grab_focus
parameter_list|(
name|GimpResolutionEntry
modifier|*
name|gre
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_resolution_entry_set_activates_default
parameter_list|(
name|GimpResolutionEntry
modifier|*
name|gre
parameter_list|,
name|gboolean
name|setting
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_resolution_entry_get_width_help_widget
parameter_list|(
name|GimpResolutionEntry
modifier|*
name|gre
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_resolution_entry_get_height_help_widget
parameter_list|(
name|GimpResolutionEntry
modifier|*
name|gre
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_resolution_entry_get_x_help_widget
parameter_list|(
name|GimpResolutionEntry
modifier|*
name|gre
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_resolution_entry_get_y_help_widget
parameter_list|(
name|GimpResolutionEntry
modifier|*
name|gre
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* signal callback convenience functions */
end_comment

begin_function_decl
name|void
name|gimp_resolution_entry_update_width
parameter_list|(
name|GimpResolutionEntry
modifier|*
name|gre
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_resolution_entry_update_height
parameter_list|(
name|GimpResolutionEntry
modifier|*
name|gre
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_resolution_entry_update_x
parameter_list|(
name|GimpResolutionEntry
modifier|*
name|gre
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_resolution_entry_update_x_in_dpi
parameter_list|(
name|GimpResolutionEntry
modifier|*
name|gre
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_resolution_entry_update_y
parameter_list|(
name|GimpResolutionEntry
modifier|*
name|gre
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_resolution_entry_update_y_in_dpi
parameter_list|(
name|GimpResolutionEntry
modifier|*
name|gre
parameter_list|,
name|gpointer
name|data
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
comment|/* __GIMP_RESOLUTION_ENTRY_H__ */
end_comment

end_unit

