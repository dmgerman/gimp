begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * First, the stuff that ends up in the outside-world include file  = #ifdef WIN32  = #define API_EXPORT(type)    __declspec(dllexport) type __stdcall  = #else  = #define API_EXPORT(type)    type  = #endif  =  = typedef off_t regoff_t;  = typedef struct {  = 	int re_magic;  = 	size_t re_nsub;		// number of parenthesized subexpressions  = 	const char *re_endp;	// end pointer for REG_PEND  = 	struct re_guts *re_g;	// none of your business :-)  = } regex_t;  = typedef struct {  = 	regoff_t rm_so;		// start of match  = 	regoff_t rm_eo;		// end of match  = } regmatch_t;  */
end_comment

begin_comment
comment|/*  * internals of regex_t  */
end_comment

begin_define
DECL|macro|MAGIC1
define|#
directive|define
name|MAGIC1
value|((('r'^0200)<<8) | 'e')
end_define

begin_comment
comment|/*  * The internal representation is a *strip*, a sequence of  * operators ending with an endmarker.  (Some terminology etc. is a  * historical relic of earlier versions which used multiple strips.)  * Certain oddities in the representation are there to permit running  * the machinery backwards; in particular, any deviation from sequential  * flow must be marked at both its source and its destination.  Some  * fine points:  *  * - OPLUS_ and O_PLUS are *inside* the loop they create.  * - OQUEST_ and O_QUEST are *outside* the bypass they create.  * - OCH_ and O_CH are *outside* the multi-way branch they create, while  *   OOR1 and OOR2 are respectively the end and the beginning of one of  *   the branches.  Note that there is an implicit OOR2 following OCH_  *   and an implicit OOR1 preceding O_CH.  *  * In state representations, an operator's bit is on to signify a state  * immediately *preceding* "execution" of that operator.  */
end_comment

begin_typedef
DECL|typedef|sop
typedef|typedef
name|unsigned
name|long
name|sop
typedef|;
end_typedef

begin_comment
DECL|typedef|sop
comment|/* strip operator */
end_comment

begin_typedef
DECL|typedef|sopno
typedef|typedef
name|long
name|sopno
typedef|;
end_typedef

begin_define
DECL|macro|OPRMASK
define|#
directive|define
name|OPRMASK
value|0xf8000000
end_define

begin_define
DECL|macro|OPDMASK
define|#
directive|define
name|OPDMASK
value|0x07ffffff
end_define

begin_define
DECL|macro|OPSHIFT
define|#
directive|define
name|OPSHIFT
value|((unsigned)27)
end_define

begin_define
DECL|macro|OP (n)
define|#
directive|define
name|OP
parameter_list|(
name|n
parameter_list|)
value|((n)&OPRMASK)
end_define

begin_define
DECL|macro|OPND (n)
define|#
directive|define
name|OPND
parameter_list|(
name|n
parameter_list|)
value|((n)&OPDMASK)
end_define

begin_define
DECL|macro|SOP (op,opnd)
define|#
directive|define
name|SOP
parameter_list|(
name|op
parameter_list|,
name|opnd
parameter_list|)
value|((op)|(opnd))
end_define

begin_comment
comment|/* operators			   meaning	operand			*/
end_comment

begin_comment
comment|/*						(back, fwd are offsets)	*/
end_comment

begin_define
DECL|macro|OEND
define|#
directive|define
name|OEND
value|(1<<OPSHIFT)
end_define

begin_comment
DECL|macro|OEND
comment|/* endmarker	-			*/
end_comment

begin_define
DECL|macro|OCHAR
define|#
directive|define
name|OCHAR
value|(2<<OPSHIFT)
end_define

begin_comment
DECL|macro|OCHAR
comment|/* character	unsigned char		*/
end_comment

begin_define
DECL|macro|OBOL
define|#
directive|define
name|OBOL
value|(3<<OPSHIFT)
end_define

begin_comment
DECL|macro|OBOL
comment|/* left anchor	-			*/
end_comment

begin_define
DECL|macro|OEOL
define|#
directive|define
name|OEOL
value|(4<<OPSHIFT)
end_define

begin_comment
DECL|macro|OEOL
comment|/* right anchor	-			*/
end_comment

begin_define
DECL|macro|OANY
define|#
directive|define
name|OANY
value|(5<<OPSHIFT)
end_define

begin_comment
DECL|macro|OANY
comment|/* .		-			*/
end_comment

begin_define
DECL|macro|OANYOF
define|#
directive|define
name|OANYOF
value|(6<<OPSHIFT)
end_define

begin_comment
DECL|macro|OANYOF
comment|/* [...]	set number		*/
end_comment

begin_define
DECL|macro|OBACK_
define|#
directive|define
name|OBACK_
value|(7<<OPSHIFT)
end_define

begin_comment
DECL|macro|OBACK_
comment|/* begin \d	paren number		*/
end_comment

