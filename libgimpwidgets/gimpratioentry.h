begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpratioentry.h  * Copyright (C) 2006  Simon Budig<simon@gimp.org>  * Copyright (C) 2007  Sven Neumann<sven@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_RATIO_ENTRY_H__
end_ifndef

begin_define
DECL|macro|__GIMP_RATIO_ENTRY_H__
define|#
directive|define
name|__GIMP_RATIO_ENTRY_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|GIMP_TYPE_RATIO_ENTRY
define|#
directive|define
name|GIMP_TYPE_RATIO_ENTRY
value|(gimp_ratio_entry_get_type ())
end_define

begin_define
DECL|macro|GIMP_RATIO_ENTRY (obj)
define|#
directive|define
name|GIMP_RATIO_ENTRY
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_RATIO_ENTRY, GimpRatioEntry))
end_define

begin_define
DECL|macro|GIMP_RATIO_ENTRY_CLASS (klass)
define|#
directive|define
name|GIMP_RATIO_ENTRY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_RATIO_ENTRY, GimpRatioEntryClass))
end_define

begin_define
DECL|macro|GIMP_IS_RATIO_ENTRY (obj)
define|#
directive|define
name|GIMP_IS_RATIO_ENTRY
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_RATIO_ENTRY))
end_define

begin_define
DECL|macro|GIMP_IS_RATIO_ENTRY_CLASS (klass)
define|#
directive|define
name|GIMP_IS_RATIO_ENTRY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_RATIO_ENTRY))
end_define

begin_define
DECL|macro|GIMP_RATIO_ENTRY_GET_CLASS (obj)
define|#
directive|define
name|GIMP_RATIO_ENTRY_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_RATIO_AREA, GimpRatioEntryClass))
end_define

begin_typedef
DECL|typedef|GimpRatioEntryClass
typedef|typedef
name|struct
name|_GimpRatioEntryClass
name|GimpRatioEntryClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpRatioEntry
struct|struct
name|_GimpRatioEntry
block|{
DECL|member|parent_instance
name|GtkEntry
name|parent_instance
decl_stmt|;
DECL|member|numerator
name|gdouble
name|numerator
decl_stmt|;
DECL|member|denominator
name|gdouble
name|denominator
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpRatioEntryClass
struct|struct
name|_GimpRatioEntryClass
block|{
DECL|member|parent_class
name|GtkEntryClass
name|parent_class
decl_stmt|;
DECL|member|history
name|GtkListStore
modifier|*
name|history
decl_stmt|;
DECL|member|ratio_changed
name|void
function_decl|(
modifier|*
name|ratio_changed
function_decl|)
parameter_list|(
name|GimpRatioEntry
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
name|gimp_ratio_entry_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_ratio_entry_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_ratio_entry_set_fraction
parameter_list|(
name|GimpRatioEntry
modifier|*
name|entry
parameter_list|,
name|gdouble
name|numerator
parameter_list|,
name|gdouble
name|denominator
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_ratio_entry_get_fraction
parameter_list|(
name|GimpRatioEntry
modifier|*
name|entry
parameter_list|,
name|gdouble
modifier|*
name|numerator
parameter_list|,
name|gdouble
modifier|*
name|denominator
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_ratio_entry_set_ratio
parameter_list|(
name|GimpRatioEntry
modifier|*
name|entry
parameter_list|,
name|gdouble
name|ratio
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_ratio_entry_get_ratio
parameter_list|(
name|GimpRatioEntry
modifier|*
name|entry
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_ratio_entry_set_aspect
parameter_list|(
name|GimpRatioEntry
modifier|*
name|entry
parameter_list|,
name|GimpAspectType
name|aspect
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpAspectType
name|gimp_ratio_entry_get_aspect
parameter_list|(
name|GimpRatioEntry
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
comment|/* __GIMP_RATIO_ENTRY_H__ */
end_comment

end_unit

