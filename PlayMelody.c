/*****************************
 * Melody sound implement c file.
 *
 *
 ****************************/
void playMelody(){
	for (int thisNote = 0; thisNote < 8; thisNote++) {

    	// to calculate the note duration, take one second
    	// divided by the note type.
    	//e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    	int noteDuration = 1000/noteDurations[thisNote];
    	static int fre = melody[thisNote];

    	// to distinguish the notes, set a minimum time between them.
    	// the note's duration + 30% seems to work well:
    	int pauseBetweenNotes = noteDuration * 1.30;
    	// stop the tone playing:
  	}
}

