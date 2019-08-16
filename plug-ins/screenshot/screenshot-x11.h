begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__SCREENSHOT_X11_H__
end_ifndef

begin_define
DECL|macro|__SCREENSHOT_X11_H__
define|#
directive|define
name|__SCREENSHOT_X11_H__
end_define

begin_ifdef
ifdef|#
directive|ifdef
name|GDK_WINDOWING_X11
end_ifdef

begin_function_decl
name|gboolean
name|screenshot_x11_available
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ScreenshotCapabilities
name|screenshot_x11_get_capabilities
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpPDBStatusType
name|screenshot_x11_shoot
parameter_list|(
name|ScreenshotValues
modifier|*
name|shootvals
parameter_list|,
name|GdkMonitor
modifier|*
name|monitor
parameter_list|,
name|GimpImage
modifier|*
modifier|*
name|image
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* GDK_WINDOWING_X11 */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __SCREENSHOT_X11_H__ */
end_comment

end_unit

