begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_decl_stmt
DECL|variable|msg
specifier|static
name|char
modifier|*
name|msg
index|[
literal|4
index|]
index|[
literal|104
index|]
init|=
block|{
comment|/* English messages */
block|{
literal|"OK"
block|,
literal|"Cancel"
block|,
literal|"Delete fractal"
block|,
literal|"Are you sure you want to delete"
block|,
literal|"\"%s\" from the list and from disk?"
block|,
literal|"Delete"
block|,
literal|"Error opening: %s"
block|,
literal|"File '%s' Not a FractalExplorer file"
block|,
literal|"File '%s' corrupt file - Line %d Option section incorrect"
block|,
literal|"Internal error - list item has null object!"
block|,
literal|"Unknown event\n"
block|,
literal|"Edit fractal name"
block|,
literal|"Fractal name:"
block|,
literal|"New fractal"
block|,
literal|"%s [copy]"
block|,
literal|"Save"
block|,
literal|"Save as..."
block|,
literal|"Copy"
block|,
literal|"Load"
block|,
literal|"No fractalexplorer-path in gimprc:\n"
literal|"You need to add an entry like\n"
literal|"(fractalexplorer-path \"${gimp_dir}/fractalexplorer:${gimp_data_dir}/fractalexplorer\n"
literal|"to your ~/.gimprc/gimprc file\n"
block|,
literal|"fractalexplorer-path miss-configured - \nPath `%.100s' not found\n"
block|,
literal|"Entry %.100s is not a directory\n"
block|,
literal|"error reading fractalexplorer directory \"%s\""
block|,
literal|"My first fractal"
block|,
literal|"Choose fractal by double-clicking on it"
block|,
literal|"Rescan"
block|,
literal|"Select directory and rescan collection"
block|,
literal|"New"
block|,
literal|"Create a new fractal for editing"
block|,
literal|"Rename"
block|,
literal|"Rename fractal in list"
block|,
literal|"Delete currently selected fractal"
block|,
literal|"Choose gradient by double-clicking on it"
block|,
literal|"Add FractalExplorer path"
block|,
literal|"Rescan for fractals"
block|,
literal|"Add dir"
block|,
literal|"Parameters"
block|,
literal|"Parameters"
block|,
literal|"Change the first (minimal) x-coordinate delimitation"
block|,
literal|"Change the second (maximal) x-coordinate delimitation"
block|,
literal|"Change the first (minimal) y-coordinate delimitation"
block|,
literal|"Change the second (maximal) y-coordinate delimitation"
block|,
literal|"Change the iteration value. The higher it is, the more details will be calculated, which will take more time."
block|,
literal|"Change the CX value (changes aspect of fractal, active with every fractal but Mandelbrot and Sierpinski)"
block|,
literal|"Change the CY value (changes aspect of fractal, active with every fractal but Mandelbrot and Sierpinski)"
block|,
literal|"Reset parameters to default values"
block|,
literal|"Load a fractal from file"
block|,
literal|"Save active fractal to file"
block|,
literal|"Fractal type"
block|,
literal|"Options"
block|,
literal|"Reset to default values"
block|,
literal|"Preview options"
block|,
literal|"Realtime preview"
block|,
literal|"If you enable this option the preview will be redrawn automatically."
block|,
literal|"Redraw"
block|,
literal|"Redraw preview"
block|,
literal|"Zoom options"
block|,
literal|"Undo zoom"
block|,
literal|"Undo last zoom"
block|,
literal|"Redo zoom"
block|,
literal|"Redo last zoom"
block|,
literal|"Step in"
block|,
literal|"Step out"
block|,
literal|"Colors"
block|,
literal|"Color density"
block|,
literal|"Red"
block|,
literal|"Green"
block|,
literal|"Blue"
block|,
literal|"Change the intensity of the red channel"
block|,
literal|"Change the intensity of the green channel"
block|,
literal|"Change the intensity of the blue channel"
block|,
literal|"Color function"
block|,
literal|"Sine"
block|,
literal|"Cosine"
block|,
literal|"None"
block|,
literal|"Use sine-function for this color component"
block|,
literal|"Use cosine-function for this color component"
block|,
literal|"Use linear mapping instead of any trigonometrical function for this color channel"
block|,
literal|"Inversion"
block|,
literal|"If you enable this option higher color values will be swapped with lower ones and vice versa."
block|,
literal|"Color mode"
block|,
literal|"As specified above"
block|,
literal|"Create a color-map with the options you specified above (color density/function). The result is visible in the preview image"
block|,
literal|"Apply active gradient to final image"
block|,
literal|"Create a color-map using a gradient from the gradient editor."
block|,
literal|"Gradients"
block|,
literal|"Fractals"
block|,
literal|"Accept settings and start the calculation of the fractal"
block|,
literal|"Discard any changes and close dialog box"
block|,
literal|"About"
block|,
literal|"Show information about the plug-in and the author"
block|,
literal|"This will close the information box"
block|,
literal|"Error opening '%.100s' could not save"
block|,
literal|"Failed to write file\n"
block|,
literal|"Save: No filename given"
block|,
literal|"Save: Can't save to a directory"
block|,
literal|"Load fractal parameters"
block|,
literal|"Click here to load your file."
block|,
literal|"Click here to cancel load procedure."
block|,
literal|"Save fractal parameters"
block|,
literal|"Click here to save your file."
block|,
literal|"Click here to cancel save procedure."
block|,
literal|"Save settings"
block|,
literal|"This saves the currently selected language to the configuration file"
block|, }
block|,
comment|/* Messages en français */
block|{
literal|"Accepter"
block|,
literal|"Annuler"
block|,
literal|"Effacer fractal"
block|,
literal|"Etes-vous sur de vouloir effacer le fichier"
block|,
literal|"\"%s\" de la liste est du disque?"
block|,
literal|"Effacer"
block|,
literal|"Erreur lors de l'ouverture du fichier: %s"
block|,
literal|"Le fichier '%s' ne correspond pas au format FractalExplorer!"
block|,
literal|"Le fichier '%s' est corrompu - Ligne %d incorrecte."
block|,
literal|"Erreur interne - l'élément de la liste contient un objet NULL!"
block|,
literal|"Evénement inconnu.\n"
block|,
literal|"Changer le nom du fractal"
block|,
literal|"Nom du fractal:"
block|,
literal|"Nouveau fractal"
block|,
literal|"%s [copie]"
block|,
literal|"Enregistrer"
block|,
literal|"Enregistrer sous..."
block|,
literal|"Copier"
block|,
literal|"Charger"
block|,
literal|"Aucun répertoire FractalExplorer inscrit dans gimprc:\n"
literal|"Vous devez aujouter une ligne telle que\n"
literal|"(fractalexplorer-path \"${gimp_dir}/fractalexplorer:${gimp_data_dir}/fractalexplorer\n"
literal|"dans votre fichier ~/.gimprc/gimprc\n"
block|,
literal|"fractalexplorer-path n'est pas configuré correctement - \nDossier `%.100s' introuvable.\n"
block|,
literal|"L'entrée %.100s n'est pas un répertoire.\n"
block|,
literal|"Erreur lors de la lecture du répertoire \"%s\"."
block|,
literal|"Mon premier fractal"
block|,
literal|"Choisissez un fractal en double-cliquant sur celui-ci"
block|,
literal|"Rafraîchir"
block|,
literal|"Choix du répertoire et rechargement de la collection."
block|,
literal|"Nouveau"
block|,
literal|"Créer nouveau fractal."
block|,
literal|"Renommer"
block|,
literal|"Renommer le fractal contenu dans la liste."
block|,
literal|"Efface le fractal actuellement selectioné dans la liste."
block|,
literal|"Choisissez un dégradé de couleurs avec un double-click"
block|,
literal|"Ajouter un dossier FractalExplorer."
block|,
literal|"Rechargement de nouveaux fractals."
block|,
literal|"Ajout de répertoires"
block|,
literal|"Paramètres"
block|,
literal|"Paramètres"
block|,
literal|"Change la première delimitation de l'axe x (delimitation minimale de x)."
block|,
literal|"Change la deuxième delimitation de l'axe x (delimitation maximale de x)."
block|,
literal|"Change la première delimitation de l'axe y (delimitation minimale de y)."
block|,
literal|"Change la deuxième delimitation de l'axe y (delimitation maximale de y)."
block|,
literal|"Change la valeur d'iteration. Une valeur plus haute rend l'image plus detailée, mais utilise plus de temps de calcul."
block|,
literal|"Change la valeur CX (cela change l'aspect du fractal; l'option n'est pas active pour les types de fractal Mandelbrot and Sierpinski)."
block|,
literal|"Change la valeur CY (cela change l'aspect du fractal; l'option n'est pas active pour les types de fractal Mandelbrot and Sierpinski)."
block|,
literal|"Remets tous les paramètres à leur valeur par défaut."
block|,
literal|"Charge un fractal à partir d'un fichier."
block|,
literal|"Enregistre un fractal dans un fichier."
block|,
literal|"Type de fractal"
block|,
literal|"Configuration"
block|,
literal|"Valeurs par défaut"
block|,
literal|"Prévisualisation"
block|,
literal|"En temps réel"
block|,
literal|"Si vous activez cette option, la fenêtre de prévisualisation sera automatiquement rafraîchie après chaque changement d'option."
block|,
literal|"Actualiser"
block|,
literal|"Actualise et redessine la prévisualisation."
block|,
literal|"Options de zoom"
block|,
literal|"Annuler zoom"
block|,
literal|"Ceci annule le dernier zoom."
block|,
literal|"Refaire zoom"
block|,
literal|"Ceci annule la dernière annulation du zoom."
block|,
literal|"Se rapprocher"
block|,
literal|"S'éloigner"
block|,
literal|"Couleurs"
block|,
literal|"Densité des valeurs RVB d'une couleur"
block|,
literal|"Rouge"
block|,
literal|"Vert"
block|,
literal|"Bleu"
block|,
literal|"Change l'intensité du canal rouge."
block|,
literal|"Change l'intensité du canal vert."
block|,
literal|"Change l'intensité du canal bleu."
block|,
literal|"Fonctions appliqués aux canaux RVB"
block|,
literal|"Sinus"
block|,
literal|"Cosinus"
block|,
literal|"Aucun"
block|,
literal|"Utilise la fonction trigonométrique 'sinus' pour le calcul de cette composante de couleur."
block|,
literal|"Utilise la fonction trigonométrique 'cosinus' pour le calcul de cette composante de couleur."
block|,
literal|"Utilise une fonction linéaire au lieu d'une fonction trigonométrique pour ce canal."
block|,
literal|"Inversion"
block|,
literal|"En activant cette option, vous assignez de grandes valeurs de couleurs aux couleurs ayant reçu des valeurs petites et vice versa."
block|,
literal|"Mode de couleur"
block|,
literal|"Comme specifié ci-dessus"
block|,
literal|"Crée une palette de couleur en utilisant les options que vous avez choisies ci-dessus (densité/fonction). Le résultat est visible dans l'image de prévisualisation."
block|,
literal|"Applique le dégradé de couleur actif"
block|,
literal|"Crée une palette en utilisant le dégradé de couleur du 'Gradient Editor'."
block|,
literal|"Dégradés"
block|,
literal|"Fractals"
block|,
literal|"Accepte les options et démarre la calculation du fractal."
block|,
literal|"Rejette tout changement et ferme la boîte de dialogue."
block|,
literal|"Info..."
block|,
literal|"Affiche des informations concernant l'auteur et le plug-in."
block|,
literal|"Ceci fermera la boîte de dialogue d'info."
block|,
literal|"Erreur lors de l'ouverture de '%.100s'. Sauvegarde echouée."
block|,
literal|"Ecriture du fichier impossible.\n"
block|,
literal|"Enregistrement: Aucun fichier specifié."
block|,
literal|"Enregistrement: Impossible de sauvegarder dans un répertoire."
block|,
literal|"Chargement des paramètres d'un fractal"
block|,
literal|"Cliquez ici afin de charger un fichier FractalExplorer."
block|,
literal|"Cliquez ici pour interrompre la procédure de chargement."
block|,
literal|"Enregistrement des paramètres d'un fractal"
block|,
literal|"Cliquez ici pour charger votre fichier."
block|,
literal|"Cliquez ici pour imterropre la procédure d'enregistrement."
block|,
literal|"Enregistrer langue"
block|,
literal|"Ceci enregistre la langue actuelle dans le fichier de configuration."
block|, }
block|,
comment|/* Deutsche Mitteilungen */
block|{
literal|"Weiter"
block|,
literal|"Abbrechen"
block|,
literal|"Fraktal löschen"
block|,
literal|"Sind sie sicher, dass sie die Datei"
block|,
literal|"\"%s\" aus der Liste und von der Festplatte entfernen möchten?"
block|,
literal|"Löschen"
block|,
literal|"Fehler beim Öffnen der Datei: %s"
block|,
literal|"Die Datei '%s' scheint nicht im FractalExplorer-Format zu sein!"
block|,
literal|"Die Datei '%s' ist beschädigt - Zeile %d inkorrekt."
block|,
literal|"Interner Fehler - das Listenelement besitzt ein NULL Objekt!"
block|,
literal|"Unbekanntes Ereignis.\n"
block|,
literal|"Ändere Fraktalnamen"
block|,
literal|"Fraktal-Name:"
block|,
literal|"Neues Fraktal"
block|,
literal|"%s [Kopie]"
block|,
literal|"Speichern"
block|,
literal|"Speichern als..."
block|,
literal|"Kopie"
block|,
literal|"Laden"
block|,
literal|"Kein fractalexplorer-path in gimprc:\n"
literal|"Sie müssen einen Eintrag wie der folgende in ihre ~/.gimprc/gimprc Datei einfügen:\n"
literal|"(fractalexplorer-path \"${gimp_dir}/fractalexplorer:${gimp_data_dir}/fractalexplorer\n"
block|,
literal|"fractalexplorer-path falsch konfiguriert - \nPfad `%.100s' nicht gefunden\n"
block|,
literal|"Eintrag %.100s ist kein Verzeichnis.\n"
block|,
literal|"Fehler beim Lesen des FractalExplorer-Verzeichnisses \"%s\"."
block|,
literal|"Mein erstes Fraktal"
block|,
literal|"Wählen Sie ein Fraktal durch Doppelklick aus"
block|,
literal|"Aktualisieren"
block|,
literal|"Wahl eines Verzeichnisses und Wiedereinlese der Dateisammlung."
block|,
literal|"Neu"
block|,
literal|"Erstellt ein neues Fraktal."
block|,
literal|"Umbenennen"
block|,
literal|"Benennt das Fraktal in der Liste um."
block|,
literal|"Löscht das gerade gewählte Fraktal der Liste."
block|,
literal|"Wählen Sie einen Farbverlauf durch Doppelklick aus"
block|,
literal|"Füge FractalExplorer-Pfad hinzu"
block|,
literal|"Nach neuen Fraktalen suchen"
block|,
literal|"Neues Verzeichis hinzufügen."
block|,
literal|"Fraktal-Optionen"
block|,
literal|"Parameter"
block|,
literal|"Ändert die erste (minimale) Begrenzung der x-Koordinate."
block|,
literal|"Ändert die zweite (maximale) Begrenzung der x-Koordinate."
block|,
literal|"Ändert die erste (minimale) Begrenzung der y-Koordinate."
block|,
literal|"Ändert die zweite (maximale) Begrenzung der y-Koordinate."
block|,
literal|"Ändert die Iterations-Variable. Je höher sie ist, um so genauer und detailierter wird das Bild sein. Eine grössere Berechenzeit ist allerdings in Kauf zu nehmen."
block|,
literal|"Ändert den CX-Wert (Dies wirkt sich auf alle Fraktale aus, ausser Mandelbrot und Sierpinski)."
block|,
literal|"Ändert den CY-Wert (Dies wirkt sich auf alle Fraktale aus, ausser Mandelbrot und Sierpinski)."
block|,
literal|"Setze Parameter auf die Standardwerte zurueck."
block|,
literal|"Lade ein Fraktal aus einer Datei"
block|,
literal|"Speichere das aktive Fraktal in eine Datei"
block|,
literal|"Fraktal-Typ"
block|,
literal|"Diverse Optionen"
block|,
literal|"Zurücksetzen"
block|,
literal|"Vorschau-Optionen"
block|,
literal|"Echtzeit-Vorschau"
block|,
literal|"Falls Sie diese Option aktivieren, wird das Vorschaufenster stets automatisch aktualisiert."
block|,
literal|"Neu zeichnen"
block|,
literal|"Zeichnet die Vorschau neu"
block|,
literal|"Zoom-Optionen"
block|,
literal|"Rueckgängig"
block|,
literal|"Macht den letzten Zoom-Vorgang wieder rückgängig."
block|,
literal|"Wiederherstellen"
block|,
literal|"Stellt den letzten Zoom-Vorgang wieder her."
block|,
literal|"Hinein"
block|,
literal|"Hinaus"
block|,
literal|"Farb-Optionen"
block|,
literal|"Farbintensität"
block|,
literal|"Rot"
block|,
literal|"Gruen"
block|,
literal|"Blau"
block|,
literal|"Ändert die Intensität des roten Kanals."
block|,
literal|"Ändert die Intensität des gruenen Kanals."
block|,
literal|"Ändert die Intensität des blauen Kanals."
block|,
literal|"Farb-Funktion"
block|,
literal|"Sinus"
block|,
literal|"Cosinus"
block|,
literal|"Keine"
block|,
literal|"Verwende Sinus-Funktion für diese Farbkomponente."
block|,
literal|"Verwende Cosinus-Funktion für diese Farbkomponente."
block|,
literal|"Verwende lineare Farbabstufung statt einer trigonometrischen Funktion."
block|,
literal|"Inversion"
block|,
literal|"Falls Sie diese Option aktivieren, werden tiefere Farbwerte durch höhere ausgetauscht und umgekehrt."
block|,
literal|"Farb-Modus"
block|,
literal|"Wie oben stehend angegeben"
block|,
literal|"Berechne Farbpalette mit den oben angegebenen Optionen (Farb-Intensität/-Funktion). Das Resultat ist in der Vorschau sichtbar."
block|,
literal|"Wende aktiven Farbverlauf an"
block|,
literal|"Berechne Farbpalette mit den Angaben eines Verlaufes aus dem Gradient-Editor."
block|,
literal|"Farbverläufe"
block|,
literal|"Fraktale"
block|,
literal|"Akzeptiere Einstellungen und starte die Berechnung des Fraktals."
block|,
literal|"Verwerfe jegliche Änderungen und schliesse das Fenster."
block|,
literal|"Über..."
block|,
literal|"Zeige Informationen über den Autor und das Plug-In."
block|,
literal|"Info-Box schliessen"
block|,
literal|"Fehler beim Öffnen von '%.100s'. Konnte nicht speichern"
block|,
literal|"Speichern der Datei fehlgeschlagen\n"
block|,
literal|"Speichern: Keine Datei angegeben"
block|,
literal|"Speichern: Kann nicht in ein Verzeichnis speichern"
block|,
literal|"Lade Parameter eines Fraktals"
block|,
literal|"Klicken Sie hier, um das Fraktal zu laden."
block|,
literal|"Klicken Sie hier, um den Ladevorgang abzubrechen."
block|,
literal|"Speichere Fraktalparameter"
block|,
literal|"Klicken Sie hier, um das Fraktal in eine Datei zu speichern."
block|,
literal|"Klicken Sie hier, um den Speicherungsvorgang abzubrechen."
block|,
literal|"Sprache abspeichern"
block|,
literal|"Klicken Sie hier, um die gewaehlte Sprache als Standard zu definieren und in die Konfigurationsdatei abzuspeichern."
block|, }
block|,
comment|/* Schwedische Mitteilungen     ========================    Hier koenntest Du die schwedischen Texte einfuegen, d.h. die deutschen ueberschreiben. */
block|{
literal|"Weiter"
block|,
literal|"Abbrechen"
block|,
literal|"Fraktal löschen"
block|,
literal|"Sind sie sicher, dass sie die Datei"
block|,
literal|"\"%s\" aus der Liste und von der Festplatte entfernen möchten?"
block|,
literal|"Löschen"
block|,
literal|"Fehler beim Öffnen der Datei: %s"
block|,
literal|"Die Datei '%s' scheint nicht im FractalExplorer-Format zu sein!"
block|,
literal|"Die Datei '%s' ist beschädigt - Zeile %d inkorrekt."
block|,
literal|"Interner Fehler - das Listenelement besitzt ein NULL Objekt!"
block|,
literal|"Unbekanntes Ereignis.\n"
block|,
literal|"Ändere Fraktalnamen"
block|,
literal|"Fraktal-Name:"
block|,
literal|"Neues Fraktal"
block|,
literal|"%s [Kopie]"
block|,
literal|"Speichern"
block|,
literal|"Speichern als..."
block|,
literal|"Kopie"
block|,
literal|"Laden"
block|,
literal|"Kein fractalexplorer-path in gimprc:\n"
literal|"Sie müssen einen Eintrag wie der folgende in ihre ~/.gimprc/gimprc Datei einfügen:\n"
literal|"(fractalexplorer-path \"${gimp_dir}/fractalexplorer:${gimp_data_dir}/fractalexplorer\n"
block|,
literal|"fractalexplorer-path falsch konfiguriert - \nPfad `%.100s' nicht gefunden\n"
block|,
literal|"Eintrag %.100s ist kein Verzeichnis.\n"
block|,
literal|"Fehler beim Lesen des FractalExplorer-Verzeichnisses \"%s\"."
block|,
literal|"Mein erstes Fraktal"
block|,
literal|"Wählen Sie ein Fraktal durch Doppelklick aus"
block|,
literal|"Aktualisieren"
block|,
literal|"Wahl eines Verzeichnisses und Wiedereinlese der Dateisammlung."
block|,
literal|"Neu"
block|,
literal|"Erstellt ein neues Fraktal."
block|,
literal|"Umbenennen"
block|,
literal|"Benennt das Fraktal in der Liste um."
block|,
literal|"Löscht das gerade gewählte Fraktal der Liste."
block|,
literal|"Wählen Sie einen Farbverlauf durch Doppelklick aus"
block|,
literal|"Füge FractalExplorer-Pfad hinzu"
block|,
literal|"Nach neuen Fraktalen suchen"
block|,
literal|"Neues Verzeichis hinzufügen."
block|,
literal|"Fraktal-Optionen"
block|,
literal|"Parameter"
block|,
literal|"Ändert die erste (minimale) Begrenzung der x-Koordinate."
block|,
literal|"Ändert die zweite (maximale) Begrenzung der x-Koordinate."
block|,
literal|"Ändert die erste (minimale) Begrenzung der y-Koordinate."
block|,
literal|"Ändert die zweite (maximale) Begrenzung der y-Koordinate."
block|,
literal|"Ändert die Iterations-Variable. Je höher sie ist, um so genauer und detailierter wird das Bild sein. Eine grössere Berechenzeit ist allerdings in Kauf zu nehmen."
block|,
literal|"Ändert den CX-Wert (Dies wirkt sich auf alle Fraktale aus, ausser Mandelbrot und Sierpinski)."
block|,
literal|"Ändert den CY-Wert (Dies wirkt sich auf alle Fraktale aus, ausser Mandelbrot und Sierpinski)."
block|,
literal|"Setze Parameter auf die Standardwerte zurueck."
block|,
literal|"Lade ein Fraktal aus einer Datei"
block|,
literal|"Speichere das aktive Fraktal in eine Datei"
block|,
literal|"Fraktal-Typ"
block|,
literal|"Diverse Optionen"
block|,
literal|"Zurücksetzen"
block|,
literal|"Vorschau-Optionen"
block|,
literal|"Echtzeit-Vorschau"
block|,
literal|"Falls Sie diese Option aktivieren, wird das Vorschaufenster stets automatisch aktualisiert."
block|,
literal|"Neu zeichnen"
block|,
literal|"Zeichnet die Vorschau neu"
block|,
literal|"Zoom-Optionen"
block|,
literal|"Rueckgängig"
block|,
literal|"Macht den letzten Zoom-Vorgang wieder rückgängig."
block|,
literal|"Wiederherstellen"
block|,
literal|"Stellt den letzten Zoom-Vorgang wieder her."
block|,
literal|"Hinein"
block|,
literal|"Hinaus"
block|,
literal|"Farb-Optionen"
block|,
literal|"Farbintensität"
block|,
literal|"Rot"
block|,
literal|"Gruen"
block|,
literal|"Blau"
block|,
literal|"Ändert die Intensität des roten Kanals."
block|,
literal|"Ändert die Intensität des gruenen Kanals."
block|,
literal|"Ändert die Intensität des blauen Kanals."
block|,
literal|"Farb-Funktion"
block|,
literal|"Sinus"
block|,
literal|"Cosinus"
block|,
literal|"Keine"
block|,
literal|"Verwende Sinus-Funktion für diese Farbkomponente."
block|,
literal|"Verwende Cosinus-Funktion für diese Farbkomponente."
block|,
literal|"Verwende lineare Farbabstufung statt einer trigonometrischen Funktion."
block|,
literal|"Inversion"
block|,
literal|"Falls Sie diese Option aktivieren, werden tiefere Farbwerte durch höhere ausgetauscht und umgekehrt."
block|,
literal|"Farb-Modus"
block|,
literal|"Wie oben stehend angegeben"
block|,
literal|"Berechne Farbpalette mit den oben angegebenen Optionen (Farb-Intensität/-Funktion). Das Resultat ist in der Vorschau sichtbar."
block|,
literal|"Wende aktiven Farbverlauf an"
block|,
literal|"Berechne Farbpalette mit den Angaben eines Verlaufes aus dem Gradient-Editor."
block|,
literal|"Farbverläufe"
block|,
literal|"Fraktale"
block|,
literal|"Akzeptiere Einstellungen und starte die Berechnung des Fraktals."
block|,
literal|"Verwerfe jegliche Änderungen und schliesse das Fenster."
block|,
literal|"Über..."
block|,
literal|"Zeige Informationen über den Autor und das Plug-In."
block|,
literal|"Info-Box schliessen"
block|,
literal|"Fehler beim Öffnen von '%.100s'. Konnte nicht speichern"
block|,
literal|"Speichern der Datei fehlgeschlagen\n"
block|,
literal|"Speichern: Keine Datei angegeben"
block|,
literal|"Speichern: Kann nicht in ein Verzeichnis speichern"
block|,
literal|"Lade Parameter eines Fraktals"
block|,
literal|"Klicken Sie hier, um das Fraktal zu laden."
block|,
literal|"Klicken Sie hier, um den Ladevorgang abzubrechen."
block|,
literal|"Speichere Fraktalparameter"
block|,
literal|"Klicken Sie hier, um das Fraktal in eine Datei zu speichern."
block|,
literal|"Klicken Sie hier, um den Speicherungsvorgang abzubrechen."
block|,
literal|"Sprache abspeichern"
block|,
literal|"Klicken Sie hier, um die gewaehlte Sprache als Standard zu definieren und in die Konfigurationsdatei abzuspeichern."
block|, }
block|,  }
decl_stmt|;
end_decl_stmt

