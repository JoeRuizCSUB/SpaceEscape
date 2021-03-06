// typedefine.h
//
//////////////////////////////////////////////////////////////////////////////////////
// Jonathan Added
#include "fonts.h"
#include "ppm.h"
#include <cstdlib>
#include </usr/include/AL/alut.h>
//defined types
typedef float Flt;
typedef float Vec[3];
typedef Flt Matrix[4][4];
extern int xres, yres;

//macros
#define rnd() (((double)rand())/(double)RAND_MAX)
#define random(a) (rand()%a)
#define VecZero(v) (v)[0]=0.0,(v)[1]=0.0,(v)[2]=0.0
#define MakeVector(x, y, z, v) (v)[0]=(x),(v)[1]=(y),(v)[2]=(z)
#define VecCopy(a,b) (b)[0]=(a)[0];(b)[1]=(a)[1];(b)[2]=(a)[2]
#define VecDot(a,b)     ((a)[0]*(b)[0]+(a)[1]*(b)[1]+(a)[2]*(b)[2])
#define VecSub(a,b,c) (c)[0]=(a)[0]-(b)[0]; \
                             (c)[1]=(a)[1]-(b)[1]; \
(c)[2]=(a)[2]-(b)[2]
//constants
const float timeslice = 1.0f;
const float gravity = -0.2f;
#define PI 3.141592653589793
#define ALPHA 1
const int MAX_BULLETS = 100;
const Flt MINIMUM_ASTEROID_SIZE = 60.0;

typedef double Arr[3];
struct Sprite {
        Arr pos;
	    Arr vel;
};


//-----------------------------------------------------------------------------
//Setup timers
const double physicsRate = 1.0 / 60.0;
const double oobillion = 1.0 / 1e9;
extern struct timespec timeStart, timeCurrent;
extern struct timespec timePause;
extern double physicsCountdown;
extern double timeSpan;
extern double timeDiff(struct timespec *start, struct timespec *end);
extern void timeCopy(struct timespec *dest, struct timespec *source);
extern int ShowBackground();
extern Sprite bullet_sprite;
extern Ppmimage *bulletImage;
extern GLuint bulletTexture;

//-----------------------------------------------------------------------------

struct Astronaut {
    Vec dir;
    Vec pos;
    Vec vel;
    int mass;
    float angle;
    float color[3];
    Astronaut() {
        VecZero(dir);
        pos[0] = 10.0;
        pos[1] = 20.0;
        pos[2] = 0.0f;
        VecZero(vel);
        angle = 0.0;
        color[0] = 1.0;
        color[1] = 1.0;
        color[2] = 1.0;
    }
};

struct Bullet {
    Vec pos;
    Vec vel;
    float color[3];
    struct timespec time;
    Bullet() { }
};
struct Asteroid {
    Vec pos;
    Vec vel;
    int mass;
    int nverts;
    Flt radius;
    Vec vert[8];
    float angle;
    float rotate;
    float color[3];
    struct Asteroid *prev;
    struct Asteroid *next;
    Asteroid() {
        prev = NULL;
        next = NULL;
    }
};


struct HealthBox {
    Vec pos;
    Vec vel;
    Flt radius;
    float angle;
    float rotate;

};
struct Vector {
        float x, y, z;
};
struct Shape {
        float width, height;
	    float radius;
	        Vector center;
};


struct FuelBox {
    Vec pos;
    Vec vel;
    Flt radius;
    float angle;
    float rotate;

};
struct AmoBox {
    Vec pos;
    Vec vel;
    Flt radius;
    float angle;
    float rotate;

};

struct Alien{
    Vec pos;
    Vec vel;
    Flt radius;
    float angle;
    float rotate;
    int dead;
};



struct Game {
    Astronaut astronaut;
    Asteroid *ahead;
    Bullet *barr;
    int big_asteroids;
    int small_asteroids;
    int nbullets;
    struct timespec bulletTimer;
    Game() {
        ahead = NULL;
        barr = new Bullet[MAX_BULLETS];
        big_asteroids = 0;
	small_asteroids = 0;
        nbullets = 0;
    }
    ~Game() {
        delete [] barr;
    }
};

//function prototypes
void initXWindows(void);
void init_opengl(void);
void init_openal(void);
void cleanupXWindows(void);
void check_resize(XEvent *e);
void check_mouse(XEvent *e, Game *game);
int check_keys(XEvent *e, Game *g);
void init(Game *g, int i, bool GameStartMenu);
void init_sounds(void);
void physics(Game *game);
void render(Game *game);
void show_mouse_cursor(const int onoff);

// Jonathan Added
void astronautCollision(struct Game *g, int &health);
void deleteAsteroid(Game *g, Asteroid *node);
void buildAsteroidFragment(Asteroid *ta, Asteroid *a);
int fuelRemains(float fuel);
float reduceFuel(float fuel);
int remainingAmo(int bulletsRemain);
int reduceAmo(int bulletsRemain);
int getHealthPack(Game *g, HealthBox *healthbox, int &health);
int getFuelPack(Game *g, FuelBox *fuelbox, float &fuel);
int getAmoPack(Game *g, AmoBox *amobox, int &bulletsRemain);
void DrawFuelBox(GLuint fuelBoxTexture, FuelBox *f);
void DrawAmoBox(GLuint amoBoxTexture, AmoBox *a);
void buildFuelBox(FuelBox *f);
void buildAmoBox(AmoBox *a);
void buildAlien(Alien *a);
void DrawAlien(GLuint AlienTexture, Alien *a);
void AlienFollows(Game *g, Alien *alien);
int AlienHits(Game *g, Alien *alien, int &health);
int ShotAlien(Game *a, Alien *alien, int &score);
// Joe Added
void init(Game *g);
void pauseGame(int xsize, int ysize, Rect pausebox);
void deadGame(int xsize, int ysize, Rect pausebox);
void strandedGame(int xsize, int ysize, Rect pausebox);
void restartLevel(int &health, float &fuel, int &bulletsRemain, int &score, 
	int &levelnum, int &background, Game *g);
void asteroidsRemainingBox(Rect r, Game *g);
void windowBorderCollision(Game *g);
void initBigAsteroid(Game *g, bool GameStartMenu);
void moreAsteroids(Game *g, int levelnum);
// Sean Added
void changeBackground(int, GLuint, GLuint, GLuint);
void init_openal(ALuint*, ALuint*);
void cleanup_openAl(ALuint*, ALuint*);
void getAudio(int, ALuint*); 
void showLevel(Rect, int);
void nextLevel(int&, float&, int&, Game*, bool GameStartMenu);
void backstory(Rect);
void check_n(XEvent *e);    
///////////////////////////////////////////////////////////////////////////////
void healthbar(int x, Rect r, int &health);
void fuelbar(int x, Rect r, float &fuel);

void buildHealthBox(HealthBox *h);
void DrawHealthBox(GLuint, HealthBox *h);
unsigned char *buildAlphaData(Ppmimage *img);
void menubar(int a, Rect r, int score);
void bulletdisplay(int &bulletsRemain, Sprite bullet_sprite);
unsigned char *buildAlphaData(Ppmimage *img);
int Score(int score);
void check(XEvent *e);
void highScoreMenu(Rect r);
void highScorefile(int score);
void ifhighScore(int score);

