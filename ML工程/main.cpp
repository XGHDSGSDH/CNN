#include "data_handler.hpp"
#include<cstdio>
#include<algorithm>

int main()
{
	data_handler *dh=new data_handler();
	dh->read_feature_vector("./train-images.idx3-ubyte"); 
	dh->read_feature_label("./train-labels.idx1-ubyte");
	dh->split_data();
	dh->count_classes();
	return 0;
}
