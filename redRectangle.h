/* redRectangle.h */


#ifndef FILEREDRECTANGLEH
#define FILEREDRECTANGLEH


/* A red rectangle! */


#define REDRECTANGLEW 3
#define REDRECTANGLEH 3


typedef struct
{
  int width;
  int height;
  int chars[REDRECTANGLEW * REDRECTANGLEH];
  int colors[REDRECTANGLEW * REDRECTANGLEH];
} _REDRECTANGLE;


_REDRECTANGLE REDRECTANGLE = 
{
  REDRECTANGLEW,
  REDRECTANGLEH,
  {
    219, 219, 219,
    219, 219, 219,
    219, 219, 219,
  },
  {
    4  , 4  , 4  ,
    4  , 4  , 4  ,
    4  , 4  , 4  ,
  }
};


#endif /* FILEREDRECTANGLEH */