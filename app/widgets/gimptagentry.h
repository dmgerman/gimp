begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimptagentry.h  * Copyright (C) 2008 Aurimas JuÅ¡ka<aurisj@svn.gnome.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TAG_ENTRY_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TAG_ENTRY_H__
define|#
directive|define
name|__GIMP_TAG_ENTRY_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_TAG_ENTRY
define|#
directive|define
name|GIMP_TYPE_TAG_ENTRY
value|(gimp_tag_entry_get_type ())
end_define

begin_define
DECL|macro|GIMP_TAG_ENTRY (obj)
define|#
directive|define
name|GIMP_TAG_ENTRY
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_TAG_ENTRY, GimpTagEntry))
end_define

begin_define
DECL|macro|GIMP_TAG_ENTRY_CLASS (klass)
define|#
directive|define
name|GIMP_TAG_ENTRY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_TAG_ENTRY, GimpTagEntryClass))
end_define

begin_define
DECL|macro|GIMP_IS_TAG_ENTRY (obj)
define|#
directive|define
name|GIMP_IS_TAG_ENTRY
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_TAG_ENTRY))
end_define

begin_define
DECL|macro|GIMP_IS_TAG_ENTRY_CLASS (klass)
define|#
directive|define
name|GIMP_IS_TAG_ENTRY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_TAG_ENTRY))
end_define

begin_define
DECL|macro|GIMP_TAG_ENTRY_GET_CLASS (obj)
define|#
directive|define
name|GIMP_TAG_ENTRY_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_TAG_ENTRY, GimpTagEntryClass))
end_define

begin_typedef
DECL|typedef|GimpTagEntryClass
typedef|typedef
name|struct
name|_GimpTagEntryClass
name|GimpTagEntryClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpTagEntry
struct|struct
name|_GimpTagEntry
block|{
DECL|member|parent_instance
name|GtkEntry
name|parent_instance
decl_stmt|;
DECL|member|container
name|GimpTaggedContainer
modifier|*
name|container
decl_stmt|;
comment|/* mask describes the meaning of each char in GimpTagEntry.    * It is maintained automatically on insert-text and delete-text    * events. If manual mask modification is desired, then    * suppress_mask_update must be increased before calling any    * function changing entry contents.    * Meaning of mask chars:    * u - undefined / unknown (just typed unparsed text)    * t - tag    * s - separator    * w - whitespace.    */
DECL|member|mask
name|GString
modifier|*
name|mask
decl_stmt|;
DECL|member|selected_items
name|GList
modifier|*
name|selected_items
decl_stmt|;
DECL|member|common_tags
name|GList
modifier|*
name|common_tags
decl_stmt|;
DECL|member|recent_list
name|GList
modifier|*
name|recent_list
decl_stmt|;
DECL|member|tab_completion_index
name|gint
name|tab_completion_index
decl_stmt|;
DECL|member|internal_operation
name|gint
name|internal_operation
decl_stmt|;
DECL|member|suppress_mask_update
name|gint
name|suppress_mask_update
decl_stmt|;
DECL|member|suppress_tag_query
name|gint
name|suppress_tag_query
decl_stmt|;
DECL|member|mode
name|GimpTagEntryMode
name|mode
decl_stmt|;
DECL|member|description_shown
name|gboolean
name|description_shown
decl_stmt|;
DECL|member|has_invalid_tags
name|gboolean
name|has_invalid_tags
decl_stmt|;
DECL|member|tag_query_pending
name|gboolean
name|tag_query_pending
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpTagEntryClass
struct|struct
name|_GimpTagEntryClass
block|{
DECL|member|parent_class
name|GtkEntryClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_tag_entry_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_tag_entry_new
parameter_list|(
name|GimpTaggedContainer
modifier|*
name|container
parameter_list|,
name|GimpTagEntryMode
name|mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tag_entry_set_selected_items
parameter_list|(
name|GimpTagEntry
modifier|*
name|entry
parameter_list|,
name|GList
modifier|*
name|items
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
modifier|*
name|gimp_tag_entry_parse_tags
parameter_list|(
name|GimpTagEntry
modifier|*
name|entry
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tag_entry_set_tag_string
parameter_list|(
name|GimpTagEntry
modifier|*
name|entry
parameter_list|,
specifier|const
name|gchar
modifier|*
name|tag_string
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_tag_entry_get_separator
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_TAG_ENTRY_H__  */
end_comment

end_unit

