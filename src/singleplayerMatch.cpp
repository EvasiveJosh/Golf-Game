#include "singleplayerMatch.h"
#include "singleplayerPauseMenu.h"

SingleplayerMatch::SingleplayerMatch(std::vector<int> info) : isPaused(false)
{
    //Settings for the match, so far serve no purpose
    this->difficulty = info[0];
    this->wind = info[1];
    this->endlessMode = !info[2];
    end = false;
    Terrain terrainGenerator;
    
    //Load mouse
    mouse = Mouse();
    //Load golfball
    golfball = Ball(WHITE);
    // To align hole png and hitbox, flag image is basex - 98, hole box is basex -169,
    // so flag image must be -71 more than hole to align assuming the flag scale is not changed.
    // For the y axis, the hole is -10, the flag is -189 to align. So the flag image must
    // be -179 more than the hole.

    // TODO: When implementing the hole with terrain generation, a larger than ball sized gap in the
    // terrain will be needed to allow the ball to fall into the hole. This will allow for proper hit detection.
    // When this happens, the hole hitbox will need to be lowered below the flag image.

    //Create golfballButton
    Vector2 ballPosVec = golfball.getBallPosition();
    addButton("Ball", {ballPosVec.x - 13, ballPosVec.y - 13, 28, 28});
    //Create Hole at ground level at opposite playing side
    int holeX = sst::baseX - 98;
    int holeY = sst::baseY - GRASS_HEIGHT - 5;
    addButton("Hole", Rectangle{(float)holeX, (float)holeY, 15, 15});

    //old flag code (just in case) DELETE LATER
    // flag.loadImage("resources", PixelFlag); //Get flag
    // flag.rescale((int)sst::cxf(100 * 1.0f), sst::cy(100 * 2.0f)); //Rescale flag to fit windowSize
    // flag.loadTexture(); //Load the image into a texture

    //initialize flag - adjust X position slightly less to the left
    flag = Flag(holeX, holeY, 1.0f);
    terrain = terrainGenerator.GenerateTerrain(difficulty,golfball,flag);
    // Initialize camera
    camera.target = {sst::cxf(sst::baseX / 2.0f), sst::cyf(sst::baseY / 2.0f)}; // Set camera target to center of screen
    camera.offset = {sst::cxf(sst::baseX / 2.0f), sst::cyf(sst::baseY / 2.0f)}; // Center of the screen
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    cameraShouldFollowBall = false;
    cameraShouldCenter = false;
    smoothingFactor = 0.1f; // Adjust smoothing (lower is slower)
    defaultZoom = 1.0f;
}

void SingleplayerMatch::draw()
{
    // Begin using the camera for scaling world elements
    BeginMode2D(camera);

    //base terrain
    DrawRectangle(sst::cx(0), sst::cyf(sst::baseY - GRASS_HEIGHT), 
                 sst::cx(sst::baseX), sst::cyf(GRASS_HEIGHT), GREEN);

    //Draw some default sky
    DrawRectangle(sst::cx(0), sst::cy(0), 
                 sst::cx(sst::baseX), sst::cyf(sst::baseY - GRASS_HEIGHT), BLUE);

    //draw flag
    flag.draw();
    
    //draw each terrain segment
    for (const TerrainSquare& square : terrain) {
        int yPos = sst::baseY - GRASS_HEIGHT - square.getHeight() + 1;
        DrawRectangle(sst::cxf(square.getPosX()), 
                     sst::cyf(yPos),
                     sst::cxf(square.getWidth()),
                     sst::cyf(square.getHeight()),
                     GREEN);
    }
    
    golfball.draw();
    EndMode2D();
}

void SingleplayerMatch::drawDebug()
{
    // Convert mouse position to world coordinates
    Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);

    // Create a new hitbox in world coordinates for the mouse
    Rectangle mouseHitboxWorld = {
        mouseWorldPos.x,
        mouseWorldPos.y,
        mouse.mouseHitbox().width,
        mouse.mouseHitbox().height
    };

    // Begin using the camera for scaling world elements
    BeginMode2D(camera);

    // Draw golfball debug information
    golfball.drawDebug();

    // Draw the mouse hitbox in world coordinates
    DrawRectangle(
        mouseHitboxWorld.x,
        mouseHitboxWorld.y,
        mouseHitboxWorld.width,
        mouseHitboxWorld.height,
        PURPLE
    );

    // Draw button hitboxes, scaled with the camera
    for (int i = 0; i < amountOfButtons(); i++)
    {
        Rectangle buttonBounds = buttons[i].getBounds();
        DrawRectangleLinesEx(
            Rectangle{
                buttonBounds.x,
                buttonBounds.y,
                buttonBounds.width,
                buttonBounds.height
            },
            sst::cx(5),
            PURPLE
        );
    }

    // End using the camera before drawing fixed-position UI elements
    EndMode2D();

    // UI elements (text) remain in screen space
    int font = 20;
    DrawText(TextFormat("Buttons[%i]", buttonClicked()), 0, 0, sst::cx(font), BLACK);
    DrawText(TextFormat("Wind: %i", wind), 0, sst::cy(40), sst::cx(font), BLACK);
}

