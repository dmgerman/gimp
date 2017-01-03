begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * gimprational.h  *  *  Created on: 19.09.2014  *      Author: kuhse  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMPRATIONAL_H__
end_ifndef

begin_define
DECL|macro|__GIMPRATIONAL_H__
define|#
directive|define
name|__GIMPRATIONAL_H__
end_define

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|GIMP_TYPE_RATIONAL
define|#
directive|define
name|GIMP_TYPE_RATIONAL
value|(rational_get_type  ())
end_define

begin_define
DECL|macro|GIMP_TYPE_SRATIONAL
define|#
directive|define
name|GIMP_TYPE_SRATIONAL
value|(srational_get_type ())
end_define

begin_typedef
DECL|typedef|RationalValue
typedef|typedef
name|struct
name|_RationalValue
name|RationalValue
typedef|;
end_typedef

begin_struct
DECL|struct|_RationalValue
struct|struct
name|_RationalValue
block|{
DECL|member|nom
name|guint
name|nom
decl_stmt|;
DECL|member|denom
name|guint
name|denom
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|SRationalValue
typedef|typedef
name|struct
name|_SRationalValue
name|SRationalValue
typedef|;
end_typedef

begin_struct
DECL|struct|_SRationalValue
struct|struct
name|_SRationalValue
block|{
DECL|member|nom
name|gint
name|nom
decl_stmt|;
DECL|member|denom
name|guint
name|denom
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|Rational
typedef|typedef
name|struct
name|_Rational
name|Rational
typedef|;
end_typedef

begin_struct
DECL|struct|_Rational
struct|struct
name|_Rational
block|{
DECL|member|rational_array
name|GArray
modifier|*
name|rational_array
decl_stmt|;
DECL|member|length
name|gint
name|length
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|SRational
typedef|typedef
name|struct
name|_SRational
name|SRational
typedef|;
end_typedef

begin_struct
DECL|struct|_SRational
struct|struct
name|_SRational
block|{
DECL|member|srational_array
name|GArray
modifier|*
name|srational_array
decl_stmt|;
DECL|member|length
name|gint
name|length
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|rational_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|GType
name|srational_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|rational_free
parameter_list|(
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|srational_free
parameter_list|(
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|string_to_rational
parameter_list|(
name|gchar
modifier|*
name|string
parameter_list|,
name|Rational
modifier|*
modifier|*
name|rational
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|rational_to_int
parameter_list|(
name|Rational
modifier|*
name|rational
parameter_list|,
name|gint
modifier|*
modifier|*
name|nom
parameter_list|,
name|gint
modifier|*
modifier|*
name|denom
parameter_list|,
name|gint
modifier|*
name|length
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|string_to_srational
parameter_list|(
name|gchar
modifier|*
name|string
parameter_list|,
name|SRational
modifier|*
modifier|*
name|srational
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMPRATIONAL_H__ */
end_comment

end_unit

