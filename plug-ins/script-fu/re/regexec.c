begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * the outer shell of regexec()  *  * This file includes engine.c *twice*, after muchos fiddling with the  * macros that code uses.  This lets the same code operate on two different  * representations for state sets.  */
end_comment

begin_include
include|#
directive|include
file|"regex.h"
end_include

begin_include
include|#
directive|include
file|"utils.h"
end_include

begin_include
include|#
directive|include
file|"regex2.h"
end_include

begin_ifndef
ifndef|#
directive|ifndef
name|NDEBUG
end_ifndef

begin_decl_stmt
DECL|variable|nope
specifier|static
name|int
name|nope
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_comment
DECL|variable|nope
comment|/* for use in asserts; shuts lint up */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* macros for manipulating states, small version */
end_comment

begin_define
DECL|macro|states
define|#
directive|define
name|states
value|long
end_define

begin_define
DECL|macro|states1
define|#
directive|define
name|states1
value|states
end_define

begin_comment
DECL|macro|states1
comment|/* for later use in regexec() decision */
end_comment

begin_define
DECL|macro|CLEAR (v)
define|#
directive|define
name|CLEAR
parameter_list|(
name|v
parameter_list|)
value|((v) = 0)
end_define

begin_define
DECL|macro|SET0 (v,n)
define|#
directive|define
name|SET0
parameter_list|(
name|v
parameter_list|,
name|n
parameter_list|)
value|((v)&= ~(1<< (n)))
end_define

begin_define
DECL|macro|SET1 (v,n)
define|#
directive|define
name|SET1
parameter_list|(
name|v
parameter_list|,
name|n
parameter_list|)
value|((v) |= 1<< (n))
end_define

begin_define
DECL|macro|ISSET (v,n)
define|#
directive|define
name|ISSET
parameter_list|(
name|v
parameter_list|,
name|n
parameter_list|)
value|((v)& (1<< (n)))
end_define

begin_define
DECL|macro|ASSIGN (d,s)
define|#
directive|define
name|ASSIGN
parameter_list|(
name|d
parameter_list|,
name|s
parameter_list|)
value|((d) = (s))
end_define

begin_define
DECL|macro|EQ (a,b)
define|#
directive|define
name|EQ
parameter_list|(
name|a
parameter_list|,
name|b
parameter_list|)
value|((a) == (b))
end_define

begin_define
DECL|macro|STATEVARS
define|#
directive|define
name|STATEVARS
value|int dummy
end_define

begin_comment
DECL|macro|STATEVARS
comment|/* dummy version */
end_comment

begin_define
DECL|macro|STATESETUP (m,n)
define|#
directive|define
name|STATESETUP
parameter_list|(
name|m
parameter_list|,
name|n
parameter_list|)
end_define

begin_comment
DECL|macro|STATESETUP (m,n)
comment|/* nothing */
end_comment

begin_define
DECL|macro|STATETEARDOWN (m)
define|#
directive|define
name|STATETEARDOWN
parameter_list|(
name|m
parameter_list|)
end_define

begin_comment
DECL|macro|STATETEARDOWN (m)
comment|/* nothing */
end_comment

begin_define
DECL|macro|SETUP (v)
define|#
directive|define
name|SETUP
parameter_list|(
name|v
parameter_list|)
value|((v) = 0)
end_define

begin_define
DECL|macro|onestate
define|#
directive|define
name|onestate
value|int
end_define

begin_define
DECL|macro|INIT (o,n)
define|#
directive|define
name|INIT
parameter_list|(
name|o
parameter_list|,
name|n
parameter_list|)
value|((o) = (unsigned)1<< (n))
end_define

begin_define
DECL|macro|INC (o)
define|#
directive|define
name|INC
parameter_list|(
name|o
parameter_list|)
value|((o)<<= 1)
end_define

begin_define
DECL|macro|ISSTATEIN (v,o)
define|#
directive|define
name|ISSTATEIN
parameter_list|(
name|v
parameter_list|,
name|o
parameter_list|)
value|((v)& (o))
end_define

begin_comment
comment|/* some abbreviations; note that some of these know variable names! */
end_comment

begin_comment
comment|/* do "if I'm here, I can also be there" etc without branches */
end_comment

begin_define
DECL|macro|FWD (dst,src,n)
define|#
directive|define
name|FWD
parameter_list|(
name|dst
parameter_list|,
name|src
parameter_list|,
name|n
parameter_list|)
value|((dst) |= ((unsigned)(src)&(here))<< (n))
end_define

begin_define
DECL|macro|BACK (dst,src,n)
define|#
directive|define
name|BACK
parameter_list|(
name|dst
parameter_list|,
name|src
parameter_list|,
name|n
parameter_list|)
value|((dst) |= ((unsigned)(src)&(here))>> (n))
end_define

begin_define
DECL|macro|ISSETBACK (v,n)
define|#
directive|define
name|ISSETBACK
parameter_list|(
name|v
parameter_list|,
name|n
parameter_list|)
value|((v)& ((unsigned)here>> (n)))
end_define

