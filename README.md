# TODO
1. Ball (Thomas)
        - Ball needs an overhaul. A physics engine needs to be created seperate from ball. 
        - Collision will be done inside the physics engine

        Nobody touch ball.cpp and ball.h
3. Singleplayer
        - When RESTART is selected, the difficulty, wind and endless mode of previous match are not carried over, they need to be.
4. Multiplayer (Thomas)
        - Singplayer class but with things added (so real)
5. Menu
        - Settings menu needs careful consideration. 
        - Do not store screen resolutions anywhere
        - HostMenu
        - Kian needs to fix joinMultiplayerMenu (Add box for IP)
6. General
        - Logic updates should be moves after EndDrawing() (to avoid conflicts with draw and drawDebug)
        - Find better music for the game
        - Overhaul Project organization
                - Headers in one file
                - Cpp is another
                - Update CMAKE
7. Terrain
        - Bound the random terrain between the starting ball position and the flag
        - Collisions for terrain
        - Please rename DrawTerrain, it literally does NOT DRAW THE TERRAIN
8. Camera 
        - Make option for it to center on the ball (just use position of ball)
        - Debug view needs to be overhauled. It needs to stay put when the camera moves (rn it moves with the camera)



# Golf-Game

Welcome to the golfgame code!

NOTE: THE SINGLEPLAYERMATCH CODE DOES NOT WORK ON OTHER RESOLUTIONS OTHER THAN THE INTITAL ONE. I HAVE YET TO FIX THIS
        When in the game, press p to toggle debug view. If you get stuck, press the ESCAPE key to terminate program.


Here is whats going on:

Program: It is the heart of everything. Every Menu returns a "state" that is then evaluated in Program::updateLogic
        Note that the "states" come from GuiEnum.h under the GuiEvent enum. Every menu that inherits from menu.h has a
        function that returns a GuiEvent to be evaluated by the program.

Menu: First, menu has the following children (header file and class names are the same)
        - startMenu
        - singleplayerGameSettingsMenu
        - multiplayerMenu
        - joinMultiplayerMenu
        - generalSettingsMenu
        These are all standard menus, and each child has its own enum and its own logic function. That function returns a GuiEvent and
        that is how it can communicate with the program. If it must return information, additional functions overwritten from the Menu class
        are needed. 

joinMultiplayerMenu: In this, you can set your own name and the host's username, although nothing will change when you press Join,
                    the menu will send the two names you have typed in to the Program (check out the GuiEvent code for this!). 

singleplayerGameSettingsMenu: When you set your settings (which for now do nothing, except if you choose unpredictable wind), and start the game,
                                the Program will set the std::unique_ptr<Menu> to nullptr, effectively destroying the menu. It will then set
                                inSingleplayerGame = true and a new std::unique_ptr<Match> is used to hold the actual game.

Match: The Match class (in match.h) is a class to be inherited, and its children are singleplayerMatch (somewhat implemented) 
        and multiplayerMatch (not implemented). This was done as textureClass cannot be copied properly (its a whole thing), and I found it easier to
        just manage memory using std::unique_ptr. 

Button: This is used extensively in every menu and in the Matches to store hitboxes. These hitboxes interact with your mouse hitbox. 
        Each menu has a vector of them. Note that you must keep track of the indices, as for each class, each index represents a different button.

Mouse: Just your usual mouse stuff, do note that in any menu or match logic function, you need to run mouse.updateMousePosition() 
        and do some things with it

screenSizeTransfer: This is the most important function for the gui. You will notice that it is practically everywhere. This is due to the need to rescale
                    everything that is being drawn to the screen (using a raylib function) when the screensize is changed (which can be done in
                    generalSettingsMenu). The general rule of thumb is to use it only in raylib functions as our class functions should account for
                    it in their definition (for example, see the Button::labelBounds function, in the button.cpp file). 
                    Essentially, the whole gui is built using a default resolution of 1280x720 (accessed using sst::baseX and sst::baseY).


General notes:

    I may or may have not left some TODO's at some places, they may or may not already be implemented (most likely not).
    Writing a menu child class is not simple the first time, I suggest you look at completed ones first to get a feel.

    singleplayerMatch has a barebones implementation. I took the physics code and implemented it inside the game. That's really it. 
    A terrain class should be given to the match class (so that the children can have access to it) and the physics ball should
    handle the collisions (although code for that is not implemented).

    Also for the terrain class and any other added classes, PLEASE make them MODULAR!!!!!!!! (It makes life easy)

READ THE CODE, UNDERSTAND WHAT IT DOES!

Im too tired to continue. Let me know if you got any questions.