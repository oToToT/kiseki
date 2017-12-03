// I/O optimization start {{{
static inline int_fast32_t fastAtoi(const char *p, uint_fast32_t len) {
	uint_fast32_t res = 0;
	uint_fast8_t neg = *p == '-';
	if (neg) p++, len--;
	switch (len) {
		case 10: res += (*p++ & 15) * 1000000000;
		case 9: res += (*p++ & 15) * 100000000;
		case 8: res += (*p++ & 15) * 10000000;
		case 7: res += (*p++ & 15) * 1000000;
		case 6: res += (*p++ & 15) * 100000;
		case 5: res += (*p++ & 15) * 10000;
		case 4: res += (*p++ & 15) * 1000;
		case 3: res += (*p++ & 15) * 100;
		case 2: res += (*p++ & 15) * 10;
		case 1: res += (*p & 15);
	}
	return res * (neg ? -1 : 1);
}

static inline bool getRawChar(char *c) {
	static char buf[1 << 20], *p = buf, *end = buf;
	if (p == end) {
		if ((end = buf + fread(buf, 1, 1 << 20, stdin)) == buf) return false;
		p = buf;
	}
	*c = *p++;
	return true;
}

static inline bool getInt(int32_t *x) {
	static char buf[12];
	uint_fast32_t i = 0;
	while (getRawChar(buf + i)) {
		if ((unsigned)(buf[i] - '0') > 10U && buf[i] != '-') {
			if (i) break;
			else continue;
		}
		i++;
	}
	if (!i) return false;
	*x = fastAtoi(buf, i);
	return true;
}
// I/O optimization end }}}