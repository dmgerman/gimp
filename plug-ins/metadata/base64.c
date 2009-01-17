begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* base64.h - encode and decode base64 encoding according to RFC 2045  *  * Copyright (C) 2005, RaphaÃ«l Quinet<raphael@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/* Yet another implementation of base64 encoding and decoding.  I  * ended up writing this because most of the implementations that I  * found required a null-terminated buffer, some of the others did not  * ignore whitespace (especially those written for HTTP usage) and the  * rest were not compatible with the LGPL (some were GPL, not LGPL).  * Or at least I haven't been able to find LGPL implementations.  * Writing this according to RFC 2045 did not take long anyway.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|WITHOUT_GIMP
end_ifndef

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|"base64.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_else
else|#
directive|else
end_else

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|"base64.h"
end_include

begin_define
DECL|macro|_ (String)
define|#
directive|define
name|_
parameter_list|(
name|String
parameter_list|)
value|(String)
end_define

begin_define
DECL|macro|N_ (String)
define|#
directive|define
name|N_
parameter_list|(
name|String
parameter_list|)
value|(String)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
name|HAVE_STDIO_H
end_if

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
name|HAVE_STDLIB_H
end_if

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_decl_stmt
DECL|variable|base64_code
specifier|static
specifier|const
name|gchar
name|base64_code
index|[]
init|=
literal|"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|base64_6bits
specifier|static
specifier|const
name|gint
name|base64_6bits
index|[
literal|256
index|]
init|=
block|{
operator|-
literal|2
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|1
block|,
operator|-
literal|1
block|,
operator|-
literal|1
block|,
operator|-
literal|1
block|,
operator|-
literal|1
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|1
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
literal|62
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
literal|63
block|,
literal|52
block|,
literal|53
block|,
literal|54
block|,
literal|55
block|,
literal|56
block|,
literal|57
block|,
literal|58
block|,
literal|59
block|,
literal|60
block|,
literal|61
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|2
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
literal|0
block|,
literal|1
block|,
literal|2
block|,
literal|3
block|,
literal|4
block|,
literal|5
block|,
literal|6
block|,
literal|7
block|,
literal|8
block|,
literal|9
block|,
literal|10
block|,
literal|11
block|,
literal|12
block|,
literal|13
block|,
literal|14
block|,
literal|15
block|,
literal|16
block|,
literal|17
block|,
literal|18
block|,
literal|19
block|,
literal|20
block|,
literal|21
block|,
literal|22
block|,
literal|23
block|,
literal|24
block|,
literal|25
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
literal|26
block|,
literal|27
block|,
literal|28
block|,
literal|29
block|,
literal|30
block|,
literal|31
block|,
literal|32
block|,
literal|33
block|,
literal|34
block|,
literal|35
block|,
literal|36
block|,
literal|37
block|,
literal|38
block|,
literal|39
block|,
literal|40
block|,
literal|41
block|,
literal|42
block|,
literal|43
block|,
literal|44
block|,
literal|45
block|,
literal|46
block|,
literal|47
block|,
literal|48
block|,
literal|49
block|,
literal|50
block|,
literal|51
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|,
operator|-
literal|3
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* -1: skip whitespace, -2: end of input, -3: error */
end_comment

begin_comment
comment|/**  * base64_decode:  * @src_b64: input buffer containing base64-encoded data  * @src_size: input buffer size (in bytes) or -1 if @src_b64 is nul-terminated  * @dest: buffer in which the decoded data should be stored  * @dest_size: size of the destination buffer  * @ignore_errors: if #TRUE, skip all invalid characters (no data validation)  *  * Read base64-encoded data from the input buffer @src_b64 and write  * the decoded data into @dest.  *  * The base64 encoding uses 4 bytes for every 3 bytes of input, so  * @dest_size should be at least 3/4 of @src_size (or less if the  * input contains whitespace characters).  The base64 encoding has no  * reliable EOF marker, so this can cause additional data following  * the base64-encoded block to be misinterpreted if @src_size is not  * specified correctly.  The decoder will stop at the first nul byte  * or at the first '=' (padding byte) so you should ensure that one of  * these is present if you supply -1 for @src_size.  For more details  * about the base64 encoding, see RFC 2045, chapter 6.8.  *  * Returns: the number of bytes stored in @dest, or -1 if invalid data was found.  */
end_comment

