import "mod_mouse"
import "mod_video"
import "mod_say"
import "mod_timers"

Process main()
Private
    int i=0;

Begin
    // Check that we can set the video mode before actually setting it
    if(!mode_is_ok(640, 480, 16, MODE_WINDOW))
        return -1;
    end;
    set_mode(640, 480, 16, MODE_WINDOW);
    set_fps(4,0);
    while(! mouse.left)
        say("X: "+mouse.x+" Y:"+mouse.y);
        FRAME;
    end;
End;
