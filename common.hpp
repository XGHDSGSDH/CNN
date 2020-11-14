#ifndef COMMON_HPP
#define COMMON_HPP

#include "data.hpp"
#include <vector>

class common_data
{
	protected:
		std::vector<data*> *training_data;//—µ¡∑ 
		std::vector<data*> *test_data;//≤‚ ‘ 
		std::vector<data*> *validation_data;//—È÷§
	
	public:
		void set_training_data(std::vector<data*> *vect);
		void set_validation_data(std::vector<data*> *vect);
		void set_test_data(std::vector<data*> *vect);
	
};
#endif
