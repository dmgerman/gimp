begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* 	DDS GIMP plugin  	Copyright (C) 2004-2012 Shawn Kirst<skirst@gmail.com>,    with parts (C) 2003 Arne Reuter<homepage@arnereuter.de> where specified.  	This program is free software; you can redistribute it and/or 	modify it under the terms of the GNU General Public 	License as published by the Free Software Foundation; either 	version 2 of the License, or (at your option) any later version.  	This program is distributed in the hope that it will be useful, 	but WITHOUT ANY WARRANTY; without even the implied warranty of 	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 	General Public License for more details.  	You should have received a copy of the GNU General Public License 	along with this program; see the file COPYING.  If not, write to 	the Free Software Foundation, 51 Franklin Street, Fifth Floor 	Boston, MA 02110-1301, USA. */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|IMATH_H
end_ifndef

begin_define
DECL|macro|IMATH_H
define|#
directive|define
name|IMATH_H
end_define

begin_ifndef
ifndef|#
directive|ifndef
name|MIN
end_ifndef

begin_ifdef
ifdef|#
directive|ifdef
name|__GNUC__
end_ifdef

begin_define
DECL|macro|MIN (a,b)
define|#
directive|define
name|MIN
parameter_list|(
name|a
parameter_list|,
name|b
parameter_list|)
value|({typeof(a) _a=(a); typeof(b) _b=(b); _a< _b ? _a : _b;})
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|MIN (a,b)
define|#
directive|define
name|MIN
parameter_list|(
name|a
parameter_list|,
name|b
parameter_list|)
value|((a)< (b) ? (a) : (b))
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|MAX
end_ifndef

begin_ifdef
ifdef|#
directive|ifdef
name|__GNUC__
end_ifdef

begin_define
DECL|macro|MAX (a,b)
define|#
directive|define
name|MAX
parameter_list|(
name|a
parameter_list|,
name|b
parameter_list|)
value|({typeof(a) _a=(a); typeof(b) _b=(b); _a> _b ? _a : _b;})
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|MAX (a,b)
define|#
directive|define
name|MAX
parameter_list|(
name|a
parameter_list|,
name|b
parameter_list|)
value|((a)> (b) ? (a) : (b))
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|IS_POW2 (x)
define|#
directive|define
name|IS_POW2
parameter_list|(
name|x
parameter_list|)
value|(!((x)& ((x) - 1)))
end_define

begin_define
DECL|macro|IS_MUL4 (x)
define|#
directive|define
name|IS_MUL4
parameter_list|(
name|x
parameter_list|)
value|(((x)& 3) == 0)
end_define

begin_comment
comment|/* round integer x up to next multiple of 4 */
end_comment

begin_define
DECL|macro|RND_MUL4 (x)
define|#
directive|define
name|RND_MUL4
parameter_list|(
name|x
parameter_list|)
value|((x) + (4 - ((x)& 3)))
end_define

begin_function
DECL|function|mul8bit (int a,int b)
specifier|static
specifier|inline
name|int
name|mul8bit
parameter_list|(
name|int
name|a
parameter_list|,
name|int
name|b
parameter_list|)
block|{
name|int
name|t
init|=
name|a
operator|*
name|b
operator|+
literal|128
decl_stmt|;
return|return
operator|(
operator|(
name|t
operator|+
operator|(
name|t
operator|>>
literal|8
operator|)
operator|)
operator|>>
literal|8
operator|)
return|;
block|}
end_function

begin_function
DECL|function|blerp (int a,int b,int x)
specifier|static
specifier|inline
name|int
name|blerp
parameter_list|(
name|int
name|a
parameter_list|,
name|int
name|b
parameter_list|,
name|int
name|x
parameter_list|)
block|{
return|return
operator|(
name|a
operator|+
name|mul8bit
argument_list|(
name|b
operator|-
name|a
argument_list|,
name|x
argument_list|)
operator|)
return|;
block|}
end_function

begin_function
DECL|function|icerp (int a,int b,int c,int d,int x)
specifier|static
specifier|inline
name|int
name|icerp
parameter_list|(
name|int
name|a
parameter_list|,
name|int
name|b
parameter_list|,
name|int
name|c
parameter_list|,
name|int
name|d
parameter_list|,
name|int
name|x
parameter_list|)
block|{
name|int
name|p
init|=
operator|(
name|d
operator|-
name|c
operator|)
operator|-
operator|(
name|a
operator|-
name|b
operator|)
decl_stmt|;
name|int
name|q
init|=
operator|(
name|a
operator|-
name|b
operator|)
operator|-
name|p
decl_stmt|;
name|int
name|r
init|=
name|c
operator|-
name|a
decl_stmt|;
return|return
operator|(
operator|(
name|x
operator|*
operator|(
name|x
operator|*
operator|(
name|x
operator|*
name|p
operator|+
operator|(
name|q
operator|<<
literal|7
operator|)
operator|)
operator|+
operator|(
name|r
operator|<<
literal|14
operator|)
operator|)
operator|+
operator|(
name|b
operator|<<
literal|21
operator|)
operator|)
operator|>>
literal|21
operator|)
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

end_unit

