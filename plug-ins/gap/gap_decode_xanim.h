begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* gap_decode_xanim.h  * 1999.11.22 hof (Wolfgang Hofer)  *  * GAP ... Gimp Animation Plugins  *         Call xanim exporting edition (the loki version)  *         via shellscript gap_xanim_export.sh  *         To split any xanim supported video into  *         anim frames (single images on disk)  *         Audio Tracks can also be extracted.  *  */
end_comment

begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* revision history:  * 1.1.11b; 1999/11/22   hof: first release  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_GAP_XANIM_H
end_ifndef

begin_define
DECL|macro|_GAP_XANIM_H
define|#
directive|define
name|_GAP_XANIM_H
end_define

begin_include
include|#
directive|include
file|"libgimp/gimp.h"
end_include

begin_comment
comment|/* fileformats supported by gap_decode_xanim */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b72c8230103
block|{
DECL|enumerator|XAENC_XCF
name|XAENC_XCF
comment|/* no direct support by xanim, have to convert */
DECL|enumerator|XAENC_PPMRAW
block|,
name|XAENC_PPMRAW
DECL|enumerator|XAENC_JPEG
block|,
name|XAENC_JPEG
DECL|typedef|t_gap_xa_formats
block|}
name|t_gap_xa_formats
typedef|;
end_typedef

begin_function_decl
name|int
name|gap_xanim_decode
parameter_list|(
name|GimpRunModeType
name|run_mode
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

end_unit