begin_enum
DECL|enum|__anon29bd91840103
enum|enum
block|{
DECL|enumerator|MSG_OK
name|MSG_OK
block|,
DECL|enumerator|MSG_CANCEL
name|MSG_CANCEL
block|,
DECL|enumerator|MSG_DELFRAC
name|MSG_DELFRAC
block|,
DECL|enumerator|MSG_DELSURE
name|MSG_DELSURE
block|,
DECL|enumerator|MSG_DELSURE2
name|MSG_DELSURE2
block|,
DECL|enumerator|MSG_DEL
name|MSG_DEL
block|,
DECL|enumerator|MSG_OPENERROR
name|MSG_OPENERROR
block|,
DECL|enumerator|MSG_WRONGFILETYPE
name|MSG_WRONGFILETYPE
block|,
DECL|enumerator|MSG_CORRUPTFILE
name|MSG_CORRUPTFILE
block|,
DECL|enumerator|MSG_NULLLIST
name|MSG_NULLLIST
block|,
DECL|enumerator|MSG_UNKNOWN_EVENT
name|MSG_UNKNOWN_EVENT
block|,
DECL|enumerator|MSG_EDIT_FRACNAME
name|MSG_EDIT_FRACNAME
block|,
DECL|enumerator|MSG_FRACNAME
name|MSG_FRACNAME
block|,
DECL|enumerator|MSG_NEWFRAC
name|MSG_NEWFRAC
block|,
DECL|enumerator|MSG_COPYNAME
name|MSG_COPYNAME
block|,
DECL|enumerator|MSG_SAVE
name|MSG_SAVE
block|,
DECL|enumerator|MSG_SAVEAS
name|MSG_SAVEAS
block|,
DECL|enumerator|MSG_COPY
name|MSG_COPY
block|,
DECL|enumerator|MSG_LOAD
name|MSG_LOAD
block|,
DECL|enumerator|MSG_MISSING_GIMPRC
name|MSG_MISSING_GIMPRC
block|,
DECL|enumerator|MSG_WRONGPATH
name|MSG_WRONGPATH
block|,
DECL|enumerator|MSG_NOTDIR
name|MSG_NOTDIR
block|,
DECL|enumerator|MSG_DIRREADERROR
name|MSG_DIRREADERROR
block|,
DECL|enumerator|MSG_FIRSTFRACTAL
name|MSG_FIRSTFRACTAL
block|,
DECL|enumerator|MSG_CHOOSE_FRACTAL
name|MSG_CHOOSE_FRACTAL
block|,
DECL|enumerator|MSG_RESCAN
name|MSG_RESCAN
block|,
DECL|enumerator|MSG_RESCAN_COMMENT
name|MSG_RESCAN_COMMENT
block|,
DECL|enumerator|MSG_NEW
name|MSG_NEW
block|,
DECL|enumerator|MSG_NEW_COMMENT
name|MSG_NEW_COMMENT
block|,
DECL|enumerator|MSG_RENAME
name|MSG_RENAME
block|,
DECL|enumerator|MSG_RENAME_COMMENT
name|MSG_RENAME_COMMENT
block|,
DECL|enumerator|MSG_DELETE_COMMENT
name|MSG_DELETE_COMMENT
block|,
DECL|enumerator|MSG_CHOOSE_GRADIENT
name|MSG_CHOOSE_GRADIENT
block|,
DECL|enumerator|MSG_ADDPATH
name|MSG_ADDPATH
block|,
DECL|enumerator|MSG_RESCANTITLE1
name|MSG_RESCANTITLE1
block|,
DECL|enumerator|MSG_ADDDIR
name|MSG_ADDDIR
block|,
DECL|enumerator|MSG_FRACTALOPTIONS
name|MSG_FRACTALOPTIONS
block|,
DECL|enumerator|MSG_PARAMETERS
name|MSG_PARAMETERS
block|,
DECL|enumerator|MSG_XMIN
name|MSG_XMIN
block|,
DECL|enumerator|MSG_XMAX
name|MSG_XMAX
block|,
DECL|enumerator|MSG_YMIN
name|MSG_YMIN
block|,
DECL|enumerator|MSG_YMAX
name|MSG_YMAX
block|,
DECL|enumerator|MSG_ITER
name|MSG_ITER
block|,
DECL|enumerator|MSG_CX
name|MSG_CX
block|,
DECL|enumerator|MSG_CY
name|MSG_CY
block|,
DECL|enumerator|MSG_RESET_PARAM_COMMENT
name|MSG_RESET_PARAM_COMMENT
block|,
DECL|enumerator|MSG_LOADCOMMENT
name|MSG_LOADCOMMENT
block|,
DECL|enumerator|MSG_SAVECOMMENT
name|MSG_SAVECOMMENT
block|,
DECL|enumerator|MSG_FRACTALTYPE
name|MSG_FRACTALTYPE
block|,
DECL|enumerator|MSG_GENERALOPTIONS
name|MSG_GENERALOPTIONS
block|,
DECL|enumerator|MSG_RESET
name|MSG_RESET
block|,
DECL|enumerator|MSG_PREVIEW
name|MSG_PREVIEW
block|,
DECL|enumerator|MSG_REALTIMEPREVIEW
name|MSG_REALTIMEPREVIEW
block|,
DECL|enumerator|MSG_REDRAWCOMMENT
name|MSG_REDRAWCOMMENT
block|,
DECL|enumerator|MSG_REDRAW
name|MSG_REDRAW
block|,
DECL|enumerator|MSG_REDRAWPREVIEW
name|MSG_REDRAWPREVIEW
block|,
DECL|enumerator|MSG_ZOOMOPTS
name|MSG_ZOOMOPTS
block|,
DECL|enumerator|MSG_UNDOZOOM
name|MSG_UNDOZOOM
block|,
DECL|enumerator|MSG_UNDOCOMMENT
name|MSG_UNDOCOMMENT
block|,
DECL|enumerator|MSG_REDOZOOM
name|MSG_REDOZOOM
block|,
DECL|enumerator|MSG_REDOCOMMENT
name|MSG_REDOCOMMENT
block|,
DECL|enumerator|MSG_STEPIN
name|MSG_STEPIN
block|,
DECL|enumerator|MSG_STEPOUT
name|MSG_STEPOUT
block|,
DECL|enumerator|MSG_COLOROPTS
name|MSG_COLOROPTS
block|,
DECL|enumerator|MSG_COLORDENSITY
name|MSG_COLORDENSITY
block|,
DECL|enumerator|MSG_RED
name|MSG_RED
block|,
DECL|enumerator|MSG_GREEN
name|MSG_GREEN
block|,
DECL|enumerator|MSG_BLUE
name|MSG_BLUE
block|,
DECL|enumerator|MSG_REDINTENSITY
name|MSG_REDINTENSITY
block|,
DECL|enumerator|MSG_GREENINTENSITY
name|MSG_GREENINTENSITY
block|,
DECL|enumerator|MSG_BLUEINTENSITY
name|MSG_BLUEINTENSITY
block|,
DECL|enumerator|MSG_COLORFUNCTION
name|MSG_COLORFUNCTION
block|,
DECL|enumerator|MSG_SINE
name|MSG_SINE
block|,
DECL|enumerator|MSG_COSINE
name|MSG_COSINE
block|,
DECL|enumerator|MSG_NONE
name|MSG_NONE
block|,
DECL|enumerator|MSG_SINECOMMENT
name|MSG_SINECOMMENT
block|,
DECL|enumerator|MSG_COSINECOMMENT
name|MSG_COSINECOMMENT
block|,
DECL|enumerator|MSG_NONECOMMENT
name|MSG_NONECOMMENT
block|,
DECL|enumerator|MSG_INVERSION
name|MSG_INVERSION
block|,
DECL|enumerator|MSG_INVERSIONCOMMENT
name|MSG_INVERSIONCOMMENT
block|,
DECL|enumerator|MSG_COLORMODE
name|MSG_COLORMODE
block|,
DECL|enumerator|MSG_ASSPECIFIED
name|MSG_ASSPECIFIED
block|,
DECL|enumerator|MSG_ASSPECIFIEDCOMMENT
name|MSG_ASSPECIFIEDCOMMENT
block|,
DECL|enumerator|MSG_APPLYGRADIENT
name|MSG_APPLYGRADIENT
block|,
DECL|enumerator|MSG_APPLYGRADIENTCOMMENT
name|MSG_APPLYGRADIENTCOMMENT
block|,
DECL|enumerator|MSG_GRADIENTPRESETS
name|MSG_GRADIENTPRESETS
block|,
DECL|enumerator|MSG_FRACTALPRESETS
name|MSG_FRACTALPRESETS
block|,
DECL|enumerator|MSG_STARTCALC
name|MSG_STARTCALC
block|,
DECL|enumerator|MSG_MAINDLGCANCEL
name|MSG_MAINDLGCANCEL
block|,
DECL|enumerator|MSG_ABOUT
name|MSG_ABOUT
block|,
DECL|enumerator|MSG_ABOUTCOMMENT
name|MSG_ABOUTCOMMENT
block|,
DECL|enumerator|MSG_ABOUTBOXOKCOMMENT
name|MSG_ABOUTBOXOKCOMMENT
block|,
DECL|enumerator|MSG_SAVEERROR
name|MSG_SAVEERROR
block|,
DECL|enumerator|MSG_WRITEFAILURE
name|MSG_WRITEFAILURE
block|,
DECL|enumerator|MSG_NOFILENAME
name|MSG_NOFILENAME
block|,
DECL|enumerator|MSG_NOSAVETODIR
name|MSG_NOSAVETODIR
block|,
DECL|enumerator|MSG_LOADWINTITLE
name|MSG_LOADWINTITLE
block|,
DECL|enumerator|MSG_LOADBUTTONCOMMENT
name|MSG_LOADBUTTONCOMMENT
block|,
DECL|enumerator|MSG_CANCELLOAD
name|MSG_CANCELLOAD
block|,
DECL|enumerator|MSG_SAVEWINTITLE
name|MSG_SAVEWINTITLE
block|,
DECL|enumerator|MSG_SAVEBUTTONCOMMENT
name|MSG_SAVEBUTTONCOMMENT
block|,
DECL|enumerator|MSG_CANCELSAVE
name|MSG_CANCELSAVE
block|,
DECL|enumerator|MSG_SAVELANGUAGE
name|MSG_SAVELANGUAGE
block|,
DECL|enumerator|MSG_SAVELANGUAGE_COMMENT
name|MSG_SAVELANGUAGE_COMMENT
block|}
enum|;
end_enum

begin_enum
DECL|enum|__anon29bd91840203
enum|enum
block|{
DECL|enumerator|LNG_ENGLISH
name|LNG_ENGLISH
block|,
DECL|enumerator|LNG_FRENCH
name|LNG_FRENCH
block|,
DECL|enumerator|LNG_GERMAN
name|LNG_GERMAN
block|,
DECL|enumerator|LNG_ITALIAN
name|LNG_ITALIAN
block|,
DECL|enumerator|LNG_SPANISH
name|LNG_SPANISH
block|}
enum|;
end_enum

end_unit

