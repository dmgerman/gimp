begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|LIGHTINGAPPLYH
end_ifndef

begin_define
DECL|macro|LIGHTINGAPPLYH
define|#
directive|define
name|LIGHTINGAPPLYH
end_define

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<math.h>
end_include

begin_include
include|#
directive|include
file|<gdk/gdk.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|<gck/gck.h>
end_include

begin_include
include|#
directive|include
file|"lighting_main.h"
end_include

begin_include
include|#
directive|include
file|"lighting_image.h"
end_include

begin_function_decl
specifier|extern
name|void
name|init_compute
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|compute_image
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

end_unit

