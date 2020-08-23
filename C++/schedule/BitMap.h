#ifndef BITMAP_H
#define BITMAP_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>

#ifdef __cplusplus
extern "C" {
#endif

	typedef uint64_t QWORD;

	typedef struct BitMap {
		QWORD* data;
		QWORD qsize; // QWORD array size
		QWORD size; // bit num;
	}BitMap;

	//BitMap* bitmap_init(BitMap*, QWORD);
	void BitMapDestroy(BitMap** bitMapAddr);
	void BitMapClear(BitMap* bitMap);
	void BitMapSetAll(BitMap* bitMap);

	BitMap* CreateBitMap(QWORD amount);
	bool BitMapIsSet(BitMap* bitMap, QWORD pos);
	void BitMapSet(BitMap* bitMap, QWORD pos);
	void BitMapReset(BitMap* bitMap, QWORD pos);
	QWORD BitMapFindFirst(BitMap* bitMap, bool* isOk);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _BITMAP_H_