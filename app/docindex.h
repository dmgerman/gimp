begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* docindex.h - Header file for document index in gimp.  *  * Copyright (C) 1998 Chris Lahey.  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2, or (at your option)  * any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__DOCINDEX_H__
end_ifndef

begin_define
DECL|macro|__DOCINDEX_H__
define|#
directive|define
name|__DOCINDEX_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_typedef
DECL|struct|idea_manager
typedef|typedef
struct|struct
name|idea_manager
block|{
comment|/* The scrollbar */
DECL|member|vscrollbar
name|GtkWidget
modifier|*
name|vscrollbar
decl_stmt|,
comment|/* The GTK window */
DECL|member|window
modifier|*
name|window
decl_stmt|;
DECL|member|tree
name|GtkWidget
modifier|*
name|tree
decl_stmt|;
comment|/* The menufactory */
DECL|member|menubar
name|GtkMenuFactory
modifier|*
name|menubar
decl_stmt|;
comment|/* The window menu widget */
DECL|member|window_menu
name|GtkWidget
modifier|*
name|window_menu
decl_stmt|;
comment|/* The status bar widget */
DECL|member|status
name|GtkWidget
modifier|*
name|status
decl_stmt|;
comment|/* The main status context id */
DECL|member|contextid
name|guint
name|contextid
decl_stmt|;
DECL|member|changed
name|gboolean
name|changed
decl_stmt|;
DECL|member|named
name|gboolean
name|named
decl_stmt|;
DECL|member|title
name|gchar
modifier|*
name|title
decl_stmt|;
DECL|member|auto_save
name|gint
name|auto_save
decl_stmt|;
DECL|member|long_term_auto_save
name|gint
name|long_term_auto_save
decl_stmt|;
DECL|member|count
name|gint
name|count
decl_stmt|;
DECL|typedef|idea_manager
block|}
name|idea_manager
typedef|;
end_typedef

begin_function_decl
name|void
name|make_idea_window
parameter_list|(
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|open_idea_window
parameter_list|()
function_decl|;
end_function_decl

begin_function_decl
name|void
name|idea_add
parameter_list|(
name|gchar
modifier|*
name|label
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|idea_add_in_position
parameter_list|(
name|gchar
modifier|*
name|label
parameter_list|,
name|gint
name|position
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|raise_idea_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
specifier|extern
name|idea_manager
modifier|*
name|ideas
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __DOCINDEX_H__ */
end_comment

end_unit

