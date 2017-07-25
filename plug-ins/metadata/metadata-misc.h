begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Copyright (C) 2016, 2017 Ben Touchette  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__METADATA_MISC_H__
end_ifndef

begin_define
DECL|macro|__METADATA_MISC_H__
define|#
directive|define
name|__METADATA_MISC_H__
end_define

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon29f91ffe0108
block|{
DECL|member|dialog
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
DECL|member|builder
name|GtkBuilder
modifier|*
name|builder
decl_stmt|;
DECL|member|metadata
name|GExiv2Metadata
modifier|*
name|metadata
decl_stmt|;
DECL|member|image_id
name|gint32
name|image_id
decl_stmt|;
DECL|member|filename
name|gchar
modifier|*
name|filename
decl_stmt|;
DECL|typedef|metadata_editor
block|}
name|metadata_editor
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon29f91ffe0208
block|{
DECL|member|tag
name|gchar
modifier|*
name|tag
decl_stmt|;
DECL|member|mode
name|gchar
modifier|*
name|mode
decl_stmt|;
DECL|member|other_tag_index
name|gint32
name|other_tag_index
decl_stmt|;
DECL|member|tag_type
name|gint32
name|tag_type
decl_stmt|;
DECL|member|xmp_type
name|gint32
name|xmp_type
decl_stmt|;
DECL|typedef|metadata_tag
block|}
name|metadata_tag
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon29f91ffe0308
block|{
DECL|member|data
name|gchar
modifier|*
name|data
decl_stmt|;
DECL|member|display
name|gchar
modifier|*
name|display
decl_stmt|;
DECL|typedef|combobox_str_tag
block|}
name|combobox_str_tag
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon29f91ffe0408
block|{
DECL|member|data
name|gint32
name|data
decl_stmt|;
DECL|member|display
name|gchar
modifier|*
name|display
decl_stmt|;
DECL|typedef|combobox_int_tag
block|}
name|combobox_int_tag
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon29f91ffe0508
block|{
DECL|member|header
name|gchar
modifier|*
name|header
decl_stmt|;
DECL|member|type
name|gchar
modifier|*
name|type
decl_stmt|;
DECL|member|size
name|gint32
name|size
decl_stmt|;
DECL|typedef|TranslateHeaderTag
block|}
name|TranslateHeaderTag
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon29f91ffe0608
block|{
DECL|member|id
name|gchar
modifier|*
name|id
decl_stmt|;
DECL|member|tag
name|gchar
modifier|*
name|tag
decl_stmt|;
DECL|member|mode
name|gchar
modifier|*
name|mode
decl_stmt|;
DECL|member|other_tag_index
name|gint32
name|other_tag_index
decl_stmt|;
DECL|member|tag_type
name|gint32
name|tag_type
decl_stmt|;
DECL|typedef|TranslateTag
block|}
name|TranslateTag
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __METADATA_MISC_H__ */
end_comment

end_unit
