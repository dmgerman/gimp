begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library         * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball   *  * gimpsizeentry.h  * Copyright (C) 1999-2000 Sven Neumann<sven@gimp.org>  *                         Michael Natterer<mitch@gimp.org>   *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_SIZE_ENTRY_H__
end_ifndef

begin_define
DECL|macro|__GIMP_SIZE_ENTRY_H__
define|#
directive|define
name|__GIMP_SIZE_ENTRY_H__
end_define

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
comment|/* __cplusplus */
comment|/* For information look into the C source or the html documentation */
DECL|macro|GIMP_TYPE_SIZE_ENTRY
define|#
directive|define
name|GIMP_TYPE_SIZE_ENTRY
value|(gimp_size_entry_get_type ())
DECL|macro|GIMP_SIZE_ENTRY (obj)
define|#
directive|define
name|GIMP_SIZE_ENTRY
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_CAST ((obj), GIMP_TYPE_SIZE_ENTRY, GimpSizeEntry))
DECL|macro|GIMP_SIZE_ENTRY_CLASS (klass)
define|#
directive|define
name|GIMP_SIZE_ENTRY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_CAST ((klass), GIMP_TYPE_SIZE_ENTRY, GimpSizeEntryClass))
DECL|macro|GIMP_IS_SIZE_ENTRY (obj)
define|#
directive|define
name|GIMP_IS_SIZE_ENTRY
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_TYPE (obj, GIMP_TYPE_SIZE_ENTRY))
DECL|macro|GIMP_IS_SIZE_ENTRY_CLASS (klass)
define|#
directive|define
name|GIMP_IS_SIZE_ENTRY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_SIZE_ENTRY))
DECL|typedef|GimpSizeEntryClass
typedef|typedef
name|struct
name|_GimpSizeEntryClass
name|GimpSizeEntryClass
typedef|;
DECL|typedef|GimpSizeEntryField
typedef|typedef
name|struct
name|_GimpSizeEntryField
name|GimpSizeEntryField
typedef|;
DECL|struct|_GimpSizeEntry
struct|struct
name|_GimpSizeEntry
block|{
DECL|member|table
name|GtkTable
name|table
decl_stmt|;
DECL|member|fields
name|GSList
modifier|*
name|fields
decl_stmt|;
DECL|member|number_of_fields
name|gint
name|number_of_fields
decl_stmt|;
DECL|member|unitmenu
name|GtkWidget
modifier|*
name|unitmenu
decl_stmt|;
DECL|member|unit
name|GimpUnit
name|unit
decl_stmt|;
DECL|member|menu_show_pixels
name|gboolean
name|menu_show_pixels
decl_stmt|;
DECL|member|menu_show_percent
name|gboolean
name|menu_show_percent
decl_stmt|;
DECL|member|show_refval
name|gboolean
name|show_refval
decl_stmt|;
DECL|member|update_policy
name|GimpSizeEntryUpdatePolicy
name|update_policy
decl_stmt|;
block|}
struct|;
DECL|struct|_GimpSizeEntryClass
struct|struct
name|_GimpSizeEntryClass
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
name|GimpSizeEntry
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
name|GimpSizeEntry
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
name|GimpSizeEntry
modifier|*
name|gse
parameter_list|)
function_decl|;
block|}
struct|;
comment|/* For information look into the C source or the html documentation */
name|GtkType
name|gimp_size_entry_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
name|GtkWidget
modifier|*
name|gimp_size_entry_new
parameter_list|(
name|gint
name|number_of_fields
parameter_list|,
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
name|gboolean
name|show_refval
parameter_list|,
name|gint
name|spinbutton_usize
parameter_list|,
name|GimpSizeEntryUpdatePolicy
name|update_policy
parameter_list|)
function_decl|;
name|void
name|gimp_size_entry_add_field
parameter_list|(
name|GimpSizeEntry
modifier|*
name|gse
parameter_list|,
name|GtkSpinButton
modifier|*
name|value_spinbutton
parameter_list|,
name|GtkSpinButton
modifier|*
name|refval_spinbutton
parameter_list|)
function_decl|;
name|void
name|gimp_size_entry_attach_label
parameter_list|(
name|GimpSizeEntry
modifier|*
name|gse
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
name|void
name|gimp_size_entry_set_resolution
parameter_list|(
name|GimpSizeEntry
modifier|*
name|gse
parameter_list|,
name|gint
name|field
parameter_list|,
name|gdouble
name|resolution
parameter_list|,
name|gboolean
name|keep_size
parameter_list|)
function_decl|;
name|void
name|gimp_size_entry_set_size
parameter_list|(
name|GimpSizeEntry
modifier|*
name|gse
parameter_list|,
name|gint
name|field
parameter_list|,
name|gdouble
name|lower
parameter_list|,
name|gdouble
name|upper
parameter_list|)
function_decl|;
name|void
name|gimp_size_entry_set_value_boundaries
parameter_list|(
name|GimpSizeEntry
modifier|*
name|gse
parameter_list|,
name|gint
name|field
parameter_list|,
name|gdouble
name|lower
parameter_list|,
name|gdouble
name|upper
parameter_list|)
function_decl|;
name|gdouble
name|gimp_size_entry_get_value
parameter_list|(
name|GimpSizeEntry
modifier|*
name|gse
parameter_list|,
name|gint
name|field
parameter_list|)
function_decl|;
name|void
name|gimp_size_entry_set_value
parameter_list|(
name|GimpSizeEntry
modifier|*
name|gse
parameter_list|,
name|gint
name|field
parameter_list|,
name|gdouble
name|value
parameter_list|)
function_decl|;
name|void
name|gimp_size_entry_set_refval_boundaries
parameter_list|(
name|GimpSizeEntry
modifier|*
name|gse
parameter_list|,
name|gint
name|field
parameter_list|,
name|gdouble
name|lower
parameter_list|,
name|gdouble
name|upper
parameter_list|)
function_decl|;
name|void
name|gimp_size_entry_set_refval_digits
parameter_list|(
name|GimpSizeEntry
modifier|*
name|gse
parameter_list|,
name|gint
name|field
parameter_list|,
name|gint
name|digits
parameter_list|)
function_decl|;
name|gdouble
name|gimp_size_entry_get_refval
parameter_list|(
name|GimpSizeEntry
modifier|*
name|gse
parameter_list|,
name|gint
name|field
parameter_list|)
function_decl|;
name|void
name|gimp_size_entry_set_refval
parameter_list|(
name|GimpSizeEntry
modifier|*
name|gse
parameter_list|,
name|gint
name|field
parameter_list|,
name|gdouble
name|refval
parameter_list|)
function_decl|;
name|GimpUnit
name|gimp_size_entry_get_unit
parameter_list|(
name|GimpSizeEntry
modifier|*
name|gse
parameter_list|)
function_decl|;
name|void
name|gimp_size_entry_set_unit
parameter_list|(
name|GimpSizeEntry
modifier|*
name|gse
parameter_list|,
name|GimpUnit
name|unit
parameter_list|)
function_decl|;
name|void
name|gimp_size_entry_grab_focus
parameter_list|(
name|GimpSizeEntry
modifier|*
name|gse
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

begin_comment
comment|/* __cplusplus */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_SIZE_ENTRY_H__ */
end_comment

end_unit

