
#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "OMBSON.h"
#ifdef __cplusplus
	};
#endif

#include "json.h"
#include "bsonobjbuilder.h"
#include <string.h>

UDINT bur_heap_size = 0xFFFF;

// https://github.com/dwight/bson-cxx/blob/master/src/examples/example1.cpp
/* TODO: Add your comment here */
unsigned long json2bson(unsigned long Bin, unsigned long Str, unsigned long BufferSize)
{
	_bson::bsonobjbuilder b;
	std::stringstream s((char*)Str);
	_bson::bsonobj o = fromjson(s, b);
	if (o.objsize() <= BufferSize) {
		memcpy((char*)Bin, o.objdata(), o.objsize());
		return o.objsize();
	}
	return 0;
}
