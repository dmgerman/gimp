begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_BASE_ENUMS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_BASE_ENUMS_H__
define|#
directive|define
name|__GIMP_BASE_ENUMS_H__
end_define

begin_decl_stmt
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
comment|/*  * these enums that are registered with the type system  */
DECL|macro|GIMP_TYPE_IMAGE_BASE_TYPE
define|#
directive|define
name|GIMP_TYPE_IMAGE_BASE_TYPE
value|(gimp_image_base_type_get_type ())
name|GType
name|gimp_image_base_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon29f4e4b00103
block|{
DECL|enumerator|GIMP_RGB
name|GIMP_RGB
block|,
comment|/*< desc="RGB color">*/
DECL|enumerator|GIMP_GRAY
name|GIMP_GRAY
block|,
comment|/*< desc="Grayscale">*/
DECL|enumerator|GIMP_INDEXED
name|GIMP_INDEXED
comment|/*< desc="Indexed color">*/
DECL|typedef|GimpImageBaseType
block|}
name|GimpImageBaseType
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_IMAGE_TYPE
define|#
directive|define
name|GIMP_TYPE_IMAGE_TYPE
value|(gimp_image_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_image_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon29f4e4b00203
block|{
DECL|enumerator|GIMP_RGB_IMAGE
name|GIMP_RGB_IMAGE
block|,
comment|/*< desc="RGB">*/
DECL|enumerator|GIMP_RGBA_IMAGE
name|GIMP_RGBA_IMAGE
block|,
comment|/*< desc="RGB-alpha">*/
DECL|enumerator|GIMP_GRAY_IMAGE
name|GIMP_GRAY_IMAGE
block|,
comment|/*< desc="Grayscale">*/
DECL|enumerator|GIMP_GRAYA_IMAGE
name|GIMP_GRAYA_IMAGE
block|,
comment|/*< desc="Grayscale-alpha">*/
DECL|enumerator|GIMP_INDEXED_IMAGE
name|GIMP_INDEXED_IMAGE
block|,
comment|/*< desc="Indexed">*/
DECL|enumerator|GIMP_INDEXEDA_IMAGE
name|GIMP_INDEXEDA_IMAGE
comment|/*< desc="Indexed-alpha">*/
DECL|typedef|GimpImageType
block|}
name|GimpImageType
typedef|;
end_typedef

begin_comment
comment|/*  * non-registered enums  */
end_comment

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon29f4e4b00303
block|{
DECL|enumerator|GIMP_UNIT_PIXEL
name|GIMP_UNIT_PIXEL
init|=
literal|0
block|,
DECL|enumerator|GIMP_UNIT_INCH
name|GIMP_UNIT_INCH
init|=
literal|1
block|,
DECL|enumerator|GIMP_UNIT_MM
name|GIMP_UNIT_MM
init|=
literal|2
block|,
DECL|enumerator|GIMP_UNIT_POINT
name|GIMP_UNIT_POINT
init|=
literal|3
block|,
DECL|enumerator|GIMP_UNIT_PICA
name|GIMP_UNIT_PICA
init|=
literal|4
block|,
DECL|enumerator|GIMP_UNIT_END
name|GIMP_UNIT_END
init|=
literal|5
block|,
DECL|enumerator|GIMP_UNIT_PERCENT
name|GIMP_UNIT_PERCENT
init|=
literal|65536
comment|/*< pdb-skip>*/
DECL|typedef|GimpUnit
block|}
name|GimpUnit
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon29f4e4b00403
block|{
DECL|enumerator|GIMP_PDB_INT32
name|GIMP_PDB_INT32
block|,
DECL|enumerator|GIMP_PDB_INT16
name|GIMP_PDB_INT16
block|,
DECL|enumerator|GIMP_PDB_INT8
name|GIMP_PDB_INT8
block|,
DECL|enumerator|GIMP_PDB_FLOAT
name|GIMP_PDB_FLOAT
block|,
DECL|enumerator|GIMP_PDB_STRING
name|GIMP_PDB_STRING
block|,
DECL|enumerator|GIMP_PDB_INT32ARRAY
name|GIMP_PDB_INT32ARRAY
block|,
DECL|enumerator|GIMP_PDB_INT16ARRAY
name|GIMP_PDB_INT16ARRAY
block|,
DECL|enumerator|GIMP_PDB_INT8ARRAY
name|GIMP_PDB_INT8ARRAY
block|,
DECL|enumerator|GIMP_PDB_FLOATARRAY
name|GIMP_PDB_FLOATARRAY
block|,
DECL|enumerator|GIMP_PDB_STRINGARRAY
name|GIMP_PDB_STRINGARRAY
block|,
DECL|enumerator|GIMP_PDB_COLOR
name|GIMP_PDB_COLOR
block|,
DECL|enumerator|GIMP_PDB_REGION
name|GIMP_PDB_REGION
block|,
DECL|enumerator|GIMP_PDB_DISPLAY
name|GIMP_PDB_DISPLAY
block|,
DECL|enumerator|GIMP_PDB_IMAGE
name|GIMP_PDB_IMAGE
block|,
DECL|enumerator|GIMP_PDB_LAYER
name|GIMP_PDB_LAYER
block|,
DECL|enumerator|GIMP_PDB_CHANNEL
name|GIMP_PDB_CHANNEL
block|,
DECL|enumerator|GIMP_PDB_DRAWABLE
name|GIMP_PDB_DRAWABLE
block|,
DECL|enumerator|GIMP_PDB_SELECTION
name|GIMP_PDB_SELECTION
block|,
DECL|enumerator|GIMP_PDB_BOUNDARY
name|GIMP_PDB_BOUNDARY
block|,
DECL|enumerator|GIMP_PDB_PATH
name|GIMP_PDB_PATH
block|,
DECL|enumerator|GIMP_PDB_PARASITE
name|GIMP_PDB_PARASITE
block|,
DECL|enumerator|GIMP_PDB_STATUS
name|GIMP_PDB_STATUS
block|,
DECL|enumerator|GIMP_PDB_END
name|GIMP_PDB_END
DECL|typedef|GimpPDBArgType
block|}
name|GimpPDBArgType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon29f4e4b00503
block|{
DECL|enumerator|GIMP_INTERNAL
name|GIMP_INTERNAL
block|,
DECL|enumerator|GIMP_PLUGIN
name|GIMP_PLUGIN
block|,
DECL|enumerator|GIMP_EXTENSION
name|GIMP_EXTENSION
block|,
DECL|enumerator|GIMP_TEMPORARY
name|GIMP_TEMPORARY
DECL|typedef|GimpPDBProcType
block|}
name|GimpPDBProcType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon29f4e4b00603
block|{
DECL|enumerator|GIMP_PDB_EXECUTION_ERROR
name|GIMP_PDB_EXECUTION_ERROR
block|,
DECL|enumerator|GIMP_PDB_CALLING_ERROR
name|GIMP_PDB_CALLING_ERROR
block|,
DECL|enumerator|GIMP_PDB_PASS_THROUGH
name|GIMP_PDB_PASS_THROUGH
block|,
DECL|enumerator|GIMP_PDB_SUCCESS
name|GIMP_PDB_SUCCESS
block|,
DECL|enumerator|GIMP_PDB_CANCEL
name|GIMP_PDB_CANCEL
DECL|typedef|GimpPDBStatusType
block|}
name|GimpPDBStatusType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon29f4e4b00703
block|{
DECL|enumerator|GIMP_MESSAGE_BOX
name|GIMP_MESSAGE_BOX
block|,
DECL|enumerator|GIMP_CONSOLE
name|GIMP_CONSOLE
block|,
DECL|enumerator|GIMP_ERROR_CONSOLE
name|GIMP_ERROR_CONSOLE
DECL|typedef|GimpMessageHandlerType
block|}
name|GimpMessageHandlerType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon29f4e4b00803
block|{
DECL|enumerator|GIMP_STACK_TRACE_NEVER
name|GIMP_STACK_TRACE_NEVER
block|,
DECL|enumerator|GIMP_STACK_TRACE_QUERY
name|GIMP_STACK_TRACE_QUERY
block|,
DECL|enumerator|GIMP_STACK_TRACE_ALWAYS
name|GIMP_STACK_TRACE_ALWAYS
DECL|typedef|GimpStackTraceMode
block|}
name|GimpStackTraceMode
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
comment|/* __GIMP_BASE_ENUMS_H__ */
end_comment

end_unit

