#include "Primitives.h"

Primitives::Primitives() {
	vertexCount, indexCount = 0;
}
Primitives::Primitives(int vCount, int iCount) {
	vertexCount = vCount;
	indexCount = iCount;
}
Primitives::~Primitives() {

}
