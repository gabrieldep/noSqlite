#ifndef NOSQLITE_PAGEHEADER_H
#define NOSQLITE_PAGEHEADER_H


#include <cstdint>

#pragma pack(push, 1)

struct PageHeader {
    uint8_t page_type; // 1 byte  | Tipo da página (1=Dados, 2=Índice, 3=Livre)
    uint8_t flags; // 1 byte  | Flags de estado (ex: bit 0 = dirty/suja, bit 1 = compactada)
    uint16_t collection_id; // 2 bytes | ID numérico da coleção à qual esta página pertence
    uint32_t next_page_id; // 4 bytes | Ponteiro p/ próxima página (Útil para criar listas encadeadas)
    uint16_t slot_count; // 2 bytes | Quantidade de registros/slots ativos nesta página
    uint16_t free_space_end; // 2 bytes | Offset onde termina o espaço livre (onde o último doc foi injetado)
};

#pragma pack(pop)

#endif //NOSQLITE_PAGEHEADER_H
