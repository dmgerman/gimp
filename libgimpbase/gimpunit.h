begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library                                                     * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball                  *  * gimpunit.h  * Copyright (C) 1999 Michael Natterer<mitschel@cs.tu-berlin.de>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Library General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Library General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* NOTE:  *  * This file serves as header for both app/gimpunit.c and libgimp/gimpunit.c  * because the unit functions are needed by widgets which are used by both  * the gimp app and plugins.  */
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
typedef|typedef
enum|enum
DECL|enum|__anon29e1ba630103
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
DECL|enumerator|UNIT_MM
name|UNIT_MM
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
DECL|enumerator|UNIT_END
name|UNIT_END
init|=
literal|5
block|,
comment|/*  never use UNIT_END but 			*  gimp_unit_get_number_of_units() instead 			*/
DECL|enumerator|UNIT_PERCENT
name|UNIT_PERCENT
init|=
literal|65536
comment|/*  this one does not really belong here but it's 			*  convenient to use the unit system for the 			*  various strings (symbol, singular, ...) 			* 			*  you can only ask it for it's strings, asking for 			*  factor, digits or deletion_flag will produce 			*  an error. 			*/
DECL|typedef|GUnit
block|}
name|GUnit
typedef|;
name|gint
name|gimp_unit_get_number_of_units
parameter_list|(
name|void
parameter_list|)
function_decl|;
name|gint
name|gimp_unit_get_number_of_built_in_units
parameter_list|(
name|void
parameter_list|)
function_decl|;
comment|/* Create a new user unit and returns it's ID.  *  * Note that a new unit is always created with it's deletion flag  * set to TRUE. You will have to set it to FALSE after creation to make  * the unit definition persistant.  */
name|GUnit
name|gimp_unit_new
parameter_list|(
name|gchar
modifier|*
name|identifier
parameter_list|,
name|gdouble
name|factor
parameter_list|,
name|gint
name|digits
parameter_list|,
name|gchar
modifier|*
name|symbol
parameter_list|,
name|gchar
modifier|*
name|abbreviation
parameter_list|,
name|gchar
modifier|*
name|singular
parameter_list|,
name|gchar
modifier|*
name|plural
parameter_list|)
function_decl|;
comment|/* The following functions fall back to inch (not pixel, as pixel is not  * a 'real' unit) if the value passed is out of range.  *  * Trying to change the deletion flag of built-in units will be ignored.  */
comment|/* If the deletion flag for a unit is TRUE on GIMP exit, this unit  * will not be saved in the user units database.  */
name|guint
name|gimp_unit_get_deletion_flag
parameter_list|(
name|GUnit
name|unit
parameter_list|)
function_decl|;
name|void
name|gimp_unit_set_deletion_flag
parameter_list|(
name|GUnit
name|unit
parameter_list|,
name|guint
name|deletion_flag
parameter_list|)
function_decl|;
comment|/* The meaning of 'factor' is:  * distance_in_units == ( factor * distance_in_inches )  *  * Returns 0 for unit == UNIT_PIXEL as we don't have resolution info here  */
name|gdouble
name|gimp_unit_get_factor
parameter_list|(
name|GUnit
name|unit
parameter_list|)
function_decl|;
comment|/* The following function gives a hint how many digits a spinbutton  * should provide to get approximately the accuracy of an inch-spinbutton  * with two digits.  *  * Returns 0 for unit == UNIT_PIXEL as we don't have resolution info here.  */
name|gint
name|gimp_unit_get_digits
parameter_list|(
name|GUnit
name|unit
parameter_list|)
function_decl|;
comment|/* NOTE:  *  * the gchar pointer returned is constant in the gimp application but must  * be g_free()'d by plug-ins.  */
comment|/* This one is an untranslated string for gimprc */
name|gchar
modifier|*
name|gimp_unit_get_identifier
parameter_list|(
name|GUnit
name|unit
parameter_list|)
function_decl|;
name|gchar
modifier|*
name|gimp_unit_get_symbol
parameter_list|(
name|GUnit
name|unit
parameter_list|)
function_decl|;
name|gchar
modifier|*
name|gimp_unit_get_abbreviation
parameter_list|(
name|GUnit
name|unit
parameter_list|)
function_decl|;
name|gchar
modifier|*
name|gimp_unit_get_singular
parameter_list|(
name|GUnit
name|unit
parameter_list|)
function_decl|;
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

