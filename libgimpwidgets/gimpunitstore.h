begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpunitstore.h  * Copyright (C) 2004  Sven Neumann<sven@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_if
if|#
directive|if
operator|!
name|defined
argument_list|(
name|__GIMP_WIDGETS_H_INSIDE__
argument_list|)
operator|&&
operator|!
name|defined
argument_list|(
name|GIMP_WIDGETS_COMPILATION
argument_list|)
end_if

begin_error
error|#
directive|error
literal|"Only<libgimpwidgets/gimpwidgets.h> can be included directly."
end_error

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_UNIT_STORE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_UNIT_STORE_H__
define|#
directive|define
name|__GIMP_UNIT_STORE_H__
end_define

begin_decl_stmt
name|G_BEGIN_DECLS
name|enum
DECL|enum|__anon27d31b300103
type|{
DECL|enumerator|GIMP_UNIT_STORE_UNIT
name|GIMP_UNIT_STORE_UNIT
decl_stmt|,
DECL|enumerator|GIMP_UNIT_STORE_UNIT_FACTOR
name|GIMP_UNIT_STORE_UNIT_FACTOR
decl_stmt|,
DECL|enumerator|GIMP_UNIT_STORE_UNIT_DIGITS
name|GIMP_UNIT_STORE_UNIT_DIGITS
decl_stmt|,
DECL|enumerator|GIMP_UNIT_STORE_UNIT_IDENTIFIER
name|GIMP_UNIT_STORE_UNIT_IDENTIFIER
decl_stmt|,
DECL|enumerator|GIMP_UNIT_STORE_UNIT_SYMBOL
name|GIMP_UNIT_STORE_UNIT_SYMBOL
decl_stmt|,
DECL|enumerator|GIMP_UNIT_STORE_UNIT_ABBREVIATION
name|GIMP_UNIT_STORE_UNIT_ABBREVIATION
decl_stmt|,
DECL|enumerator|GIMP_UNIT_STORE_UNIT_SINGULAR
name|GIMP_UNIT_STORE_UNIT_SINGULAR
decl_stmt|,
DECL|enumerator|GIMP_UNIT_STORE_UNIT_PLURAL
name|GIMP_UNIT_STORE_UNIT_PLURAL
decl_stmt|,
DECL|enumerator|GIMP_UNIT_STORE_UNIT_SHORT_FORMAT
name|GIMP_UNIT_STORE_UNIT_SHORT_FORMAT
decl_stmt|,
DECL|enumerator|GIMP_UNIT_STORE_UNIT_LONG_FORMAT
name|GIMP_UNIT_STORE_UNIT_LONG_FORMAT
decl_stmt|,
DECL|enumerator|GIMP_UNIT_STORE_UNIT_COLUMNS
name|GIMP_UNIT_STORE_UNIT_COLUMNS
decl_stmt|,
DECL|enumerator|GIMP_UNIT_STORE_FIRST_VALUE
name|GIMP_UNIT_STORE_FIRST_VALUE
init|=
name|GIMP_UNIT_STORE_UNIT_COLUMNS
end_decl_stmt

begin_define
unit|};
DECL|macro|GIMP_TYPE_UNIT_STORE
define|#
directive|define
name|GIMP_TYPE_UNIT_STORE
value|(gimp_unit_store_get_type ())
end_define

begin_define
DECL|macro|GIMP_UNIT_STORE (obj)
define|#
directive|define
name|GIMP_UNIT_STORE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_UNIT_STORE, GimpUnitStore))
end_define

begin_define
DECL|macro|GIMP_UNIT_STORE_CLASS (klass)
define|#
directive|define
name|GIMP_UNIT_STORE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_UNIT_STORE, GimpUnitStoreClass))
end_define

begin_define
DECL|macro|GIMP_IS_UNIT_STORE (obj)
define|#
directive|define
name|GIMP_IS_UNIT_STORE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_UNIT_STORE))
end_define