begin_define
DECL|macro|O_BACK
define|#
directive|define
name|O_BACK
value|(8<<OPSHIFT)
end_define

begin_comment
DECL|macro|O_BACK
comment|/* end \d	paren number		*/
end_comment

begin_define
DECL|macro|OPLUS_
define|#
directive|define
name|OPLUS_
value|(9<<OPSHIFT)
end_define

begin_comment
DECL|macro|OPLUS_
comment|/* + prefix	fwd to suffix		*/
end_comment

begin_define
DECL|macro|O_PLUS
define|#
directive|define
name|O_PLUS
value|(10<<OPSHIFT)
end_define

begin_comment
DECL|macro|O_PLUS
comment|/* + suffix	back to prefix		*/
end_comment

begin_define
DECL|macro|OQUEST_
define|#
directive|define
name|OQUEST_
value|(11<<OPSHIFT)
end_define

begin_comment
DECL|macro|OQUEST_
comment|/* ? prefix	fwd to suffix		*/
end_comment

begin_define
DECL|macro|O_QUEST
define|#
directive|define
name|O_QUEST
value|(12<<OPSHIFT)
end_define

begin_comment
DECL|macro|O_QUEST
comment|/* ? suffix	back to prefix		*/
end_comment

begin_define
DECL|macro|OLPAREN
define|#
directive|define
name|OLPAREN
value|(13<<OPSHIFT)
end_define

begin_comment
DECL|macro|OLPAREN
comment|/* (		fwd to )		*/
end_comment

begin_define
DECL|macro|ORPAREN
define|#
directive|define
name|ORPAREN
value|(14<<OPSHIFT)
end_define

begin_comment
DECL|macro|ORPAREN
comment|/* )		back to (		*/
end_comment

begin_define
DECL|macro|OCH_
define|#
directive|define
name|OCH_
value|(15<<OPSHIFT)
end_define

begin_comment
DECL|macro|OCH_
comment|/* begin choice	fwd to OOR2		*/
end_comment

begin_define
DECL|macro|OOR1
define|#
directive|define
name|OOR1
value|(16u<<OPSHIFT)
end_define

begin_comment
DECL|macro|OOR1
comment|/* | pt. 1	back to OOR1 or OCH_	*/
end_comment

begin_define
DECL|macro|OOR2
define|#
directive|define
name|OOR2
value|(17u<<OPSHIFT)
end_define

begin_comment
DECL|macro|OOR2
comment|/* | pt. 2	fwd to OOR2 or O_CH	*/
end_comment

begin_define
DECL|macro|O_CH
define|#
directive|define
name|O_CH
value|(18u<<OPSHIFT)
end_define

begin_comment
DECL|macro|O_CH
comment|/* end choice	back to OOR1		*/
end_comment

begin_define
DECL|macro|OBOW
define|#
directive|define
name|OBOW
value|(19u<<OPSHIFT)
end_define

begin_comment
DECL|macro|OBOW
comment|/* begin word	-			*/
end_comment

begin_define
DECL|macro|OEOW
define|#
directive|define
name|OEOW
value|(20u<<OPSHIFT)
end_define

begin_comment
DECL|macro|OEOW
comment|/* end word	-			*/
end_comment

begin_comment
comment|/*  * Structure for [] character-set representation.  Character sets are  * done as bit vectors, grouped 8 to a byte vector for compactness.  * The individual set therefore has both a pointer to the byte vector  * and a mask to pick out the relevant bit of each byte.  A hash code  * simplifies testing whether two sets could be identical.  *  * This will get trickier for multicharacter collating elements.  As  * preliminary hooks for dealing with such things, we also carry along  * a string of multi-character elements, and decide the size of the  * vectors at run time.  */
end_comment

begin_typedef
DECL|struct|__anon2c7557090108
typedef|typedef
struct|struct
block|{
DECL|member|ptr
name|uch
modifier|*
name|ptr
decl_stmt|;
comment|/* -> uch [csetsize] */
DECL|member|mask
name|uch
name|mask
decl_stmt|;
comment|/* bit within array */
DECL|member|hash
name|uch
name|hash
decl_stmt|;
comment|/* hash code */
DECL|member|smultis
name|size_t
name|smultis
decl_stmt|;
DECL|member|multis
name|char
modifier|*
name|multis
decl_stmt|;
comment|/* -> char[smulti]  ab\0cd\0ef\0\0 */
DECL|typedef|cset
block|}
name|cset
typedef|;
end_typedef

begin_comment
comment|/* note that CHadd and CHsub are unsafe, and CHIN doesn't yield 0/1 */
end_comment

begin_define
DECL|macro|CHadd (cs,c)
define|#
directive|define
name|CHadd
parameter_list|(
name|cs
parameter_list|,
name|c
parameter_list|)
value|((cs)->ptr[(uch)(c)] |= (cs)->mask, (cs)->hash += (c))
end_define

