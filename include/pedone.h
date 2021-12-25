#include "scacchiera.h"

class Pedone : public Pedina
{

public:
	Pedone(int l, int n, bool color) : Pedina(l, n, color) {}
	bool move(int, int) override;
	bool checkPos() override;
};