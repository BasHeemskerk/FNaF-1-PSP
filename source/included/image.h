#ifndef __IMAGE__
#define __IMAGE__

struct Vertex3DCNP {
	unsigned long color;
	float nx,ny,nz;
	float x,y,z;
};
struct Vertex3DTNP {
	float u,v;
	float nx,ny,nz;
	float x,y,z;
};
struct Vertex3DCP {
	unsigned long color;
	float x,y,z;
};
struct Vertex3DTCP {
	float u,v;
	unsigned long color;
	float x,y,z;
};
struct Vertex3DTCNP {
	float u,v;
	unsigned long color;
	float nx,ny,nz;
	float x,y,z;
};
struct Vertex3DTP {
	float u,v;
	float x,y,z;
};
struct Vertex3DTPfast {
	short u,v;
	short x,y,z;
};
struct Vertex3DCPfast {
	unsigned long color;
	short x,y,z;
};
struct Vertex3DTfast {
	short u,v;
};
struct Vertex3DPfast {
	short x,y,z;
};

typedef unsigned int Color;
typedef struct Image
{
        int textureWidth;  // the real width of data, 2^n with n>=0
        int textureHeight;  // the real height of data, 2^n with n>=0
        int imageWidth;  // the image width
        int imageHeight;	// the image height
        int isSwizzled;	// Is the image swizzled?
        int vram;		// Is the image in vram or not?
        int format;		// default is GU_COLOR_8888
        Color* data;
        Color* palette;	// used for 4 bpp and 8bpp modes.
        char filename[256];	// for debug purposes
} Image;
/* typedef struct ImageMip
{
        int textureWidth, textureWidth1, textureWidth2, textureWidth3;  // the real width of data, 2^n with n>=0
        int textureHeight, textureHeight1, textureHeight2, textureHeight3;  // the real height of data, 2^n with n>=0
        int imageWidth, imageWidth1, imageWidth2, imageWidth3;  // the image width
        int imageHeight, imageHeight1, imageHeight2, imageHeight3;	// the image height
        int isSwizzled;	// Is the image swizzled?
        int vram;		// Is the image in vram or not?
        int format;		// default is GU_COLOR_8888
        Color* data, data1, data2, data3;
        Color* palette;	// used for 4 bpp and 8bpp modes.
        char filename[256];	// for debug purposes
} ImageMip; */
Image *loadPng(const char *filename);
//ImageMip *loadPngMip(const char *filename);
void freeImage(Image *image);
//void freeImageMip(ImageMip *image);
void resetVRam();
void reportVRam();
extern int swizzleToVRam;
void swizzleFast(Image *source);
//void swizzleFastMip(ImageMip *source);
void saveImagePng(const char* filename, Color* data, int width, int height, int lineSize, int saveAlpha);
void saveImageTarga(const char* filename, Color* data, int width, int height, int lineSize, int saveAlpha);
Image *newImage(int width,int height);

struct AnimFrame {
	float scale[3];
	float translate[3];
	struct Vertex3DPfast *vert;
};
struct AnimMesh {
	Image *texture;
	int frameCount;
	int polyCount;
	int skinWidth,skinHeight;
	struct AnimFrame *frames;
	struct Vertex3DTfast *uv;
};
struct AnimMesh *md2Load(const char *fname);
void md2GetFractionalFrame(struct AnimMesh *mesh,int frame,int nextFrame,float fraction,struct Vertex3DTP *buffer,float *minMax);
void md2Free(struct AnimMesh *mesh);

int loadItemImage(const char *fname);
void loadItems();
void freeItems();
int getItemCount();
void setItemPos(int i,float x,float y,float z);
float itemGetVertex(int i, float x, float z);
void renderItem(int i, unsigned int modelcolor);
float *getItemMin(int i); 
float *getItemMax(int i);

//void drawSpriteAlpha(int sx, int sy, int width, int height, Image* source, int dx, int dy, int alpha);

#endif

