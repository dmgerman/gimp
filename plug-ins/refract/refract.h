begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* refract.h, 1/2/98  * refract: a plug-in for the GIMP 0.99  * By Kevin Turner<kevint@poboxes.com>  * http://www.poboxes.com/kevint/gimp/refract.html  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|REFRACT_DEBUG
end_ifndef

begin_warning
warning|#
directive|warning
literal|"REFRACT_DEBUG flag is Off."
end_warning

begin_define
DECL|macro|REFRACT_TITLE
define|#
directive|define
name|REFRACT_TITLE
value|"Refract 1/2/98-Beta"
end_define

begin_else
else|#
directive|else
end_else

begin_warning
warning|#
directive|warning
literal|"REFRACT_DEBUG flag is On."
end_warning

begin_define
DECL|macro|REFRACT_TITLE
define|#
directive|define
name|REFRACT_TITLE
value|"Refract 1/2/98 (debug)"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* Update the progress bar every this-many rows...  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|PROGRESS_ROWS
end_ifndef

begin_define
DECL|macro|PROGRESS_ROWS
define|#
directive|define
name|PROGRESS_ROWS
value|8
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* Realistically, this number should be 1.0.  An index of refraction    of less than 1 means the speed of light in that substance is    *faster* than in a vacuum!  But hey, it's GIMP, when was the last    time we payed any attention to reality?  Go ahead...  Add    "subspace" to the list of materials... */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|INDEX_SCALE_MIN
end_ifndef

begin_define
DECL|macro|INDEX_SCALE_MIN
define|#
directive|define
name|INDEX_SCALE_MIN
value|0.0
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* This can be whatever is convient.  However, I don't know of any    substances (even artifically generated ones) that have an index of    refraction higher than 4.7 or so...*/
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|INDEX_SCALE_MAX
end_ifndef

begin_define
DECL|macro|INDEX_SCALE_MAX
define|#
directive|define
name|INDEX_SCALE_MAX
value|5.0
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* For now, our height maps only have one byte per pixel, so guchar    should be sufficient.  May need to change in future versions of    GIMP when it supports greater pixel depth.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|HEIGHT_TYPE
end_ifndef

begin_define
DECL|macro|HEIGHT_TYPE
define|#
directive|define
name|HEIGHT_TYPE
value|guchar
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* Should we rely more on macros or functions? */
end_comment

begin_comment
comment|/* #define OLD_SLOPE_MACROS */
end_comment

begin_include
include|#
directive|include
file|"gtk/gtk.h"
end_include

begin_typedef
DECL|struct|__anon29f2052f0108
typedef|typedef
struct|struct
block|{
DECL|member|lensmap
name|gint32
name|lensmap
decl_stmt|;
comment|/* lens map id */
DECL|member|thick
name|gint32
name|thick
decl_stmt|;
comment|/* lens thickness */
DECL|member|dist
name|gint32
name|dist
decl_stmt|;
comment|/* distance */
DECL|member|na
name|gdouble
name|na
decl_stmt|;
comment|/* index a */
DECL|member|nb
name|gdouble
name|nb
decl_stmt|;
comment|/* index b */
DECL|member|edge
name|gint
name|edge
decl_stmt|;
comment|/* wrap/transparent */
DECL|member|newl
name|gint
name|newl
decl_stmt|;
comment|/* new layer? */
DECL|member|xofs
name|gint
name|xofs
decl_stmt|;
comment|/* offset x */
DECL|member|yofs
name|gint
name|yofs
decl_stmt|;
comment|/* offset y */
DECL|typedef|RefractValues
block|}
name|RefractValues
typedef|;
end_typedef

begin_comment
comment|/* for refractvals.edge */
end_comment

begin_comment
comment|/* If a point is outside the selection, then */
end_comment

begin_define
DECL|macro|BACKGROUND
define|#
directive|define
name|BACKGROUND
value|0
end_define

begin_comment
DECL|macro|BACKGROUND
comment|/* use background color (or leave transparent, if alpha) */
end_comment

begin_define
DECL|macro|OUTSIDE
define|#
directive|define
name|OUTSIDE
value|1
end_define

begin_comment
DECL|macro|OUTSIDE
comment|/* look outside the selection for the point.  If the point is 		     beyond the edge of the layer, use background or alpha. 		     Only makes sense if the drawable is a selection of only part 		     of the layer. */
end_comment

begin_define
DECL|macro|WRAP
define|#
directive|define
name|WRAP
value|2
end_define

begin_comment
DECL|macro|WRAP
comment|/* like OUTSIDE, but if the point is over the edge of the layer, 		  get the point by wrapping around.  Probably most useful on 		  images which are tileable. */
end_comment

begin_comment
comment|/* TO DO: provide a "smear" option?  Would take whatever pixel was on    the edge of the selection or layer (depending if IN_ONLY or    OUTSIDE) where we went over.  Then BACKGROUND/SMEAR would be a    choice independant of IN_ONLY/OUTSIDE/WRAP.  BACKGROUND/SMEAR would    be ignored in the case of WRAP. */
end_comment

begin_comment
comment|/* One can also imagine a WRAP_WITHIN_SELECTION option, but I don't    think I would use it too often.  Would you?  Well, if you're    enthusiastic enough, either write a patch to implement it or    convince me to.  For now, take the selection and float it, make it    a new layer, merge it back when you're done, or whatever. */
end_comment

end_unit

