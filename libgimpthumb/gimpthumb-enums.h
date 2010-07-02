begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * Thumbnail handling according to the Thumbnail Managing Standard.  * http://triq.net/~pearl/thumbnail-spec/  *  * Copyright (C) 2001-2003  Sven Neumann<sven@gimp.org>  *                          Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_THUMB_ENUMS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_THUMB_ENUMS_H__
define|#
directive|define
name|__GIMP_THUMB_ENUMS_H__
end_define

begin_decl_stmt
name|G_BEGIN_DECLS
comment|/**  * SECTION: gimpthumb-enums  * @title: GimpThumb-enums  * @short_description: Enumerations used by libgimpthumb  *  * Enumerations used by libgimpthumb  **/
comment|/**  * GimpThumbFileType:  * @GIMP_THUMB_FILE_TYPE_NONE:    file does not exist  * @GIMP_THUMB_FILE_TYPE_REGULAR: a regular file  * @GIMP_THUMB_FILE_TYPE_FOLDER:  a directory  * @GIMP_THUMB_FILE_TYPE_SPECIAL: a special file (device node, fifo, socket, ...)  *  * File types as returned by gimp_thumb_file_test().  **/
DECL|macro|GIMP_TYPE_THUMB_FILE_TYPE
define|#
directive|define
name|GIMP_TYPE_THUMB_FILE_TYPE
value|(gimp_thumb_file_type_get_type ())
name|GType
name|gimp_thumb_file_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon28efd0200103
block|{
DECL|enumerator|GIMP_THUMB_FILE_TYPE_NONE
name|GIMP_THUMB_FILE_TYPE_NONE
block|,
DECL|enumerator|GIMP_THUMB_FILE_TYPE_REGULAR
name|GIMP_THUMB_FILE_TYPE_REGULAR
block|,
DECL|enumerator|GIMP_THUMB_FILE_TYPE_FOLDER
name|GIMP_THUMB_FILE_TYPE_FOLDER
block|,
DECL|enumerator|GIMP_THUMB_FILE_TYPE_SPECIAL
name|GIMP_THUMB_FILE_TYPE_SPECIAL
DECL|typedef|GimpThumbFileType
block|}
name|GimpThumbFileType
typedef|;
end_typedef

begin_comment
comment|/**  * GimpThumbSize:  * @GIMP_THUMB_SIZE_FAIL:   special size used to indicate a thumbnail  *                          creation failure  * @GIMP_THUMB_SIZE_NORMAL: normal thumbnail size (128 pixels)  * @GIMP_THUMB_SIZE_LARGE:  large thumbnail size (256 pixels)  *  * Possible thumbnail sizes as defined by the Thumbnail Managaging  * Standard.  **/
end_comment

begin_define
DECL|macro|GIMP_TYPE_THUMB_SIZE
define|#
directive|define
name|GIMP_TYPE_THUMB_SIZE
value|(gimp_thumb_size_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_thumb_size_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon28efd0200203
block|{
DECL|enumerator|GIMP_THUMB_SIZE_FAIL
name|GIMP_THUMB_SIZE_FAIL
init|=
literal|0
block|,
DECL|enumerator|GIMP_THUMB_SIZE_NORMAL
name|GIMP_THUMB_SIZE_NORMAL
init|=
literal|128
block|,
DECL|enumerator|GIMP_THUMB_SIZE_LARGE
name|GIMP_THUMB_SIZE_LARGE
init|=
literal|256
DECL|typedef|GimpThumbSize
block|}
name|GimpThumbSize
typedef|;
end_typedef

begin_comment
comment|/**  * GimpThumbState:  * @GIMP_THUMB_STATE_UNKNOWN:   nothing is known about the file/thumbnail  * @GIMP_THUMB_STATE_REMOTE:    the file is on a remote file system  * @GIMP_THUMB_STATE_FOLDER:  * @GIMP_THUMB_STATE_SPECIAL:  * @GIMP_THUMB_STATE_NOT_FOUND: the file/thumbnail doesn't exist  * @GIMP_THUMB_STATE_EXISTS:    the file/thumbnail exists  * @GIMP_THUMB_STATE_OLD:       the thumbnail may be outdated  * @GIMP_THUMB_STATE_FAILED:    the thumbnail couldn't be created  * @GIMP_THUMB_STATE_OK:        the thumbnail exists and matches the image  *  * Possible image and thumbnail file states used by libgimpthumb.  **/
end_comment

begin_define
DECL|macro|GIMP_TYPE_THUMB_STATE
define|#
directive|define
name|GIMP_TYPE_THUMB_STATE
value|(gimp_thumb_state_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_thumb_state_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon28efd0200303
block|{
DECL|enumerator|GIMP_THUMB_STATE_UNKNOWN
name|GIMP_THUMB_STATE_UNKNOWN
block|,
DECL|enumerator|GIMP_THUMB_STATE_REMOTE
name|GIMP_THUMB_STATE_REMOTE
block|,
DECL|enumerator|GIMP_THUMB_STATE_FOLDER
name|GIMP_THUMB_STATE_FOLDER
block|,
DECL|enumerator|GIMP_THUMB_STATE_SPECIAL
name|GIMP_THUMB_STATE_SPECIAL
block|,
DECL|enumerator|GIMP_THUMB_STATE_NOT_FOUND
name|GIMP_THUMB_STATE_NOT_FOUND
block|,
DECL|enumerator|GIMP_THUMB_STATE_EXISTS
name|GIMP_THUMB_STATE_EXISTS
block|,
DECL|enumerator|GIMP_THUMB_STATE_OLD
name|GIMP_THUMB_STATE_OLD
block|,
DECL|enumerator|GIMP_THUMB_STATE_FAILED
name|GIMP_THUMB_STATE_FAILED
block|,
DECL|enumerator|GIMP_THUMB_STATE_OK
name|GIMP_THUMB_STATE_OK
DECL|typedef|GimpThumbState
block|}
name|GimpThumbState
typedef|;
end_typedef

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_THUMB_ENUMS_H__ */
end_comment

end_unit

