begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpmultiwindowstrategy.h  * Copyright (C) 2011 Martin Nordholts<martinn@src.gnome.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_MULTI_WINDOW_STRATEGY_H__
end_ifndef

begin_define
DECL|macro|__GIMP_MULTI_WINDOW_STRATEGY_H__
define|#
directive|define
name|__GIMP_MULTI_WINDOW_STRATEGY_H__
end_define

begin_include
include|#
directive|include
file|"core/gimpobject.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_MULTI_WINDOW_STRATEGY
define|#
directive|define
name|GIMP_TYPE_MULTI_WINDOW_STRATEGY
value|(gimp_multi_window_strategy_get_type ())
end_define

begin_define
DECL|macro|GIMP_MULTI_WINDOW_STRATEGY (obj)
define|#
directive|define
name|GIMP_MULTI_WINDOW_STRATEGY
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_MULTI_WINDOW_STRATEGY, GimpMultiWindowStrategy))
end_define

begin_define
DECL|macro|GIMP_MULTI_WINDOW_STRATEGY_CLASS (klass)
define|#
directive|define
name|GIMP_MULTI_WINDOW_STRATEGY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_MULTI_WINDOW_STRATEGY, GimpMultiWindowStrategyClass))
end_define

begin_define
DECL|macro|GIMP_IS_MULTI_WINDOW_STRATEGY (obj)
define|#
directive|define
name|GIMP_IS_MULTI_WINDOW_STRATEGY
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_MULTI_WINDOW_STRATEGY))
end_define

begin_define
DECL|macro|GIMP_IS_MULTI_WINDOW_STRATEGY_CLASS (klass)
define|#
directive|define
name|GIMP_IS_MULTI_WINDOW_STRATEGY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_MULTI_WINDOW_STRATEGY))
end_define

begin_define
DECL|macro|GIMP_MULTI_WINDOW_STRATEGY_GET_CLASS (obj)
define|#
directive|define
name|GIMP_MULTI_WINDOW_STRATEGY_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_MULTI_WINDOW_STRATEGY, GimpMultiWindowStrategyClass))
end_define

begin_typedef
DECL|typedef|GimpMultiWindowStrategyClass
typedef|typedef
name|struct
name|_GimpMultiWindowStrategyClass
name|GimpMultiWindowStrategyClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpMultiWindowStrategy
struct|struct
name|_GimpMultiWindowStrategy
block|{
DECL|member|parent_instance
name|GimpObject
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpMultiWindowStrategyClass
struct|struct
name|_GimpMultiWindowStrategyClass
block|{
DECL|member|parent_class
name|GimpObjectClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_multi_window_strategy_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpObject
modifier|*
name|gimp_multi_window_strategy_get_singleton
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_MULTI_WINDOW_STRATEGY_H__ */
end_comment

end_unit

