begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* re.c */
end_comment

begin_comment
comment|/* Henry Spencer's implementation of Regular Expressions,    used for TinyScheme */
end_comment

begin_comment
comment|/* Refurbished by Stephen Gildea */
end_comment

begin_include
include|#
directive|include
file|"regex.h"
end_include

begin_include
include|#
directive|include
file|"tinyscheme/scheme-private.h"
end_include

begin_if
if|#
directive|if
name|defined
argument_list|(
name|_WIN32
argument_list|)
end_if

begin_define
DECL|macro|EXPORT
define|#
directive|define
name|EXPORT
value|__declspec( dllexport )
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|EXPORT
define|#
directive|define
name|EXPORT
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* Since not exported */
end_comment

begin_define
DECL|macro|T_STRING
define|#
directive|define
name|T_STRING
value|1
end_define

begin_function
DECL|function|set_vector_elem (pointer vec,int ielem,pointer newel)
specifier|static
name|void
name|set_vector_elem
parameter_list|(
name|pointer
name|vec
parameter_list|,
name|int
name|ielem
parameter_list|,
name|pointer
name|newel
parameter_list|)
block|{
name|int
name|n
init|=
name|ielem
operator|/
literal|2
decl_stmt|;
if|if
condition|(
name|ielem
operator|%
literal|2
operator|==
literal|0
condition|)
block|{
name|vec
index|[
literal|1
operator|+
name|n
index|]
operator|.
name|_object
operator|.
name|_cons
operator|.
name|_car
operator|=
name|newel
expr_stmt|;
block|}
else|else
block|{
name|vec
index|[
literal|1
operator|+
name|n
index|]
operator|.
name|_object
operator|.
name|_cons
operator|.
name|_cdr
operator|=
name|newel
expr_stmt|;
block|}
block|}
end_function