begin_function
name|gssize
DECL|function|base64_decode (const gchar * src_b64,gsize src_size,gchar * dest,gsize dest_size,gboolean ignore_errors)
name|base64_decode
parameter_list|(
specifier|const
name|gchar
modifier|*
name|src_b64
parameter_list|,
name|gsize
name|src_size
parameter_list|,
name|gchar
modifier|*
name|dest
parameter_list|,
name|gsize
name|dest_size
parameter_list|,
name|gboolean
name|ignore_errors
parameter_list|)
block|{
name|gint32
name|decoded
decl_stmt|;
name|gssize
name|i
decl_stmt|;
name|gint
name|n
decl_stmt|;
name|gint
name|bits
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|src_b64
operator|!=
name|NULL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|dest
operator|!=
name|NULL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|decoded
operator|=
literal|0
expr_stmt|;
name|n
operator|=
literal|0
expr_stmt|;
name|bits
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
operator|(
name|src_size
operator|!=
literal|0
operator|)
operator|&&
operator|(
name|i
operator|+
literal|3
operator|<=
name|dest_size
operator|)
condition|;
name|src_b64
operator|++
operator|,
name|src_size
operator|--
control|)
block|{
name|bits
operator|=
name|base64_6bits
index|[
operator|(
name|int
operator|)
operator|*
name|src_b64
operator|&
literal|0xff
index|]
expr_stmt|;
if|if
condition|(
name|bits
operator|<
literal|0
condition|)
block|{
if|if
condition|(
name|bits
operator|==
operator|-
literal|2
condition|)
break|break;
elseif|else
if|if
condition|(
operator|(
name|bits
operator|==
operator|-
literal|3
operator|)
operator|&&
operator|!
name|ignore_errors
condition|)
return|return
operator|-
literal|1
return|;
else|else
continue|continue;
block|}
name|decoded
operator|<<=
literal|6
expr_stmt|;
name|decoded
operator|+=
name|bits
expr_stmt|;
if|if
condition|(
operator|++
name|n
operator|>=
literal|4
condition|)
block|{
comment|/* we have decoded 4 source chars => 24 bits of output (3 chars) */
name|dest
index|[
name|i
operator|++
index|]
operator|=
name|decoded
operator|>>
literal|16
expr_stmt|;
name|dest
index|[
name|i
operator|++
index|]
operator|=
operator|(
name|decoded
operator|>>
literal|8
operator|)
operator|&
literal|0xff
expr_stmt|;
name|dest
index|[
name|i
operator|++
index|]
operator|=
name|decoded
operator|&
literal|0xff
expr_stmt|;
name|decoded
operator|=
literal|0
expr_stmt|;
name|n
operator|=
literal|0
expr_stmt|;
block|}
block|}
if|if
condition|(
operator|(
name|n
operator|==
literal|3
operator|)
operator|&&
operator|(
name|i
operator|+
literal|2
operator|<=
name|dest_size
operator|)
condition|)
block|{
comment|/* 3 source chars (+ 1 padding "=") => 16 bits of output (2 chars) */
name|dest
index|[
name|i
operator|++
index|]
operator|=
name|decoded
operator|>>
literal|10
expr_stmt|;
name|dest
index|[
name|i
operator|++
index|]
operator|=
operator|(
name|decoded
operator|>>
literal|2
operator|)
operator|&
literal|0xff
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|(
name|n
operator|==
literal|2
operator|)
operator|&&
operator|(
name|i
operator|+
literal|1
operator|<=
name|dest_size
operator|)
condition|)
block|{
comment|/* 2 source chars (+ 2 padding "=") => 8 bits of output (1 char) */
name|dest
index|[
name|i
operator|++
index|]
operator|=
name|decoded
operator|>>
literal|4
expr_stmt|;
block|}
if|if
condition|(
name|i
operator|<
name|dest_size
condition|)
name|dest
index|[
name|i
index|]
operator|=
literal|0
expr_stmt|;
return|return
name|i
return|;
block|}
end_function

begin_comment
comment|/**  * base64_encode:  * @src: input buffer  * @src_size: input buffer size (in bytes) or -1 if @src is nul-terminated  * @dest_b64: buffer in which the base64 encoded data should be stored  * @dest_size: size of the destination buffer  * @columns: if> 0, add line breaks in the output after this many columns  *  * Read binary data from the input buffer @src and write  * base64-encoded data into @dest_b64.  *  * Since the base64 encoding uses 4 bytes for every 3 bytes of input,  * @dest_size should be at least 4/3 of @src_size, plus optional line  * breaks if @columns> 0 and up to two padding bytes at the end.  For  * more details about the base64 encoding, see RFC 2045, chapter 6.8.  * Note that RFC 2045 recommends setting @columns to 76.  *  * Returns: the number of bytes stored in @dest.  */
end_comment

