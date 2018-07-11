begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * IfsCompose is a interface for creating IFS fractals by  * direct manipulation.  * Copyright (C) 1997 Owen Taylor  *  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTBILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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

begin_comment
comment|/* strlen */
end_comment

begin_include
include|#
directive|include
file|<gdk/gdk.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|"ifs-compose.h"
end_include

begin_typedef
DECL|enum|__anon2b9f7a820103
typedef|typedef
enum|enum
block|{
DECL|enumerator|TOKEN_INVALID
name|TOKEN_INVALID
init|=
name|G_TOKEN_LAST
block|,
DECL|enumerator|TOKEN_ITERATIONS
name|TOKEN_ITERATIONS
block|,
DECL|enumerator|TOKEN_MAX_MEMORY
name|TOKEN_MAX_MEMORY
block|,
DECL|enumerator|TOKEN_SUBDIVIDE
name|TOKEN_SUBDIVIDE
block|,
DECL|enumerator|TOKEN_RADIUS
name|TOKEN_RADIUS
block|,
DECL|enumerator|TOKEN_ASPECT_RATIO
name|TOKEN_ASPECT_RATIO
block|,
DECL|enumerator|TOKEN_CENTER_X
name|TOKEN_CENTER_X
block|,
DECL|enumerator|TOKEN_CENTER_Y
name|TOKEN_CENTER_Y
block|,
DECL|enumerator|TOKEN_ELEMENT
name|TOKEN_ELEMENT
block|,
DECL|enumerator|TOKEN_X
name|TOKEN_X
block|,
DECL|enumerator|TOKEN_Y
name|TOKEN_Y
block|,
DECL|enumerator|TOKEN_THETA
name|TOKEN_THETA
block|,
DECL|enumerator|TOKEN_SCALE
name|TOKEN_SCALE
block|,
DECL|enumerator|TOKEN_ASYM
name|TOKEN_ASYM
block|,
DECL|enumerator|TOKEN_SHEAR
name|TOKEN_SHEAR
block|,
DECL|enumerator|TOKEN_FLIP
name|TOKEN_FLIP
block|,
DECL|enumerator|TOKEN_RED_COLOR
name|TOKEN_RED_COLOR
block|,
DECL|enumerator|TOKEN_GREEN_COLOR
name|TOKEN_GREEN_COLOR
block|,
DECL|enumerator|TOKEN_BLUE_COLOR
name|TOKEN_BLUE_COLOR
block|,
DECL|enumerator|TOKEN_BLACK_COLOR
name|TOKEN_BLACK_COLOR
block|,
DECL|enumerator|TOKEN_TARGET_COLOR
name|TOKEN_TARGET_COLOR
block|,
DECL|enumerator|TOKEN_HUE_SCALE
name|TOKEN_HUE_SCALE
block|,
DECL|enumerator|TOKEN_VALUE_SCALE
name|TOKEN_VALUE_SCALE
block|,
DECL|enumerator|TOKEN_SIMPLE_COLOR
name|TOKEN_SIMPLE_COLOR
block|,
DECL|enumerator|TOKEN_PROB
name|TOKEN_PROB
DECL|typedef|IfsComposeToken
block|}
name|IfsComposeToken
typedef|;
end_typedef

