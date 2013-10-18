#include "SDL.h"
#include "SDL_opengl.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static void setup_sdl() 
{
    const SDL_VideoInfo* video;

    if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }
        
    /* Quit SDL properly on exit */
    atexit(SDL_Quit);

    /* Get the current video information */
    video = SDL_GetVideoInfo( );
    if( video == NULL ) {
        fprintf(stderr, "Couldn't get video information: %s\n", SDL_GetError());
        exit(1);
    }

    /* Set the minimum requirements for the OpenGL window */
    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

    /* Note the SDL_DOUBLEBUF flag is not required to enable double 
     * buffering when setting an OpenGL video mode. 
     * Double buffering is enabled or disabled using the 
     * SDL_GL_DOUBLEBUFFER attribute.
     */
    if( SDL_SetVideoMode( 1, 1, video->vfmt->BitsPerPixel, SDL_OPENGL ) == 0 ) {
        fprintf(stderr, "Couldn't set video mode: %s\n", SDL_GetError());
        exit(1);
    }
}

int main(int argc, char* argv[])
{	
	setup_sdl();
    
	GLuint list = glGenLists(1);
	glNewList( list, GL_COMPILE );
	glEndList();
	if( glGetError() == GL_INVALID_ENUM )
		exit( 2 );
	else 
		exit( 0 );  
	
	return 0;
}
