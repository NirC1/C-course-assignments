#include <stdio.h>
#include <stdlib.h>

#include "../exercises/song.h"

int main(void) {
    Song *s = (Song *)malloc(sizeof(Song));
    if (s == NULL) {
        return 1;
    }

    set_song(s, "Blinding Lights", "The Weeknd", 202, POP);
    print_song(s);

    free_song(s);
    return 0;
}
