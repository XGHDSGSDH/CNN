#ifndef __DATA_H 
#define __DATA_H

#include<cstdio>
#include<vector>
#include<stdint.h> 

class data
{
	std::vector<uint8_t> * feature_vector;//label放在下面 
	uint8_t label;
	int enum_label;//大类型
	
	public:
		data();
		~data();
		void set_feature_vector(std::vector<uint8_t> *);
		void set_label(uint8_t);
		void set_enumerated_label(int);
		void append_to_feature_vector(uint8_t);
		
		int get_feature_vector_size();
		uint8_t get_label();
		int get_enumerated_label();
		std::vector<uint8_t> * get_feature_vector();
};
#endif