begin_comment
comment|/* function names */
end_comment

begin_define
DECL|macro|SNAMES
define|#
directive|define
name|SNAMES
end_define

begin_comment
DECL|macro|SNAMES
comment|/* engine.c looks after details */
end_comment

begin_include
include|#
directive|include
file|"engine.c"
end_include

begin_comment
comment|/* now undo things */
end_comment

begin_undef
undef|#
directive|undef
name|states
end_undef

begin_undef
undef|#
directive|undef
name|CLEAR
end_undef

begin_undef
undef|#
directive|undef
name|SET0
end_undef

begin_undef
undef|#
directive|undef
name|SET1
end_undef

begin_undef
undef|#
directive|undef
name|ISSET
end_undef

begin_undef
undef|#
directive|undef
name|ASSIGN
end_undef

begin_undef
undef|#
directive|undef
name|EQ
end_undef

begin_undef
undef|#
directive|undef
name|STATEVARS
end_undef

begin_undef
undef|#
directive|undef
name|STATESETUP
end_undef

begin_undef
undef|#
directive|undef
name|STATETEARDOWN
end_undef

begin_undef
undef|#
directive|undef
name|SETUP
end_undef

begin_undef
undef|#
directive|undef
name|onestate
end_undef

begin_undef
undef|#
directive|undef
name|INIT
end_undef

begin_undef
undef|#
directive|undef
name|INC
end_undef

begin_undef
undef|#
directive|undef
name|ISSTATEIN
end_undef

begin_undef
undef|#
directive|undef
name|FWD
end_undef

begin_undef
undef|#
directive|undef
name|BACK
end_undef

begin_undef
undef|#
directive|undef
name|ISSETBACK
end_undef

begin_undef
undef|#
directive|undef
name|SNAMES
end_undef

begin_comment
comment|/* macros for manipulating states, large version */
end_comment

begin_define
DECL|macro|states
define|#
directive|define
name|states
value|char *
end_define

begin_define
DECL|macro|CLEAR (v)
define|#
directive|define
name|CLEAR
parameter_list|(
name|v
parameter_list|)
value|memset(v, 0, m->g->nstates)
end_define

begin_define
DECL|macro|SET0 (v,n)
define|#
directive|define
name|SET0
parameter_list|(
name|v
parameter_list|,
name|n
parameter_list|)
value|((v)[n] = 0)
end_define

begin_define
DECL|macro|SET1 (v,n)
define|#
directive|define
name|SET1
parameter_list|(
name|v
parameter_list|,
name|n
parameter_list|)
value|((v)[n] = 1)
end_define

begin_define
DECL|macro|ISSET (v,n)
define|#
directive|define
name|ISSET
parameter_list|(
name|v
parameter_list|,
name|n
parameter_list|)
value|((v)[n])
end_define

begin_define
DECL|macro|ASSIGN (d,s)
define|#
directive|define
name|ASSIGN
parameter_list|(
name|d
parameter_list|,
name|s
parameter_list|)
value|memcpy(d, s, m->g->nstates)
end_define

begin_define
DECL|macro|EQ (a,b)
define|#
directive|define
name|EQ
parameter_list|(
name|a
parameter_list|,
name|b
parameter_list|)
value|(memcmp(a, b, m->g->nstates) == 0)
end_define

begin_define
DECL|macro|STATEVARS
define|#
directive|define
name|STATEVARS
value|int vn; char *space
end_define

begin_define
DECL|macro|STATESETUP (m,nv)
define|#
directive|define
name|STATESETUP
parameter_list|(
name|m
parameter_list|,
name|nv
parameter_list|)
value|{ (m)->space = malloc((nv)*(m)->g->nstates); \                     if ((m)->space == NULL) return(REG_ESPACE); \                     (m)->vn = 0; }
end_define

begin_define
DECL|macro|STATETEARDOWN (m)
define|#
directive|define
name|STATETEARDOWN
parameter_list|(
name|m
parameter_list|)
value|{ free((m)->space); }
end_define

begin_define
DECL|macro|SETUP (v)
define|#
directive|define
name|SETUP
parameter_list|(
name|v
parameter_list|)
value|((v) =&m->space[m->vn++ * m->g->nstates])
end_define

begin_define
DECL|macro|onestate
define|#
directive|define
name|onestate
value|int
end_define

begin_define
DECL|macro|INIT (o,n)
define|#
directive|define
name|INIT
parameter_list|(
name|o
parameter_list|,
name|n
parameter_list|)
value|((o) = (n))
end_define

begin_define
DECL|macro|INC (o)
define|#
directive|define
name|INC
parameter_list|(
name|o
parameter_list|)
value|((o)++)
end_define

begin_define
DECL|macro|ISSTATEIN (v,o)
define|#
directive|define
name|ISSTATEIN
parameter_list|(
name|v
parameter_list|,
name|o
parameter_list|)
value|((v)[o])
end_define

