begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* gap_mpege.h  * 1998.07.04 hof (Wolfgang Hofer)  *  * GAP ... Gimp Animation Plugins  *  *  */
end_comment

begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* revision history:  * 0.96.00; 1998/07/02   hof: first release  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_GAP_MPEGE_H
end_ifndef

begin_define
DECL|macro|_GAP_MPEGE_H
define|#
directive|define
name|_GAP_MPEGE_H
end_define

begin_include
include|#
directive|include
file|"libgimp/gimp.h"
end_include

begin_comment
comment|/* Animation sizechange modes */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c8a2cec0103
block|{
DECL|enumerator|MPEG_ENCODE
name|MPEG_ENCODE
DECL|enumerator|MPEG2ENCODE
block|,
name|MPEG2ENCODE
DECL|typedef|t_gap_mpeg_encoder
block|}
name|t_gap_mpeg_encoder
typedef|;
end_typedef

begin_function_decl
name|int
name|gap_mpeg_encode
parameter_list|(
name|GimpRunModeType
name|run_mode
parameter_list|,
name|gint32
name|image_id
parameter_list|,
name|t_gap_mpeg_encoder
name|encoder
comment|/* ,                              char   *output,                              gint    bitrate,                              gdouble framerate                            */
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

end_unit

