#ifndef __DATA_HANDLER
#define __DATA_HANDLER

#include<cstdio>
#include<vector>
#include<string>
#include<map>
#include "data.hpp"


class data_handler
{
	std::vector<data*> *data_array; //提前裂开(误 
	std::vector<data*> *training_data;//训练 
	std::vector<data*> *test_data;//测试 
	std::vector<data*> *validation_data;//验证
	
	int num_classes,feature_vector_size;
	std::map<uint8_t,int> class_map;
	
	const double training_percent=0.75;
	const double test_percent=0.2;
	const double validation_percent=0.05;
	
	public:
		data_handler();
		~data_handler();
		
		void read_feature_vector(std::string path);
		void read_feature_label(std::string path);
		void split_data();
		void count_classes();
		
		uint32_t convert_to_little_endian(const unsigned char* bytes);
		
		std::vector<data*> * get_training_data();
		std::vector<data*> * get_test_data();
		std::vector<data*> * get_validation_data();
};

#endif
