#ifdef NOWII
import "mod_say";
import "mod_sound";
#endif

Process main()
Private
	int song=0;
	string fname="song.ogg";
Begin
	say("Going to play "+fname+", hope you like it");
	song = load_song(fname);
	if(song > 0)
		say("Loaded succesfully");
		play_song(song, 0);
		while(is_playing_song())
			FRAME;
		end;
		stop_song();
		unload_song(song);
	end;
End;
