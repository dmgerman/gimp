begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/**************************************************  * file: megawidget/megawidget.h  *  * Copyright (c) 1997 Eric L. Hernes (erich@rrnet.com)  * All rights reserved.  *  * Redistribution and use in source and binary forms, with or without  * modification, are permitted provided that the following conditions  * are met:  * 1. Redistributions of source code must retain the above copyright  *    notice, this list of conditions and the following disclaimer.  * 2. The name of the author may not be used to endorse or promote products  *    derived from this software withough specific prior written permission  *  * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR  * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES  * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT  * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,  * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY  * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT  * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF  * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  *  * $Id$  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__MEGAWIDGET_H__
end_ifndef

begin_define
DECL|macro|__MEGAWIDGET_H__
define|#
directive|define
name|__MEGAWIDGET_H__
end_define

begin_struct
DECL|struct|mwPreview
struct|struct
name|mwPreview
block|{
DECL|member|width
name|gint
name|width
decl_stmt|;
DECL|member|height
name|gint
name|height
decl_stmt|;
DECL|member|bpp
name|gint
name|bpp
decl_stmt|;
DECL|member|scale
name|gdouble
name|scale
decl_stmt|;
DECL|member|bits
name|guchar
modifier|*
name|bits
decl_stmt|;
block|}
struct|;
end_struct

begin_ifndef
ifndef|#
directive|ifndef
name|PREVIEW_SIZE
end_ifndef

begin_define
DECL|macro|PREVIEW_SIZE
define|#
directive|define
name|PREVIEW_SIZE
value|100
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_decl_stmt
specifier|extern
name|gint
name|do_preview
decl_stmt|;
end_decl_stmt

begin_typedef
DECL|typedef|pvw
typedef|typedef
name|void
name|mw_preview_t
parameter_list|(
name|GtkWidget
modifier|*
name|pvw
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
name|GtkWidget
modifier|*
name|mw_preview_new
parameter_list|(
name|GtkWidget
modifier|*
name|parent
parameter_list|,
name|struct
name|mwPreview
modifier|*
name|mwp
parameter_list|,
name|mw_preview_t
modifier|*
name|fcn
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|struct
name|mwPreview
modifier|*
name|mw_preview_build
parameter_list|(
name|GDrawable
modifier|*
name|drw
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|struct
name|mwPreview
modifier|*
name|mw_preview_build_virgin
parameter_list|(
name|GDrawable
modifier|*
name|drw
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __MEGAWIDGET_H__ */
end_comment

end_unit

