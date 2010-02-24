import "mod_mouse"
import "mod_video"
import "mod_say"
import "mod_timers"
import "mod_map"

Process main()
Private
    int i=0;

Begin
    // Check that we can set the video mode before actually setting it
    if(!mode_is_ok(640, 480, 16, MODE_WINDOW))
        return -1;
    end;
    set_mode(640, 480, 16, MODE_WINDOW);
    mouse.graph = load_png("mouse.png");
    while(! mouse.left)
        x=mouse.x;
        y=mouse.y;
        FRAME;
    end;
    unload_map(0, mouse.graph);
End;
