begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/***************************************************************************/
end_comment

begin_comment
comment|/* GCK - The General Convenience Kit. Generally useful conveniece routines */
end_comment

begin_comment
comment|/* for GIMP plug-in writers and users of the GDK/GTK libraries.            */
end_comment

begin_comment
comment|/* Copyright (C) 1996 Tom Bech                                             */
end_comment

begin_comment
comment|/*                                                                         */
end_comment

begin_comment
comment|/* This program is free software; you can redistribute it and/or modify    */
end_comment

begin_comment
comment|/* it under the terms of the GNU General Public License as published by    */
end_comment

begin_comment
comment|/* the Free Software Foundation; either version 2 of the License, or       */
end_comment

begin_comment
comment|/* (at your option) any later version.                                     */
end_comment

begin_comment
comment|/*                                                                         */
end_comment

begin_comment
comment|/* This program is distributed in the hope that it will be useful,         */
end_comment

begin_comment
comment|/* but WITHOUT ANY WARRANTY; without even the implied warranty of          */
end_comment

begin_comment
comment|/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           */
end_comment

begin_comment
comment|/* GNU General Public License for more details.                            */
end_comment

begin_comment
comment|/*                                                                         */
end_comment

begin_comment
comment|/* You should have received a copy of the GNU General Public License       */
end_comment

begin_comment
comment|/* along with this program; if not, write to the Free Software             */
end_comment

begin_comment
comment|/* Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.               */
end_comment

begin_comment
comment|/***************************************************************************/
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GCKNOTEBOOK_H__
end_ifndef

begin_define
DECL|macro|__GCKNOTEBOOK_H__
define|#
directive|define
name|__GCKNOTEBOOK_H__
end_define

begin_include
include|#
directive|include
file|<gck/gck.h>
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
name|GckNoteBook
modifier|*
name|gck_notebook_new
parameter_list|(
name|GtkWidget
modifier|*
name|container
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|GtkPositionType
name|tab_position
parameter_list|)
function_decl|;
name|void
name|gck_notebook_destroy
parameter_list|(
name|GckNoteBook
modifier|*
name|notebook
parameter_list|)
function_decl|;
name|GckNoteBookPage
modifier|*
name|gck_notebook_page_new
parameter_list|(
name|gchar
modifier|*
name|label
parameter_list|,
name|GckNoteBook
modifier|*
name|notebook
parameter_list|)
function_decl|;
name|void
name|gck_notebook_insert_page
parameter_list|(
name|GckNoteBook
modifier|*
name|notebook
parameter_list|,
name|GckNoteBookPage
modifier|*
name|page
parameter_list|,
name|gint
name|position
parameter_list|)
function_decl|;
name|void
name|gck_notebook_append_page
parameter_list|(
name|GckNoteBook
modifier|*
name|notebook
parameter_list|,
name|GckNoteBookPage
modifier|*
name|page
parameter_list|)
function_decl|;
name|void
name|gck_notebook_prepend_page
parameter_list|(
name|GckNoteBook
modifier|*
name|notebook
parameter_list|,
name|GckNoteBookPage
modifier|*
name|page
parameter_list|)
function_decl|;
name|void
name|gck_notebook_remove_page
parameter_list|(
name|GckNoteBook
modifier|*
name|notebook
parameter_list|,
name|gint
name|page_num
parameter_list|)
function_decl|;
name|GckNoteBookPage
modifier|*
name|gck_notebook_get_page
parameter_list|(
name|GckNoteBook
modifier|*
name|notebook
parameter_list|)
function_decl|;
name|void
name|gck_notebook_set_page
parameter_list|(
name|GckNoteBook
modifier|*
name|notebook
parameter_list|,
name|gint
name|page_num
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

begin_endif
endif|#
directive|endif
end_endif

end_unit

