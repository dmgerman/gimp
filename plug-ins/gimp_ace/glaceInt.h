begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  See the file COPYING for details.  *  */
end_comment

begin_include
include|#
directive|include
file|"glace.h"
end_include

begin_comment
comment|/* GLACE_GIMP implements these as macros, not functions. */
end_comment

begin_comment
comment|/* But this is wrapper-specific stuff, so that should be okay, right? */
end_comment

begin_comment
comment|/*   * The alternative would be just to #ifdef them out and define macros  * in glaceG.c [jas].  */
end_comment

begin_ifdef
ifdef|#
directive|ifdef
name|GLACE_GIMP
end_ifdef

begin_define
DECL|macro|GlaceWMalloc (size)
define|#
directive|define
name|GlaceWMalloc
parameter_list|(
name|size
parameter_list|)
value|g_malloc(size)
end_define

begin_define
DECL|macro|GlaceWRealloc (p,size)
define|#
directive|define
name|GlaceWRealloc
parameter_list|(
name|p
parameter_list|,
name|size
parameter_list|)
value|g_realloc(p, size)
end_define

begin_define
DECL|macro|GlaceWCalloc (nObj,size)
define|#
directive|define
name|GlaceWCalloc
parameter_list|(
name|nObj
parameter_list|,
name|size
parameter_list|)
value|g_malloc0((size) * (nObj))
end_define

begin_define
DECL|macro|GlaceWFree (ptr)
define|#
directive|define
name|GlaceWFree
parameter_list|(
name|ptr
parameter_list|)
value|g_free(ptr)
end_define

begin_else
else|#
directive|else
end_else

begin_function_decl
name|void
modifier|*
name|GlaceWMalloc
parameter_list|(
name|size_t
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
modifier|*
name|GlaceWRealloc
parameter_list|(
name|void
modifier|*
name|p
parameter_list|,
name|size_t
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
modifier|*
name|GlaceWCalloc
parameter_list|(
name|size_t
name|nObj
parameter_list|,
name|size_t
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|GlaceWFree
parameter_list|(
name|void
modifier|*
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
literal|0
end_if

begin_if
if|#
directive|if
name|__STDC__
end_if

begin_define
define|#
directive|define
name|ARGS
parameter_list|(
name|alist
parameter_list|)
value|alist
end_define

begin_else
else|#
directive|else
end_else

begin_comment
comment|/*__STDC__*/
end_comment

begin_define
define|#
directive|define
name|ARGS
parameter_list|(
name|alist
parameter_list|)
value|()
end_define

begin_define
define|#
directive|define
name|const
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*__STDC__*/
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  * For glaceCfg.c  */
end_comment

begin_define
DECL|macro|HLB
define|#
directive|define
name|HLB
value|15
end_define

begin_define
DECL|macro|BIG_TMP_BITS
define|#
directive|define
name|BIG_TMP_BITS
value|31
end_define

begin_define
DECL|macro|MID_TMP_BITS
define|#
directive|define
name|MID_TMP_BITS
value|15
end_define

begin_define
DECL|macro|ACC_BITS
define|#
directive|define
name|ACC_BITS
value|14
end_define

begin_define
DECL|macro|OUT_BITS
define|#
directive|define
name|OUT_BITS
value|8
end_define

begin_define
DECL|macro|AFT_FILTVAL
define|#
directive|define
name|AFT_FILTVAL
value|ldexp(255.0, BIG_TMP_BITS-8)
end_define

begin_define
DECL|macro|MAFT_FILTVAL
define|#
directive|define
name|MAFT_FILTVAL
value|ldexp(255.0, MID_TMP_BITS-8)
end_define

begin_define
DECL|macro|BSHIFT
define|#
directive|define
name|BSHIFT
value|(BIG_TMP_BITS-HLB)
end_define

begin_define
DECL|macro|MSHIFT
define|#
directive|define
name|MSHIFT
value|(MID_TMP_BITS-HLB)
end_define

begin_define
DECL|macro|NOT_FILTVAL
define|#
directive|define
name|NOT_FILTVAL
value|ldexp(255.0, HLB-8-1)
end_define

begin_define
DECL|macro|FORCE_NO_BIT_SHIFT
define|#
directive|define
name|FORCE_NO_BIT_SHIFT
value|(-1000)
end_define

begin_define
DECL|macro|MAX_BIT_SHIFT
define|#
directive|define
name|MAX_BIT_SHIFT
value|(32)
end_define

begin_define
DECL|macro|MAX_MESSAGE_LEN
define|#
directive|define
name|MAX_MESSAGE_LEN
value|150
end_define

end_unit

