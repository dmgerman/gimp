begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* docindexif.h - Interface file for the docindex for gimp.  *  * Copyright (C) 1998 Chris Lahey.  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2, or (at your option)  * any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__DOCINDEXIF_H__
end_ifndef

begin_define
DECL|macro|__DOCINDEXIF_H__
define|#
directive|define
name|__DOCINDEXIF_H__
end_define

begin_include
include|#
directive|include
file|<ctype.h>
end_include

begin_include
include|#
directive|include
file|<gdk/gdkprivate.h>
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_include
include|#
directive|include
file|"gimage.h"
end_include

begin_include
include|#
directive|include
file|"fileops.h"
end_include

begin_include
include|#
directive|include
file|"file_new_dialog.h"
end_include

begin_include
include|#
directive|include
file|"commands.h"
end_include

begin_function_decl
name|void
name|open_or_raise
parameter_list|(
name|gchar
modifier|*
name|file_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|raise_if_match
parameter_list|(
name|gpointer
name|data
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|exit_from_go
parameter_list|()
function_decl|;
end_function_decl

begin_function_decl
name|void
name|open_file_in_position
parameter_list|(
name|gchar
modifier|*
name|filename
parameter_list|,
name|gint
name|position
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkMenuFactory
modifier|*
name|create_idea_menu
parameter_list|()
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|create_idea_toolbar
parameter_list|()
function_decl|;
end_function_decl

begin_function_decl
name|void
name|clear_white
parameter_list|(
name|FILE
modifier|*
name|fp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|getinteger
parameter_list|(
name|FILE
modifier|*
name|fp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|append2
parameter_list|(
name|gchar
modifier|*
name|string1
parameter_list|,
name|gboolean
name|del1
parameter_list|,
name|gchar
modifier|*
name|string2
parameter_list|,
name|gboolean
name|del2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|reset_usize
parameter_list|(
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|IDEAPATH
define|#
directive|define
name|IDEAPATH
value|"/" GIMPDIR "/ideas"
end_define

begin_struct
DECL|struct|bool_char_pair
struct|struct
name|bool_char_pair
block|{
DECL|member|boole
name|gboolean
name|boole
decl_stmt|;
DECL|member|string
name|gchar
modifier|*
name|string
decl_stmt|;
block|}
struct|;
end_struct

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __DOCINDEXIF_H__ */
end_comment

end_unit

