import "mod_mouse"
import "mod_video"
import "mod_say"
import "mod_timers"
import "mod_map"

Process main()
Begin
    // Check that we can set the video mode before actually setting it
    if(!mode_is_ok(640, 480, 16, MODE_WINDOW))
        return -1;
    end;
    set_mode(640, 480, 16, MODE_WINDOW);
    mouse.graph = png_load("mouse.png");
    /*say("mouse.graph: "+mouse.graph);
    say("mouse.width: "+graphic_info(0, mouse.graph, G_WIDTH));
    say("mouse.height: "+graphic_info(0, mouse.graph, G_HEIGHT));
    say("mouse.flags: "+mouse.flags);
    say("mouse.region: "+mouse.region);*/
    //map_save(0, mouse.graph, "mouse.map");
    while(! mouse.left)
        FRAME;
    end;
    unload_map(0, mouse.graph);
End;