GuiEvent SingleplayerMatch::updateLogic()
{   
    if (IsKeyPressed(KEY_GRAVE)) // Use grave key as the pause hotkey
    {
        isPaused = !isPaused;
        return isPaused ? PauseGame : ResumeGame;
    }

    if (isPaused)
        return Nothing;
    
    //General logic to be checked here
    mouse.updateMousePosition();
    golfball.updatePhysics();
    Vector2 ballPosVec = golfball.getBallPosition();
    buttons[0].updateButtonBounds({ballPosVec.x - 13, ballPosVec.y - 13, 28, 28});

    // Update camera logic
    updateCamera();

    //Check is ball has stopped on hole, if so, you won!
    if (CheckCollisionRecs(buttons[0].getBounds(), buttons[1].getBounds()) && golfball.isStopped)
    {
        end = true;
        // Round is finished, open win menu
        return OpenSingleplayerWinMenu;
    }

    //Launch the ball check
    if (golfball.isStopped)
    {
        // Convert mouse position to world coordinates
        Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && !golfball.isDragging)
        {
            // Apply scaling (similar to how you're drawing the ball)
            Vector2 scaledBallPos = {sst::cxf(golfball.getBallPosition().x), sst::cyf(golfball.getBallPosition().y)};
            
            // Scale the radius by zoom level
            float scaledRadius = BALL_RADIUS * sqrt((float)GetScreenWidth() / sst::baseX * (float)GetScreenHeight() / sst::baseY);

            // Check if mouse position is inside the ball's screen-space bounds
            if (CheckCollisionPointCircle(mouseWorldPos, scaledBallPos, scaledRadius))
            {
                golfball.isDragging = true;
                golfball.startDrag = scaledBallPos;
                golfball.currentDrag = mouseWorldPos;
                golfball.updateVelocity({0,0});
            }
        }
        else if(IsMouseButtonDown(MOUSE_LEFT_BUTTON) && golfball.isDragging)
        {
            golfball.currentDrag = mouseWorldPos;
        }
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && golfball.isDragging)
        {
            Vector2 dragVector = {golfball.startDrag.x - golfball.currentDrag.x, golfball.startDrag.y - golfball.currentDrag.y};
            golfball.updateVelocity({(dragVector.x * LAUNCH_SCALE) / sst::cxf(1), (dragVector.y * LAUNCH_SCALE) / sst::cyf(1)});
            golfball.isDragging = false;
            golfball.isRolling = (wind == 3);
            golfball.updateLogic();
        }
    }
    return Nothing;
}

void SingleplayerMatch::updateCamera() {
    // Variables to store the desired target position
    Vector2 desiredTarget = camera.target;

    // Handle panning controls (camera movement when keys are held down)
    if (IsKeyDown(KEY_A)) {
        desiredTarget.x -= sst::cx(100);  // Move camera left (increase speed)
        cameraShouldFollowBall = false;  // Stop following
        cameraShouldCenter = false; // Stop center
    }
    if (IsKeyDown(KEY_D)) {
        desiredTarget.x += sst::cx(100);  // Move camera right (increase speed)
        cameraShouldFollowBall = false;  // Stop following
        cameraShouldCenter = false; // Stop center
    }
    if (IsKeyDown(KEY_W)) {
        desiredTarget.y -= sst::cy(100);  // Move camera up (increase speed)
        cameraShouldFollowBall = false;  // Stop following
        cameraShouldCenter = false; // Stop center
    }
    if (IsKeyDown(KEY_S)) {
        desiredTarget.y += sst::cy(100);  // Move camera down (increase speed)
        cameraShouldFollowBall = false;  // Stop following
        cameraShouldCenter = false; // Stop center
    }

    // Smoothly transition the camera towards the desired target
    camera.target.x += (desiredTarget.x - camera.target.x) * smoothingFactor;
    camera.target.y += (desiredTarget.y - camera.target.y) * smoothingFactor;

    // Reset to follow the ball when `KEY_F` is pressed
    if (IsKeyPressed(KEY_F)) {
        cameraShouldCenter = false;
        cameraShouldFollowBall = !cameraShouldFollowBall;
    }

    // Reset to follow centre when 'KEY_C' is pressed
    if (IsKeyPressed(KEY_C)) {
        cameraShouldFollowBall = false;
        cameraShouldCenter = !cameraShouldCenter;
    }

    // Camera following ball logic (when `cameraShouldFollowBall` is true)
    if (cameraShouldFollowBall) {
        // Get the ball's position (target for the camera)
        Vector2 targetPosition = {
            sst::cxf(golfball.getBallPosition().x),
            sst::cyf(golfball.getBallPosition().y)
        };
        // Smoothly move the camera towards the ball's position
        camera.target.x += (targetPosition.x - camera.target.x) * smoothingFactor;
        camera.target.y += (targetPosition.y - camera.target.y) * smoothingFactor;
    }

    // Camera centered (when `cameraShouldCenter` is true)
    if (cameraShouldCenter) {
        Vector2 targetPosition = {sst::cxf(sst::baseX / 2.0f), sst::cyf(sst::baseY / 2.0f)};
        float centerZoom = 1.0f;

        // Smoothly move the camera towards the center position
        camera.target.x += (targetPosition.x - camera.target.x) * smoothingFactor;
        camera.target.y += (targetPosition.y - camera.target.y) * smoothingFactor;
        defaultZoom = centerZoom;

        // Default zoom unless scrollwheel moves
        if(GetMouseWheelMove() != 0) {
            cameraShouldCenter = false;
        } else {
            camera.zoom += (centerZoom - camera.zoom) * smoothingFactor;
        }
    }

    // Update desired zoom level when the mouse wheel moves
    defaultZoom += GetMouseWheelMove() * 0.25f;

    // Limit the desired zoom range
    if (defaultZoom < 0.5f) defaultZoom = 0.5f;
    if (defaultZoom > 10.0f) defaultZoom = 10.0f;

    // Smoothly transition the current zoom to the desired zoom level
    camera.zoom += (defaultZoom - camera.zoom) * smoothingFactor;
}

int SingleplayerMatch::getShotCount() const 
{
    return golfball.getShotCount();
}

void SingleplayerMatch::resume()
{
    isPaused = false;
}
