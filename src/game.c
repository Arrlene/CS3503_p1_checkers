#include "bitboard.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

static int save_state(const char *path, const GameState *g)
{
    FILE *f = fopen(path, "wb");
    if (!f)
    {
        perror("save");
        return 0;
    }
    size_t n = fwrite(g, sizeof(GameState), 1, f);
    fclose(f);
    return (int)(n == 1);
}

static int load_state(const char *path, GameState *g)
{
    FILE *f = fopen(path, "rb");
    if (!f)
    {
        perror("load");
        return 0;
    }
    size_t n = fread(g, sizeof(GameState), 1, f);
    fclose(f);
    return (int)(n == 1);
}

static void help()
{
    printf("Commands:\n");
    printf("  m FROM TO   -> move from index to index (0..63)\n");
    printf("  p           -> print board\n");
    printf("  q           -> quit\n");
    printf("Examples: m 9 14  |  m 22 17\n");
}

int main()
{
    GameState g;
    game_init(&g);
    print_board(&g);
    help();

    char cmd[64];
    while (1)
    {
        printf("P%d> ", g.turn);
        if (!fgets(cmd, sizeof(cmd), stdin))
            break;
        if (cmd[0] == 'q')
            break;

        if (cmd[0] == 'p')
        {
            print_board(&g);
            continue;
        }

        if (cmd[0] == 's')
        {
            char path[128];
            if (sscanf(cmd + 1, "%127s", path) == 1)
            {
                if (save_state(path, &g))
                    printf("Saved to %s\n", path);
                else
                    printf("Save failed.\n");
            }
            else
            {
                printf("Usage: s <filename>\n");
            }
            continue;
        }

        if (cmd[0] == 'l')
        {
            char path[128];
            if (sscanf(cmd + 1, "%127s", path) == 1)
            {
                if (load_state(path, &g))
                    print_board(&g);
                else
                    printf("Load failed.\n");
            }
            else
            {
                printf("Usage: l <filename>\n");
            }
            continue;
        }

        if (cmd[0] == 'm')
        {
            int a, b;
            if (sscanf(cmd + 1, "%d %d", &a, &b) == 2)
            {
                if (try_move(&g, a, b))
                {
                    print_board(&g);
                    int w = has_winner(&g);
                    if (w)
                    {
                        printf("Winner: P%d\n", w);
                        break;
                    }
                    if (!current_player_can_move_simple(&g))
                    {
                        printf("Stalemate or no legal move. P%d cannot move.\n", g.turn);
                        break;
                    }
                }
                else
                {
                    printf("Invalid move.\n");
                }
            }
            else
            {
                printf("Usage: m FROM TO\n");
            }
            continue;
        }

        printf("Unknown command. Type 'p' to print, 'm' to move, 's' to save, 'l' to load, 'q' to quit.\n");
    }

    return 0;
}