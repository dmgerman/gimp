begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1999 Andy Thomas alt@picnic.demon.co.uk  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PATHSP_H__
end_ifndef

begin_define
DECL|macro|__PATHSP_H__
define|#
directive|define
name|__PATHSP_H__
end_define

begin_comment
comment|/* Cutdown representation of the bezier curve description */
end_comment

begin_comment
comment|/* Will be used to hopefully store in XCF format...  */
end_comment

begin_typedef
DECL|struct|__anon2c1568650108
typedef|typedef
struct|struct
block|{
DECL|member|type
name|guint32
name|type
decl_stmt|;
DECL|member|x
name|gint32
name|x
decl_stmt|;
DECL|member|y
name|gint32
name|y
decl_stmt|;
DECL|typedef|BZPOINT
DECL|typedef|BZPOINTP
block|}
name|BZPOINT
operator|,
typedef|*
name|BZPOINTP
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2c1568650208
typedef|typedef
struct|struct
block|{
DECL|member|bezier_details
name|GSList
modifier|*
name|bezier_details
decl_stmt|;
DECL|member|closed
name|gboolean
name|closed
decl_stmt|;
DECL|member|state
name|guint32
name|state
decl_stmt|;
DECL|member|locked
name|guint32
name|locked
decl_stmt|;
comment|/* Only bottom bit used */
DECL|member|name
name|GString
modifier|*
name|name
decl_stmt|;
DECL|typedef|BZPATH
DECL|typedef|BZPATHP
block|}
name|BZPATH
operator|,
typedef|*
name|BZPATHP
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2c1568650308
typedef|typedef
struct|struct
block|{
DECL|member|gimage
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
DECL|member|gdisp
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
comment|/* This is a hack.. Needed so we can get back to  		      * the same display that these curves were added 		      * too. That way when an entry in the paths dialog 		      * is clicked the bezier tool can be targeted at  		      * correct display. Note this display could have been 		      * deleted (ie different view), but gdisplays_check_valid() 		      * function will take care of that.. In this case we just 		      * pick a display that the gimage is rendered in. 		      */
DECL|member|bz_paths
name|GSList
modifier|*
name|bz_paths
decl_stmt|;
comment|/* list of BZPATHP */
DECL|member|sig_id
name|guint
name|sig_id
decl_stmt|;
DECL|member|last_selected_row
name|gint32
name|last_selected_row
decl_stmt|;
DECL|typedef|PATHIMAGELIST
DECL|typedef|PATHIMAGELISTP
DECL|typedef|PathsList
block|}
name|PATHIMAGELIST
operator|,
typedef|*
name|PATHIMAGELISTP
operator|,
name|PathsList
typedef|;
end_typedef

begin_function_decl
name|BZPOINTP
name|bzpoint_new
parameter_list|(
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|BZPATHP
name|bzpath_new
parameter_list|(
name|GSList
modifier|*
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gchar
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|PathsList
modifier|*
name|pathsList_new
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|gint
parameter_list|,
name|GSList
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __PATHSP_H__  */
end_comment

end_unit

