begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * GIMP Dynamic Text -- This is a plug-in for The GIMP 1.0  * Copyright (C) 1998,1999 Marco Lamberto<lm@geocities.com>  * Web page: http://www.geocities.com/Tokyo/1474/gimp/  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  * $Id$  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_CHARMAP_H_
end_ifndef

begin_define
DECL|macro|_CHARMAP_H_
define|#
directive|define
name|_CHARMAP_H_
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
DECL|macro|CHARMAP (obj)
define|#
directive|define
name|CHARMAP
parameter_list|(
name|obj
parameter_list|)
value|GTK_CHECK_CAST(obj, charmap_get_type(), CharMap)
DECL|macro|CHARMAP_CLASS (klass)
define|#
directive|define
name|CHARMAP_CLASS
parameter_list|(
name|klass
parameter_list|)
value|GTK_CHECK_CLASS_CAST(klass, charmap_get_type(), CharMapClass)
DECL|macro|IS_CHARMAP (obj)
define|#
directive|define
name|IS_CHARMAP
parameter_list|(
name|obj
parameter_list|)
value|GTK_CHECK_TYPE(obj, charmap_get_type())
DECL|typedef|CharMap
typedef|typedef
name|struct
name|_CharMap
name|CharMap
typedef|;
DECL|typedef|CharMapClass
typedef|typedef
name|struct
name|_CharMapClass
name|CharMapClass
typedef|;
DECL|struct|_CharMap
struct|struct
name|_CharMap
block|{
DECL|member|vbox
name|GtkVBox
name|vbox
decl_stmt|;
DECL|member|buttons
name|GtkWidget
modifier|*
name|buttons
index|[
literal|256
index|]
decl_stmt|;
DECL|member|width
name|gint
name|width
decl_stmt|;
DECL|member|height
name|gint
name|height
decl_stmt|;
DECL|member|current_char
name|gint32
name|current_char
decl_stmt|;
block|}
struct|;
DECL|struct|_CharMapClass
struct|struct
name|_CharMapClass
block|{
DECL|member|parent_class
name|GtkVBoxClass
name|parent_class
decl_stmt|;
DECL|member|char_selected
name|void
function_decl|(
modifier|*
name|char_selected
function_decl|)
parameter_list|(
name|CharMap
modifier|*
name|cm
parameter_list|)
function_decl|;
block|}
struct|;
name|guint
name|charmap_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
name|GtkWidget
modifier|*
name|charmap_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
name|void
name|charmap_set_font
parameter_list|(
name|CharMap
modifier|*
name|cm
parameter_list|,
name|GdkFont
modifier|*
name|font
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
comment|/* _CHARMAP_H_ */
end_comment

begin_comment
comment|/* vim: set ts=2 sw=2 tw=79 ai nowrap: */
end_comment

end_unit

