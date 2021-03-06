import "mod_wpad"
import "mod_video"
import "mod_text"
import "mod_mouse"

GLOBAL
scr_width = 640, scr_height=480;
End;

Process rumble_a_bit(int which)
Begin
    wpad_rumble(which, 1);  // Start rumbling
    FRAME(200);
    wpad_rumble(which, 0);
End;

Process main()
Private
    int myw=0, myh=0, vx=5, vy=5, was_colliding=0;

Begin
    // Check that we can set the video mode before actually setting it
    if(!mode_is_ok(scr_width, scr_height, 16, MODE_WINDOW))
        return -1;
    end;
    set_mode(scr_width, scr_height, 16, MODE_WINDOW);

    graph = png_load("logo.png");

    x=scr_width/2; y=scr_height/2;

    while(! mouse.left)
        x = mouse.x; y=mouse.y;
        angle = wpad_info(0, WPAD_ANGLE);
        write(0, scr_width/2, scr_height/2, 4, "ANGLE: "+wpad_info(0, WPAD_ANGLE));
        write(0, scr_width/2, scr_height/2+10, 4, "ACCELX: "+wpad_info(0, WPAD_ACCELX));
        write(0, scr_width/2, scr_height/2+20, 4, "ACCELY: "+wpad_info(0, WPAD_ACCELY));
        write(0, scr_width/2, scr_height/2+30, 4, "ACCELZ: "+wpad_info(0, WPAD_ACCELZ));
        FRAME;
        delete_text(ALL_TEXT);
    End;
    
    map_unload(0, graph);
End;
