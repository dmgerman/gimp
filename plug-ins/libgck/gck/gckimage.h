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
comment|/* Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307,   */
end_comment

begin_comment
comment|/* USA.                                                                    */
end_comment

begin_comment
comment|/***************************************************************************/
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GCKIMAGE_H__
end_ifndef

begin_define
DECL|macro|_
define|#
directive|define
name|_
value|-GCKIMAGE_H__
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
DECL|struct|__anon2bd5a2920108
typedef|typedef
struct|struct
block|{
DECL|member|width
name|guint
name|width
decl_stmt|;
DECL|member|height
name|guint
name|height
decl_stmt|;
DECL|member|indextab
name|unsigned
name|long
modifier|*
name|indextab
decl_stmt|;
DECL|member|numbytes
name|unsigned
name|long
modifier|*
name|numbytes
decl_stmt|;
DECL|member|rowsize
name|unsigned
name|long
modifier|*
name|rowsize
decl_stmt|;
DECL|member|data
name|guchar
modifier|*
name|data
decl_stmt|;
DECL|typedef|RGBImage
block|}
name|RGBImage
typedef|;
name|RGBImage
modifier|*
name|RGB_image_new
parameter_list|(
name|guint
name|width
parameter_list|,
name|guint
name|height
parameter_list|)
function_decl|;
name|void
name|RGB_image_destroy
parameter_list|(
name|RGBImage
modifier|*
name|image
parameter_list|)
function_decl|;
name|void
name|RGB_image_fill
parameter_list|(
name|RGBImage
modifier|*
name|image
parameter_list|,
name|guchar
name|red
parameter_list|,
name|guchar
name|green
parameter_list|,
name|guchar
name|blue
parameter_list|)
function_decl|;
name|void
name|RGB_image_draw_rectangle
parameter_list|(
name|RGBImage
modifier|*
name|image
parameter_list|,
name|gint
name|filled
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|guchar
name|red
parameter_list|,
name|guchar
name|green
parameter_list|,
name|guchar
name|blue
parameter_list|)
function_decl|;
name|void
name|RGB_image_draw_line
parameter_list|(
name|RGBImage
modifier|*
name|image
parameter_list|,
name|int
name|x1
parameter_list|,
name|int
name|y1
parameter_list|,
name|int
name|x2
parameter_list|,
name|int
name|y2
parameter_list|,
name|guchar
name|red
parameter_list|,
name|guchar
name|green
parameter_list|,
name|guchar
name|blue
parameter_list|)
function_decl|;
name|void
name|RGB_image_draw_arc
parameter_list|(
name|RGBImage
modifier|*
name|image
parameter_list|,
name|gint
name|filled
parameter_list|,
name|int
name|x
parameter_list|,
name|int
name|y
parameter_list|,
name|guint
name|radius
parameter_list|,
name|guint
name|angle1
parameter_list|,
name|guint
name|angle2
parameter_list|,
name|guchar
name|red
parameter_list|,
name|guchar
name|green
parameter_list|,
name|guchar
name|blue
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

