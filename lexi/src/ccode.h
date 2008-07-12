#ifndef H_LEXI_CCODE_INCLUDED
#define H_LEXI_CCODE_INCLUDED

#include "exds/common.h"
#include "exds/dstring.h"

typedef enum CcodeItemTypeT_tag { Ccode_string, Ccode_identifier, Ccode_reference, Ccode_at} CcodeItemTypeT;

typedef struct CcodeItemT_tag {
	CcodeItemTypeT item_type;
	NStringT name;
	struct CcodeItemT_tag* next;
} CcodeItemT;

typedef struct CcodeT_tag {
	CcodeItemT*  head;
	CcodeItemT** tail;
} CcodeT;

void ccode_init(CcodeT*);
void ccode_assign(CcodeT*, CcodeT*);
void ccode_append_at(CcodeT*);
void ccode_append_identifier(CcodeT*, NStringT*);
void ccode_append_string(CcodeT*, NStringT*);
void ccode_output(FILE*, CcodeT*);

#endif /*H_LEXI_CCODE_INCLUDED*/

