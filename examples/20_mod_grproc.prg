import "mod_grproc"
import "mod_map"
import "mod_mouse"
import "mod_math"
import "mod_video"
import "mod_rand"
import "mod_text"

GLOBAL
scr_width = 640, scr_height=480;
End;

Process robot(x, y, graph)
Private
    int vx=5, vy=5;
    int myw=0, myh=0;
Begin
    myw=graphic_info(0, graph, G_WIDTH)/2;
    myh=graphic_info(0, graph, G_HEIGHT)/2;
    while(! mouse.left)
        if(x > scr_width-(myw+abs(vx)) || x < (myw+abs(vx)))
            vx = -vx;
        end;
        if(y > scr_height-(myh+abs(vy)) || y < (myh+abs(vy)))
            vy = -vy;
        end;
        x+=vx;
        y+=vy;
        if(collision(TYPE robot))
            write(0, scr_width/2, scr_height/2, 4, "Collision!");
        else
            delete_text(ALL_TEXT);
        end;
        FRAME;
    End;
End;

Process main()
Begin
    // Check that we can set the video mode before actually setting it
    if(!mode_is_ok(scr_width, scr_height, 16, MODE_WINDOW))
        return -1;
    end;
    set_mode(scr_width, scr_height, 16, MODE_WINDOW);
    robot(rand(scr_width/6, 5*scr_width/6), rand(scr_height/6, 5*scr_height/6),
          png_load("mouse.png"));
    robot(rand(scr_width/6, 5*scr_width/6), rand(scr_height/6, 5*scr_height/6),
          png_load("logo.png"));
    set_text_color(rgb(255, 0, 0));
End;
