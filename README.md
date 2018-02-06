# Only3keys
---

Only3keys is a userspace application that allows you to type using only 3 keys!

### Why?

 - Did you ever think your keyboard is too large and useful?
 - Did your keyboard burst into flames magically and destroy all but 3 keys?
 - Maybe you're just super 1337 and you bought one of these!


 (insert images of 3 key keyboards here)

 Well don't worry! I got you!

 ### How?

 Only3keys works by using 2 keys as 1 and 0, and a 3rd key for
 enter. Typing in binary, you can produce any ASCII code, and output it
 through a named pipe ("/tmp/only3keys" by default). The application on the
 other end of the pipe will happily accept it. Thats it! Additionally, because
 typing everything in binary is so excessively painful, certain features have
 been added to lessen the blow like responsive ascii charts that update as you
 type and "Double Tap" - allowing you to enter characters multiple times in
 few keystrokes (like "dd" or "1000000").

 ### Example
 '''
 code block here showing how to run it
 '''
 include gif of me using it.

 ### Limitations

    - limited to ascii (doesn't support: F1-F12, CTRL, ALT, Arrows, etc.)
        - does support ESC! Hello vi my old friend!
        - tools like emacs, screen, tmux, etc. that rely on CTRL, or other
        modifiers cannot and will not work. This will never be fixed, as it
        would require an entire rewrite of the project.

    - must have window focus to capture keys.
        - this makes using a mouse near impossible. I recommend a tiling WM
        like i3, and just throwing the mouse right out the window.

    - It's insanely impractical and near useless.
        - but hey, I did it for the lulz.
