begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|__CPERCEP_H__
end_ifndef

begin_define
DECL|macro|__CPERCEP_H__
define|#
directive|define
name|__CPERCEP_H__
end_define

begin_comment
comment|/* Copyright (C) 1997-2002 Adam D. Moss (the "Author").  All Rights Reserved.  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is fur- nished to do so, subject to the following conditions:  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FIT- NESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CON- NECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.  Except as contained in this notice, the name of the Author of the Software shall not be used in advertising or otherwise to promote the sale, use or other dealings in this Software without prior written authorization from the Author. */
end_comment

begin_comment
comment|/*   cpercep.c: The CPercep Functions v0.9: 2002-02-10   Adam D. Moss: adam@gimp.org<http://www.foxbox.org/adam/code/cpercep/>    TODO: document functions, rename erroneously-named arguments */
end_comment

begin_function_decl
name|void
name|init_conversions
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|rgb_to_space
parameter_list|(
name|double
name|inr
parameter_list|,
name|double
name|ing
parameter_list|,
name|double
name|inb
parameter_list|,
name|double
modifier|*
name|outr
parameter_list|,
name|double
modifier|*
name|outg
parameter_list|,
name|double
modifier|*
name|outb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|space_to_rgb
parameter_list|(
name|double
name|inr
parameter_list|,
name|double
name|ing
parameter_list|,
name|double
name|inb
parameter_list|,
name|double
modifier|*
name|outr
parameter_list|,
name|double
modifier|*
name|outg
parameter_list|,
name|double
modifier|*
name|outb
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* This is in the header so that it can potentially be inlined. */
end_comment

begin_function
specifier|static
specifier|const
name|double
DECL|function|distance_space (const double L1,const double a1,const double b1,const double L2,const double a2,const double b2)
name|distance_space
parameter_list|(
specifier|const
name|double
name|L1
parameter_list|,
specifier|const
name|double
name|a1
parameter_list|,
specifier|const
name|double
name|b1
parameter_list|,
specifier|const
name|double
name|L2
parameter_list|,
specifier|const
name|double
name|a2
parameter_list|,
specifier|const
name|double
name|b2
parameter_list|)
block|{
specifier|const
name|double
name|Ld
init|=
name|L1
operator|-
name|L2
decl_stmt|;
specifier|const
name|double
name|ad
init|=
name|a1
operator|-
name|a2
decl_stmt|;
specifier|const
name|double
name|bd
init|=
name|b1
operator|-
name|b2
decl_stmt|;
return|return
operator|(
name|Ld
operator|*
name|Ld
operator|+
name|ad
operator|*
name|ad
operator|+
name|bd
operator|*
name|bd
operator|)
return|;
block|}
end_function

begin_comment
comment|/* EXPERIMENTAL */
end_comment

begin_if
if|#
directive|if
literal|0
end_if

begin_comment
unit|void mix_colours (const double L1, const double a1, const double b1, 	     const double L2, const double a2, const double b2, 	     double *rtnL, double *rtna, double *rtnb, 	     double mass1, double mass2);
comment|/* util function */
end_comment

begin_define
unit|const double xscaler(const double start, const double end, 	const double me, const double him);
define|#
directive|define
name|MF
parameter_list|(
name|L
parameter_list|)
value|((L)<=0.0 ? 0.0 : 1.0)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* EXPERIMENTAL */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __CPERCEP_H__ */
end_comment

end_unit

