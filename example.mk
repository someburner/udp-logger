### Includes, standard locations
INC_DIRS := -I/usr/include
LD_DIRS  := -L/usr/lib

### Router example
INC_DIRS := -I/mmc/usr/include -I/mmc/include
LD_DIRS  := -L/mmc/usr/lib -L/mmc/lib

### Defines - customize user defs
LOCAL_DEFINES := -DRT3200_BLD
