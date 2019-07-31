# Introspectable sources for libgimp and libgimpui

PDB_WRAPPERS_C = \
	$(top_srcdir)/libgimp/gimp_pdb.c			\
	$(top_srcdir)/libgimp/gimpbrush_pdb.c			\
	$(top_srcdir)/libgimp/gimpbrushes_pdb.c			\
	$(top_srcdir)/libgimp/gimpbrushselect_pdb.c		\
	$(top_srcdir)/libgimp/gimpbuffer_pdb.c			\
	$(top_srcdir)/libgimp/gimpchannel_pdb.c			\
	$(top_srcdir)/libgimp/gimpcontext_pdb.c			\
	$(top_srcdir)/libgimp/gimpdebug_pdb.c			\
	$(top_srcdir)/libgimp/gimpdisplay_pdb.c			\
	$(top_srcdir)/libgimp/gimpdrawable_pdb.c		\
	$(top_srcdir)/libgimp/gimpdrawablecolor_pdb.c		\
	$(top_srcdir)/libgimp/gimpdrawableedit_pdb.c		\
	$(top_srcdir)/libgimp/gimpdynamics_pdb.c		\
	$(top_srcdir)/libgimp/gimpedit_pdb.c			\
	$(top_srcdir)/libgimp/gimpfileops_pdb.c			\
	$(top_srcdir)/libgimp/gimpfloatingsel_pdb.c		\
	$(top_srcdir)/libgimp/gimpfonts_pdb.c			\
	$(top_srcdir)/libgimp/gimpfontselect_pdb.c		\
	$(top_srcdir)/libgimp/gimpgimprc_pdb.c			\
	$(top_srcdir)/libgimp/gimpgradient_pdb.c		\
	$(top_srcdir)/libgimp/gimpgradients_pdb.c		\
	$(top_srcdir)/libgimp/gimpgradientselect_pdb.c		\
	$(top_srcdir)/libgimp/gimphelp_pdb.c			\
	$(top_srcdir)/libgimp/gimpimage_pdb.c			\
	$(top_srcdir)/libgimp/gimpimagecolorprofile_pdb.c	\
	$(top_srcdir)/libgimp/gimpimageconvert_pdb.c		\
	$(top_srcdir)/libgimp/gimpimagegrid_pdb.c		\
	$(top_srcdir)/libgimp/gimpimageguides_pdb.c		\
	$(top_srcdir)/libgimp/gimpimagesamplepoints_pdb.c	\
	$(top_srcdir)/libgimp/gimpimageselect_pdb.c		\
	$(top_srcdir)/libgimp/gimpimagetransform_pdb.c		\
	$(top_srcdir)/libgimp/gimpimageundo_pdb.c		\
	$(top_srcdir)/libgimp/gimpitem_pdb.c			\
	$(top_srcdir)/libgimp/gimpitemtransform_pdb.c		\
	$(top_srcdir)/libgimp/gimplayer_pdb.c			\
	$(top_srcdir)/libgimp/gimpmessage_pdb.c			\
	$(top_srcdir)/libgimp/gimppainttools_pdb.c		\
	$(top_srcdir)/libgimp/gimppalette_pdb.c			\
	$(top_srcdir)/libgimp/gimppalettes_pdb.c		\
	$(top_srcdir)/libgimp/gimppaletteselect_pdb.c		\
	$(top_srcdir)/libgimp/gimppattern_pdb.c			\
	$(top_srcdir)/libgimp/gimppatterns_pdb.c		\
	$(top_srcdir)/libgimp/gimppatternselect_pdb.c		\
	$(top_srcdir)/libgimp/gimpplugin_pdb.c			\
	$(top_srcdir)/libgimp/gimpproceduraldb_pdb.c		\
	$(top_srcdir)/libgimp/gimpprogress_pdb.c		\
	$(top_srcdir)/libgimp/gimpselection_pdb.c		\
	$(top_srcdir)/libgimp/gimptextlayer_pdb.c		\
	$(top_srcdir)/libgimp/gimptexttool_pdb.c		\
	$(top_srcdir)/libgimp/gimpunit_pdb.c			\
	$(top_srcdir)/libgimp/gimpvectors_pdb.c