begin_function
name|gssize
DECL|function|base64_encode (const gchar * src,gsize src_size,gchar * dest_b64,gsize dest_size,gint columns)
name|base64_encode
parameter_list|(
specifier|const
name|gchar
modifier|*
name|src
parameter_list|,
name|gsize
name|src_size
parameter_list|,
name|gchar
modifier|*
name|dest_b64
parameter_list|,
name|gsize
name|dest_size
parameter_list|,
name|gint
name|columns
parameter_list|)
block|{
name|guint32
name|bits
decl_stmt|;
name|gssize
name|i
decl_stmt|;
name|gint
name|n
decl_stmt|;
name|gint
name|c
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|src
operator|!=
name|NULL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|dest_b64
operator|!=
name|NULL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|n
operator|=
literal|0
expr_stmt|;
name|bits
operator|=
literal|0
expr_stmt|;
name|c
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
operator|(
name|src_size
operator|!=
literal|0
operator|)
operator|&&
operator|(
name|i
operator|+
literal|4
operator|<=
name|dest_size
operator|)
condition|;
name|src
operator|++
operator|,
name|src_size
operator|--
control|)
block|{
name|bits
operator|+=
operator|*
operator|(
name|guchar
operator|*
operator|)
name|src
expr_stmt|;
if|if
condition|(
operator|++
name|n
operator|==
literal|3
condition|)
block|{
name|dest_b64
index|[
name|i
operator|++
index|]
operator|=
name|base64_code
index|[
operator|(
name|bits
operator|>>
literal|18
operator|)
operator|&
literal|0x3f
index|]
expr_stmt|;
name|dest_b64
index|[
name|i
operator|++
index|]
operator|=
name|base64_code
index|[
operator|(
name|bits
operator|>>
literal|12
operator|)
operator|&
literal|0x3f
index|]
expr_stmt|;
name|dest_b64
index|[
name|i
operator|++
index|]
operator|=
name|base64_code
index|[
operator|(
name|bits
operator|>>
literal|6
operator|)
operator|&
literal|0x3f
index|]
expr_stmt|;
name|dest_b64
index|[
name|i
operator|++
index|]
operator|=
name|base64_code
index|[
name|bits
operator|&
literal|0x3f
index|]
expr_stmt|;
name|bits
operator|=
literal|0
expr_stmt|;
name|n
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|columns
operator|>
literal|0
condition|)
block|{
name|c
operator|+=
literal|4
expr_stmt|;
if|if
condition|(
operator|(
name|c
operator|>=
name|columns
operator|)
operator|&&
operator|(
name|i
operator|<
name|dest_size
operator|)
condition|)
block|{
name|dest_b64
index|[
name|i
operator|++
index|]
operator|=
literal|'\n'
expr_stmt|;
name|c
operator|=
literal|0
expr_stmt|;
block|}
block|}
block|}
else|else
block|{
name|bits
operator|<<=
literal|8
expr_stmt|;
block|}
block|}
if|if
condition|(
operator|(
name|n
operator|!=
literal|0
operator|)
operator|&&
operator|(
name|i
operator|+
literal|4
operator|<=
name|dest_size
operator|)
condition|)
block|{
if|if
condition|(
name|n
operator|==
literal|1
condition|)
block|{
name|dest_b64
index|[
name|i
operator|++
index|]
operator|=
name|base64_code
index|[
operator|(
name|bits
operator|>>
literal|10
operator|)
operator|&
literal|0x3f
index|]
expr_stmt|;
name|dest_b64
index|[
name|i
operator|++
index|]
operator|=
name|base64_code
index|[
operator|(
name|bits
operator|>>
literal|4
operator|)
operator|&
literal|0x3f
index|]
expr_stmt|;
name|dest_b64
index|[
name|i
operator|++
index|]
operator|=
literal|'='
expr_stmt|;
name|dest_b64
index|[
name|i
operator|++
index|]
operator|=
literal|'='
expr_stmt|;
block|}
else|else
block|{
name|dest_b64
index|[
name|i
operator|++
index|]
operator|=
name|base64_code
index|[
operator|(
name|bits
operator|>>
literal|18
operator|)
operator|&
literal|0x3f
index|]
expr_stmt|;
name|dest_b64
index|[
name|i
operator|++
index|]
operator|=
name|base64_code
index|[
operator|(
name|bits
operator|>>
literal|12
operator|)
operator|&
literal|0x3f
index|]
expr_stmt|;
name|dest_b64
index|[
name|i
operator|++
index|]
operator|=
name|base64_code
index|[
operator|(
name|bits
operator|>>
literal|6
operator|)
operator|&
literal|0x3f
index|]
expr_stmt|;
name|dest_b64
index|[
name|i
operator|++
index|]
operator|=
literal|'='
expr_stmt|;
block|}
block|}
if|if
condition|(
operator|(
name|columns
operator|>
literal|0
operator|)
operator|&&
operator|(
operator|(
name|c
operator|!=
literal|0
operator|)
operator|||
operator|(
name|n
operator|!=
literal|0
operator|)
operator|)
operator|&&
operator|(
name|i
operator|+
literal|1
operator|<
name|dest_size
operator|)
condition|)
name|dest_b64
index|[
name|i
operator|++
index|]
operator|=
literal|'\n'
expr_stmt|;
if|if
condition|(
name|i
operator|<
name|dest_size
condition|)
name|dest_b64
index|[
name|i
index|]
operator|=
literal|0
expr_stmt|;
return|return
name|i
return|;
block|}
end_function

end_unit

