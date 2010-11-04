begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* Lighting Effects - A plug-in for GIMP  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__LIGHTING_PREVIEW_H__
end_ifndef

begin_define
DECL|macro|__LIGHTING_PREVIEW_H__
define|#
directive|define
name|__LIGHTING_PREVIEW_H__
end_define

begin_define
DECL|macro|PREVIEW_WIDTH
define|#
directive|define
name|PREVIEW_WIDTH
value|200
end_define

begin_define
DECL|macro|PREVIEW_HEIGHT
define|#
directive|define
name|PREVIEW_HEIGHT
value|200
end_define

begin_comment
comment|/* Externally visible variables */
end_comment

begin_decl_stmt
specifier|extern
name|gdouble
modifier|*
name|xpostab
decl_stmt|,
modifier|*
name|ypostab
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* Externally visible functions */
end_comment

begin_function_decl
name|void
name|draw_preview_image
parameter_list|(
name|gboolean
name|recompute
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|interactive_preview_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|preview_events
parameter_list|(
name|GtkWidget
modifier|*
name|area
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|update_light
parameter_list|(
name|gint
name|xpos
parameter_list|,
name|gint
name|ypos
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __LIGHTING_PREVIEW_H__ */
end_comment

end_unit

