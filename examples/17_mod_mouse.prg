import "mod_mouse"
import "mod_video"
import "mod_say"

Process main()
Begin
    // Check that we can set the video mode before actually setting it
    if(!mode_is_ok(640, 480, 16, MODE_WINDOW))
        return -1;
    end;
    set_mode(640, 480, 16, MODE_WINDOW);
    while(! mouse.left)
        say("X: "+mouse.x+" Y:"+mouse.y);
        FRAME;
    end;
End;