begin_struct
specifier|static
struct|struct
DECL|struct|__anon2b9f7a820208
block|{
DECL|member|name
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|member|token
name|IfsComposeToken
name|token
decl_stmt|;
DECL|variable|symbols
block|}
name|symbols
index|[]
init|=
block|{
block|{
literal|"iterations"
block|,
name|TOKEN_ITERATIONS
block|}
block|,
block|{
literal|"max_memory"
block|,
name|TOKEN_MAX_MEMORY
block|}
block|,
block|{
literal|"subdivide"
block|,
name|TOKEN_SUBDIVIDE
block|}
block|,
block|{
literal|"radius"
block|,
name|TOKEN_RADIUS
block|}
block|,
block|{
literal|"aspect_ratio"
block|,
name|TOKEN_ASPECT_RATIO
block|}
block|,
block|{
literal|"center_x"
block|,
name|TOKEN_CENTER_X
block|}
block|,
block|{
literal|"center_y"
block|,
name|TOKEN_CENTER_Y
block|}
block|,
block|{
literal|"element"
block|,
name|TOKEN_ELEMENT
block|}
block|,
block|{
literal|"x"
block|,
name|TOKEN_X
block|}
block|,
block|{
literal|"y"
block|,
name|TOKEN_Y
block|}
block|,
block|{
literal|"theta"
block|,
name|TOKEN_THETA
block|}
block|,
block|{
literal|"scale"
block|,
name|TOKEN_SCALE
block|}
block|,
block|{
literal|"asym"
block|,
name|TOKEN_ASYM
block|}
block|,
block|{
literal|"shear"
block|,
name|TOKEN_SHEAR
block|}
block|,
block|{
literal|"flip"
block|,
name|TOKEN_FLIP
block|}
block|,
block|{
literal|"red_color"
block|,
name|TOKEN_RED_COLOR
block|}
block|,
block|{
literal|"green_color"
block|,
name|TOKEN_GREEN_COLOR
block|}
block|,
block|{
literal|"blue_color"
block|,
name|TOKEN_BLUE_COLOR
block|}
block|,
block|{
literal|"black_color"
block|,
name|TOKEN_BLACK_COLOR
block|}
block|,
block|{
literal|"target_color"
block|,
name|TOKEN_TARGET_COLOR
block|}
block|,
block|{
literal|"hue_scale"
block|,
name|TOKEN_HUE_SCALE
block|}
block|,
block|{
literal|"value_scale"
block|,
name|TOKEN_VALUE_SCALE
block|}
block|,
block|{
literal|"simple_color"
block|,
name|TOKEN_SIMPLE_COLOR
block|}
block|,
block|{
literal|"prob"
block|,
name|TOKEN_PROB
block|}
block|}
struct|;
end_struct

begin_function
specifier|static
name|GTokenType
DECL|function|ifsvals_parse_color (GScanner * scanner,GimpRGB * result)
name|ifsvals_parse_color
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|GimpRGB
modifier|*
name|result
parameter_list|)
block|{
name|GTokenType
name|token
decl_stmt|;
name|token
operator|=
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
if|if
condition|(
name|token
operator|!=
name|G_TOKEN_LEFT_CURLY
condition|)
return|return
name|G_TOKEN_LEFT_CURLY
return|;
name|token
operator|=
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
if|if
condition|(
name|token
operator|!=
name|G_TOKEN_FLOAT
condition|)
return|return
name|G_TOKEN_FLOAT
return|;
name|result
operator|->
name|r
operator|=
name|scanner
operator|->
name|value
operator|.
name|v_float
expr_stmt|;
name|token
operator|=
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
if|if
condition|(
name|token
operator|!=
name|G_TOKEN_COMMA
condition|)
return|return
name|G_TOKEN_COMMA
return|;
name|token
operator|=
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
if|if
condition|(
name|token
operator|!=
name|G_TOKEN_FLOAT
condition|)
return|return
name|G_TOKEN_FLOAT
return|;
name|result
operator|->
name|g
operator|=
name|scanner
operator|->
name|value
operator|.
name|v_float
expr_stmt|;
name|token
operator|=
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
if|if
condition|(
name|token
operator|!=
name|G_TOKEN_COMMA
condition|)
return|return
name|G_TOKEN_COMMA
return|;
name|token
operator|=
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
if|if
condition|(
name|token
operator|!=
name|G_TOKEN_FLOAT
condition|)
return|return
name|G_TOKEN_FLOAT
return|;
name|result
operator|->
name|b
operator|=
name|scanner
operator|->
name|value
operator|.
name|v_float
expr_stmt|;
name|token
operator|=
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
if|if
condition|(
name|token
operator|!=
name|G_TOKEN_RIGHT_CURLY
condition|)
return|return
name|G_TOKEN_RIGHT_CURLY
return|;
return|return
name|G_TOKEN_NONE
return|;
block|}
end_function

begin_comment
comment|/* Parse a float which (unlike G_TOKEN_FLOAT) can be negative  */
end_comment

begin_function
specifier|static
name|GTokenType
DECL|function|parse_genuine_float (GScanner * scanner,gdouble * result)
name|parse_genuine_float
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|gdouble
modifier|*
name|result
parameter_list|)
block|{
name|gboolean
name|negate
init|=
name|FALSE
decl_stmt|;
name|GTokenType
name|token
decl_stmt|;
name|token
operator|=
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
if|if
condition|(
name|token
operator|==
literal|'-'
condition|)
block|{
name|negate
operator|=
name|TRUE
expr_stmt|;
name|token
operator|=
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|token
operator|==
name|G_TOKEN_FLOAT
condition|)
block|{
operator|*
name|result
operator|=
name|negate
condition|?
operator|-
name|scanner
operator|->
name|value
operator|.
name|v_float
else|:
name|scanner
operator|->
name|value
operator|.
name|v_float
expr_stmt|;
return|return
name|G_TOKEN_NONE
return|;
block|}
else|else
return|return
name|G_TOKEN_FLOAT
return|;
block|}
end_function

