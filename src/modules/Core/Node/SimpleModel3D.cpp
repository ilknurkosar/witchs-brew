#include "SimpleModel3D.hpp"
#include "SimpleModelResource.hpp"

// input data mush be a void pointer array with {SimpleModelResource*}
void SimpleModel3D::Init(void** data){
    smodel = (SimpleModelResource*)data[0];
}