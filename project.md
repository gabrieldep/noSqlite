---

```markdown
# noSqlite Architecture & Master Plan

This document establishes the end-to-end architectural design, low-level specifications, and incremental execution plan for **noSqlite**—an embedded, document-based, serverless NoSQL storage engine built entirely in **pure C**.

---

## 1. Architectural Overview (Layered Design)

The system is strictly divided into 5 layers with isolated responsibilities. The data flow is strictly vertical:

```text
+-------------------------------------------------------+
| 5. CLIENT API (Collections, Documents, CRUD)          |
+-------------------------------------------------------+
                           |
+-------------------------------------------------------+
| 4. DOCUMENT & INDEX LAYER (BSON/JSON, B-Tree/Hash)    |
+-------------------------------------------------------+
                           |
+-------------------------------------------------------+
| 3. SLOTTED PAGE FORMATTER (Byte-level slicing)        |
+-------------------------------------------------------+
                           |
+-------------------------------------------------------+
| 2. BUFFER POOL MANAGER (RAM Cache, LRU, Page Table)   |
+-------------------------------------------------------+
                           |
+-------------------------------------------------------+
| 1. STORAGE MANAGER (OS File I/O, Page Allocation)    |
+-------------------------------------------------------+

```

---

## 2. Deep Dive by Layer

### Layer 1: Storage Manager (`PageManager`)

* **Responsibility:** Manages physical interactions with the `.nosqlite` file using binary OS file I/O (`fopen`, `fseek`, `fread`, `fwrite`).
* **Abstraction:** Views the database file as a continuous linear array of fixed 4096-byte blocks.
* **Global Metadata (Page 0):** Stores the file header (versioning, total allocated pages, and a pointer to the head of the *Free List* of deallocated pages).
* **Space Management:** Extends the physical file size when new pages are requested and manages page recycling via a linked list of deleted pages.

### Layer 2: Buffer Pool Manager (`BufferPool`)

* **Responsibility:** Keeps frequently accessed disk blocks in RAM to bypass slow disk I/O bottlenecks.
* **Critical C Components:**
* **Page Pool Array:** A contiguous block of memory pre-allocated in RAM holding `N` `Page` objects.
* **Frame Metadata:** An array tracking `pin_count` (active readers) and `is_dirty` (modification state).
* **Page Table (Hash Table):** Fast lookup mapping a disk `page_id` to its current memory `frame_id`.
* **LRU Tracker:** A static doubly-linked list managing eviction candidates (pages with a `pin_count == 0`).



### Layer 3: Slotted Page Formatter

* **Responsibility:** Performs surgical byte-level manipulations within a single raw 4096-byte `Page`.
* **Binary Memory Layout (4096 bytes):**
* **PageHeader (Start - 12 bytes):** Contains metadata describing the block's current state.
* **Slot Array (Grows forward/right):** An array of internal pointers (`offset` + `size`) pointing to individual records inside the page.
* **Payload (Grows backward/left):** Raw document bytes inserted from the end of the page moving toward the slots.


* **Free Space Calculation:** `free_space_end - (sizeof(PageHeader) + (slot_count * sizeof(PageSlot)))`.

### Layer 4: Document & Index Layer

* **Responsibility:** Handles efficient binary document serialization and accelerates lookups.
* **Binary Type System (BSON-style):** Avoids text-based JSON representations to optimize space and CPU usage. Supports types like `Null`, `Bool`, `Int32/64`, `Double`, `String`, and raw 16-byte `UUID`s.
* **Primary Index:** An in-memory mapping structure linking document `UUID`s directly to their hosting `page_id`, achieving $O(1)$ or $O(\log N)$ lookups without scanning the entire file.

### Layer 5: Client API

* **Responsibility:** The public interface exposed to the user (Facade Pattern).
* **Abstraction:** Provides clean NoSQL concepts of **Collections** and **Documents**.
* **Core API Operations:** `collection_insert()`, `collection_find_by_id()`, and `collection_delete()`.

---

## 3. Binary Structure Specifications

### PageHeader (12 bytes, packed & aligned)

```c
#pragma pack(push, 1)
typedef struct PageHeader {
    uint8_t  page_type;        // 1 = Data, 2 = Index, 3 = Free List node
    uint8_t  flags;            // Bitwise state flags (e.g., bit 0 = dirty)
    uint16_t collection_id;    // Numerical identifier of the owner collection
    uint32_t next_page_id;     // Pointer to the next page in the collection chain
    uint16_t slot_count;       // Count of active records/slots on this page
    uint16_t free_space_end;   // Lower bound offset where data payload begins
} PageHeader;
#pragma pack(pop)

```

### PageSlot (4 bytes)

```c
#pragma pack(push, 1)
typedef struct PageSlot {
    uint16_t offset;           // Internal byte offset relative to the page start
    uint16_t size;             // Total size of the document payload in bytes
} PageSlot;
#pragma pack(pop)

```

---

## 4. Incremental Execution Roadmap (Sprints)

We will build from the bottom up, utilizing mocks for higher layers to isolate testing at each phase.

* [ ] **Sprint 1: Internal Buffer Pool Data Structures**
* Design and implement a custom C Hash Table for `page_table`.
* Design and implement a static Doubly-Linked List for `lru_list`.
* *Deliverable:* Eradicate `void *` placeholders from the current `BufferPool` struct.


* [ ] **Sprint 2: Physical Persistence (`PageManager`)**
* Implement binary file initialization, open, close, block read, and block write mechanisms.
* Implement the internal physical file allocation logic (`allocate_page`).


* [ ] **Sprint 3: Memory Cache Integration**
* Connect the `BufferPool` layer directly to the `PageManager`.
* Implement full cache hit, cache miss, page eviction, and lazy writing (*Dirty Pages* flushing) logic.


* [ ] **Sprint 4: Slotted Page Formatter**
* Code byte-shifting algorithms, dynamic slot entry placement, and backward data writing.
* Implement internal page defragmentation (compaction) when records are deleted.


* [ ] **Sprint 5: Document Serialization & High-Level API**
* Write the binary encoder/decoder parser for NoSQL document variants.
* Construct the finalized `Collection` public CRUD facade.



```

---

Agora que temos o plano macro todo mapeado em inglês, vamos iniciar a **Sprint 1**. Qual das duas estruturas internas do seu pool você quer que a gente comece a planejar conceitualmente: a estrutura da **Tabela Hash (`page_table`)** ou o encadeamento estático da **Lista LRU (`lru_list`)**?

```