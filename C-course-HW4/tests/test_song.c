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

    /* The expected output file has a blank line after the song line. */
    printf("\n");

    free_song(s);
    return 0;
}
