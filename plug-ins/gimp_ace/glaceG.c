begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* :PREAMBLE: GlaceG.c  *  * Wrapper-specific Code:  *           GIMP plug-in version  *  * Based on glaceT.c and glaceP.c by J.Alex Stark  * g_ified by Kevin M. Turner  */
end_comment

begin_comment
comment|/*  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  See the file COPYING for details.  *  */
end_comment

begin_comment
comment|/* :HEADERS:  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|GLACE_GIMP
end_ifndef

begin_define
DECL|macro|GLACE_GIMP
define|#
directive|define
name|GLACE_GIMP
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|"glaceInt.h"
end_include

begin_include
include|#
directive|include
file|<ctype.h>
end_include

begin_comment
comment|/* for tolower in keymatch */
end_comment

begin_comment
comment|/* Other things we're implementing  * Included first, because glace.h needs to know about it.  */
end_comment

begin_comment
comment|/* :*** Internal Functions ***:  * GlaceWMalloc,Realloc,Calloc, and Free  * have been implemented as defines in an #ifdef block in glaceInt.h  * Ugly, but true.  */
end_comment

begin_comment
comment|/**************************************************************/
end_comment

begin_comment
comment|/* :*** Errors and Messages ***:   * :FUNCTION: Glace_WError  */
end_comment

begin_function
name|int
comment|/* Sets error and returns error flag (but may exit) */
DECL|function|Glace_WError (Glace_WData wData,char * argErrStr)
name|Glace_WError
parameter_list|(
name|Glace_WData
name|wData
parameter_list|,
name|char
modifier|*
name|argErrStr
parameter_list|)
block|{
if|if
condition|(
name|wData
operator|==
name|NULL
condition|)
name|g_warning
argument_list|(
literal|"Fatal error (error rountine called"
literal|" with invalid package data structure."
argument_list|)
expr_stmt|;
name|WRAPPER
argument_list|(
name|errorValue
argument_list|)
operator|=
name|GLACE_ERROR
expr_stmt|;
name|g_warning
argument_list|(
name|argErrStr
argument_list|)
expr_stmt|;
return|return
name|GLACE_ERROR
return|;
block|}
end_function

begin_comment
comment|/*  * :FUNCTION: Glace_WErrorValue  */
end_comment

