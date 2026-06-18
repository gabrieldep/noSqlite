# noSqlite

A learning project: an embedded, serverless NoSQL storage engine written in C++23.

Inspired by SQLite's single-file, in-process design — but for document/key-value data instead of relational tables.

## Status

Early stage. Currently building the storage layer:

- **Storage** — page layout, page manager
- **Memory** — buffer pool manager
- **CLI** — entry point (`apps/cli/`)

## Build

Requires CMake and a C++23 compiler (GCC 13+ or Clang 16+).

```bash
cmake -B build -S .
cmake --build build
./build/noSqlite
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
