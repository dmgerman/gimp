begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* gserialize.h  * Copyright (C) 1998 Jay Cox<jaycox@earthlink.net>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Library General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Library General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GSERIALIZE_H__
end_ifndef

begin_define
DECL|macro|__GSERIALIZE_H__
define|#
directive|define
name|__GSERIALIZE_H__
end_define

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
include|#
directive|include
file|<glib.h>
include|#
directive|include
file|<stdarg.h>
DECL|enum|__anon296df8000103
typedef|typedef
enum|enum
block|{
DECL|enumerator|GSERIAL_END
name|GSERIAL_END
init|=
literal|0
block|,
comment|/* for internal use only */
DECL|enumerator|GSERIAL_INT8
name|GSERIAL_INT8
init|=
literal|1
block|,
DECL|enumerator|GSERIAL_INT16
name|GSERIAL_INT16
init|=
literal|2
block|,
DECL|enumerator|GSERIAL_INT32
name|GSERIAL_INT32
init|=
literal|3
block|,
DECL|enumerator|GSERIAL_FLOAT
name|GSERIAL_FLOAT
init|=
literal|4
block|,
comment|/* 32 bit IEEE fp value */
DECL|enumerator|GSERIAL_DOUBLE
name|GSERIAL_DOUBLE
init|=
literal|5
block|,
comment|/* 64 bit IEEE fp value */
DECL|enumerator|GSERIAL_STRING
name|GSERIAL_STRING
init|=
literal|101
block|,
DECL|enumerator|GSERIAL_INT8ARRAY
name|GSERIAL_INT8ARRAY
init|=
literal|102
block|,
DECL|enumerator|GSERIAL_INT16ARRAY
name|GSERIAL_INT16ARRAY
init|=
literal|103
block|,
DECL|enumerator|GSERIAL_INT32ARRAY
name|GSERIAL_INT32ARRAY
init|=
literal|104
block|,
DECL|enumerator|GSERIAL_FLOATARRAY
name|GSERIAL_FLOATARRAY
init|=
literal|105
block|,
DECL|enumerator|GSERIAL_DOUBLEARRAY
name|GSERIAL_DOUBLEARRAY
init|=
literal|106
block|,
DECL|enumerator|GSERIAL_LAST_TYPE
name|GSERIAL_LAST_TYPE
init|=
literal|107
DECL|typedef|GSerialType
block|}
name|GSerialType
typedef|;
DECL|typedef|GSerialItem
typedef|typedef
name|struct
name|_GSerialItem
name|GSerialItem
typedef|;
DECL|typedef|GSerialDescription
typedef|typedef
name|struct
name|_GSerialDescription
name|GSerialDescription
typedef|;
name|GSerialItem
modifier|*
name|g_new_serial_item
parameter_list|(
name|GSerialType
name|type
parameter_list|,
name|gulong
name|offset
parameter_list|,
name|gint32
name|length
parameter_list|,
name|gulong
name|length_offset
parameter_list|)
function_decl|;
DECL|macro|g_serial_item (type,struct_,member)
define|#
directive|define
name|g_serial_item
parameter_list|(
name|type
parameter_list|,
name|struct_
parameter_list|,
name|member
parameter_list|)
define|\
value|g_new_serial_item(type, G_STRUCT_OFFSET(struct_, member), 0, 0)
DECL|macro|g_serial_array (type,struct_,member,length)
define|#
directive|define
name|g_serial_array
parameter_list|(
name|type
parameter_list|,
name|struct_
parameter_list|,
name|member
parameter_list|,
name|length
parameter_list|)
define|\
value|g_new_serial_item(type, G_STRUCT_OFFSET(struct_, member), length, 0)
DECL|macro|g_serial_vlen_array (type,struct_,member,length_member)
define|#
directive|define
name|g_serial_vlen_array
parameter_list|(
name|type
parameter_list|,
name|struct_
parameter_list|,
name|member
parameter_list|,
name|length_member
parameter_list|)
define|\
value|g_new_serial_item(type, G_STRUCT_OFFSET(struct_, member), -1,   \ 		    G_STRUCT_OFFSET(struct_, length_member))
name|GSerialDescription
modifier|*
name|g_new_serial_description
parameter_list|(
name|char
modifier|*
name|name
parameter_list|,
modifier|...
parameter_list|)
function_decl|;
comment|/* pass it g_serial_s.  null terminated */
name|void
name|g_free_serial_description
parameter_list|(
name|GSerialDescription
modifier|*
parameter_list|)
function_decl|;
name|long
name|g_serialize
parameter_list|(
name|GSerialDescription
modifier|*
name|d
parameter_list|,
name|void
modifier|*
modifier|*
name|output
parameter_list|,
name|void
modifier|*
name|struct_data
parameter_list|)
function_decl|;
comment|/* returns the length of the serialized data.       g_mallocs space for the data and stores a pointer to it in output */
name|long
name|g_deserialize
parameter_list|(
name|GSerialDescription
modifier|*
name|d
parameter_list|,
name|void
modifier|*
name|output
parameter_list|,
name|void
modifier|*
name|serial
parameter_list|)
function_decl|;
comment|/* output must be a preallocated area large enough to hold the       deserialized struct. */
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
comment|/* __GSERIALIZE_H__*/
end_comment

end_unit

