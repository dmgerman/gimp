begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* types.h: general types.  Copyright (C) 1992 Free Software Foundation, Inc.  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|TYPES_H
end_ifndef

begin_define
DECL|macro|TYPES_H
define|#
directive|define
name|TYPES_H
end_define

begin_comment
comment|/* Booleans.  */
end_comment

begin_typedef
DECL|enum|__anon29244a2f0103
DECL|typedef|boolean
typedef|typedef
enum|enum
block|{
name|false
init|=
literal|0
block|,
name|true
init|=
literal|1
block|}
name|boolean
typedef|;
end_typedef

begin_comment
comment|/* The X11 library defines `FALSE' and `TRUE', and so we only want to    define them if necessary.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|FALSE
end_ifndef

begin_define
DECL|macro|FALSE
define|#
directive|define
name|FALSE
value|false
end_define

begin_define
DECL|macro|TRUE
define|#
directive|define
name|TRUE
value|true
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* FALSE */
end_comment

begin_comment
comment|/* The usual null-terminated string.  */
end_comment

begin_typedef
DECL|typedef|string
typedef|typedef
name|char
modifier|*
name|string
typedef|;
end_typedef

begin_comment
comment|/* A generic pointer in ANSI C.  */
end_comment

begin_typedef
DECL|typedef|address
typedef|typedef
name|void
modifier|*
name|address
typedef|;
end_typedef

begin_comment
comment|/* We use `real' for our floating-point variables.  */
end_comment

begin_typedef
DECL|typedef|real
typedef|typedef
name|double
name|real
typedef|;
end_typedef

begin_comment
comment|/* A character code.  Perhaps someday we will allow for 16-bit    character codes, but for now we are restricted to 256 characters per    font (like TeX and PostScript).  */
end_comment

begin_typedef
DECL|typedef|charcode_type
typedef|typedef
name|unsigned
name|char
name|charcode_type
typedef|;
end_typedef

begin_comment
comment|/* Used in file formats.  */
end_comment

begin_typedef
DECL|typedef|one_byte
typedef|typedef
name|unsigned
name|char
name|one_byte
typedef|;
end_typedef

begin_typedef
DECL|typedef|signed_byte
typedef|typedef
name|signed
name|char
name|signed_byte
typedef|;
end_typedef

begin_typedef
DECL|typedef|two_bytes
typedef|typedef
name|unsigned
name|short
name|two_bytes
typedef|;
end_typedef

begin_typedef
DECL|typedef|signed_2_bytes
typedef|typedef
name|short
name|signed_2_bytes
typedef|;
end_typedef

begin_typedef
DECL|typedef|four_bytes
typedef|typedef
name|unsigned
name|int
name|four_bytes
typedef|;
end_typedef

begin_typedef
DECL|typedef|signed_4_bytes
typedef|typedef
name|int
name|signed_4_bytes
typedef|;
end_typedef

begin_typedef
DECL|typedef|byte_count_type
typedef|typedef
name|int
name|byte_count_type
typedef|;
end_typedef

begin_comment
comment|/* These are intended to be used for output in file formats where a    ``byte'' is defined to be eight bits, regardless of the hardware.  */
end_comment

begin_define
DECL|macro|ONE_BYTE_BIG
define|#
directive|define
name|ONE_BYTE_BIG
value|(1<< 8)
end_define

begin_define
DECL|macro|TWO_BYTES_BIG
define|#
directive|define
name|TWO_BYTES_BIG
value|(1<< 16)
end_define

begin_define
DECL|macro|THREE_BYTES_BIG
define|#
directive|define
name|THREE_BYTES_BIG
value|(1<< 24)
end_define

begin_comment
comment|/* Complex numbers.  */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon29244a2f0208
block|{
DECL|member|real
name|real
name|real
decl_stmt|;
DECL|member|imag
name|real
name|imag
decl_stmt|;
DECL|typedef|complex
block|}
name|complex
typedef|;
end_typedef

begin_typedef
DECL|enum|__anon29244a2f0303
DECL|enumerator|first_complex_part
DECL|enumerator|second_complex_part
DECL|typedef|complex_part_type
typedef|typedef
enum|enum
block|{
name|first_complex_part
block|,
name|second_complex_part
block|}
name|complex_part_type
typedef|;
end_typedef