begin_function
specifier|static
name|GTokenType
DECL|function|ifsvals_parse_element (GScanner * scanner,AffElementVals * result)
name|ifsvals_parse_element
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|AffElementVals
modifier|*
name|result
parameter_list|)
block|{
name|GTokenType
name|token
decl_stmt|;
name|GTokenType
name|expected_token
decl_stmt|;
name|token
operator|=
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
if|if
condition|(
name|token
operator|!=
name|G_TOKEN_LEFT_CURLY
condition|)
return|return
name|G_TOKEN_LEFT_CURLY
return|;
name|token
operator|=
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
while|while
condition|(
name|token
operator|!=
name|G_TOKEN_RIGHT_CURLY
condition|)
block|{
switch|switch
condition|(
operator|(
name|IfsComposeToken
operator|)
name|token
condition|)
block|{
case|case
name|TOKEN_X
case|:
name|expected_token
operator|=
name|parse_genuine_float
argument_list|(
name|scanner
argument_list|,
operator|&
name|result
operator|->
name|x
argument_list|)
expr_stmt|;
if|if
condition|(
name|expected_token
operator|!=
name|G_TOKEN_NONE
condition|)
return|return
name|expected_token
return|;
break|break;
case|case
name|TOKEN_Y
case|:
name|expected_token
operator|=
name|parse_genuine_float
argument_list|(
name|scanner
argument_list|,
operator|&
name|result
operator|->
name|y
argument_list|)
expr_stmt|;
if|if
condition|(
name|expected_token
operator|!=
name|G_TOKEN_NONE
condition|)
return|return
name|expected_token
return|;
break|break;
case|case
name|TOKEN_THETA
case|:
name|expected_token
operator|=
name|parse_genuine_float
argument_list|(
name|scanner
argument_list|,
operator|&
name|result
operator|->
name|theta
argument_list|)
expr_stmt|;
if|if
condition|(
name|expected_token
operator|!=
name|G_TOKEN_NONE
condition|)
return|return
name|expected_token
return|;
break|break;
case|case
name|TOKEN_SCALE
case|:
name|expected_token
operator|=
name|parse_genuine_float
argument_list|(
name|scanner
argument_list|,
operator|&
name|result
operator|->
name|scale
argument_list|)
expr_stmt|;
if|if
condition|(
name|expected_token
operator|!=
name|G_TOKEN_NONE
condition|)
return|return
name|expected_token
return|;
break|break;
case|case
name|TOKEN_ASYM
case|:
name|expected_token
operator|=
name|parse_genuine_float
argument_list|(
name|scanner
argument_list|,
operator|&
name|result
operator|->
name|asym
argument_list|)
expr_stmt|;
if|if
condition|(
name|expected_token
operator|!=
name|G_TOKEN_NONE
condition|)
return|return
name|expected_token
return|;
break|break;
case|case
name|TOKEN_SHEAR
case|:
name|expected_token
operator|=
name|parse_genuine_float
argument_list|(
name|scanner
argument_list|,
operator|&
name|result
operator|->
name|shear
argument_list|)
expr_stmt|;
if|if
condition|(
name|expected_token
operator|!=
name|G_TOKEN_NONE
condition|)
return|return
name|expected_token
return|;
break|break;
case|case
name|TOKEN_FLIP
case|:
name|token
operator|=
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
if|if
condition|(
name|token
operator|!=
name|G_TOKEN_INT
condition|)
return|return
name|G_TOKEN_INT
return|;
name|result
operator|->
name|flip
operator|=
name|scanner
operator|->
name|value
operator|.
name|v_int
expr_stmt|;
break|break;
case|case
name|TOKEN_RED_COLOR
case|:
name|token
operator|=
name|ifsvals_parse_color
argument_list|(
name|scanner
argument_list|,
operator|&
name|result
operator|->
name|red_color
argument_list|)
expr_stmt|;
if|if
condition|(
name|token
operator|!=
name|G_TOKEN_NONE
condition|)
return|return
name|token
return|;
break|break;
case|case
name|TOKEN_GREEN_COLOR
case|:
name|token
operator|=
name|ifsvals_parse_color
argument_list|(
name|scanner
argument_list|,
operator|&
name|result
operator|->
name|green_color
argument_list|)
expr_stmt|;
if|if
condition|(
name|token
operator|!=
name|G_TOKEN_NONE
condition|)
return|return
name|token
return|;
break|break;
case|case
name|TOKEN_BLUE_COLOR
case|:
name|token
operator|=
name|ifsvals_parse_color
argument_list|(
name|scanner
argument_list|,
operator|&
name|result
operator|->
name|blue_color
argument_list|)
expr_stmt|;
if|if
condition|(
name|token
operator|!=
name|G_TOKEN_NONE
condition|)
return|return
name|token
return|;
break|break;
case|case
name|TOKEN_BLACK_COLOR
case|:
name|token
operator|=
name|ifsvals_parse_color
argument_list|(
name|scanner
argument_list|,
operator|&
name|result
operator|->
name|black_color
argument_list|)
expr_stmt|;
if|if
condition|(
name|token
operator|!=
name|G_TOKEN_NONE
condition|)
return|return
name|token
return|;
break|break;
case|case
name|TOKEN_TARGET_COLOR
case|:
name|token
operator|=
name|ifsvals_parse_color
argument_list|(
name|scanner
argument_list|,
operator|&
name|result
operator|->
name|target_color
argument_list|)
expr_stmt|;
if|if
condition|(
name|token
operator|!=
name|G_TOKEN_NONE
condition|)
return|return
name|token
return|;
break|break;
case|case
name|TOKEN_HUE_SCALE
case|:
name|expected_token
operator|=
name|parse_genuine_float
argument_list|(
name|scanner
argument_list|,
operator|&
name|result
operator|->
name|hue_scale
argument_list|)
expr_stmt|;
if|if
condition|(
name|expected_token
operator|!=
name|G_TOKEN_NONE
condition|)
return|return
name|expected_token
return|;
break|break;
case|case
name|TOKEN_VALUE_SCALE
case|:
name|expected_token
operator|=
name|parse_genuine_float
argument_list|(
name|scanner
argument_list|,
operator|&
name|result
operator|->
name|value_scale
argument_list|)
expr_stmt|;
if|if
condition|(
name|expected_token
operator|!=
name|G_TOKEN_NONE
condition|)
return|return
name|expected_token
return|;
break|break;
case|case
name|TOKEN_SIMPLE_COLOR
case|:
name|token
operator|=
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
if|if
condition|(
name|token
operator|!=
name|G_TOKEN_INT
condition|)
return|return
name|G_TOKEN_INT
return|;
name|result
operator|->
name|simple_color
operator|=
name|scanner
operator|->
name|value
operator|.
name|v_int
expr_stmt|;
break|break;
case|case
name|TOKEN_PROB
case|:
name|token
operator|=
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
if|if
condition|(
name|token
operator|!=
name|G_TOKEN_FLOAT
condition|)
return|return
name|G_TOKEN_FLOAT
return|;
name|result
operator|->
name|prob
operator|=
name|scanner
operator|->
name|value
operator|.
name|v_float
expr_stmt|;
break|break;
default|default:
return|return
name|G_TOKEN_SYMBOL
return|;
block|}
name|token
operator|=
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
block|}
return|return
name|G_TOKEN_NONE
return|;
block|}
end_function

