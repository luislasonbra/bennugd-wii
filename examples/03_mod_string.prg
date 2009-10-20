#ifdef NOWII
import "mod_say";
import "mod_string";
#endif

Process main()
Private
	string teststr="Hello, World!";
Begin
	say("String '"+teststr+"' is "+len(teststr)+" characters long");
End;
