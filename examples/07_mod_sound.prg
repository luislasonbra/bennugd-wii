#ifndef OS_WII
import "mod_say";
import "mod_sound";
import "mod_joy";
#endif

Process main()
Private
	int song=0, fd=0;
	string fname="game.s3m";
Begin
	say("Going to play "+fname+", hope you like it :)");
	say("Press (A) in you Wiimote to quit.");
	song = load_song(fname);
	play_song(song, 0);
	say("Playing sound @ "+SOUND_FREQ+"Hz");
	while(is_playing_song() && !joy_getbutton(0, 0))
		FRAME;
	end;
	stop_song();
	unload_song(song);
	say("Quitting...");
End;