begin_comment
comment|/* some abbreviations; note that some of these know variable names! */
end_comment

begin_comment
comment|/* do "if I'm here, I can also be there" etc without branches */
end_comment

begin_define
DECL|macro|FWD (dst,src,n)
define|#
directive|define
name|FWD
parameter_list|(
name|dst
parameter_list|,
name|src
parameter_list|,
name|n
parameter_list|)
value|((dst)[here+(n)] |= (src)[here])
end_define

begin_define
DECL|macro|BACK (dst,src,n)
define|#
directive|define
name|BACK
parameter_list|(
name|dst
parameter_list|,
name|src
parameter_list|,
name|n
parameter_list|)
value|((dst)[here-(n)] |= (src)[here])
end_define

begin_define
DECL|macro|ISSETBACK (v,n)
define|#
directive|define
name|ISSETBACK
parameter_list|(
name|v
parameter_list|,
name|n
parameter_list|)
value|((v)[here - (n)])
end_define

begin_comment
comment|/* function names */
end_comment

begin_define
DECL|macro|LNAMES
define|#
directive|define
name|LNAMES
end_define

begin_comment
DECL|macro|LNAMES
comment|/* flag */
end_comment

begin_include
include|#
directive|include
file|"engine.c"
end_include

begin_comment
comment|/*  - regexec - interface for matching  = API_EXPORT(int) regexec(const regex_t *, const char *, size_t, \  =                       regmatch_t [], int);  = #define     REG_NOTBOL     00001  = #define     REG_NOTEOL     00002  = #define     REG_STARTEND   00004  = #define     REG_TRACE 00400     // tracing of execution  = #define     REG_LARGE 01000     // force large representation  = #define     REG_BACKR 02000     // force use of backref code  *  * We put this here so we can exploit knowledge of the state representation  * when choosing which matcher to call.  Also, by this point the matchers  * have been prototyped.  */
end_comment

begin_macro
name|API_EXPORT
argument_list|(
argument|int
argument_list|)
end_macro

begin_comment
comment|/* 0 success, REG_NOMATCH failure */
end_comment

begin_macro
name|regexec
argument_list|(
argument|preg
argument_list|,
argument|string
argument_list|,
argument|nmatch
argument_list|,
argument|pmatch
argument_list|,
argument|eflags
argument_list|)
end_macro

begin_decl_stmt
specifier|const
name|regex_t
modifier|*
name|preg
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|string
specifier|const
name|char
modifier|*
name|string
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|nmatch
name|size_t
name|nmatch
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|pmatch
name|regmatch_t
name|pmatch
index|[]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|eflags
name|int
name|eflags
decl_stmt|;
end_decl_stmt

begin_block
block|{
DECL|variable|g
specifier|register
name|struct
name|re_guts
modifier|*
name|g
init|=
name|preg
operator|->
name|re_g
decl_stmt|;
ifdef|#
directive|ifdef
name|REDEBUG
DECL|macro|GOODFLAGS (f)
define|#
directive|define
name|GOODFLAGS
parameter_list|(
name|f
parameter_list|)
value|(f)
else|#
directive|else
DECL|macro|GOODFLAGS (f)
define|#
directive|define
name|GOODFLAGS
parameter_list|(
name|f
parameter_list|)
value|((f)&(REG_NOTBOL|REG_NOTEOL|REG_STARTEND))
endif|#
directive|endif
if|if
condition|(
name|preg
operator|->
name|re_magic
operator|!=
name|MAGIC1
operator|||
name|g
operator|->
name|magic
operator|!=
name|MAGIC2
condition|)
return|return
operator|(
name|REG_BADPAT
operator|)
return|;
name|assert
argument_list|(
operator|!
operator|(
name|g
operator|->
name|iflags
operator|&
name|BAD
operator|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|g
operator|->
name|iflags
operator|&
name|BAD
condition|)
comment|/* backstop for no-debug case */
return|return
operator|(
name|REG_BADPAT
operator|)
return|;
name|eflags
operator|=
name|GOODFLAGS
argument_list|(
name|eflags
argument_list|)
expr_stmt|;
if|if
condition|(
name|g
operator|->
name|nstates
operator|<=
name|CHAR_BIT
operator|*
sizeof|sizeof
argument_list|(
name|states1
argument_list|)
operator|&&
operator|!
operator|(
name|eflags
operator|&
name|REG_LARGE
operator|)
condition|)
return|return
operator|(
name|smatcher
argument_list|(
name|g
argument_list|,
operator|(
name|char
operator|*
operator|)
name|string
argument_list|,
name|nmatch
argument_list|,
name|pmatch
argument_list|,
name|eflags
argument_list|)
operator|)
return|;
else|else
return|return
operator|(
name|lmatcher
argument_list|(
name|g
argument_list|,
operator|(
name|char
operator|*
operator|)
name|string
argument_list|,
name|nmatch
argument_list|,
name|pmatch
argument_list|,
name|eflags
argument_list|)
operator|)
return|;
block|}
end_block

end_unit

