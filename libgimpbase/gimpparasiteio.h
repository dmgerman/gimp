begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpparasiteio.h  * Copyright (C) 1999 Tor Lillqvist<tml@iki.fi>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PARASITE_IO_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PARASITE_IO_H__
define|#
directive|define
name|__GIMP_PARASITE_IO_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look into the C source or the html documentation */
end_comment

begin_comment
comment|/*  Data structures for various standard parasites used by plug-ins and  *  the GIMP core, and functions to build and parse their string  *  representations.  */
end_comment

begin_comment
comment|/*  *  Pixmap brush pipes.  */
end_comment

begin_define
DECL|macro|GIMP_PIXPIPE_MAXDIM
define|#
directive|define
name|GIMP_PIXPIPE_MAXDIM
value|4
end_define

begin_typedef
DECL|typedef|GimpPixPipeParams
typedef|typedef
name|struct
name|_GimpPixPipeParams
name|GimpPixPipeParams
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpPixPipeParams
struct|struct
name|_GimpPixPipeParams
block|{
DECL|member|step
name|gint
name|step
decl_stmt|;
DECL|member|ncells
name|gint
name|ncells
decl_stmt|;
DECL|member|dim
name|gint
name|dim
decl_stmt|;
DECL|member|cols
name|gint
name|cols
decl_stmt|;
DECL|member|rows
name|gint
name|rows
decl_stmt|;
DECL|member|cellwidth
name|gint
name|cellwidth
decl_stmt|;
DECL|member|cellheight
name|gint
name|cellheight
decl_stmt|;
DECL|member|placement
name|gchar
modifier|*
name|placement
decl_stmt|;
DECL|member|free_placement_string
name|gboolean
name|free_placement_string
decl_stmt|;
DECL|member|rank
name|gint
name|rank
index|[
name|GIMP_PIXPIPE_MAXDIM
index|]
decl_stmt|;
DECL|member|selection
name|gchar
modifier|*
name|selection
index|[
name|GIMP_PIXPIPE_MAXDIM
index|]
decl_stmt|;
DECL|member|free_selection_string
name|gboolean
name|free_selection_string
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/* Initalize with dummy values */
end_comment

begin_function_decl
name|void
name|gimp_pixpipe_params_init
parameter_list|(
name|GimpPixPipeParams
modifier|*
name|params
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Parse a string into a GimpPixPipeParams */
end_comment

begin_function_decl
name|void
name|gimp_pixpipe_params_parse
parameter_list|(
specifier|const
name|gchar
modifier|*
name|parameters
parameter_list|,
name|GimpPixPipeParams
modifier|*
name|params
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Build a string representation of GimpPixPipeParams */
end_comment

begin_decl_stmt
name|gchar
modifier|*
name|gimp_pixpipe_params_build
argument_list|(
name|GimpPixPipeParams
operator|*
name|params
argument_list|)
name|G_GNUC_MALLOC
decl_stmt|;
end_decl_stmt

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PARASITE_IO_H__ */
end_comment

end_unit

