begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library   * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  * Copyright (C) 2000 Sven Neumann<sven@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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

begin_include
include|#
directive|include
file|"gimputils.h"
end_include

begin_comment
comment|/**  * gimp_strescape:  * @source: A string to escape special characters in.  * @exceptions: A string holding characters not to be escaped.  *   * Escapes special characters in a string in the same way as in the  * C language, i.e. either with one of the sequences \b, \f, \n, \r,  * \t, \\, \", or as a three-digit octal escape sequence \nnn.  *  * If the list of exceptions is NULL, all ASCII control characters,  * the backslash character, the double-quote character, and all  * non-ASCII characters are escaped.  *  * If glib> 1.3 is installed this function is identical to   * g_strescape(). For systems using glib-1.2 this function provides the   * added functionality from glib-1.3.  *   * Returns: A newly allocated copy of the string, with all special  * characters escaped as in the C language.  */
end_comment

begin_if
if|#
directive|if
operator|!
operator|(
name|defined
argument_list|(
name|GLIB_CHECK_VERSION
argument_list|)
operator|&&
name|GLIB_CHECK_VERSION
argument_list|(
literal|1
operator|,
literal|3
operator|,
literal|1
argument_list|)
operator|)
end_if

begin_function
name|gchar
modifier|*
DECL|function|gimp_strescape (const gchar * source,const gchar * exceptions)
name|gimp_strescape
parameter_list|(
specifier|const
name|gchar
modifier|*
name|source
parameter_list|,
specifier|const
name|gchar
modifier|*
name|exceptions
parameter_list|)
block|{
specifier|const
name|guchar
modifier|*
name|p
init|=
operator|(
name|guchar
operator|*
operator|)
name|source
decl_stmt|;
comment|/* Each source byte needs maximally four destination chars (\777) */
name|gchar
modifier|*
name|dest
init|=
name|g_malloc
argument_list|(
name|strlen
argument_list|(
name|source
argument_list|)
operator|*
literal|4
operator|+
literal|1
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|q
init|=
name|dest
decl_stmt|;
name|guchar
name|excmap
index|[
literal|256
index|]
decl_stmt|;
name|memset
argument_list|(
name|excmap
argument_list|,
literal|0
argument_list|,
literal|256
argument_list|)
expr_stmt|;
if|if
condition|(
name|exceptions
condition|)
block|{
name|guchar
modifier|*
name|e
init|=
operator|(
name|guchar
operator|*
operator|)
name|exceptions
decl_stmt|;
while|while
condition|(
operator|*
name|e
condition|)
block|{
name|excmap
index|[
operator|*
name|e
index|]
operator|=
literal|1
expr_stmt|;
name|e
operator|++
expr_stmt|;
block|}
block|}
while|while
condition|(
operator|*
name|p
condition|)
block|{
if|if
condition|(
name|excmap
index|[
operator|*
name|p
index|]
condition|)
operator|*
name|q
operator|++
operator|=
operator|*
name|p
expr_stmt|;
else|else
block|{
switch|switch
condition|(
operator|*
name|p
condition|)
block|{
case|case
literal|'\b'
case|:
operator|*
name|q
operator|++
operator|=
literal|'\\'
expr_stmt|;
operator|*
name|q
operator|++
operator|=
literal|'b'
expr_stmt|;
break|break;
case|case
literal|'\f'
case|:
operator|*
name|q
operator|++
operator|=
literal|'\\'
expr_stmt|;
operator|*
name|q
operator|++
operator|=
literal|'f'
expr_stmt|;
break|break;
case|case
literal|'\n'
case|:
operator|*
name|q
operator|++
operator|=
literal|'\\'
expr_stmt|;
operator|*
name|q
operator|++
operator|=
literal|'n'
expr_stmt|;
break|break;
case|case
literal|'\r'
case|:
operator|*
name|q
operator|++
operator|=
literal|'\\'
expr_stmt|;
operator|*
name|q
operator|++
operator|=
literal|'r'
expr_stmt|;
break|break;
case|case
literal|'\t'
case|:
operator|*
name|q
operator|++
operator|=
literal|'\\'
expr_stmt|;
operator|*
name|q
operator|++
operator|=
literal|'t'
expr_stmt|;
break|break;
case|case
literal|'\\'
case|:
operator|*
name|q
operator|++
operator|=
literal|'\\'
expr_stmt|;
operator|*
name|q
operator|++
operator|=
literal|'\\'
expr_stmt|;
break|break;
case|case
literal|'"'
case|:
operator|*
name|q
operator|++
operator|=
literal|'\\'
expr_stmt|;
operator|*
name|q
operator|++
operator|=
literal|'"'
expr_stmt|;
break|break;
default|default:
if|if
condition|(
operator|(
operator|*
name|p
operator|<
literal|' '
operator|)
operator|||
operator|(
operator|*
name|p
operator|>=
literal|0177
operator|)
condition|)
block|{
operator|*
name|q
operator|++
operator|=
literal|'\\'
expr_stmt|;
operator|*
name|q
operator|++
operator|=
literal|'0'
operator|+
operator|(
operator|(
operator|(
operator|*
name|p
operator|)
operator|>>
literal|6
operator|)
operator|&
literal|07
operator|)
expr_stmt|;
operator|*
name|q
operator|++
operator|=
literal|'0'
operator|+
operator|(
operator|(
operator|(
operator|*
name|p
operator|)
operator|>>
literal|3
operator|)
operator|&
literal|07
operator|)
expr_stmt|;
operator|*
name|q
operator|++
operator|=
literal|'0'
operator|+
operator|(
operator|(
operator|*
name|p
operator|)
operator|&
literal|07
operator|)
expr_stmt|;
block|}
else|else
operator|*
name|q
operator|++
operator|=
operator|*
name|p
expr_stmt|;
break|break;
block|}
block|}
name|p
operator|++
expr_stmt|;
block|}
operator|*
name|q
operator|=
literal|0
expr_stmt|;
return|return
name|dest
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* GLIB<= 1.3 */
end_comment

begin_comment
comment|/**  * gimp_strcompress:  * @source: A string to that has special characters escaped.  *   * Does the opposite of g_strescape(), that is it converts escaped  * characters back to their unescaped form.  *  * Escaped characters are either one of the sequences \b, \f, \n, \r,  * \t, \\, \", or a three-digit octal escape sequence \nnn.  *  * If glib> 1.3 is installed this function is identical to   * g_strcompress(). For systems using glib-1.2 this function provides   * the functionality from glib-1.3.  *   * Returns: A newly allocated copy of the string, with all escaped   * special characters converted to their unescaped form.  */
end_comment

begin_if
if|#
directive|if
operator|!
operator|(
name|defined
argument_list|(
name|GLIB_CHECK_VERSION
argument_list|)
operator|&&
name|GLIB_CHECK_VERSION
argument_list|(
literal|1
operator|,
literal|3
operator|,
literal|1
argument_list|)
operator|)
end_if

begin_function
name|gchar
modifier|*
DECL|function|gimp_strcompress (const gchar * source)
name|gimp_strcompress
parameter_list|(
specifier|const
name|gchar
modifier|*
name|source
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|p
init|=
name|source
decl_stmt|,
modifier|*
name|octal
decl_stmt|;
name|gchar
modifier|*
name|dest
init|=
name|g_malloc
argument_list|(
name|strlen
argument_list|(
name|source
argument_list|)
operator|+
literal|1
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|q
init|=
name|dest
decl_stmt|;
while|while
condition|(
operator|*
name|p
condition|)
block|{
if|if
condition|(
operator|*
name|p
operator|==
literal|'\\'
condition|)
block|{
name|p
operator|++
expr_stmt|;
switch|switch
condition|(
operator|*
name|p
condition|)
block|{
case|case
literal|'0'
case|:
case|case
literal|'1'
case|:
case|case
literal|'2'
case|:
case|case
literal|'3'
case|:
case|case
literal|'4'
case|:
case|case
literal|'5'
case|:
case|case
literal|'6'
case|:
case|case
literal|'7'
case|:
operator|*
name|q
operator|=
literal|0
expr_stmt|;
name|octal
operator|=
name|p
expr_stmt|;
while|while
condition|(
operator|(
name|p
operator|<
name|octal
operator|+
literal|3
operator|)
operator|&&
operator|(
operator|*
name|p
operator|>=
literal|'0'
operator|)
operator|&&
operator|(
operator|*
name|p
operator|<=
literal|'7'
operator|)
condition|)
block|{
operator|*
name|q
operator|=
operator|(
operator|*
name|q
operator|*
literal|8
operator|)
operator|+
operator|(
operator|*
name|p
operator|-
literal|'0'
operator|)
expr_stmt|;
name|p
operator|++
expr_stmt|;
block|}
name|q
operator|++
expr_stmt|;
name|p
operator|--
expr_stmt|;
break|break;
case|case
literal|'b'
case|:
operator|*
name|q
operator|++
operator|=
literal|'\b'
expr_stmt|;
break|break;
case|case
literal|'f'
case|:
operator|*
name|q
operator|++
operator|=
literal|'\f'
expr_stmt|;
break|break;
case|case
literal|'n'
case|:
operator|*
name|q
operator|++
operator|=
literal|'\n'
expr_stmt|;
break|break;
case|case
literal|'r'
case|:
operator|*
name|q
operator|++
operator|=
literal|'\r'
expr_stmt|;
break|break;
case|case
literal|'t'
case|:
operator|*
name|q
operator|++
operator|=
literal|'\t'
expr_stmt|;
break|break;
default|default:
comment|/* Also handles \" and \\ */
operator|*
name|q
operator|++
operator|=
operator|*
name|p
expr_stmt|;
break|break;
block|}
block|}
else|else
operator|*
name|q
operator|++
operator|=
operator|*
name|p
expr_stmt|;
name|p
operator|++
expr_stmt|;
block|}
operator|*
name|q
operator|=
literal|0
expr_stmt|;
return|return
name|dest
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* GLIB<= 1.3 */
end_comment

end_unit

