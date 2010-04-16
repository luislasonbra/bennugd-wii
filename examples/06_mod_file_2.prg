import "mod_key"
import "mod_video"
import "mod_text"
import "mod_mouse"
import "mod_rand"
import "mod_file"
import "mod_dir"

GLOBAL
scr_width = 640, scr_height=480;
End;

Process main()
Private
    string var1="The answer to life, the universe and everything";
    int var2=42;

Begin
    // Check that we can set the video mode before actually setting it
    if(!mode_is_ok(scr_width, scr_height, 16, MODE_WINDOW))
        return -1;
    end;
    set_mode(scr_width, scr_height, 16, MODE_WINDOW);

    // Save the data to a file
    save("var1.saved", var1);
    save("var2.saved", var2);

    // Clear the vars
    var1="";
    var2=0;

    // Reload the vars
    load("var1.saved", var1);
    load("var2.saved", var2);

    write(0, scr_width/2, 30, 4, "All the following lines should display 'OK'");
    write(0, scr_width/2, 40, 4,
        var1=="The answer to life, the universe and everything" ? "OK":"Fail!");
    write(0, scr_width/2, 50, 4, var2==42 ? "OK":"Fail!");
    while(! mouse.left)
        FRAME;
    end;

    // Delete the variable savefiles
    rm("var1.saved");
    rm("var2.saved");
End;
