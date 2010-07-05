begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpratioentry.h  * Copyright (C) 2006  Simon Budig<simon@gimp.org>  * Copyright (C) 2007  Sven Neumann<sven@gimp.org>  * Copyright (C) 2007  Martin Nordholts<martin@svn.gnome.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_NUMBER_PAIR_ENTRY_H__
end_ifndef

begin_define
DECL|macro|__GIMP_NUMBER_PAIR_ENTRY_H__
define|#
directive|define
name|__GIMP_NUMBER_PAIR_ENTRY_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|GIMP_TYPE_NUMBER_PAIR_ENTRY
define|#
directive|define
name|GIMP_TYPE_NUMBER_PAIR_ENTRY
value|(gimp_number_pair_entry_get_type ())
end_define

begin_define
DECL|macro|GIMP_NUMBER_PAIR_ENTRY (obj)
define|#
directive|define
name|GIMP_NUMBER_PAIR_ENTRY
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_NUMBER_PAIR_ENTRY, GimpNumberPairEntry))
end_define

begin_define
DECL|macro|GIMP_NUMBER_PAIR_ENTRY_CLASS (klass)
define|#
directive|define
name|GIMP_NUMBER_PAIR_ENTRY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_NUMBER_PAIR_ENTRY, GimpNumberPairEntryClass))
end_define

begin_define
DECL|macro|GIMP_IS_NUMBER_PAIR_ENTRY (obj)
define|#
directive|define
name|GIMP_IS_NUMBER_PAIR_ENTRY
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_NUMBER_PAIR_ENTRY))
end_define

begin_define
DECL|macro|GIMP_IS_NUMBER_PAIR_ENTRY_CLASS (klass)
define|#
directive|define
name|GIMP_IS_NUMBER_PAIR_ENTRY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_NUMBER_PAIR_ENTRY))
end_define

begin_define
DECL|macro|GIMP_NUMBER_PAIR_ENTRY_GET_CLASS (obj)
define|#
directive|define
name|GIMP_NUMBER_PAIR_ENTRY_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_NUMBER_PAIR_AREA, GimpNumberPairEntryClass))
end_define

begin_typedef
DECL|typedef|GimpNumberPairEntryClass
typedef|typedef
name|struct
name|_GimpNumberPairEntryClass
name|GimpNumberPairEntryClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpNumberPairEntry
struct|struct
name|_GimpNumberPairEntry
block|{
DECL|member|parent_instance
name|GtkEntry
name|parent_instance
decl_stmt|;
DECL|member|priv
name|gpointer
name|priv
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpNumberPairEntryClass
struct|struct
name|_GimpNumberPairEntryClass
block|{
DECL|member|parent_class
name|GtkEntryClass
name|parent_class
decl_stmt|;
DECL|member|numbers_changed
name|void
function_decl|(
modifier|*
name|numbers_changed
function_decl|)
parameter_list|(
name|GimpNumberPairEntry
modifier|*
name|entry
parameter_list|)
function_decl|;
DECL|member|ratio_changed
name|void
function_decl|(
modifier|*
name|ratio_changed
function_decl|)
parameter_list|(
name|GimpNumberPairEntry
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
name|gimp_number_pair_entry_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_number_pair_entry_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|separators
parameter_list|,
name|gboolean
name|allow_simplification
parameter_list|,
name|gdouble
name|min_valid_value
parameter_list|,
name|gdouble
name|max_valid_value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_number_pair_entry_set_default_values
parameter_list|(
name|GimpNumberPairEntry
modifier|*
name|entry
parameter_list|,
name|gdouble
name|left
parameter_list|,
name|gdouble
name|right
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_number_pair_entry_get_default_values
parameter_list|(
name|GimpNumberPairEntry
modifier|*
name|entry
parameter_list|,
name|gdouble
modifier|*
name|left
parameter_list|,
name|gdouble
modifier|*
name|right
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_number_pair_entry_set_values
parameter_list|(
name|GimpNumberPairEntry
modifier|*
name|entry
parameter_list|,
name|gdouble
name|left
parameter_list|,
name|gdouble
name|right
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_number_pair_entry_get_values
parameter_list|(
name|GimpNumberPairEntry
modifier|*
name|entry
parameter_list|,
name|gdouble
modifier|*
name|left
parameter_list|,
name|gdouble
modifier|*
name|right
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_number_pair_entry_set_default_text
parameter_list|(
name|GimpNumberPairEntry
modifier|*
name|entry
parameter_list|,
specifier|const
name|gchar
modifier|*
name|string
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_number_pair_entry_get_default_text
parameter_list|(
name|GimpNumberPairEntry
modifier|*
name|entry
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_number_pair_entry_set_ratio
parameter_list|(
name|GimpNumberPairEntry
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
name|gimp_number_pair_entry_get_ratio
parameter_list|(
name|GimpNumberPairEntry
modifier|*
name|entry
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_number_pair_entry_set_aspect
parameter_list|(
name|GimpNumberPairEntry
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
name|gimp_number_pair_entry_get_aspect
parameter_list|(
name|GimpNumberPairEntry
modifier|*
name|entry
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_number_pair_entry_set_user_override
parameter_list|(
name|GimpNumberPairEntry
modifier|*
name|entry
parameter_list|,
name|gboolean
name|user_override
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_number_pair_entry_get_user_override
parameter_list|(
name|GimpNumberPairEntry
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
comment|/* __GIMP_NUMBER_PAIR_ENTRY_H__ */
end_comment

end_unit

