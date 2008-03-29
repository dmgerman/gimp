begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  *  * gimpmd5.c  *  * This code implements the MD5 message-digest algorithm.  * The algorithm is due to Ron Rivest.  This code was  * written by Colin Plumb in 1993, no copyright is claimed.  * This code is in the public domain; do with it what you wish.  *  * Equivalent code is available from RSA Data Security, Inc.  * This code has been tested against that, and is equivalent,  * except that you don't need to include two pages of legalese  * with every copy.  *  * GIMPified 2002 by Sven Neumann<sven@gimp.org>  */
end_comment

begin_comment
comment|/* parts of this file are :  * Written March 1993 by Branko Lankester  * Modified June 1993 by Colin Plumb for altered md5.c.  * Modified October 1995 by Erik Troan for RPM  */
end_comment

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
file|<glib.h>
end_include

begin_undef
undef|#
directive|undef
name|GIMP_DISABLE_DEPRECATED
end_undef

begin_include
include|#
directive|include
file|"gimpmd5.h"
end_include

begin_typedef
DECL|typedef|GimpMD5Context
typedef|typedef
name|struct
name|_GimpMD5Context
name|GimpMD5Context
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpMD5Context
struct|struct
name|_GimpMD5Context
block|{
DECL|member|buf
name|guint32
name|buf
index|[
literal|4
index|]
decl_stmt|;
DECL|member|bits
name|guint32
name|bits
index|[
literal|2
index|]
decl_stmt|;
DECL|member|in
name|guchar
name|in
index|[
literal|64
index|]
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_md5_init
parameter_list|(
name|GimpMD5Context
modifier|*
name|ctx
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_md5_transform
parameter_list|(
name|guint32
name|buf
index|[
literal|4
index|]
parameter_list|,
specifier|const
name|guint32
name|in
index|[
literal|16
index|]
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_md5_update
parameter_list|(
name|GimpMD5Context
modifier|*
name|ctx
parameter_list|,
specifier|const
name|gchar
modifier|*
name|buf
parameter_list|,
name|guint32
name|len
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_md5_final
parameter_list|(
name|GimpMD5Context
modifier|*
name|ctx
parameter_list|,
name|guchar
name|digest
index|[
literal|16
index|]
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/**  * gimp_md5_get_digest:  * @buffer:      byte buffer  * @buffer_size: buffer size (in bytes) or -1 if @buffer is nul-terminated.  * @digest:      16 bytes buffer receiving the hash code.  *  * This function is deprecated! Use %GChecksum from GLib instead.  *  * Get the md5 hash of a buffer. The result is put in the 16 bytes  * buffer @digest. For more information see RFC 1321.  **/
end_comment

begin_function
name|void
DECL|function|gimp_md5_get_digest (const gchar * buffer,gint buffer_size,guchar digest[16])
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
block|{
name|GimpMD5Context
name|ctx
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|buffer
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|digest
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|buffer_size
operator|<
literal|0
condition|)
name|buffer_size
operator|=
name|strlen
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|gimp_md5_init
argument_list|(
operator|&
name|ctx
argument_list|)
expr_stmt|;
name|gimp_md5_update
argument_list|(
operator|&
name|ctx
argument_list|,
name|buffer
argument_list|,
name|buffer_size
argument_list|)
expr_stmt|;
name|gimp_md5_final
argument_list|(
operator|&
name|ctx
argument_list|,
name|digest
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
specifier|inline
name|void
DECL|function|byte_reverse (guint32 * buf,guint32 longs)
name|byte_reverse
parameter_list|(
name|guint32
modifier|*
name|buf
parameter_list|,
name|guint32
name|longs
parameter_list|)
block|{
if|#
directive|if
name|G_BYTE_ORDER
operator|!=
name|G_LITTLE_ENDIAN
do|do
block|{
operator|*
name|buf
operator|=
name|GINT32_TO_LE
argument_list|(
operator|*
name|buf
argument_list|)
expr_stmt|;
name|buf
operator|++
expr_stmt|;
block|}
do|while
condition|(
operator|--
name|longs
condition|)
do|;
endif|#
directive|endif
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_md5_init (GimpMD5Context * ctx)
name|gimp_md5_init
parameter_list|(
name|GimpMD5Context
modifier|*
name|ctx
parameter_list|)
block|{
name|ctx
operator|->
name|buf
index|[
literal|0
index|]
operator|=
literal|0x67452301
expr_stmt|;
name|ctx
operator|->
name|buf
index|[
literal|1
index|]
operator|=
literal|0xefcdab89
expr_stmt|;
name|ctx
operator|->
name|buf
index|[
literal|2
index|]
operator|=
literal|0x98badcfe
expr_stmt|;
name|ctx
operator|->
name|buf
index|[
literal|3
index|]
operator|=
literal|0x10325476
expr_stmt|;
name|ctx
operator|->
name|bits
index|[
literal|0
index|]
operator|=
literal|0
expr_stmt|;
name|ctx
operator|->
name|bits
index|[
literal|1
index|]
operator|=
literal|0
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_md5_update (GimpMD5Context * ctx,const gchar * buf,guint32 len)
name|gimp_md5_update
parameter_list|(
name|GimpMD5Context
modifier|*
name|ctx
parameter_list|,
specifier|const
name|gchar
modifier|*
name|buf
parameter_list|,
name|guint32
name|len
parameter_list|)
block|{
name|guint32
name|t
decl_stmt|;
comment|/* Update bitcount */
name|t
operator|=
name|ctx
operator|->
name|bits
index|[
literal|0
index|]
expr_stmt|;
if|if
condition|(
operator|(
name|ctx
operator|->
name|bits
index|[
literal|0
index|]
operator|=
name|t
operator|+
operator|(
operator|(
name|guint32
operator|)
name|len
operator|<<
literal|3
operator|)
operator|)
operator|<
name|t
condition|)
name|ctx
operator|->
name|bits
index|[
literal|1
index|]
operator|++
expr_stmt|;
comment|/* Carry from low to high */
name|ctx
operator|->
name|bits
index|[
literal|1
index|]
operator|+=
name|len
operator|>>
literal|29
expr_stmt|;
name|t
operator|=
operator|(
name|t
operator|>>
literal|3
operator|)
operator|&
literal|0x3f
expr_stmt|;
comment|/* Handle any leading odd-sized chunks */
if|if
condition|(
name|t
condition|)
block|{
name|guchar
modifier|*
name|p
init|=
operator|(
name|guchar
operator|*
operator|)
name|ctx
operator|->
name|in
operator|+
name|t
decl_stmt|;
name|t
operator|=
literal|64
operator|-
name|t
expr_stmt|;
if|if
condition|(
name|len
operator|<
name|t
condition|)
block|{
name|memcpy
argument_list|(
name|p
argument_list|,
name|buf
argument_list|,
name|len
argument_list|)
expr_stmt|;
return|return;
block|}
name|memcpy
argument_list|(
name|p
argument_list|,
name|buf
argument_list|,
name|t
argument_list|)
expr_stmt|;
name|byte_reverse
argument_list|(
operator|(
name|guint32
operator|*
operator|)
name|ctx
operator|->
name|in
argument_list|,
literal|16
argument_list|)
expr_stmt|;
name|gimp_md5_transform
argument_list|(
name|ctx
operator|->
name|buf
argument_list|,
operator|(
name|guint32
operator|*
operator|)
name|ctx
operator|->
name|in
argument_list|)
expr_stmt|;
name|buf
operator|+=
name|t
expr_stmt|;
name|len
operator|-=
name|t
expr_stmt|;
block|}
comment|/* Process data in 64-byte chunks */
while|while
condition|(
name|len
operator|>=
literal|64
condition|)
block|{
name|memcpy
argument_list|(
name|ctx
operator|->
name|in
argument_list|,
name|buf
argument_list|,
literal|64
argument_list|)
expr_stmt|;
name|byte_reverse
argument_list|(
operator|(
name|guint32
operator|*
operator|)
name|ctx
operator|->
name|in
argument_list|,
literal|16
argument_list|)
expr_stmt|;
name|gimp_md5_transform
argument_list|(
name|ctx
operator|->
name|buf
argument_list|,
operator|(
name|guint32
operator|*
operator|)
name|ctx
operator|->
name|in
argument_list|)
expr_stmt|;
name|buf
operator|+=
literal|64
expr_stmt|;
name|len
operator|-=
literal|64
expr_stmt|;
block|}
comment|/* Handle any remaining bytes of data. */
name|memcpy
argument_list|(
name|ctx
operator|->
name|in
argument_list|,
name|buf
argument_list|,
name|len
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_md5_final (GimpMD5Context * ctx,guchar digest[16])
name|gimp_md5_final
parameter_list|(
name|GimpMD5Context
modifier|*
name|ctx
parameter_list|,
name|guchar
name|digest
index|[
literal|16
index|]
parameter_list|)
block|{
name|guint32
name|count
decl_stmt|;
name|guchar
modifier|*
name|p
decl_stmt|;
comment|/* Compute number of bytes mod 64 */
name|count
operator|=
operator|(
name|ctx
operator|->
name|bits
index|[
literal|0
index|]
operator|>>
literal|3
operator|)
operator|&
literal|0x3F
expr_stmt|;
comment|/* Set the first char of padding to 0x80.  This is safe since there is      always at least one byte free */
name|p
operator|=
name|ctx
operator|->
name|in
operator|+
name|count
expr_stmt|;
operator|*
name|p
operator|++
operator|=
literal|0x80
expr_stmt|;
comment|/* Bytes of padding needed to make 64 bytes */
name|count
operator|=
literal|64
operator|-
literal|1
operator|-
name|count
expr_stmt|;
comment|/* Pad out to 56 mod 64 */
if|if
condition|(
name|count
operator|<
literal|8
condition|)
block|{
comment|/* Two lots of padding:  Pad the first block to 64 bytes */
name|memset
argument_list|(
name|p
argument_list|,
literal|0
argument_list|,
name|count
argument_list|)
expr_stmt|;
name|byte_reverse
argument_list|(
operator|(
name|guint32
operator|*
operator|)
name|ctx
operator|->
name|in
argument_list|,
literal|16
argument_list|)
expr_stmt|;
name|gimp_md5_transform
argument_list|(
name|ctx
operator|->
name|buf
argument_list|,
operator|(
name|guint32
operator|*
operator|)
name|ctx
operator|->
name|in
argument_list|)
expr_stmt|;
comment|/* Now fill the next block with 56 bytes */
name|memset
argument_list|(
name|ctx
operator|->
name|in
argument_list|,
literal|0
argument_list|,
literal|56
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* Pad block to 56 bytes */
name|memset
argument_list|(
name|p
argument_list|,
literal|0
argument_list|,
name|count
operator|-
literal|8
argument_list|)
expr_stmt|;
block|}
name|byte_reverse
argument_list|(
operator|(
name|guint32
operator|*
operator|)
name|ctx
operator|->
name|in
argument_list|,
literal|14
argument_list|)
expr_stmt|;
comment|/* Append length in bits and transform */
operator|(
operator|(
name|guint32
operator|*
operator|)
name|ctx
operator|->
name|in
operator|)
index|[
literal|14
index|]
operator|=
name|ctx
operator|->
name|bits
index|[
literal|0
index|]
expr_stmt|;
operator|(
operator|(
name|guint32
operator|*
operator|)
name|ctx
operator|->
name|in
operator|)
index|[
literal|15
index|]
operator|=
name|ctx
operator|->
name|bits
index|[
literal|1
index|]
expr_stmt|;
name|gimp_md5_transform
argument_list|(
name|ctx
operator|->
name|buf
argument_list|,
operator|(
name|guint32
operator|*
operator|)
name|ctx
operator|->
name|in
argument_list|)
expr_stmt|;
name|byte_reverse
argument_list|(
name|ctx
operator|->
name|buf
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|digest
argument_list|,
name|ctx
operator|->
name|buf
argument_list|,
literal|16
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* The four core functions - F1 is optimized somewhat */
end_comment

begin_comment
comment|/* #define F1(x, y, z) (x& y | ~x& z) */
end_comment

begin_define
DECL|macro|F1 (x,y,z)
define|#
directive|define
name|F1
parameter_list|(
name|x
parameter_list|,
name|y
parameter_list|,
name|z
parameter_list|)
value|(z ^ (x& (y ^ z)))
end_define

begin_define
DECL|macro|F2 (x,y,z)
define|#
directive|define
name|F2
parameter_list|(
name|x
parameter_list|,
name|y
parameter_list|,
name|z
parameter_list|)
value|F1(z, x, y)
end_define

begin_define
DECL|macro|F3 (x,y,z)
define|#
directive|define
name|F3
parameter_list|(
name|x
parameter_list|,
name|y
parameter_list|,
name|z
parameter_list|)
value|(x ^ y ^ z)
end_define

begin_define
DECL|macro|F4 (x,y,z)
define|#
directive|define
name|F4
parameter_list|(
name|x
parameter_list|,
name|y
parameter_list|,
name|z
parameter_list|)
value|(y ^ (x | ~z))
end_define

begin_comment
comment|/* This is the central step in the MD5 algorithm. */
end_comment

begin_define
DECL|macro|MD5STEP (f,w,x,y,z,data,s)
define|#
directive|define
name|MD5STEP
parameter_list|(
name|f
parameter_list|,
name|w
parameter_list|,
name|x
parameter_list|,
name|y
parameter_list|,
name|z
parameter_list|,
name|data
parameter_list|,
name|s
parameter_list|)
define|\
value|( w += f(x, y, z) + data,  w = w<<s | w>>(32-s),  w += x )
end_define

begin_comment
comment|/*  * The core of the MD5 algorithm, this alters an existing MD5 hash to  * reflect the addition of 16 longwords of new data.  md5_Update blocks  * the data and converts bytes into longwords for this routine.  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_md5_transform (guint32 buf[4],const guint32 in[16])
name|gimp_md5_transform
parameter_list|(
name|guint32
name|buf
index|[
literal|4
index|]
parameter_list|,
specifier|const
name|guint32
name|in
index|[
literal|16
index|]
parameter_list|)
block|{
specifier|register
name|guint32
name|a
decl_stmt|,
name|b
decl_stmt|,
name|c
decl_stmt|,
name|d
decl_stmt|;
name|a
operator|=
name|buf
index|[
literal|0
index|]
expr_stmt|;
name|b
operator|=
name|buf
index|[
literal|1
index|]
expr_stmt|;
name|c
operator|=
name|buf
index|[
literal|2
index|]
expr_stmt|;
name|d
operator|=
name|buf
index|[
literal|3
index|]
expr_stmt|;
name|MD5STEP
argument_list|(
name|F1
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|in
index|[
literal|0
index|]
operator|+
literal|0xd76aa478
argument_list|,
literal|7
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F1
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|in
index|[
literal|1
index|]
operator|+
literal|0xe8c7b756
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F1
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|in
index|[
literal|2
index|]
operator|+
literal|0x242070db
argument_list|,
literal|17
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F1
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|in
index|[
literal|3
index|]
operator|+
literal|0xc1bdceee
argument_list|,
literal|22
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F1
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|in
index|[
literal|4
index|]
operator|+
literal|0xf57c0faf
argument_list|,
literal|7
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F1
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|in
index|[
literal|5
index|]
operator|+
literal|0x4787c62a
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F1
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|in
index|[
literal|6
index|]
operator|+
literal|0xa8304613
argument_list|,
literal|17
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F1
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|in
index|[
literal|7
index|]
operator|+
literal|0xfd469501
argument_list|,
literal|22
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F1
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|in
index|[
literal|8
index|]
operator|+
literal|0x698098d8
argument_list|,
literal|7
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F1
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|in
index|[
literal|9
index|]
operator|+
literal|0x8b44f7af
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F1
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|in
index|[
literal|10
index|]
operator|+
literal|0xffff5bb1
argument_list|,
literal|17
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F1
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|in
index|[
literal|11
index|]
operator|+
literal|0x895cd7be
argument_list|,
literal|22
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F1
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|in
index|[
literal|12
index|]
operator|+
literal|0x6b901122
argument_list|,
literal|7
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F1
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|in
index|[
literal|13
index|]
operator|+
literal|0xfd987193
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F1
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|in
index|[
literal|14
index|]
operator|+
literal|0xa679438e
argument_list|,
literal|17
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F1
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|in
index|[
literal|15
index|]
operator|+
literal|0x49b40821
argument_list|,
literal|22
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F2
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|in
index|[
literal|1
index|]
operator|+
literal|0xf61e2562
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F2
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|in
index|[
literal|6
index|]
operator|+
literal|0xc040b340
argument_list|,
literal|9
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F2
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|in
index|[
literal|11
index|]
operator|+
literal|0x265e5a51
argument_list|,
literal|14
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F2
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|in
index|[
literal|0
index|]
operator|+
literal|0xe9b6c7aa
argument_list|,
literal|20
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F2
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|in
index|[
literal|5
index|]
operator|+
literal|0xd62f105d
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F2
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|in
index|[
literal|10
index|]
operator|+
literal|0x02441453
argument_list|,
literal|9
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F2
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|in
index|[
literal|15
index|]
operator|+
literal|0xd8a1e681
argument_list|,
literal|14
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F2
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|in
index|[
literal|4
index|]
operator|+
literal|0xe7d3fbc8
argument_list|,
literal|20
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F2
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|in
index|[
literal|9
index|]
operator|+
literal|0x21e1cde6
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F2
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|in
index|[
literal|14
index|]
operator|+
literal|0xc33707d6
argument_list|,
literal|9
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F2
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|in
index|[
literal|3
index|]
operator|+
literal|0xf4d50d87
argument_list|,
literal|14
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F2
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|in
index|[
literal|8
index|]
operator|+
literal|0x455a14ed
argument_list|,
literal|20
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F2
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|in
index|[
literal|13
index|]
operator|+
literal|0xa9e3e905
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F2
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|in
index|[
literal|2
index|]
operator|+
literal|0xfcefa3f8
argument_list|,
literal|9
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F2
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|in
index|[
literal|7
index|]
operator|+
literal|0x676f02d9
argument_list|,
literal|14
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F2
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|in
index|[
literal|12
index|]
operator|+
literal|0x8d2a4c8a
argument_list|,
literal|20
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F3
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|in
index|[
literal|5
index|]
operator|+
literal|0xfffa3942
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F3
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|in
index|[
literal|8
index|]
operator|+
literal|0x8771f681
argument_list|,
literal|11
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F3
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|in
index|[
literal|11
index|]
operator|+
literal|0x6d9d6122
argument_list|,
literal|16
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F3
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|in
index|[
literal|14
index|]
operator|+
literal|0xfde5380c
argument_list|,
literal|23
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F3
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|in
index|[
literal|1
index|]
operator|+
literal|0xa4beea44
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F3
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|in
index|[
literal|4
index|]
operator|+
literal|0x4bdecfa9
argument_list|,
literal|11
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F3
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|in
index|[
literal|7
index|]
operator|+
literal|0xf6bb4b60
argument_list|,
literal|16
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F3
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|in
index|[
literal|10
index|]
operator|+
literal|0xbebfbc70
argument_list|,
literal|23
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F3
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|in
index|[
literal|13
index|]
operator|+
literal|0x289b7ec6
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F3
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|in
index|[
literal|0
index|]
operator|+
literal|0xeaa127fa
argument_list|,
literal|11
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F3
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|in
index|[
literal|3
index|]
operator|+
literal|0xd4ef3085
argument_list|,
literal|16
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F3
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|in
index|[
literal|6
index|]
operator|+
literal|0x04881d05
argument_list|,
literal|23
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F3
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|in
index|[
literal|9
index|]
operator|+
literal|0xd9d4d039
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F3
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|in
index|[
literal|12
index|]
operator|+
literal|0xe6db99e5
argument_list|,
literal|11
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F3
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|in
index|[
literal|15
index|]
operator|+
literal|0x1fa27cf8
argument_list|,
literal|16
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F3
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|in
index|[
literal|2
index|]
operator|+
literal|0xc4ac5665
argument_list|,
literal|23
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F4
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|in
index|[
literal|0
index|]
operator|+
literal|0xf4292244
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F4
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|in
index|[
literal|7
index|]
operator|+
literal|0x432aff97
argument_list|,
literal|10
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F4
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|in
index|[
literal|14
index|]
operator|+
literal|0xab9423a7
argument_list|,
literal|15
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F4
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|in
index|[
literal|5
index|]
operator|+
literal|0xfc93a039
argument_list|,
literal|21
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F4
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|in
index|[
literal|12
index|]
operator|+
literal|0x655b59c3
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F4
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|in
index|[
literal|3
index|]
operator|+
literal|0x8f0ccc92
argument_list|,
literal|10
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F4
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|in
index|[
literal|10
index|]
operator|+
literal|0xffeff47d
argument_list|,
literal|15
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F4
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|in
index|[
literal|1
index|]
operator|+
literal|0x85845dd1
argument_list|,
literal|21
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F4
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|in
index|[
literal|8
index|]
operator|+
literal|0x6fa87e4f
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F4
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|in
index|[
literal|15
index|]
operator|+
literal|0xfe2ce6e0
argument_list|,
literal|10
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F4
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|in
index|[
literal|6
index|]
operator|+
literal|0xa3014314
argument_list|,
literal|15
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F4
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|in
index|[
literal|13
index|]
operator|+
literal|0x4e0811a1
argument_list|,
literal|21
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F4
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|in
index|[
literal|4
index|]
operator|+
literal|0xf7537e82
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F4
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|in
index|[
literal|11
index|]
operator|+
literal|0xbd3af235
argument_list|,
literal|10
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F4
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|in
index|[
literal|2
index|]
operator|+
literal|0x2ad7d2bb
argument_list|,
literal|15
argument_list|)
expr_stmt|;
name|MD5STEP
argument_list|(
name|F4
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|in
index|[
literal|9
index|]
operator|+
literal|0xeb86d391
argument_list|,
literal|21
argument_list|)
expr_stmt|;
name|buf
index|[
literal|0
index|]
operator|+=
name|a
expr_stmt|;
name|buf
index|[
literal|1
index|]
operator|+=
name|b
expr_stmt|;
name|buf
index|[
literal|2
index|]
operator|+=
name|c
expr_stmt|;
name|buf
index|[
literal|3
index|]
operator|+=
name|d
expr_stmt|;
block|}
end_function

end_unit

