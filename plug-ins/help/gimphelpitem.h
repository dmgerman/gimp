begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * The GIMP Help plug-in  * Copyright (C) 1999-2004 Sven Neumann<sven@gimp.org>  *                         Michael Natterer<mitch@gimp.org>  *                         Henrik Brix Andersen<brix@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_HELP_ITEM_H__
end_ifndef

begin_define
DECL|macro|__GIMP_HELP_ITEM_H__
define|#
directive|define
name|__GIMP_HELP_ITEM_H__
end_define

begin_struct
DECL|struct|_GimpHelpItem
struct|struct
name|_GimpHelpItem
block|{
DECL|member|ref
name|gchar
modifier|*
name|ref
decl_stmt|;
DECL|member|title
name|gchar
modifier|*
name|title
decl_stmt|;
DECL|member|parent
name|gchar
modifier|*
name|parent
decl_stmt|;
comment|/* eek */
DECL|member|children
name|GList
modifier|*
name|children
decl_stmt|;
DECL|member|index
name|gint
name|index
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|GimpHelpItem
modifier|*
name|gimp_help_item_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|ref
parameter_list|,
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|parent
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_help_item_free
parameter_list|(
name|GimpHelpItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_HELP_ITEM_H__ */
end_comment

end_unit

