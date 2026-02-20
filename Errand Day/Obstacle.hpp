#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

// ---- constants ----
#define OB_COUNT 10

#define MAX_OBS_ON_SCREEN 2

static int OB_WIDTH[OB_COUNT] = { 102, 95, 56, 108, 98, 120, 95, 120, 59, 117 };
static int OB_HEIGHT[OB_COUNT] = { 74, 63, 101, 74, 100, 76, 63, 76, 76, 108 };


static int gRoadLeft = 72;
static int gRoadRight = 636;
static int gScreenH = 1080;
static int gBag[OB_COUNT];
static int gBagIndex = OB_COUNT;  

// obstacle state
struct Obstacle {
    int active;
    int imgIndex;
    int lane;
    float x;
    float y;

	int width;      
	int height;     
};

// Limit Max Obstacles At A Time
static Obstacle gObs[MAX_OBS_ON_SCREEN];

// Spawn Timer
static int gSpawnTicks = 60;

// Lane Width
static int laneWidth() {
    return (gRoadRight - gRoadLeft) / 4;
}

static float laneX(int lane, int obstacleWidth) {
	int lw = laneWidth(); // still 141
	return (float)(gRoadLeft + lane * lw + (lw - obstacleWidth) / 2);
}

// Collision
static int collision(float ax, float ay, float aw, float ah,
                float bx, float by, float bw, float bh)
{
    return (ax < bx + bw) && (ax + aw > bx) &&
           (ay < by + bh) && (ay + ah > by);
}

static void initObstacleSystem(int roadLeft, int roadRight, int screenH)
{
	gRoadLeft = roadLeft;
	gRoadRight = roadRight;
	gScreenH = screenH;

	for (int i = 0; i < MAX_OBS_ON_SCREEN; i++)
		gObs[i].active = 0;

	gSpawnTicks = 60;
}

static void resetObstacles()
{
	for (int i = 0; i < MAX_OBS_ON_SCREEN; i++)
		gObs[i].active = 0;

	gSpawnTicks = 60;
}

static int activeObstacleCount()
{
    int c = 0;
	for (int i = 0; i < MAX_OBS_ON_SCREEN; i++){
		if (gObs[i].active){
			c++;
		}
	}
    return c;
}

static void refillBag()
{

	for (int i = 0; i < OB_COUNT; i++)
		gBag[i] = i;

	// Shuffle
	for (int i = 0; i < OB_COUNT; i++)
	{
		int r = rand() % OB_COUNT;
		int temp = gBag[i];
		gBag[i] = gBag[r];
		gBag[r] = temp;
	}

	gBagIndex = 0;
}


static void spawnObstacle()
{
    if (activeObstacleCount() >= MAX_OBS_ON_SCREEN) return;

    // Free Slot Finder
    int idx = -1;
    for (int i = 0; i < MAX_OBS_ON_SCREEN; i++) {
        if (!gObs[i].active){
			idx = i;
			break;
		}
    }
    if (idx < 0) return;

	gObs[idx].active = 1;

	// Empty Bag Check
	if (gBagIndex >= OB_COUNT)
		refillBag();

	gObs[idx].imgIndex = gBag[gBagIndex++];
	gObs[idx].lane = rand() % 4;

	// set size based on which obstacle
	int k = gObs[idx].imgIndex;
	gObs[idx].width = OB_WIDTH[k];
	gObs[idx].height = OB_HEIGHT[k];

	// center in lane using its width
	gObs[idx].x = laneX(gObs[idx].lane, gObs[idx].width);

	// spawn above screen
	gObs[idx].y = (float)(gScreenH + (rand() % 200));

}

static void updateObstacles(float speed)
{
    gSpawnTicks--;
	if (gSpawnTicks <= 0) {

		// Only spawn with some probability.

		int spawnChancePercent = 60;

		if ((rand() % 100) < spawnChancePercent) {
			spawnObstacle();
		}

		int active = activeObstacleCount();

		// longer delay if there's already one on screen
		if (active == 0) gSpawnTicks = 60 + (rand() % 180);
		else             gSpawnTicks = 80 + (rand() % 240);

	}


    for (int i = 0; i < MAX_OBS_ON_SCREEN; i++) {
        if (!gObs[i].active) continue;

        gObs[i].y -= speed;

		if (gObs[i].y < -gObs[i].height) {
			gObs[i].active = 0;
		}
    }
}

// returns 1 if collision
static int checkObstacleCollision(float carX, float carY, float carW, float carH)
{
    for (int i = 0; i < MAX_OBS_ON_SCREEN; i++) {
        if (!gObs[i].active) continue;

		if (collision(carX, carY, carW, carH,
			gObs[i].x, gObs[i].y,
			(float)gObs[i].width, (float)gObs[i].height))
		{
			gObs[i].active = 0;
			return 1;
		}

    }
    return 0;
}

#endif
