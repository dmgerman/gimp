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
DECL|struct|__anon2c52906f0108
typedef|typedef
struct|struct
block|{
DECL|member|type
name|guint32
name|type
decl_stmt|;
DECL|member|x
name|gdouble
name|x
decl_stmt|;
DECL|member|y
name|gdouble
name|y
decl_stmt|;
DECL|typedef|PATHPOINT
DECL|typedef|PATHPOINTP
block|}
name|PATHPOINT
operator|,
typedef|*
name|PATHPOINTP
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2c52906f0208
typedef|typedef
struct|struct
block|{
DECL|member|path_details
name|GSList
modifier|*
name|path_details
decl_stmt|;
DECL|member|pathtype
name|guint32
name|pathtype
decl_stmt|;
comment|/* Only beziers to start with */
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
DECL|typedef|PATH
DECL|typedef|PATHP
block|}
name|PATH
operator|,
typedef|*
name|PATHP
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2c52906f0308
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

begin_typedef
DECL|enum|__anon2c52906f0403
typedef|typedef
enum|enum
block|{
DECL|enumerator|BEZIER
name|BEZIER
init|=
literal|1
block|, }
DECL|typedef|PathType
name|PathType
typedef|;
end_typedef

begin_function_decl
name|PATHPOINTP
name|pathpoint_new
parameter_list|(
name|gint
parameter_list|,
name|gdouble
parameter_list|,
name|gdouble
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|PATHP
name|path_new
parameter_list|(
name|PathType
parameter_list|,
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

begin_function_decl
name|gboolean
name|paths_set_path
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|gchar
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|paths_set_path_points
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|gchar
modifier|*
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gdouble
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|paths_stroke
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|PathsList
modifier|*
parameter_list|,
name|PATHP
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

