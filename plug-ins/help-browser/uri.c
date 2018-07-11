begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * The GIMP Help Browser - URI functions  * Copyright (C) 2001  Jacob Schroeder<jacob@convergence.de>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"uri.h"
end_include

begin_comment
comment|/*  #define URI_DEBUG 1  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2913e1230103
block|{
DECL|enumerator|URI_UNKNOWN
name|URI_UNKNOWN
block|,
DECL|enumerator|URI_ABSURI
name|URI_ABSURI
block|,
DECL|enumerator|URI_NETPATH
name|URI_NETPATH
block|,
DECL|enumerator|URI_ABSPATH
name|URI_ABSPATH
block|,
DECL|enumerator|URI_RELPATH
name|URI_RELPATH
block|,
DECL|enumerator|URI_QUERY
name|URI_QUERY
block|,
DECL|enumerator|URI_EMPTY
name|URI_EMPTY
block|,
DECL|enumerator|URI_FRAGMENT
name|URI_FRAGMENT
block|,
DECL|enumerator|URI_INVALID
name|URI_INVALID
DECL|typedef|UriType
block|}
name|UriType
typedef|;
end_typedef

begin_function
specifier|static
name|UriType
DECL|function|uri_get_type (const gchar * uri)
name|uri_get_type
parameter_list|(
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|)
block|{
name|gchar
name|c
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|cptr
decl_stmt|;
name|UriType
name|type
init|=
name|URI_UNKNOWN
decl_stmt|;
if|if
condition|(
operator|!
name|uri
condition|)
return|return
name|type
return|;
name|cptr
operator|=
name|uri
expr_stmt|;
name|c
operator|=
operator|*
name|cptr
operator|++
expr_stmt|;
if|if
condition|(
name|g_ascii_isalpha
argument_list|(
name|c
argument_list|)
condition|)
block|{
name|type
operator|=
name|URI_RELPATH
expr_stmt|;
comment|/* assume relative path */
while|while
condition|(
operator|(
name|c
operator|=
operator|*
name|cptr
operator|++
operator|)
condition|)
block|{
if|if
condition|(
name|g_ascii_isalnum
argument_list|(
name|c
argument_list|)
operator|||
name|c
operator|==
literal|'+'
operator|||
name|c
operator|==
literal|'-'
operator|||
name|c
operator|==
literal|'.'
condition|)
continue|continue;
if|if
condition|(
name|c
operator|==
literal|':'
condition|)
block|{
comment|/* it was a scheme */
name|type
operator|=
name|URI_ABSURI
expr_stmt|;
block|}
break|break;
block|}
block|}
else|else
block|{
switch|switch
condition|(
name|c
condition|)
block|{
case|case
literal|'/'
case|:
if|if
condition|(
operator|*
name|cptr
operator|==
literal|'/'
condition|)
block|{
name|cptr
operator|++
expr_stmt|;
name|type
operator|=
name|URI_NETPATH
expr_stmt|;
block|}
else|else
block|{
name|type
operator|=
name|URI_ABSPATH
expr_stmt|;
block|}
break|break;
case|case
literal|'?'
case|:
name|type
operator|=
name|URI_QUERY
expr_stmt|;
break|break;
case|case
literal|'#'
case|:
name|type
operator|=
name|URI_FRAGMENT
expr_stmt|;
break|break;
case|case
literal|'\0'
case|:
name|type
operator|=
name|URI_EMPTY
expr_stmt|;
break|break;
default|default:
name|type
operator|=
name|URI_RELPATH
expr_stmt|;
break|break;
block|}
block|}
ifdef|#
directive|ifdef
name|URI_DEBUG
name|g_print
argument_list|(
literal|"uri_get_type (\"%s\") -> "
argument_list|,
name|uri
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|type
condition|)
block|{
case|case
name|URI_UNKNOWN
case|:
name|g_print
argument_list|(
literal|"unknown"
argument_list|)
expr_stmt|;
break|break;
case|case
name|URI_ABSURI
case|:
name|g_print
argument_list|(
literal|"absuri"
argument_list|)
expr_stmt|;
break|break;
case|case
name|URI_NETPATH
case|:
name|g_print
argument_list|(
literal|"netpath"
argument_list|)
expr_stmt|;
break|break;
case|case
name|URI_ABSPATH
case|:
name|g_print
argument_list|(
literal|"abspath"
argument_list|)
expr_stmt|;
break|break;
case|case
name|URI_RELPATH
case|:
name|g_print
argument_list|(
literal|"relpath"
argument_list|)
expr_stmt|;
break|break;
case|case
name|URI_QUERY
case|:
name|g_print
argument_list|(
literal|"query"
argument_list|)
expr_stmt|;
break|break;
case|case
name|URI_EMPTY
case|:
name|g_print
argument_list|(
literal|"empty"
argument_list|)
expr_stmt|;
break|break;
case|case
name|URI_FRAGMENT
case|:
name|g_print
argument_list|(
literal|"fragment"
argument_list|)
expr_stmt|;
break|break;
case|case
name|URI_INVALID
case|:
name|g_print
argument_list|(
literal|"invalid"
argument_list|)
expr_stmt|;
break|break;
block|}
name|g_print
argument_list|(
literal|"\n"
argument_list|)
expr_stmt|;
endif|#
directive|endif
return|return
name|type
return|;
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|uri_to_abs (const gchar * uri,const gchar * base_uri)
name|uri_to_abs
parameter_list|(
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
specifier|const
name|gchar
modifier|*
name|base_uri
parameter_list|)
block|{
name|gchar
name|c
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|cptr
decl_stmt|;
name|gchar
modifier|*
name|retval
init|=
name|NULL
decl_stmt|;
name|UriType
name|uri_type
init|=
name|URI_UNKNOWN
decl_stmt|;
name|UriType
name|base_type
init|=
name|URI_UNKNOWN
decl_stmt|;
name|gint
name|base_cnt
init|=
literal|0
decl_stmt|;
comment|/* no of chars to be copied from base URI  */
name|gint
name|uri_cnt
init|=
literal|0
decl_stmt|;
comment|/* no of chars to be copied from URI       */
name|gint
name|sep_cnt
init|=
literal|0
decl_stmt|;
comment|/* no of chars to be inserted between them */
specifier|const
name|gchar
modifier|*
name|sep_str
init|=
literal|""
decl_stmt|;
comment|/* string to insert between base and uri */
specifier|const
name|gchar
modifier|*
name|part
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|last_segment
init|=
name|NULL
decl_stmt|;
ifdef|#
directive|ifdef
name|URI_DEBUG
name|g_print
argument_list|(
literal|"uri_to_abs (\"%s\", \"%s\")\n"
argument_list|,
name|uri
argument_list|,
name|base_uri
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* this function does not use the algorithm that is being proposed    * in RFC 2396. Instead it analyses the first characters of each    * URI to determine its kind (abs, net, path, ...).    * After that it locates the missing parts in the base URI and then    * concats everything into a newly allocated string.    */
comment|/* determine the kind of the URIs */
name|uri_type
operator|=
name|uri_get_type
argument_list|(
name|uri
argument_list|)
expr_stmt|;
if|if
condition|(
name|uri_type
operator|!=
name|URI_ABSURI
condition|)
block|{
name|base_type
operator|=
name|uri_get_type
argument_list|(
name|base_uri
argument_list|)
expr_stmt|;
if|if
condition|(
name|base_type
operator|!=
name|URI_ABSURI
condition|)
return|return
name|NULL
return|;
comment|/*  neither uri nor base uri are absolute  */
block|}
comment|/* find missing parts in base URI */
switch|switch
condition|(
name|uri_type
condition|)
block|{
case|case
name|URI_ABSURI
case|:
comment|/* base uri not needed */
break|break;
case|case
name|URI_QUERY
case|:
comment|/* ??? last segment? */
name|uri_type
operator|=
name|URI_RELPATH
expr_stmt|;
case|case
name|URI_NETPATH
case|:
comment|/* base scheme */
case|case
name|URI_ABSPATH
case|:
comment|/* base scheme and authority */
case|case
name|URI_RELPATH
case|:
comment|/* base scheme, authority and path */
name|cptr
operator|=
name|base_uri
expr_stmt|;
comment|/* skip scheme */
while|while
condition|(
operator|(
name|c
operator|=
operator|*
name|cptr
operator|++
operator|)
operator|&&
name|c
operator|!=
literal|':'
condition|)
empty_stmt|;
comment|/* nada */
name|base_cnt
operator|=
name|cptr
operator|-
name|base_uri
expr_stmt|;
comment|/* incl : */
if|if
condition|(
operator|*
name|cptr
operator|!=
literal|'/'
condition|)
block|{
comment|/* completion not possible */
return|return
name|NULL
return|;
block|}
if|if
condition|(
name|uri_type
operator|==
name|URI_NETPATH
condition|)
break|break;
comment|/* skip authority */
if|if
condition|(
name|cptr
index|[
literal|0
index|]
operator|==
literal|'/'
operator|&&
name|cptr
index|[
literal|1
index|]
operator|==
literal|'/'
condition|)
block|{
name|part
operator|=
name|cptr
expr_stmt|;
name|cptr
operator|+=
literal|2
expr_stmt|;
while|while
condition|(
operator|(
name|c
operator|=
operator|*
name|cptr
operator|++
operator|)
operator|&&
name|c
operator|!=
literal|'/'
operator|&&
name|c
operator|!=
literal|'?'
operator|&&
name|c
operator|!=
literal|'#'
condition|)
empty_stmt|;
comment|/* nada */
name|cptr
operator|--
expr_stmt|;
name|base_cnt
operator|+=
name|cptr
operator|-
name|part
expr_stmt|;
block|}
if|if
condition|(
name|uri_type
operator|==
name|URI_ABSPATH
condition|)
break|break;
comment|/* skip path */
if|if
condition|(
operator|*
name|cptr
operator|!=
literal|'/'
condition|)
block|{
name|sep_cnt
operator|=
literal|1
expr_stmt|;
name|sep_str
operator|=
literal|"/"
expr_stmt|;
break|break;
block|}
name|part
operator|=
name|cptr
expr_stmt|;
name|g_assert
argument_list|(
operator|*
name|cptr
operator|==
literal|'/'
argument_list|)
expr_stmt|;
while|while
condition|(
operator|(
name|c
operator|=
operator|*
name|cptr
operator|++
operator|)
operator|&&
name|c
operator|!=
literal|'?'
operator|&&
name|c
operator|!=
literal|'#'
condition|)
block|{
if|if
condition|(
name|c
operator|==
literal|'/'
condition|)
name|last_segment
operator|=
name|cptr
operator|-
literal|1
expr_stmt|;
block|}
empty_stmt|;
name|g_assert
argument_list|(
name|last_segment
argument_list|)
expr_stmt|;
name|cptr
operator|=
name|last_segment
expr_stmt|;
while|while
condition|(
operator|(
name|c
operator|=
operator|*
name|uri
operator|)
operator|&&
name|c
operator|==
literal|'.'
operator|&&
name|cptr
operator|>
name|part
condition|)
block|{
name|gint
name|shift_segment
init|=
literal|0
decl_stmt|;
name|c
operator|=
name|uri
index|[
literal|1
index|]
expr_stmt|;
if|if
condition|(
name|c
operator|==
literal|'.'
condition|)
block|{
name|c
operator|=
name|uri
index|[
literal|2
index|]
expr_stmt|;
name|shift_segment
operator|=
literal|1
expr_stmt|;
block|}
if|if
condition|(
name|c
operator|==
literal|'/'
condition|)
block|{
name|uri
operator|+=
literal|2
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|c
operator|==
literal|0
operator|||
name|c
operator|==
literal|'?'
operator|||
name|c
operator|==
literal|'#'
condition|)
block|{
name|uri
operator|+=
literal|1
expr_stmt|;
block|}
else|else
block|{
break|break;
block|}
name|g_assert
argument_list|(
operator|*
name|cptr
operator|==
literal|'/'
argument_list|)
expr_stmt|;
if|if
condition|(
name|shift_segment
condition|)
block|{
name|uri
operator|+=
literal|1
expr_stmt|;
while|while
condition|(
name|cptr
operator|>
name|part
operator|&&
operator|*
operator|--
name|cptr
operator|!=
literal|'/'
condition|)
empty_stmt|;
comment|/* nada */
block|}
block|}
name|base_cnt
operator|+=
name|cptr
operator|-
name|part
operator|+
literal|1
expr_stmt|;
break|break;
case|case
name|URI_EMPTY
case|:
case|case
name|URI_FRAGMENT
case|:
comment|/* use whole base uri */
name|base_cnt
operator|=
name|strlen
argument_list|(
name|base_uri
argument_list|)
expr_stmt|;
break|break;
case|case
name|URI_UNKNOWN
case|:
case|case
name|URI_INVALID
case|:
return|return
name|NULL
return|;
block|}
comment|/* do not include fragment part from the URI reference */
for|for
control|(
name|cptr
operator|=
name|uri
init|;
operator|(
name|c
operator|=
operator|*
name|cptr
operator|)
operator|&&
name|c
operator|!=
literal|'#'
condition|;
name|cptr
operator|++
control|)
empty_stmt|;
comment|/* nada */
name|uri_cnt
operator|=
name|cptr
operator|-
name|uri
expr_stmt|;
comment|/* allocate string and copy characters */
name|retval
operator|=
name|g_new
argument_list|(
name|gchar
argument_list|,
name|base_cnt
operator|+
name|sep_cnt
operator|+
name|uri_cnt
operator|+
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|base_cnt
condition|)
name|strncpy
argument_list|(
name|retval
argument_list|,
name|base_uri
argument_list|,
name|base_cnt
argument_list|)
expr_stmt|;
if|if
condition|(
name|sep_cnt
condition|)
name|strncpy
argument_list|(
name|retval
operator|+
name|base_cnt
argument_list|,
name|sep_str
argument_list|,
name|sep_cnt
argument_list|)
expr_stmt|;
if|if
condition|(
name|uri_cnt
condition|)
name|strncpy
argument_list|(
name|retval
operator|+
name|base_cnt
operator|+
name|sep_cnt
argument_list|,
name|uri
argument_list|,
name|uri_cnt
argument_list|)
expr_stmt|;
name|retval
index|[
name|base_cnt
operator|+
name|sep_cnt
operator|+
name|uri_cnt
index|]
operator|=
literal|'\0'
expr_stmt|;
ifdef|#
directive|ifdef
name|URI_DEBUG
name|g_print
argument_list|(
literal|"  ->  \"%s\"\n"
argument_list|,
name|retval
argument_list|)
expr_stmt|;
endif|#
directive|endif
return|return
name|retval
return|;
block|}
end_function

begin_if
if|#
directive|if
literal|0
end_if

begin_endif
unit|RFC 2396                   URI Generic Syntax                August 1998   A. Collected BNF for URI        URI-reference = [ absoluteURI | relativeURI ] [ "#" fragment ]       absoluteURI   = scheme ":" ( hier_part | opaque_part )       relativeURI   = ( net_path | abs_path | rel_path ) [ "?" query ]        hier_part     = ( net_path | abs_path ) [ "?" query ]       opaque_part   = uric_no_slash *uric        uric_no_slash = unreserved | escaped | ";" | "?" | ":" | "@" |                       "&" | "=" | "+" | "$" | ","        net_path      = "//" authority [ abs_path ]       abs_path      = "/"  path_segments       rel_path      = rel_segment [ abs_path ]        rel_segment   = 1*( unreserved | escaped |                           ";" | "@" | "&" | "=" | "+" | "$" | "," )        scheme        = alpha *( alpha | digit | "+" | "-" | "." )        authority     = server | reg_name        reg_name      = 1*( unreserved | escaped | "$" | "," |                           ";" | ":" | "@" | "&" | "=" | "+" )        server        = [ [ userinfo "@" ] hostport ]       userinfo      = *( unreserved | escaped |                          ";" | ":" | "&" | "=" | "+" | "$" | "," )        hostport      = host [ ":" port ]       host          = hostname | IPv4address       hostname      = *( domainlabel "." ) toplabel [ "." ]       domainlabel   = alphanum | alphanum *( alphanum | "-" ) alphanum       toplabel      = alpha | alpha *( alphanum | "-" ) alphanum       IPv4address   = 1*digit "." 1*digit "." 1*digit "." 1*digit       port          = *digit        path          = [ abs_path | opaque_part ]       path_segments = segment *( "/" segment )       segment       = *pchar *( ";" param )       param         = *pchar       pchar         = unreserved | escaped |                       ":" | "@" | "&" | "=" | "+" | "$" | ","        query         = *uric        fragment      = *uric        uric          = reserved | unreserved | escaped       reserved      = ";" | "/" | "?" | ":" | "@" | "&" | "=" | "+" |                       "$" | ","       unreserved    = alphanum | mark       mark          = "-" | "_" | "." | "!" | "~" | "*" | "'" |                       "(" | ")"        escaped       = "%" hex hex       hex           = digit | "A" | "B" | "C" | "D" | "E" | "F" |                               "a" | "b" | "c" | "d" | "e" | "f"        alphanum      = alpha | digit       alpha         = lowalpha | upalpha        lowalpha = "a" | "b" | "c" | "d" | "e" | "f" | "g" | "h" | "i" |                  "j" | "k" | "l" | "m" | "n" | "o" | "p" | "q" | "r" |                  "s" | "t" | "u" | "v" | "w" | "x" | "y" | "z"       upalpha  = "A" | "B" | "C" | "D" | "E" | "F" | "G" | "H" | "I" |                  "J" | "K" | "L" | "M" | "N" | "O" | "P" | "Q" | "R" |                  "S" | "T" | "U" | "V" | "W" | "X" | "Y" | "Z"       digit    = "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" |                  "8" | "9"
endif|#
directive|endif
end_endif

end_unit

