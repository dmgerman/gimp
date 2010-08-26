begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpcontroller.h  * Copyright (C) 2004 Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|GIMP_ENABLE_CONTROLLER_UNDER_CONSTRUCTION
end_ifndef

begin_error
error|#
directive|error
error|GimpController is unstable API under construction
end_error

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CONTROLLER_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CONTROLLER_H__
define|#
directive|define
name|__GIMP_CONTROLLER_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look at the html documentation */
end_comment

begin_comment
comment|/**  * GimpControllerEventType:  * @GIMP_CONTROLLER_EVENT_TRIGGER: the event is a simple trigger  * @GIMP_CONTROLLER_EVENT_VALUE:   the event carries a double value  *  * Event types for #GimpController.  **/
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b4a62d00103
block|{
DECL|enumerator|GIMP_CONTROLLER_EVENT_TRIGGER
name|GIMP_CONTROLLER_EVENT_TRIGGER
block|,
DECL|enumerator|GIMP_CONTROLLER_EVENT_VALUE
name|GIMP_CONTROLLER_EVENT_VALUE
DECL|typedef|GimpControllerEventType
block|}
name|GimpControllerEventType
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpControllerEventAny
typedef|typedef
name|struct
name|_GimpControllerEventAny
name|GimpControllerEventAny
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpControllerEventTrigger
typedef|typedef
name|struct
name|_GimpControllerEventTrigger
name|GimpControllerEventTrigger
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpControllerEventValue
typedef|typedef
name|struct
name|_GimpControllerEventValue
name|GimpControllerEventValue
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpControllerEvent
typedef|typedef
name|union
name|_GimpControllerEvent
name|GimpControllerEvent
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpControllerEventAny
struct|struct
name|_GimpControllerEventAny
block|{
DECL|member|type
name|GimpControllerEventType
name|type
decl_stmt|;
DECL|member|source
name|GimpController
modifier|*
name|source
decl_stmt|;
DECL|member|event_id
name|gint
name|event_id
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpControllerEventTrigger
struct|struct
name|_GimpControllerEventTrigger
block|{
DECL|member|type
name|GimpControllerEventType
name|type
decl_stmt|;
DECL|member|source
name|GimpController
modifier|*
name|source
decl_stmt|;
DECL|member|event_id
name|gint
name|event_id
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpControllerEventValue
struct|struct
name|_GimpControllerEventValue
block|{
DECL|member|type
name|GimpControllerEventType
name|type
decl_stmt|;
DECL|member|source
name|GimpController
modifier|*
name|source
decl_stmt|;
DECL|member|event_id
name|gint
name|event_id
decl_stmt|;
DECL|member|value
name|GValue
name|value
decl_stmt|;
block|}
struct|;
end_struct

begin_union
DECL|union|_GimpControllerEvent
union|union
name|_GimpControllerEvent
block|{
DECL|member|type
name|GimpControllerEventType
name|type
decl_stmt|;
DECL|member|any
name|GimpControllerEventAny
name|any
decl_stmt|;
DECL|member|trigger
name|GimpControllerEventTrigger
name|trigger
decl_stmt|;
DECL|member|value
name|GimpControllerEventValue
name|value
decl_stmt|;
block|}
union|;
end_union

begin_define
DECL|macro|GIMP_TYPE_CONTROLLER
define|#
directive|define
name|GIMP_TYPE_CONTROLLER
value|(gimp_controller_get_type ())
end_define

begin_define
DECL|macro|GIMP_CONTROLLER (obj)
define|#
directive|define
name|GIMP_CONTROLLER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CONTROLLER, GimpController))
end_define

begin_define
DECL|macro|GIMP_CONTROLLER_CLASS (klass)
define|#
directive|define
name|GIMP_CONTROLLER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CONTROLLER, GimpControllerClass))
end_define

begin_define
DECL|macro|GIMP_IS_CONTROLLER (obj)
define|#
directive|define
name|GIMP_IS_CONTROLLER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CONTROLLER))
end_define

begin_define
DECL|macro|GIMP_IS_CONTROLLER_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CONTROLLER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CONTROLLER))
end_define

begin_define
DECL|macro|GIMP_CONTROLLER_GET_CLASS (obj)
define|#
directive|define
name|GIMP_CONTROLLER_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_CONTROLLER, GimpControllerClass))
end_define

begin_typedef
DECL|typedef|GimpControllerClass
typedef|typedef
name|struct
name|_GimpControllerClass
name|GimpControllerClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpController
struct|struct
name|_GimpController
block|{
DECL|member|parent_instance
name|GObject
name|parent_instance
decl_stmt|;
DECL|member|name
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|member|state
name|gchar
modifier|*
name|state
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpControllerClass
struct|struct
name|_GimpControllerClass
block|{
DECL|member|parent_class
name|GObjectClass
name|parent_class
decl_stmt|;
DECL|member|name
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|member|help_domain
specifier|const
name|gchar
modifier|*
name|help_domain
decl_stmt|;
DECL|member|help_id
specifier|const
name|gchar
modifier|*
name|help_id
decl_stmt|;
comment|/*  virtual functions  */
DECL|member|get_n_events
name|gint
function_decl|(
modifier|*
name|get_n_events
function_decl|)
parameter_list|(
name|GimpController
modifier|*
name|controller
parameter_list|)
function_decl|;
DECL|member|get_event_name
specifier|const
name|gchar
modifier|*
function_decl|(
modifier|*
name|get_event_name
function_decl|)
parameter_list|(
name|GimpController
modifier|*
name|controller
parameter_list|,
name|gint
name|event_id
parameter_list|)
function_decl|;
DECL|member|get_event_blurb
specifier|const
name|gchar
modifier|*
function_decl|(
modifier|*
name|get_event_blurb
function_decl|)
parameter_list|(
name|GimpController
modifier|*
name|controller
parameter_list|,
name|gint
name|event_id
parameter_list|)
function_decl|;
comment|/*  signals  */
DECL|member|event
name|gboolean
function_decl|(
modifier|*
name|event
function_decl|)
parameter_list|(
name|GimpController
modifier|*
name|controller
parameter_list|,
specifier|const
name|GimpControllerEvent
modifier|*
name|event
parameter_list|)
function_decl|;
DECL|member|stock_id
specifier|const
name|gchar
modifier|*
name|stock_id
decl_stmt|;
comment|/* Padding for future expansion */
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
name|gimp_controller_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpController
modifier|*
name|gimp_controller_new
parameter_list|(
name|GType
name|controller_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_controller_get_n_events
parameter_list|(
name|GimpController
modifier|*
name|controller
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_controller_get_event_name
parameter_list|(
name|GimpController
modifier|*
name|controller
parameter_list|,
name|gint
name|event_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_controller_get_event_blurb
parameter_list|(
name|GimpController
modifier|*
name|controller
parameter_list|,
name|gint
name|event_id
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  protected  */
end_comment

begin_function_decl
name|gboolean
name|gimp_controller_event
parameter_list|(
name|GimpController
modifier|*
name|controller
parameter_list|,
specifier|const
name|GimpControllerEvent
modifier|*
name|event
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
comment|/* __GIMP_CONTROLLER_H__ */
end_comment

end_unit

