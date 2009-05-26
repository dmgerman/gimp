begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcombotagentry.h  * Copyright (C) 2008 Aurimas JuÅ¡ka<aurisj@svn.gnome.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_COMBO_TAG_ENTRY_H__
end_ifndef

begin_define
DECL|macro|__GIMP_COMBO_TAG_ENTRY_H__
define|#
directive|define
name|__GIMP_COMBO_TAG_ENTRY_H__
end_define

begin_include
include|#
directive|include
file|"gimptagentry.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_COMBO_TAG_ENTRY
define|#
directive|define
name|GIMP_TYPE_COMBO_TAG_ENTRY
value|(gimp_combo_tag_entry_get_type ())
end_define

begin_define
DECL|macro|GIMP_COMBO_TAG_ENTRY (obj)
define|#
directive|define
name|GIMP_COMBO_TAG_ENTRY
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_COMBO_TAG_ENTRY, GimpComboTagEntry))
end_define

begin_define
DECL|macro|GIMP_COMBO_TAG_ENTRY_CLASS (klass)
define|#
directive|define
name|GIMP_COMBO_TAG_ENTRY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_COMBO_TAG_ENTRY, GimpComboTagEntryClass))
end_define

begin_define
DECL|macro|GIMP_IS_COMBO_TAG_ENTRY (obj)
define|#
directive|define
name|GIMP_IS_COMBO_TAG_ENTRY
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_COMBO_TAG_ENTRY))
end_define

begin_define
DECL|macro|GIMP_IS_COMBO_TAG_ENTRY_CLASS (klass)
define|#
directive|define
name|GIMP_IS_COMBO_TAG_ENTRY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_COMBO_TAG_ENTRY))
end_define

begin_define
DECL|macro|GIMP_COMBO_TAG_ENTRY_GET_CLASS (obj)
define|#
directive|define
name|GIMP_COMBO_TAG_ENTRY_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_COMBO_TAG_ENTRY, GimpComboTagEntryClass))
end_define

begin_typedef
DECL|typedef|GimpComboTagEntryClass
typedef|typedef
name|struct
name|_GimpComboTagEntryClass
name|GimpComboTagEntryClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpComboTagEntry
struct|struct
name|_GimpComboTagEntry
block|{
DECL|member|parent_instance
name|GimpTagEntry
name|parent_instance
decl_stmt|;
DECL|member|popup
name|GtkWidget
modifier|*
name|popup
decl_stmt|;
DECL|member|focus_width
name|gint
name|focus_width
decl_stmt|;
DECL|member|normal_item_attr
name|PangoAttrList
modifier|*
name|normal_item_attr
decl_stmt|;
DECL|member|selected_item_attr
name|PangoAttrList
modifier|*
name|selected_item_attr
decl_stmt|;
DECL|member|insensitive_item_attr
name|PangoAttrList
modifier|*
name|insensitive_item_attr
decl_stmt|;
DECL|member|selected_item_color
name|GdkColor
name|selected_item_color
decl_stmt|;
DECL|member|interior_focus
name|gboolean
name|interior_focus
decl_stmt|;
DECL|member|cursor_type
name|GdkCursorType
name|cursor_type
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpComboTagEntryClass
struct|struct
name|_GimpComboTagEntryClass
block|{
DECL|member|parent_class
name|GimpTagEntryClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_combo_tag_entry_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_combo_tag_entry_new
parameter_list|(
name|GimpFilteredContainer
modifier|*
name|container
parameter_list|,
name|GimpTagEntryMode
name|mode
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_COMBO_TAG_ENTRY_H__  */
end_comment

end_unit

