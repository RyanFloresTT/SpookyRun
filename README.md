# Spooky Run

A puzzle game about one pawn crossing a chess board. Built in C++20 with raylib for Solo Dev Jam 13 (October 23 to 26, 2026, theme: "the other side").

**Play it in the browser:** https://ryanflorestt.itch.io/pawn-run

![Spooky Run](https://ryanflores.dev/static/images/projects/spookyrun.png)

## The game

You are a pawn. Move like a pawn, except you can also move one step backwards. Captures are diagonal in all directions.

Enemy pieces sit on the board and move like the chess pieces they are based on (rook, bishop, knight, king, queen).

## Systems worth looking at

- **Board and threat model** (`src/board.h`): the board owns the pieces and the grid. There is no stored attack map. After every change, the threat display is rebuilt from scratch by asking each piece to mark the squares it attacks, so the display can never disagree with the actual piece positions. Piece removal is deferred, because captures happen while other code is still iterating the piece list.
- **Validated level loading** (`src/levels/`): levels are JSON data (size, pieces, optional patrol routes). The loader checks every value before using it. An unknown piece type or an out of bounds position logs a warning and is skipped instead of crashing the game.
- **Scenes** (`src/scenes/`): each screen is a class behind a small interface, owned by a scene manager. Scene changes are stored and constructed halfway through a fade transition, so callers never handle transition timing.
- **One save interface, two backends** (`src/save/`): progress is the highest unlocked level. The desktop backend stores it in a JSON file. The web backend stores it in localStorage through the Emscripten HTML5 API.
- **Asset manager** (`src/raii/assets.h`): one registry per asset type, keyed by an enum, with loading in a single loop per type. Adding an asset is an enum entry and a registry row.

## Build

Desktop (Windows or Linux):

```sh
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

Dependencies (raylib 5.5, nlohmann/json) are pulled in by CMake FetchContent, there is nothing to install by hand. The desktop build copies the `assets` folder next to the executable after building.

Web: build with the Emscripten toolchain (`emcmake cmake -B build-web && cmake --build build-web`). Assets are preloaded into the web build, and the result is what runs on itch.io.

## Status

The jam version is finished and playable at the link above. The reusable parts of this codebase (scene manager, asset manager) are being extracted into [Lantern](https://github.com/RyanFloresTT/lantern), a small C++ 2D framework.

## Attributions

- Font: [Supply Center by nhfonts](https://www.1001fonts.com/supply-center-font.html)
- Cursor, interface sounds, star, UI, RPG sounds, Tiny Dungeon: [Kenney](https://kenney.nl)
- Music: [Abstraction](https://tallbeard.itch.io/music-loop-bundle), nastelbom
