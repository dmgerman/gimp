begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpeevl.c  * Copyright (C) 2008 Fredrik Alstromer<roe@excu.se>  * Copyright (C) 2008 Martin Nordholts<martinn@svn.gnome.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/* Introducing eevl eva, the evaluator. A straightforward recursive  * descent parser, no fuss, no new dependencies. The lexer is hand  * coded, tedious, not extremely fast but works. It evaluates the  * expression as it goes along, and does not create a parse tree or  * anything, and will not optimize anything. It uses doubles for  * precision, with the given use case, that's enough to combat any  * rounding errors (as opposed to optimizing the evaluation).  *  * It relies on external unit resolving through a callback and does  * elementary dimensionality constraint check (e.g. "2 mm + 3 px * 4  * in" is an error, as L + L^2 is a missmatch). It uses setjmp/longjmp  * for try/catch like pattern on error, it uses g_strtod() for numeric  * conversions and it's non-destructive in terms of the parameters, and  * it's reentrant.  *  * EBNF:  *  *   expression    ::= term { ('+' | '-') term }*  |  *<empty string> ;  *  *   term          ::= ratio { ( '*' | '/' ) ratio }* ;  *  *   ratio         ::= signed factor { ':' signed factor }* ;  *  *   signed factor ::= ( '+' | '-' )? factor ;  *  *   unit factor   ::= factor unit? ;  *  *   factor        ::= number | '(' expression ')' ;  *  *   number        ::= ? what g_strtod() consumes ? ;  *  *   unit          ::= ? what not g_strtod() consumes and not whitespace ? ;  *  * The code should match the EBNF rather closely (except for the  * non-terminal unit factor, which is inlined into factor) for  * maintainability reasons.  *  * It will allow 1++1 and 1+-1 (resulting in 2 and 0, respectively),  * but I figured one might want that, and I don't think it's going to  * throw anyone off.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<setjmp.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"gimpeevl.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgets-error.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/libgimp-intl.h"
end_include

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b0dadeb0103
block|{
DECL|enumerator|GIMP_EEVL_TOKEN_NUM
name|GIMP_EEVL_TOKEN_NUM
init|=
literal|30000
block|,
DECL|enumerator|GIMP_EEVL_TOKEN_IDENTIFIER
name|GIMP_EEVL_TOKEN_IDENTIFIER
init|=
literal|30001
block|,
DECL|enumerator|GIMP_EEVL_TOKEN_ANY
name|GIMP_EEVL_TOKEN_ANY
init|=
literal|40000
block|,
DECL|enumerator|GIMP_EEVL_TOKEN_END
name|GIMP_EEVL_TOKEN_END
init|=
literal|50000
DECL|typedef|GimpEevlTokenType
block|}
name|GimpEevlTokenType
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2b0dadeb0208
block|{
DECL|member|type
name|GimpEevlTokenType
name|type
decl_stmt|;
union|union
DECL|union|__anon2b0dadeb030a
block|{
DECL|member|fl
name|gdouble
name|fl
decl_stmt|;
struct|struct
DECL|struct|__anon2b0dadeb0408
block|{
DECL|member|c
specifier|const
name|gchar
modifier|*
name|c
decl_stmt|;
DECL|member|size
name|gint
name|size
decl_stmt|;
block|}
struct|;
DECL|member|value
block|}
name|value
union|;
DECL|typedef|GimpEevlToken
block|}
name|GimpEevlToken
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2b0dadeb0508
block|{
DECL|member|string
specifier|const
name|gchar
modifier|*
name|string
decl_stmt|;
DECL|member|options
name|GimpEevlOptions
name|options
decl_stmt|;
DECL|member|current_token
name|GimpEevlToken
name|current_token
decl_stmt|;
DECL|member|start_of_current_token
specifier|const
name|gchar
modifier|*
name|start_of_current_token
decl_stmt|;
DECL|member|catcher
name|jmp_buf
name|catcher
decl_stmt|;
DECL|member|error_message
specifier|const
name|gchar
modifier|*
name|error_message
decl_stmt|;
DECL|typedef|GimpEevl
block|}
name|GimpEevl
typedef|;
end_typedef

begin_function_decl
specifier|static
name|void
name|gimp_eevl_init
parameter_list|(
name|GimpEevl
modifier|*
name|eva
parameter_list|,
specifier|const
name|gchar
modifier|*
name|string
parameter_list|,
specifier|const
name|GimpEevlOptions
modifier|*
name|options
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpEevlQuantity
name|gimp_eevl_complete
parameter_list|(
name|GimpEevl
modifier|*
name|eva
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpEevlQuantity
name|gimp_eevl_expression
parameter_list|(
name|GimpEevl
modifier|*
name|eva
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpEevlQuantity
name|gimp_eevl_term
parameter_list|(
name|GimpEevl
modifier|*
name|eva
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpEevlQuantity
name|gimp_eevl_ratio
parameter_list|(
name|GimpEevl
modifier|*
name|eva
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpEevlQuantity
name|gimp_eevl_signed_factor
parameter_list|(
name|GimpEevl
modifier|*
name|eva
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpEevlQuantity
name|gimp_eevl_factor
parameter_list|(
name|GimpEevl
modifier|*
name|eva
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_eevl_accept
parameter_list|(
name|GimpEevl
modifier|*
name|eva
parameter_list|,
name|GimpEevlTokenType
name|token_type
parameter_list|,
name|GimpEevlToken
modifier|*
name|consumed_token
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_eevl_lex
parameter_list|(
name|GimpEevl
modifier|*
name|eva
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_eevl_lex_accept_count
parameter_list|(
name|GimpEevl
modifier|*
name|eva
parameter_list|,
name|gint
name|count
parameter_list|,
name|GimpEevlTokenType
name|token_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_eevl_lex_accept_to
parameter_list|(
name|GimpEevl
modifier|*
name|eva
parameter_list|,
name|gchar
modifier|*
name|to
parameter_list|,
name|GimpEevlTokenType
name|token_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_eevl_move_past_whitespace
parameter_list|(
name|GimpEevl
modifier|*
name|eva
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_eevl_unit_identifier_start
parameter_list|(
name|gunichar
name|c
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_eevl_unit_identifier_continue
parameter_list|(
name|gunichar
name|c
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|gimp_eevl_unit_identifier_size
parameter_list|(
specifier|const
name|gchar
modifier|*
name|s
parameter_list|,
name|gint
name|start
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_eevl_expect
parameter_list|(
name|GimpEevl
modifier|*
name|eva
parameter_list|,
name|GimpEevlTokenType
name|token_type
parameter_list|,
name|GimpEevlToken
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_eevl_error
parameter_list|(
name|GimpEevl
modifier|*
name|eva
parameter_list|,
name|gchar
modifier|*
name|msg
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/**  * gimp_eevl_evaluate:  * @string:        The NULL-terminated string to be evaluated.  * @options:       Evaluations options.  * @result:        Result of evaluation.  * @error_pos:     Will point to the positon within the string,  *                 before which the parse / evaluation error  *                 occurred. Will be set to null of no error occurred.  * @error_message: Will point to a static string with a semi-descriptive  *                 error message if parsing / evaluation failed.  *  * Evaluates the given arithmetic expression, along with an optional dimension  * analysis, and basic unit conversions.  *  * All units conversions factors are relative to some implicit  * base-unit (which in GIMP is inches). This is also the unit of the  * returned value.  *  * Returns: A #GimpEevlQuantity with a value given in the base unit along with  * the order of the dimension (i.e. if the base unit is inches, a dimension  * order of two means in^2).  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_eevl_evaluate (const gchar * string,const GimpEevlOptions * options,GimpEevlQuantity * result,const gchar ** error_pos,GError ** error)
name|gimp_eevl_evaluate
parameter_list|(
specifier|const
name|gchar
modifier|*
name|string
parameter_list|,
specifier|const
name|GimpEevlOptions
modifier|*
name|options
parameter_list|,
name|GimpEevlQuantity
modifier|*
name|result
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|error_pos
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpEevl
name|eva
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|g_utf8_validate
argument_list|(
name|string
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|options
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|options
operator|->
name|unit_resolver_proc
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|result
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|==
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_eevl_init
argument_list|(
operator|&
name|eva
argument_list|,
name|string
argument_list|,
name|options
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|setjmp
argument_list|(
name|eva
operator|.
name|catcher
argument_list|)
condition|)
comment|/* try... */
block|{
operator|*
name|result
operator|=
name|gimp_eevl_complete
argument_list|(
operator|&
name|eva
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
else|else
comment|/* catch.. */
block|{
if|if
condition|(
name|error_pos
condition|)
operator|*
name|error_pos
operator|=
name|eva
operator|.
name|start_of_current_token
expr_stmt|;
name|g_set_error_literal
argument_list|(
name|error
argument_list|,
name|GIMP_WIDGETS_ERROR
argument_list|,
name|GIMP_WIDGETS_PARSE_ERROR
argument_list|,
name|eva
operator|.
name|error_message
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_eevl_init (GimpEevl * eva,const gchar * string,const GimpEevlOptions * options)
name|gimp_eevl_init
parameter_list|(
name|GimpEevl
modifier|*
name|eva
parameter_list|,
specifier|const
name|gchar
modifier|*
name|string
parameter_list|,
specifier|const
name|GimpEevlOptions
modifier|*
name|options
parameter_list|)
block|{
name|eva
operator|->
name|string
operator|=
name|string
expr_stmt|;
name|eva
operator|->
name|options
operator|=
operator|*
name|options
expr_stmt|;
name|eva
operator|->
name|current_token
operator|.
name|type
operator|=
name|GIMP_EEVL_TOKEN_END
expr_stmt|;
name|eva
operator|->
name|error_message
operator|=
name|NULL
expr_stmt|;
comment|/* Preload symbol... */
name|gimp_eevl_lex
argument_list|(
name|eva
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GimpEevlQuantity
DECL|function|gimp_eevl_complete (GimpEevl * eva)
name|gimp_eevl_complete
parameter_list|(
name|GimpEevl
modifier|*
name|eva
parameter_list|)
block|{
name|GimpEevlQuantity
name|result
init|=
block|{
literal|0
block|,
literal|0
block|}
decl_stmt|;
name|GimpEevlQuantity
name|default_unit_factor
decl_stmt|;
comment|/* Empty expression evaluates to 0 */
if|if
condition|(
name|gimp_eevl_accept
argument_list|(
name|eva
argument_list|,
name|GIMP_EEVL_TOKEN_END
argument_list|,
name|NULL
argument_list|)
condition|)
return|return
name|result
return|;
name|result
operator|=
name|gimp_eevl_expression
argument_list|(
name|eva
argument_list|)
expr_stmt|;
comment|/* There should be nothing left to parse by now */
name|gimp_eevl_expect
argument_list|(
name|eva
argument_list|,
name|GIMP_EEVL_TOKEN_END
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|eva
operator|->
name|options
operator|.
name|unit_resolver_proc
argument_list|(
name|NULL
argument_list|,
operator|&
name|default_unit_factor
argument_list|,
name|eva
operator|->
name|options
operator|.
name|data
argument_list|)
expr_stmt|;
comment|/* Entire expression is dimensionless, apply default unit if    * applicable    */
if|if
condition|(
name|result
operator|.
name|dimension
operator|==
literal|0
operator|&&
name|default_unit_factor
operator|.
name|dimension
operator|!=
literal|0
condition|)
block|{
name|result
operator|.
name|value
operator|/=
name|default_unit_factor
operator|.
name|value
expr_stmt|;
name|result
operator|.
name|dimension
operator|=
name|default_unit_factor
operator|.
name|dimension
expr_stmt|;
block|}
return|return
name|result
return|;
block|}
end_function

begin_function
specifier|static
name|GimpEevlQuantity
DECL|function|gimp_eevl_expression (GimpEevl * eva)
name|gimp_eevl_expression
parameter_list|(
name|GimpEevl
modifier|*
name|eva
parameter_list|)
block|{
name|gboolean
name|subtract
decl_stmt|;
name|GimpEevlQuantity
name|evaluated_terms
decl_stmt|;
name|evaluated_terms
operator|=
name|gimp_eevl_term
argument_list|(
name|eva
argument_list|)
expr_stmt|;
comment|/* continue evaluating terms, chained with + or -. */
for|for
control|(
name|subtract
operator|=
name|FALSE
init|;
name|gimp_eevl_accept
argument_list|(
name|eva
argument_list|,
literal|'+'
argument_list|,
name|NULL
argument_list|)
operator|||
operator|(
name|subtract
operator|=
name|gimp_eevl_accept
argument_list|(
name|eva
argument_list|,
literal|'-'
argument_list|,
name|NULL
argument_list|)
operator|)
condition|;
name|subtract
operator|=
name|FALSE
control|)
block|{
name|GimpEevlQuantity
name|new_term
init|=
name|gimp_eevl_term
argument_list|(
name|eva
argument_list|)
decl_stmt|;
comment|/* If dimensions missmatch, attempt default unit assignment */
if|if
condition|(
name|new_term
operator|.
name|dimension
operator|!=
name|evaluated_terms
operator|.
name|dimension
condition|)
block|{
name|GimpEevlQuantity
name|default_unit_factor
decl_stmt|;
name|eva
operator|->
name|options
operator|.
name|unit_resolver_proc
argument_list|(
name|NULL
argument_list|,
operator|&
name|default_unit_factor
argument_list|,
name|eva
operator|->
name|options
operator|.
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|new_term
operator|.
name|dimension
operator|==
literal|0
operator|&&
name|evaluated_terms
operator|.
name|dimension
operator|==
name|default_unit_factor
operator|.
name|dimension
condition|)
block|{
name|new_term
operator|.
name|value
operator|/=
name|default_unit_factor
operator|.
name|value
expr_stmt|;
name|new_term
operator|.
name|dimension
operator|=
name|default_unit_factor
operator|.
name|dimension
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|evaluated_terms
operator|.
name|dimension
operator|==
literal|0
operator|&&
name|new_term
operator|.
name|dimension
operator|==
name|default_unit_factor
operator|.
name|dimension
condition|)
block|{
name|evaluated_terms
operator|.
name|value
operator|/=
name|default_unit_factor
operator|.
name|value
expr_stmt|;
name|evaluated_terms
operator|.
name|dimension
operator|=
name|default_unit_factor
operator|.
name|dimension
expr_stmt|;
block|}
else|else
block|{
name|gimp_eevl_error
argument_list|(
name|eva
argument_list|,
literal|"Dimension missmatch during addition"
argument_list|)
expr_stmt|;
block|}
block|}
name|evaluated_terms
operator|.
name|value
operator|+=
operator|(
name|subtract
condition|?
operator|-
name|new_term
operator|.
name|value
else|:
name|new_term
operator|.
name|value
operator|)
expr_stmt|;
block|}
return|return
name|evaluated_terms
return|;
block|}
end_function

begin_function
specifier|static
name|GimpEevlQuantity
DECL|function|gimp_eevl_term (GimpEevl * eva)
name|gimp_eevl_term
parameter_list|(
name|GimpEevl
modifier|*
name|eva
parameter_list|)
block|{
name|gboolean
name|division
decl_stmt|;
name|GimpEevlQuantity
name|evaluated_ratios
decl_stmt|;
name|evaluated_ratios
operator|=
name|gimp_eevl_ratio
argument_list|(
name|eva
argument_list|)
expr_stmt|;
for|for
control|(
name|division
operator|=
name|FALSE
init|;
name|gimp_eevl_accept
argument_list|(
name|eva
argument_list|,
literal|'*'
argument_list|,
name|NULL
argument_list|)
operator|||
operator|(
name|division
operator|=
name|gimp_eevl_accept
argument_list|(
name|eva
argument_list|,
literal|'/'
argument_list|,
name|NULL
argument_list|)
operator|)
condition|;
name|division
operator|=
name|FALSE
control|)
block|{
name|GimpEevlQuantity
name|new_ratio
init|=
name|gimp_eevl_ratio
argument_list|(
name|eva
argument_list|)
decl_stmt|;
if|if
condition|(
name|division
condition|)
block|{
name|evaluated_ratios
operator|.
name|value
operator|/=
name|new_ratio
operator|.
name|value
expr_stmt|;
name|evaluated_ratios
operator|.
name|dimension
operator|-=
name|new_ratio
operator|.
name|dimension
expr_stmt|;
block|}
else|else
block|{
name|evaluated_ratios
operator|.
name|value
operator|*=
name|new_ratio
operator|.
name|value
expr_stmt|;
name|evaluated_ratios
operator|.
name|dimension
operator|+=
name|new_ratio
operator|.
name|dimension
expr_stmt|;
block|}
block|}
return|return
name|evaluated_ratios
return|;
block|}
end_function

begin_function
specifier|static
name|GimpEevlQuantity
DECL|function|gimp_eevl_ratio (GimpEevl * eva)
name|gimp_eevl_ratio
parameter_list|(
name|GimpEevl
modifier|*
name|eva
parameter_list|)
block|{
name|GimpEevlQuantity
name|evaluated_signed_factors
decl_stmt|;
if|if
condition|(
operator|!
name|eva
operator|->
name|options
operator|.
name|ratio_expressions
condition|)
return|return
name|gimp_eevl_signed_factor
argument_list|(
name|eva
argument_list|)
return|;
name|evaluated_signed_factors
operator|=
name|gimp_eevl_signed_factor
argument_list|(
name|eva
argument_list|)
expr_stmt|;
while|while
condition|(
name|gimp_eevl_accept
argument_list|(
name|eva
argument_list|,
literal|':'
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|GimpEevlQuantity
name|new_signed_factor
init|=
name|gimp_eevl_signed_factor
argument_list|(
name|eva
argument_list|)
decl_stmt|;
if|if
condition|(
name|eva
operator|->
name|options
operator|.
name|ratio_invert
condition|)
block|{
name|GimpEevlQuantity
name|temp
decl_stmt|;
name|temp
operator|=
name|evaluated_signed_factors
expr_stmt|;
name|evaluated_signed_factors
operator|=
name|new_signed_factor
expr_stmt|;
name|new_signed_factor
operator|=
name|temp
expr_stmt|;
block|}
name|evaluated_signed_factors
operator|.
name|value
operator|*=
name|eva
operator|->
name|options
operator|.
name|ratio_quantity
operator|.
name|value
operator|/
name|new_signed_factor
operator|.
name|value
expr_stmt|;
name|evaluated_signed_factors
operator|.
name|dimension
operator|+=
name|eva
operator|->
name|options
operator|.
name|ratio_quantity
operator|.
name|dimension
operator|-
name|new_signed_factor
operator|.
name|dimension
expr_stmt|;
block|}
return|return
name|evaluated_signed_factors
return|;
block|}
end_function

begin_function
specifier|static
name|GimpEevlQuantity
DECL|function|gimp_eevl_signed_factor (GimpEevl * eva)
name|gimp_eevl_signed_factor
parameter_list|(
name|GimpEevl
modifier|*
name|eva
parameter_list|)
block|{
name|GimpEevlQuantity
name|result
decl_stmt|;
name|gboolean
name|negate
init|=
name|FALSE
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_eevl_accept
argument_list|(
name|eva
argument_list|,
literal|'+'
argument_list|,
name|NULL
argument_list|)
condition|)
name|negate
operator|=
name|gimp_eevl_accept
argument_list|(
name|eva
argument_list|,
literal|'-'
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|result
operator|=
name|gimp_eevl_factor
argument_list|(
name|eva
argument_list|)
expr_stmt|;
if|if
condition|(
name|negate
condition|)
name|result
operator|.
name|value
operator|=
operator|-
name|result
operator|.
name|value
expr_stmt|;
return|return
name|result
return|;
block|}
end_function

begin_function
specifier|static
name|GimpEevlQuantity
DECL|function|gimp_eevl_factor (GimpEevl * eva)
name|gimp_eevl_factor
parameter_list|(
name|GimpEevl
modifier|*
name|eva
parameter_list|)
block|{
name|GimpEevlQuantity
name|evaluated_factor
init|=
block|{
literal|0
block|,
literal|0
block|}
decl_stmt|;
name|GimpEevlToken
name|consumed_token
decl_stmt|;
if|if
condition|(
name|gimp_eevl_accept
argument_list|(
name|eva
argument_list|,
name|GIMP_EEVL_TOKEN_NUM
argument_list|,
operator|&
name|consumed_token
argument_list|)
condition|)
block|{
name|evaluated_factor
operator|.
name|value
operator|=
name|consumed_token
operator|.
name|value
operator|.
name|fl
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|gimp_eevl_accept
argument_list|(
name|eva
argument_list|,
literal|'('
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|evaluated_factor
operator|=
name|gimp_eevl_expression
argument_list|(
name|eva
argument_list|)
expr_stmt|;
name|gimp_eevl_expect
argument_list|(
name|eva
argument_list|,
literal|')'
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_eevl_error
argument_list|(
name|eva
argument_list|,
literal|"Expected number or '('"
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|eva
operator|->
name|current_token
operator|.
name|type
operator|==
name|GIMP_EEVL_TOKEN_IDENTIFIER
condition|)
block|{
name|gchar
modifier|*
name|identifier
decl_stmt|;
name|GimpEevlQuantity
name|result
decl_stmt|;
name|gimp_eevl_accept
argument_list|(
name|eva
argument_list|,
name|GIMP_EEVL_TOKEN_ANY
argument_list|,
operator|&
name|consumed_token
argument_list|)
expr_stmt|;
name|identifier
operator|=
name|g_newa
argument_list|(
name|gchar
argument_list|,
name|consumed_token
operator|.
name|value
operator|.
name|size
operator|+
literal|1
argument_list|)
expr_stmt|;
name|strncpy
argument_list|(
name|identifier
argument_list|,
name|consumed_token
operator|.
name|value
operator|.
name|c
argument_list|,
name|consumed_token
operator|.
name|value
operator|.
name|size
argument_list|)
expr_stmt|;
name|identifier
index|[
name|consumed_token
operator|.
name|value
operator|.
name|size
index|]
operator|=
literal|'\0'
expr_stmt|;
if|if
condition|(
name|eva
operator|->
name|options
operator|.
name|unit_resolver_proc
argument_list|(
name|identifier
argument_list|,
operator|&
name|result
argument_list|,
name|eva
operator|->
name|options
operator|.
name|data
argument_list|)
condition|)
block|{
name|evaluated_factor
operator|.
name|value
operator|/=
name|result
operator|.
name|value
expr_stmt|;
name|evaluated_factor
operator|.
name|dimension
operator|+=
name|result
operator|.
name|dimension
expr_stmt|;
block|}
else|else
block|{
name|gimp_eevl_error
argument_list|(
name|eva
argument_list|,
literal|"Unit was not resolved"
argument_list|)
expr_stmt|;
block|}
block|}
return|return
name|evaluated_factor
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_eevl_accept (GimpEevl * eva,GimpEevlTokenType token_type,GimpEevlToken * consumed_token)
name|gimp_eevl_accept
parameter_list|(
name|GimpEevl
modifier|*
name|eva
parameter_list|,
name|GimpEevlTokenType
name|token_type
parameter_list|,
name|GimpEevlToken
modifier|*
name|consumed_token
parameter_list|)
block|{
name|gboolean
name|existed
init|=
name|FALSE
decl_stmt|;
if|if
condition|(
name|token_type
operator|==
name|eva
operator|->
name|current_token
operator|.
name|type
operator|||
name|token_type
operator|==
name|GIMP_EEVL_TOKEN_ANY
condition|)
block|{
name|existed
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|consumed_token
condition|)
operator|*
name|consumed_token
operator|=
name|eva
operator|->
name|current_token
expr_stmt|;
comment|/* Parse next token */
name|gimp_eevl_lex
argument_list|(
name|eva
argument_list|)
expr_stmt|;
block|}
return|return
name|existed
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_eevl_lex (GimpEevl * eva)
name|gimp_eevl_lex
parameter_list|(
name|GimpEevl
modifier|*
name|eva
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|s
decl_stmt|;
name|gimp_eevl_move_past_whitespace
argument_list|(
name|eva
argument_list|)
expr_stmt|;
name|s
operator|=
name|eva
operator|->
name|string
expr_stmt|;
name|eva
operator|->
name|start_of_current_token
operator|=
name|s
expr_stmt|;
if|if
condition|(
operator|!
name|s
operator|||
name|s
index|[
literal|0
index|]
operator|==
literal|'\0'
condition|)
block|{
comment|/* We're all done */
name|eva
operator|->
name|current_token
operator|.
name|type
operator|=
name|GIMP_EEVL_TOKEN_END
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|s
index|[
literal|0
index|]
operator|==
literal|'+'
operator|||
name|s
index|[
literal|0
index|]
operator|==
literal|'-'
condition|)
block|{
comment|/* Snatch these before the g_strtod() does, otherwise they might        * be used in a numeric conversion.        */
name|gimp_eevl_lex_accept_count
argument_list|(
name|eva
argument_list|,
literal|1
argument_list|,
name|s
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* Attempt to parse a numeric value */
name|gchar
modifier|*
name|endptr
init|=
name|NULL
decl_stmt|;
name|gdouble
name|value
init|=
name|g_strtod
argument_list|(
name|s
argument_list|,
operator|&
name|endptr
argument_list|)
decl_stmt|;
if|if
condition|(
name|endptr
operator|&&
name|endptr
operator|!=
name|s
condition|)
block|{
comment|/* A numeric could be parsed, use it */
name|eva
operator|->
name|current_token
operator|.
name|value
operator|.
name|fl
operator|=
name|value
expr_stmt|;
name|gimp_eevl_lex_accept_to
argument_list|(
name|eva
argument_list|,
name|endptr
argument_list|,
name|GIMP_EEVL_TOKEN_NUM
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|gimp_eevl_unit_identifier_start
argument_list|(
name|s
index|[
literal|0
index|]
argument_list|)
condition|)
block|{
comment|/* Unit identifier */
name|eva
operator|->
name|current_token
operator|.
name|value
operator|.
name|c
operator|=
name|s
expr_stmt|;
name|eva
operator|->
name|current_token
operator|.
name|value
operator|.
name|size
operator|=
name|gimp_eevl_unit_identifier_size
argument_list|(
name|s
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_eevl_lex_accept_count
argument_list|(
name|eva
argument_list|,
name|eva
operator|->
name|current_token
operator|.
name|value
operator|.
name|size
argument_list|,
name|GIMP_EEVL_TOKEN_IDENTIFIER
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* Everything else is a single character token */
name|gimp_eevl_lex_accept_count
argument_list|(
name|eva
argument_list|,
literal|1
argument_list|,
name|s
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_eevl_lex_accept_count (GimpEevl * eva,gint count,GimpEevlTokenType token_type)
name|gimp_eevl_lex_accept_count
parameter_list|(
name|GimpEevl
modifier|*
name|eva
parameter_list|,
name|gint
name|count
parameter_list|,
name|GimpEevlTokenType
name|token_type
parameter_list|)
block|{
name|eva
operator|->
name|current_token
operator|.
name|type
operator|=
name|token_type
expr_stmt|;
name|eva
operator|->
name|string
operator|+=
name|count
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_eevl_lex_accept_to (GimpEevl * eva,gchar * to,GimpEevlTokenType token_type)
name|gimp_eevl_lex_accept_to
parameter_list|(
name|GimpEevl
modifier|*
name|eva
parameter_list|,
name|gchar
modifier|*
name|to
parameter_list|,
name|GimpEevlTokenType
name|token_type
parameter_list|)
block|{
name|eva
operator|->
name|current_token
operator|.
name|type
operator|=
name|token_type
expr_stmt|;
name|eva
operator|->
name|string
operator|=
name|to
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_eevl_move_past_whitespace (GimpEevl * eva)
name|gimp_eevl_move_past_whitespace
parameter_list|(
name|GimpEevl
modifier|*
name|eva
parameter_list|)
block|{
if|if
condition|(
operator|!
name|eva
operator|->
name|string
condition|)
return|return;
while|while
condition|(
name|g_ascii_isspace
argument_list|(
operator|*
name|eva
operator|->
name|string
argument_list|)
condition|)
name|eva
operator|->
name|string
operator|++
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_eevl_unit_identifier_start (gunichar c)
name|gimp_eevl_unit_identifier_start
parameter_list|(
name|gunichar
name|c
parameter_list|)
block|{
return|return
operator|(
name|g_unichar_isalpha
argument_list|(
name|c
argument_list|)
operator|||
name|c
operator|==
operator|(
name|gunichar
operator|)
literal|'%'
operator|||
name|c
operator|==
operator|(
name|gunichar
operator|)
literal|'\''
operator|)
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_eevl_unit_identifier_continue (gunichar c)
name|gimp_eevl_unit_identifier_continue
parameter_list|(
name|gunichar
name|c
parameter_list|)
block|{
return|return
operator|(
name|gimp_eevl_unit_identifier_start
argument_list|(
name|c
argument_list|)
operator|||
name|g_unichar_isdigit
argument_list|(
name|c
argument_list|)
operator|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_eevl_unit_identifier_size:  * @s:  * @start:  *  * Returns: Size of identifier in bytes (not including NULL  * terminator).  **/
end_comment

begin_function
specifier|static
name|gint
DECL|function|gimp_eevl_unit_identifier_size (const gchar * string,gint start_offset)
name|gimp_eevl_unit_identifier_size
parameter_list|(
specifier|const
name|gchar
modifier|*
name|string
parameter_list|,
name|gint
name|start_offset
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|start
init|=
name|g_utf8_offset_to_pointer
argument_list|(
name|string
argument_list|,
name|start_offset
argument_list|)
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|s
init|=
name|start
decl_stmt|;
name|gunichar
name|c
init|=
name|g_utf8_get_char
argument_list|(
name|s
argument_list|)
decl_stmt|;
name|gint
name|length
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|gimp_eevl_unit_identifier_start
argument_list|(
name|c
argument_list|)
condition|)
block|{
name|s
operator|=
name|g_utf8_next_char
argument_list|(
name|s
argument_list|)
expr_stmt|;
name|c
operator|=
name|g_utf8_get_char
argument_list|(
name|s
argument_list|)
expr_stmt|;
name|length
operator|++
expr_stmt|;
while|while
condition|(
name|gimp_eevl_unit_identifier_continue
argument_list|(
name|c
argument_list|)
condition|)
block|{
name|s
operator|=
name|g_utf8_next_char
argument_list|(
name|s
argument_list|)
expr_stmt|;
name|c
operator|=
name|g_utf8_get_char
argument_list|(
name|s
argument_list|)
expr_stmt|;
name|length
operator|++
expr_stmt|;
block|}
block|}
return|return
name|g_utf8_offset_to_pointer
argument_list|(
name|start
argument_list|,
name|length
argument_list|)
operator|-
name|start
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_eevl_expect (GimpEevl * eva,GimpEevlTokenType token_type,GimpEevlToken * value)
name|gimp_eevl_expect
parameter_list|(
name|GimpEevl
modifier|*
name|eva
parameter_list|,
name|GimpEevlTokenType
name|token_type
parameter_list|,
name|GimpEevlToken
modifier|*
name|value
parameter_list|)
block|{
if|if
condition|(
operator|!
name|gimp_eevl_accept
argument_list|(
name|eva
argument_list|,
name|token_type
argument_list|,
name|value
argument_list|)
condition|)
name|gimp_eevl_error
argument_list|(
name|eva
argument_list|,
literal|"Unexpected token"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_eevl_error (GimpEevl * eva,gchar * msg)
name|gimp_eevl_error
parameter_list|(
name|GimpEevl
modifier|*
name|eva
parameter_list|,
name|gchar
modifier|*
name|msg
parameter_list|)
block|{
name|eva
operator|->
name|error_message
operator|=
name|msg
expr_stmt|;
name|longjmp
argument_list|(
name|eva
operator|->
name|catcher
argument_list|,
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