begin_define
DECL|macro|GIMP_IS_UNIT_STORE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_UNIT_STORE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_UNIT_STORE))
end_define

begin_define
DECL|macro|GIMP_UNIT_STORE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_UNIT_STORE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_UNIT_STORE, GimpUnitStoreClass))
end_define

begin_typedef
DECL|typedef|GimpUnitStorePrivate
typedef|typedef
name|struct
name|_GimpUnitStorePrivate
name|GimpUnitStorePrivate
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpUnitStoreClass
typedef|typedef
name|struct
name|_GimpUnitStoreClass
name|GimpUnitStoreClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpUnitStore
struct|struct
name|_GimpUnitStore
block|{
DECL|member|parent_instance
name|GObject
name|parent_instance
decl_stmt|;
DECL|member|priv
name|GimpUnitStorePrivate
modifier|*
name|priv
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpUnitStoreClass
struct|struct
name|_GimpUnitStoreClass
block|{
DECL|member|parent_class
name|GObjectClass
name|parent_class
decl_stmt|;
comment|/* Padding for future expansion */
DECL|member|_gimp_reserved1
name|void
function_decl|(
modifier|*
name|_gimp_reserved1
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved2
name|void
function_decl|(
modifier|*
name|_gimp_reserved2
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved3
name|void
function_decl|(
modifier|*
name|_gimp_reserved3
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved4
name|void
function_decl|(
modifier|*
name|_gimp_reserved4
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved5
name|void
function_decl|(
modifier|*
name|_gimp_reserved5
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved6
name|void
function_decl|(
modifier|*
name|_gimp_reserved6
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved7
name|void
function_decl|(
modifier|*
name|_gimp_reserved7
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved8
name|void
function_decl|(
modifier|*
name|_gimp_reserved8
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_unit_store_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpUnitStore
modifier|*
name|gimp_unit_store_new
parameter_list|(
name|gint
name|num_values
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_unit_store_set_has_pixels
parameter_list|(
name|GimpUnitStore
modifier|*
name|store
parameter_list|,
name|gboolean
name|has_pixels
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_unit_store_get_has_pixels
parameter_list|(
name|GimpUnitStore
modifier|*
name|store
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_unit_store_set_has_percent
parameter_list|(
name|GimpUnitStore
modifier|*
name|store
parameter_list|,
name|gboolean
name|has_percent
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_unit_store_get_has_percent
parameter_list|(
name|GimpUnitStore
modifier|*
name|store
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_unit_store_set_pixel_value
parameter_list|(
name|GimpUnitStore
modifier|*
name|store
parameter_list|,
name|gint
name|index
parameter_list|,
name|gdouble
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_unit_store_set_pixel_values
parameter_list|(
name|GimpUnitStore
modifier|*
name|store
parameter_list|,
name|gdouble
name|first_value
parameter_list|,
modifier|...
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_unit_store_set_resolution
parameter_list|(
name|GimpUnitStore
modifier|*
name|store
parameter_list|,
name|gint
name|index
parameter_list|,
name|gdouble
name|resolution
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_unit_store_set_resolutions
parameter_list|(
name|GimpUnitStore
modifier|*
name|store
parameter_list|,
name|gdouble
name|first_resolution
parameter_list|,
modifier|...
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_unit_store_get_value
parameter_list|(
name|GimpUnitStore
modifier|*
name|store
parameter_list|,
name|GimpUnit
name|unit
parameter_list|,
name|gint
name|index
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_unit_store_get_values
parameter_list|(
name|GimpUnitStore
modifier|*
name|store
parameter_list|,
name|GimpUnit
name|unit
parameter_list|,
name|gdouble
modifier|*
name|first_value
parameter_list|,
modifier|...
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|_gimp_unit_store_sync_units
parameter_list|(
name|GimpUnitStore
modifier|*
name|store
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_UNIT_STORE_H__ */
end_comment

end_unit

