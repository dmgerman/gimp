#!/bin/sh

PACKAGE="gimp-script-fu"

if [ "x$1" = "x--help" ]; then

echo Usage: ./update.sh langcode
echo --help                  display this help and exit
echo
echo Examples of use:
echo ./update.sh ----- just creates a new pot file from the source
echo ./update.sh da -- created new pot file and updated the da.po file 

elif [ "x$1" = "x" ]; then 

echo "Building the $PACKAGE.pot ..."

xgettext --default-domain=$PACKAGE --directory=.. \
  --add-comments --keyword=_ --keyword=N_ \
  --files-from=./POTFILES.in \
&& ./script-fu-xgettext \
	../plug-ins/script-fu/scripts/*.scm \
        ../plug-ins/gap/sel-to-anim-img.scm \
        ../plug-ins/webbrowser/web-browser.scm \
        >> $PACKAGE.po \
&& test ! -f $PACKAGE.po \
   || ( rm -f ./$PACKAGE.pot \
&& mv $PACKAGE.po ./$PACKAGE.pot );

else

echo "Building the $PACKAGE.pot ..."

xgettext --default-domain=$PACKAGE --directory=.. \
  --add-comments --keyword=_ --keyword=N_ \
  --files-from=./POTFILES.in \
&& ./script-fu-xgettext \
	../plug-ins/script-fu/scripts/*.scm \
        ../plug-ins/gap/sel-to-anim-img.scm \
        ../plug-ins/webbrowser/web-browser.scm \
        >> $PACKAGE.po \
&& test ! -f $PACKAGE.po \
   || ( rm -f ./$PACKAGE.pot \
&& mv $PACKAGE.po ./$PACKAGE.pot );

echo "Now merging $1.po with $PACKAGE.pot, and creating an updated $1.po ..." 

mv $1.po $1.po.old && msgmerge $1.po.old $PACKAGE.pot -o $1.po \
&& rm $1.po.old;

msgfmt --statistics $1.po -o /dev/null

fi;
