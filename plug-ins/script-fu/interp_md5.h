begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* MD5.H - header file for MD5C.C    $Id$  */
end_comment

begin_comment
comment|/* Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All    rights reserved.     License to copy and use this software is granted provided that it    is identified as the "RSA Data Security, Inc. MD5 Message-Digest    Algorithm" in all material mentioning or referencing this software    or this function.     License is also granted to make and use derivative works provided    that such works are identified as "derived from the RSA Data    Security, Inc. MD5 Message-Digest Algorithm" in all material    mentioning or referencing the derived work.     RSA Data Security, Inc. makes no representations concerning either    the merchantability of this software or the suitability of this    software for any particular purpose. It is provided "as is"    without express or implied warranty of any kind.     These notices must be retained in any copies of any part of this    documentation and/or software.  */
end_comment

begin_comment
comment|/* POINTER defines a generic pointer type */
end_comment

begin_typedef
DECL|typedef|POINTER
typedef|typedef
name|unsigned
name|char
modifier|*
name|POINTER
typedef|;
end_typedef

begin_comment
comment|/* UINT2 defines a two byte word */
end_comment

begin_typedef
DECL|typedef|UINT2
typedef|typedef
name|unsigned
name|short
name|int
name|UINT2
typedef|;
end_typedef

begin_comment
comment|/* UINT4 defines a four byte word */
end_comment

begin_ifdef
ifdef|#
directive|ifdef
name|__alpha
end_ifdef

begin_typedef
DECL|typedef|UINT4
typedef|typedef
name|unsigned
name|int
name|UINT4
typedef|;
end_typedef

begin_else
else|#
directive|else
end_else

begin_typedef
DECL|typedef|UINT4
typedef|typedef
name|unsigned
name|long
name|int
name|UINT4
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|PROTO_LIST (list)
define|#
directive|define
name|PROTO_LIST
parameter_list|(
name|list
parameter_list|)
value|list
end_define

begin_comment
comment|/* MD5 context. */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c915acb0108
block|{
DECL|member|state
name|UINT4
name|state
index|[
literal|4
index|]
decl_stmt|;
comment|/* state (ABCD) */
DECL|member|count
name|UINT4
name|count
index|[
literal|2
index|]
decl_stmt|;
comment|/* number of bits, modulo 2^64 (lsb first) */
DECL|member|buffer
name|unsigned
name|char
name|buffer
index|[
literal|64
index|]
decl_stmt|;
comment|/* input buffer */
block|}
DECL|typedef|MD5_CTX
name|MD5_CTX
typedef|;
end_typedef

begin_decl_stmt
name|void
name|MD5Init
name|PROTO_LIST
argument_list|(
operator|(
name|MD5_CTX
operator|*
operator|)
argument_list|)
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|void
name|MD5Update
name|PROTO_LIST
argument_list|(
operator|(
name|MD5_CTX
operator|*
operator|,
name|unsigned
name|char
operator|*
operator|,
name|unsigned
name|int
operator|)
argument_list|)
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|void
name|MD5Final
name|PROTO_LIST
argument_list|(
operator|(
name|unsigned
name|char
index|[
literal|16
index|]
operator|,
name|MD5_CTX
operator|*
operator|)
argument_list|)
decl_stmt|;
end_decl_stmt

end_unit

