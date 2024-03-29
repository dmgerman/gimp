begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpplugin-private.h  * Copyright (C) 2019 Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PLUG_IN_PRIVATE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PLUG_IN_PRIVATE_H__
define|#
directive|define
name|__GIMP_PLUG_IN_PRIVATE_H__
end_define

begin_function_decl
name|G_BEGIN_DECLS
name|void
name|_gimp_plug_in_query
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|_gimp_plug_in_init
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|_gimp_plug_in_run
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|_gimp_plug_in_quit
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GIOChannel
modifier|*
name|_gimp_plug_in_get_read_channel
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GIOChannel
modifier|*
name|_gimp_plug_in_get_write_channel
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|_gimp_plug_in_read_expect_msg
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
name|GimpWireMessage
modifier|*
name|msg
parameter_list|,
name|gint
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpProcedure
modifier|*
name|_gimp_plug_in_create_procedure
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|procedure_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpProcedure
modifier|*
name|_gimp_plug_in_get_procedure
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpDisplay
modifier|*
name|_gimp_plug_in_get_display
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
name|gint32
name|display_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImage
modifier|*
name|_gimp_plug_in_get_image
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
name|gint32
name|image_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpItem
modifier|*
name|_gimp_plug_in_get_item
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
name|gint32
name|item_id
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
comment|/* __GIMP_PLUG_IN_PRIVATE_H__ */
end_comment

end_unit

