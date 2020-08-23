#include "BitMap.h"

static QWORD qword_lowest_bit(QWORD oneData);
static QWORD qword_highest_bit(QWORD oneData);
static BitMap* bitmap_init(BitMap* bitMap, QWORD amount);

static QWORD qword_lowest_bit(QWORD oneData) // 0 ~ 63      
{
	QWORD n = 63; //0x 
	if (oneData & 0x00000000ffffffff) {
		n -= 32;
		oneData &= 0x00000000ffffffff;
	}
	if (oneData & 0x0000ffff0000ffff) {
		n -= 16;
		oneData &= 0x0000ffff0000ffff;
	}
	if (oneData & 0x00ff00ff00ff00ff) {
		n -= 8;
		oneData &= 0x00ff00ff00ff00ff;
	}
	if (oneData & 0x0f0f0f0f0f0f0f0f) {
		n -= 4;
		oneData &= 0x0f0f0f0f0f0f0f0f;
	}
	if (oneData & 0x3333333333333333) {
		n -= 2;
		oneData &= 0x3333333333333333;
	}
	if (oneData & 0x5555555555555555) {
		n -= 1;
	}
	return n;
}

static QWORD qword_highest_bit(QWORD oneData) // 0 ~ 63
{
	QWORD n = 0;
	if (oneData & 0xffffffff00000000) {
		n += 32;
		oneData &= 0xffffffff00000000;
	}
	if (oneData & 0xffff0000ffff0000) {
		n += 16;
		oneData &= 0xffff0000ffff0000;
	}
	if (oneData & 0xff00ff00ff00ff00) {
		n += 8;
		oneData &= 0xff00ff00ff00ff00;
	}
	if (oneData & 0xf0f0f0f0f0f0f0f0) {
		n += 4;
		oneData &= 0xf0f0f0f0f0f0f0f0;
	}
	if (oneData & 0xcccccccccccccccc) {
		n += 2;
		oneData &= 0xcccccccccccccccc;
	}
	if (oneData & 0xaaaaaaaaaaaaaaaa) {
		n += 1;
	}
	return n;
}

static BitMap* bitmap_init(BitMap* bitMap, QWORD amount)
{
	bitMap->qsize = (amount >> 6) + ((amount & 0x3f) ? 1 : 0);
	bitMap->data = (QWORD*)malloc(bitMap->qsize << 3);
	if (!bitMap->data)
		return NULL;
	bitMap->size = amount;
	return bitMap;
}

void BitMapClear(BitMap* bitMap)
{
	memset(bitMap->data, 0, bitMap->qsize << 3);
}

void BitMapSetAll(BitMap* bitMap)
{
	memset(bitMap->data, 0xff, bitMap->qsize << 3);
}

void BitMapDestroy(BitMap** bitMap)
{
	free((*bitMap)->data);
	(*bitMap)->data = NULL;
	(*bitMap)->size = 0;
	free(*bitMap);
	*bitMap = NULL;
}

BitMap* CreateBitMap(QWORD amount)
{
	BitMap* bmap = (BitMap*)malloc(sizeof(BitMap));
	if (!bmap || !bitmap_init(bmap, amount))
		return NULL;
	BitMapClear(bmap);
	return bmap;
}

bool BitMapIsSet(BitMap* bitMap, QWORD pos)
{
	QWORD q = ((QWORD)1) << (pos & 0x3f);
	return (bitMap->data[pos >> 6] & q) ? true : false;
}

void BitMapSet(BitMap* bitMap, QWORD pos)
{
	QWORD q = ((QWORD)1) << (pos & 0x3f);
	bitMap->data[pos >> 6] |= q;
}

void BitMapReset(BitMap* bitMap, QWORD pos)
{
	QWORD q = ((QWORD)1) << (pos & 0x3f);
	bitMap->data[pos >> 6] &= ~q;
}

QWORD BitMapFindFirst(BitMap* bitMap, bool* isOk)
{
	QWORD i = 0, res = 0;
	for (; i < bitMap->qsize; ++i)
		if (bitMap->data[i] ^ 0xffffffffffffffff)
			break;
	if (i == bitMap->qsize) {
		if (isOk)
			*isOk = false;
		return i;
	}
	res = (i << 6) + qword_lowest_bit(~bitMap->data[i]);
	if (isOk) {
		if (res < bitMap->size)
			*isOk = true;
		else
			*isOk = false;
	}
	return res;
}