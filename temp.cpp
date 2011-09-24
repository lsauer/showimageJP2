int num;

void le2be(int&num) {
	int Lby = num & 0x00FF;
	Lby <<= 8;
	num >>= 8;
	num |= Lby;

	//return num;
}