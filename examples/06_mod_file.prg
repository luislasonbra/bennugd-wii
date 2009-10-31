#ifdef NOWII
import "mod_say";
import "mod_file";
#endif

Process main()
Private
	string file="cancion_pirata_espronceda.txt", line="";
	int fd=0;

Begin
	say("Going to read file "+file);
	/* It's really José de Espronceda */
	/* http://es.wikipedia.org/wiki/José_de_Espronceda */
	say("This poem was written by the famous spanish poet Jose de Espronceda.");
	say("");
	fd = fopen(file, O_READ);
	if(fd == 0)
	    say("Couldn't load poem file :(");
	else
	    while(!feof(fd))
	    	line = fgets(fd);
	    	say(line);
	    end;
	    fclose(fd);
	end;
End;
