begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__MODREGISTER_H__
end_ifndef

begin_define
DECL|macro|__MODREGISTER_H__
define|#
directive|define
name|__MODREGISTER_H__
end_define

begin_ifdef
ifdef|#
directive|ifdef
name|__EMX__
end_ifdef

begin_struct
DECL|struct|main_funcs_struc
struct|struct
name|main_funcs_struc
block|{
DECL|member|name
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|member|func
name|void
function_decl|(
modifier|*
name|func
function_decl|)
parameter_list|()
function_decl|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|color_reg_func
typedef|typedef
name|GimpColorSelectorID
function_decl|(
modifier|*
name|color_reg_func
function_decl|)
parameter_list|(
specifier|const
name|char
modifier|*
parameter_list|,
specifier|const
name|char
modifier|*
parameter_list|,
name|GimpColorSelectorMethods
modifier|*
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|color_unreg_func
typedef|typedef
name|gboolean
function_decl|(
modifier|*
name|color_unreg_func
function_decl|)
parameter_list|(
name|GimpColorSelectorID
parameter_list|,
name|void
function_decl|(
modifier|*
function_decl|)
parameter_list|(
name|void
modifier|*
parameter_list|)
parameter_list|,
name|void
modifier|*
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
name|GimpColorSelectorID
name|mod_color_selector_register
parameter_list|(
specifier|const
name|char
modifier|*
name|name
parameter_list|,
specifier|const
name|char
modifier|*
name|help_page
parameter_list|,
name|GimpColorSelectorMethods
modifier|*
name|methods
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|mod_color_selector_unregister
parameter_list|(
name|GimpColorSelectorID
name|id
parameter_list|,
name|void
function_decl|(
modifier|*
name|callback
function_decl|)
parameter_list|(
name|void
modifier|*
name|data
parameter_list|)
parameter_list|,
name|void
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __MODREGISTER_H__  */
end_comment

end_unit