begin_define
DECL|macro|CHsub (cs,c)
define|#
directive|define
name|CHsub
parameter_list|(
name|cs
parameter_list|,
name|c
parameter_list|)
value|((cs)->ptr[(uch)(c)]&= ~(cs)->mask, (cs)->hash -= (c))
end_define

begin_define
DECL|macro|CHIN (cs,c)
define|#
directive|define
name|CHIN
parameter_list|(
name|cs
parameter_list|,
name|c
parameter_list|)
value|((cs)->ptr[(uch)(c)]& (cs)->mask)
end_define

begin_define
DECL|macro|MCadd (p,cs,cp)
define|#
directive|define
name|MCadd
parameter_list|(
name|p
parameter_list|,
name|cs
parameter_list|,
name|cp
parameter_list|)
value|mcadd(p, cs, cp)
end_define

begin_comment
DECL|macro|MCadd (p,cs,cp)
comment|/* regcomp() internal fns */
end_comment

begin_comment
comment|/* stuff for character categories */
end_comment

begin_typedef
DECL|typedef|cat_t
typedef|typedef
name|unsigned
name|char
name|cat_t
typedef|;
end_typedef

begin_comment
comment|/*  * main compiled-expression structure  */
end_comment

begin_struct
DECL|struct|re_guts
struct|struct
name|re_guts
block|{
DECL|member|magic
name|int
name|magic
decl_stmt|;
DECL|macro|MAGIC2
define|#
directive|define
name|MAGIC2
value|((('R'^0200)<<8)|'E')
DECL|member|strip
name|sop
modifier|*
name|strip
decl_stmt|;
comment|/* malloced area for strip */
DECL|member|csetsize
name|int
name|csetsize
decl_stmt|;
comment|/* number of bits in a cset vector */
DECL|member|ncsets
name|int
name|ncsets
decl_stmt|;
comment|/* number of csets in use */
DECL|member|sets
name|cset
modifier|*
name|sets
decl_stmt|;
comment|/* -> cset [ncsets] */
DECL|member|setbits
name|uch
modifier|*
name|setbits
decl_stmt|;
comment|/* -> uch[csetsize][ncsets/CHAR_BIT] */
DECL|member|cflags
name|int
name|cflags
decl_stmt|;
comment|/* copy of regcomp() cflags argument */
DECL|member|nstates
name|sopno
name|nstates
decl_stmt|;
comment|/* = number of sops */
DECL|member|firststate
name|sopno
name|firststate
decl_stmt|;
comment|/* the initial OEND (normally 0) */
DECL|member|laststate
name|sopno
name|laststate
decl_stmt|;
comment|/* the final OEND */
DECL|member|iflags
name|int
name|iflags
decl_stmt|;
comment|/* internal flags */
DECL|macro|USEBOL
define|#
directive|define
name|USEBOL
value|01
comment|/* used ^ */
DECL|macro|USEEOL
define|#
directive|define
name|USEEOL
value|02
comment|/* used $ */
DECL|macro|BAD
define|#
directive|define
name|BAD
value|04
comment|/* something wrong */
DECL|member|nbol
name|int
name|nbol
decl_stmt|;
comment|/* number of ^ used */
DECL|member|neol
name|int
name|neol
decl_stmt|;
comment|/* number of $ used */
DECL|member|ncategories
name|int
name|ncategories
decl_stmt|;
comment|/* how many character categories */
DECL|member|categories
name|cat_t
modifier|*
name|categories
decl_stmt|;
comment|/* ->catspace[-CHAR_MIN] */
DECL|member|must
name|char
modifier|*
name|must
decl_stmt|;
comment|/* match must contain this string */
DECL|member|mlen
name|int
name|mlen
decl_stmt|;
comment|/* length of must */
DECL|member|nsub
name|size_t
name|nsub
decl_stmt|;
comment|/* copy of re_nsub */
DECL|member|backrefs
name|int
name|backrefs
decl_stmt|;
comment|/* does it use back references? */
DECL|member|nplus
name|sopno
name|nplus
decl_stmt|;
comment|/* how deep does it nest +s? */
comment|/* catspace must be last */
DECL|member|catspace
name|cat_t
name|catspace
index|[
literal|1
index|]
decl_stmt|;
comment|/* actually [NC] */
block|}
struct|;
end_struct

begin_comment
comment|/* misc utilities */
end_comment

begin_define
DECL|macro|OUT
define|#
directive|define
name|OUT
value|(CHAR_MAX+1)
end_define

begin_comment
DECL|macro|OUT
comment|/* a non-character value */
end_comment

begin_define
DECL|macro|ISWORD (c)
define|#
directive|define
name|ISWORD
parameter_list|(
name|c
parameter_list|)
value|(isalnum(c) || (c) == '_')
end_define

end_unit

