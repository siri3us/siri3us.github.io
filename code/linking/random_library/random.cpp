unsigned int _seed;

unsigned int get_random_number() {
	_seed = (_seed + 1) * 123456789u;
	return _seed;
}