begin_function
DECL|function|foreign_re_match (scheme * sc,pointer args)
name|pointer
name|foreign_re_match
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
name|pointer
name|args
parameter_list|)
block|{
name|pointer
name|retval
init|=
name|sc
operator|->
name|F
decl_stmt|;
name|int
name|retcode
decl_stmt|;
name|regex_t
name|rt
decl_stmt|;
name|pointer
name|first_arg
decl_stmt|,
name|second_arg
decl_stmt|;
name|pointer
name|third_arg
init|=
name|sc
operator|->
name|NIL
decl_stmt|;
name|char
modifier|*
name|string
decl_stmt|;
name|char
modifier|*
name|pattern
decl_stmt|;
name|int
name|num
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
operator|(
operator|(
name|args
operator|!=
name|sc
operator|->
name|NIL
operator|)
operator|&&
name|sc
operator|->
name|vptr
operator|->
name|is_string
argument_list|(
operator|(
name|first_arg
operator|=
name|sc
operator|->
name|vptr
operator|->
name|pair_car
argument_list|(
name|args
argument_list|)
operator|)
argument_list|)
operator|&&
operator|(
name|args
operator|=
name|sc
operator|->
name|vptr
operator|->
name|pair_cdr
argument_list|(
name|args
argument_list|)
operator|)
operator|&&
name|sc
operator|->
name|vptr
operator|->
name|is_pair
argument_list|(
name|args
argument_list|)
operator|&&
name|sc
operator|->
name|vptr
operator|->
name|is_string
argument_list|(
operator|(
name|second_arg
operator|=
name|sc
operator|->
name|vptr
operator|->
name|pair_car
argument_list|(
name|args
argument_list|)
operator|)
argument_list|)
operator|)
condition|)
block|{
return|return
name|sc
operator|->
name|F
return|;
block|}
name|pattern
operator|=
name|sc
operator|->
name|vptr
operator|->
name|string_value
argument_list|(
name|first_arg
argument_list|)
expr_stmt|;
name|string
operator|=
name|sc
operator|->
name|vptr
operator|->
name|string_value
argument_list|(
name|second_arg
argument_list|)
expr_stmt|;
name|args
operator|=
name|sc
operator|->
name|vptr
operator|->
name|pair_cdr
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|args
operator|!=
name|sc
operator|->
name|NIL
condition|)
block|{
if|if
condition|(
operator|!
operator|(
name|sc
operator|->
name|vptr
operator|->
name|is_pair
argument_list|(
name|args
argument_list|)
operator|&&
name|sc
operator|->
name|vptr
operator|->
name|is_vector
argument_list|(
operator|(
name|third_arg
operator|=
name|sc
operator|->
name|vptr
operator|->
name|pair_car
argument_list|(
name|args
argument_list|)
operator|)
argument_list|)
operator|)
condition|)
block|{
return|return
name|sc
operator|->
name|F
return|;
block|}
else|else
block|{
name|num
operator|=
name|third_arg
operator|->
name|_object
operator|.
name|_number
operator|.
name|value
operator|.
name|ivalue
expr_stmt|;
block|}
block|}
if|if
condition|(
name|regcomp
argument_list|(
operator|&
name|rt
argument_list|,
name|pattern
argument_list|,
name|REG_EXTENDED
argument_list|)
operator|!=
literal|0
condition|)
block|{
return|return
name|sc
operator|->
name|F
return|;
block|}
if|if
condition|(
name|num
operator|==
literal|0
condition|)
block|{
name|retcode
operator|=
name|regexec
argument_list|(
operator|&
name|rt
argument_list|,
name|string
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|regmatch_t
modifier|*
name|pmatch
init|=
name|malloc
argument_list|(
operator|(
name|num
operator|+
literal|1
operator|)
operator|*
sizeof|sizeof
argument_list|(
name|regmatch_t
argument_list|)
argument_list|)
decl_stmt|;
if|if
condition|(
name|pmatch
operator|!=
literal|0
condition|)
block|{
name|retcode
operator|=
name|regexec
argument_list|(
operator|&
name|rt
argument_list|,
name|string
argument_list|,
name|num
operator|+
literal|1
argument_list|,
name|pmatch
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|retcode
operator|==
literal|0
condition|)
block|{
name|int
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|num
condition|;
name|i
operator|++
control|)
block|{
undef|#
directive|undef
name|cons
name|set_vector_elem
argument_list|(
name|third_arg
argument_list|,
name|i
argument_list|,
name|sc
operator|->
name|vptr
operator|->
name|cons
argument_list|(
name|sc
argument_list|,
name|sc
operator|->
name|vptr
operator|->
name|mk_integer
argument_list|(
name|sc
argument_list|,
name|pmatch
index|[
name|i
index|]
operator|.
name|rm_so
argument_list|)
argument_list|,
name|sc
operator|->
name|vptr
operator|->
name|mk_integer
argument_list|(
name|sc
argument_list|,
name|pmatch
index|[
name|i
index|]
operator|.
name|rm_eo
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
name|free
argument_list|(
name|pmatch
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|sc
operator|->
name|no_memory
operator|=
literal|1
expr_stmt|;
name|retcode
operator|=
operator|-
literal|1
expr_stmt|;
block|}
block|}
if|if
condition|(
name|retcode
operator|==
literal|0
condition|)
block|{
name|retval
operator|=
name|sc
operator|->
name|T
expr_stmt|;
block|}
name|regfree
argument_list|(
operator|&
name|rt
argument_list|)
expr_stmt|;
return|return
operator|(
name|retval
operator|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|utilities
specifier|static
name|char
modifier|*
name|utilities
init|=
literal|";; return the substring of STRING matched in MATCH-VECTOR, \n"
literal|";; the Nth subexpression match (default 0).\n"
literal|"(define (re-match-nth string match-vector . n)\n"
literal|"  (let ((n (if (pair? n) (car n) 0)))\n"
literal|"    (substring string (car (vector-ref match-vector n))\n"
literal|"                    (cdr (vector-ref match-vector n)))))\n"
literal|"(define (re-before-nth string match-vector . n)\n"
literal|"  (let ((n (if (pair? n) (car n) 0)))\n"
literal|"    (substring string 0 (car (vector-ref match-vector n)))))\n"
literal|"(define (re-after-nth string match-vector . n)\n"
literal|"  (let ((n (if (pair? n) (car n) 0)))\n"
literal|"    (substring string (cdr (vector-ref match-vector n))\n"
literal|"             (string-length string))))\n"
decl_stmt|;
end_decl_stmt

begin_function
DECL|function|init_re (scheme * sc)
name|EXPORT
name|void
name|init_re
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|)
block|{
name|sc
operator|->
name|vptr
operator|->
name|scheme_define
argument_list|(
name|sc
argument_list|,
name|sc
operator|->
name|global_env
argument_list|,
name|sc
operator|->
name|vptr
operator|->
name|mk_symbol
argument_list|(
name|sc
argument_list|,
literal|"re-match"
argument_list|)
argument_list|,
name|sc
operator|->
name|vptr
operator|->
name|mk_foreign_func
argument_list|(
name|sc
argument_list|,
name|foreign_re_match
argument_list|)
argument_list|)
expr_stmt|;
comment|/*    sc->vptr->load_string(sc,utilities);*/
block|}
end_function

end_unit

