#ifndef _LLTABLE_H_
#define _LLTABLE_H_

typedef struct{
    Queue *cols;
    Queue *rows;
    Produc ***table;
} LLTable;

extern Word *get_infer(FILE *fp);
extern size_t scan_row(FILE *fp, size_t col);
extern LLTable *get_lltable(FILE *fp, Word *infer);
extern void destory_lltable(LLTable *lltable);

#endif