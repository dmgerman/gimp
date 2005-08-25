begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * SIOX: Simple Interactive Object Extraction  *  * For algorithm documentation refer to:  * G. Friedland, K. Jantz, L. Knipping, R. Rojas:  * "Image Segmentation by Uniform Color Clustering  *  -- Approach and Benchmark Results",  * Technical Report B-05-07, Department of Computer Science,  * Freie Universitaet Berlin, June 2005.  * http://www.inf.fu-berlin.de/inst/pubs/tr-b-05-07.pdf  *  * See http://www.siox.org/ for more information.  *  * Algorithm idea by Gerald Friedland.  * This implementation is Copyright (C) 2005  * by Gerald Friedland<fland@inf.fu-berlin.de>  * and Kristian Jantz<jantz@inf.fu-berlin.de>.  *  * This program is free software; you can redistribute it and/or  * modify it under the terms of the GNU General Public License  * as published by the Free Software Foundation; either version 2  * of the License, or (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  * 02110-1301, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__SIOX_H__
end_ifndef

begin_define
DECL|macro|__SIOX_H__
define|#
directive|define
name|__SIOX_H__
end_define

begin_define
DECL|macro|SIOX_DEFAULT_SMOOTHNESS
define|#
directive|define
name|SIOX_DEFAULT_SMOOTHNESS
value|3
end_define

begin_define
DECL|macro|SIOX_DEFAULT_SENSITIVITY_L
define|#
directive|define
name|SIOX_DEFAULT_SENSITIVITY_L
value|0.66
end_define

begin_define
DECL|macro|SIOX_DEFAULT_SENSITIVITY_A
define|#
directive|define
name|SIOX_DEFAULT_SENSITIVITY_A
value|1.25
end_define

begin_define
DECL|macro|SIOX_DEFAULT_SENSITIVITY_B
define|#
directive|define
name|SIOX_DEFAULT_SENSITIVITY_B
value|2.5
end_define

begin_typedef
DECL|typedef|SioxProgressFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|SioxProgressFunc
function_decl|)
parameter_list|(
name|gpointer
name|progress_data
parameter_list|,
name|gdouble
name|fraction
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
name|void
name|siox_foreground_extract
parameter_list|(
name|TileManager
modifier|*
name|pixels
parameter_list|,
specifier|const
name|guchar
modifier|*
name|colormap
parameter_list|,
name|gint
name|offset_x
parameter_list|,
name|gint
name|offset_y
parameter_list|,
name|TileManager
modifier|*
name|mask
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|smoothness
parameter_list|,
specifier|const
name|gdouble
name|sensitivity
index|[
literal|3
index|]
parameter_list|,
name|SioxProgressFunc
name|progress_callback
parameter_list|,
name|gpointer
name|progress_data
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __SIOX_H__ */
end_comment

end_unit