PDB_WRAPPERS_H = \
	$(top_srcdir)/libgimp/gimp_pdb_headers.h		\
	$(top_srcdir)/libgimp/gimp_pdb.h			\
	$(top_srcdir)/libgimp/gimpbrush_pdb.h			\
	$(top_srcdir)/libgimp/gimpbrushes_pdb.h			\
	$(top_srcdir)/libgimp/gimpbrushselect_pdb.h		\
	$(top_srcdir)/libgimp/gimpbuffer_pdb.h			\
	$(top_srcdir)/libgimp/gimpchannel_pdb.h			\
	$(top_srcdir)/libgimp/gimpcontext_pdb.h			\
	$(top_srcdir)/libgimp/gimpdebug_pdb.h			\
	$(top_srcdir)/libgimp/gimpdisplay_pdb.h			\
	$(top_srcdir)/libgimp/gimpdrawable_pdb.h		\
	$(top_srcdir)/libgimp/gimpdrawablecolor_pdb.h		\
	$(top_srcdir)/libgimp/gimpdrawableedit_pdb.h		\
	$(top_srcdir)/libgimp/gimpdynamics_pdb.h		\
	$(top_srcdir)/libgimp/gimpedit_pdb.h			\
	$(top_srcdir)/libgimp/gimpfileops_pdb.h			\
	$(top_srcdir)/libgimp/gimpfloatingsel_pdb.h		\
	$(top_srcdir)/libgimp/gimpfonts_pdb.h			\
	$(top_srcdir)/libgimp/gimpfontselect_pdb.h		\
	$(top_srcdir)/libgimp/gimpgimprc_pdb.h			\
	$(top_srcdir)/libgimp/gimpgradient_pdb.h		\
	$(top_srcdir)/libgimp/gimpgradients_pdb.h		\
	$(top_srcdir)/libgimp/gimpgradientselect_pdb.h		\
	$(top_srcdir)/libgimp/gimphelp_pdb.h			\
	$(top_srcdir)/libgimp/gimpimage_pdb.h			\
	$(top_srcdir)/libgimp/gimpimagecolorprofile_pdb.h	\
	$(top_srcdir)/libgimp/gimpimageconvert_pdb.h		\
	$(top_srcdir)/libgimp/gimpimagegrid_pdb.h		\
	$(top_srcdir)/libgimp/gimpimageguides_pdb.h		\
	$(top_srcdir)/libgimp/gimpimagesamplepoints_pdb.h	\
	$(top_srcdir)/libgimp/gimpimageselect_pdb.h		\
	$(top_srcdir)/libgimp/gimpimagetransform_pdb.h		\
	$(top_srcdir)/libgimp/gimpimageundo_pdb.h		\
	$(top_srcdir)/libgimp/gimpitem_pdb.h			\
	$(top_srcdir)/libgimp/gimpitemtransform_pdb.h		\
	$(top_srcdir)/libgimp/gimplayer_pdb.h			\
	$(top_srcdir)/libgimp/gimpmessage_pdb.h			\
	$(top_srcdir)/libgimp/gimppainttools_pdb.h		\
	$(top_srcdir)/libgimp/gimppalette_pdb.h			\
	$(top_srcdir)/libgimp/gimppalettes_pdb.h		\
	$(top_srcdir)/libgimp/gimppaletteselect_pdb.h		\
	$(top_srcdir)/libgimp/gimppattern_pdb.h			\
	$(top_srcdir)/libgimp/gimppatterns_pdb.h		\
	$(top_srcdir)/libgimp/gimppatternselect_pdb.h		\
	$(top_srcdir)/libgimp/gimpplugin_pdb.h			\
	$(top_srcdir)/libgimp/gimpproceduraldb_pdb.h		\
	$(top_srcdir)/libgimp/gimpprogress_pdb.h		\
	$(top_srcdir)/libgimp/gimpselection_pdb.h		\
	$(top_srcdir)/libgimp/gimptextlayer_pdb.h		\
	$(top_srcdir)/libgimp/gimptexttool_pdb.h		\
	$(top_srcdir)/libgimp/gimpunit_pdb.h			\
	$(top_srcdir)/libgimp/gimpvectors_pdb.h