begin_typedef
DECL|enum|__anon29244a2f0403
DECL|enumerator|polar_rep
DECL|enumerator|rectangular_rep
DECL|typedef|complex_rep_type
typedef|typedef
enum|enum
block|{
name|polar_rep
block|,
name|rectangular_rep
block|}
name|complex_rep_type
typedef|;
end_typedef

begin_comment
comment|/* Dimensions of a rectangle.  */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon29244a2f0508
block|{
DECL|member|height
DECL|member|width
name|unsigned
name|height
decl_stmt|,
name|width
decl_stmt|;
DECL|typedef|dimensions_type
block|}
name|dimensions_type
typedef|;
end_typedef

begin_define
DECL|macro|DIMENSIONS_HEIGHT (d)
define|#
directive|define
name|DIMENSIONS_HEIGHT
parameter_list|(
name|d
parameter_list|)
value|((d).height)
end_define

begin_define
DECL|macro|DIMENSIONS_WIDTH (d)
define|#
directive|define
name|DIMENSIONS_WIDTH
parameter_list|(
name|d
parameter_list|)
value|((d).width)
end_define

begin_comment
comment|/* Cartesian points.  */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon29244a2f0608
block|{
DECL|member|x
DECL|member|y
name|int
name|x
decl_stmt|,
name|y
decl_stmt|;
DECL|typedef|coordinate_type
block|}
name|coordinate_type
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon29244a2f0708
block|{
DECL|member|x
DECL|member|y
name|double
name|x
decl_stmt|,
name|y
decl_stmt|;
DECL|typedef|real_coordinate_type
block|}
name|real_coordinate_type
typedef|;
end_typedef

begin_if
if|#
directive|if
literal|0
end_if

begin_else
unit|typedef struct {   double       align_threshold;   double       corner_always_threshold;   unsigned int corner_surround;   double       corner_threshold;   double       error_threshold;   unsigned int filter_alternative_surround;   double       filter_epsilon;   unsigned int filter_iteration_count;   double       filter_percent;   unsigned int filter_secondary_surround;   unsigned int filter_surround;   boolean      keep_knees;   double       line_reversion_threshold;   double       line_threshold;   double       reparameterize_improvement;   double       reparameterize_threshold;   double       subdivide_search;   unsigned int subdivide_surround;   double       subdivide_threshold;   unsigned int tangent_surround; } SELVALS;
else|#
directive|else
end_else

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon29244a2f0808
block|{
DECL|member|align_threshold
name|double
name|align_threshold
decl_stmt|;
DECL|member|corner_always_threshold
name|double
name|corner_always_threshold
decl_stmt|;
DECL|member|corner_surround
name|double
name|corner_surround
decl_stmt|;
DECL|member|corner_threshold
name|double
name|corner_threshold
decl_stmt|;
DECL|member|error_threshold
name|double
name|error_threshold
decl_stmt|;
DECL|member|filter_alternative_surround
name|double
name|filter_alternative_surround
decl_stmt|;
DECL|member|filter_epsilon
name|double
name|filter_epsilon
decl_stmt|;
DECL|member|filter_iteration_count
name|double
name|filter_iteration_count
decl_stmt|;
DECL|member|filter_percent
name|double
name|filter_percent
decl_stmt|;
DECL|member|filter_secondary_surround
name|double
name|filter_secondary_surround
decl_stmt|;
DECL|member|filter_surround
name|double
name|filter_surround
decl_stmt|;
DECL|member|keep_knees
name|boolean
name|keep_knees
decl_stmt|;
DECL|member|line_reversion_threshold
name|double
name|line_reversion_threshold
decl_stmt|;
DECL|member|line_threshold
name|double
name|line_threshold
decl_stmt|;
DECL|member|reparameterize_improvement
name|double
name|reparameterize_improvement
decl_stmt|;
DECL|member|reparameterize_threshold
name|double
name|reparameterize_threshold
decl_stmt|;
DECL|member|subdivide_search
name|double
name|subdivide_search
decl_stmt|;
DECL|member|subdivide_surround
name|double
name|subdivide_surround
decl_stmt|;
DECL|member|subdivide_threshold
name|double
name|subdivide_threshold
decl_stmt|;
DECL|member|tangent_surround
name|double
name|tangent_surround
decl_stmt|;
DECL|typedef|SELVALS
block|}
name|SELVALS
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* 1 */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* not TYPES_H */
end_comment

end_unit

