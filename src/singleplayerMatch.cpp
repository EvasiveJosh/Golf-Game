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
    terrain = terrainGenerator.DrawTerrain(difficulty);
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
    addButton("Hole", {sst::baseX - 98, sst::baseY - GRASS_HEIGHT - 10, 15, 15}); //Do not modify without notifying (I modified this see note above - Gabriel)

    //Load flag
    flag.loadImage("resources", PixelFlag); //Get flag
    flag.rescale((int)sst::cxf(100 * 1.0f), sst::cy(100 * 2.0f)); //Rescale flag to fit windowSize
    flag.loadTexture(); //Load the image into a texture

    // Initialize camera
    camera.target = {sst::cxf(sst::baseX / 2.0f), sst::cyf(sst::baseY / 2.0f)}; // Set camera target to center of screen
    camera.offset = {sst::cxf(sst::baseX / 2.0f), sst::cyf(sst::baseY / 2.0f)}; // Center of the screen
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    cameraShouldFollowBall = false;
    cameraShouldCenter = false;
    smoothingFactor = 0.1f; // Adjust smoothing (lower is slower)
}

void SingleplayerMatch::draw()
{
    // Start using camera
    BeginMode2D(camera);

    //base terrain
    DrawRectangle(sst::cx(0), sst::cyf(sst::baseY - GRASS_HEIGHT), sst::cx(sst::baseX), sst::cyf(GRASS_HEIGHT), GREEN);

    DrawCircle(10,10,3,RED);
    //Draw some default sky
    DrawRectangle(sst::cx(0), sst::cy(0), sst::cx(sst::baseX), sst::cyf(sst::baseY - GRASS_HEIGHT), BLUE);
    //Draw flag
    DrawTexture(flag.getTexture(0), sst::cx(sst::baseX - 169), sst::cy(sst::baseY - GRASS_HEIGHT - 189), WHITE); //Do not modify without notifying

    //draw each terrain segment
    for (const TerrainSquare& square : terrain) {
        int yPos = sst::baseY - GRASS_HEIGHT - square.getHeight();
        int posX = square.getPosX();
        int width = square.getWidth();
        DrawRectangle(posX, yPos, width, square.getHeight(), GREEN); // Call the draw method for each square
    }
    // Draw other elements (e.g., golfball)
    golfball.draw();

    // End using camera (before drawing UI text)
    EndMode2D();
}

void SingleplayerMatch::drawDebug()
{
    golfball.drawDebug();
    //Draw mouse hitbox
    DrawRectangleRec(mouse.mouseHitbox(), PURPLE);
    //Draw button hitboxes
    for (int i = 0; i < amountOfButtons(); i++)
    {
        DrawRectangleLinesEx(buttons[i].getBounds(), 5, PURPLE);
    }
    //Show current selection
    int font = 20;
    DrawText(TextFormat("Buttons[%i]", buttonClicked()), 0, 0, sst::cx(font), BLACK);
    DrawText(TextFormat("Wind: %i", wind), 0, sst::cy(40), sst::cx(font), BLACK);
}

GuiEvent SingleplayerMatch::updateLogic()
{   
    if (IsKeyPressed(KEY_GRAVE)) // Use grave key as the pause hotkey
    {
        togglePause();
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
        // World-space mouse position
        Vector2 worldMousePos = GetScreenToWorld2D(mouse.position(), camera);

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && !golfball.isDragging)
        {
            // Convert ball world position to screen position
            Vector2 screenBallPosition = GetWorldToScreen2D(golfball.getBallPosition(), camera);

            // Check if mouse position is inside the ball's screen-space bounds
            float ballScreenRadius = BALL_RADIUS * camera.zoom; // Scale the radius by zoom level
            if (CheckCollisionPointCircle(mouse.position(), screenBallPosition, ballScreenRadius))
            {
                golfball.isDragging = true;
                golfball.startDrag = golfball.getBallPosition();
                golfball.currentDrag = GetScreenToWorld2D({
                    mouse.position().x / sst::cxf(1),
                    mouse.position().y / sst::cyf(1)
                }, camera);
                golfball.updateVelocity({0,0});
            }
        } 
        else if(IsMouseButtonDown(MOUSE_LEFT_BUTTON) && golfball.isDragging)
        {
            golfball.currentDrag = GetScreenToWorld2D({
                mouse.position().x / sst::cxf(1),
                mouse.position().y / sst::cyf(1)
            }, camera);
        }
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && golfball.isDragging)
        {
            Vector2 dragVector = {golfball.startDrag.x - golfball.currentDrag.x, golfball.startDrag.y - golfball.currentDrag.y};
            golfball.updateVelocity({dragVector.x * LAUNCH_SCALE, dragVector.y * LAUNCH_SCALE});
            golfball.isDragging = false;
            if (wind == 3)
                golfball.isRolling = true; //A neat little thing happens, the ball slows down drastically in the x direction
            else
                golfball.isRolling = false;
            golfball.updateLogic();
        }
    }
    return Nothing;
}

void SingleplayerMatch::togglePause()
{
    if (isPaused)
    {
        resume();
    }
    else
    {
        pause();
    }
}

void SingleplayerMatch::pause()
{
    isPaused = true;
}

void SingleplayerMatch::resume()
{
    isPaused = false;
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
        float targetZoom = 1.0f;

        // Smoothly move the camera towards the center position
        camera.target.x += (targetPosition.x - camera.target.x) * smoothingFactor;
        camera.target.y += (targetPosition.y - camera.target.y) * smoothingFactor;

        // Default zoom unless scrollwheel moves
        if(GetMouseWheelMove() != 0) {
            cameraShouldCenter = false;
        } else {
            camera.zoom += (targetZoom - camera.zoom) * smoothingFactor;
        }
    }

    // Zoom camera (mouse wheel)
    camera.zoom += GetMouseWheelMove() * 0.25f;

    // Limit zoom range
    if (camera.zoom < 0.5f) camera.zoom = 0.5f;
    if (camera.zoom > 10.0f) camera.zoom = 10.0f;
}

int SingleplayerMatch::getShotCount() const 
{
    return golfball.getShotCount();
}
