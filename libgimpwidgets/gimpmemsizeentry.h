begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpmemsizeentry.h  * Copyright (C) 2000-2003  Sven Neumann<sven@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_MEMSIZE_ENTRY_H__
end_ifndef

begin_define
DECL|macro|__GIMP_MEMSIZE_ENTRY_H__
define|#
directive|define
name|__GIMP_MEMSIZE_ENTRY_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|GIMP_TYPE_MEMSIZE_ENTRY
define|#
directive|define
name|GIMP_TYPE_MEMSIZE_ENTRY
value|(gimp_memsize_entry_get_type ())
end_define

begin_define
DECL|macro|GIMP_MEMSIZE_ENTRY (obj)
define|#
directive|define
name|GIMP_MEMSIZE_ENTRY
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_MEMSIZE_ENTRY, GimpMemsizeEntry))
end_define

begin_define
DECL|macro|GIMP_MEMSIZE_ENTRY_CLASS (klass)
define|#
directive|define
name|GIMP_MEMSIZE_ENTRY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_MEMSIZE_ENTRY, GimpMemsizeEntryClass))
end_define

begin_define
DECL|macro|GIMP_IS_MEMSIZE_ENTRY (obj)
define|#
directive|define
name|GIMP_IS_MEMSIZE_ENTRY
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_MEMSIZE_ENTRY))
end_define

begin_define
DECL|macro|GIMP_IS_MEMSIZE_ENTRY_CLASS (klass)
define|#
directive|define
name|GIMP_IS_MEMSIZE_ENTRY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_MEMSIZE_ENTRY))
end_define

begin_define
DECL|macro|GIMP_MEMSIZE_ENTRY_GET_CLASS (obj)
define|#
directive|define
name|GIMP_MEMSIZE_ENTRY_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_MEMSIZE_ENTRY, GimpMemsizeEntryClass))
end_define

begin_typedef
DECL|typedef|GimpMemsizeEntryClass
typedef|typedef
name|struct
name|_GimpMemsizeEntryClass
name|GimpMemsizeEntryClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpMemsizeEntry
struct|struct
name|_GimpMemsizeEntry
block|{
DECL|member|parent_instance
name|GtkHBox
name|parent_instance
decl_stmt|;
comment|/*< private>*/
DECL|member|value
name|guint64
name|value
decl_stmt|;
DECL|member|lower
name|guint64
name|lower
decl_stmt|;
DECL|member|upper
name|guint64
name|upper
decl_stmt|;
DECL|member|shift
name|guint
name|shift
decl_stmt|;
DECL|member|adjustment
name|GtkAdjustment
modifier|*
name|adjustment
decl_stmt|;
DECL|member|spinbutton
name|GtkWidget
modifier|*
name|spinbutton
decl_stmt|;
DECL|member|menu
name|GtkWidget
modifier|*
name|menu
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpMemsizeEntryClass
struct|struct
name|_GimpMemsizeEntryClass
block|{
DECL|member|parent_class
name|GtkHBoxClass
name|parent_class
decl_stmt|;
DECL|member|value_changed
name|void
function_decl|(
modifier|*
name|value_changed
function_decl|)
parameter_list|(
name|GimpMemsizeEntry
modifier|*
name|entry
parameter_list|)
function_decl|;
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
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_memsize_entry_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_memsize_entry_new
parameter_list|(
name|guint64
name|value
parameter_list|,
name|guint64
name|lower
parameter_list|,
name|guint64
name|upper
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_memsize_entry_set_value
parameter_list|(
name|GimpMemsizeEntry
modifier|*
name|entry
parameter_list|,
name|guint64
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|guint64
name|gimp_memsize_entry_get_value
parameter_list|(
name|GimpMemsizeEntry
modifier|*
name|entry
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
comment|/* __GIMP_MEMSIZE_ENTRY_H__ */
end_comment

end_unit

