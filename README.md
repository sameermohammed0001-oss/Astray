# Astray

A small C project: a lightweight lexer for .as files (work-in-progress).

## Project layout

- `src/` — source code (`lexer.c`, `lexer.h`, `main.c`)
- `tests/` — example inputs (e.g. `basic.as`)

## Requirements

- A C compiler (GCC or Clang)

## Build

Compile the project with a C compiler:

```sh
gcc -std=c11 -Wall -Wextra -o astray src/*.c
```

## Run

Run the built binary with an example file:

```sh
./astray tests/basic.as
```

## Contributing

Contributions, bug reports and feature requests are welcome. Open an issue or send a PR.

## License

TBD