begin_comment
comment|/*************************************************************  * ifsvals_parse:  *     Read in ifsvalues from a GScanner  *   arguments:  *     scanner:  *     vals:  *     elements:  *  *   results:  *     If parsing succeeded, TRUE; otherwise FALSE, in which  *     case vals and elements are unchanged  *************************************************************/
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|ifsvals_parse (GScanner * scanner,IfsComposeVals * vals,AffElement *** elements)
name|ifsvals_parse
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|IfsComposeVals
modifier|*
name|vals
parameter_list|,
name|AffElement
modifier|*
modifier|*
modifier|*
name|elements
parameter_list|)
block|{
name|GTokenType
name|token
decl_stmt|,
name|expected_token
decl_stmt|;
name|AffElement
modifier|*
name|el
decl_stmt|;
name|IfsComposeVals
name|new_vals
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|GList
modifier|*
name|el_list
init|=
name|NULL
decl_stmt|;
name|GList
modifier|*
name|tmp_list
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|new_vals
operator|=
operator|*
name|vals
expr_stmt|;
name|new_vals
operator|.
name|num_elements
operator|=
literal|0
expr_stmt|;
name|i
operator|=
literal|0
expr_stmt|;
name|expected_token
operator|=
name|G_TOKEN_NONE
expr_stmt|;
while|while
condition|(
name|expected_token
operator|==
name|G_TOKEN_NONE
condition|)
block|{
name|token
operator|=
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_scanner_eof
argument_list|(
name|scanner
argument_list|)
condition|)
break|break;
switch|switch
condition|(
operator|(
name|IfsComposeToken
operator|)
name|token
condition|)
block|{
case|case
name|TOKEN_ITERATIONS
case|:
name|token
operator|=
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
if|if
condition|(
name|token
operator|==
name|G_TOKEN_INT
condition|)
name|new_vals
operator|.
name|iterations
operator|=
name|scanner
operator|->
name|value
operator|.
name|v_int
expr_stmt|;
else|else
name|expected_token
operator|=
name|G_TOKEN_INT
expr_stmt|;
break|break;
case|case
name|TOKEN_MAX_MEMORY
case|:
name|token
operator|=
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
if|if
condition|(
name|token
operator|==
name|G_TOKEN_INT
condition|)
name|new_vals
operator|.
name|max_memory
operator|=
name|scanner
operator|->
name|value
operator|.
name|v_int
expr_stmt|;
else|else
name|expected_token
operator|=
name|G_TOKEN_INT
expr_stmt|;
break|break;
case|case
name|TOKEN_SUBDIVIDE
case|:
name|token
operator|=
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
if|if
condition|(
name|token
operator|==
name|G_TOKEN_INT
condition|)
name|new_vals
operator|.
name|subdivide
operator|=
name|scanner
operator|->
name|value
operator|.
name|v_int
expr_stmt|;
else|else
name|expected_token
operator|=
name|G_TOKEN_INT
expr_stmt|;
break|break;
case|case
name|TOKEN_RADIUS
case|:
name|expected_token
operator|=
name|parse_genuine_float
argument_list|(
name|scanner
argument_list|,
operator|&
name|new_vals
operator|.
name|radius
argument_list|)
expr_stmt|;
break|break;
case|case
name|TOKEN_ASPECT_RATIO
case|:
name|expected_token
operator|=
name|parse_genuine_float
argument_list|(
name|scanner
argument_list|,
operator|&
name|new_vals
operator|.
name|aspect_ratio
argument_list|)
expr_stmt|;
break|break;
case|case
name|TOKEN_CENTER_X
case|:
name|expected_token
operator|=
name|parse_genuine_float
argument_list|(
name|scanner
argument_list|,
operator|&
name|new_vals
operator|.
name|center_x
argument_list|)
expr_stmt|;
break|break;
case|case
name|TOKEN_CENTER_Y
case|:
name|expected_token
operator|=
name|parse_genuine_float
argument_list|(
name|scanner
argument_list|,
operator|&
name|new_vals
operator|.
name|center_y
argument_list|)
expr_stmt|;
break|break;
case|case
name|TOKEN_ELEMENT
case|:
name|el
operator|=
name|aff_element_new
argument_list|(
literal|0.0
argument_list|,
literal|0.0
argument_list|,
operator|&
name|color
argument_list|,
operator|++
name|i
argument_list|)
expr_stmt|;
name|expected_token
operator|=
name|ifsvals_parse_element
argument_list|(
name|scanner
argument_list|,
operator|&
name|el
operator|->
name|v
argument_list|)
expr_stmt|;
if|if
condition|(
name|expected_token
operator|==
name|G_TOKEN_NONE
condition|)
block|{
name|el_list
operator|=
name|g_list_prepend
argument_list|(
name|el_list
argument_list|,
name|el
argument_list|)
expr_stmt|;
name|new_vals
operator|.
name|num_elements
operator|++
expr_stmt|;
block|}
else|else
name|aff_element_free
argument_list|(
name|el
argument_list|)
expr_stmt|;
break|break;
default|default:
name|expected_token
operator|=
name|G_TOKEN_SYMBOL
expr_stmt|;
block|}
block|}
if|if
condition|(
name|expected_token
operator|!=
name|G_TOKEN_NONE
condition|)
block|{
name|g_scanner_unexp_token
argument_list|(
name|scanner
argument_list|,
name|expected_token
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|"using default values..."
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_list_free_full
argument_list|(
name|el_list
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_free
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
operator|*
name|vals
operator|=
name|new_vals
expr_stmt|;
name|el_list
operator|=
name|g_list_reverse
argument_list|(
name|el_list
argument_list|)
expr_stmt|;
operator|*
name|elements
operator|=
name|g_new
argument_list|(
name|AffElement
operator|*
argument_list|,
name|new_vals
operator|.
name|num_elements
argument_list|)
expr_stmt|;
name|tmp_list
operator|=
name|el_list
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|new_vals
operator|.
name|num_elements
condition|;
name|i
operator|++
control|)
block|{
operator|(
operator|*
name|elements
operator|)
index|[
name|i
index|]
operator|=
name|tmp_list
operator|->
name|data
expr_stmt|;
name|tmp_list
operator|=
name|tmp_list
operator|->
name|next
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|el_list
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|ifsvals_parse_string (const gchar * str,IfsComposeVals * vals,AffElement *** elements)
name|ifsvals_parse_string
parameter_list|(
specifier|const
name|gchar
modifier|*
name|str
parameter_list|,
name|IfsComposeVals
modifier|*
name|vals
parameter_list|,
name|AffElement
modifier|*
modifier|*
modifier|*
name|elements
parameter_list|)
block|{
name|GScanner
modifier|*
name|scanner
init|=
name|g_scanner_new
argument_list|(
name|NULL
argument_list|)
decl_stmt|;
name|gboolean
name|result
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|scanner
operator|->
name|config
operator|->
name|symbol_2_token
operator|=
name|TRUE
expr_stmt|;
name|scanner
operator|->
name|config
operator|->
name|scan_identifier_1char
operator|=
name|TRUE
expr_stmt|;
name|scanner
operator|->
name|input_name
operator|=
literal|"IfsCompose Saved Data"
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|G_N_ELEMENTS
argument_list|(
name|symbols
argument_list|)
condition|;
name|i
operator|++
control|)
name|g_scanner_scope_add_symbol
argument_list|(
name|scanner
argument_list|,
literal|0
argument_list|,
name|symbols
index|[
name|i
index|]
operator|.
name|name
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|symbols
index|[
name|i
index|]
operator|.
name|token
argument_list|)
argument_list|)
expr_stmt|;
name|g_scanner_input_text
argument_list|(
name|scanner
argument_list|,
name|str
argument_list|,
name|strlen
argument_list|(
name|str
argument_list|)
argument_list|)
expr_stmt|;
name|result
operator|=
name|ifsvals_parse
argument_list|(
name|scanner
argument_list|,
name|vals
argument_list|,
name|elements
argument_list|)
expr_stmt|;
name|g_scanner_destroy
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
return|return
name|result
return|;
block|}
end_function

begin_comment
comment|/*************************************************************  * ifsvals_stringify:  *     Stringify a set of vals and elements  *   arguments:  *     vals:  *     elements  *   results:  *     The stringified result (free with g_free)  *************************************************************/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|ifsvals_stringify (IfsComposeVals * vals,AffElement ** elements)
name|ifsvals_stringify
parameter_list|(
name|IfsComposeVals
modifier|*
name|vals
parameter_list|,
name|AffElement
modifier|*
modifier|*
name|elements
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
name|gchar
name|buf
index|[
name|G_ASCII_DTOSTR_BUF_SIZE
index|]
decl_stmt|;
name|gchar
name|cbuf
index|[
literal|3
index|]
index|[
name|G_ASCII_DTOSTR_BUF_SIZE
index|]
decl_stmt|;
name|GString
modifier|*
name|result
decl_stmt|;
name|result
operator|=
name|g_string_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|g_string_append_printf
argument_list|(
name|result
argument_list|,
literal|"iterations %d\n"
argument_list|,
name|vals
operator|->
name|iterations
argument_list|)
expr_stmt|;
name|g_string_append_printf
argument_list|(
name|result
argument_list|,
literal|"max_memory %d\n"
argument_list|,
name|vals
operator|->
name|max_memory
argument_list|)
expr_stmt|;
name|g_string_append_printf
argument_list|(
name|result
argument_list|,
literal|"subdivide %d\n"
argument_list|,
name|vals
operator|->
name|subdivide
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|buf
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|vals
operator|->
name|radius
argument_list|)
expr_stmt|;
name|g_string_append_printf
argument_list|(
name|result
argument_list|,
literal|"radius %s\n"
argument_list|,
name|buf
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|buf
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|vals
operator|->
name|aspect_ratio
argument_list|)
expr_stmt|;
name|g_string_append_printf
argument_list|(
name|result
argument_list|,
literal|"aspect_ratio %s\n"
argument_list|,
name|buf
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|buf
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|vals
operator|->
name|center_x
argument_list|)
expr_stmt|;
name|g_string_append_printf
argument_list|(
name|result
argument_list|,
literal|"center_x %s\n"
argument_list|,
name|buf
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|buf
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|vals
operator|->
name|center_y
argument_list|)
expr_stmt|;
name|g_string_append_printf
argument_list|(
name|result
argument_list|,
literal|"center_y %s\n"
argument_list|,
name|buf
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|vals
operator|->
name|num_elements
condition|;
name|i
operator|++
control|)
block|{
name|g_string_append
argument_list|(
name|result
argument_list|,
literal|"element {\n"
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|buf
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|elements
index|[
name|i
index|]
operator|->
name|v
operator|.
name|x
argument_list|)
expr_stmt|;
name|g_string_append_printf
argument_list|(
name|result
argument_list|,
literal|"    x %s\n"
argument_list|,
name|buf
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|buf
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|elements
index|[
name|i
index|]
operator|->
name|v
operator|.
name|y
argument_list|)
expr_stmt|;
name|g_string_append_printf
argument_list|(
name|result
argument_list|,
literal|"    y %s\n"
argument_list|,
name|buf
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|buf
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|elements
index|[
name|i
index|]
operator|->
name|v
operator|.
name|theta
argument_list|)
expr_stmt|;
name|g_string_append_printf
argument_list|(
name|result
argument_list|,
literal|"    theta %s\n"
argument_list|,
name|buf
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|buf
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|elements
index|[
name|i
index|]
operator|->
name|v
operator|.
name|scale
argument_list|)
expr_stmt|;
name|g_string_append_printf
argument_list|(
name|result
argument_list|,
literal|"    scale %s\n"
argument_list|,
name|buf
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|buf
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|elements
index|[
name|i
index|]
operator|->
name|v
operator|.
name|asym
argument_list|)
expr_stmt|;
name|g_string_append_printf
argument_list|(
name|result
argument_list|,
literal|"    asym %s\n"
argument_list|,
name|buf
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|buf
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|elements
index|[
name|i
index|]
operator|->
name|v
operator|.
name|shear
argument_list|)
expr_stmt|;
name|g_string_append_printf
argument_list|(
name|result
argument_list|,
literal|"    shear %s\n"
argument_list|,
name|buf
argument_list|)
expr_stmt|;
name|g_string_append_printf
argument_list|(
name|result
argument_list|,
literal|"    flip %d\n"
argument_list|,
name|elements
index|[
name|i
index|]
operator|->
name|v
operator|.
name|flip
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|cbuf
index|[
literal|0
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|elements
index|[
name|i
index|]
operator|->
name|v
operator|.
name|red_color
operator|.
name|r
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|cbuf
index|[
literal|1
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|elements
index|[
name|i
index|]
operator|->
name|v
operator|.
name|red_color
operator|.
name|g
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|cbuf
index|[
literal|2
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|elements
index|[
name|i
index|]
operator|->
name|v
operator|.
name|red_color
operator|.
name|b
argument_list|)
expr_stmt|;
name|g_string_append_printf
argument_list|(
name|result
argument_list|,
literal|"    red_color { %s,%s,%s }\n"
argument_list|,
name|cbuf
index|[
literal|0
index|]
argument_list|,
name|cbuf
index|[
literal|1
index|]
argument_list|,
name|cbuf
index|[
literal|2
index|]
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|cbuf
index|[
literal|0
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|elements
index|[
name|i
index|]
operator|->
name|v
operator|.
name|green_color
operator|.
name|r
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|cbuf
index|[
literal|1
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|elements
index|[
name|i
index|]
operator|->
name|v
operator|.
name|green_color
operator|.
name|g
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|cbuf
index|[
literal|2
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|elements
index|[
name|i
index|]
operator|->
name|v
operator|.
name|green_color
operator|.
name|b
argument_list|)
expr_stmt|;
name|g_string_append_printf
argument_list|(
name|result
argument_list|,
literal|"    green_color { %s,%s,%s }\n"
argument_list|,
name|cbuf
index|[
literal|0
index|]
argument_list|,
name|cbuf
index|[
literal|1
index|]
argument_list|,
name|cbuf
index|[
literal|2
index|]
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|cbuf
index|[
literal|0
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|elements
index|[
name|i
index|]
operator|->
name|v
operator|.
name|blue_color
operator|.
name|r
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|cbuf
index|[
literal|1
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|elements
index|[
name|i
index|]
operator|->
name|v
operator|.
name|blue_color
operator|.
name|g
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|cbuf
index|[
literal|2
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|elements
index|[
name|i
index|]
operator|->
name|v
operator|.
name|blue_color
operator|.
name|b
argument_list|)
expr_stmt|;
name|g_string_append_printf
argument_list|(
name|result
argument_list|,
literal|"    blue_color { %s,%s,%s }\n"
argument_list|,
name|cbuf
index|[
literal|0
index|]
argument_list|,
name|cbuf
index|[
literal|1
index|]
argument_list|,
name|cbuf
index|[
literal|2
index|]
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|cbuf
index|[
literal|0
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|elements
index|[
name|i
index|]
operator|->
name|v
operator|.
name|black_color
operator|.
name|r
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|cbuf
index|[
literal|1
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|elements
index|[
name|i
index|]
operator|->
name|v
operator|.
name|black_color
operator|.
name|g
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|cbuf
index|[
literal|2
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|elements
index|[
name|i
index|]
operator|->
name|v
operator|.
name|black_color
operator|.
name|b
argument_list|)
expr_stmt|;
name|g_string_append_printf
argument_list|(
name|result
argument_list|,
literal|"    black_color { %s,%s,%s }\n"
argument_list|,
name|cbuf
index|[
literal|0
index|]
argument_list|,
name|cbuf
index|[
literal|1
index|]
argument_list|,
name|cbuf
index|[
literal|2
index|]
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|cbuf
index|[
literal|0
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|elements
index|[
name|i
index|]
operator|->
name|v
operator|.
name|target_color
operator|.
name|r
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|cbuf
index|[
literal|1
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|elements
index|[
name|i
index|]
operator|->
name|v
operator|.
name|target_color
operator|.
name|g
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|cbuf
index|[
literal|2
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|elements
index|[
name|i
index|]
operator|->
name|v
operator|.
name|target_color
operator|.
name|b
argument_list|)
expr_stmt|;
name|g_string_append_printf
argument_list|(
name|result
argument_list|,
literal|"    target_color { %s,%s,%s }\n"
argument_list|,
name|cbuf
index|[
literal|0
index|]
argument_list|,
name|cbuf
index|[
literal|1
index|]
argument_list|,
name|cbuf
index|[
literal|2
index|]
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|buf
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|elements
index|[
name|i
index|]
operator|->
name|v
operator|.
name|hue_scale
argument_list|)
expr_stmt|;
name|g_string_append_printf
argument_list|(
name|result
argument_list|,
literal|"    hue_scale %s\n"
argument_list|,
name|buf
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|buf
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|elements
index|[
name|i
index|]
operator|->
name|v
operator|.
name|value_scale
argument_list|)
expr_stmt|;
name|g_string_append_printf
argument_list|(
name|result
argument_list|,
literal|"    value_scale %s\n"
argument_list|,
name|buf
argument_list|)
expr_stmt|;
name|g_string_append_printf
argument_list|(
name|result
argument_list|,
literal|"    simple_color %d\n"
argument_list|,
name|elements
index|[
name|i
index|]
operator|->
name|v
operator|.
name|simple_color
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|buf
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|elements
index|[
name|i
index|]
operator|->
name|v
operator|.
name|prob
argument_list|)
expr_stmt|;
name|g_string_append_printf
argument_list|(
name|result
argument_list|,
literal|"    prob %s\n"
argument_list|,
name|buf
argument_list|)
expr_stmt|;
name|g_string_append
argument_list|(
name|result
argument_list|,
literal|"}\n"
argument_list|)
expr_stmt|;
block|}
return|return
name|g_string_free
argument_list|(
name|result
argument_list|,
name|FALSE
argument_list|)
return|;
block|}
end_function

end_unit

