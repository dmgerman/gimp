begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* gimpunit.h  * Copyright (C) 1999 Michael Natterer<mitschel@cs.tu-berlin.de>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Library General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Library General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMPUNIT_H__
end_ifndef

begin_define
DECL|macro|__GIMPUNIT_H__
define|#
directive|define
name|__GIMPUNIT_H__
end_define

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|__cplusplus
end_ifdef

begin_extern
extern|extern
literal|"C"
block|{
endif|#
directive|endif
comment|/* __cplusplus */
comment|/* I've put this here and not to libgimp/gimpenums.h, because if this  * file includes libgimp/gimpenums.h there is a name clash wherever  * someone includes libgimp/gimpunit.h and app/gimpimage.h  * (the constants RGB, GRAY and INDEXED are defined in both  * gimpenums.h and gimpimage.h) (is this a bug? don't know...)  */
typedef|typedef
enum|enum
DECL|enum|__anon29441e220103
block|{
DECL|enumerator|UNIT_PIXEL
name|UNIT_PIXEL
init|=
literal|0
block|,
DECL|enumerator|UNIT_INCH
name|UNIT_INCH
init|=
literal|1
block|,
DECL|enumerator|UNIT_CM
name|UNIT_CM
init|=
literal|2
block|,
DECL|enumerator|UNIT_POINT
name|UNIT_POINT
init|=
literal|3
block|,
DECL|enumerator|UNIT_PICA
name|UNIT_PICA
init|=
literal|4
block|,
DECL|enumerator|UNIT_MM
name|UNIT_MM
init|=
literal|5
block|,
DECL|enumerator|UNIT_METER
name|UNIT_METER
init|=
literal|6
block|,
DECL|enumerator|UNIT_FOOT
name|UNIT_FOOT
init|=
literal|7
block|,
DECL|enumerator|UNIT_YARD
name|UNIT_YARD
init|=
literal|8
block|,
DECL|enumerator|UNIT_END
name|UNIT_END
DECL|typedef|GUnit
block|}
name|GUnit
typedef|;
DECL|macro|gimp_unit_get_number_of_units ()
define|#
directive|define
name|gimp_unit_get_number_of_units
parameter_list|()
value|UNIT_END
comment|/* the following functions fall back to inch (not pixel, as pixel is not  * a 'real' unit) if the value passed is out of range  */
comment|/* the meaning of 'factor' is:  * distance_in_units == ( factor * distance_in_inches )  *  * returns 0 for unit == UNIT_PIXEL as we don't have resolution info here  */
name|gfloat
name|gimp_unit_get_factor
parameter_list|(
name|GUnit
name|unit
parameter_list|)
function_decl|;
comment|/* the following function gives a hint how many digits a spinbutton  * should provide to get approximately the accuracy of an inch-spinbutton  * with two digits.  *  * returns 0 for unit == UNIT_PIXEL as we don't have resolution info here  */
name|gint
name|gimp_unit_get_digits
parameter_list|(
name|GUnit
name|unit
parameter_list|)
function_decl|;
specifier|const
name|gchar
modifier|*
name|gimp_unit_get_symbol
parameter_list|(
name|GUnit
name|unit
parameter_list|)
function_decl|;
specifier|const
name|gchar
modifier|*
name|gimp_unit_get_abbreviation
parameter_list|(
name|GUnit
name|unit
parameter_list|)
function_decl|;
specifier|const
name|gchar
modifier|*
name|gimp_unit_get_singular
parameter_list|(
name|GUnit
name|unit
parameter_list|)
function_decl|;
specifier|const
name|gchar
modifier|*
name|gimp_unit_get_plural
parameter_list|(
name|GUnit
name|unit
parameter_list|)
function_decl|;
ifdef|#
directive|ifdef
name|__cplusplus
block|}
end_extern

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __cplusplus */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMPUNIT_H__  */
end_comment

end_unit

