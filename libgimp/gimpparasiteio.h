begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* parasite.h  * Copyright (C) 1999 Tor Lillqvist<tml@iki.fi>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_PARASITEIO_H_
end_ifndef

begin_define
DECL|macro|_PARASITEIO_H_
DECL|macro|_PARASITEIO_H_
define|#
directive|define
name|_PARASITEIO_H_
end_define

begin_comment
comment|/* Data structures for various standard parasites used by plug-ins and  * the GIMP core, and functions to build and parse their string  * representations.  */
end_comment

begin_comment
comment|/*  * Pixmap brush pipes.  */
end_comment

begin_define
DECL|macro|PIXPIPE_MAXDIM
DECL|macro|PIXPIPE_MAXDIM
define|#
directive|define
name|PIXPIPE_MAXDIM
value|4
end_define

begin_typedef
DECL|struct|__anon2be6ba680108
DECL|struct|__anon2be6ba680208
typedef|typedef
struct|struct
block|{
DECL|member|step
DECL|member|step
name|gint
name|step
decl_stmt|;
DECL|member|ncells
DECL|member|ncells
name|gint
name|ncells
decl_stmt|;
DECL|member|dim
DECL|member|dim
name|gint
name|dim
decl_stmt|;
DECL|member|cols
DECL|member|cols
name|gint
name|cols
decl_stmt|;
DECL|member|rows
DECL|member|rows
name|gint
name|rows
decl_stmt|;
DECL|member|cellwidth
DECL|member|cellwidth
name|gint
name|cellwidth
decl_stmt|;
DECL|member|cellheight
DECL|member|cellheight
name|gint
name|cellheight
decl_stmt|;
DECL|member|placement
DECL|member|placement
name|gchar
modifier|*
name|placement
decl_stmt|;
DECL|member|free_placement_string
DECL|member|free_placement_string
name|gboolean
name|free_placement_string
decl_stmt|;
DECL|member|rank
DECL|member|rank
name|gint
name|rank
index|[
name|PIXPIPE_MAXDIM
index|]
decl_stmt|;
DECL|member|selection
DECL|member|selection
name|gchar
modifier|*
name|selection
index|[
name|PIXPIPE_MAXDIM
index|]
decl_stmt|;
DECL|member|free_selection_string
DECL|member|free_selection_string
name|gboolean
name|free_selection_string
decl_stmt|;
DECL|typedef|PixPipeParams
DECL|typedef|PixPipeParams
block|}
name|PixPipeParams
typedef|;
end_typedef

begin_comment
comment|/* Initalize with dummy values */
end_comment

begin_function_decl
name|void
name|pixpipeparams_init
parameter_list|(
name|PixPipeParams
modifier|*
name|params
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Parse a string into a PixPipeParams */
end_comment

begin_function_decl
name|void
name|pixpipeparams_parse
parameter_list|(
name|gchar
modifier|*
name|parameters
parameter_list|,
name|PixPipeParams
modifier|*
name|params
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Build a string representation of PixPipeParams */
end_comment

begin_function_decl
name|gchar
modifier|*
name|pixpipeparams_build
parameter_list|(
name|PixPipeParams
modifier|*
name|params
parameter_list|)
function_decl|;
end_function_decl

begin_ifdef
ifdef|#
directive|ifdef
name|__cplusplus
end_ifdef

begin_endif
unit|}
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
comment|/* _PARASITEIO_H_ */
end_comment

end_unit