libgimp_introspectable = \
	$(top_srcdir)/libgimp/gimp.c			\
	$(top_srcdir)/libgimp/gimp.h			\
	$(top_srcdir)/libgimp/gimptypes.h		\
	$(top_srcdir)/libgimp/gimpenums.h		\
	${PDB_WRAPPERS_C}				\
	${PDB_WRAPPERS_H}				\
	$(top_srcdir)/libgimp/gimpbrushselect.c		\
	$(top_srcdir)/libgimp/gimpbrushselect.h		\
	$(top_srcdir)/libgimp/gimpchannel.c		\
	$(top_srcdir)/libgimp/gimpchannel.h		\
	$(top_srcdir)/libgimp/gimpdrawable.c		\
	$(top_srcdir)/libgimp/gimpdrawable.h		\
	$(top_srcdir)/libgimp/gimpfontselect.c		\
	$(top_srcdir)/libgimp/gimpfontselect.h		\
	$(top_srcdir)/libgimp/gimpgimprc.c		\
	$(top_srcdir)/libgimp/gimpgimprc.h		\
	$(top_srcdir)/libgimp/gimpgradientselect.c	\
	$(top_srcdir)/libgimp/gimpgradientselect.h	\
	$(top_srcdir)/libgimp/gimpimage.c		\
	$(top_srcdir)/libgimp/gimpimage.h		\
	$(top_srcdir)/libgimp/gimpimagecolorprofile.c	\
	$(top_srcdir)/libgimp/gimpimagecolorprofile.h	\
	$(top_srcdir)/libgimp/gimplayer.c		\
	$(top_srcdir)/libgimp/gimplayer.h		\
	$(top_srcdir)/libgimp/gimppaletteselect.c	\
	$(top_srcdir)/libgimp/gimppaletteselect.h	\
	$(top_srcdir)/libgimp/gimpparamspecs.c		\
	$(top_srcdir)/libgimp/gimpparamspecs.h		\
	$(top_srcdir)/libgimp/gimppatternselect.c	\
	$(top_srcdir)/libgimp/gimppatternselect.h	\
	$(top_srcdir)/libgimp/gimppixbuf.c		\
	$(top_srcdir)/libgimp/gimppixbuf.h		\
	$(top_srcdir)/libgimp/gimpplugin.c		\
	$(top_srcdir)/libgimp/gimpplugin.h		\
	$(top_srcdir)/libgimp/gimpproceduraldb.c	\
	$(top_srcdir)/libgimp/gimpproceduraldb.h	\
	$(top_srcdir)/libgimp/gimpprocedure.c		\
	$(top_srcdir)/libgimp/gimpprocedure.h		\
	$(top_srcdir)/libgimp/gimpprogress.c		\
	$(top_srcdir)/libgimp/gimpprogress.h		\
	$(top_srcdir)/libgimp/gimpselection.c		\
	$(top_srcdir)/libgimp/gimpselection.h		\
	\
	$(top_srcdir)/libgimp/gimplegacy.c		\
	$(top_srcdir)/libgimp/gimplegacy.h

# Let's keep gimplegacy as introspectable until we figure out how to use
# the new GimpPlugIn API in bindings. TODO: remove later and put back
# into libgimp_private_sources.

libgimpui_introspectable =				\
	$(top_srcdir)/libgimp/gimpui.c			\
	$(top_srcdir)/libgimp/gimpui.h			\
	$(top_srcdir)/libgimp/gimpuitypes.h		\
	$(top_srcdir)/libgimp/gimpaspectpreview.c     	\
	$(top_srcdir)/libgimp/gimpaspectpreview.h     	\
	$(top_srcdir)/libgimp/gimpbrushselectbutton.c	\
	$(top_srcdir)/libgimp/gimpbrushselectbutton.h	\
	$(top_srcdir)/libgimp/gimpdrawablepreview.c	\
	$(top_srcdir)/libgimp/gimpdrawablepreview.h	\
	$(top_srcdir)/libgimp/gimpexport.c		\
	$(top_srcdir)/libgimp/gimpexport.h		\
	$(top_srcdir)/libgimp/gimpfontselectbutton.c	\
	$(top_srcdir)/libgimp/gimpfontselectbutton.h	\
	$(top_srcdir)/libgimp/gimpgradientselectbutton.c\
	$(top_srcdir)/libgimp/gimpgradientselectbutton.h\
	$(top_srcdir)/libgimp/gimpimagecombobox.c	\
	$(top_srcdir)/libgimp/gimpimagecombobox.h	\
	$(top_srcdir)/libgimp/gimpimagemetadata.c	\
	$(top_srcdir)/libgimp/gimpimagemetadata.h	\
	$(top_srcdir)/libgimp/gimpitemcombobox.c	\
	$(top_srcdir)/libgimp/gimpitemcombobox.h	\
	$(top_srcdir)/libgimp/gimppaletteselectbutton.c	\
	$(top_srcdir)/libgimp/gimppaletteselectbutton.h	\
	$(top_srcdir)/libgimp/gimppatternselectbutton.c	\
	$(top_srcdir)/libgimp/gimppatternselectbutton.h	\
	$(top_srcdir)/libgimp/gimpprocbrowserdialog.c	\
	$(top_srcdir)/libgimp/gimpprocbrowserdialog.h	\
	$(top_srcdir)/libgimp/gimpprocview.c		\
	$(top_srcdir)/libgimp/gimpprocview.h		\
	$(top_srcdir)/libgimp/gimpprogressbar.c		\
	$(top_srcdir)/libgimp/gimpprogressbar.h		\
	$(top_srcdir)/libgimp/gimpselectbutton.c	\
	$(top_srcdir)/libgimp/gimpselectbutton.h	\
	$(top_srcdir)/libgimp/gimpzoompreview.c		\
	$(top_srcdir)/libgimp/gimpzoompreview.h
