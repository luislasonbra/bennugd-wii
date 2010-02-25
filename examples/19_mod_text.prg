import "mod_map"
import "mod_math"
import "mod_mouse"
import "mod_video"
import "mod_proc"
import "mod_say"
import "mod_text"

Global
    scr_width=640, scr_height=480;
End;

Process main()
Begin
    // Check that we can set the video mode before actually setting it
    if(!mode_is_ok(scr_width, scr_height, 16, MODE_WINDOW))
        return -1;
    end;
    set_mode(scr_width, scr_height, 16, MODE_WINDOW);
    write(0, scr_width/2, scr_height/2, ALIGN_CENTER, "Hello, world!");
    while(! mouse.left)
        FRAME;
    end;
End;
