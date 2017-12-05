begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpfilter.h  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_FILTER_H__
end_ifndef

begin_define
DECL|macro|__GIMP_FILTER_H__
define|#
directive|define
name|__GIMP_FILTER_H__
end_define

begin_include
include|#
directive|include
file|"gimpviewable.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_FILTER
define|#
directive|define
name|GIMP_TYPE_FILTER
value|(gimp_filter_get_type ())
end_define

begin_define
DECL|macro|GIMP_FILTER (obj)
define|#
directive|define
name|GIMP_FILTER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_FILTER, GimpFilter))
end_define

begin_define
DECL|macro|GIMP_FILTER_CLASS (klass)
define|#
directive|define
name|GIMP_FILTER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_FILTER, GimpFilterClass))
end_define

begin_define
DECL|macro|GIMP_IS_FILTER (obj)
define|#
directive|define
name|GIMP_IS_FILTER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_FILTER))
end_define

begin_define
DECL|macro|GIMP_IS_FILTER_CLASS (klass)
define|#
directive|define
name|GIMP_IS_FILTER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_FILTER))
end_define

begin_define
DECL|macro|GIMP_FILTER_GET_CLASS (obj)
define|#
directive|define
name|GIMP_FILTER_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_FILTER, GimpFilterClass))
end_define

begin_typedef
DECL|typedef|GimpFilterClass
typedef|typedef
name|struct
name|_GimpFilterClass
name|GimpFilterClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpFilter
struct|struct
name|_GimpFilter
block|{
DECL|member|parent_instance
name|GimpViewable
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpFilterClass
struct|struct
name|_GimpFilterClass
block|{
DECL|member|parent_class
name|GimpViewableClass
name|parent_class
decl_stmt|;
comment|/*  signals  */
DECL|member|active_changed
name|void
function_decl|(
modifier|*
name|active_changed
function_decl|)
parameter_list|(
name|GimpFilter
modifier|*
name|filter
parameter_list|)
function_decl|;
comment|/*  virtual functions  */
DECL|member|get_node
name|GeglNode
modifier|*
function_decl|(
modifier|*
name|get_node
function_decl|)
parameter_list|(
name|GimpFilter
modifier|*
name|filter
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_filter_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpFilter
modifier|*
name|gimp_filter_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GeglNode
modifier|*
name|gimp_filter_get_node
parameter_list|(
name|GimpFilter
modifier|*
name|filter
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GeglNode
modifier|*
name|gimp_filter_peek_node
parameter_list|(
name|GimpFilter
modifier|*
name|filter
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_filter_set_active
parameter_list|(
name|GimpFilter
modifier|*
name|filter
parameter_list|,
name|gboolean
name|active
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_filter_get_active
parameter_list|(
name|GimpFilter
modifier|*
name|filter
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_filter_is_active
parameter_list|(
name|GimpFilter
modifier|*
name|filter
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_filter_set_is_last_node
parameter_list|(
name|GimpFilter
modifier|*
name|filter
parameter_list|,
name|gboolean
name|is_last_node
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_filter_get_is_last_node
parameter_list|(
name|GimpFilter
modifier|*
name|filter
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_filter_set_applicator
parameter_list|(
name|GimpFilter
modifier|*
name|filter
parameter_list|,
name|GimpApplicator
modifier|*
name|applicator
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpApplicator
modifier|*
name|gimp_filter_get_applicator
parameter_list|(
name|GimpFilter
modifier|*
name|filter
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_FILTER_H__ */
end_comment

end_unit

