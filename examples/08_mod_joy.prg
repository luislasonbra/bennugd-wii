#ifdef NOWII
import "mod_say";
import "mod_joy";
#endif

Process main()
Private
	int n=0, i=0, die=0;
Begin
	n = joy_number();	// Get the number of available joysticks
	if(n > 0)
    	say("There are "+n+" joysticks available");
	    say("Joystick names and avilable buttons");  // Display the names for all the joysticks
        for(i=0; i<n; i++)
            say("Joy["+i+"]: "+joy_name(i)+" has "+joy_numbuttons(i)+" buttons");
        end;
        say("");    // Empty line
        say("Press (A) in your wiimote to continue");
        while(die == 0)
            for(i=0; i<n; i++)
                if(joy_getbutton(i, 0))
                    say("You pressed (A) in joystick "+i);
                    die = 1;
                end;
            end;
        end;
    else
        say("Please, plug in a joystick to be able to use this code");
    end;
End;