begin_function
name|int
comment|/* Returns error flag */
DECL|function|Glace_WErrorValue (Glace_WData wData)
name|Glace_WErrorValue
parameter_list|(
name|Glace_WData
name|wData
parameter_list|)
block|{
return|return
name|WRAPPER
argument_list|(
name|errorValue
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  * :FUNCTION: Glace_WIsError  */
end_comment

begin_function
name|int
comment|/* Returns boolean */
DECL|function|Glace_WIsError (Glace_WData wData)
name|Glace_WIsError
parameter_list|(
name|Glace_WData
name|wData
parameter_list|)
block|{
return|return
operator|(
name|WRAPPER
argument_list|(
name|errorValue
argument_list|)
operator|==
name|GLACE_ERROR
operator|)
return|;
block|}
end_function

begin_comment
comment|/*  * :FUNCTION: Glace_WMessage  */
end_comment

begin_decl_stmt
name|void
DECL|function|Glace_WMessage (GLACE_OVAR (Glace_WData wData),char * messageStr)
name|Glace_WMessage
argument_list|(
name|GLACE_OVAR
argument_list|(
argument|Glace_WData wData
argument_list|)
argument_list|,
name|char
operator|*
name|messageStr
argument_list|)
block|{
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"%s"
argument_list|,
name|messageStr
argument_list|)
expr_stmt|;
block|}
end_decl_stmt

begin_comment
comment|/**************************************************************/
end_comment

begin_comment
comment|/* :*** Wrapper-specific Setup ***:   * :FUNCTION: Glace_WInit  */
end_comment

begin_decl_stmt
name|void
DECL|function|Glace_WInit (GLACE_OVAR (Glace_WData wData))
name|Glace_WInit
argument_list|(
name|GLACE_OVAR
argument_list|(
argument|Glace_WData wData
argument_list|)
argument_list|)
block|{
ifdef|#
directive|ifdef
name|__EMX__
name|_fsetmode
argument_list|(
name|stdin
argument_list|,
literal|"b"
argument_list|)
expr_stmt|;
name|_fsetmode
argument_list|(
name|stdout
argument_list|,
literal|"b"
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
end_decl_stmt

begin_comment
comment|/**************************************************************/
end_comment

begin_comment
comment|/*  * :FUNCTION: Glace_WWrapTell  */
end_comment

begin_function
name|Glace_WrapTypes
DECL|function|Glace_WWrapTell ()
name|Glace_WWrapTell
parameter_list|()
block|{
return|return
name|GLACE_GIMP_VER
return|;
block|}
end_function

begin_comment
comment|/**************************************************************/
end_comment

begin_comment
comment|/*  * :FUNCTION: Glace_WDataAlloc  */
end_comment

begin_function
name|Glace_WData
DECL|function|Glace_WDataAlloc ()
name|Glace_WDataAlloc
parameter_list|()
block|{
return|return
operator|(
name|Glace_WData
operator|)
name|GlaceWMalloc
argument_list|(
sizeof|sizeof
argument_list|(
name|GlaceGimpData
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/* :*** Argument Parsing and Warning ***:   * :FUNCTION: Glace_WKeyMatch  *  * NB This is an independent rewrite of PBMPLUS routine,  * just to be sure about copyright issues. [Alex]  *  * (Probably not necessary for GIMP version.  Feel free to substitute  * pm_keymatch back in...) [kmt]  */
end_comment

begin_function
name|int
DECL|function|Glace_WKeyMatch (char * str,char * keyword,int minchars)
name|Glace_WKeyMatch
parameter_list|(
name|char
modifier|*
name|str
parameter_list|,
name|char
modifier|*
name|keyword
parameter_list|,
name|int
name|minchars
parameter_list|)
block|{
name|int
name|i
decl_stmt|,
name|slen
decl_stmt|;
name|slen
operator|=
name|strlen
argument_list|(
name|str
argument_list|)
expr_stmt|;
if|if
condition|(
name|slen
operator|<
name|minchars
condition|)
return|return
literal|0
return|;
elseif|else
if|if
condition|(
name|slen
operator|>
operator|(
name|int
operator|)
name|strlen
argument_list|(
name|keyword
argument_list|)
condition|)
return|return
literal|0
return|;
else|else
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|slen
condition|;
name|i
operator|++
control|)
if|if
condition|(
name|tolower
argument_list|(
name|str
index|[
name|i
index|]
argument_list|)
operator|!=
name|tolower
argument_list|(
name|keyword
index|[
name|i
index|]
argument_list|)
condition|)
return|return
literal|0
return|;
return|return
literal|1
return|;
block|}
end_function

begin_comment
comment|/**************************************************************/
end_comment

begin_comment
comment|/*  * :FUNCTION: Glace_WUsage  */
end_comment

begin_function
name|void
DECL|function|Glace_WUsage (Glace_WData wData,char * usage)
name|Glace_WUsage
parameter_list|(
name|Glace_WData
name|wData
parameter_list|,
name|char
modifier|*
name|usage
parameter_list|)
block|{
name|Glace_WMessage
argument_list|(
name|wData
argument_list|,
name|usage
argument_list|)
expr_stmt|;
name|WRAPPER
argument_list|(
name|errorValue
argument_list|)
operator|=
name|GLACE_ERROR
expr_stmt|;
block|}
end_function

begin_comment
comment|/* :*** Image Input and Output ***:   * :FUNCTION: FIXME Glace_WOpenImage   */
end_comment

begin_decl_stmt
name|void
DECL|function|Glace_WOpenImage (GLACE_OVAR (Glace_WData wData),GLACE_OVAR (Glace_CfgInfo * cfgInfoPtr),char * name,Glace_ImageHandle * handlePtr)
name|Glace_WOpenImage
argument_list|(
name|GLACE_OVAR
argument_list|(
argument|Glace_WData wData
argument_list|)
argument_list|,
name|GLACE_OVAR
argument_list|(
name|Glace_CfgInfo
operator|*
name|cfgInfoPtr
argument_list|)
argument_list|,
name|char
operator|*
name|name
argument_list|,
name|Glace_ImageHandle
operator|*
name|handlePtr
argument_list|)
block|{
comment|/* g_print(" *** Glace_WOpenImage doesn't do jack! ***\n"); */
block|}
end_decl_stmt

begin_comment
comment|/**************************************************************/
end_comment

begin_comment
comment|/*  * :FUNCTION: FIXME Glace_WPutImgStart  * Here we initalize a pixel region to write to,   * and set the output pointer to the temp space.  */
end_comment

begin_decl_stmt
name|void
DECL|function|Glace_WPutImgStart (GLACE_OVAR (Glace_WData wData),GLACE_OVAR (Glace_CfgInfo * cfgInfoPtr),Glace_ImgArrays * imgArraysPtr)
name|Glace_WPutImgStart
argument_list|(
name|GLACE_OVAR
argument_list|(
argument|Glace_WData wData
argument_list|)
argument_list|,
name|GLACE_OVAR
argument_list|(
name|Glace_CfgInfo
operator|*
name|cfgInfoPtr
argument_list|)
argument_list|,
name|Glace_ImgArrays
operator|*
name|imgArraysPtr
argument_list|)
block|{
comment|/* gimp_pixel_rgn_init (GPixelRgn *pr, 		     GDrawable *drawable, 		     int       x, 		     int       y, 		     int       width, 		     int       height, 		     int       dirty, 		     int       shadow) */
comment|/*  puts(" *** I am Glace_WPutImgStart, here me roar! ***"); */
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|WRAPPER
argument_list|(
name|dest_rgn_ptr
argument_list|)
argument_list|,
name|WRAPPER
argument_list|(
name|drawable_ptr
argument_list|)
argument_list|,
name|WRAPPER
argument_list|(
name|gimp_x0
argument_list|)
argument_list|,
name|WRAPPER
argument_list|(
name|gimp_y0
argument_list|)
argument_list|,
name|GLACE_IMG
argument_list|(
name|cols
argument_list|)
argument_list|,
name|GLACE_IMG
argument_list|(
name|rows
argument_list|)
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
comment|/* GLACE_IMG(putImgRowPtr)=(Glace_Gray *)GLACE_IMG(tmpImgPtr); */
name|GLACE_IMG
argument_list|(
name|putImgRowPtr
argument_list|)
operator|=
name|WRAPPER
argument_list|(
name|gimpImgPtr
argument_list|)
expr_stmt|;
block|}
end_decl_stmt

begin_comment
comment|/**************************************************************/
end_comment

begin_comment
comment|/*  * :FUNCTION: Glace_WPutImgRowStart  * (we don't use it)  */
end_comment

begin_decl_stmt
name|void
DECL|function|Glace_WPutImgRowStart (GLACE_OVAR (Glace_WData wData),GLACE_OVAR (Glace_CfgInfo * cfgInfoPtr),GLACE_OVAR (Glace_ImgArrays * imgArraysPtr),GLACE_OVAR (int row))
name|Glace_WPutImgRowStart
argument_list|(
name|GLACE_OVAR
argument_list|(
argument|Glace_WData wData
argument_list|)
argument_list|,
name|GLACE_OVAR
argument_list|(
name|Glace_CfgInfo
operator|*
name|cfgInfoPtr
argument_list|)
argument_list|,
name|GLACE_OVAR
argument_list|(
name|Glace_ImgArrays
operator|*
name|imgArraysPtr
argument_list|)
argument_list|,
name|GLACE_OVAR
argument_list|(
argument|int row
argument_list|)
argument_list|)
block|{  }
end_decl_stmt

begin_comment
comment|/**************************************************************/
end_comment

begin_comment
comment|/*  * :FUNCTION: FIXME Glace_WPutImgRowFinish  * It *should* take the row of data that has been produced and  * give it to the Gimp.  I think it does this, but the output  * sure doesn't look right.  */
end_comment

begin_decl_stmt
name|void
DECL|function|Glace_WPutImgRowFinish (GLACE_OVAR (Glace_WData wData),Glace_CfgInfo * cfgInfoPtr,Glace_ImgArrays * imgArraysPtr,GLACE_OVAR (int row))
name|Glace_WPutImgRowFinish
argument_list|(
name|GLACE_OVAR
argument_list|(
argument|Glace_WData wData
argument_list|)
argument_list|,
name|Glace_CfgInfo
operator|*
name|cfgInfoPtr
argument_list|,
name|Glace_ImgArrays
operator|*
name|imgArraysPtr
argument_list|,
name|GLACE_OVAR
argument_list|(
argument|int row
argument_list|)
argument_list|)
block|{
comment|/* If we were outputting by row, we'd do this: */
comment|/* gimp_pixel_rgn_set_row (GPixelRgn *pr,                              guchar   *buf,                              int       x, 			     int       y, 			     int       width) */
comment|/* gimp_pixel_rgn_set_row(&WRAPPER(dest_rgn_ptr), 	 		 GLACE_IMG(putImgRowPtr), 			 WRAPPER(gimp_x0), 			 WRAPPER(gimp_y0) + row, 			 GLACE_IMG(cols));*/
comment|/* But we're writing it all to a temp buffer instead... */
comment|/* Faster, and the temp buffer is already allocated. */
name|GLACE_IMG
argument_list|(
name|putImgRowPtr
argument_list|)
operator|+=
name|GLACE_IMG
argument_list|(
name|cols
argument_list|)
operator|*
name|WRAPPER
argument_list|(
name|drawable_ptr
argument_list|)
operator|->
name|bpp
expr_stmt|;
block|}
end_decl_stmt

begin_comment
comment|/**************************************************************/
end_comment

begin_comment
comment|/*  * :FUNCTION: Glace_WPutImgFinish  */
end_comment

begin_decl_stmt
name|void
DECL|function|Glace_WPutImgFinish (GLACE_OVAR (Glace_WData wData),GLACE_OVAR (Glace_CfgInfo * cfgInfoPtr),GLACE_OVAR (Glace_ImgArrays * imgArraysPtr))
name|Glace_WPutImgFinish
argument_list|(
name|GLACE_OVAR
argument_list|(
argument|Glace_WData wData
argument_list|)
argument_list|,
name|GLACE_OVAR
argument_list|(
name|Glace_CfgInfo
operator|*
name|cfgInfoPtr
argument_list|)
argument_list|,
name|GLACE_OVAR
argument_list|(
name|Glace_ImgArrays
operator|*
name|imgArraysPtr
argument_list|)
argument_list|)
block|{
comment|/* g_print("*** Glace_WPutImgFinish coming through. ***\n"); */
comment|/* We could do something like this to write the entire image      at one time instead of row by row. */
name|gimp_pixel_rgn_set_rect
argument_list|(
operator|&
name|WRAPPER
argument_list|(
name|dest_rgn_ptr
argument_list|)
argument_list|,
name|WRAPPER
argument_list|(
name|gimpImgPtr
argument_list|)
argument_list|,
name|WRAPPER
argument_list|(
name|gimp_x0
argument_list|)
argument_list|,
name|WRAPPER
argument_list|(
name|gimp_y0
argument_list|)
argument_list|,
name|GLACE_IMG
argument_list|(
name|cols
argument_list|)
argument_list|,
name|GLACE_IMG
argument_list|(
name|rows
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_drawable_flush
argument_list|(
name|WRAPPER
argument_list|(
name|drawable_ptr
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_drawable_merge_shadow
argument_list|(
name|WRAPPER
argument_list|(
name|drawable_ptr
argument_list|)
operator|->
name|id
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|WRAPPER
argument_list|(
name|drawable_ptr
argument_list|)
operator|->
name|id
argument_list|,
name|WRAPPER
argument_list|(
name|gimp_x0
argument_list|)
argument_list|,
name|WRAPPER
argument_list|(
name|gimp_y0
argument_list|)
argument_list|,
name|GLACE_IMG
argument_list|(
name|cols
argument_list|)
argument_list|,
name|GLACE_IMG
argument_list|(
name|rows
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_drawable_detach
argument_list|(
name|WRAPPER
argument_list|(
name|drawable_ptr
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_displays_flush
argument_list|()
expr_stmt|;
block|}
end_decl_stmt

begin_comment
comment|/**************************************************************/
end_comment

end_unit

