begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library                                                     * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball                  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Library General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.               *                                                                                * This library is distributed in the hope that it will be useful,                * but WITHOUT ANY WARRANTY; without even the implied warranty of                 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU              * Library General Public License for more details.  *  * You should have received a copy of the GNU Library General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_ENTRY_H__
end_ifndef

begin_define
DECL|macro|__GIMP_ENTRY_H__
define|#
directive|define
name|__GIMP_ENTRY_H__
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
value|(GTK_CHECK_TYPE (obj, GIMP_TYPE_SIZE_ENTRY)
DECL|macro|GIMP_IS_ENTRY_CLASS (klass)
define|#
directive|define
name|GIMP_IS_ENTRY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_TYPE ((klass), GTK_TYPE_ENTRY))
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
DECL|struct|_GimpSizeEntry
struct|struct
name|_GimpSizeEntry
block|{
DECL|member|hbox
name|GtkHBox
name|hbox
decl_stmt|;
DECL|member|spinbutton
name|GtkWidget
modifier|*
name|spinbutton
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
DECL|member|resolution
name|gfloat
name|resolution
decl_stmt|;
DECL|member|positive_only
name|guint
name|positive_only
decl_stmt|;
block|}
struct|;
DECL|struct|_GimpSizeEntryClass
struct|struct
name|_GimpSizeEntryClass
block|{
DECL|member|parent_class
name|GtkHBoxClass
name|parent_class
decl_stmt|;
DECL|member|gimp_size_entry
name|void
function_decl|(
modifier|*
name|gimp_size_entry
function_decl|)
parameter_list|(
name|GimpSizeEntry
modifier|*
name|gse
parameter_list|)
function_decl|;
block|}
struct|;
name|guint
name|gimp_size_entry_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
name|GtkWidget
modifier|*
name|gimp_size_entry_new
parameter_list|(
name|gfloat
name|value
parameter_list|,
name|GUnit
name|unit
parameter_list|,
name|gfloat
name|resolution
parameter_list|,
name|guint
name|positive_only
parameter_list|)
function_decl|;
name|void
name|gimp_size_entry_set_value
parameter_list|(
name|GimpSizeEntry
modifier|*
name|gse
parameter_list|,
name|gfloat
name|value
parameter_list|)
function_decl|;
name|void
name|gimp_size_entry_set_value_as_pixels
parameter_list|(
name|GimpSizeEntry
modifier|*
name|gse
parameter_list|,
name|gint
name|pixels
parameter_list|)
function_decl|;
name|gfloat
name|gimp_size_entry_get_value
parameter_list|(
name|GimpSizeEntry
modifier|*
name|gse
parameter_list|)
function_decl|;
name|gint
name|gimp_size_entry_get_value_as_pixels
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
name|GUnit
name|gimp_size_entry_get_unit
parameter_list|(
name|GimpSizeEntry
modifier|*
name|gse
parameter_list|)
function_decl|;
name|void
name|gimp_size_entry_set_resolution
parameter_list|(
name|GimpSizeEntry
modifier|*
name|gse
parameter_list|,
name|gfloat
name|resolution
parameter_list|)
function_decl|;
comment|/* This function does NOT change the value of the size_entry                for you! You have to take care of that yourself.           */
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
comment|/* __GIMP_ENTRY_H__ */
end_comment

end_unit

