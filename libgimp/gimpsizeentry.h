begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library                                                     * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball                  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.               *                                                                                * This library is distributed in the hope that it will be useful,                * but WITHOUT ANY WARRANTY; without even the implied warranty of                 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU              * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"gimpunit.h"
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
comment|/* __cplusplus */
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
DECL|typedef|GimpSizeEntry
typedef|typedef
name|struct
name|_GimpSizeEntry
name|GimpSizeEntry
typedef|;
DECL|typedef|GimpSizeEntryClass
typedef|typedef
name|struct
name|_GimpSizeEntryClass
name|GimpSizeEntryClass
typedef|;
typedef|typedef
enum|enum
DECL|enum|__anon27dc0f030103
block|{
DECL|enumerator|GIMP_SIZE_ENTRY_UPDATE_NONE
name|GIMP_SIZE_ENTRY_UPDATE_NONE
init|=
literal|0
block|,
DECL|enumerator|GIMP_SIZE_ENTRY_UPDATE_SIZE
name|GIMP_SIZE_ENTRY_UPDATE_SIZE
init|=
literal|1
block|,
DECL|enumerator|GIMP_SIZE_ENTRY_UPDATE_RESOLUTION
name|GIMP_SIZE_ENTRY_UPDATE_RESOLUTION
init|=
literal|2
DECL|typedef|GimpSizeEntryUP
block|}
name|GimpSizeEntryUP
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
name|GUnit
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
name|GimpSizeEntryUP
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
name|GtkType
name|gimp_size_entry_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
comment|/* creates a new GimpSizeEntry widget  * number_of_fields  -- how many spinbuttons to show  * unit              -- unit to show initially  * unit_format       -- printf-like unit-format (see GimpUnitMenu)  * menu_show_pixels  -- should the unit menu contain 'pixels'  *                      this parameter is ignored if you select an update_policy  * show_refval       -- TRUE if you want the extra 'reference value' row  * spinbutton_usize  -- the minimal horizontal size the spinbuttons will have  * update_policy     -- how calculations should be performed  *                      GIMP_SIZE_ENTRY_UPDATE_NONE --> no calculations  *			GIMP_SIZE_ENTRY_UPDATE_SIZE --> consider the values to  *                        be distances. The reference value equals to pixels  *			GIMP_SIZE_ENTRY_UPDATE_RESOLUTION --> consider the values  *                        to be resolutions. The reference value equals to dpi  *  * to have all automatic calculations performed correctly, set up the  * widget in the following order:  * 1. gimp_size_entry_new  * 2. (for each additional input field) gimp_size_entry_add_field  * 3. gimp_size_entry_set_unit  * for each input field:  * 4. gimp_size_entry_set_resolution  * 5. gimp_size_entry_set_value_boundaries (or _set_refval_boundaries)  * 6. gimp_size_entry_set_size  * 7. gimp_size_entry_set_value (or _set_refval)  *  * the newly created GimpSizeEntry table will have an empty border  * of one cell width on each side plus an empty column left of the  * unit menu to allow the caller to add labels  */
name|GtkWidget
modifier|*
name|gimp_size_entry_new
parameter_list|(
name|gint
name|number_of_fields
parameter_list|,
name|GUnit
name|unit
parameter_list|,
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
name|GimpSizeEntryUP
name|update_policy
parameter_list|)
function_decl|;
comment|/* add a field to the sizeentry  * if show_refval if FALSE, then the refval pointers will be ignored  *  * the new field will have the index 0  */
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
comment|/* this one is just a convenience function if you want to add labels  * to the empty cells of the widget  */
name|void
name|gimp_size_entry_attach_label
parameter_list|(
name|GimpSizeEntry
modifier|*
name|gse
parameter_list|,
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
comment|/* this one sets the resolution (in dpi)  *  * does nothing if update_policy != GIMP_SIZE_ENTRY_UPDATE_SIZE  *  * keep_size is a boolean value. If TRUE, the size in pixels will stay  * the same, otherwise the size in units will stay the same.  */
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
name|guint
name|keep_size
parameter_list|)
function_decl|;
comment|/* this one sets the values (in pixels) which will be treated as  * 0% and 100% when we want "percent" in the unit menu  *  * does nothing if update_policy != GIMP_SIZE_ENTRY_UPDATE_SIZE  */
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
comment|/* these functions set/return the value in the units the user selected  * note that in some cases where the caller chooses not to have the  * reference value row and the user selected the reference unit  * the both values 'value' and 'refval' will be the same  */
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
comment|/* these functions set/return the value in the 'reference unit' for the  * current update policy  * for GIMP_SIZE_ENTRY_UPDATE_SIZE       it's the value in pixels  * for GIMP_SIZE_ENTRY_UPDATE_RESOLUTION it's the resolution in dpi  * for GIMP_SIZE_ENTRY_UPDATE_NONE       it's up to the caller as he has to  *                                       provide a correct value<->refval  *                                       mapping  */
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
comment|/* these functions set/return the currently used unit  * note that for GIMP_SIZE_ENTRY_UPDATE_SIZE a value of UNIT_PIXEL  * will be silently ignored if we have the extra refvalue line  */
name|GUnit
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
name|GUnit
name|unit
parameter_list|)
function_decl|;
comment|/* this makes the first spinbutton grab the focus  */
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

