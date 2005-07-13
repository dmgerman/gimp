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

begin_comment
comment|/* Amount of color dimensions in one point */
end_comment

begin_define
DECL|macro|SIOX_DIMS
define|#
directive|define
name|SIOX_DIMS
value|3
end_define

begin_function_decl
name|void
name|siox_foreground_extract
parameter_list|(
name|TileManager
modifier|*
name|tiles
parameter_list|,
name|TileManager
modifier|*
name|trimap
parameter_list|,
name|gfloat
name|limits
index|[
name|SIOX_DIMS
index|]
parameter_list|,
name|gint
name|smoothness
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

