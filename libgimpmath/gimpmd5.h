begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  *  * gimpmd5.h  *  * This code implements the MD5 message-digest algorithm.  * The algorithm is due to Ron Rivest.  This code was  * written by Colin Plumb in 1993, no copyright is claimed.  * This code is in the public domain; do with it what you wish.  *  * Equivalent code is available from RSA Data Security, Inc.  * This code has been tested against that, and is equivalent,  * except that you don't need to include two pages of legalese  * with every copy.  *  * GIMPified 2002 by Sven Neumann<sven@gimp.org>  */
end_comment

begin_comment
comment|/* parts of this file are :  * Written March 1993 by Branko Lankester  * Modified June 1993 by Colin Plumb for altered md5.c.  * Modified October 1995 by Erik Troan for RPM  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_MD5_H__
end_ifndef

begin_define
DECL|macro|__GIMP_MD5_H__
define|#
directive|define
name|__GIMP_MD5_H__
end_define

begin_function_decl
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
name|void
name|gimp_md5_get_digest
parameter_list|(
specifier|const
name|gchar
modifier|*
name|buffer
parameter_list|,
name|gint
name|buffer_size
parameter_list|,
name|guchar
name|digest
index|[
literal|16
index|]
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_MD5_H__ */
end_comment

end_unit

