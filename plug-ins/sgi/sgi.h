begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * "$Id$"  *  *   SGI image file format library definitions.  *  *   Copyright 1997 Michael Sweet (mike@easysw.com)  *  *   This program is free software; you can redistribute it and/or modify it  *   under the terms of the GNU General Public License as published by the Free  *   Software Foundation; either version 2 of the License, or (at your option)  *   any later version.  *  *   This program is distributed in the hope that it will be useful, but  *   WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY  *   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License  *   for more details.  *  *   You should have received a copy of the GNU General Public License  *   along with this program; if not, write to the Free Software  *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  *  * Revision History:  *  *   $Log$  *   Revision 1.1  1997/11/24 22:04:37  sopwith  *   Initial revision  *  *   Revision 1.3  1997/11/18 03:04:29  nobody  *   fixed ugly comment-bugs introduced by evil darkwing  *   keep out configuration empty dirs  *   	--darkwing  *  *   Revision 1.2  1997/11/17 05:44:04  nobody  *   updated ChangeLog  *   dropped non-working doc/Makefile entries  *   applied many fixes from the registry as well as the devel ML  *   applied missing patches by Art Haas  *  *   	--darkwing  *  *   Revision 1.2  1997/06/18  00:55:28  mike  *   Updated to hold length table when writing.  *   Updated to hold current length when doing ARLE.  *  *   Revision 1.1  1997/06/15  03:37:19  mike  *   Initial revision  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_SGI_H_
end_ifndef

begin_define
DECL|macro|_SGI_H_
define|#
directive|define
name|_SGI_H_
end_define

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
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
comment|/*  * Constants...  */
DECL|macro|SGI_MAGIC
define|#
directive|define
name|SGI_MAGIC
value|474
comment|/* Magic number in image file */
DECL|macro|SGI_READ
define|#
directive|define
name|SGI_READ
value|0
comment|/* Read from an SGI image file */
DECL|macro|SGI_WRITE
define|#
directive|define
name|SGI_WRITE
value|1
comment|/* Write to an SGI image file */
DECL|macro|SGI_COMP_NONE
define|#
directive|define
name|SGI_COMP_NONE
value|0
comment|/* No compression */
DECL|macro|SGI_COMP_RLE
define|#
directive|define
name|SGI_COMP_RLE
value|1
comment|/* Run-length encoding */
DECL|macro|SGI_COMP_ARLE
define|#
directive|define
name|SGI_COMP_ARLE
value|2
comment|/* Agressive run-length encoding */
comment|/*  * Image structure...  */
typedef|typedef
struct|struct
DECL|struct|__anon28ffd4c20108
block|{
DECL|member|file
name|FILE
modifier|*
name|file
decl_stmt|;
comment|/* Image file */
DECL|member|mode
name|int
name|mode
decl_stmt|,
comment|/* File open mode */
DECL|member|bpp
name|bpp
decl_stmt|,
comment|/* Bytes per pixel/channel */
DECL|member|comp
name|comp
decl_stmt|;
comment|/* Compression */
DECL|member|xsize
name|unsigned
name|short
name|xsize
decl_stmt|,
comment|/* Width in pixels */
DECL|member|ysize
name|ysize
decl_stmt|,
comment|/* Height in pixels */
DECL|member|zsize
name|zsize
decl_stmt|;
comment|/* Number of channels */
DECL|member|firstrow
name|long
name|firstrow
decl_stmt|,
comment|/* File offset for first row */
DECL|member|nextrow
name|nextrow
decl_stmt|,
comment|/* File offset for next row */
DECL|member|table
modifier|*
modifier|*
name|table
decl_stmt|,
comment|/* Offset table for compression */
DECL|member|length
modifier|*
modifier|*
name|length
decl_stmt|;
comment|/* Length table for compression */
DECL|member|arle_row
name|short
modifier|*
name|arle_row
decl_stmt|;
comment|/* Advanced RLE compression buffer */
DECL|member|arle_offset
name|long
name|arle_offset
decl_stmt|,
comment|/* Advanced RLE buffer offset */
DECL|member|arle_length
name|arle_length
decl_stmt|;
comment|/* Advanced RLE buffer length */
DECL|typedef|sgi_t
block|}
name|sgi_t
typedef|;
comment|/*  * Prototypes...  */
specifier|extern
name|int
name|sgiClose
parameter_list|(
name|sgi_t
modifier|*
name|sgip
parameter_list|)
function_decl|;
specifier|extern
name|int
name|sgiGetRow
parameter_list|(
name|sgi_t
modifier|*
name|sgip
parameter_list|,
name|short
modifier|*
name|row
parameter_list|,
name|int
name|y
parameter_list|,
name|int
name|z
parameter_list|)
function_decl|;
specifier|extern
name|sgi_t
modifier|*
name|sgiOpen
parameter_list|(
name|char
modifier|*
name|filename
parameter_list|,
name|int
name|mode
parameter_list|,
name|int
name|comp
parameter_list|,
name|int
name|bpp
parameter_list|,
name|int
name|xsize
parameter_list|,
name|int
name|ysize
parameter_list|,
name|int
name|zsize
parameter_list|)
function_decl|;
specifier|extern
name|int
name|sgiPutRow
parameter_list|(
name|sgi_t
modifier|*
name|sgip
parameter_list|,
name|short
modifier|*
name|row
parameter_list|,
name|int
name|y
parameter_list|,
name|int
name|z
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* !_SGI_H_ */
end_comment

begin_comment
comment|/*  * End of "$Id$".  */
end_comment

end_unit

