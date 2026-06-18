# noSqlite

A learning project: an embedded, serverless NoSQL storage engine written in C11.

Inspired by SQLite's single-file, in-process design — but for document/key-value data instead of relational tables.

## Status

Early stage. Currently building the storage layer:

- **Storage** — page layout, page manager
- **Memory** — buffer pool manager
- **CLI** — entry point (`apps/cli/`)

## Build

Requires a C11 compiler (GCC or Clang).

```bash
make
./build/nosqlite
```

Debug build:

```bash
make clean
CFLAGS="-std=c11 -Wall -Wextra -Wpedantic -g -O0" make
```

## Layout

```
src/
├── core/
│   ├── storage/   # disk pages, page manager
│   └── memory/    # buffer pool, frame metadata
├── errors/        # error types
apps/cli/          # executable
```

## License

See [LICENSE](LICENSE).
