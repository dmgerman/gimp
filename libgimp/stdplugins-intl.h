begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_include
include|#
directive|include
file|<locale.h>
end_include

begin_ifndef
ifndef|#
directive|ifndef
name|LOCALEDIR
end_ifndef

begin_define
DECL|macro|LOCALEDIR
define|#
directive|define
name|LOCALEDIR
value|g_strconcat (gimp_data_directory (), \ 			       G_DIR_SEPARATOR_S, \ 			       "locale", \ 			       NULL)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_LC_MESSAGES
end_ifdef

begin_define
DECL|macro|INIT_I18N ()
define|#
directive|define
name|INIT_I18N
parameter_list|()
define|\
value|setlocale(LC_MESSAGES, ""); \   bindtextdomain("gimp-std-plugins", LOCALEDIR); \   textdomain("gimp-std-plugins")
end_define

begin_define
DECL|macro|INIT_I18N_UI ()
define|#
directive|define
name|INIT_I18N_UI
parameter_list|()
define|\
value|gtk_set_locale(); \   setlocale (LC_NUMERIC, "C"); \   INIT_I18N();
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|INIT_I18N ()
define|#
directive|define
name|INIT_I18N
parameter_list|()
define|\
value|bindtextdomain("gimp-std-plugins", LOCALEDIR); \   textdomain("gimp-std-plugins")
end_define

begin_define
DECL|macro|INIT_I18N_UI ()
define|#
directive|define
name|INIT_I18N_UI
parameter_list|()
define|\
value|gtk_set_locale(); \   setlocale (LC_NUMERIC, "C"); \   INIT_I18N();
end_define

begin_endif
endif|#
directive|endif
end_endif

end_unit

